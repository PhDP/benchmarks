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
  auto left() const -> expr const& { return m_lhs; }
  auto right() const -> expr const& { return m_rhs; }
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

struct add_visit {
  auto operator()(int64_t lhs, int64_t rhs) const -> expr {
    return expr{lhs + rhs};
  }

  template<typename R>
  auto operator()(int64_t lhs, R const& rhs) const -> expr {
    return lhs == 0? expr{rhs} : expr{lhs} + expr{rhs};
  }

  template<typename L>
  auto operator()(L const& lhs, int64_t rhs) const -> expr{
    return rhs == 0? expr{lhs} : expr{lhs} + expr{rhs};
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return expr{lhs} + expr{rhs};
  }
};

struct sub_visit {
  auto operator()(int64_t lhs, int64_t rhs) const -> expr {
    return expr{lhs - rhs};
  }

  template<typename R>
  auto operator()(int64_t lhs, R const& rhs) const -> expr {
    return lhs == 0? expr{rhs} : expr{lhs} - expr{rhs};
  }

  template<typename L>
  auto operator()(L const& lhs, int64_t rhs) const -> expr{
    return rhs == 0? expr{lhs} : expr{lhs} - expr{rhs};
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return expr{lhs} - expr{rhs};
  }
};

struct mul_visit {
  auto operator()(int64_t lhs, int64_t rhs) const -> expr {
    return expr{lhs * rhs};
  }

  template<typename R>
  auto operator()(int64_t lhs, R const& rhs) const -> expr {
    return lhs == 0?
      expr{0} : (lhs == 1? expr{rhs} : expr{lhs} * expr{rhs});
  }

  template<typename L>
  auto operator()(L const& lhs, int64_t rhs) const -> expr {
    return rhs == 0?
      expr{0} : (rhs == 1? expr{lhs} : expr{rhs} * expr{lhs});
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return expr{lhs} * expr{rhs};
  }
};

struct div_visit {
  auto operator()(int64_t lhs, int64_t rhs) const -> expr {
    return expr{lhs / rhs};
  }

  template<typename R>
  auto operator()(int64_t lhs, R const& rhs) const -> expr {
    return lhs == 0? expr{0} : expr{lhs} / expr{rhs};
  }

  template<typename L>
  auto operator()(L const& lhs, int64_t rhs) const -> expr {
    return rhs == 1? expr{lhs} : expr{lhs} / expr{rhs};
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return expr{lhs} / expr{rhs};
  }
};

struct simplify1 {
  auto operator()(addition const& a) const -> expr {
    return std::visit(add_visit{}, a.left(), a.right());
  }

  auto operator()(substraction const& s) const -> expr {
    return std::visit(sub_visit{}, s.left(), s.right());
  }

  auto operator()(multiplication const& m) const -> expr {
    return std::visit(mul_visit{}, m.left(), m.right());
  }

  auto operator()(division const& d) const -> expr {
    return std::visit(div_visit{}, d.left(), d.right());
  }

  template<typename T>
  auto operator()(T const& t) const -> expr {
    return expr{t};
  }
};

struct simplify {
  auto operator()(addition const& a) const -> expr {
    auto left = std::visit(simplify{}, a.left());
    auto right = std::visit(simplify{}, a.right());
    auto add_lr = std::visit(add_visit{}, left, right);
    return std::visit(simplify1{}, add_lr);
  }

  auto operator()(substraction const& s) const -> expr {
    auto left = std::visit(simplify{}, s.left());
    auto right = std::visit(simplify{}, s.right());
    auto sub_lr = std::visit(sub_visit{}, left, right);
    return std::visit(simplify1{}, sub_lr);
  }

  auto operator()(multiplication const& m) const -> expr {
    auto left = std::visit(simplify{}, m.left());
    auto right = std::visit(simplify{}, m.right());
    auto mul_lr = std::visit(mul_visit{}, left, right);
    return std::visit(simplify1{}, mul_lr);
  }

  auto operator()(division const& d) const -> expr {
    auto left = std::visit(simplify{}, d.left());
    auto right = std::visit(simplify{}, d.right());
    auto div_lr = std::visit(div_visit{}, left, right);
    return std::visit(simplify1{}, div_lr);
  }

  template<typename T>
  auto operator()(T const& t) const -> expr {
    return expr{t};
  }
};

} /* end namespace va */

#endif
