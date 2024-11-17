#ifndef ATTRIBUTE
#define ATTRIBUTE
#pragma once

#include <vector>

namespace Attr {

typedef struct Attribute {} Attribute;

// Must initalize this, or create a specific Vector that does it
template <typename T>
struct AttributeVec : Attribute {
    std::shared_ptr<std::vector<T>> attrs;
};

// (0, 0) = Left Top, Pixel Point
typedef struct Point : Attribute {
    int x = 0;
    int y = 0;
} Point;

typedef struct PointVec : AttributeVec<Point> {
    PointVec() {
        std::shared_ptr<std::vector<Attr::Point>> _vertices = std::make_shared<std::vector<Attr::Point>>();
        for (int i=0; i < 3; i++) {
            Attr::Point pt;
            _vertices->push_back(pt);
        }
        attrs = _vertices;
    }
} PointVec;

typedef struct Color : Attribute {
    int r = 75; // 0 to 255
    int g = 144; // 0 to 255
    int b = 214; // 0 to 255
    int a = 80; // 0 to 100
} Color;

typedef struct Integer : Attribute {
    int _int = 0;
} Integer;

typedef struct String : Attribute {
    std::string _str = "";
} String;

}

#endif
