#ifndef OO_GATES_HH_
#define OO_GATES_HH_

#include <iostream>
#include <memory>
#include <vector>

namespace oo_gate {

// Base class for gates:
struct gate {
  virtual void apply(std::vector<bool>& bits) const = 0;
  virtual std::ostream& print(std::ostream&) const = 0;
};

inline auto operator<<(std::ostream& os, gate const& g) -> std::ostream& {
  return g.print(os);
}

struct toffoli_gate : public gate {
  uint32_t c0, c1, x;
  toffoli_gate(uint32_t c0_, uint32_t c1_, uint32_t x_) noexcept
    : c0(c0_), c1(c1_), x(x_) {
  }
  auto apply(std::vector<bool>& bits) const -> void {
    if (bits[c0] && bits[c1]) bits[x] = !bits[x];
  }
  auto print(std::ostream& os) const -> std::ostream& {
    os << "toffoli(" << c0 << ',' << c1 << ',' << x << ')';
    return os;
  };
};

struct fredkin_gate : public gate {
  uint32_t c, a, b;
  fredkin_gate(uint32_t c_, uint32_t a_, uint32_t b_) noexcept
    : c(c_), a(a_), b(b_) {
  }
  auto apply(std::vector<bool>& bits) const -> void {
    if (bits[c]) {
      // std::vector<bool>'s operator() returns values so std::swap would fail here.
      auto const old_a = bits[a];
      bits[a] = bits[b];
      bits[b] = old_a;
    }
  }
  auto print(std::ostream& os) const -> std::ostream& {
    os << "fredkin(" << c << ',' << a << ',' << b << ')';
    return os;
  };
};

struct not_gate : public gate {
  uint32_t x;
  not_gate(uint32_t x_) noexcept : x(x_) { }
  auto apply(std::vector<bool>& bits) const -> void {
    bits[x] = !bits[x];
  }
  auto print(std::ostream& os) const -> std::ostream& {
    os << "not(" << x << ')';
    return os;
  };
};

struct cnot_gate : public gate {
  uint32_t c, x;
  cnot_gate(uint32_t c_, uint32_t x_) noexcept : c(c_), x(x_) { }
  auto apply(std::vector<bool>& bits) const -> void {
    if (bits[c]) bits[x] = !bits[x];
  }
  auto print(std::ostream& os) const -> std::ostream& {
    os << "cnot(" << c << ',' << x << ')';
    return os;
  };
};

struct swap_gate : public gate {
  uint32_t a, b;
  swap_gate(uint32_t a_, uint32_t b_) noexcept : a(a_), b(b_) { }
  auto apply(std::vector<bool>& bits) const -> void {
    auto const old_a = bits[a];
    bits[a] = bits[b];
    bits[b] = old_a;
  }
  auto print(std::ostream& os) const -> std::ostream& {
    os << "swap(" << a << ',' << b << ')';
    return os;
  };
};

// Must store pointers, I use unique to avoid memory management:
using gates = std::vector<std::unique_ptr<gate>>;

// Useful helper to add gates to a vector:
template<typename Gate>
auto add_gate(gates& gs, Gate const& g) {
  gs.push_back(std::make_unique<Gate>(g));
}

inline auto apply_gates(std::vector<bool> const& bits, gates const& gs) -> std::vector<bool> {
  auto new_bits = bits;
  for (auto const& g : gs) g->apply(new_bits);
  return new_bits;
}

} /* end namespace */

#endif
