#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glad/glad.h>

// GLM headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
    public:
        glm::vec3 cameraPos;
        glm::vec3 cameraFront;
        glm::vec3 cameraUp;
        glm::vec3 cameraRight;

        float fov = 45.0f;

    public:

        Camera();
        Camera(glm::vec3 pos, glm::vec3 camFront);

        glm::mat4 getViewMatrix() const {
            return glm::lookAt(cameraPos, cameraPos+cameraFront, cameraUp);
        }

        void processKeyboard(GLFWwindow* window, int key, int action, float deltaTime);
};

#endif