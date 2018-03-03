#include "Game.h"
#include "Ship.h"
#include <allegro5/allegro5.h>
#include <chrono>

Game::Game()
	: m_display(800, 800)
{
	init();
}

Game::~Game()
{
	al_destroy_event_queue(&m_event_queue);
	al_destroy_timer(&m_timer);
}

void Game::start_game()
{
	loop();
}

void Game::init()
{
	al_register_event_source(&m_event_queue, al_get_display_event_source(m_display.al_display()));
	al_register_event_source(&m_event_queue, al_get_keyboard_event_source());
	al_register_event_source(&m_event_queue, al_get_mouse_event_source());
	al_register_event_source(&m_event_queue, al_get_timer_event_source(&m_timer));
	al_start_timer(&m_timer);
	m_game_objects.push_back(std::make_unique<Ship>(30, 50, m_display));
}

void Game::loop()
{
	using namespace std::chrono;
	auto previous_time = system_clock::now();
	auto current_time = previous_time;
	
	while (1) {
		
		current_time = system_clock::now();
		m_delta_time = duration_cast<milliseconds>(current_time - previous_time).count() / 1000.0f;
		previous_time = current_time;
		ALLEGRO_EVENT ev;
		al_wait_for_event(&m_event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			break;
		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			
		}

		ALLEGRO_KEYBOARD_STATE keyboard_state;
		al_get_keyboard_state(&keyboard_state);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0.1));
		for (auto &&game_object : m_game_objects) {
			game_object->update(m_delta_time, keyboard_state);
			game_object->show();
			al_flip_display();
		}
	}
}