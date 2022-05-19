#ifndef __PERSPECTIVE_HPP__
#define __PERSPECTIVE_HPP__

#include "Board_Tag.hpp"

struct Perspective
{
	Board_Tag m_player{};
	Board_Tag m_enemy{};

	// Use auto because I Keep changing the underlying representation of the board, (int, enum class, etc...)
	inline void swap() { auto tmp{ m_player }; m_player = m_enemy; m_enemy = tmp; }
};

#endif