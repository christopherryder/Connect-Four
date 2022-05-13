#ifndef __GAME_CPP__
#define __GAME_CPP__

#include "Game.hpp"

#include <iostream>

void Game::play()
{
	m_position.make_move(Move{ 0,0,1 }, 1);
	m_position.make_move(Move{ 1,1,2 }, 2);

	m_position.make_move(Move{ 0,7,1 }, 1);
	m_position.make_move(Move{ 1,8,2 }, 2);

	m_position.make_move(Move{ 2,2,1 }, 1);
	m_position.make_move(Move{ 3,3,2 }, 2);

	m_position.make_move(Move{ 2,9,1 }, 1);
	m_position.make_move(Move{ 4,4,2 }, 2);

	m_position.make_move(Move{ 2,16,1 }, 1);
	m_position.make_move(Move{ 6,6,2 }, 2);

	std::cout << "The board is currently:" << m_position.board() << '\n';

	Position_Evaluator evaluator(1, 5, true, false);

	Move optimum = evaluator(m_position).find_optimum_move();
	std::cout << "The optimum move was found at index " << optimum.m_index << " in column " << optimum.m_column << ".\n";
}


#endif

