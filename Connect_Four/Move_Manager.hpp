#ifndef __MOVE_MANAGER_HPP__
#define __MOVE_MANAGER_HPP__

#include <initializer_list>

#include "Move.hpp"
#include "Move_List.hpp"
#include "Perspective.hpp"

class Move_Manager
{
public:

	Move_Manager(const int move_offset, std::initializer_list<Move> const& moves) : m_move_offset(move_offset), m_moves(Move_List(moves)) {}
	Move_Manager() : Move_Manager(0, {}) {}

	// One can only access the underlying move list GIVEN a perspective. Although it is not impossible to work with a `stale' Move_List it certainly is A LOT harder.
	inline Move_List const& operator()(Perspective const& perspective) { m_moves.set_perspective(perspective); return m_moves; }

	inline void apply_move(Move const& applied_move) { m_moves[applied_move.m_column].m_index += m_move_offset; }
	inline void revert_move(Move const& reverted_move) { m_moves[reverted_move.m_column].m_index -= m_move_offset; }

private:

	int m_move_offset{};
	Move_List m_moves{};
};

#endif