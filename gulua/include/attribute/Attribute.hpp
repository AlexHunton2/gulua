#ifndef ATTRIBUTE
#define ATTRIBUTE
#pragma once

// Some Attributes:
namespace Attr {

// (0, 0) = Left Top, Pixel Point
typedef struct Point {
	int x;
	int y;
} Point;

typedef struct Color {
	int r;
	int g;
	int b;
	int a;
} Color;

}

#endif