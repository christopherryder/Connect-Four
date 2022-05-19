#ifndef __BOARD_TAG_HPP__
#define __BOARD_TAG_HPP__

#include <ostream>

enum class Board_Tag
{
	Border,
	Empty,

	Player_1,
	Player_2
};

inline std::ostream& operator<<(std::ostream& os, Board_Tag const& tag)
{
	// People don't seem to like switch statements but I think they're a good choice in situations like this.
	switch (tag)
	{
	case Board_Tag::Border:
		os << '#';
		break;

	case Board_Tag::Empty:
		os << '.';
		break;

	case Board_Tag::Player_1:
		os << 'X';
		break;

	case Board_Tag::Player_2:
		os << 'O';
		break;

	default:
		os << '?';
		break;
	}

	return os;
}

#endif