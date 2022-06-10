//#ifndef __GAME_CPP__
//#define __GAME_CPP__
//
//#include "Game.hpp"
//
//#include "Token_Search.hpp"
//
//#include <iostream>
//#include <random>
//void Game::play()
//{
//	std::cout << m_connect_four << '\n';
//	std::cout << "Stacking tokens...\n";
//
//	// Seed the board with some random moves.
//	for (int i{ 0 }; i < 8; ++i)
//	{
//		int max{ 0 };
//		for (auto& token : m_connect_four.stackable_tokens())
//		{
//			++max;
//		}
//
//		std::random_device rd;
//		std::mt19937_64 mt(rd());
//		std::uniform_int_distribution<int> key_distribution(0, (max-1));
//
//		int seed = key_distribution(mt);
//
//		int index{ 0 };
//		for (auto& token : m_connect_four.stackable_tokens())
//		{
//			if (index == seed)
//			{
//				m_connect_four.stack_token(token);
//			}
//
//			++index;
//		}
//	}
//
//	int counter{ 0 };
//	while (!m_connect_four.is_state_terminal())
//	{
//		std::cout << m_connect_four;
//		int search_depth = (counter % 2 == 0) ? 16 : 4;
//		Token_Search token_search(m_connect_four, search_depth, m_connect_four.m_perspective.m_player);
//		Token optimum = token_search.find_optimum_move(8);
//
//		
//
//
//		// TODO: SO CLUMSY! LOL
//		for (Token& token : m_connect_four.stackable_tokens())
//		{
//			if (token == optimum)
//			{
//				m_connect_four.stack_token(token);
//				break;
//			}
//		}
//
//		if (m_connect_four.get_state() == Connect_Four::State::Won)
//		{
//			std::cout << "Won!\n";
//		}
//
//		if (m_connect_four.get_state() == Connect_Four::State::Drawn)
//		{
//			std::cout << "Drawn!\n";
//		}
//
//		std::cout << "------------------------------------------------------------------------\n";
//		++counter;
//	}
//
//	std::cout << m_connect_four;
//
//	//// Seed the board with some random moves.
//	//for (int i{ 0 }; i < 3; ++i)
//	//{
//	//	for (auto& token : m_connect_four.stackable_tokens())
//	//	{
//	//		m_connect_four.unstack_token(token);
//	//		std::cout << m_connect_four;
//	//	}
//	//}
//
//}
//
//
//#endif
//
