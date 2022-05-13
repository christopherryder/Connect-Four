#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "Move.hpp"
#include "Position.hpp"
#include "Position_Evaluator.hpp"

class Player
{
public:
	Player(const int controller_id, const int search_depth, const bool use_alpha_beta_pruning, const bool use_transposition_table) : 
		m_controller_id(controller_id), m_evaluator(Position_Evaluator(controller_id, search_depth, use_alpha_beta_pruning, use_transposition_table)) {}

	Move take_turn(Position& position) const;

private:
	int m_controller_id{};
	Position_Evaluator m_evaluator;
};

#endif