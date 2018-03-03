#pragma once
#include <allegro5/allegro5.h>
#include <allegro5/timer.h>

#include <vector>
#include <memory>

#include "IGameObject.h"
#include "Display.h"

struct Game {
	Game();
	Game(const Game &other) = delete;
	Game &operator=(const Game &other) = delete;
	~Game();
	void start_game();

	Display &get_display() { return m_display; }

private:
	using GameObjects = std::vector<std::unique_ptr<IGameObject>>;

	GameObjects m_game_objects;
	Display m_display;
	ALLEGRO_EVENT_QUEUE &m_event_queue = *al_create_event_queue();
	ALLEGRO_TIMER &m_timer = *al_create_timer(1 / 60.0);
	float m_delta_time = 0.0f;

	void init();
	void loop();
};