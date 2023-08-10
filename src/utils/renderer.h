#ifndef RENDERER_H
#define RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shaders.h"
#include "texture.h"
#include "camera.h"
#include "Sphere.h"
#include "node.h"
#include "Cylinder.h"

#include <set>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <sstream>

class Renderer {
    public:

        enum ROTATION_DIRECTION{
            CLOCK_X, CCLOCK_X, CLOCK_Y, CCLOCK_Y, CLOCK_Z, CCLOCK_Z
        };

        enum TRANSLATION_DIRECTION{
            POS_X, NEG_X, POS_Y, NEG_Y, POS_Z, NEG_Z
        };
        
        Renderer();

        void setCallbacks(GLFWframebuffersizefun framebuffer_size_callback, GLFWkeyfun key_callback) {
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
            glfwSetKeyCallback(window, key_callback);
        }

        void initBike();
        void initHuman();
        void initTrack();
        void render();

        void getModelMatrix(glm::mat4& modelMat, int model);
        void objectRotationHandler(enum ROTATION_DIRECTION);
        void modelTranslationHandler(enum TRANSLATION_DIRECTION);
        void rotationHandler(enum ROTATION_DIRECTION);
        void changeObject(int dir);
        void changeModel(int dir);
        
        // quad generates two triangles for each face and assigns colors to the vertices
        void quad1(int a, int b, int c, int d);

        void quad2(int a, int b, int c, int d);


        void ground();

        void track();

        void initBuffersGL(void);

        ~Renderer() {
            glfwTerminate();
        }

    private:
        // Window info
        const float aspect_ratio;
        const int height;
        const int width;
        GLFWwindow* window;

        Shader shader;

        // All nodes
        std::vector<std::shared_ptr<Node>> nodesHuman;
        std::vector<std::shared_ptr<Node>> nodesBike;
        std::vector<std::shared_ptr<Node>> nodesTrack;

        // Human body part nodes
        std::shared_ptr<Node> Torso1;    // root of tree
        std::shared_ptr<Node> UArmL;
        std::shared_ptr<Node> LArmL;
        std::shared_ptr<Node> HandL;
        std::shared_ptr<Node> UArmR;
        std::shared_ptr<Node> LArmR;
        std::shared_ptr<Node> HandR;
        std::shared_ptr<Node> Head;
        std::shared_ptr<Node> Torso3;
        std::shared_ptr<Node> ThighL;
        std::shared_ptr<Node> ThighR;
        std::shared_ptr<Node> LegL;
        std::shared_ptr<Node> LegR;
        std::shared_ptr<Node> FootL;
        std::shared_ptr<Node> FootR;

        // Human part objects (made of only spheres)
        std::vector<Sphere> h_sphereObjects;

        // Bike parts
        std::shared_ptr<Node> Body;
        std::shared_ptr<Node> FWheel;
        std::shared_ptr<Node> RWheel;
        std::shared_ptr<Node> Handle;

        std::shared_ptr<Node> t1;
        std::shared_ptr<Node> t2;

        std::shared_ptr<Node> fwBearing;
        std::shared_ptr<Node> rwBearing;

        std::shared_ptr<Node> seat1;
        std::shared_ptr<Node> seat2;
        std::shared_ptr<Node> seat3;

        // Sphere part objects
        std::vector<Sphere> b_sphereObjects;
        std::vector<Cylinder> b_cylinderObjects;

        int curr_obj_human = 0;
        int curr_obj_bike = 0;
        int curr_model = 0;

        unsigned int VAO, VBO, EBO;

        float rotate_x;
        float rotate_y;
        float rotate_z;


    public:
        // Camera
        Camera cam;

        bool render_bike = true;
        bool render_rider = true;
        bool render_track = true;

        glm::vec3 bikePosition;
        glm::vec3 humanPosition;
        glm::vec3 trackPosition;
        glm::mat4 trackRotation;

        float speed = 100.0f;

        glm::vec3 centroid;
        float bikeScale = 1.0f;
        float riderScale = 1.0f;
        float trackScale = 1.0f;

        glm::mat4 rotation;

        // Storage key press info
        bool keys[GLFW_KEY_MENU+1];
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        Shader shaderTrack;
        GLuint vbo, vao;

        glm::vec4 positions_ground[4] = {
        glm::vec4(10.0, -0.5, 10.0, 1.0),
        glm::vec4(-10.0, -0.5, 10.0, 1.0),
        glm::vec4(-10.0, -0.5, -10.0, 1.0),
        glm::vec4(10.0, -0.5, -10.0, 1.0)
        };


        glm::vec4 positions_track[65] = {
        glm::vec4(-4.0, 0.0, 0.0, 1.0),
        glm::vec4(-4.0, 0.0, 0.5, 1.0),

        glm::vec4(0.8, 0.0, 0.0, 1.0),
        glm::vec4(0.8, 0.0, 0.5, 1.0),

        glm::vec4(1.6, 0.3, 0.0, 1.0),
        glm::vec4(1.6, 0.3, 0.5, 1.0),

        glm::vec4(2.4, 0.3, 0.0, 1.0),
        glm::vec4(2.4, 0.3, 0.5, 1.0),

        glm::vec4(2.9, 0.3, 0.0, 1.0),
        glm::vec4(2.9, 0.3, 1.0, 1.0),
        glm::vec4(2.4, 0.3, 1.0, 1.0),

        glm::vec4(2.4, 0.0, 1.8, 1.0),
        glm::vec4(2.9, 0.0, 1.8, 1.0), //<-- 13


        // glm::vec4(2.9, 0.0, 2.3, 1.0),
        // glm::vec4(-4.0, 0.0, 2.3, 1.0),
        // glm::vec4(-4.0, 0.0, 1.8, 1.0),

        // glm::vec4(-4.5, 0.0, 2.3, 1.0),
        // glm::vec4(-4.5, 0.0, 0.0, 1.0)

        glm::vec4(2.9, 0.0, 3.3, 1.0),
        glm::vec4(2.4, 0.0, 3.3, 1.0),

        glm::vec4(2.9, 0.0, 3.8, 1.0),
        glm::vec4(1.8, 0.0, 3.8, 1.0),
        glm::vec4(1.8, 0.0, 3.3, 1.0), //<--18

        glm::vec4(1.0, 1.0, 3.8, 1.0),
        glm::vec4(1.0, 1.0, 3.3, 1.0),

        glm::vec4(0.5, 0.5, 3.8, 1.0),
        glm::vec4(0.5, 0.5, 3.3, 1.0),


        glm::vec4(0.0, 0.0, 3.8, 1.0),
        glm::vec4(0.0, 0.0, 3.3, 1.0), //<--24


        glm::vec4(-1.0, 0.2, 3.8, 1.0),
        glm::vec4(-1.0, 0.2, 3.3, 1.0),//<--26

        glm::vec4(-2.0, 0.2, 3.3, 1.0),
        glm::vec4(-2.0, 0.2, 5.0, 1.0),

        glm::vec4(-1.0, 0.2, 5.0, 1.0),
        glm::vec4(-1.0, 0.2, 4.5, 1.0), //<--30

        glm::vec4(0.0, 0.0, 5.0, 1.0),
        glm::vec4(0.0, 0.0, 4.5, 1.0), //<--32

        glm::vec4(1.0, 0.5, 5.0, 1.0),
        glm::vec4(1.0, 0.5, 4.5, 1.0), //<--34


        glm::vec4(2.0, 0.0, 5.0, 1.0),
        glm::vec4(2.0, 0.0, 4.5, 1.0), //<--36


        glm::vec4(3.0, 0.5, 5.0, 1.0),
        glm::vec4(3.0, 0.5, 4.5, 1.0), //<--38


        glm::vec4(4.0, 0.0, 5.0, 1.0),
        glm::vec4(4.0, 0.0, 4.5, 1.0), //<--40


        glm::vec4(5.0, 0.0, 5.0, 1.0),
        glm::vec4(5.0, 0.0, 7.0, 1.0), //<--42

        glm::vec4(4.0, 0.0, 6.5, 1.0),
        glm::vec4(4.0, 0.0, 7.0, 1.0), //<--44


        glm::vec4(3.5, 0.5, 6.5, 1.0),
        glm::vec4(3.5, 0.5, 7.0, 1.0), //<--46


        glm::vec4(2.5, 0.5, 6.5, 1.0),
        glm::vec4(2.5, 0.5, 7.0, 1.0), //<--48

        glm::vec4(2.0, 0.0, 6.5, 1.0),
        glm::vec4(2.0, 0.0, 7.0, 1.0), //<--50

        glm::vec4(1.0, 0.0, 6.5, 1.0),
        glm::vec4(1.0, 0.0, 7.0, 1.0), //<--52


        glm::vec4(0.5, 1.0, 6.5, 1.0),
        glm::vec4(0.5, 1.0, 7.0, 1.0), //<--54

        glm::vec4(-1.0, 0.5, 6.5, 1.0),
        glm::vec4(-1.0, 0.5, 7.0, 1.0), //<--56

        glm::vec4(-1.5, 0.0, 6.5, 1.0),
        glm::vec4(-1.5, 0.0, 7.0, 1.0), //<--0.5


        glm::vec4(-3.5, 0.0, 8.0, 1.0),
        glm::vec4(-4.0, 0.0, 7.5, 1.0), //<--60
        
        glm::vec4(-3.5, 0.0, 6.8, 1.0),
        glm::vec4(-2.5, 0.0, 5.0, 1.0), //<--62
        
        glm::vec4(-3.5, 0.0, 5.0, 1.0),
        glm::vec4(-5.0, 0.0, 3.0, 1.0), //<--64
        
        glm::vec4(-6.0, 0.0, 3.0, 1.0)

        };


        int tri_idx=0;
        const int n_vert = (29 * 2 * 3) + 6;

        glm::vec4 v_positions[180];
        glm::vec4 v_colors[180];
        glm::vec4 track_color = glm::vec4(0.5,0.5,0.5,1.0);//gray color


};

#endif