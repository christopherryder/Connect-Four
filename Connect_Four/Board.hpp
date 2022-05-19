#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <vector>
#include <ostream>

#include "Board_Tag.hpp"
#include "Move.hpp"

class Board
{
public:

	Board(int const& rows, int const& columns) : 
		m_rows(rows), m_columns(columns), m_board(make_board(1)) {}

	Board() : Board(6, 7) {}

	inline constexpr int index(const int row, const int column) const { return ((row * m_columns) + column); }

	inline constexpr int rows() const { return m_rows; }
	inline constexpr int columns() const { return m_columns; }
	inline constexpr int ssize() const { return (m_rows * m_columns); }

	inline constexpr Board_Tag const& operator()(const int row, const int column) const { return m_board[index(row, column)]; }
	inline constexpr Board_Tag& operator()(const int row, const int column) { return m_board[index(row, column)]; }

	inline constexpr Board_Tag const& operator[](const int index) const { return m_board[index]; }
	inline constexpr Board_Tag& operator[](const int index) { return m_board[index]; }

	friend std::ostream& operator<<(std::ostream& os, Board const& board);
private:

	template <typename T>
	using container_type = std::vector<T>;

	const container_type<Board_Tag> make_board(const int border_size) const;

	int m_rows{};
	int m_columns{};
	int m_size{ m_rows * m_columns };

	container_type<Board_Tag> m_board{};
};

#endif