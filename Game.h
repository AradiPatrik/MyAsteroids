#pragma once
#include <vector>
#include "IGameObject.h"

struct Game {
	void start_game();

private:

	using GameObjects = std::vector<IGameObject *>;
	GameObjects m_game_objects;
	float m_delta_time = 0.0f;

};