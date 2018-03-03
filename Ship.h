#pragma once
#include <array>
#include <utility>

#include "IGameObject.h"
#include "Display.h"

struct Ship : public IGameObject {
	Ship(unsigned width, unsigned height, const Display &display);
	Ship(const Ship& other) = delete;
	Ship &operator=(const Ship & other) = delete;
	~Ship();
	void show() const override;
	void update(float delta_time, struct ALLEGRO_KEYBOARD_STATE &keyboard_state) override;

private:
	using Shape = std::array<std::pair<float, float>, 4>;
	float m_pos_x = 0.0;
	float m_pos_y = 0.0;
	
	struct ALLEGRO_BITMAP *m_bitmap = nullptr;
	const Display &m_display;
	
	void construct_shape(const Shape &points) const;
	
};