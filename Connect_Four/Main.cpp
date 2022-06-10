#include <iostream>
#include <random>

#include "Connect_Four.hpp"
#include "Token_Search.hpp"
#include "Token.hpp"

int generate_random_int(const int min, const int max)
{
	// TODO: Wasteful to not reuse, refactor.
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> key_distribution(min, max);

	return key_distribution(mt);
}

void seed_game(Connect_Four& game, const int number_of_moves)
{
	// Seed the game with this many moves.
	for (int i{ 0 }; i < number_of_moves; ++i)
	{
		// Count the number of possible moves in the current position.
		int possible_moves{ 0 };
		for (auto const& token : game.stackable_tokens())
			++possible_moves;

		// Select a random move from this set (by index).
		int random_move_index{ generate_random_int(0, (possible_moves - 1)) };
		int current_move_index{ 0 };

		for (auto& token : game.stackable_tokens())
		{
			// Play the random move.
			if (current_move_index == random_move_index)
			{
				game.stack_token(token);
				break;
			}

			++current_move_index;
		}
	}
}

void print_result(Connect_Four::State const& state)
{
	switch (state)
	{
	case Connect_Four::State::Won:
		std::cout << "Win! Gameover!\n";
		break;
	case Connect_Four::State::Drawn:
		std::cout << "Draw! Gameover!\n";
		break;
	}
}

int main(int argc, char* argv[])
{
	constexpr int player_1_search_depth{ 18 };
	constexpr int player_2_search_depth{ 4 };

	constexpr int playable_rows{ 6 };
	constexpr int playable_columns{ 7 };
	constexpr int required_streak{ 4 };

	Connect_Four connect_four(playable_rows, playable_columns, required_streak);

	std::cout << connect_four << '\n';

	constexpr int number_of_seed_moves{ 6 };
	seed_game(connect_four, number_of_seed_moves);

	int ply{ 0 };
	while (!connect_four.is_state_terminal())
	{
		std::cout << connect_four << '\n';

		int search_depth = (ply % 2 == 0) ? player_1_search_depth : player_2_search_depth;
		Token_Search token_search(connect_four, search_depth);

		Token optimum{ token_search.find_optimum_move() };

		// This is slightly clumsy as it it's not currently clear to me how to search a filter_view.
		for (auto& token : connect_four.stackable_tokens())
		{
			if (token == optimum)
			{
				connect_four.stack_token(token);
				break;
			}
		}

		print_result(connect_four.get_state());
		++ply;

		std::cout << "------------------------------------------------------------------------\n";
	}

	std::cout << connect_four;

	return 0;
}

