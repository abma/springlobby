/* This file is part of the Springlobby (GPL v2 or later), see COPYING */

#include <windef.h>
#include <mmsystem.h>
#include "ring_sound.h"
#include "pm_sound.h"
#include "alsound.h"


ALsound::ALsound()
{
}

ALsound::~ALsound()
{
	PlaySoundA(NULL, 0, 0); // STOP ANY PLAYING SOUND
}

void ALsound::ring()
{
	PlaySoundA((LPCSTR)ring_sound_data, NULL, SND_MEMORY | SND_ASYNC);
}
void ALsound::pm()
{
	PlaySoundA((LPCSTR)pm_sound_data, NULL, SND_MEMORY | SND_ASYNC);
}

ALsound& slsound()
{
	static ALsound snd;
	return snd;
}
