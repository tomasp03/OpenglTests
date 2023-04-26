#pragma once
#include "Test.h"
#include "VAO.h"
#include "VBO.h"
#include "Shader.h"
#include <string>
#define SPHERES_COUNT 2 //also in fragment shader
#define NUMBER_OF_RANDOM 1000 //also in fragment shader


namespace test
{
    struct Material
    {
        glm::vec4 albido;
        float roughness;
        glm::vec4 emissionColor;
        float emissionStrength;
    };

    struct Sphere
    {
        glm::vec3 center;
        float radius;
        Material mat;
    };

    class RayTrace : public Test
    {
    private:
        float* image;
        unsigned char* bytes;
        GLuint screenTex;
        GLuint computeShader;
        GLuint computeProgram;
        VBO* m_VBO;
        VAO* m_VAO;
        Shader* m_Shader;
        Sphere* m_Spheres;
        Sphere* m_Light;
        float randoms[NUMBER_OF_RANDOM];

        float crntTime = 0;
        float prevTime = 0;
        float timeDiff = 0;
        int counter = 0;
        float show = 0;
        float read = 0;


        std::string FPS = " ";
        std::string ms = " ";

    public:
        RayTrace();
        void OnUpdate(float deltaTime) override;
        void OnRender(GLFWwindow* window) override;
        void OnImGuiRender() override;
    };

}

