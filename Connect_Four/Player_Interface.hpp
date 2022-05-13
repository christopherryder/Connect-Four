#ifndef __PLAYER_INTERFACE_HPP__
#define __PLAYER_INTERFACE_HPP__

#include "Move.hpp"
#include "Position.hpp"

class Player_Interface
{
public:

	virtual ~Player_Interface() = 0;

	virtual Move take_turn(Position const& position) const = 0;
	virtual int controller_id() const = 0;
};

inline Player_Interface::~Player_Interface() = default;

#endif