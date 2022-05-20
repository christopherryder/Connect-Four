#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <stack>
#include <vector>

#include "Move.hpp"
#include "Board.hpp"
#include "Board_Tag.hpp"
#include "Move_List.hpp"
#include "Position.hpp"
#include "Position_Evaluator.hpp"

class Game
{
public:

	using Move_Stack = std::stack<Move, std::vector<Move>>;
	Game() : m_position({ make_board2(), make_move_list() }) {}

	void play();

private:

	inline const Board make_board2() const { return Board(m_board_rows, m_board_columns); }
	inline const Move_List make_move_list() const { return Move_List(9, (m_board_rows * m_board_columns), { Move{ 10,Board_Tag::Empty }, Move{ 11,Board_Tag::Empty }, Move{12,Board_Tag::Empty}, Move{13,Board_Tag::Empty}, Move{14,Board_Tag::Empty}, Move{15,Board_Tag::Empty}, Move{16,Board_Tag::Empty} }); }

private:

	int m_board_rows{ 8 };
	int m_board_columns{ 9 };
	int m_required_streak{ 4 };

	//Need players, etc.

	Position m_position;
	Move_Stack m_move_history{};
};


#endif