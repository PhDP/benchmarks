#ifndef MYFLAT_HH_
#define MYFLAT_HH_

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <utility>
#include <iterator>
#include <initializer_list>

namespace my {

template<typename T>
using vector = std::vector<T>;

/** A sorted vector used for ordered sets, multisets, maps, multimaps. */
template<typename T>
class flat_tree {
 public:
  using value_type = T;
  using vector_type = vector<T>;
  using size_type = size_t;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using reference = value_type&;
  using const_reference = value_type const&;
  using iterator = typename vector_type::const_iterator;
  using const_iterator = typename vector_type::const_iterator;
  using reverse_iterator = typename vector_type::const_reverse_iterator;
  using const_reverse_iterator = typename vector_type::const_reverse_iterator;

  /** Returns whether the container is empty. */
  auto empty() const noexcept -> bool { return m_vals.empty(); }

  /** Returns how many elements are in the container. */
  auto size() const noexcept -> size_type { return m_vals.size(); }

  /** Returns the number of elements that the container has currently allocated space for. */
  auto capacity() const noexcept -> size_type { return m_vals.capacity(); }

  /** Reserve memoty for n elements. */
  auto reserve(size_type n) { m_vals.reserve(n); }

  /** Shrinks the interval vector to fit its elements. */
  auto shrink_to_fit() { m_vals.shrink_to_fit(); }

  /** Returns the nth elements of the interval vector. */
  auto nth(size_type pos) const -> const_reference { return m_vals[pos]; }

  /** Returns the first element. */
  auto front() const -> const_reference { return m_vals.front(); }

  /** Returns the last element. */
  auto back() const -> const_reference { return m_vals.back(); }

  /** Returns the address of the raw data. */
  auto data() const noexcept -> const_pointer { return m_vals.data(); }

  auto begin() const noexcept -> const_iterator { return m_vals.begin(); }
  auto cbegin() const noexcept -> const_iterator { return m_vals.begin(); }
  auto end() const noexcept -> const_iterator { return m_vals.end(); }
  auto cend() const noexcept -> const_iterator { return m_vals.end(); }
  auto rbegin() const noexcept -> const_reverse_iterator { return m_vals.rbegin(); }
  auto crbegin() const noexcept -> const_reverse_iterator { return m_vals.rbegin(); }
  auto rend() const noexcept -> const_reverse_iterator { return m_vals.rend(); }
  auto crend() const noexcept -> const_reverse_iterator { return m_vals.rend(); }

 protected:
  vector_type m_vals;
};

template<typename Key>
struct flat_set : public flat_tree<Key> {
  using key_type = Key;
  using value_type = key_type;
  using vector_type = vector<key_type>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = key_type*;
  using const_pointer = key_type const*;
  using reference = key_type&;
  using const_reference = key_type const&;
  using iterator = typename flat_tree<Key>::iterator;
  using const_iterator = typename flat_tree<Key>::const_iterator;
  using reverse_iterator = typename flat_tree<Key>::const_reverse_iterator;
  using const_reverse_iterator = typename flat_tree<Key>::const_reverse_iterator;

  flat_set(std::initializer_list<key_type> const& keys) {
    for (auto const& key : keys) insert(key);
  }

  auto find(key_type const& k) const noexcept -> const_iterator {
    if (this->empty()) return this->end();
    auto const i = std::lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    return *i == k? i : this->end();
  }

  auto insert(key_type const& k) {
    if (this->m_vals.empty() || this->m_vals.back() < k) {
      this->m_vals.push_back(k);
      return;
    }
    auto const i = std::lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    if (*i != k) this->m_vals.insert(i, k);
  }
};

template<typename Key>
struct flat_multiset : public flat_tree<Key> {
  using key_type = Key;
  using value_type = key_type;
  using vector_type = vector<key_type>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = key_type*;
  using const_pointer = key_type const*;
  using reference = key_type&;
  using const_reference = key_type const&;
  using iterator = typename flat_tree<Key>::iterator;
  using const_iterator = typename flat_tree<Key>::const_iterator;
  using reverse_iterator = typename flat_tree<Key>::const_reverse_iterator;
  using const_reverse_iterator = typename flat_tree<Key>::const_reverse_iterator;

  flat_multiset(std::initializer_list<Key> const& keys) {
    for (auto const& key : keys) insert(key);
  }

  auto find(Key const& k) const noexcept -> const_iterator {
    if (this->empty()) return this->end();
    auto const i = std::lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    return *i == k? i : this->end();
  }

  auto insert(Key const& k) {
    if (this->m_vals.empty() || this->m_vals.back() < k) {
      this->m_vals.push_back(k);
      return;
    }
    auto const i = std::lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    this->m_vals.insert(i, k);
  }
};

template<typename Key, typename Value>
using pair = std::pair<Key, Value>;

template<typename ForwardIt, typename T>
auto key_lower_bound(ForwardIt fst, ForwardIt lst, T const& value) -> ForwardIt {
  ForwardIt it;
  typename std::iterator_traits<ForwardIt>::difference_type count, step;
  count = std::distance(fst, lst);

  while (count > 0) {
    it = fst;
    step = count / 2;
    std::advance(it, step);
    if (it->first < value) {
      fst = ++it;
      count -= step + 1;
    } else {
      count = step;
    }
  }
  return fst;
}

template<typename Key, typename Value>
struct flat_map : public flat_tree<pair<Key, Value>> {
  using key_type = Key;
  using mapped_type = Value;
  using value_type = pair<key_type, mapped_type>;
  using vector_type = vector<value_type>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using reference = value_type&;
  using const_reference = value_type const&;
  using mapped_type_reference = mapped_type&;
  using iterator = typename flat_tree<value_type>::iterator;
  using const_iterator = typename flat_tree<value_type>::const_iterator;
  using reverse_iterator = typename flat_tree<value_type>::const_reverse_iterator;
  using const_reverse_iterator = typename flat_tree<value_type>::const_reverse_iterator;

  flat_map(std::initializer_list<value_type> const& ps) {
    for (auto const& p : ps) insert(p);
  }

  auto find(key_type const& k) const noexcept -> iterator {
    if (this->empty()) return this->end();
    auto const i = key_lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    return i->first == k? i : this->end();
  }

  auto insert(value_type const& p) -> pair<iterator, bool> {
    if (this->m_vals.empty() || this->m_vals.back().first < p.first) {
      this->m_vals.push_back(p);
      return pair<iterator, bool>(this->m_vals.end() - 1, true);
    }
    auto const i = key_lower_bound(this->m_vals.begin(), this->m_vals.end(), p.first);
    if (i->first != p.first) {
      auto const j = this->m_vals.insert(i, p);
      return pair<iterator, bool>(j, true);
    }
    return pair<iterator, bool>(this->m_vals.end(), false);
  }

  auto operator[](key_type const& k) -> mapped_type_reference {
    auto const i = key_lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    if (i == this->m_vals.end() || i->first != k) {
      value_type p(k, mapped_type());
      auto const j = this->m_vals.insert(i, p);
      return std::get<1>(*j);
    }
    return std::get<1>(*i);
  }
};

template<typename Key, typename Value>
struct flat_multimap : public flat_tree<pair<Key, Value>> {
  using key_type = Key;
  using mapped_type = Value;
  using value_type = pair<key_type, mapped_type>;
  using vector_type = vector<value_type>;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = value_type*;
  using const_pointer = value_type const*;
  using reference = value_type&;
  using const_reference = value_type const&;
  using mapped_type_reference = mapped_type&;
  using iterator = typename flat_tree<value_type>::iterator;
  using const_iterator = typename flat_tree<value_type>::const_iterator;
  using reverse_iterator = typename flat_tree<value_type>::const_reverse_iterator;
  using const_reverse_iterator = typename flat_tree<value_type>::const_reverse_iterator;

  flat_multimap(std::initializer_list<value_type> const& ps) {
    for (auto const& p : ps) insert(p);
  }

  auto find(key_type const& k) const noexcept -> iterator {
    if (this->empty()) return this->end();
    auto const i = key_lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    return i->first == k? i : this->end();
  }

  auto insert(value_type const& p) -> pair<iterator, bool> {
    if (this->m_vals.empty() || this->m_vals.back().first < p.first) {
      this->m_vals.push_back(p);
      return pair<iterator, bool>(this->m_vals.end() - 1, true);
    }
    auto const i = key_lower_bound(this->m_vals.begin(), this->m_vals.end(), p.first);
    auto const j = this->m_vals.insert(i, p);
    return pair<iterator, bool>(j, true);
  }

  // Check if this is how std::multimap behaves (modifying existing if possible).
  auto operator[](key_type const& k) -> mapped_type_reference {
    auto const i = key_lower_bound(this->m_vals.begin(), this->m_vals.end(), k);
    if (i == this->m_vals.end() || i->first != k) {
      value_type p(k, mapped_type());
      auto const j = this->m_vals.insert(i, p);
      return std::get<1>(*j);
    }
    return std::get<1>(*i);
  }
};

} /* end namespace my */

#endif
