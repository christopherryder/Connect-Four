#ifndef __FUNCTORS_HPP__
#define __FUNCTORS_HPP__

// FOR USE POST- Make_Move();
// Checks a board for a win, given a move.
struct Win_Evaluator
{
	// I.e:
	// Looks for a four in a row streak from a given position (doesn't neccessarily have to supply a move).
	//
	// State:
	// Requires knowing WHICH directions to check, supplied as index offsets. (std::ptrdiff_t? is what stl uses...)
	// Requires knowing HOW LONG the required streak is.
};

// FOR USE PRE- Make_Move()!
// Checks whether a given move is valid in a given position
struct Move_Validity_Predicate
{
	// Checks whether the move in a position is valid: 
	// I.e:
	// (1). Is the destination index in bounds?
	// (2). If yes -> Is the destination index `free'?
	// (3). Is the move tag the same as the perspectives player! (more of a debug one really...)
	//
	// State:
	// Requires knowing the SSIZE() of the board to check bounds.
	// Requires knowing the BOARD to know if the index is free.
	// Requires knowing the VALUE of the BOARD at the given index, AND THE PERSPECTIVE OF THE POSITION to compare tags.
};






#endif