#ifndef NODE_H
#define NODE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

// GLM headers
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <memory>

#include "shaders.h"

class Node{

    public:

        Node(int index);
        Node(int index, std::shared_ptr<Node> parent);
        Node(int index, float* vertices, unsigned int* indices, unsigned int vertex_count, unsigned int index_count
            , int stride, Shader& shader, std::shared_ptr<Node> parent = nullptr
        );

        // getters
        float get_rotation_x() { return rotation_x; }
        float get_rotation_y() { return rotation_y; }
        float get_rotation_z() { return rotation_z; }
        // glm::mat4 get_rotation() { return rotation; }

        float get_translation_x() { return tx; }
        float get_translation_y() { return ty; }
        float get_translation_z() { return tz; }

        glm::vec3 get_cor() { return center_of_rotation; }
        std::shared_ptr<Node> get_parent() { return parent; }

        // setters
        void set_cor(glm::vec3 center_of_rot) { center_of_rotation = center_of_rot; }

        void set_rotation_x(float val) {
            if (dof_x) rotation = glm::rotate(glm::mat4(1.0f), glm::radians(val), glm::vec3(1.0f, 0.0f, 0.f)) * rotation;
        }
        void set_rotation_y(float val) {
            if (dof_y) rotation = glm::rotate(glm::mat4(1.0f), glm::radians(val), glm::vec3(0.0f, 1.0f, 0.0f)) * rotation;
        }
        void set_rotation_z(float val) {
            if (dof_z) rotation = glm::rotate(glm::mat4(1.0f), glm::radians(val), glm::vec3(0.0f, 0.0f, 1.0f)) * rotation;
        }

        void set_dof_x(bool val) { dof_x = val; }
        void set_dof_y(bool val) { dof_y = val; }
        void set_dof_z(bool val) { dof_z = val; }

        void set_translation_x(float val) { tx = val; }
        void set_translation_y(float val) { ty = val; }
        void set_translation_z(float val) { tz = val; }

        void set_parent(std::shared_ptr<Node> parent) { this->parent = parent; } 
        void set_children(std::vector<std::shared_ptr<Node>> children) { this->children = children; }

        void set_vertices(float* vertices) { this->vertices = vertices;}
        void set_indices(unsigned int* indices) { this->indices = indices; }
        void set_stride(int stride) { this->stride = stride; }
        void set_vertex_count(unsigned int vertex_count) { this->vertex_count = vertex_count; }
        void set_index_count(unsigned int index_count) { this->index_count = index_count; }
        // void set_base_index_count(unsigned int base_index_count) { this->base_index_count = base_index_count; }
        void set_base_index(unsigned int base_index) { this->base_index = base_index; }
        void set_top_index(unsigned int top_index) { this->top_index = top_index; }

        void set_render_mode(unsigned int render_mode) { this->render_mode = render_mode; }
        void set_shader(Shader &shader) { this->shader = shader; }

        // rendering functions
        void insert_child(std::shared_ptr<Node> child) { children.push_back(child); }
        void init_buffers();
        void render();
        void render_tree(int index, bool flag);
        glm::mat4 rotationMatrix();
        glm::mat4 modelMatrix();

        // matrix stack methods
        static glm::mat4 top_stack();
        static void pop_stack();
        static void push_stack(glm::mat4 mat);

    private:

        int index;

        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        float* vertices;
        unsigned int* indices;
        unsigned int vertex_count;
        unsigned int index_count;
        unsigned int render_mode = 0;
        // unsigned int base_index_count;
        unsigned int base_index;
        unsigned int top_index;

        int stride = 8;

        Shader shader;

        glm::vec3 center_of_rotation;

        float rotation_x;
        float rotation_y;
        float rotation_z;
        bool dof_x = true;
        bool dof_y = true;
        bool dof_z = true;

        float tx, ty, tz;

        glm::mat4 rotation;

        std::vector<std::shared_ptr<Node>> children;
        std::shared_ptr<Node> parent;

        static std::vector<glm::mat4> matrix_stack;

};

class Primitive {

};

#endif