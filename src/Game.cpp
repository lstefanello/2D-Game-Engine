#include <Game.h> 

void Editor::TileEditor(tile_data* data, EntityManager* eman, const DisplayManager::Texture* tex, glm::vec4* tex_coords)
{
/*    ImVec2 size = ImVec2(32.0f, 32.0f);                         
    ImVec4 bg_col = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);             
    ImVec4 tint_col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);           

    ImGui::Begin("Tile Picker");
        
    int columns = int(std::floor(tex->width / 32.0f));
    int rows = int(std::floor(tex->height/ 32.0f));
    
    int ID = 0;
    for (int i = 0; i < rows; i++)
    {
        for(int j = 0; j < columns; j++)
        {
            ImVec2 uv0 = ImVec2((j * 32.f)/tex->width, (i * 32.f)/tex->height);
            ImVec2 uv1 = ImVec2(((j+1) * 32.f)/tex->width, ((i+1) * 32.f)/tex->height);

            ImGui::PushID(ID);
            ID++;

            if(ImGui::ImageButton("", (void*)(intptr_t)tex->ID, size, uv0, uv1, bg_col, tint_col))
            {
                *tex_coords = {uv0.x * tex->width, uv0.y * tex->height, 32.0f, 32.0f}; 

                if (data->ghost != -1)
                {
                    eman->destroy(data->ghost);
                }

                data->ghost = eman->create();
                eman->add<Transform>(data->ghost);
                eman->add<Render>(data->ghost);
                eman->add<FollowMouse>(data->ghost);

                auto t_data = eman->get<Transform>(data->ghost);
                t_data->tex_coords = *tex_coords;
                t_data->colors = {1.0f, 0.0f, 0.0f, 0.5f};
                t_data->scale = {32.0f, 32.0f};
                t_data->position.z = float(Globals::SCREEN_HEIGHT) - 1.0f; 
            }
            ImGui::SameLine();
            ImGui::PopID();
        }
        ImGui::NewLine();
    }
    
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
    */
}

void Editor::Brush::run(EntityManager* eman, tile_data* data)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    int x_id = int(std::floor(x/32.0f)); 
    int y_id = int(std::floor(y/32.0f)); 
    auto key = std::make_pair(x_id, y_id);

    if (data->cell_id_to_entity_id[data->layer-1].count(key) != 0)
    {
        int ID = data->cell_id_to_entity_id[data->layer-1][key];
        eman->destroy(ID);
        data->cell_id_to_entity_id[data->layer-1].erase(key);
    }
    
    int entity = eman->create();
    data->cell_id_to_entity_id[data->layer-1][key] = entity;
    
    eman->add<Transform>(entity);
    eman->add<Render>(entity);
    auto* t_data = eman->get<Transform>(entity);
    
    t_data->position.x = x_id*32.0f + 16.0f;
    t_data->position.y = y_id*32.0f + 16.0f;
    t_data->position.z = data->layer; 
    t_data->tex_coords = data->tex_coords;
    t_data->colors = {1.0f, 1.0f, 1.0f, 1.0f};
    t_data->scale = {32.0f, 32.0f};
}

void Editor::Eraser::run(EntityManager* eman, tile_data* data)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    int x_id = int(std::floor(x/32.0f)); 
    int y_id = int(std::floor(y/32.0f)); 
    auto key = std::make_pair(x_id, y_id);

    if (data->cell_id_to_entity_id[data->layer-1].count(key) != 0)
    {
        int ID = data->cell_id_to_entity_id[data->layer-1][key];
        eman->destroy(ID);
        data->cell_id_to_entity_id[data->layer-1].erase(key);
    }
}

void Editor::Selection::run(EntityManager* eman, tile_data* data)
{
    int x, y;
    SDL_GetMouseState(&x, &y);

    int x_id = int(std::floor(x/32.0f)); 
    int y_id = int(std::floor(y/32.0f)); 
    auto key = std::make_pair(x_id, y_id);

    if (data->cell_id_to_entity_id[data->layer-1].count(key) != 0)
    {
        data->selected_ID = data->cell_id_to_entity_id[data->layer-1][key];
    }
}

void Editor::Toolbox(tile_data* data, EntityManager* eman, const std::vector<std::unique_ptr<Tool>>* toolbox)
{
/*    ImGui::Begin("Toolbox");
    ImGui::Separator();
    ImGui::Text("Tools");
    ImGui::Separator();

    ImGui::Text("Current Tool:");
    ImGui::SameLine();
    ImGui::Text(data->current_tool->name);

    for (auto &t : *toolbox)
    {
        if (ImGui::Button(t.get()->name))
        {
            data->current_tool = t.get();  
        }
    }

    ImGui::Separator();
    ImGui::Text("Selection");
    ImGui::Separator();

    ImGui::Text("Selected ID:");
    ImGui::SameLine();
    if (data->selected_ID == -1)
    {
        ImGui::Text("Nothing");
    }
    else
    {
        ImGui::Text(std::to_string(data->selected_ID).c_str());
    }

    ImGui::Separator();
    ImGui::Text("Layers");
    ImGui::Separator();
    ImGui::Text("Current Layer:");
    ImGui::SameLine();
    ImGui::Text(std::to_string(data->layer).c_str());

    if (ImGui::Button("New Layer"))
    {
        data->cell_id_to_entity_id.emplace_back(boost::unordered_map<std::pair<int, int>, int>());
    }

    for (int i = 0; i < data->cell_id_to_entity_id.size(); i++)
    {
        auto layer_num = std::to_string(i+1); 
        if (ImGui::Button(layer_num.c_str()))
        {
            data->layer = i+1;
        }

        ImGui::SameLine();
        ImGui::PushID(i);
        if (ImGui::Button("Delete"))
        {

        }
        ImGui::PopID();
    }

    ImGui::End();
    */
}

StateManager::Game::Game()
{ 
  /*  toolbox.push_back(std::make_unique<Editor::Brush>());
    toolbox.push_back(std::make_unique<Editor::Eraser>());
    toolbox.push_back(std::make_unique<Editor::Selection>());*/

   // current_data.cell_id_to_entity_id.emplace_back(boost::unordered_map<std::pair<int, int>, int>());

   // current_data.current_tool = toolbox[0].get();
    //current_data.layer = 1; 
    //srand(time(0));

//        auto* emitter = em.get<ParticleEmitter>(guys[i]);
 //       emitter->colors = {(double)rand()/(double)RAND_MAX, (double)rand()/(double)RAND_MAX, (double)rand()/(double)RAND_MAX, 1.0f};
   //    auto* a_data = em.get<Animated>(guys[0]);
    //a_data->next_state = anim_states::idle; 
    
}

StateManager::Game::~Game()
{
}

void StateManager::Game::Events(Manager* sm)
{
    while(SDL_PollEvent(&event))
    {
 //       ImGui_ImplSDL2_ProcessEvent(&event);

        if (event.type == SDL_QUIT)
        {
            sm->queue_state(states::state_exit);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch(event.key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    sm->queue_state(states::state_exit);
                break;

                case SDLK_RETURN:
                    sm->queue_state(states::state_game);
                break; 
            }
        }
    }
/*        else if (event.type == SDL_MOUSEBUTTONDOWN)
        {
            if(!ImGui::GetIO().WantCaptureMouse)
            {
                current_data.current_tool->run(&em, &current_data);
            }
        }*/
//    }
}

void StateManager::Game::Logic()
{
//    ImGui_ImplOpenGL3_NewFrame();
 //   ImGui_ImplSDL2_NewFrame();
  //  ImGui::NewFrame();

    Editor::Toolbox(&current_data, &em, &toolbox);
    Editor::TileEditor(&current_data, &em, &spritesheet, &current_data.tex_coords);

    em.run_systems();
    
  //  ImGui::Render();
   // ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
