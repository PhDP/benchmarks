#ifndef BENCH_UNION_HH_
#define BENCH_UNION_HH_

#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#include <boost/container/flat_set.hpp>
#include "benchset/insert_unique.hh"

namespace benchunion {

template<typename T>
auto flatset_union(boost::container::flat_set<T> const& xs,
                   boost::container::flat_set<T> const& ys) -> boost::container::flat_set<T> {
  auto u = boost::container::flat_set<T>{};
  u.reserve(xs.size() + ys.size());
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (!(*xs_it < *ys_it) && !(*ys_it < *xs_it)) {
      u.insert(*xs_it++);
      ++ys_it;
    } else if (*xs_it < *ys_it) {
      u.insert(*xs_it++);
    } else { // *ys_it < *xs_it
      u.insert(*ys_it++);
    }
  }
  while (xs_it != xs_end) u.insert(*xs_it++);
  while (ys_it != ys_end) u.insert(*ys_it++);
  return u;
}

template<typename T>
auto flatset_union_eh(boost::container::flat_set<T> const& xs,
                      boost::container::flat_set<T> const& ys) -> boost::container::flat_set<T> {
  auto u = boost::container::flat_set<T>{};
  u.reserve(xs.size() + ys.size());
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (!(*xs_it < *ys_it) && !(*ys_it < *xs_it)) {
      u.emplace_hint(u.end(), *xs_it++);
      ++ys_it;
    } else if (*xs_it < *ys_it) {
      u.emplace_hint(u.end(), *xs_it++);
    } else { // *ys_it < *xs_it
      u.emplace_hint(u.end(), *ys_it++);
    }
  }
  while (xs_it != xs_end) u.emplace_hint(u.end(), *xs_it++);
  while (ys_it != ys_end) u.emplace_hint(u.end(), *ys_it++);
  return u;
}

template<typename T>
auto stdset_union(std::set<T> const& xs,
                  std::set<T> const& ys) -> std::set<T> {
  auto u = std::set<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (!(*xs_it < *ys_it) && !(*ys_it < *xs_it)) {
      u.insert(*xs_it++);
      ++ys_it;
    } else if (*xs_it < *ys_it) {
      u.insert(*xs_it++);
    } else { // *ys_it < *xs_it
      u.insert(*ys_it++);
    }
  }
  while (xs_it != xs_end) u.insert(*xs_it++);
  while (ys_it != ys_end) u.insert(*ys_it++);
  return u;
}

template<typename T>
auto stdset_union_eh(std::set<T> const& xs,
                     std::set<T> const& ys) -> std::set<T> {
  auto u = std::set<T>{};
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (!(*xs_it < *ys_it) && !(*ys_it < *xs_it)) {
      u.emplace_hint(u.end(), *xs_it++);
      ++ys_it;
    } else if (*xs_it < *ys_it) {
      u.emplace_hint(u.end(), *xs_it++);
    } else { // *ys_it < *xs_it
      u.emplace_hint(u.end(), *ys_it++);
    }
  }
  while (xs_it != xs_end) u.emplace_hint(u.end(), *xs_it++);
  while (ys_it != ys_end) u.emplace_hint(u.end(), *ys_it++);
  return u;
}

template<typename T>
auto stduset_union(std::unordered_set<T> const& xs,
                   std::unordered_set<T> const& ys) -> std::unordered_set<T> {
  if (xs.size() < ys.size())
    return stduset_union(ys, xs);

  auto u = xs;
  for (auto const& y : ys) u.insert(y);
  return u;
}

template<typename T>
auto sorted_vector_union(std::vector<T> const& xs,
                         std::vector<T> const& ys) -> std::vector<T> {
  auto u = std::vector<T>{};
  u.reserve(std::max(xs.size(), ys.size()));
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (!(*xs_it < *ys_it) && !(*ys_it < *xs_it)) {
      u.push_back(*xs_it++);
      ++ys_it;
    } else if (*xs_it < *ys_it) {
      u.push_back(*xs_it++);
    } else { // *ys_it < *xs_it
      u.push_back(*ys_it++);
    }
  }
  while (xs_it != xs_end) u.push_back(*xs_it++);
  while (ys_it != ys_end) u.push_back(*ys_it++);
  return u;
}


template<typename T>
auto vectorset_union(std::vector<T> const& xs,
                     std::vector<T> const& ys) -> std::vector<T> {
  auto u = std::vector<T>{};
  u.reserve(xs.size() + ys.size());
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (!(*xs_it < *ys_it) && !(*ys_it < *xs_it)) {
      insert_unique(u, *xs_it++);
      ++ys_it;
    } else if (*xs_it < *ys_it) {
      insert_unique(u, *xs_it++);
    } else { // *ys_it < *xs_it
      insert_unique(u, *ys_it++);
    }
  }
  while (xs_it != xs_end) insert_unique(u, *xs_it++);
  while (ys_it != ys_end) insert_unique(u, *ys_it++);
  return u;
}

template<typename T>
auto vectorset_union_noback(std::vector<T> const& xs,
                            std::vector<T> const& ys) -> std::vector<T> {
  auto u = std::vector<T>{};
  u.reserve(xs.size() + ys.size());
  auto const xs_end = xs.end(), ys_end = ys.end();
  auto xs_it = xs.begin(), ys_it = ys.begin();

  while (xs_it != xs_end && ys_it != ys_end) {
    if (!(*xs_it < *ys_it) && !(*ys_it < *xs_it)) {
      insert_unique_noback(u, *xs_it++);
      ++ys_it;
    } else if (*xs_it < *ys_it) {
      insert_unique_noback(u, *xs_it++);
    } else { // *ys_it < *xs_it
      insert_unique_noback(u, *ys_it++);
    }
  }
  while (xs_it != xs_end) insert_unique_noback(u, *xs_it++);
  while (ys_it != ys_end) insert_unique_noback(u, *ys_it++);
  return u;
}

} /* end namespace manti */

#endif
