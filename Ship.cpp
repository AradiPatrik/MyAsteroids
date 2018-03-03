#include "Ship.h"

#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/bitmap.h>
#include <allegro5/allegro5.h>
#include <allegro5/keyboard.h>

#include <array>
#include <utility>

#include "Display.h"

Ship::Ship(float width, float height, const Display &display)
	: m_bitmap{ al_create_bitmap(width, height) }
	, m_width{ width }
	, m_height{ height }
	, m_display{ display }
{
	using namespace std;
	Shape points = {
		make_pair(width / 2.0f, 0.0f),
		make_pair(static_cast<float>(width), static_cast<float>(height)),
		make_pair(width / 2.0f, height / 1.5f),
		make_pair(0.0f , static_cast<float>(height))
	};

	al_set_target_bitmap(m_bitmap);
	construct_shape(points);
	m_display.set_backbuffer_active();
}

void Ship::construct_shape(const Shape &points) const
{
	for (auto it1 = points.cbegin(), it2 = points.cbegin() + 1; it2 != points.cend(); ++it1, ++it2) {
		const auto &first_point = *it1;
		const auto &second_point = *it2;
		al_draw_line(first_point.first, first_point.second, second_point.first, second_point.second, al_map_rgb(255, 255, 255), 1.0f);
	}
	al_draw_line(points[0].first, points[0].second, points[3].first, points[3].second, al_map_rgb(255, 255, 255), 1.0f);
}

Ship::~Ship()
{
	al_destroy_bitmap(m_bitmap);
}

void Ship::show() const
{
	al_draw_rotated_bitmap(m_bitmap, m_width/2, m_height/2, m_pos_x, m_pos_y, m_rotation, 0);
}

void Ship::update(float delta_time, ALLEGRO_KEYBOARD_STATE &keyboard_state)
{
	if (al_key_down(&keyboard_state, ALLEGRO_KEY_W)) {
		m_pos_x += 500.0 * delta_time * std::sin(m_rotation);
		m_pos_y -= 500.0 * delta_time * std::cos(m_rotation);
	}
	if (al_key_down(&keyboard_state, ALLEGRO_KEY_S)) {
		m_pos_x -= 500.0 * delta_time * std::sin(m_rotation);
		m_pos_y += 500.0 * delta_time * std::cos(m_rotation);
	}
	if (al_key_down(&keyboard_state, ALLEGRO_KEY_D)) {
		m_rotation += 10.0 * delta_time;
	}
	if (al_key_down(&keyboard_state, ALLEGRO_KEY_A)) {
		m_rotation -= 10.0 * delta_time;
	}
}


