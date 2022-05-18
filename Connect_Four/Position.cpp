#ifndef __POSITION_CPP__
#define __POSITION_CPP__

#include "Position.hpp"

#include <algorithm>
#include <cassert>

void Position::make_move(Move const& move)
{
	// 1. Update the Board. Assign the previously empty value to the controller.
	m_board[move.m_index] = m_perspective.m_player_id;

	// 2. Update the move_manager by informing it that a move was applied.
	m_move_list.apply_move(move);

	// 3. Update the perspective to reflect the change in player
	m_perspective.swap();
}

void Position::unmake_move(Move const& move)
{
	// 1. Update the Board. Revert the controller value to the neutral value.
	m_board[move.m_index] = m_perspective.m_neutral_id;

	// 2. Update the move_manager by informing it that a move was reverted.
	m_move_list.revert_move(move);

	// 3. Update the perspective to reflect the change in player
	m_perspective.swap();
}

#endif

