#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include "ShaderProgram.h"
#include "Texture2D.h"
#include "Camera.h"
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

    ShaderProgram boxShader("shader/box"), lightShader("shader/light");

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

    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(NULL));
    glEnableVertexAttribArray(0);

    Texture2D texture1("img/cai.jpg");
    Texture2D texture2("img/container2.png", 1);
    boxShader.use();
    boxShader.setValue("utex1", texture1.getIndex());
    boxShader.setValue("utex2", texture2.getIndex());
    boxShader.setValue("lightPos", glm::vec3(1.2f, 1.0f, 2.0f));
    boxShader.setValue("material.ambient", glm::vec3(1.0f, 0.5f, 0.31f));
    boxShader.setValue("material.diffuse", glm::vec3(1.0f, 0.5f, 0.31f));
    boxShader.setValue("material.specular", glm::vec3(0.5f, 0.5f, 0.5f));
    boxShader.setValue("material.shininess", 32.0f);

    lightShader.use();
    lightShader.setValue("utex1", texture1.getIndex());
    lightShader.setValue("utex2", texture2.getIndex());
    glm::mat4 tmp;
    tmp = glm::translate(tmp, glm::vec3(1.2f, 1.0f, 2.0f));
    tmp = glm::scale(tmp, glm::vec3(0.2f));
    lightShader.setValue("model", tmp);

    glm::vec3 cubes[] = {
        glm::vec3(0.0f, 0.0f, -1.0f),
        glm::vec3(1.0f, 0.0f, -1.0f),
        glm::vec3(1.0f, 1.0f, -1.0f),
        glm::vec3(0.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, 1.0f, -1.0f),
        glm::vec3(-1.0f, -1.0f, -1.0f),
        glm::vec3(1.0f, -1.0f, -1.0f),
        glm::vec3(-1.0f, 0.0f, -1.0f),
        glm::vec3(0.0f, -1.0f, -1.0f),
    };

    const float radius = 10.0f;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glm::mat4 projection = glm::perspective(glm::radians(fov), static_cast<float>(screenWidth) / screenHeight, 0.1f, 100.0f);
        lightShader.use();
        lightShader.setValue("projection", projection);
        camera.useIn(lightShader);
        // float delta = sin(glfwGetTime()) / 2.0 + 0.5;
        // glm::vec3 lightClr(delta * 0.6f, delta * 0.8f, delta);
        glm::vec3 lightClr(
            sin(glfwGetTime() * 2.0f),
            sin(glfwGetTime() * 0.7f),
            sin(glfwGetTime() * 1.3f)
        );
        lightShader.setValue("clr", lightClr);
        glBindVertexArray(lightVAO);
        // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        boxShader.use();
        boxShader.setValue("projection", projection);
        // float camX = sin(glfwGetTime()) * radius, camZ = cos(glfwGetTime()) * radius;
        // camera.setPos(glm::vec3(camX, 0.0f, camZ));
        camera.useIn(boxShader);
        boxShader.setValue("viewPos", camera.getPos());
        boxShader.setValue("light.ambient", lightClr * 0.2f);
        boxShader.setValue("light.diffuse", lightClr * 0.5f);
        boxShader.setValue("light.specular", lightClr * 1.0f);

        texture1.use();
        texture2.use();
        glBindVertexArray(VAO);
        for (auto &i : cubes) {
            glm::mat4 model;
            model = glm::translate(model, i);
            // model = glm::rotate(model, static_cast<float>(glfwGetTime()), glm::vec3(0.5f, 1.0f, 0.1f));
            boxShader.setValue("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
            // glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        }

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
    glClearColor(0.2f, 0.4f, 0.6f, 0.2f);

    int nrAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    cout << "Maximum nr: " << nrAttributes << endl;

    glViewport(0, 0, screenWidth, screenHeight);
    glEnable(GL_DEPTH_TEST);
    mainloop(window);

    glfwTerminate();
    return 0;
}
