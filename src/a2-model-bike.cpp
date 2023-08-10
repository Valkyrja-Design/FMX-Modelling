#include <iostream>
#include <math.h>
#include <chrono>
#include <fstream>
#include <vector>

#define GLFW_DLL

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils/renderer.h"

Renderer rr;

void framebuffer_size_callback(GLFWwindow* window, int width, int height){
    glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (action == GLFW_RELEASE) rr.keys[key] = false;
    else if (action == GLFW_PRESS) rr.keys[key] = true;
    
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    rr.cam.processKeyboard(window, key, action, rr.deltaTime);

    if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.rotationHandler(Renderer::CLOCK_X);
    } else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.rotationHandler(Renderer::CCLOCK_X);
    } else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.rotationHandler(Renderer::CCLOCK_Y);
    } else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.rotationHandler(Renderer::CLOCK_Y);
    } else if (key == GLFW_KEY_LEFT_BRACKET && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.rotationHandler(Renderer::CCLOCK_Z);
    } else if (key == GLFW_KEY_RIGHT_BRACKET && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.rotationHandler(Renderer::CLOCK_Z);
    } else if (key == GLFW_KEY_Q && (action == GLFW_PRESS)){
        rr.changeObject(-1);
    } else if (key == GLFW_KEY_E && action == GLFW_PRESS){
        rr.changeObject(1);
    } else if (key == GLFW_KEY_I && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.objectRotationHandler(Renderer::CLOCK_X);
    } else if (key == GLFW_KEY_K && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.objectRotationHandler(Renderer::CCLOCK_X);
    } else if (key == GLFW_KEY_J && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.objectRotationHandler(Renderer::CCLOCK_Z);
    } else if (key == GLFW_KEY_L && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.objectRotationHandler(Renderer::CLOCK_Z);
    } else if (key == GLFW_KEY_U && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.objectRotationHandler(Renderer::CLOCK_Y);
    } else if (key == GLFW_KEY_O && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.objectRotationHandler(Renderer::CCLOCK_Y);
    } else if (key == GLFW_KEY_T && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.modelTranslationHandler(Renderer::NEG_Z);
    } else if (key == GLFW_KEY_G && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.modelTranslationHandler(Renderer::POS_Z);
    } else if (key == GLFW_KEY_F && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.modelTranslationHandler(Renderer::NEG_X);
    } else if (key == GLFW_KEY_H && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.modelTranslationHandler(Renderer::POS_X);
    } else if (key == GLFW_KEY_R && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.modelTranslationHandler(Renderer::POS_Y);
    } else if (key == GLFW_KEY_Y && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        rr.modelTranslationHandler(Renderer::NEG_Y);
    }
    
}

int main(){
    // std::cout<<"main()\n";
    rr.setCallbacks(framebuffer_size_callback, key_callback);
    rr.render_rider = false;
    rr.render_track = false;
    
    rr.changeModel(1);
    rr.render();

    return 0;
}