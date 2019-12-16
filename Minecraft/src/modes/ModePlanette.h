#pragma once

#include "Mode.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include <vector>
#include <algorithm>
#include "forms/Cube.h"


#include <memory>

namespace mode {
	class ModePlanette: public Mode
	{
	public:
		ModePlanette();
		~ModePlanette();
		void OnUpdate(float deltaTime) override;
		void OnEvent(SDL_Event& e) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		std::unique_ptr<VertexArray> m_VAO;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<Shader> m_Shader;
		std::unique_ptr<Texture> m_Texture;
		glm::mat4 m_ProjMatrix;
		camera::TrackballCamera m_TrackCam;
		camera::FreeflyCamera m_FreeCam;
		std::vector<form::Cube> m_CubeVect;
	};
}