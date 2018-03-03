#pragma once
#include <allegro5/keyboard.h>
struct IGameObject {
	virtual void update(float delta_time, ALLEGRO_KEYBOARD_STATE &keyboard_state) = 0;
	virtual void show() const = 0;
};