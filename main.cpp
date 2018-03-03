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

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_start_timer(timer);

	al_flip_display();

	const auto &ship = Ship(30, 50, *display);

	while (1) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE ) {
			break;
		}

		if (ev.type == ALLEGRO_EVENT_TIMER) {
			al_clear_to_color(al_map_rgb(0, 0, 0));
			/*al_draw_bitmap(cat_bitmap, cat_pos_x, cat_pos_y, 0);
			al_draw_text(font, al_map_rgb(255, 255, 255), 0, 0, 0, "Hello World");*/

			ALLEGRO_KEYBOARD_STATE keyboard_state;

			al_get_keyboard_state(&keyboard_state);
			if (al_key_down(&keyboard_state, ALLEGRO_KEY_RIGHT))
				cat_pos_x += 1;

			if (al_key_down(&keyboard_state, ALLEGRO_KEY_LEFT)) {
				cat_pos_x -= 1;
			}

			if (al_key_down(&keyboard_state, ALLEGRO_KEY_DOWN)) {
				cat_pos_y += 1;
			}

			if (al_key_down(&keyboard_state, ALLEGRO_KEY_UP)) {
				cat_pos_y -= 1;
			}
		}
		ship.show();
		al_flip_display();
		
	}

	al_uninstall_keyboard();
	al_destroy_timer(timer);
	al_destroy_event_queue(event_queue);

	return EXIT_SUCCESS;
}