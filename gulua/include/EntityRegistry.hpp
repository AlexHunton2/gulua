#ifndef ENTITY_REG
#define ENTITY_REG

#include <string>
#include <vector>

#include "Entity.hpp"

// singleton
class EntityRegistry {
private:
	static EntityRegistry* _instance;
	EntityRegistry();
	~EntityRegistry();

	static std::vector<Entity> m_entities;

public:
	static EntityRegistry* getInstance();
	static void add(Entity ent);
	static void remove(std::string key);
	static Entity* get(std::string key);
	static std::vector<Entity>* getAll();
};

#endif