#include "renderer.h"


Renderer :: Renderer() : aspect_ratio(16.0f/9), height(800)
        , width(static_cast<int>(height*aspect_ratio))
        , rotate_x(0.0f)
        , rotate_y(0.0f)
        , rotate_z(0.0f)
        , cam(glm::vec3(0.0f, -2.0f, 25.0f), glm::vec3(0.0f, 0.0f, -1.0f))
        , rotation(1.0f)
        , trackRotation(1.0f)
        , centroid(0.0f)
{
    
    // Initialize GLFW
    glfwInit();
    glfwInitHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwInitHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwInitHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW Window
    window = glfwCreateWindow(width, height, "OpenGL", nullptr, nullptr);
    if (window == nullptr){
        std::cerr<<"Failed to create GLFW window.\n";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)){
        std::cerr<<"Failed to initialize GLAD.\n";
        glfwTerminate();

    }

}

void Renderer :: initHuman() {

    h_sphereObjects.emplace_back(2.0f);
    Torso1 = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader);
    nodesHuman.push_back(Torso1);
    Torso1->init_buffers();
    // Torso1->set_translation_x(-10.0f);

    h_sphereObjects.emplace_back();
    UArmL = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, Torso1);
    Torso1->insert_child(UArmL);
    nodesHuman.push_back(UArmL);
    UArmL->init_buffers();
    UArmL->set_translation_x(3.0f);

    h_sphereObjects.emplace_back();
    LArmL = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, UArmL);
    UArmL->insert_child(LArmL);
    nodesHuman.push_back(LArmL);
    LArmL->init_buffers();
    LArmL->set_translation_y(-2.0f);
    LArmL->set_dof_y(false);
    LArmL->set_dof_z(false);

    h_sphereObjects.emplace_back();
    HandL = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, LArmL);
    LArmL->insert_child(HandL);
    nodesHuman.push_back(HandL);
    HandL->init_buffers();
    HandL->set_translation_y(-2.0f);

    h_sphereObjects.emplace_back();
    UArmR = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, Torso1);
    Torso1->insert_child(UArmR);
    nodesHuman.push_back(UArmR);
    UArmR->init_buffers();
    UArmR->set_translation_x(-3.0f);

    h_sphereObjects.emplace_back();
    LArmR = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, UArmR);
    UArmR->insert_child(LArmR);
    nodesHuman.push_back(LArmR);
    LArmR->init_buffers();
    LArmR->set_translation_y(-2.0f);
    LArmR->set_dof_y(false);
    LArmR->set_dof_z(false);

    h_sphereObjects.emplace_back();
    HandR = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, LArmR);
    LArmR->insert_child(HandR);
    nodesHuman.push_back(HandR);
    HandR->init_buffers();
    HandR->set_translation_y(-2.0f);

    h_sphereObjects.emplace_back(1.5f);
    Head = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, Torso1);
    Torso1->insert_child(Head);
    nodesHuman.push_back(Head);
    Head->init_buffers();
    Head->set_translation_y(3.5f);

    h_sphereObjects.emplace_back(1.5f);
    Torso3 = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, Torso1);
    Torso1->insert_child(Torso3);
    nodesHuman.push_back(Torso3);
    Torso3->init_buffers();
    Torso3->set_translation_y(-3.5f);

    h_sphereObjects.emplace_back();
    ThighL = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, Torso3);
    Torso3->insert_child(ThighL);
    nodesHuman.push_back(ThighL);
    ThighL->init_buffers();
    ThighL->set_translation_x(1.25f);
    ThighL->set_translation_y(-2.16f);

    h_sphereObjects.emplace_back();
    ThighR = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, Torso3);
    Torso3->insert_child(ThighR);
    nodesHuman.push_back(ThighR);
    ThighR->init_buffers();
    ThighR->set_translation_x(-1.25f);
    ThighR->set_translation_y(-2.16f);

    h_sphereObjects.emplace_back();
    LegL = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, ThighL);
    ThighL->insert_child(LegL);
    nodesHuman.push_back(LegL);
    LegL->init_buffers();
    LegL->set_translation_y(-2.0f);
    LegL->set_dof_y(false);
    LegL->set_dof_z(false);

    h_sphereObjects.emplace_back();
    LegR = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, ThighR);
    ThighR->insert_child(LegR);
    nodesHuman.push_back(LegR);
    LegR->init_buffers();
    LegR->set_translation_y(-2.0f);
    LegR->set_dof_y(false);
    LegR->set_dof_z(false);

    h_sphereObjects.emplace_back();
    FootL = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, LegL);
    LegL->insert_child(FootL);
    nodesHuman.push_back(FootL);
    FootL->init_buffers();
    FootL->set_translation_y(-2.0f);

    h_sphereObjects.emplace_back();
    FootR = std::make_shared<Node>((int)nodesHuman.size(), (float*)h_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)h_sphereObjects.back().getIndices(), h_sphereObjects.back().getInterleavedVertexCount()
                    , h_sphereObjects.back().getIndexCount(), h_sphereObjects.back().getInterleavedStride(), shader, LegR);
    LegR->insert_child(FootR);
    nodesHuman.push_back(FootR);
    FootR->init_buffers();
    FootR->set_translation_y(-2.0f);

    // humanPosition = glm::vec3(Torso1->get_translation_x(), Torso1->get_translation_y(), Torso1->get_translation_z());

}

void Renderer :: initBike() {
    // BIKE INITIALIZATION
    b_sphereObjects.emplace_back(1.6f); //main engine body
    Body = std::make_shared<Node>((int)nodesBike.size(), (float*)b_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_sphereObjects.back().getIndices(), b_sphereObjects.back().getInterleavedVertexCount()
                    , b_sphereObjects.back().getIndexCount(), b_sphereObjects.back().getInterleavedStride(), shader);
    nodesBike.push_back(Body);
    Body->init_buffers();
    // Body->set_translation_x(5.0f);

    b_sphereObjects.emplace_back(1.0f); //head-handle combo --- 1 dof
    Handle = std::make_shared<Node>((int)nodesBike.size(), (float*)b_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_sphereObjects.back().getIndices(), b_sphereObjects.back().getInterleavedVertexCount()
                    , b_sphereObjects.back().getIndexCount(), b_sphereObjects.back().getInterleavedStride(), shader, Body);
    Body->insert_child(Handle);
    nodesBike.push_back(Handle);
    Handle->init_buffers();
    Handle->set_translation_x(2.0f);
    Handle->set_translation_y(1.0f);
    Handle->set_dof_x(false);
    Handle->set_dof_z(false);

    b_cylinderObjects.emplace_back(0.2f, 0.2f, 4.0f);//this is for rod from handle to wheel  --> no-dof
    t1 = std::make_shared<Node>((int)nodesBike.size(), (float*)b_cylinderObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_cylinderObjects.back().getIndices(), b_cylinderObjects.back().getInterleavedVertexCount()
                    , b_cylinderObjects.back().getIndexCount(), b_cylinderObjects.back().getInterleavedStride(), shader, Handle);
    nodesBike.push_back(t1);
    Handle->insert_child(t1);
    t1->init_buffers();
    t1->set_translation_x(0.0f);
    t1->set_translation_y(0.0f);
    t1->set_translation_z(-2.0f);
    t1->set_rotation_x(-90.0f);
    t1->set_rotation_z(30.0f);
    t1->set_dof_x(false);
    t1->set_dof_y(false);
    t1->set_dof_z(false);



    b_sphereObjects.emplace_back(0.5f); //front wheel ball-bearing --> no-dof
    fwBearing = std::make_shared<Node>((int)nodesBike.size(), (float*)b_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_sphereObjects.back().getIndices(), b_sphereObjects.back().getInterleavedVertexCount()
                    , b_sphereObjects.back().getIndexCount(), b_sphereObjects.back().getInterleavedStride(), shader, t1);
    t1->insert_child(fwBearing);
    nodesBike.push_back(fwBearing);
    fwBearing->init_buffers();
    fwBearing->set_translation_x(0.0f);
    fwBearing->set_translation_y(2.0f);
    fwBearing->set_rotation_x(-90.f);
    fwBearing->set_dof_x(false);
    fwBearing->set_dof_y(false);
    fwBearing->set_dof_z(false);


    b_cylinderObjects.emplace_back(2.0f, 2.0f, 0.6f);//for the front wheel --> 1 rotational dof
    FWheel = std::make_shared<Node>((int)nodesBike.size(), (float*)b_cylinderObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_cylinderObjects.back().getIndices(), b_cylinderObjects.back().getInterleavedVertexCount()
                    , b_cylinderObjects.back().getIndexCount(), b_cylinderObjects.back().getInterleavedStride(), shader, fwBearing);
    nodesBike.push_back(FWheel);
    fwBearing->insert_child(FWheel);
    FWheel->init_buffers();
    FWheel->set_dof_x(false);
    FWheel->set_dof_y(false);
    FWheel->set_base_index(b_cylinderObjects.back().getBaseStartIndex());
    FWheel->set_top_index(b_cylinderObjects.back().getTopStartIndex());
    FWheel->set_render_mode(2);
    // FWheel->set_dof_z(false);

    b_cylinderObjects.emplace_back(0.6f, 0.6f, 4.0f);//for engine to rear wheel chain --> no dof
    t2 = std::make_shared<Node>((int)nodesBike.size(), (float*)b_cylinderObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_cylinderObjects.back().getIndices(), b_cylinderObjects.back().getInterleavedVertexCount()
                    , b_cylinderObjects.back().getIndexCount(), b_cylinderObjects.back().getInterleavedStride(), shader, Body);
    nodesBike.push_back(t2);
    Body->insert_child(t2);
    t2->init_buffers();
    t2->set_translation_x(0.6f);
    t2->set_translation_y(0.0f);
    t2->set_translation_z(-3.0f);
    t2->set_rotation_x(-90.0f);
    t2->set_rotation_z(-70.0f);
    t2->set_dof_x(false);
    t2->set_dof_y(false);
    t2->set_dof_z(false);



    b_sphereObjects.emplace_back(0.5f); //rear wheel ball-bearing --> no-dof
    rwBearing = std::make_shared<Node>((int)nodesBike.size(), (float*)b_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_sphereObjects.back().getIndices(), b_sphereObjects.back().getInterleavedVertexCount()
                    , b_sphereObjects.back().getIndexCount(), b_sphereObjects.back().getInterleavedStride(), shader, t2);
    t2->insert_child(rwBearing);
    nodesBike.push_back(rwBearing);
    rwBearing->init_buffers();
    rwBearing->set_translation_x(0.2f);
    rwBearing->set_translation_y(-2.2f);
    rwBearing->set_rotation_x(+90.f);
    rwBearing->set_dof_x(false);
    rwBearing->set_dof_y(false);
    rwBearing->set_dof_z(false);


    b_cylinderObjects.emplace_back(2.0f, 2.0f, 0.6f);//for the rear wheel --> 1 rotational dof
    RWheel = std::make_shared<Node>((int)nodesBike.size(), (float*)b_cylinderObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_cylinderObjects.back().getIndices(), b_cylinderObjects.back().getInterleavedVertexCount()
                    , b_cylinderObjects.back().getIndexCount(), b_cylinderObjects.back().getInterleavedStride(), shader, rwBearing);
    rwBearing->insert_child(RWheel);
    nodesBike.push_back(RWheel);
    RWheel->init_buffers();
    RWheel->set_dof_y(false);
    // RWheel->set_dof_z(false);
    RWheel->set_dof_x(false);
    RWheel->set_base_index(b_cylinderObjects.back().getBaseStartIndex());
    RWheel->set_top_index(b_cylinderObjects.back().getTopStartIndex());
    RWheel->set_render_mode(2);
    
    b_sphereObjects.emplace_back(1.3f); //seat1 --> no-dof
    seat1 = std::make_shared<Node>((int)nodesBike.size(), (float*)b_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_sphereObjects.back().getIndices(), b_sphereObjects.back().getInterleavedVertexCount()
                    , b_sphereObjects.back().getIndexCount(), b_sphereObjects.back().getInterleavedStride(), shader, Body);
    Body->insert_child(seat1);
    nodesBike.push_back(seat1);
    seat1->init_buffers();
    seat1->set_translation_x(-2.0f);
    seat1->set_translation_y(0.1f);
    seat1->set_dof_x(false);
    seat1->set_dof_y(false);
    seat1->set_dof_z(false);


    b_sphereObjects.emplace_back(0.7f); //seat2 --> no-dof
    seat2 = std::make_shared<Node>((int)nodesBike.size(), (float*)b_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_sphereObjects.back().getIndices(), b_sphereObjects.back().getInterleavedVertexCount()
                    , b_sphereObjects.back().getIndexCount(), b_sphereObjects.back().getInterleavedStride(), shader, seat1);
    seat1->insert_child(seat2);
    nodesBike.push_back(seat2);
    seat2->init_buffers();
    seat2->set_translation_x(-1.6f);
    seat2->set_translation_y(1.0f);
    seat2->set_dof_x(false);
    seat2->set_dof_y(false);
    seat2->set_dof_z(false);

    b_sphereObjects.emplace_back(0.7f); //seat3 --> no-dof
    seat3 = std::make_shared<Node>((int)nodesBike.size(), (float*)b_sphereObjects.back().getInterleavedVertices()
                    , (unsigned int*)b_sphereObjects.back().getIndices(), b_sphereObjects.back().getInterleavedVertexCount()
                    , b_sphereObjects.back().getIndexCount(), b_sphereObjects.back().getInterleavedStride(), shader, seat2);
    seat2->insert_child(seat3);
    nodesBike.push_back(seat3);
    seat3->init_buffers();
    seat3->set_translation_x(-1.3f);
    seat3->set_translation_y(0.0f);
    seat3->set_dof_x(false);
    seat3->set_dof_y(false);
    seat3->set_dof_z(false);

    // bikePosition = glm::vec3(Body->get_translation_x(), Body->get_translation_y(), Body->get_translation_z());

}


void Renderer :: render() {

    shader = Shader("./src/shader_source/shaderCube.vs", "./src/shader_source/shaderCube.fs");

    if (render_rider) {
        initHuman();
    }
    if (render_bike) {
        initBike();
    }
    if (render_track){
        initBuffersGL();
    }

    // enable Depth Testing
    glEnable(GL_DEPTH_TEST);
    

    // Render loop
    while (!glfwWindowShouldClose(window)){

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Updating current frame time
        float currTime = glfwGetTime();
        deltaTime = currTime - lastFrame;
        lastFrame = currTime;

        // perspective projection matrix
        glm::mat4 projection = glm::perspective(glm::radians(cam.fov), aspect_ratio, 1.0f, 300.0f);
        glm::mat4 view = cam.getViewMatrix();
        glm::mat4 model = glm::mat4(1.0f);

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        // glBindVertexArray(VAO);
        if (render_rider){
            getModelMatrix(model, 0);
            Node::push_stack(model);
            Torso1->render_tree(curr_obj_human, curr_model == 0);
            Node::pop_stack();
        } 
        if (render_bike){
            model = glm::mat4(1.0f);
            getModelMatrix(model, 1);
            Node::push_stack(model);
            Body->render_tree(curr_obj_bike, curr_model == 1);
            Node::pop_stack();
        }
        if (render_track){
            shaderTrack.use();
            shaderTrack.setMat4("view", view);
            shaderTrack.setMat4("projection", projection);
            model = glm::mat4(1.0f);
            // model = glm::scale(model, glm::vec3(5.0f, 5.0f, 5.0f));
            getModelMatrix(model, 2);
            shaderTrack.setMat4("model", model);
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, n_vert);
        }
 
        // Swaps front & back buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Renderer :: getModelMatrix(glm::mat4& modelMat, int model) {
    // modelMat = glm::mat4(1.0f);
    if (model == 0) {
        modelMat = glm::translate(modelMat, centroid);
        modelMat = rotation * modelMat;
        modelMat = glm::translate(modelMat, -centroid);
        modelMat = glm::translate(modelMat, humanPosition);
        modelMat = glm::scale(modelMat, glm::vec3(riderScale));

    }
    else if (model == 1) {
        modelMat = glm::translate(modelMat, centroid);
        modelMat = rotation * modelMat;
        modelMat = glm::translate(modelMat, -centroid);
        modelMat = glm::translate(modelMat, bikePosition);
        modelMat = glm::scale(modelMat, glm::vec3(bikeScale));

    } else if (model == 2){
        modelMat = glm::translate(modelMat, centroid);
        modelMat = rotation * modelMat;
        modelMat = glm::translate(modelMat, -centroid);
        modelMat = glm::translate(modelMat, trackPosition);
        modelMat = glm::scale(modelMat, glm::vec3(trackScale));
        modelMat = modelMat * trackRotation;
    }
}

void Renderer :: rotationHandler(enum ROTATION_DIRECTION move){
    float rotationSpeed = 200.0f*deltaTime;

    glm::mat4 rot = glm::mat4(1.0f);
    if (move == CCLOCK_Y){
        rotation = glm::rotate(rot, glm::radians(rotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f)) * rotation;
    } else if (move == CLOCK_Y){
        rotation = glm::rotate(rot, glm::radians(-rotationSpeed), glm::vec3(0.0f, 1.0f, 0.0f)) * rotation;
        // rotate_y -= rotationSpeed;
    } else if (move == CLOCK_X){
        rotation = glm::rotate(rot, glm::radians(-rotationSpeed), glm::vec3(1.0f, 0.0f, 0.0f)) * rotation;
        // rotate_x -= rotationSpeed;
    } else if (move == CCLOCK_X){
        rotation = glm::rotate(rot, glm::radians(rotationSpeed), glm::vec3(1.0f, 0.0f, 0.0f)) * rotation;
        // rotate_x += rotationSpeed;
    } else if (move == CCLOCK_Z){
        rotation = glm::rotate(rot, glm::radians(rotationSpeed), glm::vec3(0.0f, 0.0f, 1.0f)) * rotation;
        // rotate_z += rotationSpeed;
    } else {
        rotation = glm::rotate(rot, glm::radians(-rotationSpeed), glm::vec3(0.0f, 0.0f, 1.0f)) * rotation;
        // rotate_z -= rotationSpeed;
    }
}

void Renderer :: changeObject(int dir){
    if (curr_model == 0) curr_obj_human = (curr_obj_human+dir+(int)nodesHuman.size())%(int)nodesHuman.size();
    else if (curr_model == 1) curr_obj_bike = (curr_obj_bike+dir+(int)nodesBike.size())%(int)nodesBike.size();
}

void Renderer :: changeModel(int dir){
    curr_model = (curr_model + dir + 3)%3;
}

void Renderer :: objectRotationHandler(enum ROTATION_DIRECTION dir){
    float rot = 200.0f*deltaTime;

    if (dir == CLOCK_X){
        float curr_rot_x;
        if (curr_model == 0){
            nodesHuman[curr_obj_human]->set_rotation_x(rot);
        } else if (curr_model == 1){
            nodesBike[curr_obj_bike]->set_rotation_x(rot);
        } else {
            trackRotation = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(1.0f, 0.0f, 0.0f)) * trackRotation;
        }

    } else if (dir == CCLOCK_X){
        float curr_rot_x;
        if (curr_model == 0){
            nodesHuman[curr_obj_human]->set_rotation_x(-rot);
        } else if (curr_model == 1){
            nodesBike[curr_obj_bike]->set_rotation_x(-rot);
        } else {
            trackRotation = glm::rotate(glm::mat4(1.0f), glm::radians(-rot), glm::vec3(1.0f, 0.0f, 0.0f)) * trackRotation;
        }
    } else if (dir == CLOCK_Y){
        float curr_rot_y;
        if (curr_model == 0){
            nodesHuman[curr_obj_human]->set_rotation_y(rot);
        } else if (curr_model == 1){
            nodesBike[curr_obj_bike]->set_rotation_y(rot);
        } else {
            trackRotation = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0.0f, 1.0f, 0.0f)) * trackRotation;

        }
    } else if (dir == CCLOCK_Y){
        float curr_rot_y;
        if (curr_model == 0){
            nodesHuman[curr_obj_human]->set_rotation_y(-rot);
        } else if (curr_model == 1){
            nodesBike[curr_obj_bike]->set_rotation_y(-rot);
        } else {
            trackRotation = glm::rotate(glm::mat4(1.0f), glm::radians(-rot), glm::vec3(0.0f, 1.0f, 0.0f)) * trackRotation;

        }
    } else if (dir == CLOCK_Z){
        float curr_rot_z;
        if (curr_model == 0){
            nodesHuman[curr_obj_human]->set_rotation_z(-rot);
        } else if (curr_model == 1){
            nodesBike[curr_obj_bike]->set_rotation_z(rot);
        } else {
            trackRotation = glm::rotate(glm::mat4(1.0f), glm::radians(-rot), glm::vec3(0.0f, 0.0f, 1.0f)) * trackRotation;
        }
    } else if (dir == CCLOCK_Z){
        float curr_rot_z;
        if (curr_model == 0){
            nodesHuman[curr_obj_human]->set_rotation_z(rot);
        } else if (curr_model == 1){
            nodesBike[curr_obj_bike]->set_rotation_z(-rot);
        } else {
            trackRotation = glm::rotate(glm::mat4(1.0f), glm::radians(rot), glm::vec3(0.0f, 0.0f, 1.0f)) * trackRotation;
        }
    }
}

void Renderer :: modelTranslationHandler(enum TRANSLATION_DIRECTION dir){
    float dis = speed * deltaTime;

    if (dir == POS_X){
        if (curr_model == 0) humanPosition.x += dis;
        else if (curr_model == 1) bikePosition.x += dis;
        else if (curr_model == 2) trackPosition.x += dis;
    } else if (dir == NEG_X){
        if (curr_model == 0) humanPosition.x -= dis;
        else if (curr_model == 1) bikePosition.x -= dis;
        else if (curr_model == 2) trackPosition.x -= dis;

    } else if (dir == POS_Y){
        if (curr_model == 0) humanPosition.y += dis;
        else if (curr_model == 1) bikePosition.y += dis;
        else if (curr_model == 2) trackPosition.y += dis;

    } else if (dir == NEG_Y){
        if (curr_model == 0) humanPosition.y -= dis;
        else if (curr_model == 1) bikePosition.y -= dis;
        else if (curr_model == 2) trackPosition.y -= dis;

    } else if (dir == POS_Z){
        if (curr_model == 0) humanPosition.z += dis;
        else if (curr_model == 1) bikePosition.z += dis;
        else if (curr_model == 2) trackPosition.z += dis;

    } else if (dir == NEG_Z){
        if (curr_model == 0) humanPosition.z -= dis;
        else if (curr_model == 1) bikePosition.z -= dis;
        else if (curr_model == 2) trackPosition.z += dis;
    }

}


void Renderer :: quad1(int a, int b, int c, int d)
{
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_track[a]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_track[b]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_track[c]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_track[a]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_track[c]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_track[d]; tri_idx++;
 }


void Renderer :: quad2(int a, int b, int c, int d)
{
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_ground[a]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_ground[b]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_ground[c]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_ground[a]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_ground[c]; tri_idx++;
  v_colors[tri_idx] = track_color; v_positions[tri_idx] = positions_ground[d]; tri_idx++;
 } 


void Renderer :: ground(){
  track_color = glm::vec4(0.5,0.4,0.1,1.0);//yellow color
  quad2(0,1,2,3);
}

void Renderer :: track(){
  track_color = glm::vec4(0.5,0.5,0.5,1.0);//gray color
  quad1(0, 1, 3, 2);
  quad1(2, 3, 5, 4);
  quad1(4,5,7,6);
  quad1(6,8,9,10);
  quad1(9,10,11,12);

  quad1(11,12,13,14);//<--6
  quad1(15,16,17,13);//<--7

  quad1(16,17,19,18);//<--8
  quad1(18,19,21,20);//<--9
  quad1(20,21,23,22);//<--10
  quad1(24,22,23,25);//<--11
  quad1(25,26,27,28);//<--12
  
  
  
  quad1(29,28,30,31);//<--13
  quad1(30,31,33,32);//<--14
  quad1(32,33,35,34);//<--15
  
  quad1(34,35,37,36);//<--16
  quad1(36,37,39,38);//<--17
  quad1(39,40,41,43);//<--18

  quad1(42,43,45,44);//<--19
  quad1(44,45,47,46);//<--20
  quad1(46,47,49,48);//<--21
  quad1(48,49,51,50);//<--22
  quad1(50,51,53,52);//<--23
  quad1(52,53,55,54);//<--24
  quad1(54,55,57,56);//<--25
  
  quad1(56,57,58,59);//<--26
  quad1(59,58,61,62);//<--27
  quad1(61,62,64,63);//<--28
  quad1(63,64,0,1);//<--29

}

void Renderer :: initBuffersGL(void)
{
  //colorcube();
  //colorprism();
    shaderTrack = Shader("./src/shader_source/vshader.glsl", "./src/shader_source/fshader.glsl");
//   glUseProgram( shaderProgram );
    shaderTrack.use();
    ground();
    track();

    //Ask GL for a Vertex Attribute Object (vao)
    glGenVertexArrays (1, &vao);
    //Set it as the current array to be used by binding it
    glBindVertexArray (vao);

    //Ask GL for a Vertex Buffer Object (vbo)
    glGenBuffers (1, &vbo);
    //Set it as the current buffer to be used by binding it
    glBindBuffer (GL_ARRAY_BUFFER, vbo);
    //Copy the points into the current buffer
    glBufferData (GL_ARRAY_BUFFER, sizeof (v_positions) + sizeof(v_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(v_positions), v_positions );
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(v_positions), sizeof(v_colors), v_colors );
    
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 4, GL_FLOAT, GL_FALSE, 0, (void*)0 );
    
    //   GLuint vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
    glEnableVertexAttribArray( 1 );
    glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, 0, (void*)(sizeof(v_positions)) );

    //   uModelViewProjectMatrix = glGetUniformLocation( shaderProgram, "uModelViewProjectMatrix");
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}