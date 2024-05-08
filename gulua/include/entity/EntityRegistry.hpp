#ifndef ENTITY_REG
#define ENTITY_REG

#include <memory>
#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include <typeinfo>

#include "Entity.hpp"

// singleton
class EntityRegistry {
private:
	EntityRegistry();

	std::map<std::string, std::shared_ptr<Entity>> mEntities;
	std::unordered_set<int> mIds;
public:
	static std::shared_ptr<EntityRegistry> getInstance() noexcept;
	std::string add(std::shared_ptr<Entity> ent) noexcept;
	int remove(std::string key) noexcept; // 0 means none removed, 1 means success
	std::shared_ptr<Entity> get(std::string key) noexcept;
	std::vector<std::shared_ptr<Entity>> getAll() noexcept;
	void clear() noexcept;
};

#endif