#ifndef __MOVE_LIST_HPP__
#define __MOVE_LIST_HPP__

#include <vector>
#include <ranges>

#include "Move.hpp"

class Move_List
{
public:
	using container = std::vector<Move>;
	using iterator = container::iterator;
	using const_iterator = container::const_iterator;

	template <typename Iterator>
	Move_List(Iterator first, Iterator last) : m_moves(container(first, last)) {}

	template <typename container_type>
	Move_List(container_type const& container_t) : Move_List(container_t.begin(), container_t.end()) {}
	Move_List(std::initializer_list<Move> const& moves) : Move_List(moves.begin(), moves.end()) {}


	template <class Predicate>
	constexpr auto get(Predicate predicate) const { return m_moves | std::ranges::filter_view(predicate); }

	constexpr iterator begin() { return m_moves.begin(); }
	constexpr const_iterator begin() const { return m_moves.begin(); }

	constexpr iterator end() { return m_moves.end(); }
	constexpr const_iterator end() const { return m_moves.end(); }

	inline constexpr Move const& operator[](const int index) const { return m_moves[index]; }
	inline constexpr Move& operator[](const int index) { return m_moves[index]; }

private:
	container m_moves{};
};

#endif