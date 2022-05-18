#ifndef __END_EVALUATOR_HPP__
#define __END_EVALUATOR_HPP__

#include "Position.hpp"

// Given a move made in a position, evaluate whether the making of that move resulted in a game termination.
// I.e, it evaluates the position to find if the made move results in a require win streak.
// Additionally, it checks if there are any subsequent moves that could be made in this position.
// Such that if the made move did NOT result in a win, AND there are no subsequent moves the game terminates in a draw.
// Otherwise, there is no end. 

struct End_Evaluator
{
public:

	// In this case, making a move has a posibility to end the game.
	// Either, a move doesn't end the game, or it does. 
	// If it does, from the perspective of the person making the move, the game can only end in either a `win' or a `draw'.

	enum class Evaluation
	{
		No_End,
		Win_End,
		Draw_End
	};

	End_Evaluator(const int required_streak, std::initializer_list<int> const& unit_traversal_vectors) : m_required_streak(required_streak), m_unit_traversal_vectors(unit_traversal_vectors) {}
	inline Evaluation operator()(Position const& position, Move const& move) const { return evaluate_end(position, move); }

private:

	Evaluation evaluate_end(Position const& position, Move const& move) const;

	const bool is_winning_move(Position const& position, Move const& move) const;
	const bool is_moves_remaining(Position const& position) const;

	struct Range
	{
		int m_begin{};
		int m_end{};
		int m_step{};
	};

	const Range make_move_evaluation_range(Position const& position, Move const& move, const int vector) const;

	int m_required_streak{};
	std::vector<int> m_unit_traversal_vectors{};

};

#endif