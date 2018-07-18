#ifndef C_LOGIC_PROP_HH_
#define C_LOGIC_PROP_HH_

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <unordered_set>

typedef enum {
  bottom_kind = 0,
  variable_kind = 1,
  negation_kind = 10,
  disjunction_kind = 100
} c_formula_kind;

typedef struct c_formula_ {
  union {
    std::string *var_name;
    struct c_formula_* child;
    struct {
      struct c_formula_* lhs;
      struct c_formula_* rhs;
    };
  };
  c_formula_kind kind;
} c_formula;

inline c_formula* make_variable(std::string const& s) {
  c_formula* f = (c_formula*)malloc(sizeof(c_formula));
  f->kind = variable_kind;
  f->var_name = new std::string(s);
  return f;
}

inline c_formula* make_negation(c_formula* child) {
  c_formula* f = (c_formula*)malloc(sizeof(c_formula));
  f->kind = negation_kind;
  f->child = child;
  return f;
}

inline c_formula* make_bottom() {
  c_formula* f = (c_formula*)malloc(sizeof(c_formula));
  f->kind = bottom_kind;
  return f;
}

inline c_formula* make_top() {
  c_formula* f = (c_formula*)malloc(sizeof(c_formula));
  f->kind = bottom_kind;
  return make_negation(f);
}

inline c_formula* make_disjunction(c_formula* lhs, c_formula* rhs) {
  c_formula* f = (c_formula*)malloc(sizeof(c_formula));
  f->kind = disjunction_kind;
  f->lhs = lhs;
  f->rhs = rhs;
  return f;
}

inline c_formula* make_conjunction(c_formula* lhs, c_formula* rhs) {
  c_formula* f = (c_formula*)malloc(sizeof(c_formula));
  f->kind = disjunction_kind;
  f->lhs = make_negation(lhs);
  f->rhs = make_negation(rhs);
  return make_negation(f);
}

inline void c_formula_free(c_formula *f) {
  switch (f->kind) {
  case variable_kind:
    delete f->var_name;
    break;
  case negation_kind:
    c_formula_free(f->child);
    free(f->child);
    break;
  case disjunction_kind:
    c_formula_free(f->lhs);
    free(f->lhs);
    c_formula_free(f->rhs);
    free(f->rhs);
    break;
  }
}

inline bool c_eval(c_formula const* f, std::unordered_set<std::string> const& values) {
  switch (f->kind) {
  case bottom_kind:
    return false;
  case variable_kind:
    return values.find(*f->var_name) != values.end();
  case negation_kind:
    return !c_eval(f->child, values);
  case disjunction_kind:
    return c_eval(f->lhs, values) || c_eval(f->rhs, values);
  }
}

#endif
