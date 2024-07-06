#include <SDL_mixer.h>

#include "audio.h"

Audio::Audio()
{
    beep = nullptr;
}

Audio::~Audio()
{
    if (beep != nullptr)
    {
        Mix_FreeChunk(beep);
        beep = nullptr;
    }
    Mix_CloseAudio(); // Close the audio device
}

void Audio::playSound()
{
    Mix_PlayChannel(-1, beep, 0);
}

bool Audio::loadMedia(void)
{
    // Load sound effect
    beep = Mix_LoadWAV("assets/beep.wav");
    return beep != nullptr;
}
