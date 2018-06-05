#ifndef C_GATES_HH_
#define C_GATES_HH_

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint32_t c0;
  uint32_t c1;
  uint32_t x;
} c_toffoli_gate;

typedef struct {
  uint32_t c;
  uint32_t a;
  uint32_t b;
} c_fredkin_gate;

typedef struct {
  uint32_t x;
} c_not_gate;

typedef struct {
  uint32_t c;
  uint32_t x;
} c_cnot_gate;

typedef struct {
  uint32_t a;
  uint32_t b;
} c_swap_gate;

typedef enum {
  c_toffoli_gate_t,
  c_fredkin_gate_t,
  c_not_gate_t,
  c_cnot_gate_t,
  c_swap_gate_t
} c_gate_kind;

typedef struct {
  union {
    c_toffoli_gate t;
    c_fredkin_gate f;
    c_not_gate n;
    c_cnot_gate c;
    c_swap_gate s;
  };
  c_gate_kind kind;
} c_gate;

inline void apply_c_gates(uint8_t* bits, const uint32_t nbits, const c_gate* gates, const uint32_t ngates) {
  uint32_t i = 0;
  for (; i < ngates; ++i) {
    if (gates[i].kind == c_toffoli_gate_t) {
      if (bits[gates[i].t.c0] && bits[gates[i].t.c1]) {
        bits[gates[i].t.x] = !bits[gates[i].t.x];
      }
    } else if (gates[i].kind == c_fredkin_gate_t) {
      if (bits[gates[i].f.c]) {
        const bool old_a = bits[gates[i].f.a]; // The xor trick would do too...
        bits[gates[i].f.a] = bits[gates[i].f.b];
        bits[gates[i].f.b] = old_a;
      }
    } else if (gates[i].kind == c_not_gate_t) {
      bits[gates[i].n.x] = !bits[gates[i].n.x];
    } else if (gates[i].kind == c_cnot_gate_t) {
      if (bits[gates[i].c.c]) {
        bits[gates[i].c.x] = !bits[gates[i].c.x];
      }
    } else if (gates[i].kind == c_swap_gate_t) {
      const bool old_a = bits[gates[i].s.a];
      bits[gates[i].s.a] = bits[gates[i].s.b];
      bits[gates[i].s.b] = old_a;
    }
  }
}

#endif
