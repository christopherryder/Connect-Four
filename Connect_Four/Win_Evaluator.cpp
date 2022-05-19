#ifndef __WIN_EVALUATOR_CPP__
#define __WIN_EVALUATOR_CPP__

#include "Win_Evaluator.hpp"

#include <algorithm>

const bool Win_Evaluator::is_winning_move(Position const& position, Move const& move) const
{
	// TODO: Refactor this code, it is sloppy (but it does work).

	// Need to check each unit vector (win direction) for a required streak.
	for (auto const& vector : m_unit_traversal_vectors)
	{
		// We desire to scan forward and backward among the supplied vectors. 
		// We require all supplied vectors to be given in a `forward' direction, and the negation of these is the reverse vector.

		// We store the current streak, initialised to +1 (as we count the move we're evaluating implicitly).
		int current_streak{ 1 };


		// Similar we start the loop from +1 as we don't want to double count the initial move when reversing. 
		for (int i{ 1 }; i < (m_required_streak); ++i)
		{
			// If we manage to encounter the required streak in this direction, we return true.
			if (current_streak == m_required_streak)
			{
				return true;
			}

			// Similarly, if our streak is broken in this direction we break and attempt the reverse.
			if (position.m_board[(move.m_index) + (i * vector)] != move.m_tag)
			{
				break;
			}

			// Otherwise we increment the streak counter.
			current_streak += 1;
		}

		// Similar we start the loop from +1 as we don't want to double count the initial move when reversing. 
		for (int i{ 1 }; i < (m_required_streak); ++i)
		{
			// If we manage to encounter the required streak in this direction, we return true.
			if (current_streak == m_required_streak)
			{
				return true;
			}

			// Similarly, if our streak is broken in this direction we break and attempt the reverse.
			if (position.m_board[(move.m_index) - (i * vector)] != move.m_tag)
			{
				break;
			}

			// Otherwise we increment the streak counter.
			current_streak += 1;
		}

		// Repeat check just in case the last increment was the one.
		if (current_streak == m_required_streak)
		{
			return true;
		}
	}

	// No streak was found in any of the given vectors.
	return false;
}

#endif


