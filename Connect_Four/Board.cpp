#ifndef __BOARD_CPP__
#define __BOARD_CPP__

#include "Board.hpp"

std::ostream& operator<<(std::ostream& os, Board const& board)
{
	os << '\n';

	for (auto i{ 0 }; i < board.rows(); ++i)
	{
		for (auto j{ 0 }; j < board.columns(); ++j)
		{
			os << board((board.rows() - 1 - i), j) << ' ';
		}

		os << '\n';
	}

	return os;
}

const Board::container_type<Board_Tag> Board::make_board() const
{
	container_type<Board_Tag> board{ container_type<Board_Tag>((m_size), m_default_tag) };

	for (int i{ 0 }; i < m_rows; ++i)
	{
		for (int j{ 0 }; j < m_columns; ++j)
		{
			// We require a full-width border on the first and last rows.
			if (i < m_border_size || i > ((m_rows - 1) - m_border_size))
			{
				board[index(i, j)] = m_border_tag;
			}
			else if (j < m_border_size || j >((m_columns - 1) - m_border_size))
			{
				// Otherwise we only require the first column and last column to have padding.
				board[index(i, j)] = m_border_tag;
			}
		}
	}

	return board;
}


#endif