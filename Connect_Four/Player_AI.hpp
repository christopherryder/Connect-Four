#ifndef __PLAYER_AI_HPP__
#define __PLAYER_AI_HPP__

#include "Player_Interface.hpp"

#include "Position_Evaluator.hpp"
#include "Move.hpp"

class Player_AI : public Player_Interface
{
public:
	Player_AI(const int controller_id, Position_Evaluator const& evaluator) : m_controller_id(controller_id), m_evaluator(evaluator) {}

	Move take_turn(Position const& position) const override;
	inline int controller_id() const override { return m_controller_id; }

private:
	int m_controller_id{};
	Position_Evaluator m_evaluator;
};

#endif