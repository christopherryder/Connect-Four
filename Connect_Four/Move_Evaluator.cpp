#ifndef __MOVE_EVALUATOR_CPP__
#define __MOVE_EVALUATOR_CPP__

#include "Move_Evaluator.hpp"

#include <algorithm>
#include <cassert>

Move_Evaluator::Evaluation Move_Evaluator::evaluate(Board const& board, Move_List const& moves, Move const& move) const
{
	// First check if the move is even valid.
	if (is_valid_move(board, move))
	{
		return Evaluation::Invalid_Move;
	}

	// Check for a winning move.
	if (is_winning_move(board, move))
	{
		return Evaluation::Winning_Move;
	}

	// There wasn't a winning move, therefore if there are still valid moves possible then it wasn't a drawing move.
	if (is_moves_remaining(board, moves))
	{
		return Evaluation::Normal_Move;
	}

	// The move wasn't winning and there are no more possible moves, therefore it is a drawing move.
	return Evaluation::Drawing_Move;
}

const bool Move_Evaluator::is_winning_move(Board const& board, Move const& move) const
{
	//Need to check each unit vector.
	for (auto const& vector : m_unit_traversal_vectors)
	{
		//Build a win range object
		Range range{ make_validation_range(board, move, vector) };
		int current_streak{ 0 };

		//Might need to be != need to check
		assert(false && "Did you check if it was i<end or i!=end?");

		for (int i{ range.m_begin }; i < range.m_end; i += range.m_step)
		{
			current_streak = (board[i] == move.m_controller) ? (current_streak + 1) : 0;
			if (current_streak == m_required_streak)
			{
				return true;
			}
		}
	}

	return false;
}

const bool Move_Evaluator::is_valid_move(Board const& board, Move const& move) const
{
	return (move.m_index < board.ssize());
}

const bool Move_Evaluator::is_moves_remaining(Board const& board, Move_List const& moves) const
{
	for (auto const& move : moves)
	{
		if (is_valid_move(board, move))
		{
			return true;
		}
	}

	return false;
}

const Move_Evaluator::Range Move_Evaluator::make_validation_range(Board const& board, Move const& move, int const& vector) const
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
	int positive_extent{ std::min(m_required_streak - 1, (board.columns() - 1 - move.m_column)) };

	int begin{ move.m_index - (negative_extent * vector) };
	int end{ move.m_index + (positive_extent * vector) };

	return Range{ begin, end, vector };
}

#endif