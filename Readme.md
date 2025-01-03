# [GuLua](https://github.com/AlexHunton2/gulua)

## Summary
GuLua (<ins>G</ins>raphical <ins>u</ins>tility \[for\] <ins>Lua</ins>) is a graphics library wrapped around OpenGL for the Lua Programming Language. GuLua allows for the drawing of basic geometric objects and input handling in order to create simple graphics programs with Lua.

Inspiration of design was taken from different projects:
* [Processing](https://processingfoundation.org) - Similar idea, but with Lua.
* [GMod](https://wiki.facepunch.com/gmod/) - Lua design of *Entities* and *Hooks*
* [Glitter](https://github.com/Polytonic/Glitter) - Code template starting point.

This project is particularly thankful to Processing and GMod as it serves as a a love letter to both as they were instrumental in my computer science journey.

Finally if you are looking for a project with more support that does the same thing check out [Love](https://love2d.org/wiki/love.graphics)

## Dependencies:
The following are the submodules of this project located in `gulua/external`
* [Lua](https://www.lua.org) - User inputted code
* [glad](https://github.com/Dav1dde/glad) - OpenGL Function Loader
* [glfw](https://github.com/glfw/glfw) - Window and Input
* [glm](https://github.com/g-truc/glm) - OpenGL Math
* [stb](https://github.com/nothings/stb) - Texture Loading
* [FreeType](https://gitlab.freedesktop.org/freetype/freetype) - Font/Text Loading

## Getting Started

#### Step 1: Cloning
```bash
git clone ...
cd gulua
git submodule update --init --recursive
cd build
```

#### Step 2: Building
```bash
# UNIX Makefile
cmake ..

# Mac OSX
cmake -G "Xcode" ..

# Microsoft Windows
cmake -G "Visual Studio 14" ..
cmake -G "Visual Studio 14 Win64" ..
...
```

```bash
make
```

#### Step 3: Running
In the build folder, you are able to run some of the examples provided:

```bash
cd gulua
./gulua <relative location of lua file> 
```
Example:
```bash
cd gulua && ./gulua ../../gulua/examples/trianglemove.lua && cd ..  
```
** Must be in the gulua folder while running the program so the shaders can find themselves.

## Documentation

TODO: Documentation!

## License
>The MIT License (MIT)

>Copyright (c) 2023 Alex Hunton

>Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

>The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

>THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
