#ifndef __POSITION_HPP__
#define __POSITION_HPP__

#include "Board.hpp"
#include "Move.hpp"
#include "Perspective.hpp"
#include "Move_Manager.hpp"
#include "Move_List.hpp"
#include "Move_Evaluator.hpp"

class Position
{
public:

	// QOL abbreviation.
	using Evaluation = Move_Evaluator::Evaluation;

	Position(Board const& board, Move_Manager const& moves, Move_Evaluator const& evaluator, Perspective const& perspective) : m_board(board), m_move_manager(moves), m_evaluator(evaluator), m_perspective(perspective) {}
	Position(Board const& board, Move_Manager const& moves, Move_Evaluator const& evaluator) : Position(board, moves, evaluator, Perspective{ 0,1,2 }) {}

	void make_move(Move const& move);
	void unmake_move(Move const& move);

	
	// TODO: Unfortunately, I had to un-const these functions because evaluating a move requires making/unmaking it, therefore mutating the position. Need to think about implications of this
	// Evaluates the effect of a move on the position AFTER the move has been made.
	inline Move_List const& moves() { return m_move_manager(m_perspective); }
	inline Evaluation evaluate_move(Move const& move) { return m_evaluator.evaluate(m_board, moves(), move); }

	// Old const& {...} const accessors. Possibly not even required. 
	inline Board const& board() const { return m_board; }
	inline Move_Manager const& move_manager() const { return m_move_manager; }
	inline Move_Evaluator const& evaluator() const { return m_evaluator; }

private:

	/*
	* We only really want to expose the underlying make up of the position to the Position_Evaluator class, hence we define it a friend.
	* We also define a set of `read-only' accessor methods for use by the Position_Evaluator, mostly for QOL purposes.
	*/

	friend class Position_Evaluator;

	// In general I don't need to expose the default-constructible Position. only the Position_Evaluator requires it for the wrapper.
	Position() : Position(Board{}, Move_Manager{}, Move_Evaluator{}) {}

	//inline Board& board() { return m_board; }
	//inline Move_List& moves() { return m_moves; }
	//inline Move_Evaluator& evaluator() { return m_evaluator; }

	Board m_board;
	Move_Manager m_move_manager;
	Move_Evaluator m_evaluator;
	Perspective m_perspective;
};

#endif