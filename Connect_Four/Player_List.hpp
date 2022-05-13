#ifndef __PLAYER_LIST_HPP__
#define __PLAYER_LIST_HPP__

#include <memory>

#include "Player_Interface.hpp"

class Player_List
{
public:

	using player_unique_ptr = std::unique_ptr<Player_Interface>;
	Player_List() {}

	void register_player(player_unique_ptr&& player);
	void swap();


private:


	std::unique_ptr<Player_Interface> m_player;
	std::unique_ptr<Player_Interface> m_enemy;
};

#endif