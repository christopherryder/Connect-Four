#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <vector>
#include <ostream>
#include <numeric>

#include "Move.hpp"

class Board
{
public:

	template <typename T>
	using container_type = std::vector<T>;

private:

	int m_rows{};
	int m_columns{};
	int m_size{ m_rows * m_columns };

	container_type<int> m_board{};

public:

	Board(int const& rows, int const& columns) : 
		m_rows(rows), m_columns(columns), m_board(make_board()) {}

	Board() : Board(6, 7) {}

	inline const int rows() const { return m_rows; }
	inline const int columns() const { return m_columns; }
	inline const int ssize() const { return (m_rows * m_columns); }

	inline int const& operator[](const int index) const { return m_board[index]; }
	inline int& operator[](const int index) { return m_board[index]; }

	friend std::ostream& operator<<(std::ostream& os, Board const& board);

private:

	const container_type<int> make_board() const;
	
};

#endif