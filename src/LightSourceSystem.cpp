#include <LightSourceSystem.h>

void ECS::Systems::LightSourceSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(Render));
    required_pools.push_back(typeid(LightSource));
}

void ECS::Systems::LightSourceSystem::run() 
{
    glUseProgram(DisplayManager::shaderProgram);
    int number_of_lights_loc = glGetUniformLocation(DisplayManager::shaderProgram, "number_of_lights");
    glUniform1i(number_of_lights_loc, entities.size());


    int index = 0;
    for (auto &i : entities)
    {
       auto* l_data = em->get<LightSource>(i);
       auto* t_data = em->get<Transform>(i);


       if(!l_data->timer.started)
       {
          l_data->timer.start();
       }

       std::string position_str = "LightArray[" + std::to_string(index) + "].position";
       std::string color_str = "LightArray[" + std::to_string(index) + "].color";
       std::string timer_str = "LightArray[" + std::to_string(index) + "].timer";
       std::string intensity_str = "LightArray[" + std::to_string(index) + "].intensity";
       std::string radius_str = "LightArray[" + std::to_string(index) + "].radius";

       int p_location = glGetUniformLocation(DisplayManager::shaderProgram, position_str.c_str());
       int c_location = glGetUniformLocation(DisplayManager::shaderProgram, color_str.c_str());
       int t_location = glGetUniformLocation(DisplayManager::shaderProgram, timer_str.c_str());
       int i_location = glGetUniformLocation(DisplayManager::shaderProgram, intensity_str.c_str());
       int r_location = glGetUniformLocation(DisplayManager::shaderProgram, radius_str.c_str());

       glUniform2f(p_location, t_data->position.x, t_data->position.y); 
       glUniform4f(c_location, l_data->color.x, l_data->color.y, l_data->color.z, l_data->color.w);
       glUniform1f(t_location, l_data->timer.GetTime());
       glUniform1f(i_location, l_data->intensity);
       glUniform1f(r_location, l_data->radius);

       index += 1;
    }
}
