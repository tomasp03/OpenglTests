#pragma once
#include "Test.h"
#include <glm/glm.hpp>
#include <glad/glad.h>
#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>

#include "Loader.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Window.h"
#include "Shapes.h"

namespace test
{
    struct Data
    {
        float scale = 1.0f;
        bool show = true;
        glm::vec4 color = glm::vec4(1.0f);
        glm::vec2 position = { 10.f, 10.f };
        glm::vec2 speed = { 500.f, 300.f };
        float size = 100.f;

        glm::vec2 PosForOpneGL(int width, int height)
        {
            float f_width = (float)width * 0.5f;
            float f_height = (float)height * 0.5f;

            return glm::vec2(position.x / f_width - 1.0f, -(position.y / f_height - 1.0f));
        }

        float SizeForOpenGL(int width, int height)
        {
            return 2 * (size / (float)width);
        }
    };

    class Squares : public Test
    {
    public:
        Squares(int w_width, int w_height);
        ~Squares() override;

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
        GLFWwindow* WindowID();

    private:
        static const unsigned int MaxQuads = 1000000;
        static const unsigned int NumberOfVertices = 4 * MaxQuads;
        static const unsigned int NumberOfIndices = 6 * MaxQuads;
        Data m_Squares[MaxQuads];

        Window* m_window;
        Shader* m_shader;
        VBO* m_VBO;
        VAO* m_VAO;
        EBO* m_EBO;

        float dt;
        double prevTime;
        double crntTime;
        double timeDiff;
        unsigned int counter;
        std::string FPS;
        std::string ms;
    };

}

