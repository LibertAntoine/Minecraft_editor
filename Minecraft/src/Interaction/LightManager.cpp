#include "LightManager.h"


namespace interaction {
	LightManager::LightManager() 
		:m_direction(glm::vec3(1.0f, 1.0f, 1.0f)), m_position(glm::vec3(1.0f, 1.0f, 1.0f)),
		m_currentLight(NONE)
	{
		m_dirLight = {
			glm::vec3(0.7, 0.7, 0.7),
			glm::vec3(0.3, 0.3, 0.3),
			1,
			glm::vec3(0, 0, 0),
			glm::vec3(0.2, 0.2, 0.2),
		};

		m_pointLightList.push_back(PointLight{
			glm::vec3(0.7, 0.7, 0.7),
			glm::vec3(0.3, 0.3, 0.3),
			1,
			glm::vec3(1, 0, 1),
			glm::vec3(0.2, 0.2, 0.2),
			});
	}

	LightManager::~LightManager() {
	
	
	}


}