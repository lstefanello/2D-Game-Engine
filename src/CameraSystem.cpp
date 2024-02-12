#include <CameraSystem.h>

void ECS::Systems::CameraSystem::init()
{
    required_pools.push_back(typeid(Camera));
    required_pools.push_back(typeid(Transform));
}

int ECS::Systems::CameraSystem::FindScaleFactor(int target_x, int target_y)
{
    return floor(float(Globals::SCREEN_WIDTH*Globals::SCREEN_HEIGHT)/float(target_x*target_y));
}

void ECS::Systems::CameraSystem::run() 
{
    glUseProgram(DisplayManager::shaderProgram);
    int cam_loc = glGetUniformLocation(DisplayManager::shaderProgram, "camera_position");
    int scale_factor_loc = glGetUniformLocation(DisplayManager::shaderProgram, "scale_factor");

    int cam = entities[0];
    auto* cam_dat = em->get<Camera>(cam);
    auto* attached_ent_dat = em->get<Transform>(cam);

    cam_dat->params.x = attached_ent_dat->position.x;
    cam_dat->params.y = attached_ent_dat->position.y;

    int factor = FindScaleFactor(800, 600);
    cam_dat->scale_factor = factor;

    if (cam_dat->params.y < Globals::SCREEN_HEIGHT/(2*factor))
    {
        cam_dat->params.y = Globals::SCREEN_HEIGHT/(2*factor);
    }
    else if (cam_dat->params.y > Globals::SCREEN_HEIGHT - (Globals::SCREEN_HEIGHT/(2*factor)))
    {
        cam_dat->params.y = Globals::SCREEN_HEIGHT - (Globals::SCREEN_HEIGHT/(2*factor));
    }

    if (cam_dat->params.x < Globals::SCREEN_WIDTH/(2*factor))
    {
        cam_dat->params.x = Globals::SCREEN_WIDTH/(2*factor);
    }
    else if (cam_dat->params.x > Globals::SCREEN_WIDTH - (Globals::SCREEN_WIDTH/(2*factor)))
    {
        cam_dat->params.x = Globals::SCREEN_WIDTH - (Globals::SCREEN_WIDTH/(2*factor));
    }

    float cam_x = factor*cam_dat->params.x - Globals::SCREEN_WIDTH/2; 
    float cam_y = factor*cam_dat->params.y - Globals::SCREEN_HEIGHT/2;

    glUniform2f(cam_loc, cam_x, cam_y);
    glUniform1i(scale_factor_loc, factor);
}
