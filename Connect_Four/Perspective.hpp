#ifndef __PERSPECTIVE_HPP__
#define __PERSPECTIVE_HPP__

// Lightweight aggregate for describing whose turn it is in a two player game.
// TODO: It could be fun to generalise this to N players...

template <typename T>
struct Perspective
{
	using value_type = T;

	T m_player{};
	T m_enemy{};

	inline constexpr void swap() 
	{ 
		T tmp{ m_player }; 
		m_player = m_enemy; 
		m_enemy = tmp; 
	}
};

#endif