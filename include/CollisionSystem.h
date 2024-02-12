#pragma once
#include <Globals.h>
#include <cmath>
#include <ECS.h>

namespace ECS
{
	namespace Systems
	{
        class CollisionSystem : public SystemBase
          {
                public:
                CollisionSystem(EntityManager* em) : SystemBase(em){};

                void run();
                void init();
                private:

        int cell_dim;
        int num_cells;
        //std::vector<bool> member_cells;
        boost::unordered_map<int, std::vector<bool>> static_member_cells; //kee    p a bitset to make sure we're not registering duplicates
        boost::unordered_map<int, std::vector<bool>> dynamic_member_cells;
  
        void BuildStaticHashMap();
        bool static_hashmap_built{false};
        void BuildDynamicHashMap();
                                     
        void DetectCollisions();
        void ResolveCollisions();
        std::array<std::pair<float, float>, 4> GetVertices(int ID);
        int GetCellID(std::pair<float, float> vertex); //cells in hashmap are     indexed one-dimensionally. This function takes in vertex coordinates and s    pits out the cell number the entity is inside
        void AddToStaticCell(int ID, std::pair<float, float> vertex);
        void AddToDynamicCell(int ID, std::pair<float, float> vertex);
  
        boost::unordered_map<int, std::vector<int>> static_hmap;
        boost::unordered_map<int, std::vector<int>> dynamic_hmap;
        boost::unordered_map<int, std::vector<int>> key; //maps entity ID with     a dynamic collider component to a vector of cell IDs that it lives inside
        std::vector<std::pair<int, int>> static_dynamic_collisions; //collisi    ons between a static collider and a dynamic collider
        EntityManager* pman;
          };
	}
}
