#ifndef BENCH_INTERSECTION_HH_
#define BENCH_INTERSECTION_HH_

#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <boost/container/flat_set.hpp>
#include "benchset/insert_unique.hh"

namespace benchunion {

template<typename T>
auto flatset_intersection(boost::container::flat_set<T> const& xs,
                          boost::container::flat_set<T> const& ys)
                          -> boost::container::flat_set<T> {
  auto inter = boost::container::flat_set<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (*xs_it < *ys_it) {
      ++xs_it;
    } else {
      if (!(*ys_it < *xs_it)) {
        inter.insert(*xs_it++);
      }
      ++ys_it;
    }
  }
  return inter;
}

template<typename T>
auto flatset_intersection_eh(boost::container::flat_set<T> const& xs,
                             boost::container::flat_set<T> const& ys)
                             -> boost::container::flat_set<T> {
  auto inter = boost::container::flat_set<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (*xs_it < *ys_it) {
      ++xs_it;
    } else {
      if (!(*ys_it < *xs_it)) {
        inter.emplace_hint(inter.end(), *xs_it++);
      }
      ++ys_it;
    }
  }
  return inter;
}

template<typename T>
auto stdset_intersection(std::set<T> const& xs, std::set<T> const& ys) -> std::set<T> {
  auto inter = std::set<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (*xs_it < *ys_it) {
      ++xs_it;
    } else {
      if (!(*ys_it < *xs_it)) {
        inter.insert(*xs_it++);
      }
      ++ys_it;
    }
  }
  return inter;
}

template<typename T>
auto stdset_intersection_eh(std::set<T> const& xs, std::set<T> const& ys) -> std::set<T> {
  auto inter = std::set<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (*xs_it < *ys_it) {
      ++xs_it;
    } else {
      if (!(*ys_it < *xs_it)) {
        inter.emplace_hint(inter.end(), *xs_it++);
      }
      ++ys_it;
    }
  }
  return inter;
}

template<typename T>
auto stduset_intersection(std::unordered_set<T> const& xs,
                          std::unordered_set<T> const& ys) -> std::unordered_set<T> {
  if (xs.size() > ys.size())
    return stduset_intersection(ys, xs);

  auto inter = std::unordered_set<T>{};
  for (auto const& x : xs) if (ys.find(x) != ys.end()) inter.insert(x);
  return inter;
}

template<typename T>
auto vectorset_intersection(std::vector<T> const& xs,
                            std::vector<T> const& ys) -> std::vector<T> {
  auto inter = std::vector<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (*xs_it < *ys_it) {
      ++xs_it;
    } else {
      if (!(*ys_it < *xs_it)) {
        insert_unique(inter, *xs_it++);
      }
      ++ys_it;
    }
  }
  return inter;
}

template<typename T>
auto vectorset_intersection_noback(std::vector<T> const& xs,
                                   std::vector<T> const& ys) -> std::vector<T> {
  auto inter = std::vector<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (*xs_it < *ys_it) {
      ++xs_it;
    } else {
      if (!(*ys_it < *xs_it)) {
        insert_unique_noback(inter, *xs_it++);
      }
      ++ys_it;
    }
  }
  return inter;
}

} /* end namespace manti */

#endif
