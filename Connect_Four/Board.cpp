#ifndef __BOARD_CPP__
#define __BOARD_CPP__

#include "Board.hpp"

std::ostream& operator<<(std::ostream& os, Board const& board)
{
	os << '\n';

	for (auto i{ 0 }; i < board.m_rows; ++i)
	{
		for (auto j{ 0 }; j < board.m_columns; ++j)
		{
			if (j == 0)
			{
				os << (board.m_rows - 1 - i) << '|';
			}

			os << board[((board.m_rows - 1 - i) * board.m_columns) + j] << ' ';
		}

		if (i == (board.m_rows - 1))
		{
			os << '\n';
			os << "  ";

			for (auto j{ 0 }; j < board.m_columns; ++j)
			{
				os << j << ' ';
			}
		}

		os << '\n';
	}

	return os;
}

#endif

const Board::container_type<int> Board::make_board() const
{
	return container_type<int>(ssize(), 0);
}
