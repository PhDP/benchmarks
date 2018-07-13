#ifndef EXPR_BT_HH_
#define EXPR_BT_HH_

#include <string>
#include <boost/variant.hpp>

namespace bt {

// Forward declarations:
struct addition;
struct substraction;
struct multiplication;
struct division;

// The variant for the expression:
using expr = boost::variant<
  int,
  std::string,
  boost::recursive_wrapper<addition>,
  boost::recursive_wrapper<substraction>,
  boost::recursive_wrapper<multiplication>,
  boost::recursive_wrapper<division>>;

// A base class for all binary operations:
class binary_op {
 public:
  binary_op(expr const& lhs, expr const& rhs) : m_lhs(lhs), m_rhs(rhs) { }
  auto left() const -> expr const& { return m_lhs; }
  auto right() const -> expr const& { return m_rhs; }
 private:
  expr m_lhs, m_rhs;
};

struct addition : public binary_op {
  addition(expr const& left, expr const &right) : binary_op(left, right) { }
};

struct substraction : public binary_op {
  substraction(expr const& left, expr const &right) : binary_op(left, right) { }
};

struct multiplication : public binary_op {
  multiplication(expr const& left, expr const &right) : binary_op(left, right) { }
};

struct division : public binary_op {
  division(expr const& left, expr const &right) : binary_op(left, right) { }
};

// Overload * and + to simplify creating expressions.

inline auto operator+(expr const& lhs, expr const& rhs) -> expr {
  return addition{lhs, rhs};
}

inline auto operator-(expr const& lhs, expr const& rhs) -> expr {
  return substraction{lhs, rhs};
}

inline auto operator*(expr const& lhs, expr const& rhs) -> expr {
  return multiplication{lhs, rhs};
}

inline auto operator/(expr const& lhs, expr const& rhs) -> expr {
  return division{lhs, rhs};
}

struct add_visit : public boost::static_visitor<expr> {
  auto operator()(int lhs, int rhs) const -> expr {
    return expr{lhs + rhs};
  }

  template<typename R>
  auto operator()(int lhs, R const& rhs) const -> expr {
    return lhs == 0? expr{rhs} : addition{expr{lhs}, expr{rhs}};
  }

  template<typename L>
  auto operator()(L const& lhs, int rhs) const -> expr{
    return rhs == 0? expr{lhs} : addition{expr{lhs}, expr{rhs}};
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return addition{expr{lhs}, expr{rhs}};
  }
};

struct sub_visit : public boost::static_visitor<expr> {
  auto operator()(int lhs, int rhs) const -> expr {
    return expr{lhs - rhs};
  }

  template<typename R>
  auto operator()(int lhs, R const& rhs) const -> expr {
    return lhs == 0? expr{rhs} : substraction{expr{lhs}, expr{rhs}};
  }

  template<typename L>
  auto operator()(L const& lhs, int rhs) const -> expr{
    return rhs == 0? expr{lhs} : substraction{expr{lhs}, expr{rhs}};
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return substraction{expr{lhs}, expr{rhs}};
  }
};

struct mul_visit : public boost::static_visitor<expr> {
  auto operator()(int lhs, int rhs) const -> expr {
    return expr{lhs * rhs};
  }

  template<typename R>
  auto operator()(int lhs, R const& rhs) const -> expr {
    return lhs == 0?
      expr{0} : (lhs == 1? expr{rhs} : multiplication{expr{lhs}, expr{rhs}});
  }

  template<typename L>
  auto operator()(L const& lhs, int rhs) const -> expr {
    return rhs == 0?
      expr{0} : (rhs == 1? expr{lhs} : multiplication{expr{rhs}, expr{lhs}});
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return multiplication{expr{lhs}, expr{rhs}};
  }
};

struct div_visit : public boost::static_visitor<expr> {
  auto operator()(int lhs, int rhs) const -> expr {
    return expr{lhs / rhs};
  }

  template<typename R>
  auto operator()(int lhs, R const& rhs) const -> expr {
    return lhs == 0? expr{0} : division{expr{lhs}, expr{rhs}};
  }

  template<typename L>
  auto operator()(L const& lhs, int rhs) const -> expr {
    return rhs == 1? expr{lhs} : division{expr{lhs}, expr{rhs}};
  }

  template<typename L, typename R>
  auto operator()(L const& lhs, R const& rhs) const -> expr {
    return division{expr{lhs}, expr{rhs}};
  }
};

struct simplify1 : public boost::static_visitor<expr> {
  auto operator()(addition const& a) const -> expr {
    return boost::apply_visitor(add_visit{}, a.left(), a.right());
  }

  auto operator()(substraction const& s) const -> expr {
    return boost::apply_visitor(sub_visit{}, s.left(), s.right());
  }

  auto operator()(multiplication const& m) const -> expr {
    return boost::apply_visitor(mul_visit{}, m.left(), m.right());
  }

  auto operator()(division const& d) const -> expr {
    return boost::apply_visitor(div_visit{}, d.left(), d.right());
  }

  template<typename T>
  auto operator()(T const& t) const -> expr {
    return expr{t};
  }
};

struct simplify : public boost::static_visitor<expr> {
  auto operator()(addition const& a) const -> expr {
    auto left = boost::apply_visitor(simplify{}, a.left());
    auto right = boost::apply_visitor(simplify{}, a.right());
    auto add_lr = boost::apply_visitor(add_visit{}, left, right);
    return boost::apply_visitor(simplify1{}, add_lr);
  }

  auto operator()(substraction const& s) const -> expr {
    auto left = boost::apply_visitor(simplify{}, s.left());
    auto right = boost::apply_visitor(simplify{}, s.right());
    auto sub_lr = boost::apply_visitor(sub_visit{}, left, right);
    return boost::apply_visitor(simplify1{}, sub_lr);
  }

  auto operator()(multiplication const& m) const -> expr {
    auto left = boost::apply_visitor(simplify{}, m.left());
    auto right = boost::apply_visitor(simplify{}, m.right());
    auto mul_lr = boost::apply_visitor(mul_visit{}, left, right);
    return boost::apply_visitor(simplify1{}, mul_lr);
  }

  auto operator()(division const& d) const -> expr {
    auto left = boost::apply_visitor(simplify{}, d.left());
    auto right = boost::apply_visitor(simplify{}, d.right());
    auto div_lr = boost::apply_visitor(div_visit{}, left, right);
    return boost::apply_visitor(simplify1{}, div_lr);
  }

  template<typename T>
  auto operator()(T const& t) const -> expr {
    return expr{t};
  }
};

} /* end namespace bt */

#endif
