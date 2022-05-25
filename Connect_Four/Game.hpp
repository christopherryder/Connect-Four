#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <stack>
#include <vector>

#include "Move.hpp"
#include "Move_Manager.hpp"
#include "Board.hpp"
#include "Board_Tag.hpp"
#include "Perspective.hpp"
#include "Position.hpp"
#include "Position_Evaluator.hpp"

#include <iostream>

class Game
{
public:

	using Move_Stack = std::stack<Move, std::vector<Move>>;
	Game() : m_position({ make_board(), make_perspective(), make_move_manager(make_board()) }) {}

	void play();

private:

	inline const Board make_board() const { return Board(m_total_rows, m_total_columns, Board_Tag::Empty, m_border_size, Board_Tag::Border); }
	inline const Perspective make_perspective() const { return Perspective{ Board_Tag::Player_1, Board_Tag::Player_2 }; }
	const Move_Manager make_move_manager(Board const& board) const
	{
		std::vector<int> candidate_moves{};

		for (int j{ 0 }; j < m_total_columns; ++j)
		{

			for (int i{ 0 }; i < m_total_rows; ++i)
			{
				if (board[(m_total_columns * i) + j] == board.default_tag())
				{
					candidate_moves.push_back((m_total_columns * i) + j);
					break;
				}
			}
		}

		return Move_Manager(candidate_moves);
	}

private:

	int m_playable_rows{ 6 };
	int m_playable_columns{ 7 };

	int m_required_streak{ 4 };

	int m_border_size{ m_required_streak - 1 };

	int m_total_rows{ m_border_size + m_playable_rows + m_border_size };
	int m_total_columns{ m_border_size + m_playable_columns + m_border_size };

	//Need players, etc.

	Position m_position;
	Move_Stack m_move_history{};
};


#endif