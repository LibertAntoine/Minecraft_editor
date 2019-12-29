#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <vector>

namespace interaction {

	typedef enum lightStatus {
		NONE = 0, 
		DIRECTIONNAL = 1,
		PONCTUAL = 2
	} lightStatus;

	typedef struct dirLight {
		glm::vec3 uKd;
		glm::vec3 uKs;
		float shininess;
		glm::vec3 lightDirection;
		glm::vec3 lightIntensity;
	} DirLight;

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
		void AddPonctLight(const PointLight& pointLight);

		inline DirLight& dirLight() { return m_dirLight; }
		inline std::vector<PointLight>& pointLightList() { return m_pointLightList; };

		inline glm::vec3& direction() { return m_direction; };
		inline glm::vec3& position() { return m_position; };



	};

}
