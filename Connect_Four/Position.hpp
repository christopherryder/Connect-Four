#ifndef __POSITION_HPP__
#define __POSITION_HPP__

#include <vector>
#include <algorithm>
#include <ranges>
#include <ostream>

#include "Board.hpp"
#include "Board_Tag.hpp"
#include "Move.hpp"
#include "Move_Manager.hpp"
#include "Perspective.hpp"

class Position
{
public:

	enum class State
	{
		Ongoing,
		Drawn,
		Won
	};

	Position(Board const& board, Perspective const& perspective, Move_Manager const& move_manager) : m_board(board), m_perspective(perspective), m_move_manager(move_manager) {}

	// Grab moves from the move manager based on a predicate.
	inline auto moves() const { return m_move_manager.get_moves([this](const int move) { return (this->is_legal_move(move)); }); }

	void make_move(int& move);
	void unmake_move(int& move);

	const bool is_won(const int last_move) const;
	const bool is_drawn(const int last_move) const;

	inline constexpr State view_state() const { return m_state; }
	inline constexpr bool is_terminal() const { return ((m_state == State::Won) || (m_state == State::Drawn)); }

	inline constexpr Board const& debug_board() const { return m_board; }
	inline Move_Manager& debug_move_manager() { return m_move_manager; }

private:

	// Private default constructor
	Position() : Position(Board{}, Perspective{}, Move_Manager{}) {}

	// Verification methods
	inline constexpr bool is_legal_move(const int move) const { return ((move < m_board.ssize()) && (m_board[move] == m_board.default_tag())); }
	const bool is_vector_won(const int last_move, const int vector) const;

	const State get_state(const int last_move);
	inline void update_state(const int last_move) { m_state = get_state(last_move); }

	// Utility, converting indices to row/col.
	inline constexpr int row_from_index(const int index) const { return (index / m_total_columns); }
	inline constexpr int column_from_index(const int index) const { return (index - (row_from_index(index) * m_total_columns)); }

	// Utility, increment move
	inline void increment_move_row(int& move) const { move += m_total_columns; }
	inline void decrement_move_row(int& move) const { move -= m_total_columns; }

	// Should be supplied by manager, temporary stop-gap.
	// constexpr Board make_board() const;
	// constexpr Perspective make_perspective() const;
	

private:

	// A position evaluator is essentially an observer of this class (it is probably not an owner!?). Regardless in order to do it's job it requires
	// access to the underlying components of this class. 
	// However, in order to not expose this to everyone, we name it a friend class.
	friend class Position_Evaluator;

	// These are essentially configuration options and should be taken from a config file, or similar.
	int m_playable_rows{ 6 };
	int m_playable_columns{ 7 };

	int m_required_streak{ 4 };

	int m_border_size{ m_required_streak - 1 };

	int m_total_rows{ m_border_size + m_playable_rows + m_border_size };
	int m_total_columns{ m_border_size + m_playable_columns + m_border_size };

	std::vector<int> m_search_vectors{ std::vector<int>{+1, (m_total_columns + 1), m_total_columns, (m_total_columns - 1)} };

	// Naturally, a position can be described by a board only. 
	// Given a board, it is seen from the perspective of the player using it.
	// Additionally, a list of moves is also tied to a game `frame' (or position).
	Board m_board;
	Perspective m_perspective;
	Move_Manager m_move_manager;

	// Additionally, we define a state variable.
	State m_state{};
};

#endif