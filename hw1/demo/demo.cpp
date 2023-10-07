#include <stdio.h>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <chrono>
#include <cmath>
#include<vector>
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


const GLint WIDTH = 800, HEIGHT = 600;

float r = 0.5f;

// Hexagon points
std::vector<float> points = {
    0.0f, r, 0.0f,                                       // point_1
    r * (float)std::cos(M_PI / 6), r * (float)std::sin(M_PI / 6), 0.0f, // point_2
    r * (float)std::cos(M_PI / 6), -r * (float)std::sin(M_PI / 6), 0.0f, // point_3
    0.0f, -r, 0.0f,                                      // point_4
    -r * (float)std::cos(M_PI / 6), -r * (float)std::sin(M_PI / 6), 0.0f, // point_5
    -r * (float)std::cos(M_PI / 6), r * (float)std::sin(M_PI / 6), 0.0f, // point_6
     r * 3.0f / 5.0f * (float)std::cos(6.0f / 5.0f * M_PI), r * 3.0f / 5.0f * (float)std::sin(6.0f / 5.0f * M_PI), 0.0f, // tr_1
    r * 2.0f / 3.0f * (float)std::cos(1.0f / 5.0f * M_PI), r * 2.0f / 3.0f * (float)std::sin(1.0f / 5.0f * M_PI), 0.0f, // tr_2
    r * 4.0f / 7.0f * (float)std::cos(-2.0f / 7.0f * M_PI), r * 4.0f / 7.0f * (float)std::sin(-2.0f / 7.0f * M_PI), 0.0f  // tr_3
};

// New points
std::vector<float> tr_points = {
    r * 3.0f / 5.0f * (float)std::cos(6.0f / 5.0f * M_PI), r * 3.0f / 5.0f * (float)std::sin(6.0f / 5.0f * M_PI), 0.0f, // tr_1
    r * 2.0f / 3.0f * (float)std::cos(1.0f / 5.0f * M_PI), r * 2.0f / 3.0f * (float)std::sin(1.0f / 5.0f * M_PI), 0.0f, // tr_2
    r * 4.0f / 7.0f * (float)std::cos(-2.0f / 7.0f * M_PI), r * 4.0f / 7.0f * (float)std::sin(-2.0f / 7.0f * M_PI), 0.0f  // tr_3
};

std::vector<float> triangles = {
    // Triangle 1
    tr_points[0], tr_points[1], tr_points[2], // tr_1
    points[0], points[1], points[2],          // point_1
    points[15], points[16], points[17],       // point_6

    // Triangle 2
    points[0], points[1], points[2],          // point_1
    tr_points[0], tr_points[1], tr_points[2], // tr_1
    tr_points[3], tr_points[4], tr_points[5], // tr_2

    // Triangle 3
    points[0], points[1], points[2],          // point_1
    tr_points[3], tr_points[4], tr_points[5], // tr_2
    points[3], points[4], points[5],          // point_2

    // Triangle 4
    points[12], points[13], points[14],       // point_5
    points[15], points[16], points[17],       // point_6
    tr_points[0], tr_points[1], tr_points[2], // tr_1

    // Triangle 5
    tr_points[0], tr_points[1], tr_points[2], // tr_1
    tr_points[3], tr_points[4], tr_points[5], // tr_2
    tr_points[6], tr_points[7], tr_points[8], // tr_3

    // Triangle 6
    tr_points[3], tr_points[4], tr_points[5], // tr_2
    tr_points[6], tr_points[7], tr_points[8], // tr_3
    points[6], points[7], points[8],          // point_3

    // Triangle 7
    tr_points[3], tr_points[4], tr_points[5], // tr_2
    points[3], points[4], points[5],          // point_2
    points[6], points[7], points[8],          // point_3

    // Triangle 8
    points[9], points[10], points[11],        // point_4
    points[12], points[13], points[14],       // point_5
    tr_points[0], tr_points[1], tr_points[2], // tr_1

    // Triangle 9
    points[9], points[10], points[11],        // point_4
    tr_points[0], tr_points[1], tr_points[2], // tr_1
    tr_points[6], tr_points[7], tr_points[8], // tr_3

    // Triangle 10
    points[9], points[10], points[11],        // point_4
    tr_points[6], tr_points[7], tr_points[8], // tr_3
    points[6], points[7], points[8]           // point_3
};


std::vector<float> colors = {
    // Triangle 1
    247.0f / 255.0f, 149.0f / 255.0f, 209.0f / 255.0f,
    247.0f / 255.0f, 149.0f / 255.0f, 209.0f / 255.0f,
    247.0f / 255.0f, 149.0f / 255.0f, 209.0f / 255.0f,

    // Triangle 2
    196.0f / 255.0f, 52.0f / 255.0f, 137.0f / 255.0f,
    196.0f / 255.0f, 52.0f / 255.0f, 137.0f / 255.0f,
    196.0f / 255.0f, 52.0f / 255.0f, 137.0f / 255.0f,

    // Triangle 3
    140.0f / 255.0f, 13.0f / 255.0f, 78.0f / 255.0f,
    140.0f / 255.0f, 13.0f / 255.0f, 78.0f / 255.0f,
    140.0f / 255.0f, 13.0f / 255.0f, 78.0f / 255.0f,

    //Triangle 4
    225.0f / 255.0f, 109.0f / 255.0f, 178.0f / 255.0f,
    225.0f / 255.0f, 109.0f / 255.0f, 178.0f / 255.0f,
    225.0f / 255.0f, 109.0f / 255.0f, 178.0f / 255.0f,

    //Triangle 5
    140.0f / 255.0f, 11.0f / 255.0f, 77.0f / 255.0f,
    140.0f / 255.0f, 11.0f / 255.0f, 77.0f / 255.0f,
    140.0f / 255.0f, 11.0f / 255.0f, 77.0f / 255.0f,

    //Triangle 6
    156.0f / 255.0f, 27.0f / 255.0f, 94.0f / 255.0f,
    156.0f / 255.0f, 27.0f / 255.0f, 94.0f / 255.0f,
    156.0f / 255.0f, 27.0f / 255.0f, 94.0f / 255.0f,

    //Triangle 7
    103.0f / 255.0f, 6.0f / 255.0f, 48.0f / 255.0f,
    103.0f / 255.0f, 6.0f / 255.0f, 48.0f / 255.0f,
    103.0f / 255.0f, 6.0f / 255.0f, 48.0f / 255.0f,

    //Triangle 8
    179.0f / 255.0f, 0.0f / 255.0f, 89.0f / 255.0f,
    179.0f / 255.0f, 0.0f / 255.0f, 89.0f / 255.0f,
    179.0f / 255.0f, 0.0f / 255.0f, 89.0f / 255.0f,

    //Triangle 9
    102.0f / 255.0f, 4.0f / 255.0f, 49.0f / 255.0f,
    102.0f / 255.0f, 4.0f / 255.0f, 49.0f / 255.0f,
    102.0f / 255.0f, 4.0f / 255.0f, 49.0f / 255.0f,

    // Triangle 10
    189.0f / 255.0f, 59.0f / 255.0f, 119.0f / 255.0f,
    189.0f / 255.0f, 59.0f / 255.0f, 119.0f / 255.0f,
    189.0f / 255.0f, 59.0f / 255.0f, 119.0f / 255.0f,
};

std::vector<float> edges = {
    // Edges for Triangle 1
    tr_points[0], tr_points[1], tr_points[2], points[0], points[1], points[2],
    points[0], points[1], points[2], points[15], points[16], points[17],
    tr_points[0], tr_points[1], tr_points[2], points[15], points[16], points[17],

    // Edges for Triangle 2
    points[0], points[1], points[2], tr_points[0], tr_points[1], tr_points[2],
    tr_points[0], tr_points[1], tr_points[2], tr_points[3], tr_points[4], tr_points[5],
    points[0], points[1], points[2], tr_points[3], tr_points[4], tr_points[5],

    // Edges for Triangle 3
    points[0], points[1], points[2], tr_points[3], tr_points[4], tr_points[5],
    tr_points[3], tr_points[4], tr_points[5], points[3], points[4], points[5],
    points[0], points[1], points[2], points[3], points[4], points[5],

    // Edges for Triangle 4
    points[12], points[13], points[14], points[15], points[16], points[17],
    points[15], points[16], points[17], tr_points[0], tr_points[1], tr_points[2],
    points[12], points[13], points[14], tr_points[0], tr_points[1], tr_points[2],

    // Edges for Triangle 5
    tr_points[0], tr_points[1], tr_points[2], tr_points[3], tr_points[4], tr_points[5],
    tr_points[3], tr_points[4], tr_points[5], tr_points[6], tr_points[7], tr_points[8],
    tr_points[0], tr_points[1], tr_points[2], tr_points[6], tr_points[7], tr_points[8],

    // Edges for Triangle 6
    tr_points[3], tr_points[4], tr_points[5], tr_points[6], tr_points[7], tr_points[8],
    tr_points[6], tr_points[7], tr_points[8], points[6], points[7], points[8],
    tr_points[3], tr_points[4], tr_points[5], points[6], points[7], points[8],

    // Edges for Triangle 7
    tr_points[3], tr_points[4], tr_points[5], points[3], points[4], points[5],
    points[3], points[4], points[5], points[6], points[7], points[8],
    tr_points[3], tr_points[4], tr_points[5], points[6], points[7], points[8],

    // Edges for Triangle 8
    points[9], points[10], points[11], points[12], points[13], points[14],
    points[12], points[13], points[14], tr_points[0], tr_points[1], tr_points[2],
    points[9], points[10], points[11], tr_points[0], tr_points[1], tr_points[2],

    // Edges for Triangle 9
    points[9], points[10], points[11], tr_points[0], tr_points[1], tr_points[2],
    tr_points[0], tr_points[1], tr_points[2], tr_points[6], tr_points[7], tr_points[8],
    points[9], points[10], points[11], tr_points[6], tr_points[7], tr_points[8],

    // Edges for Triangle 10
    points[9], points[10], points[11], tr_points[6], tr_points[7], tr_points[8],
    tr_points[6], tr_points[7], tr_points[8], points[6], points[7], points[8],
    points[9], points[10], points[11], points[6], points[7], points[8]
};





// Vertex Shader Source
const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 ourColor;

    void main() {
        gl_Position = vec4(aPos, 1.0);
        ourColor = aColor;
    }
)";

// Fragment Shader Source
const char* fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;

    in vec3 ourColor;

    void main() {
        FragColor = vec4(ourColor, 1.0f);
    }
)";

bool isTransitioning = false;

bool showEdges = false;
unsigned int edgeCBO;
float globalTime = 0.0f;
std::vector<float> edge_colors;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_C && action == GLFW_PRESS) {
        isTransitioning = true;
    }
    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        showEdges = !showEdges; // Toggle between showing and not showing edges
    }
}

std::vector<float> generateCircleColors(int num_circles, int num_segments) {
    std::vector<float> circle_colors;
    for (int i = 0; i < num_circles; ++i) {
        for (int j = 0; j < num_segments * 3; ++j) {
            circle_colors.push_back(1.0f); // R
            circle_colors.push_back(1.0f); // G
            circle_colors.push_back(1.0f); // B
        }
    }
    return circle_colors;
}
std::vector<float> goldColor = { 1.0f, 0.8431f, 0.0f }; // RGB for gold
std::vector<float> whiteColor = { 1.0f, 1.0f, 1.0f }; // RGB for white

void updateEdgeColors() {
    for (size_t i = 0; i < edge_colors.size(); i += 3) {
        float intensity = (std::sin(globalTime + float(i) * 0.1f) + 1.0f) * 0.5f;

        edge_colors[i] = goldColor[0] * (1.0f - intensity) + whiteColor[0] * intensity; // R
        edge_colors[i + 1] = goldColor[1] * (1.0f - intensity) + whiteColor[1] * intensity; // G
        edge_colors[i + 2] = goldColor[2] * (1.0f - intensity) + whiteColor[2] * intensity; // B
    }

    glBindBuffer(GL_ARRAY_BUFFER, edgeCBO);
    glBufferData(GL_ARRAY_BUFFER, edge_colors.size() * sizeof(float), &edge_colors[0], GL_STATIC_DRAW);
}



std::vector<float> generateCircleVertices(float cx, float cy, float cz, float r, int num_segments) {
    std::vector<float> circle_vertices;
    for (int i = 0; i < num_segments; i++) {
        float theta = 2.0f * M_PI * float(i) / float(num_segments);
        float x = r * cosf(theta);
        float y = r * sinf(theta);

        // Push center vertex for triangle fan
        circle_vertices.push_back(cx);
        circle_vertices.push_back(cy);
        circle_vertices.push_back(cz);

        // Push current vertex
        circle_vertices.push_back(x + cx);
        circle_vertices.push_back(y + cy);
        circle_vertices.push_back(cz); // z-coordinate

        // Compute and push next vertex
        theta = 2.0f * M_PI * float(i + 1) / float(num_segments);
        x = r * cosf(theta);
        y = r * sinf(theta);
        circle_vertices.push_back(x + cx);
        circle_vertices.push_back(y + cy);
        circle_vertices.push_back(cz); // z-coordinate
    }
    return circle_vertices;
}


unsigned int edgeVBO, edgeVAO;


int main() {
    float initialRadii[9] = { 0.05f, 0.045f, 0.05f, 0.04f, 0.045f, 0.05f, 0.042f, 0.046f, 0.05f };  // 为每个点设置初始半径
    float radii[9];
    for (int i = 0; i < 9; i++) {
        radii[i] = initialRadii[i];  // 初始化半径数组
    }
    float time = 0;



    
    for (size_t i = 0; i < edges.size() / 3; ++i) {
        edge_colors.push_back(1.0f); // R
        edge_colors.push_back(1.0f); // G
        edge_colors.push_back(1.0f); // B
    }


    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    unsigned int edgeVBO, edgeVAO, pointVBO, pointVAO;
    float edgeThickness = 1.0f;
    float pointRadius = 1.0f;
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Triangles", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Vertex Shader
    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Fragment Shader
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Shader Program
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);

    // Delete shaders as they're linked into our program now and no longer necessary
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    unsigned int VBO, VAO, CBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &CBO);

    glBindVertexArray(VAO);

    // Load triangles
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, triangles.size() * sizeof(float), &triangles[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Load colors
    glBindBuffer(GL_ARRAY_BUFFER, CBO);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    
    glGenBuffers(1, &edgeCBO);

    // Load edge colors
    glBindBuffer(GL_ARRAY_BUFFER, edgeCBO);
    glBufferData(GL_ARRAY_BUFFER, edge_colors.size() * sizeof(float), &edge_colors[0], GL_STATIC_DRAW);


    glGenVertexArrays(1, &edgeVAO);
    glGenBuffers(1, &edgeVBO);

    glBindVertexArray(edgeVAO);


    // Load edge vertices
    glBindBuffer(GL_ARRAY_BUFFER, edgeVBO);
    glBufferData(GL_ARRAY_BUFFER, edges.size() * sizeof(float), &edges[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Load edge colors
    glBindBuffer(GL_ARRAY_BUFFER, edgeCBO);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    std::vector<float> circleVertices;
    std::vector<float> circleColors;
    int num_segments = 36; // You can adjust the number of segments as needed

    for (size_t i = 0; i < points.size(); i += 3) {
        float cx = points[i];
        float cy = points[i + 1];
        float cz = points[i + 2];
        float radius = 0.05f; // You can adjust the radius as needed
        std::vector<float> vertices = generateCircleVertices(cx, cy, cz, radius, num_segments);
        circleVertices.insert(circleVertices.end(), vertices.begin(), vertices.end());

        for (int j = 0; j < num_segments; j++) {
            circleColors.push_back(1.0f); // R
            circleColors.push_back(1.0f); // G
            circleColors.push_back(1.0f); // B
        }
    }


    unsigned int circleVBO, circleVAO, circleCBO;
    glGenVertexArrays(1, &circleVAO);
    glGenBuffers(1, &circleVBO);
    glGenBuffers(1, &circleCBO);

    // Bind and set up the circle VBO and VAO
    glBindVertexArray(circleVAO);

    // Load circle vertices
    glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
    glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), &circleVertices[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Load circle colors
    std::vector<float> circle_colors = generateCircleColors(points.size() / 3, num_segments);
    glBindBuffer(GL_ARRAY_BUFFER, circleCBO);
    glBufferData(GL_ARRAY_BUFFER, circle_colors.size() * sizeof(float), &circle_colors[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);




    float blueThreshold = 0.95f; // 例如，当蓝色分量达到0.95时停止渐变

    float lineWidth = 1.0f;
    float pointSize = 1.0f;
    bool increasing = true;
    

    while (!glfwWindowShouldClose(window)) {
        globalTime += 0.01f;
        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);  // 设置背景颜色为淡灰色
        glClear(GL_COLOR_BUFFER_BIT);
        if (isTransitioning) {
            bool allBlueEnough = true;

            for (size_t i = 0; i < colors.size(); i += 3) {
                colors[i] *= 0.9999f; // 减少红色
                colors[i + 1] *= 0.9999f; // 减少绿色
                colors[i + 2] = std::min(colors[i + 2] + 0.0002f, 1.0f); // 增加蓝色

                if (colors[i + 2] < blueThreshold) {
                    allBlueEnough = false;
                }
            }

            // 重新绑定颜色数据
            glBindBuffer(GL_ARRAY_BUFFER, CBO);
            glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(float), &colors[0], GL_STATIC_DRAW);

            if (allBlueEnough) {
                isTransitioning = false;
            }
        }

        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, triangles.size() / 3);

        if (showEdges) {
            updateEdgeColors();
            time += 0.02f;  // 更新时间
            for (int i = 0; i < 9; i++) {
                radii[i] = initialRadii[i] * std::max(0.0f, std::sin(time - i * 0.3f));  // 使用正弦函数更新半径，您可以按需更改此函数
                // 确保半径不为负
            }

            // 根据新的半径更新圆形顶点
            circleVertices.clear();  // 清除旧的顶点
            for (size_t i = 0; i < points.size(); i += 3) {
                float cx = points[i];
                float cy = points[i + 1];
                float cz = points[i + 2];
                std::vector<float> newCircleVertices = generateCircleVertices(cx, cy, cz, radii[i / 3], num_segments);
                circleVertices.insert(circleVertices.end(), newCircleVertices.begin(), newCircleVertices.end());  // 添加新的顶点
            }


            // 重新绑定更新后的circleVertices
            glBindBuffer(GL_ARRAY_BUFFER, circleVBO);
            glBufferData(GL_ARRAY_BUFFER, circleVertices.size() * sizeof(float), &circleVertices[0], GL_STATIC_DRAW);
            glBindVertexArray(edgeVAO);
            glDrawArrays(GL_LINES, 0, edges.size() / 3);
            glBindVertexArray(circleVAO);
            glDrawArrays(GL_TRIANGLES, 0, 3 * num_segments * (points.size() / 3));
        }


        glfwSwapBuffers(window);
        glfwPollEvents();
    }


    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &CBO);

    glfwTerminate();
    return 0;
}