#include <SoundEmitterSystem.h>

void ECS::Systems::SoundEmitterSystem::init()
{
    required_pools.push_back(typeid(SoundEmitter));

    good = Mix_LoadMUS("../resources/sounds/good(birds).wav");
    home = Mix_LoadMUS("../resources/sounds/home.wav");


    walk  = Mix_LoadWAV("../resources/sounds/walk.wav");
    zap = Mix_LoadWAV("../resources/sounds/zap.wav");
    blip = Mix_LoadWAV("../resources/sounds/blip.wav");
}

Mix_Chunk* ECS::Systems::SoundEmitterSystem::GetSound(int sound)
{
    switch (sound)
    {
        case ECS::SoundEmitter::Sounds::walk:
            return walk;
        break;

        case ECS::SoundEmitter::Sounds::zap:
            return zap;
        break;

        case ECS::SoundEmitter::Sounds::blip:
            return blip;
        break;
    }
}

Mix_Music* ECS::Systems::SoundEmitterSystem::GetMusic(int music)
{
    switch (music)
    {
        case ECS::SoundEmitter::Music::good:
            return good;
        break;

        case ECS::SoundEmitter::Music::home:
            return home;
        break;
    }
}

void ECS::Systems::SoundEmitterSystem::run() 
{
    for (auto &i : entities)
    {
        auto* sound_data = em->get<SoundEmitter>(i);

        if (sound_data->current_song != ECS::SoundEmitter::Music::none)
        {
            if(Mix_PlayingMusic() == 0)
            {
                Mix_PlayMusic(GetMusic(sound_data->current_song), -1);
            }
        }

        int c = 1;
        for (auto &s : sound_data->buffered_sounds)
        {
            Mix_PlayChannel(c % 8, GetSound(s), 0);
            c++;
        }

        sound_data->buffered_sounds.clear();
    }
}

ECS::Systems::SoundEmitterSystem::~SoundEmitterSystem()
{
    Mix_FreeMusic(good);

    Mix_FreeChunk(walk);
    Mix_FreeChunk(zap);
    Mix_FreeChunk(blip);
}
