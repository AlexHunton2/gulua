#ifndef ATTRIBUTE
#define ATTRIBUTE
#pragma once

#include <vector>

// Some Attributes:
namespace Attr {

typedef struct Attribute {} Attribute;

template <typename T>
struct AttributeVec : Attribute {
	std::shared_ptr<std::vector<T>> attrs;
};

// (0, 0) = Left Top, Pixel Point
typedef struct Point : Attribute {
	int x = 0;
	int y = 0;
} Point;
typedef AttributeVec<Point> PointVec;

typedef struct Color : Attribute {
	int r = 75; // 0 to 255
	int g = 144; // 0 to 255
	int b = 214; // 0 to 255
	int a = 80; // 0 to 100
} Color;

}

#endif