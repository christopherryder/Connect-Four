#ifndef __MOVE_EVALUATOR_HPP__
#define __MOVE_EVALUATOR_HPP__

/*
* The remit of the Move_Evaluator class is to perform `soft' evaluations of a given move in a given context.
* I.e: The impact of making a given move in the current position.
*
* Given this class is merely an algorithmic wrapper around components of the main class, it is not designed to be instantiated outside of the main connect four class.
*/

#include "Board.hpp"
#include "Move.hpp"
#include "Move_List.hpp"

class Move_Evaluator
{
public:

	enum class Evaluation
	{
		Winning_Move,
		Drawing_Move,
		Normal_Move
	};


	Move_Evaluator(const int required_streak, std::initializer_list<int> const& unit_traversal_vectors) : m_required_streak(required_streak), m_unit_traversal_vectors(unit_traversal_vectors) {}
	Move_Evaluator() : Move_Evaluator(0, {}) {}

	Evaluation evaluate(Board const& board, Move_List const& moves, Move const& move) const;

private:

	const bool is_winning_move(Board const& board, Move const& move) const;
	const bool is_valid_move(Board const& board, Move const& move) const;
	const bool is_moves_remaining(Board const& board, Move_List const& moves) const;

	struct Range
	{
		int m_begin{};
		int m_end{};
		int m_step{};
	};

	const Range make_validation_range(Board const& board, Move const& move, int const& vector) const;

	int m_required_streak{};
	std::vector<int> m_unit_traversal_vectors{};
};

#endif