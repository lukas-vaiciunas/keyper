#include "Camera.h"
#include "Config.h"

Camera::Camera(float x, float y) :
	x_(x),
	y_(y)
{}

void Camera::centerOn(float x, float y)
{
	x_ = x * Config::cameraScale - Config::displayWidth * 0.5f;
	y_ = y * Config::cameraScale - Config::displayHeight * 0.5f;
}

float Camera::getX() const
{
	return x_;
}

float Camera::getY() const
{
	return y_;
}