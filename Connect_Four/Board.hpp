#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <vector>
#include <ostream>

#include "Zobrist_Atlas.hpp"

template <typename Value_Type, typename Zobrist_Key_Type = std::uint64_t>
class Board
{
public:

	// Define useful type traits of the board.
	using value_type = typename Value_Type;
	using board_type = typename std::vector<value_type>;
	using zobrist_key_type = typename Zobrist_Key_Type;

	using iterator = typename board_type::iterator;
	using const_iterator = typename board_type::const_iterator;

	// This is a slightly too comprehensive constructor, quite heavy to make.
	// TODO: look into slimming down the constructor, potentially allow for the taking of a Zobrist_Atlas object instead of the intializer_list of hashable_values.
	Board(const int rows, const int columns, const value_type& default_tag, std::initializer_list<value_type> const& hashable_values)
		: m_rows{ rows }, m_columns{ columns }, m_default_tag{ default_tag }, m_size{ rows * columns },
		m_board(board_type(m_size, m_default_tag)), m_zobrist_atlas(make_zobrist_atlas(hashable_values)), m_zobrist_key{ make_zobrist_key(0) } {}

	// Allow the board to be default constructible for use in the position class.
	// TODO: look into making the position class a friend. 
	Board() : Board(0, 0, value_type{}, {}) {}

	// Mutability:
	// Main utility of the board, making and unmaking moves.
	// We can also allow an external element to modify the board as long as the integrity of the zobrist key is retained.
	constexpr void set_element(const int index, value_type const& value);

	// Utility for converting a row, column coordinate to a flattened index.
	inline constexpr int index(const int row, const int column) const { return ((row * m_columns) + column); }

	// Define const iterators explicitly using the cbegin, cend methods.
	inline constexpr board_type::const_iterator cbegin() const { return m_board.cbegin(); }
	inline constexpr board_type::const_iterator cend() const { return m_board.cend(); }

	// Define const iterators, for access, using regular begin and end.
	inline constexpr board_type::const_iterator begin() const { return m_board.begin(); }
	inline constexpr board_type::const_iterator end() const { return m_board.end(); }

	// Potentially useful access functions for member data.
	inline constexpr int rows() const { return m_rows; }
	inline constexpr int columns() const { return m_columns; }
	inline constexpr int ssize() const { return m_size; }
	inline constexpr value_type const& default_tag() const { return m_default_tag; }
	inline constexpr zobrist_key_type const& zobrist_key() const { return m_zobrist_key; }

	// Operator Overloads: We only allow const-references to board elements as we need to retain the integrity of the zobrist key.
	inline constexpr value_type const& operator()(const int row, const int column) const { return m_board[index(row, column)]; }
	inline constexpr value_type const& operator[](const int index) const { return m_board[index]; }

	// Output
	std::ostream& stream(std::ostream& os) const;
	friend inline std::ostream& operator<<(std::ostream& os, Board const& board) { return board.stream(os); }

private:

	// Utilities for constructing the Zobrist atlas and Zobrist key.
	inline const Zobrist_Atlas<value_type, zobrist_key_type> make_zobrist_atlas(std::initializer_list<value_type> const& hashable_values) const { return Zobrist_Atlas<value_type, zobrist_key_type>(m_size, hashable_values); }
	constexpr zobrist_key_type make_zobrist_key(const zobrist_key_type initial_key) const;

	// Utilities for making a zobrist_key form the underlying board, or for updating the key.
	constexpr void update_zobrist_key(value_type const& hashable_value, const int index);

	int m_rows{};
	int m_columns{};
	value_type m_default_tag{};

	// The board's border is uniform about it's entire edge.
	int m_size{ m_rows * m_columns };
	std::vector<value_type> m_board{};

	// Store the zobrist keys here too
	Zobrist_Atlas<value_type, zobrist_key_type> m_zobrist_atlas{};
	zobrist_key_type m_zobrist_key{};
};

#include "Board_Implementation.hpp"

#endif