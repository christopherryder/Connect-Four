#ifndef __GAME_CPP__
#define __GAME_CPP__

#include "Game.hpp"

#include <iostream>

void Game::play()
{
	m_position.make_move(Move{ 10, Board_Tag::Player_1 });
	m_position.make_move(Move{ 11,Board_Tag::Player_2 });

	m_position.make_move(Move{ 19,Board_Tag::Player_1 });
	m_position.make_move(Move{ 20,Board_Tag::Player_2 });

	m_position.make_move(Move{ 12,Board_Tag::Player_1 });
	m_position.make_move(Move{ 13,Board_Tag::Player_2 });

	m_position.make_move(Move{ 21,Board_Tag::Player_1 });
	m_position.make_move(Move{ 22,Board_Tag::Player_2 });

	m_position.make_move(Move{ 30,Board_Tag::Player_1 });
	m_position.make_move(Move{ 14,Board_Tag::Player_2 });

	std::cout << "The board is currently:" << m_position.board() << '\n';

}


#endif

