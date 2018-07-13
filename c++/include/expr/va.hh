#ifndef EXPR_VA_HH_
#define EXPR_VA_HH_

#include <string>
#include <variant>
#include <memory>

namespace va {

// Forward declarations:
struct addition;
struct substraction;
struct multiplication;
struct division;

// The variant for the expression:
using expr = std::variant<
  int64_t,
  std::string,
  std::shared_ptr<division>,
  std::shared_ptr<substraction>,
  std::shared_ptr<multiplication>,
  std::shared_ptr<addition>>;

// A base class for all binary operations:
class binary_op {
 public:
  binary_op(expr const& lhs, expr const& rhs) : m_lhs(lhs), m_rhs(rhs) { }
  auto lhs() const -> expr const& { return m_lhs; }
  auto rhs() const -> expr const& { return m_rhs; }
 private:
  expr m_lhs, m_rhs;
};

// Defines the 'addition' operator.
struct addition : public binary_op {
  addition(expr const& left, expr const &right) : binary_op(left, right) { }
};

// Defines the 'addition' operator.
struct substraction : public binary_op {
  substraction(expr const& left, expr const &right) : binary_op(left, right) { }
};

// Defines the 'multiplication' operator.
struct multiplication : public binary_op {
  multiplication(expr const& left, expr const &right) : binary_op(left, right) { }
};

// Defines the 'multiplication' operator.
struct division : public binary_op {
  division(expr const& left, expr const &right) : binary_op(left, right) { }
};

inline auto operator+(expr const& lhs, expr const& rhs) -> expr {
  return std::make_shared<addition>(addition{lhs, rhs});
}

inline auto operator-(expr const& lhs, expr const& rhs) -> expr {
  return std::make_shared<substraction>(substraction{lhs, rhs});
}

inline auto operator*(expr const& lhs, expr const& rhs) -> expr {
  return std::make_shared<multiplication>(multiplication{lhs, rhs});
}

inline auto operator/(expr const& lhs, expr const& rhs) -> expr {
  return std::make_shared<division>(division{lhs, rhs});
}

template<typename... Ts> struct overloaded : Ts... { using Ts::operator()...; };
template<typename... Ts> overloaded(Ts...) -> overloaded<Ts...>;

inline auto simplify1(expr const& e) -> expr {
  return std::visit(overloaded {
    [](int x) -> expr { return x; },
    [](std::string const& x) -> expr { return x; },
    [](std::shared_ptr<addition> const& a) -> expr {
      return std::visit(overloaded {
        [&a](int x, int y) -> expr { return x + y; },
        [&a](int x, expr const& y) -> expr { return x == 0? expr(x) : a; },
        [&a](expr const& x, int y) -> expr { return y == 0? expr(x) : a; },
        [&a](expr const& x, expr const& y) -> expr { return a; },
      }, a->lhs(), a->rhs());
    },
    [](std::shared_ptr<substraction> const& s) -> expr {
      return std::visit(overloaded {
        [&s](int x, int y) -> expr { return x - y; },
        [&s](int x, expr const& y) -> expr { return x == 0? expr(x) : s; },
        [&s](expr const& x, int y) -> expr { return y == 0? expr(x) : s; },
        [&s](expr const& x, expr const& y) -> expr { return s; },
      }, s->lhs(), s->rhs());
    },
    [](std::shared_ptr<multiplication> const& m) -> expr {
      return std::visit(overloaded {
        [&m](int x, int y) -> expr { return x * y; },
        [&m](int x, expr const& y) -> expr { return x == 0? 0 : (x == 1? y : m); },
        [&m](expr const& x, int y) -> expr { return y == 0? 0 : (y == 1? x : m); },
        [&m](expr const& x, expr const& y) -> expr { return m; },
      }, m->lhs(), m->rhs());
    },
    [](std::shared_ptr<division> const& d) -> expr {
      return std::visit(overloaded {
        [&d](int x, int y) -> expr { return x / y; },
        [&d](int x, expr const& y) -> expr { return x == 0? 0 : d; },
        [&d](expr const& x, int y) -> expr { return y == 1? x : d; },
        [&d](expr const& x, expr const& y) -> expr { return d; },
      }, d->lhs(), d->rhs());
    }
  }, e);
}

inline auto simplify(expr const& e) -> expr {
  return std::visit(overloaded {
    [](std::shared_ptr<addition> const& a) -> expr {
      return simplify1(simplify(a->lhs()) + simplify(a->rhs()));
    },
    [](std::shared_ptr<substraction> const& s) -> expr {
      return simplify1(simplify(s->lhs()) - simplify(s->rhs()));
    },
    [](std::shared_ptr<multiplication> const& m) -> expr {
      return simplify1(simplify(m->lhs()) * simplify(m->rhs()));
    },
    [](std::shared_ptr<division> const& d) -> expr {
      return simplify1(simplify(d->lhs()) / simplify(d->rhs()));
    },
    [](expr const& x) -> expr { return x; }
  }, e);
}

} /* end namespace va */

#endif
