#include "CubeSelector.h"



namespace interaction {

	CubeSelector::CubeSelector(renderer::CubeRenderer& renderer, const int& capacity)
		:m_Cuberenderer(&renderer), m_SizeWorld(capacity), m_CubeWorld(capacity * 2, nullptr)
	{
		m_selector = new interaction::Selector();
		m_selector->selectorPosition = glm::vec3(0, 1, 0);
		m_selector->selectedPosition = glm::vec3(0, 1, 0);
		m_selector->currentSelected = false;
		m_selector->currentCopy = false;
		m_selector->selectorScale = 2;
		m_TextureList.addToList("res/textures/blocks/log_acacia_top.png");
		m_TextureList.addToList("res/textures/blocks/piston_bottom.png");
		m_TextureList.addToList("res/textures/blocks/red_sandstone_bottom.png");
		m_TextureList.addToList("res/textures/blocks/lava_placeholder.png");
		m_selector->selectorTexture = m_TextureList.give("log_acacia_top");

		this->Create(glm::vec3(0, 0, 0), nullptr, m_selector->selectorScale);
		this->Create(glm::vec3(3, 3, 3), m_selector->selectorTexture, m_selector->selectorScale);
		this->Create(glm::vec3(0, 3, 3), m_selector->selectorTexture, m_selector->selectorScale);
		this->refresh();
	}	

	CubeSelector::~CubeSelector() {

	}

	void CubeSelector::Create(const glm::vec3& position, Texture* texture, const int& scale, const glm::vec3& color) {
		{
			m_selector->currentSelected = false;
			form::Cube* cube = m_CubeWorld.at(position.x + m_SizeWorld, position.y + m_SizeWorld, position.z + m_SizeWorld);
			if (cube != nullptr) {
				this->Delete(cube);
			}
			m_CubeWorld.set(
				(int)position.x + m_SizeWorld,
				(int)position.y + m_SizeWorld,
				(int)position.z + m_SizeWorld,
				m_Cuberenderer->add(form::Cube(position, texture, scale, color))
			);
			this->refresh();
		}
	}

	void CubeSelector::Delete(form::Cube* cube) {
		m_selector->currentSelected = false;
		if (cube != nullptr) {
			m_CubeWorld.erase(cube->position().x + m_SizeWorld, cube->position().y + m_SizeWorld, cube->position().z + m_SizeWorld);
			m_Cuberenderer->del(cube);
			this->refresh();
		}
	}

	void CubeSelector::refresh() {
		m_selector->currentCube = m_CubeWorld.at(m_selector->selectorPosition.x + m_SizeWorld, m_selector->selectorPosition.y + m_SizeWorld, m_selector->selectorPosition.z + m_SizeWorld);
	}

	form::Cube* CubeSelector::currentSelected() {
		return m_CubeWorld.at(m_selector->selectedPosition.x + m_SizeWorld, m_selector->selectedPosition.y + m_SizeWorld, m_selector->selectedPosition.z + m_SizeWorld);
	}

	void CubeSelector::Show(glm::mat4 view, glm::mat4 projection) {
		if (m_selector->currentSelected == true)
			m_Cuberenderer->drawSelector(m_selector->selectedPosition, m_selector->selectorScale, m_TextureList.selected(), view, projection);
		m_Cuberenderer->drawSelector(m_selector->selectorPosition, m_selector->selectorScale, m_TextureList.selector(), view, projection);
		}

	void CubeSelector::MoveIn() {
		if (m_selector->currentCube != nullptr) {
			m_selector->currentSelected = true;
			m_selector->selectedPosition = m_selector->selectorPosition;
			this->refresh();
		}
	}

	void CubeSelector::MoveOut() {
		if (m_selector->currentSelected == true) {
			this->DeleteToSelector();
			m_selector->currentSelected = false;
			this->Move(this->currentSelected(), m_selector->selectorPosition);
		}
	}

	void CubeSelector::Move(form::Cube* cube, const glm::vec3& newPosition) {
		if (cube != nullptr) {
			m_CubeWorld.erase(cube->position().x + m_SizeWorld, cube->position().y + m_SizeWorld, cube->position().z + m_SizeWorld);
			m_CubeWorld.set(newPosition.x + m_SizeWorld, newPosition.y + m_SizeWorld, newPosition.z + m_SizeWorld, cube);
			cube->position(newPosition);
		}
	}


	void  CubeSelector::Extrude() {
		form::Cube* cube = nullptr;
		int size = m_SizeWorld * 2;
		for (int i = 1; cube == nullptr && i <= size; ++i) {
			cube = m_CubeWorld.at(m_selector->selectorPosition.x + m_SizeWorld, size - i, m_selector->selectorPosition.z + m_SizeWorld);
		}
		if (cube == nullptr)
			this->Create(glm::vec3(m_selector->selectorPosition.x, 1, m_selector->selectorPosition.z), m_selector->selectorTexture, m_selector->selectorScale);
		else
			this->Create(glm::vec3(cube->position().x, cube->position().y + 2, cube->position().z), cube->texture(), cube->scale());
	}

	void CubeSelector::Dig() {
		form::Cube* cube = nullptr;
		int size = m_SizeWorld * 2;
		for (int i = 1; cube == nullptr && i <= size; ++i) {
			cube = m_CubeWorld.at(m_selector->selectorPosition.x + m_SizeWorld, size - i, m_selector->selectorPosition.z + m_SizeWorld);
		}
		this->Delete(cube);
	}



	void CubeSelector::MoveSelector(const glm::ivec3& deplacement) {
		m_selector->selectorPosition += deplacement;
		if (m_selector->selectorPosition.y - m_selector->selectorScale < 1)
			m_selector->selectorPosition.y = 1;
		this->refresh();
	}

	void CubeSelector::SetSelector(const glm::ivec3& NewPosition) {
		m_selector->selectorPosition = NewPosition;
		if (m_selector->selectorPosition.y - m_selector->selectorScale < 1)
			m_selector->selectorPosition.y = 1;
		this->refresh();
	}

	void CubeSelector::AddToSelector() {
		this->Create(m_selector->selectorPosition, m_selector->selectorTexture, m_selector->selectorScale);
	}

	void CubeSelector::DeleteToSelector() {
		this->Delete(m_selector->currentCube);
	}

}