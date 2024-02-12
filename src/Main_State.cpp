#include <Main_State.h>
#include <cstdlib>
#include <random>


StateManager::Main_State::Main_State()
{
//    srand(time(0));
//
    int music = em.create();
    em.add<SoundEmitter>(music);
//    auto* m_dat = em.get<SoundEmitter>(music);
 //   m_dat->current_song = ECS::SoundEmitter::Music::home;

    ent = em.create(); 
    em.add<Render>(ent);
    em.add<Transform>(ent);
    em.add<Animated>(ent);
//    em.add<ColorRotationPos>(ent);
    em.add<Physics>(ent);
    em.add<KeyboardControlled>(ent);
    em.add<ParticleEmitter>(ent);
    em.add<Depth>(ent);
    em.add<Shoot>(ent);
    em.add<DynamicCollidable>(ent);
    em.add<Camera>(ent);
    em.add<SoundEmitter>(ent);

    auto* c_dat = em.get<Camera>(ent);
   
    em.add<LightSource>(ent);

    auto* l_dat = em.get<LightSource>(ent);
//    l_dat->radius = 0.1f;
    l_dat->intensity = 2.5f;
    l_dat->color = {1.0f, 0.75f, 0.0f, 1.0f};



    auto* part_dat = em.get<ParticleEmitter>(ent);
    //part_dat->particles_per_second = 50;
    part_dat->particles_per_second = 10;
    part_dat->scale = {13/4, 13/4};
    //part_dat->is_active = false;

    auto* data = em.get<Transform>(ent);
    //data->position.x = rand() % Globals::SCREEN_WIDTH;
    //data->position.y = rand() % Globals::SCREEN_HEIGHT;
    data->position.x = Globals::SCREEN_WIDTH/2;
    data->position.y = Globals::SCREEN_HEIGHT/2;

    data->position.z = 1.0f; 
    data->tex_coords = {4.0f, 64.0f, 15.0f, 17.0f};
    //data->scale = {15.0f * 3.0f, 17.0f * 3.0f};
    data->scale = {15.0f, 17.0f};
    data->colors = {1.0f, 1.0f, 1.0f, 1.0f};

    auto* a_data = em.get<Animated>(ent);
    a_data->next_state = anim_states::idle;

    for (int i = 0; i < 20; i++)
    {
        int block = em.create();
        em.add<StaticRender>(block);
        em.add<Transform>(block);
        em.add<Depth>(block);
        em.add<Physics>(block);
        em.add<StaticCollidable>(block);

        auto* dat = em.get<Transform>(block);
        dat->position.x = rand() % (Globals::SCREEN_WIDTH - 50) + 50;
        dat->position.y = rand() % (Globals::SCREEN_HEIGHT - 50) + 50;
        dat->position.z = 1.0f;

        dat->scale = {30.0f, 30.0f};
        dat->colors = {1.0f, 1.0f, 1.0f, 1.0f};
        dat->tex_coords = {942.0f, 12.0f, 60.0f, 60.0f};
    }

    for (int i = 0; i < std::ceil(Globals::SCREEN_WIDTH/13.0f); i++)
    {
        for (int j = 0; j < std::ceil(Globals::SCREEN_HEIGHT/13.0f); j++)
        {
            int guy = em.create();
            em.add<StaticRender>(guy);
            em.add<Transform>(guy);

            auto* g_data = em.get<Transform>(guy);
            g_data->position.x = i * 13.0f; 
            g_data->position.y = j * 13.0f; 
            g_data->position.z = -1.0f;
            g_data->tex_coords = {223.0f, 94.0f, 30.0f, 30.0f};
            //g_data->scale = {3.0f*13.0f, 3.0f*13.0f};
            g_data->scale = {13.0f, 13.0f};
            g_data->colors = {1.0f, 1.0f, 1.0f, 1.0f};
        }
    }
}

void StateManager::Main_State::Events(StateManager::Manager* sm)
{
    while(SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            sm->queue_state(states::state_exit);
        }
        else if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                {
                    sm->queue_state(states::state_exit);
                }
                break;

                case SDLK_RETURN:
                {
                    sm->queue_state(states::state_main);
                }
                break;

                case SDLK_p:
                {
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_real_distribution<> dis(0, 1);
         
                    int guy = em.create();
                    em.add<Render>(guy);
                    em.add<Transform>(guy);
                    em.add<Physics>(guy);
                    em.add<Depth>(guy);
                    em.add<Attractor>(guy);
                    em.add<LightSource>(guy);
         
                    auto* l_dat = em.get<LightSource>(guy);
                    l_dat->intensity = 5;
                    l_dat->color = {dis(gen), dis(gen), dis(gen), 1.0f};
         
                    auto* g_data = em.get<Transform>(guy);
                    auto* transform_data = em.get<Transform>(ent);

                    g_data->position.x = transform_data->position.x;
                    g_data->position.y = transform_data->position.y;
                    g_data->scale = {24.0f, 24.0f};
                    g_data->colors = {1.0f, 1.0f, 1.0f, 1.0f};
                    g_data->tex_coords = {5.0f, 86.0f, 48.0f, 48.0f};
                }
                break;

                case SDLK_m:
                {
                    int companion = em.create();
                    em.add<Render>(companion);
                    em.add<Depth>(companion);
                    em.add<DynamicCollidable>(companion);
                    em.add<Transform>(companion);
                    em.add<Animated>(companion);
                    em.add<Physics>(companion);
                    em.add<Follow>(companion);

                    auto f_dat = em.get<Follow>(companion);
                    f_dat->target_id = ent;

                    auto pos = em.get<Transform>(ent)->position;

                    auto comp_tr = em.get<Transform>(companion);
                    comp_tr->position = pos;
                    comp_tr->colors = {1.0f, 1.0f, 1.0f, 1.0f};
                    comp_tr->tex_coords = {18.0f, 389.0f, 14, 19};
                    comp_tr->scale = {14.0f, 19.0f};

                    auto comp_anim = em.get<Animated>(companion);
                    comp_anim->next_state = ECS::anim_states::finn_walk;
                }
                break;
            }
        }  
    }
}

void StateManager::Main_State::Logic()
{
    em.run_systems();
}

StateManager::Main_State::~Main_State()
{

}
