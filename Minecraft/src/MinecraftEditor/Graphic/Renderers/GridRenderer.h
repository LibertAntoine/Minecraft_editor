#pragma once

/**
 * \file CubeRenderer.h
 * \brief Manage the render of the grids in the scene and the click selection grid texture.
 * \author Antoine Libert & Nicolas Lienart
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include "GraphicEngine/VertexBuffer.h"
#include "GraphicEngine/VertexArray.h"
#include "GraphicEngine/IndexBuffer.h"
#include "GraphicEngine/Shader.h"
#include "GraphicEngine/VertexBufferLayout.h"
#include "GraphicEngine/Camera.h"

#include "MinecraftEditor/Graphic/Forms/Grid.h"
#include <memory>

namespace renderer {
  class GridRenderer
  {
		private:
			// Scene Grids //
			std::unique_ptr<VertexArray> m_VAOGrid;
			std::unique_ptr<IndexBuffer> m_IndexBufferGrid;
			std::unique_ptr<VertexBuffer> m_VertexBufferGrid;
			Forms::Grid m_grid;
			std::unique_ptr<Shader> m_ShaderGrid;

			// Click Selection Grid Texture //
			std::unique_ptr<VertexArray> m_VAOGridSelection;
			std::unique_ptr<VertexBuffer> m_VertexBufferGridSelection;
			std::unique_ptr<IndexBuffer> m_IndexBufferGridSelection;
			Forms::GridSelection m_gridSelection;
			std::unique_ptr<Shader> m_ShaderGridSelection;

		public:

			/**
			 * \brief Init the grid renderer.
			 * \param size of the grid in the scene.
			 * \param color of the grid.
			 */
			GridRenderer(const unsigned int& size, glm::vec3 color);
			~GridRenderer();

			/**
			 * \brief Draw the different grids of the scene (if visible).
			 * \param camera : current camera of the scene.
			 * \param projection : current projection matrix.
			 * \param active : array of three bool said which grid are visible (x, y, z grid).
			 */
			void drawGrid(const camera::FreeflyCamera& camera, const glm::mat4& projection, bool* active);

			/**
			 * \brief Draw the click selection grid texture.
			 * \param camera : current camera of the scene.
			 * \param projection : current projection matrix.
			 */
			void drawGridSelection(const camera::FreeflyCamera& camera, const glm::mat4& projection);
  };

}
