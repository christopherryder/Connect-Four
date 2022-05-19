#ifndef __WIN_EVALUATOR_HPP__
#define __WIN_EVALUATOR_HPP__

#include "Position.hpp"

// Given a move made in a position, evaluate whether the making of that move resulted in a game termination.
// I.e, it evaluates the position to find if the made move results in a require win streak.
// Additionally, it checks if there are any subsequent moves that could be made in this position.
// Such that if the made move did NOT result in a win, AND there are no subsequent moves the game terminates in a draw.
// Otherwise, there is no end. 

struct Win_Evaluator
{
public:

	Win_Evaluator(const int required_streak, std::initializer_list<int> const& unit_traversal_vectors) : m_required_streak(required_streak), m_unit_traversal_vectors(unit_traversal_vectors) {}
	inline bool operator()(Position const& position, Move const& move) const { return is_winning_move(position, move); }

private:

	const bool is_winning_move(Position const& position, Move const& move) const;

	int m_required_streak{};
	std::vector<int> m_unit_traversal_vectors{};
};

#endif