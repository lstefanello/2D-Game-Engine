#pragma once
#include <StateManager.h>

namespace Editor
{
	class Tool;
	struct tile_data
	{
		glm::vec4 tex_coords;
		int layer;
		int ghost{-1};
		Tool* current_tool;
		int selected_ID{-1};
		std::vector<boost::unordered_map<std::pair<int,int>, int>> cell_id_to_entity_id;
	};

	class Tool
	{
		public:
			~Tool(){};

			virtual void run(EntityManager* eman, tile_data* data) = 0;
			const char* name;
	};

	class Brush : public Tool
	{
		public:
			Brush(){name = "Brush";}
			void run(EntityManager* eman, tile_data* data);
	};

	class Eraser : public Tool
	{
		public:
			Eraser(){name = "Eraser";}
			void run(EntityManager* eman, tile_data* data);
	};

	void Toolbox(tile_data* data, EntityManager* eman,  const std::vector<std::unique_ptr<Editor::Tool>>* toolbox);
	void TileEditor(tile_data* data, EntityManager* eman, const DisplayManager::Texture* tex, glm::vec4* tex_coords);

	class Selection : public Tool
	{
		public:
			Selection(){name = "Selection";}
			void run(EntityManager* eman, tile_data* data);
	};
}

namespace StateManager
{
	class Game : public State
	{
		public:
			Game();
			~Game();

			void Events(StateManager::Manager* sm);
			void Logic();

		private:
			DisplayManager::Texture spritesheet{"../resources/tiles.png"};
			Editor::tile_data current_data;
			std::vector<std::unique_ptr<Editor::Tool>> toolbox;
	};	
}
