#ifndef __POSITION_HPP__
#define __POSITION_HPP__

#include "Board.hpp"
#include "Board_Tag.hpp"
#include "Move.hpp"
#include "Perspective.hpp"
#include "Move_List.hpp"

class Position
{
public:

	Position(Board const& board, Move_List const& moves, Perspective const& perspective) : m_board(board), m_move_list(moves), m_perspective(perspective) {}
	Position(Board const& board, Move_List const& moves) : Position(board, moves, Perspective{ Board_Tag::Player_1, Board_Tag::Player_2 }) {}

	void make_move(Move const& move);
	void unmake_move(Move const& move);

	
	// TODO: Unfortunately, I had to un-const these functions because evaluating a move requires making/unmaking it, therefore mutating the position. Need to think about implications of this
	// Evaluates the effect of a move on the position AFTER the move has been made.
	inline Move_List const& moves() { return m_move_list(m_perspective); }

	// Old const& {...} const accessors. Possibly not even required. 
	inline Board const& board() const { return m_board; }

private:

	/*
	* We only really want to expose the underlying make up of the position to the Position_Evaluator class, hence we define it a friend.
	* We also define a set of `read-only' accessor methods for use by the Position_Evaluator, mostly for QOL purposes.
	*/

	friend struct Win_Evaluator;
	friend class Position_Evaluator;

	// In general I don't need to expose the default-constructible Position. only the Position_Evaluator requires it for the wrapper.
	Position() : Position(Board{}, Move_List{}) {}

	//inline Board& board() { return m_board; }
	//inline Move_List& moves() { return m_moves; }
	//inline Move_Evaluator& evaluator() { return m_evaluator; }

	Board m_board;
	Move_List m_move_list;
	Perspective m_perspective;
};

#endif