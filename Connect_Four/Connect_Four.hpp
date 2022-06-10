#ifndef __CONNECT_FOUR_HPP__
#define __CONNECT_FOUR_HPP__

#include <vector>
#include <ranges>
#include <ostream>

#include "Board.hpp"
#include "Board_Tag.hpp"
#include "Token.hpp"
#include "Perspective.hpp"

class Connect_Four
{
public:

	// Define these type traits as concrete definitions of template classes.
	using tag_type = Board_Tag;
	using board_type = Board<tag_type>;
	using zobrist_key_type = board_type::zobrist_key_type;
	using perspective_type = Perspective<tag_type>;

	// Define an enum class which succinctly determines the possible states a position could be in.
	// Of these three states, two are terminal (i.e result in a game end): Drawn, Won.
	// TODO: Look into using a FSM (?) Could be able to do some interesting things...
	enum class State
	{
		Ongoing,
		Drawn,
		Won
	};

	// This constructor is ghastly but it does represent a generic case of connect-four...
	Connect_Four(const int board_playable_rows, const int board_playable_columns, tag_type const& empty_tag, tag_type const& origin_tag,
		tag_type const& border_tag, const int required_streak) 
		: m_board_playable_rows(board_playable_rows), m_board_playable_columns(board_playable_columns), m_empty_tag(empty_tag), m_origin_tag(origin_tag),
		m_border_tag(border_tag), m_required_streak(required_streak) {}

	Connect_Four(const int board_playable_rows, const int board_playable_columns, const int required_streak)
		: Connect_Four(board_playable_rows, board_playable_columns, tag_type::Empty, tag_type::Origin, tag_type::Border, required_streak) {}

	Connect_Four() : Connect_Four(6, 7, tag_type::Empty, tag_type::Origin, tag_type::Border, 4) {}

	// Returns all of the tokens which can be stacked on top of. 
	inline auto stackable_tokens() { return m_tokens | std::ranges::views::filter([this](Token const& token) { return this->is_playable_token(token); }); }
	inline auto stackable_tokens() const { return m_tokens | std::ranges::views::filter([this](Token const& token) { return this->is_playable_token(token); }); }

	void stack_token(Token& token);
	void unstack_token(Token& token);

	// It's important to expose the state of the game so the game manager can determine when this instantiation is finished.
	inline constexpr State get_state() const { return m_state; }
	inline constexpr bool is_state_terminal() const { return (m_state == State::Won || m_state == State::Drawn); }

	// Allow retrieval of zobrist key for use by evaluator classes.
	inline constexpr zobrist_key_type get_zobrist_key() const { return m_board.zobrist_key(); }

	std::ostream& stream(std::ostream& os) const;
	inline friend std::ostream& operator<<(std::ostream& os, Connect_Four const& connect_four) { return connect_four.stream(os); }

private:

	// Terminality conditions.
	bool is_drawn() const;
	constexpr bool is_winning_token(Token const& token) const;
	constexpr bool is_token_winning_in_vector(Token const& token, const int vector) const;

	// Verification methods.
	constexpr bool is_playable_token(Token const& token) const;
	
	// Updating the board state after making a move.
	void update_state(Token const& token);

	// Initialisation methods for various member data.
	const board_type make_board() const;
	const std::vector<Token> make_tokens() const;
	inline constexpr perspective_type make_perspective() const { return perspective_type{ tag_type::Player_1, tag_type::Player_2 }; }

	// TODO: this is a bit messy, implement it a bit more sensibly.
	inline constexpr std::vector<int> make_search_vectors() const { return std::vector<int>{+1, (m_board_total_columns - 1), m_board_total_columns, (m_board_total_columns + 1)}; }

private:

	int m_board_playable_rows{};
	int m_board_playable_columns{};

	tag_type m_empty_tag{};
	tag_type m_origin_tag{};
	tag_type m_border_tag{};

	int m_required_streak{};

	int m_board_border_size{ m_required_streak - 1 };

	int m_board_total_rows{ m_board_border_size + m_board_playable_rows + m_board_border_size };
	int m_board_total_columns{ m_board_border_size + m_board_playable_columns + m_board_border_size };

	std::vector<int> m_search_vectors{ make_search_vectors() };

	board_type m_board{ make_board() };
	std::vector<Token> m_tokens{ make_tokens() };
	perspective_type m_perspective{ make_perspective() };

	State m_state{ State::Ongoing };
};


#endif