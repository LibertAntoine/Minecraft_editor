#include "CubeSelector.h"



namespace interaction {

	CubeSelector::CubeSelector(renderer::CubeRenderer& renderer, const int& capacity)
		:m_Cuberenderer(&renderer), m_SizeWorld(capacity), m_CubeWorld(capacity * 2, nullptr),
		m_textSelector(std::make_unique<Texture>("res/textures/blocks/Texture_Selection.png"))
	{
		m_selector = new interaction::Selector();
		m_selector->selectorPosition = glm::vec3(0, 0, 0);
		m_selector->selectorTexture = "res/textures/blocks/log_acacia_top.png";
		m_selector->selectorScale = 1;
	}

	CubeSelector::~CubeSelector() {

	}

	void CubeSelector::Create(const glm::vec3& position, const char* textName, const int& scale) {
		{
			m_CubeWorld.set(
				(int)position.x + m_SizeWorld,
				(int)position.y + m_SizeWorld,
				(int)position.z + m_SizeWorld,
				m_Cuberenderer->add(form::Cube(position, textName, scale))
			);
		}
	}

	form::Cube* CubeSelector::currentCube() {
		return m_CubeWorld.at(m_selector->selectorPosition.x + m_SizeWorld, m_selector->selectorPosition.y + m_SizeWorld, m_selector->selectorPosition.z + m_SizeWorld);
	}

	void CubeSelector::Show(glm::mat4 view, glm::mat4 projection) {
		m_Cuberenderer->drawSelector(m_selector->selectorPosition, *m_textSelector, view, projection);
	}

	void CubeSelector::Move(form::Cube* cube, const glm::vec3& NewPosition) {
		cube->position(NewPosition);
		m_CubeWorld.set(NewPosition.x + m_SizeWorld, NewPosition.y + m_SizeWorld, NewPosition.z + m_SizeWorld, cube);
	}

	void CubeSelector::MoveSelector(const glm::vec3& deplacement) {
		m_selector->selectorPosition += deplacement;
	}

	void CubeSelector::AddToSelector() {
		this->Create(m_selector->selectorPosition, m_selector->selectorTexture, m_selector->selectorScale);
	}

	void CubeSelector::DeleteToSelector() {
		form::Cube* cube = this->currentCube();
		if (cube != nullptr) {
			m_Cuberenderer->del(cube);
			m_CubeWorld.erase(m_selector->selectorPosition.x + m_SizeWorld, m_selector->selectorPosition.y + m_SizeWorld, m_selector->selectorPosition.z + m_SizeWorld);
		}
	}

}