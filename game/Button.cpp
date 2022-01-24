#include "Button.h"
#include "FontData.h"

Button::Button(float x, float y, unsigned int fontSize, const std::string &text) :
	text_(text),
	x_(x - FontData::instance().getTextWidth(fontSize, text) * 0.5f),
	y_(y),
	width_(FontData::instance().getTextWidth(fontSize, text)),
	height_(FontData::instance().getFontLineHeight(fontSize)),
	fontSize_(fontSize)
{}

bool Button::isHovered(int mouseX, int mouseY) const
{
	return mouseX >= x_ && mouseX < x_ + width_ &&
		mouseY >= y_ && mouseY < y_ + height_;
}

void Button::render() const
{
	FontData::instance().renderText(
		text_,
		x_ + width_ * 0.5f,
		y_ + height_ * 0.5f,
		fontSize_,
		al_map_rgb(225, 225, 25),
		true,
		ALLEGRO_ALIGN_CENTER);
}