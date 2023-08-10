#include "node.h"

std::vector<glm::mat4> Node :: matrix_stack = { glm::mat4(1.0f) };

glm::mat4 Node :: top_stack() { return Node::matrix_stack.back(); }
void Node :: pop_stack() { Node::matrix_stack.pop_back(); }
void Node :: push_stack(glm::mat4 mat) { Node::matrix_stack.push_back(Node::top_stack()*mat); }

Node :: Node(int index) : index(index), center_of_rotation(0.0f), rotation(1.0f) {
    tx = ty = tz = 0;
    rotation_x = rotation_y = rotation_z = 0;
}

Node :: Node(int index, std::shared_ptr<Node> parent) : index(index), parent(parent), center_of_rotation(0.0f), rotation(1.0f) {
    tx = ty = tz = 0;
    rotation_x = rotation_y = rotation_z = 0;
}

Node :: Node(
    int index, float* vertices, unsigned int* indices, unsigned int vertex_count
    , unsigned int index_count, int stride, Shader& shader, std::shared_ptr<Node> parent
    ) : index(index), vertices(vertices), indices(indices), vertex_count(vertex_count)
        , index_count(index_count), stride(stride), shader(shader), parent(parent), rotation(1.0f)
{

    tx = ty = tz = 0;
    rotation_x = rotation_y = rotation_z = 0;
}

void Node :: init_buffers(){
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertex_count * stride, vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_count * sizeof(unsigned int), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*) 0);
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

glm::mat4 Node :: rotationMatrix() {
    return rotation;
}   

glm::mat4 Node :: modelMatrix() {

    return glm::translate(rotation, glm::vec3(tx, ty, tz));
}

void Node :: render() {
    glBindVertexArray(VAO);
    if (render_mode == 0){
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
    } else if (render_mode == 1){
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);
    } else if (render_mode == 2){
        glDrawElements(GL_TRIANGLES, base_index, GL_UNSIGNED_INT, (void*)0);
        glDrawElements(GL_LINES, (index_count-base_index)/2, GL_UNSIGNED_INT, (void*)(base_index * sizeof(GLuint)));
        glDrawElements(GL_LINES, (index_count-base_index)/2, GL_UNSIGNED_INT, (void*)(top_index * sizeof(GLuint)));
    }
}

void Node :: render_tree(int index, bool flag) {
    auto thisModel = modelMatrix();
    Node::push_stack(thisModel);
    auto totalModel = Node::top_stack();
    shader.setMat4("model", totalModel);
    auto color = (index == this->index && flag ? glm::vec3(1.0f, 0.0f, 0.0f) :  glm::vec3(1.0f, 0.32f, 0.62f));
    shader.setVec3("color", color);
    render();

    for (const auto& child : children){
        child->render_tree(index, flag);
    }

    Node::pop_stack();
}