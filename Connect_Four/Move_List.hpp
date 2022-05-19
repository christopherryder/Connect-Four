#ifndef __MOVE_LIST_HPP__
#define __MOVE_LIST_HPP__

#include <vector>
#include <algorithm>

#include "Move.hpp"
#include "Perspective.hpp"

class Move_List
{
private:

	using container = typename std::vector<Move>;

	struct Const_Iterator
	{
		using iterator_concept = std::contiguous_iterator_tag;

		using value_type = typename container::value_type;
		using difference_type = typename container::difference_type;
		using const_pointer = typename container::const_pointer;
		using const_reference = value_type const&;

		constexpr Const_Iterator() noexcept : m_pointer(), m_parent() {}
		constexpr Const_Iterator(const_pointer p, Move_List const* parent) : m_pointer(p), m_parent(parent) {}

		constexpr Const_Iterator& operator=(Const_Iterator const&) noexcept = default;

		[[nodiscard]] constexpr const_reference operator*() const noexcept { return (*m_pointer); }
		[[nodiscard]] constexpr const_pointer operator->() const noexcept { return m_pointer; }

		constexpr Const_Iterator& operator++() noexcept { increment(); return (is_end() || is_valid()) ? (*this) : operator++(); }
		constexpr Const_Iterator operator++(int) noexcept { Const_Iterator tmp = (*this);  ++(*this); return tmp; }

		[[nodiscard]] constexpr bool operator==(Const_Iterator const& rhs) const noexcept { return (m_pointer == rhs.m_pointer); }
		[[nodiscard]] constexpr std::strong_ordering operator<=>(Const_Iterator const& rhs) const noexcept { return (m_pointer <=> rhs.m_pointer); }

	private:

		constexpr bool is_valid() const noexcept { return m_parent->validate_move(*(*this)); }
		constexpr bool is_begin() const noexcept { return ((*this) == m_parent->begin()); }
		constexpr bool is_end() const noexcept { return ((*this) == m_parent->end()); }

		constexpr Const_Iterator& increment() noexcept { ++m_pointer; return (*this); }
		constexpr Const_Iterator& decrement() noexcept { --m_pointer; return (*this); }

		const_pointer m_pointer;
		Move_List const* m_parent;
	};

public:

	Move_List(const int move_offset, const int move_extent, std::initializer_list<Move> const& moves) : m_move_offset(move_offset), m_move_extent(move_extent), m_moves(moves) {}
	Move_List() : Move_List(0, 0, {}) {}

	inline Move_List const& operator()(Perspective const& perspective) { set_perspective(perspective); return *this; }

	inline void apply_move(Move const& applied_move) { find_move(applied_move).m_index += m_move_offset; }
	inline void revert_move(Move const& reverted_move) { find_move(reverted_move).m_index -= m_move_offset; }

	constexpr Const_Iterator begin() const noexcept { return Const_Iterator(&m_moves.front(), this); }
	constexpr Const_Iterator end() const noexcept { return Const_Iterator(&m_moves.front() + m_moves.size(), this); }

	inline constexpr Move const& operator[](const int index) const { return m_moves[index]; }

private:

	// TODO: This is kind of naughty, Move_List has a hardcoded game rule. Need to decouple here.
	constexpr bool validate_move(const Move& move) const { return (move.m_index < m_move_extent); }
	void set_perspective(Perspective const& perspective) { std::for_each(m_moves.begin(), m_moves.end(), [perspective](Move& move) {move.m_tag = perspective.m_player; }); }

	// TODO: This implies that all moves can be found need to check it isn't end().
	Move& find_move(Move const& required_move) { return *std::find_if(m_moves.begin(), m_moves.end(), [required_move](Move const& move) {return(move.m_index == required_move.m_index); }); }

	int m_move_offset{};
	int m_move_extent{};
	container m_moves{};
};

#endif