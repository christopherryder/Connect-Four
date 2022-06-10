#ifndef __CONNECT_FOUR_CPP__
#define __CONNECT_FOUR_CPP__

#include "Connect_Four.hpp"

#include <algorithm>
#include <cassert>

void Connect_Four::stack_token(Token& token)
{
	// May as well check that the token's projected index is in bounds and that the projected index has an empty tag.
	assert((token.get_stack_index() < m_board.ssize()) && is_playable_token(token) && "Token is not playable! (Either out of bounds or projection is not on an empty tag.");
	
	// Firstly, update the internal token state.
	token.stack();
	
	// Update the board state.
	m_board.set_element(token.get_index(), m_perspective.m_player);

	// Update the game state
	update_state(token);

	// Swap the perspective.
	m_perspective.swap();
}

void Connect_Four::unstack_token(Token& token)
{
	// We cannot unstack if we're on the origin, it doesn't make any sense we will just recess into the border ad infinitum.
	assert((m_board[token.get_index()] != tag_type::Origin) && "Cannot unstack a token on the origin.");

	// Firstly, we can trivially say that the game state must revert to ongoing.
	m_state = State::Ongoing;

	// Then, remove the token from the board.
	m_board.set_element(token.get_index(), m_empty_tag);

	// Retreat the internal token state.
	token.unstack();

	// Swap the perspective.
	m_perspective.swap();
}

std::ostream& Connect_Four::stream(std::ostream& os) const
{
	os << "The board is currently:\n" << m_board << "\nFor Player " << m_perspective.m_player << " Current Moves Are : ";
	for (Token const& token : stackable_tokens())
	{
		os << "[VAL=" << m_perspective.m_player << ", IDX=" << token.get_stack_index() << "] ";
	}
	os << '\n';
	return os;
}

bool Connect_Four::is_drawn() const
{
	// It is enough to check that there exists a single moveable token for the game not to be drawn.
	for (Token const& token : stackable_tokens())
	{
		return false;
	}

	return true;
}

constexpr bool Connect_Four::is_winning_token(Token const& token) const
{
	for (const int vector : m_search_vectors)
	{
		if (is_token_winning_in_vector(token, vector))
			return true;
	}

	return false;
}

constexpr bool Connect_Four::is_token_winning_in_vector(Token const& token, const int vector) const
{
	// Due to the padding of the board, we can start behind the token and sweep past it.
	int offset{ (m_required_streak - 1) * vector };

	int index{ token.get_index() - offset };
	int end_index{ token.get_index() + offset };

	int current_streak{ 0 };

	for (index; index != end_index; index += vector)
	{
		// It is important that you don't compare with the perspective, because the perspective gets swapped after making the move.
		// Hence it is best just to compare against the tag in the location of the token. Though it might be worth asserting that
		// this tag is not empty...
		// TOOD: add assertion on tag type.
		current_streak = (m_board[index] == m_board[token.get_index()]) ? (current_streak + 1) : 0;

		if (current_streak == m_required_streak)
			return true;
	}

	return false;
}

constexpr bool Connect_Four::is_playable_token(Token const& token) const
{
	// It is enough, at this stage to just check that the project index is empty on the board.
	// One might worry about out of bounds errors but it really shouldn't happen...
	// There is no harm in asserting though:
	assert((token.get_stack_index() < m_board.ssize()) && "Token is out of bounds");
	return ((m_board[token.get_stack_index()] == m_empty_tag) && !is_state_terminal());
}

void Connect_Four::update_state(Token const& token)
{
	// Check first for a win position.
	if (is_winning_token(token))
	{
		m_state = State::Won;
	}

	// If no win, the game could be a draw.
	else if (is_drawn())
	{
		m_state = State::Drawn;
	}

	// Not in a terminal state (won/draw), hence ongoing.
	else
	{
		m_state = State::Ongoing;
	}
}

const Connect_Four::board_type Connect_Four::make_board() const
{
	// Initialise an `empty' board of the correct dimension and mark the player tags as hashable tags. 
	board_type tmp(m_board_total_rows, m_board_total_columns, m_empty_tag, { tag_type::Player_1, tag_type::Player_2 });

	// The strategy now is to place a uniform border of border tags about the `empty' board. 
	// Additionally, one must also mark the origin tiles for the tokens.
	// I don't really see a more elegant way to do this other than iterating the board's dimensions.
	for (int i{ 0 }; i < m_board_total_rows; ++i)
	{
		for (int j{ 0 }; j < m_board_total_columns; ++j)
		{
			// First we take care of the border tags:
			// We require a full-width border on the first and last rows.
			if (i < m_board_border_size || i >((m_board_total_rows - 1) - m_board_border_size))
			{
				tmp.set_element(tmp.index(i, j), m_border_tag);
			}

			// Otherwise we only require the first column and last column to have padding.
			else if (j < m_board_border_size || j >((m_board_total_columns - 1) - m_board_border_size))
			{
				
				tmp.set_element(tmp.index(i, j), m_border_tag);
			}
		}

		// Now we take care of the origin tags:
		// The origin tags are to be placed in the border region along the bottom of the first playable row.
		if (i == (m_board_border_size - 1))
		{
			for (int j{ m_board_border_size }; j < (m_board_border_size + m_board_playable_columns); ++j)
			{
				tmp.set_element(tmp.index(i, j), m_origin_tag);
			}
		}
	}

	return tmp;
}

const std::vector<Token> Connect_Four::make_tokens() const
{
	// We can quite easily initialise the token locations by using std::find_if for the origin tiles.
	std::vector<Token> tmp{};
	
	// Begin by caching the relevant iterators.
	auto iter_begin = m_board.cbegin();
	auto iter_end = m_board.cend();
	auto iter = iter_begin;

	// Define the lambda which determines whether a tag is an origin tag.
	auto is_origin_tag = [this](tag_type const& tag) {return tag == m_origin_tag; };

	// Use loop assignment to reassing iter at the start of each loop to result of find_if, GIVEN THAT IT IS NOT THE END.
	// Notably, if no origin_tag exists we will get end==end at assignment and the loop will not be entered. 
	while ((iter = std::find_if(iter, iter_end, is_origin_tag)) != iter_end)
	{
		tmp.push_back(Token{ static_cast<int>(std::distance(iter_begin, iter)), m_board_total_columns });

		// We must increment the iterator here otherwise we will just `find' the same element each time.
		// Note: this is safe as at this point of the execution iter is != end, therefore we do not increment past end.
		++iter;
	}

	return tmp;
}

#endif