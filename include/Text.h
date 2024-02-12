#pragma once
#include "ECS.h"

namespace Utilities
{
	enum alignments
	{
		left,
		right,
		center,
		top,
		middle,
		bottom,
		null
	};

	class Text
	{
		public:
			Text(ECS::EntityManager* eman);

			glm::vec4 color;
			glm::vec2 scale;
			glm::vec2 position; //top left vertex

			void print(std::string message); //worldspace x,y coordinate of top left vertex 
//			void align(int h_alignment, v_alignment, h_padding, v_padding);
		private:
			std::unordered_map<char, float> x_coord;
			std::unordered_map<char, float> y_coord;
			ECS::EntityManager* em;
			std::vector<ECS::ComponentPoolBase*> components;
	};
}
