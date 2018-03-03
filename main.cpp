#include <allegro5/allegro5.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>

#include <iostream>

#include "Ship.h"
#include "Display.h"
#include "Game.h"

void init_allegro() {
	if (!al_init()) {
		std::cerr << "Could not initialize allegro" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_font_addon()) {
		std::cerr << "Could not initialize font add on" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_ttf_addon()) {
		std::cerr << "Could not initialize TTF add on" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_install_keyboard()) {
		std::cerr << "Could not install Keyboard" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_image_addon()) {
		std::cerr << "Could not install Image add on" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_install_mouse()) {
		std::cerr << "Could not install Mouse add on" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_install_audio()) {
		std::cerr << "Could not install Audio add on" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_acodec_addon()) {
		std::cerr << "Could not init ACODEC add on" << std::endl;
		exit(EXIT_FAILURE);
	}

	if (!al_init_primitives_addon()) {
		std::cerr << "Could not init primitives add on" << std::endl;
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv) {
	
	init_allegro();

	Display display(600, 600);

	const auto font = al_load_ttf_font("AGENCYB.ttf", 64, 0);

	al_reserve_samples(1);
	auto cat_in_space_music = al_load_sample("catsong.wav");
	al_play_sample(cat_in_space_music, 1.0, 0, 1, ALLEGRO_PLAYMODE_LOOP, NULL);

	const auto event_queue = al_create_event_queue();

	constexpr auto fps_60 = 1.0 / 60.0;
	const auto timer = al_create_timer(fps_60);



	const auto &ship = Ship(30, 50, display);
	
	Game game;
	game.start_game();

	al_uninstall_keyboard();
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return EXIT_SUCCESS;
}