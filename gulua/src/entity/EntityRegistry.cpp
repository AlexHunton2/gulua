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
	ent->setID(key);
	return key;
}

int EntityRegistry::remove(std::string key) noexcept {
	return mEntities.erase(key);
}

std::shared_ptr<Entity> EntityRegistry::get(std::string key) noexcept {
	auto it = mEntities.find(key);
    if (it != mEntities.end()) {
        return it->second;
    } else {
        return nullptr;
    }
}

std::vector<std::shared_ptr<Entity>> EntityRegistry::getAll() noexcept {
	std::vector<std::shared_ptr<Entity>> ret;
	for(std::map<std::string, std::shared_ptr<Entity>>::iterator it = mEntities.begin(); it != mEntities.end(); ++it) {
		ret.push_back(it->second);
	}
	return ret;
}

void EntityRegistry::clear() noexcept {
	mEntities.clear();
}

