#pragma once

#include <iostream>
#include <glm/glm.hpp>

namespace interaction {

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
		PointLight m_pointLight;
		glm::vec3 m_direction;
		glm::vec3 m_position;
		
		
	public:


		LightManager();
		~LightManager();


		inline DirLight& dirLight() { return m_dirLight; }
		inline PointLight& pointLight() { return m_pointLight; };

		inline glm::vec3& direction() { return m_direction; };
		inline glm::vec3& position() { return m_position; };



	};

}
