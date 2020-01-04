#pragma once

/**
 * \file CubeRenderer.h
 * \brief Manage the render of the cubes in the scene, the cube selector and the selection cube texture.
 * \author Antoine Libert & Nicolas Lienart
 */


#include <iostream>
#include <glm/glm.hpp>
#include <vector>

namespace interaction {

	/**
	* \brief Indicate the current light used in the scene.
	*/
	typedef enum lightStatus {
		NONE = 0, 
		DIRECTIONNAL = 1,
		PONCTUAL = 2
	} lightStatus;

	/**
	* \brief Datas relative to a directional light.
	*/
	typedef struct dirLight {
		glm::vec3 uKd;
		glm::vec3 uKs;
		float shininess;
		glm::vec3 lightDirection;
		glm::vec3 lightIntensity;
	} DirLight;

	/**
	* \brief Datas relative to a ponctual light.
	*/
	typedef struct pointLight {
		glm::vec3 uKd;
		glm::vec3 uKs;
		float shininess;
		glm::vec3 lightPosition;
		glm::vec3 lightIntensity;
	} PointLight;

	class LightManager
	{
	private:
		DirLight m_dirLight;
		std::vector<PointLight> m_pointLightList;
		glm::vec3 m_direction;
		glm::vec3 m_position;
		lightStatus m_currentLight;
		
	public:

		LightManager();
		~LightManager();

		/**
		* \brief Add a ponctual light at the list.
		* \param pointLight to add.
		*/
		void AddPonctLight(const PointLight& pointLight);

		// GETTERS - SETTERS //
		inline DirLight& dirLight() { return m_dirLight; }
		inline std::vector<PointLight>& pointLightList() { return m_pointLightList; };
		inline glm::vec3& direction() { return m_direction; };
		inline glm::vec3& position() { return m_position; };
		inline lightStatus& currentLight() { return m_currentLight; }
	};

}
