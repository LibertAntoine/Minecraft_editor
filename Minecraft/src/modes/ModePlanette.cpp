#include "ModePlanette.h"
#include "ImGUI/imgui.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL.h>
#include <string>

namespace mode {



	ModePlanette::ModePlanette()
		: m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
		m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)), m_CubeRenderer(),
		m_CubeSelector(m_CubeRenderer, 2048), // Obligatoirement une puissance de deux.
		m_backgroundColor(0.3f, 0.3f, 0.3f)

	{
		constexpr float fov = glm::radians(70.f);
		float ratio = (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT;
		m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_CULL_FACE);

		/*
		m_CubeSelector.Create(glm::vec3(0, 0, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 2, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 4, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 6, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 8, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 10, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 12, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 14, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 16, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 18, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 20, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 22, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		m_CubeSelector.Create(glm::vec3(0, 24, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
		*/

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


		// NOTE: Selection related stuff
		m_textureSelection.EmptyTexture();
		m_frameBufferSelection.Bind();
		m_textureSelection.SimpleBind();
		m_depthBufferSelection.Bind();
		// TODO: adapt to screen size dynamically
		GLCall(glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, 1080, 720););
		GLCall(glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferSelection.getDepthBufferId()););
		GLCall(glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, m_textureSelection.GetTextureID(), 0););
		GLCall(GLenum DrawBuffers[1] = { GL_COLOR_ATTACHMENT0 };);
		GLCall(glDrawBuffers(1, DrawBuffers););

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Problem with the framebuffer" << std::endl;

		m_frameBufferSelection.Unbind();
		m_textureSelection.Unbind();
		m_depthBufferSelection.Unbind();


	}

	void ModePlanette::OnEvent(const SDL_Event& e) {}

	ModePlanette::~ModePlanette() {}

	void ModePlanette::OnUpdate(float deltaTime) {}

	void ModePlanette::OnRender()
	{

		GLCall(glClearColor(m_backgroundColor.x, m_backgroundColor.y,
			m_backgroundColor.z, 1.0f));
		// TODO: Check if necessary (redundancy) because of App.cpp beginFrame()
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		m_GridRenderer.draw(m_FreeCam, m_ProjMatrix);
		m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix);
		m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);

		// NOTE: Generating offscreen selection texture
		m_frameBufferSelection.Bind();
		glClearColor(1, 1, 1, 1); // White for unselectable air
		glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		m_CubeSelectionRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix, m_CubeRenderer.m_CubeList);
		m_frameBufferSelection.Unbind();

	}

	void ModePlanette::OnImGuiRender()
	{
		m_Interface.MenuBarInterface(m_FreeCam, m_CubeSelector);
		m_Interface.MainActionMenu(m_FreeCam, m_CubeSelector);
		m_Interface.MenuInfosInterface(m_FreeCam, m_CubeSelector);
	}
}
