#ifndef BENCH_INSERT_UNIQUE_HH_
#define BENCH_INSERT_UNIQUE_HH_

#include <algorithm>
#include <vector>
#include "benchset/insert_unique.hh"

namespace benchunion {

template<typename T>
auto insert_unique(std::vector<T>& v, T const& t) -> bool {
  if (v.empty() || v.back() < t) {
    v.push_back(t);
    return true;
  }

  auto const it = std::lower_bound(v.begin(), v.end(), t);
  if (*it != t) {
    v.insert(it, t);
    return true;
  }
  return false;
}

template<typename T>
auto insert_unique_noback(std::vector<T>& v, T const& t) -> bool {
  if (v.empty()) {
    v.push_back(t);
    return true;
  }

  auto const it = std::lower_bound(v.begin(), v.end(), t);
  if (*it != t) {
    v.insert(it, t);
    return true;
  }
  return false;
}

} /* end namespace manti */

#endif

