// Preprocessor Directives
#ifndef GULUA
#define GULUA
#pragma once

// External Headers
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Reference: https://github.com/nothings/stb/blob/master/stb_image.h#L4
// To use stb_image, add this in *one* C++ source file.
//     #define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <ft2build.h>
#include FT_FREETYPE_H

// Define Some Constants
const int mWidth = 1280;
const int mHeight = 800;

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

#define GULUA_OK 1
#define GULUA_ERR -1

#endif //~ GuLua Header
