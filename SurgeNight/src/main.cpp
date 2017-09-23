#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "SNCGraphics/ShaderProgram.h"
#include "SNCGraphics/Model.h"
#include "SNCGraphics/Camera.h"
#include "SNCGraphics/Lighting/Light.h"
#include <iostream>

using namespace std;
using namespace SurgeNight;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float screenWidth = 1366.0f, screenHeight = 768.0f, fov = 45.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.move(0.0f, 0.0f, 0.05f);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.move(0.0f, 0.0f, -0.05f);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.move(-0.05f, 0.0f, 0.0f);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.move(0.05f, 0.0f, 0.0f);
}

float lastMousePos[] = { 683.0f, 384.0f };
float offsetMouse[] = { 0.0f, 0.0f };
float pitch = 0.0f, yaw = -90.0f, roll = 0.0f, sensity = 0.05f;

void processMouse(GLFWwindow *window, double x, double y)
{
    static bool first = true;
    if (first) {
        lastMousePos[0] = x;
        lastMousePos[1] = y;
        first = false;
    }
    offsetMouse[0] = x - lastMousePos[0];
    offsetMouse[1] = lastMousePos[1] - y;
    lastMousePos[0] = x;
    lastMousePos[1] = y;
    offsetMouse[0] *= sensity;
    offsetMouse[1] *= sensity;
    yaw += offsetMouse[0];
    pitch += offsetMouse[1];
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;
    float fx = cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
          fy = sin(glm::radians(pitch)),
          fz = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    camera.lookTo(glm::vec3(fx, fy, fz));
}

void processScroll(GLFWwindow *window, double offx, double offy)
{
    window = window;offx = offx;
    if (fov >= 1.0f && fov <= 45.0f)
        fov -= offy;
    if (fov <= 1.0f)
        fov = 1.0f;
    if (fov >= 45.0f)
        fov = 45.0f;
}

void mainloop(GLFWwindow *window)
{
    unsigned int VBO, VAO, EBO;
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,   0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,   0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,   0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,  -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,  -1.0f,  0.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   1.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,   0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,   0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,   0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,   0.0f,  1.0f,  0.0f
    };
    unsigned int cors[] = {
        0, 1, 2,
        1, 2, 3,
        4, 5 ,6,
        5, 6, 7,
        0, 1, 4,
        1, 4, 5,
        0, 2, 4,
        2, 4, 6,
        1, 3, 5,
        3, 5, 7,
        2, 3, 6,
        3, 6, 7
    };

    ShaderProgram boxShader("shader/box"), nanoShader("shader/nanosuit");
    SurgeNight::Model nanoModel("model/nanosuit/nanosuit.obj");
    Light light;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(cors), cors, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(NULL));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
    glEnableVertexAttribArray(2);

    light.setAttenuation(1.0f, 0.022f, 0.0019f);
    light.setEnvironment(0.2f, 0.8f);
    light.setPosition(glm::vec3(1.2f, 0.5f, 3.0f));
    // light.setDirection(glm::vec3(-1.2f, -0.5f, -3.0f));

    Texture2D texture1("img/container2_specular.png");
    Texture2D texture2("img/container2.png", 1);
    boxShader.use();
    boxShader.setValue("utex1", texture1.getIndex());
    boxShader.setValue("utex2", texture2.getIndex());
    boxShader.setValue("material.ambient", 1);
    boxShader.setValue("material.diffuse", 1);
    boxShader.setValue("material.specular", 0);
    boxShader.setValue("material.shininess", 32.0f);

    glm::vec3 cubes[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    const float radius = 10.0f;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(screenWidth) / screenHeight, 0.1f, 100.0f);
        // float delta = sin(glfwGetTime()) / 2.0 + 0.5;
        // glm::vec3 lightClr(delta * 0.6f, delta * 0.8f, delta);
        glm::vec3 lightClr(
            1.0f);
        //     sin(glfwGetTime() * 2.0f),
        //     sin(glfwGetTime() * 0.7f),
        //     sin(glfwGetTime() * 1.3f)
        // );
        light.setColor(lightClr);

        boxShader.use();
        boxShader.setValue("projection", projection);
        camera.useIn(boxShader);
        boxShader.setValue("light.direction", camera.getTarget());
        boxShader.setValue("light.position", camera.getPos());
        boxShader.setValue("light.cutOff", cos(glm::radians(12.5f)));
        boxShader.setValue("light.outerCutOff", cos(glm::radians(17.5f)));
        light.useIn(boxShader);

        texture1.use();
        texture2.use();
        glBindVertexArray(VAO);
        unsigned int index = 0;
        for (auto &i : cubes) {
            glm::mat4 model;
            model = glm::translate(model, i);
            float angle = 20.0f * index;
            // model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(0.5f, 1.0f, 0.1f));
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            boxShader.setValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            ++index;
        }
        nanoShader.use();
        glm::mat4 model;
        model = glm::translate(model, glm::vec3(2.0f, -1.75f, 0.0f));
        model = glm::scale(model, glm::vec3(0.2f));
        nanoShader.setValue("projection", projection);
        nanoShader.setValue("model", model);
        camera.useIn(nanoShader);
        nanoShader.setValue("light.direction", camera.getTarget());
        nanoShader.setValue("light.position", camera.getPos());
        nanoShader.setValue("light.cutOff", cos(glm::radians(20.0f)));
        nanoShader.setValue("light.outerCutOff", cos(glm::radians(40.0f)));
        light.useIn(nanoShader);
        nanoModel.paint(nanoShader);
        // nanoModel.m_meshes[1].paint();


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

int main()
{
    ios::sync_with_stdio(false);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow *window = glfwCreateWindow(screenWidth, screenHeight, "GL Study E", NULL, NULL);
    if (NULL == window) {
        cerr << "Failed to create GLFW window." << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, processMouse);
    glfwSetScrollCallback(window, processScroll);
    glClearColor(0.05f, 0.1f, 0.15f, 0.2f);

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    mainloop(window);

    glfwTerminate();
    return 0;
}
