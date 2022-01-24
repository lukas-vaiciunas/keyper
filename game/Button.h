#pragma once

#include <string>

class Button
{
private:
	std::string text_;
	float x_;
	float y_;
	float width_;
	float height_;
	unsigned int fontSize_;
public:
	Button(float x, float y, unsigned int fontSize, const std::string &text);

	bool isHovered(int mouseX, int mouseY) const;

	void render() const;
};