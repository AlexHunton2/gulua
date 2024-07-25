#include "entity/Entity.hpp"

std::shared_ptr<Attr::Color> PolygonEntity::getColor() {
	auto attr_ptr = std::static_pointer_cast<Attr::Color>(mAttrMap["color"]);
	if (attr_ptr == nullptr) {
		// default
		std::shared_ptr<Attr::Color> color = std::make_shared<Attr::Color>();
		setColor(color);
		return color;
	}
	return attr_ptr;
}

void PolygonEntity::setColor(std::shared_ptr<Attr::Color> color) {
	mAttrMap["color"] = color;
}