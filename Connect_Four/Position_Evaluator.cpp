#ifndef __POSITION_EVALUATOR_CPP__
#define __POSITION_EVALUATOR_CPP__

#include "Position_Evaluator.hpp"

#include <algorithm>

Move Position_Evaluator::Wrapped_Position_Evaluator::find_optimum_move()
{
	Optimum_Move optimum_move{};
	constexpr int optimum_evaluation{ -std::numeric_limits<int>::max() };

	constexpr int initial_alpha{ -std::numeric_limits<int>::max() };
	constexpr int initial_beta{ +std::numeric_limits<int>::max() };

	for (auto& move : m_position.moves())
	{
		int evaluation{ negamax(move, m_search_depth, 1, initial_alpha, initial_beta, +1) };

		if (evaluation > optimum_evaluation)
		{
			optimum_move = Optimum_Move{ move, evaluation };
		}
	}

	return optimum_move.m_move;
}

int Position_Evaluator::Wrapped_Position_Evaluator::evaluate(Move const& move) const
{
	/*
	* Because of the use of the `negamax' algorithm one never determines a losing move. The signedness of the move depends on whether the move is executed
	* by the ACTUAL current player or the current player in the search.
	*/

	switch (m_position.evaluate_move(move))
	{
	case Position::Evaluation::Winning_Move:
		return m_base_win_value;

	case Position::Evaluation::Drawing_Move:
		return m_base_draw_value;
	}

	return 0;
}

int Position_Evaluator::Wrapped_Position_Evaluator::negamax(Move& move, int depth, int ply_from_root, int alpha, int beta, int signedness)
{
	// TODO: OR IS TERMINAL (I.e Game ending, Draw, Win).
	if (depth == 0)
	{
		// TODO: Return SIGNEDNESS * evaluation, i.e player is +1, enemy is -1.
		return evaluate(move);
	}

	// Initialise the current BEST evaluation at -Inf. I.e: any subsequent evaluation will be better than this.
	int evaluation{ -std::numeric_limits<int>::max() };

	// Now we must evaluate each of the current moves in the position
	for (Move& child_move : m_position.moves())
	{
		if (child_move.m_index < m_position.m_board.ssize())
			continue;

		m_position.make_move(child_move);
		evaluation = std::max(evaluation, -negamax(child_move, (depth - 1), (ply_from_root + 1), -alpha, -beta, -signedness));
		m_position.unmake_move(child_move);

		alpha = std::max(alpha, evaluation);

		if (alpha >= beta)
		{
			break;
		}
	}

	return evaluation;
}

#endif


