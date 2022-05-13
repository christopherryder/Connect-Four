#ifndef __PERSPECTIVE_HPP__
#define __PERSPECTIVE_HPP__

struct Perspective
{
	inline void swap() { auto tmp{ m_player_id }; m_player_id = m_enemy_id; m_enemy_id = tmp; }

	int m_neutral_id{};
	int m_player_id{};
	int m_enemy_id{};
};

#endif