#include <RenderSystem.h>

void ECS::Systems::RenderSystem::init()
{
    required_pools.push_back(typeid(Transform));
    required_pools.push_back(typeid(Render));

    t_data = em->get_pool<Transform>();

    timer.start();
}

void ECS::Systems::RenderSystem::run()
{
    glm::mat4 projection_matrix = glm::ortho(0.0f, float(Globals::SCREEN_WIDTH), float(Globals::SCREEN_HEIGHT), 0.0f, float(Globals::SCREEN_HEIGHT), 0.0f);

    unsigned int proj_matrix_location = glGetUniformLocation(DisplayManager::shaderProgram, "proj_matrix");
    glUniformMatrix4fv(proj_matrix_location, 1, GL_FALSE, glm::value_ptr(projection_matrix));

    unsigned int spriteatlas_dim_location = glGetUniformLocation(DisplayManager::shaderProgram, "spriteatlas_dim");
    glUniform2f(spriteatlas_dim_location, DisplayManager::texture_width, DisplayManager::texture_height);

    unsigned int timer_loc = glGetUniformLocation(DisplayManager::shaderProgram, "timer");
    glUniform1f(timer_loc, timer.GetTime()/1000.0f);


    GLfloat instance_buffer[13 * entities.size()]; 

    int index = 0;
    for (auto &ent : entities)
    {
        auto i = em->get_data(ent, t_data);

        memcpy(&instance_buffer[index], &i->position, sizeof(i->position)); index += 3;
        memcpy(&instance_buffer[index], &i->scale, sizeof(i->scale)); index += 2;
        memcpy(&instance_buffer[index], &i->colors, sizeof(i->colors)); index += 4;
        memcpy(&instance_buffer[index], &i->tex_coords, sizeof(i->tex_coords)); index += 4;
    } 
    
    glBindVertexArray(DisplayManager::vao);
    glUseProgram(DisplayManager::shaderProgram);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(instance_buffer), instance_buffer);
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, entities.size());    
    glBindVertexArray(0);
}
