#include "camera.h"


Camera :: Camera() 
    : cameraPos(glm::vec3(0.0f, 2.5f,  20.0f)), cameraFront(glm::vec3(0.0f, 0.0f, -1.0f)),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)) {}

Camera :: Camera(glm::vec3 pos, glm::vec3 camFront) 
    : cameraPos(pos), cameraFront(camFront),
    cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)) {}


void Camera :: processKeyboard(
    GLFWwindow* window, int key, int action, float deltaTime
) {
    float cameraSpeed = deltaTime * 50.0f;

    if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        cameraPos += cameraFront * cameraSpeed;
    }

    if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        cameraPos -= cameraFront * cameraSpeed;
    }

    if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }

    if (key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        cameraPos += cameraUp * cameraSpeed;
    }

    if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT)){
        cameraPos -= cameraUp * cameraSpeed;
    }

}
