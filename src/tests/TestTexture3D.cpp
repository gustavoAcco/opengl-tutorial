#include "TestTexture3D.h"

#include "Renderer.h"
#include "glm/ext/matrix_clip_space.hpp"
#include "imgui/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <memory>

namespace test
{
    TestTexture3D::TestTexture3D()
        : m_TranslationA(0.0f, 0.0f, -2.0f), m_TranslationB(0.0f, 0.0f, -4.0f),
        fov(45.0f), aspectRatio(960.0f / 540.0f), nearPlane(0.1f), farPlane(100.0f),
        cameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), cameraTarget(glm::vec3(0.0f, 0.0f, 0.0f)), cameraUp(glm::vec3(0.0f, 1.0f, 0.0f)),
        m_Proj(glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane)),
        m_View(glm::lookAt(cameraPos, cameraTarget, cameraUp))
    {

        float positions[] = 
        {
            -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
             0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
             0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
            -0.5f,  0.5f, 0.0f, 0.0f, 1.0f,
        };

        unsigned int indices[] = 
        {
            0, 1, 2,
            2, 3, 0
        };
    

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        
        m_VAO = std::make_unique<VertexArray>();
        
        m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 5 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(3);
        layout.Push<float>(2);

        m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 6);
        m_VAO->AddBuffer(*m_VertexBuffer, layout);
        
        m_Shader = std::make_unique<Shader>("../res/shaders/basic.shader");
        m_Shader->Bind();

        m_Texture = std::make_unique<Texture>("../res/textures/jatai.png");
        m_Shader->SetUniform1i("u_Texture", 0);
    }

    TestTexture3D::~TestTexture3D()
    {
    }

    void TestTexture3D::OnUpdate(float deltaTime)
    {
    }

    void TestTexture3D::OnRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

        Renderer renderer;

        m_Texture->Bind();
        
        m_View = (glm::lookAt(cameraPos, cameraTarget, cameraUp));

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA); 
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB); 
            glm::mat4 mvp = m_Proj * m_View * model;
            m_Shader->Bind();
            m_Shader->SetUniformMat4f("u_MVP", mvp);

            renderer.Draw(*m_VAO, *m_IndexBuffer, *m_Shader);
        }
    }

    void TestTexture3D::OnImGuiRender()
    {
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        ImGui::SliderFloat3("Translation A", &m_TranslationA.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("Translation B", &m_TranslationB.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("CameraTarget", &cameraTarget.x, -10.0f, 10.0f);
        ImGui::SliderFloat3("CameraPosition", &cameraPos.x, -10.0f, 10.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    }
}
