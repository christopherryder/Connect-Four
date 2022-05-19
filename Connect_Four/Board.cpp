#ifndef __BOARD_CPP__
#define __BOARD_CPP__

#include "Board.hpp"

std::ostream& operator<<(std::ostream& os, Board const& board)
{
	int border_size{ 1 };

	os << '\n';

	for (auto i{ 0 }; i < board.rows(); ++i)
	{
		for (auto j{ 0 }; j < board.columns(); ++j)
		{
			if (j == 0)
			{
				if (i < border_size || i >((board.rows() - 1) - border_size))
				{
					os << ' ' << ' ';
				}
				else
				{
					os << (board.rows() - 1 - i) << ' ';
				}
			}

			os << board((board.rows() - 1 - i), j) << ' ';
		}

		if (i == (board.rows() - 1))
		{

			os << '\n';
			os << "  ";

			for (auto j{ 0 }; j < board.columns(); ++j)
			{
				if (j < border_size || j >((board.columns() - 1) - border_size))
				{
					os << ' ' << ' ';
				}
				else
				{
					os << j << ' ';
				}
			}
		}

		os << '\n';
	}

	return os;
}

const Board::container_type<Board_Tag> Board::make_board(const int border_size) const
{
	container_type<Board_Tag> board{ container_type<Board_Tag>((m_size), Board_Tag::Empty) };

	for (int i{ 0 }; i < m_rows; ++i)
	{
		for (int j{ 0 }; j < m_columns; ++j)
		{
			// We require a full-width border on the first and last rows.
			if (i < border_size || i > ((m_rows - 1) - border_size))
			{
				board[index(i, j)] = Board_Tag::Border;
			}
			else if (j < border_size || j >((m_columns - 1) - border_size))
			{
				// Otherwise we only require the first column and last column to have padding.
				board[index(i, j)] = Board_Tag::Border;
			}
		}
	}

	return board;
}


#endif

