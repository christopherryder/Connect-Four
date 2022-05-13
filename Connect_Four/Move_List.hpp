#ifndef __MOVE_LIST_HPP__
#define __MOVE_LIST_HPP__

#include <vector>
#include <algorithm>

#include "Move.hpp"
#include "Perspective.hpp"

class Move_List
{
public:

	using container_type = std::vector<Move>;
	using iterator = container_type::iterator;
	using const_iterator = container_type::const_iterator;

	Move_List(std::initializer_list<Move> const& moves) : m_moves(moves) {}
	Move_List() : Move_List({}) {}

	void set_perspective(Perspective const& perspective) { std::for_each(m_moves.begin(), m_moves.end(), [perspective](Move& move) {move.m_controller = perspective.m_player_id; }); }

	// TODO: Techincally, in the interests of encapsulation one should remove the regular iterators, we don't really want anyone interacting with the Move_List outside of the manager.
	inline constexpr iterator begin() { return m_moves.begin(); }
	inline constexpr const_iterator begin() const { return m_moves.begin(); }

	inline constexpr iterator end() { return m_moves.end(); }
	inline constexpr const_iterator end() const { return m_moves.end(); }

	inline constexpr Move const& operator[](const int index) const { return m_moves[index]; }

private:

	friend class Move_Manager;

	// In the interests of encapsulation, we keep the mutable/non-mutable accessor members private and define the Move_Manager as a friend.
	// Additionally, the impact of only exposing const_iterators means than any `retained' references of the underlying Move_List cannot be mutated
	// by anyone other than the Move_Manager class.

	inline constexpr Move& operator[](const int index) { return m_moves[index]; }

	container_type m_moves{};
};

#endif