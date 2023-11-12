#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
const float shrinkDistance = 0.01f;//内缩距离
void processMesh(aiMesh* mesh) {
    std::vector<aiVector3D> shrunkVertices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];
        aiVector3D normal = mesh->mNormals[i];

        // 计算内缩后的顶点位置
        aiVector3D shrunkVertex = vertex - normal * shrinkDistance;
        shrunkVertices.push_back(shrunkVertex); 
    }
}

void loadModel(const std::string& path) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return;
    }

    std::cout << "Loaded model successfully." << std::endl;

    // 遍历每个网格
    for (unsigned int i = 0; i < scene->mNumMeshes; i++) {
        processMesh(scene->mMeshes[i]);
    }
}

void setupShrunkMesh(const std::vector<aiVector3D>& shrunkVertices) {
    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * shrunkVertices.size(), &shrunkVertices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(aiVector3D), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 在这里存储VAO和VBO以便后续渲染
}

void renderShrunkMesh(GLuint VAO, size_t numVertices) {
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}



int main() {
    loadModel("./models/bunny.obj");
    return 0;
}
