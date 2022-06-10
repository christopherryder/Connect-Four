#ifndef __ZOBRIST_ATLAS_HPP__
#define __ZOBRIST_ATLAS_HPP__

#include <limits>
#include <vector>
#include <random>
#include <algorithm>

#include <cassert>

template <typename zobrist_key_type, zobrist_key_type min = std::numeric_limits<zobrist_key_type>::min(), zobrist_key_type max = std::numeric_limits<zobrist_key_type>::max()>
class Zobrist_Table
{
public:

	Zobrist_Table(const int table_size) : m_keys(make_keys(table_size)) {}
	Zobrist_Table() : Zobrist_Table(0) {}

	// These Keys are not and should not be mutable.
	inline constexpr zobrist_key_type operator[](const int index) const { return m_keys[index]; }

private:

	inline const std::vector<zobrist_key_type> make_keys(const int table_size) const
	{
		std::random_device rd;
		std::mt19937_64 mt(rd());
		std::uniform_int_distribution<zobrist_key_type> key_distribution(min, max);

		// TODO: See if this overflow warning goes away with VS2022. I can guarantee that this will not overflow lol.
		std::vector<zobrist_key_type> tmp(table_size, zobrist_key_type{});

		// Note: the capture list [&] in the lambda.
		// std::generate takes its generator argument by value. Hence we must send references to the device, engine, and distribution.
		std::generate(tmp.begin(), tmp.end(), [&key_distribution, &mt]() { return key_distribution(mt); });

		return tmp;
	}

	std::vector<zobrist_key_type> m_keys{};
};

template <typename atlas_key_type, typename zobrist_key_type = std::uint64_t>
class Zobrist_Atlas
{
private:

	// Aggregate type for pairing a zobrist table with a key type.
	struct Mapped_Zobrist_Table
	{
		atlas_key_type m_key{};
		Zobrist_Table<zobrist_key_type> m_value{};
	};

public:

	Zobrist_Atlas(const int table_size, std::initializer_list<atlas_key_type> const& atlas_keys) : m_table_size(table_size), m_atlas_size(static_cast<int>(atlas_keys.size())), m_atlas(make_atlas(table_size, atlas_keys)) {}
	Zobrist_Atlas() : Zobrist_Atlas(0, {}) {}
	
	template <bool assert_on_not_found>
	inline const zobrist_key_type get_zobrist_key(const atlas_key_type atlas_key, const int index) const
	{
		// Check for out of bounds.
		assert(index < m_table_size && "Index out of zobrist table range!");

		// Search for the atlas key in the atlas.
		auto table_iterator = std::find_if(m_atlas.cbegin(), m_atlas.cend(), [atlas_key](Mapped_Zobrist_Table const& table) { return (table.m_key == atlas_key); });

		// If we can find the atlas, i.e WE DO NOT FIND THE END, then return the corresponding index from the found zobrist table.
		if (table_iterator != m_atlas.end())
			return (*table_iterator).m_value[index];

		// Otherwise, if a zobrist table with this key does not exist, we return 0 as A ^= 0 = A for all A.
		// TODO: Log this somehow. Although this will not change/invalidate the state of the hash it does allow some degree of `fail quietly'.
		// Assert will suffice for now.
		if constexpr (assert_on_not_found) 
			assert(false && "Unable to find atlast_key in atlas!");

		return zobrist_key_type{ 0 };
	}

	inline constexpr int table_ssize() const { return m_table_size; }
	inline constexpr int atlas_ssize() const { return m_atlas_size; }

private:

	inline const std::vector<Mapped_Zobrist_Table> make_atlas(const int table_size, std::initializer_list<atlas_key_type> const& atlas_keys) const
	{
		std::vector<Mapped_Zobrist_Table> tmp{};
		
		// Is there any benefit to doing this vs using a normal for loop? No.
		std::for_each(atlas_keys.begin(), atlas_keys.end(), 
			[table_size, &tmp](atlas_key_type const& key)
			{ 
				tmp.push_back(Mapped_Zobrist_Table{ key, Zobrist_Table<zobrist_key_type>(table_size) }); 
			}
		);

		return tmp;
	}

	int m_table_size{};
	int m_atlas_size{};
	std::vector<Mapped_Zobrist_Table> m_atlas{};
};

#endif
