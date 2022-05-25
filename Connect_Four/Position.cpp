#ifndef __POSITION_CPP__
#define __POSITION_CPP__

#include "Position.hpp"

#include <iostream>

void Position::make_move(int& move)
{
	std::cout << "setting [IDX=" << move << ", TAG=" << m_perspective.m_player << "]\n";
	m_board[move] = m_perspective.m_player;

	update_state(move);

	increment_move_row(move);

	m_perspective.swap();
}

void Position::unmake_move(int& move)
{
	m_perspective.swap();

	decrement_move_row(move);

	// This is obviously the case as one cannot continue past a terminal state.
	m_state = State::Ongoing;

	m_board[move] = m_board.default_tag();
}

const bool Position::is_won(const int last_move) const
{
	for (auto const& vector : m_search_vectors)
	{
		if (is_vector_won(last_move, vector))
		{
			return true;
		}
	}

	return false;
}

const bool Position::is_drawn(const int last_move) const
{
	// just need to guarantee the presence of one move to discount the possibility of a draw
	for (auto const& move : moves())
	{
		return false;
	}

	return true;
}

const bool Position::is_vector_won(const int last_move, const int vector) const
{
	// Due to the padding of the board, we can tighten the validation loop, i.e start behind the move and sweep past it.

	int index{ last_move - ((m_required_streak - 1) * vector) };
	int end_index{ last_move + ((m_required_streak - 1) * vector) };

	int current_streak{ 0 };

	for (index; index != end_index; index += vector)
	{
		std::cout << "CHECKING [SOURCE_IDX=" << last_move << ", CURRENT_IDX=" << index << ", VECTOR = " << vector << ", THAT: " << m_board[index] << " = " << m_board[last_move] << "]...\n";
		current_streak = (m_board[index] == m_board[last_move]) ? (current_streak + 1) : 0;

		if (current_streak == m_required_streak)
		{
			std::cout << "WIN FOUND [IDX=" << last_move << ", VECTOR=" << vector << "]\n";
			return true;
		}
	}

	// Could also remove the if from the loop and just return (current_streak >= required_streak) 
	// Would need to profile. It's hard to know whether the extra branch would hurt performance, given that generally we only traverse 7 elements to check a win condition (likely all of these will be in cache)
	// hmm...

	return false;
}

const Position::State Position::get_state(const int last_move)
{
	// Check first for a win position.
	if (is_won(last_move))
	{
		return State::Won;
	}
	
	// If no win, the game could be a draw.
	if (is_drawn(last_move))
	{
		return m_state = State::Drawn;
	}
	
	// Not in a terminal state (won/draw), hence ongoing.
	return State::Ongoing;
}

#endif

