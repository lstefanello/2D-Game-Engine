#pragma once
#include <Components.h>
#include <Globals.h>
#include <vector>
#include <boost/unordered_map.hpp>
#include <typeindex>
#include <type_traits>
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <bits/stdc++.h>

namespace ECS
{
	class ComponentPoolBase
	{
		public:
			virtual ~ComponentPoolBase(){};
			std::vector<int> member_entities;
			unsigned int ID;
			boost::unordered_map<int, int> id_to_slot; //tells you which entity owns what data; ID gets mapped to slot in vector where entity's data lives
		protected:
			virtual constexpr void reg(int entity) = 0;
			virtual constexpr void rem(int entity) = 0;
			friend class EntityManager;
	};

	template<class T> 
	class ComponentPool : public ComponentPoolBase
	{
		public:
			std::vector<T> data; 
		private:
			constexpr void reg(int entity) override
			{
				data.emplace_back(T());
				member_entities.emplace_back(entity); 
				id_to_slot[entity] = data.size() - 1;
			}

			constexpr void rem(int entity) override
			{
				int index = id_to_slot.at(entity); 
				id_to_slot.erase(entity);
				data.erase(data.begin() + index);
				member_entities.erase(member_entities.begin() + index);

				for (int i = 0; i < data.size() - index; i++)
				{
					id_to_slot[member_entities[index + i]]	-= 1;
				}
			}	
	};

	typedef std::vector<std::type_index> t_vec;
	typedef boost::unordered_map<std::type_index, std::unique_ptr<ComponentPoolBase>> type_map;
	typedef boost::unordered_map<std::type_index, int> type_id_map;

	class EntityManager;
	class SystemBase
		{
		 public:
			 SystemBase(EntityManager* em) : em(em) {}; 
			 ~SystemBase(){};
			 virtual void run() = 0;
			 virtual void init() = 0;
			 void add(unsigned int ID);
			 void del(unsigned int ID);
		 private:
			 boost::unordered_map<int, int> id_to_slot;
		 protected:
			 t_vec required_pools;
			 std::bitset<64> signature;
			 std::vector<int> entities;
			 EntityManager* em;

			 friend class SystemsManager;
			 friend class EntityManager;
	 };

	class SystemsManager
	{
	 public:
		 friend class EntityManager;
		 SystemsManager(){};
		 void RunSystems();
	 private:
		 std::vector<std::unique_ptr<SystemBase>> system_order;
		 void create_signatures(EntityManager* em);
		 void build_systems(EntityManager* em);
		 void init_systems();
	};

	class EntityManager 
	{
		public:
			EntityManager();

			int create();

			template<typename T> constexpr void add(unsigned int ID)
			{
				auto* pool = key[typeid(T)].get();
				auto* comp_bitset = &ent_id_to_components[ID];

				if(!comp_bitset->test(pool->ID))
				{
					comp_bitset->set(pool->ID, true);
					pool->reg(ID);
					notify(0, ID);
				}
			}
				
			template<typename T> constexpr void del(unsigned int ID)
			{
				auto* pool = key[typeid(T)].get();
				auto* comp_bitset = &ent_id_to_components[ID];

				if (comp_bitset->test(pool->ID))
				{
					comp_bitset->set(pool->ID, false);
					pool->rem(ID);
					notify(1, ID);
				}
			}

			void destroy(unsigned int ID);

			template<typename T> bool query(unsigned int ID)
			{
				bool returnval = false;

				auto* pool = key[typeid(T)].get();
				auto* comp_bitset = &ent_id_to_components[ID];

				if (comp_bitset->test(pool->ID))
				{
					returnval = true;
				}
				
				return returnval;
			}



			template<typename T> constexpr T* get(unsigned int ID)
			{
				auto pool = static_cast<ComponentPool<T>*>(key[typeid(T)].get());
				return &pool->data[pool->id_to_slot.at(ID)];
			}

			template<typename T> T* get_data(unsigned int ID, ComponentPool<T>* pool)
			{
				return &pool->data[pool->id_to_slot.at(ID)];
			}

			template<typename T> constexpr ComponentPool<T>* get_pool()
			{
				return static_cast<ComponentPool<T>*>(key[typeid(T)].get());
			}

			type_id_map type_to_pool_id;
			std::bitset<64> fetch_components(unsigned int ID);
			void run_systems();

		private:
			SystemsManager sm;

			template<typename T> constexpr void create_pool()
			{
					key[typeid(T)] = std::make_unique<ComponentPool<T>>();
					key[typeid(T)].get()->ID = pool_id_counter;
					get_pool<T>()->data.reserve(Globals::MAX_ENTITIES);

					pool_id_to_mem_address[pool_id_counter] = key[typeid(T)].get();
					type_to_pool_id[typeid(T)] = pool_id_counter;
					pool_id_counter++;		
			}

			void notify(int action, unsigned int ID);

			type_map key;
			boost::unordered_map<int, ComponentPoolBase*> pool_id_to_mem_address;
			boost::unordered_map<int, std::bitset<64>> ent_id_to_components;
			std::vector<int> free_ids;			

			int entity_id_counter;
			int pool_id_counter;
	};
}
