#pragma once
#include <Globals.h>
#include <ECS.h>
#include <boost/unordered_set.hpp>

namespace ECS
{
	namespace Systems
	{
		class FrustumCullingSystem : public SystemBase
		{
			public:
				FrustumCullingSystem(EntityManager* em) : SystemBase(em) {};
				void run();
				void init();

			private:
				ComponentPool<Transform>* t_pool;
				ComponentPool<StaticRender>* stat_r_pool;
				ComponentPool<DynamicRender>* dyn_r_pool;
				ComponentPool<Render>* r_pool;
				ComponentPool<Camera>* cam_pool;

				int cell_width;
				int cell_height;
				int W; //# of columns in cell grid
				int H; //# rows
				float cam_w; //camera dimensions
				float cam_h;
				bool static_map_created;

				std::vector<std::vector<int>> static_map;
				boost::unordered_set<int> visible_cells; //from last frame to compare

				void BuildStaticMap(); //would like to just put this in init and not check every frame, but when init() is called, no entities have been created yet, so that would segfault.
				int FindCell(float x, float y);
				void FindVisibleCells(boost::unordered_set<int>* s);
				int FindCameraCell();
				void Compare(boost::unordered_set<int>* s); //compares new visible cells with last frame's to determine which cells to render and which to not
		};
	}
}
