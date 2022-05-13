#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <stack>
#include <vector>

#include "Move.hpp"
#include "Board.hpp"
#include "Move_List.hpp"
#include "Move_Manager.hpp"
#include "Position.hpp"
#include "Position_Evaluator.hpp"

class Game
{
public:

	using Move_Stack = std::stack<Move, std::vector<Move>>;
	Game() : m_position({ make_board(), make_move_manager(), make_move_evaluator() }) {}

	void play();

private:

	inline const Board make_board() const { return Board(m_board_rows, m_board_columns); }
	inline const Move_Manager make_move_manager() const { return Move_Manager(m_board_columns, { Move{0,0,0 }, Move{ 1,1,0 }, Move{ 2,2,0 }, Move{3,3,0}, Move{4,4,0}, Move{5,5,0}, Move{6,6,0} }); }
	inline const Move_List make_move_list() const { return Move_List({ Move{0,0,0 }, Move{ 1,1,0 }, Move{ 2,2,0 }, Move{3,3,0}, Move{4,4,0}, Move{5,5,0}, Move{6,6,0} }); }
	inline const Move_Evaluator make_move_evaluator() const { return Move_Evaluator(m_required_streak, {m_board_columns, +1, m_board_columns + 1, m_board_columns - 1}); }

private:

	int m_board_rows{ 6 };
	int m_board_columns{ 7 };
	int m_required_streak{ 4 };

	//Need players, etc.

	Position m_position;
	Move_Stack m_move_history{};
};


#endif