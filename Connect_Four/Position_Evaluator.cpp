#ifndef __POSITION_EVALUATOR_CPP__
#define __POSITION_EVALUATOR_CPP__

#include "Position_Evaluator.hpp"

#include <algorithm>
#include <iostream>
#include <cassert>

int Position_Evaluator::find_optimum_move()
{
	int optimum_move{ 0 };
	int optimum_evaluation{ -std::numeric_limits<int>::max() };

	for (auto move : m_position_ptr->moves())
	{
		std::cout << "CURRENT MOVE: " << move << ".\n";

		// Unfortunately have to duplication this `wrapped- statement' Perhaps there is a better way to ensure this. 
		m_position_ptr->make_move(move);
		int evaluation{ negamax(8, 1, -std::numeric_limits<int>::max(), +std::numeric_limits<int>::max()) };
		m_position_ptr->unmake_move(move);

		std::cout << "Evaluated " << evaluation << " For index: " << move << ".\n\n";

		if (evaluation > optimum_evaluation)
		{
			
			optimum_evaluation = evaluation;
			optimum_move = move;
		}
	}

	return optimum_move;
}

constexpr int Position_Evaluator::evaluate() const
{
	/*
	* Because of the use of the `negamax' algorithm one never determines a losing move. The signedness of the move depends on whether the move is executed
	* by the ACTUAL current player or the current player in the search.
	*/

	switch (m_position_ptr->view_state())
	{
	case Position::State::Won:
		return m_base_win_value;

	case Position::State::Drawn:
		return m_base_draw_value;
	}

	// If we reach this stage then the node is not terminal and so we just return an empty evaluation. 
	return 0;
}

int Position_Evaluator::negamax(int depth, int ply_from_root, int alpha, int beta)
{

	// TODO: OR IS TERMINAL (I.e Game ending, Draw, Win).
	if (depth == 0 || m_position_ptr->is_terminal())
	{
		// TODO: Return SIGNEDNESS * evaluation, i.e player is +1, enemy is -1.
		return evaluate();
	}

	// Initialise the current BEST evaluation at -Inf. I.e: any subsequent evaluation will be better than this.
	int evaluation{ -std::numeric_limits<int>::max() };

	// Now we must evaluate each of the current moves in the position
	for (auto move : m_position_ptr->moves())
	{
		// Suppose the move
		m_position_ptr->make_move(move);
		evaluation = std::max(evaluation, -negamax((depth - 1), (ply_from_root + 1), -alpha, -beta));
		m_position_ptr->unmake_move(move);

		alpha = std::max(alpha, evaluation);

		if (alpha >= beta)
		{
			break;
		}
	}

	return evaluation;
}

#endif


