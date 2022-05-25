#ifndef __GAME_CPP__
#define __GAME_CPP__

#include "Game.hpp"

#include <iostream>

void Game::play()
{

	std::cout << "The board is currently:" << m_position.debug_board() << '\n';
	std::cout << "Current move indices:" << m_position.debug_move_manager() << '\n';

	m_position.make_move(m_position.debug_move_manager()[0]);
	m_position.make_move(m_position.debug_move_manager()[1]);
	m_position.make_move(m_position.debug_move_manager()[2]);
	m_position.make_move(m_position.debug_move_manager()[3]);
	m_position.make_move(m_position.debug_move_manager()[4]);
	m_position.make_move(m_position.debug_move_manager()[5]);
	m_position.make_move(m_position.debug_move_manager()[6]);

	std::cout << "The board is currently:" << m_position.debug_board() << '\n';
	std::cout << "Current move indices:" << m_position.debug_move_manager() << '\n';

	m_position.make_move(m_position.debug_move_manager()[0]);
	m_position.make_move(m_position.debug_move_manager()[1]);
	m_position.make_move(m_position.debug_move_manager()[2]);
	m_position.make_move(m_position.debug_move_manager()[3]);
	m_position.make_move(m_position.debug_move_manager()[4]);
	m_position.make_move(m_position.debug_move_manager()[5]);
	m_position.make_move(m_position.debug_move_manager()[6]);

	std::cout << "The board is currently:" << m_position.debug_board() << '\n';
	std::cout << "Current move indices:" << m_position.debug_move_manager() << '\n';

	m_position.make_move(m_position.debug_move_manager()[0]);
	m_position.make_move(m_position.debug_move_manager()[1]);
	m_position.make_move(m_position.debug_move_manager()[2]);
	m_position.make_move(m_position.debug_move_manager()[3]);
	m_position.make_move(m_position.debug_move_manager()[4]);
	m_position.make_move(m_position.debug_move_manager()[5]);
	m_position.make_move(m_position.debug_move_manager()[6]);

	std::cout << "The board is currently:" << m_position.debug_board() << '\n';
	std::cout << "Current move indices:" << m_position.debug_move_manager() << '\n';

	m_position.make_move(m_position.debug_move_manager()[1]);
	m_position.make_move(m_position.debug_move_manager()[0]);


	std::cout << "The board is currently:" << m_position.debug_board() << '\n';
	std::cout << "Current move indices:" << m_position.debug_move_manager() << '\n';

	Position_Evaluator eval(&m_position, 8, true, true);

	std::cout << eval.find_optimum_move() << '\n';
}


#endif

