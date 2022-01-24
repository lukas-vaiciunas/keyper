#pragma once

#include <allegro5/allegro_audio.h>
#include <unordered_map>

class SoundBox
{
private:
	std::unordered_map<unsigned char, ALLEGRO_SAMPLE *> samples_;

	SoundBox();
public:
	SoundBox(const SoundBox &) = delete;
	SoundBox &operator=(const SoundBox &) = delete;

	static SoundBox &instance();

	void playSample(unsigned char id, ALLEGRO_PLAYMODE allegroPlaymode, float gain);
};