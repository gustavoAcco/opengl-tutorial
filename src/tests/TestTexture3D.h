#pragma once

#include "Test.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"

#include <memory>

namespace test
{
    class TestTexture3D : public Test
    {
    public:
        TestTexture3D();
        ~TestTexture3D();

        void OnUpdate(float deltaTime) override;
        void OnRender() override;
        void OnImGuiRender() override;
    private:
        std::unique_ptr<VertexArray> m_VAO;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;
        std::unique_ptr<Shader> m_Shader;
        std::unique_ptr<Texture> m_Texture;

        glm::vec3 m_TranslationA, m_TranslationB;
        float fov, aspectRatio, nearPlane, farPlane;
        glm::vec3 cameraPos, cameraTarget, cameraUp;
        glm::mat4 m_Proj, m_View; 
    };
}
