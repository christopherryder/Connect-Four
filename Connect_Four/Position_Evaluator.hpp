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

// TODO: FUNCITFY! auto operator()(Postion const&) -> const Move; updates m_position, hm...  

class Position_Evaluator
{
private:

	class Wrapped_Position_Evaluator
	{
	public:

		Wrapped_Position_Evaluator(Position const& position, const int controller_id, const int search_depth, const bool use_alpha_beta_pruning, const bool use_transposition_table) :
			m_position(position), m_controller_id(controller_id), m_search_depth(search_depth), m_use_alpha_beta_pruning(use_alpha_beta_pruning), m_use_transposition_table(use_transposition_table) {}

		Move find_optimum_move();

		// I want to use this for chaining purposes, imagine the syntax: evaluator(position).find_optimum_move();
		inline Wrapped_Position_Evaluator& operator()(Position& position) { m_position = position; return *this; }

	private:

		struct Optimum_Move
		{
			Move m_move{};
			int m_evaluation{};
		};

		int evaluate(Move const& move);
		int negamax(Move const& move, int depth, int ply_from_root, int alpha, int beta, int signedness);

		Position m_position;

		int m_search_depth{ 8 };
		bool m_use_alpha_beta_pruning{ true };
		bool m_use_transposition_table{ false };

		int m_controller_id{ 1 };
		int m_neutral_controller_id{ 0 };

		int m_base_draw_value{ 0 };
		int m_base_win_value{ std::numeric_limits<int>::max() };
	};

	Wrapped_Position_Evaluator m_position_evaluator;

public:

	Position_Evaluator(const int controller_id, const int search_depth, const bool use_alpha_beta_pruning, const bool use_transposition_table) :
		m_position_evaluator(Position{}, controller_id, search_depth, use_alpha_beta_pruning, use_transposition_table) {}

	/*
	* For the same chaining reasons as above. Additionally, this ensures no `stale' Position_Evaluators are left behind. One must always update the Evaluator with the current context before accessing it.
	* In reality though the only calls to the Position_Evaluator should be from the AI class, which will recieve a fresh Position& every turn, so staleness shouldn't be an issue anyway.
	*/

	inline Wrapped_Position_Evaluator& operator()(Position& position) { return m_position_evaluator(position); }
};

#endif