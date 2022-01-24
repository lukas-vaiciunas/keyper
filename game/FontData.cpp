#include <allegro5/allegro_ttf.h>
#include "FontData.h"

FontData::~FontData()
{
	for (auto it = fonts_.begin(); it != fonts_.end(); ++it)
		al_destroy_font(it->second);
}

FontData &FontData::instance()
{
	static FontData fontData;
	return fontData;
}

void FontData::emplace(unsigned int size)
{
	fonts_.emplace(size, al_load_ttf_font("font/DungeonFont.ttf", size, ALLEGRO_TTF_MONOCHROME));
}

void FontData::renderText(
	const std::string &text,
	float x, float y,
	unsigned int size,
	const ALLEGRO_COLOR &color,
	bool centerVertical,
	int allegroFlags) const
{
	al_draw_text(
		fonts_.find(size)->second,
		color,
		x, (centerVertical ? y - al_get_font_line_height(fonts_.find(size)->second) * 0.5f : y),
		allegroFlags,
		text.c_str());
}

int FontData::getFontLineHeight(unsigned int fontSize) const
{
	return al_get_font_line_height(fonts_.find(fontSize)->second);
}

int FontData::getTextWidth(unsigned int fontSize, const std::string &text) const
{
	return al_get_text_width(fonts_.find(fontSize)->second, text.c_str());
}