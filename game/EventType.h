#pragma once

enum class EventType : unsigned char
{
	ChangeDriverState,
	Quit,
	LevelComplete,
	Loss
};