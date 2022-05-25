#ifndef __POSITION_EVALUATOR__
#define __POSITION_EVALUATOR__

/*
* In much the same way as the Move_Evaluator I use dependency injection to send the current Position. Though perhaps it should just be a copied member variable?
* 
* Positional evaluation is a bigger operation than move evaluation, encompassing many move evaluations. So maybe do that.
* 
* I am aware that this encompasses a deep copy of the position object but I argue that it is not too expensive to do so. additionally, it is only required once per ai turn. 
* Additionally, a deep copy of the position object ENSURES that the current game position is not damaged by any bugs in the evaluator. 
* 
* In the interests of further encapsulation I would ideally like to hide the find_optimum_move method behind the operator(), but I do not think this is possible. As the position evaluator
* is only used by the Ai, and only on their turn, 
* 
*/

#include <limits>

#include "Move.hpp"
#include "Position.hpp"

class Position_Evaluator
{
private:
	template<typename T>
	using observer_ptr = T*;

	// My own little invention, the idea is you can sandwhich a function in ->make_move, ->unmake_move calls to ensure position validity.
	template <typename Callable>
	inline auto suppose_move(const int move, Callable callable) -> decltype(callable())
	{
		if constexpr (std::is_void<decltype(callable())>::value)
		{
			m_position_ptr->make_move(move);
			callable();
			m_position_ptr->unmake_move(move);
		}
		else
		{
			m_position_ptr->make_move(move);
			auto value{ callable() };
			m_position_ptr->unmake_move(move);

			return value;
		}
	}

public:

	Position_Evaluator(observer_ptr<Position> position_ptr, const int search_depth, const bool use_alpha_beta_pruning, const bool use_transposition_table) :
		m_position_ptr(position_ptr), m_search_depth(search_depth), m_use_alpha_beta_pruning(use_alpha_beta_pruning), m_use_transposition_table(use_transposition_table) {}

	int find_optimum_move();

private:



	constexpr int evaluate() const;
	int negamax(int depth, int ply_from_root, int alpha, int beta);

	int m_search_depth{ 8 };
	bool m_use_alpha_beta_pruning{ true };
	bool m_use_transposition_table{ false };

	int m_base_draw_value{ 0 };
	int m_base_win_value{ std::numeric_limits<int>::max() };

	observer_ptr<Position> m_position_ptr;
};

#endif