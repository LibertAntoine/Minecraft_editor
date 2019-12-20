
#include "ModePlanette.h"
#include "Renderer.h"
#include "ImGUI/imgui.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL.h>
#include <string>

namespace mode {

	ModePlanette::ModePlanette()
		: m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)),
		m_CubeRenderer(),
		m_CubeSelector(m_CubeRenderer, 2048), //Obligatoirement une puissance de deux.
		m_backgroundColor(0.3f, 0.3f, 0.3f)

	{
		constexpr float fov = glm::radians(70.f);
		float ratio = 1080. / 720.;
		m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);

	}

  ModePlanette::~ModePlanette()
  {
  }

  void ModePlanette::OnUpdate(float deltaTime)
  {
  }

  void ModePlanette::OnEvent(const SDL_Event& e)
  {
  }


  void ModePlanette::OnRender()
  {

		GLCall(glClearColor(m_backgroundColor.x, m_backgroundColor.y, m_backgroundColor.z, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix);
		m_GridRenderer.draw(m_FreeCam, m_ProjMatrix);
		m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);
	}


  void ModePlanette::OnImGuiRender()
  {
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	
	m_Interface.SelectorInterface(m_CubeSelector);
	m_Interface.CameraInterface(m_FreeCam);

	ImGuiWindowFlags corner =
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoSavedSettings;

	bool open = true;
	ImGui::Begin("Test", &open, corner);
	ImGui::SetWindowPos(ImVec2(0, 500), true);
	ImGui::SetWindowSize(ImVec2(200, 200), true);

	ImGui::End();


	const float my_values[] = { 0.2f, 0.1f, 1.0f, 0.5f, 0.9f, 2.2f };
	ImGui::PlotLines("Frame Times", my_values, IM_ARRAYSIZE(my_values));


	ImGui::Begin("Infos Current Cube");
	if (m_CubeSelector.selector()->currentCube != nullptr) {
		ImGui::Text("Cube Scale : ");
		ImGui::InputInt("scalec", m_CubeSelector.selector()->currentCube->scalePtr(), 1, 100);
		if (m_CubeSelector.selector()->currentCube->texture() != nullptr) {
			ImGui::Text("Cube Texture : ");
			ImGui::Text(m_CubeSelector.selector()->currentCube->texture()->name().c_str());
			if (ImGui::BeginCombo("Texture Cube", m_CubeSelector.selector()->currentCube->texture()->name().c_str())) {
				for (int i = 0; i < m_CubeSelector.textureList()->nameList().size(); ++i)
				{
					bool is_selected = (m_CubeSelector.selector()->currentCube->texture()->name() == m_CubeSelector.textureList()->nameList()[i]);
					if (ImGui::Selectable(m_CubeSelector.textureList()->nameList()[i].c_str(), is_selected))
						m_CubeSelector.selector()->currentCube->texture(m_CubeSelector.textureList()->give(m_CubeSelector.textureList()->nameList()[i]));
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
		} else {
			ImGui::Text("Cube Color : ");
			float r = m_CubeSelector.selector()->currentCube->color().x;
			float g = m_CubeSelector.selector()->currentCube->color().y;
			float b = m_CubeSelector.selector()->currentCube->color().z;
			if (ImGui::InputFloat("r", &r, 0.01f, 0.1f, "%.3f") || ImGui::InputFloat("g", &g, 0.01f, 0.1f, "%.3f") || ImGui::InputFloat("b", &b, 0.01f, 0.1f, "%.3f")) {
				m_CubeSelector.selector()->currentCube->Setcolor(glm::vec3(r, g, b));
			};
		}

		ImGui::Text("Cube Position : ");
		int xc = m_CubeSelector.selector()->currentCube->position().x;
		int yc = m_CubeSelector.selector()->currentCube->position().y;
		int zc = m_CubeSelector.selector()->currentCube->position().z;
		if (ImGui::InputInt("x", &xc, 1, 100) || ImGui::InputInt("y", &yc, 1, 100) || ImGui::InputInt("z", &zc, 1, 100)) {
			m_CubeSelector.selector()->selectorPosition = glm::vec3(xc, yc, zc);
			m_CubeSelector.Move(m_CubeSelector.selector()->currentCube, glm::vec3(xc, yc, zc));
		};
	}
	ImGui::End();







  }
}
