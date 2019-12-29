#include "LightManager.h"


namespace interaction {
	LightManager::LightManager() 
		:m_direction(glm::vec3(0.80f, 0.96f, -0.66f)), m_position(glm::vec3(1.2f, 1.5f, -1.7f)),
		m_currentLight(PONCTUAL)
	{
		m_dirLight = {
			glm::vec3(0.7, 0.7, 0.7),
			glm::vec3(0.3, 0.3, 0.3),
			1,
			glm::vec3(0, 0, 0),
			glm::vec3(1.5, 1.5, 1.5),
		};

		m_pointLightList.push_back(PointLight{
			glm::vec3(0.7, 0.7, 0.7),
			glm::vec3(0.3, 0.3, 0.3),
			1,
			glm::vec3(1, 0, 1),
			glm::vec3(6.0, 6.0, 6.0),
			});
	}

	LightManager::~LightManager() {
	}

	void LightManager::AddPonctLight(const PointLight& pointLight) {
		m_pointLightList.push_back(pointLight);
	}

}