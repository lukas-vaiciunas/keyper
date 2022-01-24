#pragma once

#include <allegro5/allegro_font.h>
#include <unordered_map>

class FontData
{
private:
	std::unordered_map<unsigned int, ALLEGRO_FONT *> fonts_;

	FontData() {}
	~FontData();
public:
	FontData(const FontData &) = delete;
	FontData &operator=(const FontData &) = delete;

	static FontData &instance();

	void emplace(unsigned int size);

	void renderText(
		const std::string &text,
		float x, float y,
		unsigned int size,
		const ALLEGRO_COLOR &color,
		bool centerVertical = false,
		int allegroFlags = ALLEGRO_ALIGN_LEFT) const;

	int getFontLineHeight(unsigned int fontSize) const;
	int getTextWidth(unsigned int fontSize, const std::string &text) const;
};