#pragma once
struct Display {
	Display(unsigned width, unsigned height);
	~Display() { al_destroy_display(&m_al_display); }
	void set_backbuffer_active() const { al_set_target_backbuffer(&m_al_display); }
	ALLEGRO_DISPLAY *al_display() const { return &m_al_display }
private:
	struct ALLEGRO_DISPLAY &m_al_display;
	unsigned m_width = 0;
	unsigned m_height = 0;
};


