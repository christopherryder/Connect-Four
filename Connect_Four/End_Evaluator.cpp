#ifndef __END_EVALUATOR_CPP__
#define __END_EVALUATOR_CPP__

#include "End_Evaluator.hpp"

#include <algorithm>

End_Evaluator::Evaluation End_Evaluator::evaluate_end(Position const& position, Move const& move) const
{
	// Naturally, one must check for a win first.
	if (is_winning_move(position, move))
	{
		return Evaluation::Win_End;
	}

	// If there are subsequent moves and the last move did not win it cannot be an end.
	if (is_moves_remaining(position))
	{
		return Evaluation::No_End;
	}
	
	// There are no remaining moves and the last move did not win, hence it is a draw.
	return Evaluation::Draw_End;
}

const bool End_Evaluator::is_winning_move(Position const& position, Move const& move) const
{
	// Need to check each unit vector (win direction) for a required streak.
	for (auto const& vector : m_unit_traversal_vectors)
	{
		// So we construct a range object using the current vector.
		Range range{ make_move_evaluation_range(position, move, vector) };
		int current_streak{ 0 };

		for (int i{ range.m_begin }; i <= range.m_end; i += range.m_step)
		{
			// If the streak is continued, increment the counter, otherwise reset the streak to 0.
			current_streak = (position.m_board[i] == move.m_controller) ? (current_streak + 1) : 0;

			// As soon as the required streak is found we can return true, no need to continue evaluation.
			if (current_streak == m_required_streak)
			{
				return true;
			}
		}
	}

	// No streak was found in any of the given vectors.
	return false;
}

const bool End_Evaluator::is_moves_remaining(Position const& position) const
{
	// There are two ways one can perform this, either simply check the moves in the move_list against the position validty predicate
	// OR one can just iterate the move_list, knowing that it only serves valid moves and simply count the number, i.e

	// TODO: This should be refactored to the moves list, it should have a .count() function, then this simply returns move_list<pred=true>.count()
	// Additionally though the move_list should be accessed through a wrapper which dictates whether to use the true/validated counting.

	for (auto const& move : position.m_move_list)
	{
		return true;
	}

	return false;
}

const End_Evaluator::Range End_Evaluator::make_move_evaluation_range(Position const& position, Move const& move, const int vector) const
{
	// The problem with iterating a flat board is that one encounters `wrap-around' problems when traversing column-wise.
	// One does not encounter this problem when traversing row-wise, the beginning and end rows are bounded by [0,size())
	// 
	// However, if the majoring of the matrix representation is changed one would encounter row-wrapping and not column-wrapping.
	//

	// The strategy here is to build a range which encompasses all possible win opportunities for a given vector.
	// I.e, given an index i, the range will, in general, run [ i-(required_streak - 1), i+(required_streak-1) ] if the vector is +1.
	// 
	// To counter the wrap around problem, we need only know what column we're in and use tha to temper the extent of the range.
	//

	int negative_extent{ std::min(m_required_streak - 1, move.m_column) };
	int positive_extent{ std::min(m_required_streak - 1, (position.m_board.columns() - 1 - move.m_column)) };

	int begin{ move.m_index - (negative_extent * vector) };
	int end{ move.m_index + (positive_extent * vector) };

	return Range{ begin, end, vector };
}

#endif


