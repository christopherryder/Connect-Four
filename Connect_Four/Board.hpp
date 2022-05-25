#ifndef __BOARD_HPP__
#define __BOARD_HPP__

#include <vector>
#include <ostream>

#include "Board_Tag.hpp"
#include "Move.hpp"

class Board
{
public:

	Board(const int rows, const int columns, const Board_Tag default_tag, const int border_size, const Board_Tag border_tag) :
		m_rows(rows), m_columns(columns), m_default_tag(default_tag), m_border_size(border_size), m_border_tag(border_tag), m_board(make_board()) {}

	Board(const int rows, const int columns, const Board_Tag default_tag) : Board(rows, columns, default_tag, 0, default_tag) {}

	Board() : Board(0, 0, Board_Tag{}) {}

	inline constexpr int index(const int row, const int column) const { return ((row * m_columns) + column); }

	inline constexpr int rows() const { return m_rows; }
	inline constexpr int columns() const { return m_columns; }
	inline constexpr int ssize() const { return m_size; }
	inline constexpr Board_Tag default_tag() const { return m_default_tag; }

	inline constexpr int border_size() const { return m_border_size; }
	inline constexpr Board_Tag border_tag() const { return m_border_tag; }

	inline constexpr Board_Tag const& operator()(const int row, const int column) const { return m_board[index(row, column)]; }
	inline constexpr Board_Tag& operator()(const int row, const int column) { return m_board[index(row, column)]; }

	inline constexpr Board_Tag const& operator[](const int index) const { return m_board[index]; }
	inline constexpr Board_Tag& operator[](const int index) { return m_board[index]; }

	friend std::ostream& operator<<(std::ostream& os, Board const& board);

private:

	template <typename T>
	using container_type = std::vector<T>;

	const container_type<Board_Tag> make_board() const;

	int m_rows{};
	int m_columns{};
	Board_Tag m_default_tag{};

	int m_border_size{};
	Board_Tag m_border_tag{};

	int m_size{ (m_rows + m_border_size) * (m_columns + m_border_size) };

	container_type<Board_Tag> m_board{};
};

#endif