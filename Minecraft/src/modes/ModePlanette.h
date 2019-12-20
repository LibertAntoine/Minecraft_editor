#pragma once

#include "Mode.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "Texture.h"
#include "Camera.h"
#include <vector>
#include <algorithm>
#include "forms/Cube.h"
#include "Renderer/CubeRenderer.h"
#include "Renderer/GridRenderer.h"
#include "Interaction/CubeSelector.h"
#include "Interaction/Interface.h"


#include <memory>

namespace mode {
	class ModePlanette: public Mode
	{
	private:
		glm::vec3 m_backgroundColor;
		glm::mat4 m_ProjMatrix;
		camera::TrackballCamera m_TrackCam;
		camera::FreeflyCamera m_FreeCam;
		renderer::GridRenderer m_GridRenderer;
		renderer::CubeRenderer m_CubeRenderer;
		interaction::CubeSelector m_CubeSelector;
		interaction::Interface m_Interface;


	public:
		ModePlanette();
		~ModePlanette();
		void OnUpdate(float deltaTime) override;
		void OnEvent(const SDL_Event& e) override;
		void OnRender() override;
		void OnImGuiRender() override;

	};
}
