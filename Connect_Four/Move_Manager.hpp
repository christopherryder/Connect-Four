#ifndef __MOVE_MANAGER_HPP__
#define __MOVE_MANAGER_HPP__

#include <vector>
#include <ostream>
#include <ranges>

// Define an internal `move-list' object.
// This is essentially a wrapper about a contigious container (TODO: Mandate with Concept!) but allows for extracting a view about a predicate.
class Move_Manager
{
public:
	using move_type = int;
	using container = std::vector<move_type>;

	template <typename Iterator>
	Move_Manager(Iterator first, Iterator last) : m_moves(container(first, last)) {}

	template <typename container_type>
	Move_Manager(container_type const& c) : Move_Manager(c.begin(), c.end()) {}
	Move_Manager(std::initializer_list<move_type> const& moves) : Move_Manager(moves.begin(), moves.end()) {}

	template <class Predicate>
	inline constexpr auto get_moves(Predicate predicate) const { return m_moves | std::ranges::views::filter(predicate); }

	template <class Predicate>
	inline auto get_moves(Predicate predicate) { return m_moves | std::ranges::views::filter(predicate); }

	friend std::ostream& operator<<(std::ostream& os, Move_Manager const& move_manager)
	{
		for (auto move : move_manager.m_moves)
		{
			os << move << ' ';
		}

		return os;
	}

	//inline constexpr move_type const& operator[](const int index) const { return m_moves[index]; }
	inline move_type& operator[](const int index) { return m_moves[index]; }

private:

	// Allow only the position class to access the underlying list by subscript.
	friend class Position;

	Move_Manager() : Move_Manager({}) {}

	container m_moves{};
};

#endif