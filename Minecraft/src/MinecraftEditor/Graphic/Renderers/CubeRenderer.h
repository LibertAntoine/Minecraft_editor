#pragma once

/**
 * \file CubeRenderer.h
 * \brief Manage the render of the cubes in the scene, the cube selector and the selection cube texture.
 * \author Antoine Libert & Nicolas Lienart
 */

#include <iostream>
#include <memory>
#include <list>
#include <algorithm>

#include "GraphicEngine/VertexBuffer.h"
#include "GraphicEngine/VertexBufferLayout.h"
#include "GraphicEngine/TextureArray.h"
#include "GraphicEngine/Shader.h"

#include "MinecraftEditor/Graphic/Forms/Cube.h"
#include "MinecraftEditor/Graphic/Lights/LightManager.h"

namespace renderer {

  class CubeRenderer 
  {
    private:
      std::unique_ptr<Shader> m_ShaderCube; // For drawing without light.
      std::unique_ptr<Shader> m_ShaderCubeDirLight; // For drawing with directionnal light.
      std::unique_ptr<Shader> m_ShaderCubePonctLight; // For drawing with ponctual light.
      std::unique_ptr<Shader> m_ShaderSelector; // For drawing the selector.
      std::unique_ptr<Shader> m_ShaderClickSelection; // For drawing the selection texture.

      std::unique_ptr<VertexArray> m_VAO;
      std::unique_ptr<VertexBuffer> m_VertexBufferPosition;
      std::unique_ptr<VertexBuffer> m_VertexBufferColor;
      std::unique_ptr<VertexBuffer> m_VertexBufferTexture;
      std::unique_ptr<VertexBuffer> m_VertexBufferType;
      std::unique_ptr<VertexBuffer> m_VertexBufferCubeId;
	  std::list<Forms::Cube> m_CubeList;
      
    public:
      
	   inline std::list<Forms::Cube>& CubeList() { return m_CubeList; };

      CubeRenderer();
      ~CubeRenderer();

	  /**
      * \brief Draw all the cube in the scene.
      * \param view : current matrix camera view.
      * \param projection : current projection matrix.
      * \param lightManager : current light parameters.
      * \param textureArray : textureArray used for textured the cubes.
      */
	  void drawCubes(glm::mat4 view, glm::mat4 projection, interaction::LightManager& lightManager, const TextureArray& textureArray);


	  /**
	  * \brief Draw a selector in the scene.
	  * \param position : scale of the current selector.
	  * \param scale : scale of the current selector.
	  * \param texture : texture of the current selector.
	  * \param view : current matrix camera view.
	  * \param projection : current projection matrix.
	  */
	  void drawSelector(const glm::vec3& position, const int& scale, std::shared_ptr<Texture> texture, glm::mat4 view, glm::mat4 projection);

	  /**
	  * \brief Draw the click selection texture.
	  * \param view : current matrix camera view.
	  * \param projection : current projection matrix.
	  */
	  void drawSelectionTexture(const glm::mat4& view, const glm::mat4& projection);

	  /**
	  * \brief Add a new cube at the scene (in the list and the octree).
	  * \param cube to add.
	  */
      Forms::Cube* add(const Forms::Cube& cube);
	  void del(Forms::Cube* cube);

		/**
		 * \brief Add a new cube at the scene (in the list and the octree). But do not update on GPU
		 * Suited for adding multiple element at once.
		 */
		Forms::Cube* addNoUpdate(const Forms::Cube& cube);
		/**
		 * \brief Update data on GPU
		 */
		void updateAll();

	  /**
		* \brief Update the PositionBuffer regarding the current Cube List.
	  */
      void updatePosition();

	  /**
	  * \brief Update the ColorBuffer regarding the current Cube List.
      */
      void updateColor();

	  /**
	  * \brief Update the TextureBuffer regarding the current Cube List.
      */
      void updateTexture();

	  /**
	  * \brief Update the TypeBuffer (colored/textured/multi-textured) regarding the current Cube List.
      */
      void updateType();

	  /**
	  * \brief Update the PositionBuffer regarding the current Cube List.
      */
      void updateCubeId();


  };

}
