#include "Display.h"
#include <allegro5/allegro5.h>
Display::Display(unsigned width, unsigned height)
	: m_al_display(*al_create_display(width, height))
	, m_width(width)
	, m_height(height)
{
}