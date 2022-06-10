#ifndef __BOARD_IMPLEMENTATION_HPP__
#define __BOARD_IMPLEMENTATION_HPP__

#include "Board.hpp"

#include <iomanip>

template<typename value_type_t, typename zobrist_key_type_t>
inline constexpr void Board<value_type_t, zobrist_key_type_t>::set_element(const int index, value_type const& value)
{
	// Trivially, check for bounds.
	assert(index < ssize() && "Board index out of bounds!"); 
	
	// We update the zobrist key BEFORE making a change to the board.
	// We need to XOR out the current value of the element from the Zobrist key.
	// 
	// Consider:
	// let X = (A ^ B) - I.e: X is the current key and it was composed of A ^ B. (I.e: Making a move with key B on the board with key A).
	// Then due to the properties of XOR, (X ^ B) = A. as B ^ B = 0 and X ^ 0 = X.
	update_zobrist_key(m_board[index], index); 
	
	// Follow up by making the new assignment on the board.
	m_board[index] = value;

	// XOR in the new assignment to the Zobrist key.
	update_zobrist_key(value, index);
}

template<typename value_type_t, typename zobrist_key_type_t>
inline std::ostream& Board<value_type_t, zobrist_key_type_t>::stream(std::ostream& os) const
{
	// create dummy index vector 
	std::vector<int> index_board(m_size, 0);
	for (int i{ 0 }; i < m_size; ++i)
	{
		index_board[i] = i;
	}
	
	// flush a newline before printing the board (otherwise the output could be column-misaligned).
	os << '\n';

	for (int i{ 0 }; i < m_rows; ++i)
	{
		// Print a row of board tags.
		for (int j{ 0 }; j < m_columns; ++j)
		{
			os << (*this)((m_rows - 1 - i), j) << ' ';
		}

		os << '\t';

		// Print the indices corresponding to the board tags. 
		for (int j{ 0 }; j < m_columns; ++j)
		{
			os << std::left << std::setw(3) << index_board[index((m_rows - 1 - i), j)] << ' ';
		}

		os << '\n';
	}

	// TODO: Remove this for production.
	// Print the zobrist key, for interest.
	os << "\nThe Zobrist key of this board is: " << m_zobrist_key << '\n';
	return os;
}

template<typename value_type, typename zobrist_key_type>
constexpr Board<value_type, zobrist_key_type>::zobrist_key_type Board<value_type, zobrist_key_type>::make_zobrist_key(const zobrist_key_type initial_key) const
{
	zobrist_key_type zobrist_key{ initial_key };

	// Cache begin and end iterators.
	const_iterator begin_iter = cbegin();
	const_iterator end_iter = cend();
	
	for (const_iterator iter = begin_iter; iter != end_iter; ++iter)
	{
		// NOTE: if the get_zobrist_key() function is fed a value_type that is NOT in the atlas it will return 0 by design
		// as X ^= 0 is equal to X for all X.
		// Hence, we clearly disable the `assert_if_not_found' template parameter.
		zobrist_key ^= m_zobrist_atlas.get_zobrist_key<false>((*iter), static_cast<int>(std::distance(begin_iter, iter)));
	}

	return zobrist_key;
}

template<typename value_type, typename zobrist_key_type>
inline constexpr void Board<value_type, zobrist_key_type>::update_zobrist_key(value_type const& hashable_value, const int index)
{
	// In general, this method should ONLY encounter value_type const&' s that are present in the Zobrist atlas.
	// TODO: It is not possible to set this template flag to true. as when building a board instance via `set_element()' we implicitly attempt to
	// update the zobrist key. Hence setting a board element to a non-hashable value will trigger the assertion.
	m_zobrist_key ^= m_zobrist_atlas.get_zobrist_key<false>(hashable_value, index);
}

#endif