#ifndef __TRANSPOSITION_TABLE_HPP__
#define __TRANSPOSITION_TABLE_HPP__

// It is interesting to consider whether this class would be better removed and replaced with an std::unordered_map.
// Initially, I was unsure whether the baggage of unordered_map would be too great. Although this is a fallacy in of itself,
// as one should use std:: components and only change if profiling suggests so. 

// TODO: Look into using an ordered_map as the underlying transposition table and profile. 

#include <vector>
#include <cassert>

template <typename cache_type, typename key_type = std::uint64_t>
class Transposition_Table
{
public:

	// Aggregate type for pairing a zobrist key with some evaluation_type (or cache_type).
	struct Record
	{
		key_type m_key{};
		cache_type m_value{};

		// We need only check that the keys match for equality. We may get collisions! but this is a risk we're willing to take.
		inline constexpr bool operator==(Record const& rhs) const { return (m_key == rhs.m_key); }
	};

	using value_type = Record;
	using container_type = std::vector<value_type>;
	using iterator = container_type::iterator;
	using const_iterator = container_type::const_iterator;

	// Perform one large allocation of the entire vector. Because it's a hash map it's not like we're going to expand/grow the thing.
	Transposition_Table(const int size) : m_size(size), m_table(container_type(m_size, value_type{})) {}

	inline constexpr value_type make_record(key_type const& key, cache_type const& value) const { return value_type{ key, value }; }

	// Various insertion overloads. 
	// TODO: emplacement.
	inline constexpr void insert_record(value_type const& record) { (*this)[record.m_key] = record; }
	inline constexpr void insert_record(key_type const& key, cache_type const& value) { insert_record(make_record(key, value)); }

	// Utility for clearing the table.
	inline void clear() { std::fill(m_table.begin(), m_table.end(), value_type{}); }
	
	// Utility for converting a key to a transposition table index. 
	// TODO: Read up on chinese theorem can probably reduce size of key.
	inline constexpr int key_to_index(const key_type& key) const { return (key % m_size); }

	inline constexpr iterator begin() { return m_table.begin(); }
	inline constexpr iterator end() { return m_table.end(); }

	inline constexpr const_iterator begin() const { return m_table.begin(); }
	inline constexpr const_iterator end() const { return m_table.end(); }
	inline constexpr const_iterator cbegin() const { return m_table.cbegin(); }
	inline constexpr const_iterator cend() const { return m_table.cend(); }

	// Utility for performing a look up on the transposition table.
	// Essentially, if we find an empty record we return the sentinel iterator (end()), otherwise we return an iterator to the record.
	inline const_iterator find(const key_type& key) const { int index{ key_to_index(key) }; return (m_table[index] != value_type{}) ? (cbegin() + index) : cend(); }
	inline iterator find(const key_type& key) { int index{ key_to_index(key) }; return (m_table[index] != value_type{}) ? (begin() + index) : end(); }

	// Utility for accessing records. This is more akin to behaviour of an std::map. i.e, we return a reference and allow mutability of the record.
	inline constexpr Record const& operator[](const key_type& key) const { return m_table[key_to_index(key)]; }
	inline constexpr Record& operator[](const key_type& key) { return m_table[key_to_index(key)]; }

private:

	int m_size{};
	container_type m_table{};
};

#endif