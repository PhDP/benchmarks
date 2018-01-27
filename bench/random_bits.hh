#ifndef RANDOM_BITS_HH_
#define RANDOM_BITS_HH_

#include <random>
#include <vector>

inline auto random_bits(std::mt19937_64& rng, size_t nmemb) -> std::vector<bool> {
  auto bits = std::vector<bool>(nmemb, 0);
  auto unif = std::uniform_real_distribution<double>(0.0, 1.0);
  for (auto i = 0u; i < nmemb; ++i) {
    if (unif(rng) < 0.5) bits[i] = 1;
  }
  return bits;
}

#endif
