#include "entity/EntityRegistry.hpp"

EntityRegistry::EntityRegistry() {}

std::shared_ptr<EntityRegistry> EntityRegistry::getInstance() noexcept {
  	static std::shared_ptr<EntityRegistry> d(new EntityRegistry);
  	return d;
}

std::string EntityRegistry::add(std::shared_ptr<Entity> ent) noexcept {
	std::string id = util_generateid();
	std::string key = std::string(typeid(*ent).name()) + "@" + id;
	mEntities.insert({key, ent});
	mEntityOrder.push_back(key);
	ent->setID(key);
	return key;
}

int EntityRegistry::remove(std::string key) noexcept {
	mEntityOrder.remove(key);
	return mEntities.erase(key);
}

std::shared_ptr<Entity> EntityRegistry::get(std::string key) noexcept {
	auto it = mEntities.find(key);
    if (it != mEntities.end()) {
        return it->second;
    } 
    return nullptr;
}

std::vector<std::shared_ptr<Entity>> EntityRegistry::getAll() noexcept {
	std::vector<std::shared_ptr<Entity>> ret;
	for(std::list<std::string>::iterator it = mEntityOrder.begin(); it != mEntityOrder.end(); ++it) {
		std::shared_ptr<Entity> ent = get(*it);
		ret.push_back(ent);
	}
	return ret;
}

void EntityRegistry::clear() noexcept {
	mEntities.clear();
}

