// Local Headers
#include "gulua.hpp"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>
#include <memory>
#include <vector>

// lua
#include "luaapi/luaAPI.hpp"

// Entity
#include "entity/EntityRegistry.hpp"
#include "entity/Entity.hpp"

int main(int argc, char * argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Error: Sorry! Need lua file to run!\n");
        return EXIT_FAILURE;
    }

    const char* fileName = argv[1];

    // Load GLFW and Create a Window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    auto mWindow = glfwCreateWindow(mWidth, mHeight, "GuLua", nullptr, nullptr);

    // Check for Valid Context
    if (mWindow == nullptr) {
        fprintf(stderr, "Failed to Create OpenGL Context");
        return EXIT_FAILURE;
    }

    // Create Context and Load OpenGL Functions
    glfwMakeContextCurrent(mWindow);
    gladLoadGL();
    fprintf(stderr, "OpenGL %s\n", glGetString(GL_VERSION));

    // Lua
    luaAPI::loadLua(fileName);

    // testing entities
    std::shared_ptr<EntityRegistry> ent_reg = EntityRegistry::getInstance();
    
    // Rendering Loop
    while (glfwWindowShouldClose(mWindow) == false) {
        if (glfwGetKey(mWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(mWindow, true);

        // Background Fill Color
        glClearColor(0.25f, 0.25f, 0.25f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // get all entities
        std::vector<std::shared_ptr<Entity>> entities = ent_reg->getAll();

        // init
        for (auto entity : entities) {
            if (entity->isInitalized()) {
                continue;
            }
            entity->init();
        }

        // draw
        for (auto entity : entities) {
            entity->draw();
        }

        // Flip Buffers and Draw
        glfwSwapBuffers(mWindow);
        glfwPollEvents();
    }   

    glfwTerminate();
    return EXIT_SUCCESS;
}
