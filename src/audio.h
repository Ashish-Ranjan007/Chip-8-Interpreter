#pragma once

#include <SDL.h>
#include <SDL_mixer.h>

class Audio {
private:
    Mix_Chunk* beep;

public:
    
    Audio();
    ~Audio();
    void playSound(void);
    bool loadMedia(void);
};
