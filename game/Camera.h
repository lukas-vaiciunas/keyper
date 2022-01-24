#pragma once

class Camera
{
private:
	float x_;
	float y_;
public:
	Camera(float x, float y);

	void centerOn(float x, float y);

	float getX() const;
	float getY() const;
};