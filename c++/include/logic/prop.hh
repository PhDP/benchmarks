#ifndef LOGIC_PROP_HH_
#define LOGIC_PROP_HH_

#include <string>
#include <variant>
#include <memory>
#include <unordered_set>

namespace logic {

// Forward declarations:
struct bottom {};
class negation;
class disjunction;

// The variant for the expression:
using formula = std::variant<
  bottom,
  std::string,
  std::shared_ptr<negation>,
  std::shared_ptr<disjunction>>;

class negation {
 public:
  negation(formula const& f) : m_child(f) {}
  auto child() const -> formula const& { return m_child; }
 private:
  formula m_child;
};

auto make_negation(formula const& f) -> formula { return std::make_shared<negation>(negation{f}); }

class disjunction {
 public:
  disjunction(formula const& l, formula const& r) : m_lhs(l), m_rhs(r) {}
  auto lhs() const -> formula const& { return m_lhs; }
  auto rhs() const -> formula const& { return m_rhs; }
 private:
  formula m_lhs, m_rhs;
};

auto make_disjunction(formula const& l, formula const& r) -> formula {
  return std::make_shared<disjunction>(disjunction{l, r});
}

auto make_conjunction(formula const& l, formula const& r) -> formula {
  return make_negation(make_disjunction(make_negation(l), make_negation(r)));
}

auto top() -> formula { return make_negation(bottom()); }

struct eval_vstr {
  std::unordered_set<std::string> const& m_values;
  
  eval_vstr(std::unordered_set<std::string> const& values) : m_values(values) {}
  
  auto operator()(bottom const&) const -> bool { return false; }
  
  auto operator()(std::string const& v) const -> bool { return m_values.find(v) != m_values.end(); }
  
  auto operator()(std::shared_ptr<negation> const& n) const -> bool {
    return !std::visit(eval_vstr{m_values}, n->child());
  }
  
  auto operator()(std::shared_ptr<disjunction> const& d) const -> bool {
    return std::visit(eval_vstr{m_values}, d->lhs()) || std::visit(eval_vstr{m_values}, d->rhs());
  }
};

auto eval(formula const& f, std::unordered_set<std::string> const& values) {
  return std::visit(eval_vstr{values}, f);
}

} /* end namespace logic */

#endif
