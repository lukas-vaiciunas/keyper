#include "SoundBox.h"

SoundBox::SoundBox()
{
	samples_.emplace(1, al_load_sample("music/LonePeakMusic-Grim-Waltz-Retro-Gaming-Version.ogg"));
	samples_.emplace(2, al_load_sample("sound-effects/select.ogg"));
	samples_.emplace(3, al_load_sample("sound-effects/footstep.ogg"));
	samples_.emplace(4, al_load_sample("sound-effects/pickup.ogg"));
	samples_.emplace(5, al_load_sample("sound-effects/levelup.ogg"));
	samples_.emplace(6, al_load_sample("sound-effects/death.ogg"));
}

SoundBox &SoundBox::instance()
{
	static SoundBox soundBox;
	return soundBox;
}

void SoundBox::playSample(unsigned char id, ALLEGRO_PLAYMODE allegroPlaymode, float gain)
{
	ALLEGRO_SAMPLE_INSTANCE *instance = al_create_sample_instance(samples_[id]);

	al_set_sample_instance_playmode(instance, allegroPlaymode);
	al_set_sample_instance_gain(instance, gain);
	al_attach_sample_instance_to_mixer(instance, al_get_default_mixer());

	al_play_sample_instance(instance);
}