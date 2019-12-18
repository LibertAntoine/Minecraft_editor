#include "CubeSelector.h"



namespace interaction {

	CubeSelector::CubeSelector(renderer::CubeRenderer& renderer, const int& capacity)
		:m_Cuberenderer(&renderer), m_SizeWorld(capacity), m_CubeWorld(capacity * 2, nullptr),
		m_textSelector(std::make_unique<Texture>("res/textures/blocks/Texture_Selection.png")),
		m_textSelected(std::make_unique<Texture>("res/textures/blocks/Texture_Selected.png"))
	{
		m_selector = new interaction::Selector();
		m_selector->selectorPosition = glm::vec3(0, 1, 0);
		m_selector->selectedPosition = glm::vec3(0, 1, 0);
		m_selector->currentSelected = false;
		m_selector->selectorTexture = "res/textures/blocks/log_acacia_top.png";
		m_selector->selectorScale = 1;
	}

	CubeSelector::~CubeSelector() {

	}

	void CubeSelector::Create(const glm::vec3& position, const char* textName, const int& scale) {
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
				m_Cuberenderer->add(form::Cube(position, textName, scale))
			);
		}
	}

	void CubeSelector::Delete(form::Cube* cube) {
		m_selector->currentSelected = false;
		if (cube != nullptr) {
			m_CubeWorld.erase(cube->position().x + m_SizeWorld, cube->position().y + m_SizeWorld, cube->position().z + m_SizeWorld);
			m_Cuberenderer->del(cube);
		}
	}

	form::Cube* CubeSelector::currentCube() {
		return m_CubeWorld.at(m_selector->selectorPosition.x + m_SizeWorld, m_selector->selectorPosition.y + m_SizeWorld, m_selector->selectorPosition.z + m_SizeWorld);
	}

	form::Cube* CubeSelector::currentSelected() {
		return m_CubeWorld.at(m_selector->selectedPosition.x + m_SizeWorld, m_selector->selectedPosition.y + m_SizeWorld, m_selector->selectedPosition.z + m_SizeWorld);
	}

	void CubeSelector::Show(glm::mat4 view, glm::mat4 projection) {
		m_Cuberenderer->drawSelector(m_selector->selectorPosition, *m_textSelector, view, projection);
		if (m_selector->currentSelected == true)
			m_Cuberenderer->drawSelector(m_selector->selectedPosition, *m_textSelected, view, projection);
	}

	void CubeSelector::MoveIn() {
		if (this->currentCube() != nullptr) {
			m_selector->currentSelected = true;
			m_selector->selectedPosition = m_selector->selectorPosition;
		}
	}

	void CubeSelector::MoveOut() {
		if (m_selector->currentSelected == true) {
			this->DeleteToSelector();
			form::Cube* cube = this->currentSelected();
			if (cube != nullptr) {
				m_CubeWorld.set(m_selector->selectorPosition.x + m_SizeWorld, m_selector->selectorPosition.y + m_SizeWorld, m_selector->selectorPosition.z + m_SizeWorld, cube);
				m_CubeWorld.erase(m_selector->selectedPosition.x + m_SizeWorld, m_selector->selectedPosition.y + m_SizeWorld, m_selector->selectedPosition.z + m_SizeWorld);
				cube->position(m_selector->selectorPosition);
			}
			m_selector->currentSelected = false;

		}
	}

	void  CubeSelector::Extrude() {
		form::Cube* cube = nullptr;
		int size = m_SizeWorld * 2;
		for (int i = 1; cube == nullptr && i <= size; ++i) {
			cube = m_CubeWorld.at(m_selector->selectorPosition.x + m_SizeWorld, size - i, m_selector->selectorPosition.z + m_SizeWorld);
		}
		if (cube == nullptr)
			this->Create(glm::vec3(m_selector->selectorPosition.x, 1, m_selector->selectorPosition.z), "Imac.png", 1);
		else
			this->Create(glm::vec3(cube->position().x, cube->position().y + 2, cube->position().z), cube->texture(), cube->scale());
	}

	void  CubeSelector::Dig() {
		form::Cube* cube = nullptr;
		int size = m_SizeWorld * 2;
		for (int i = 1; cube == nullptr && i <= size; ++i) {
			cube = m_CubeWorld.at(m_selector->selectorPosition.x + m_SizeWorld, size - i, m_selector->selectorPosition.z + m_SizeWorld);
		}
		this->Delete(cube);
		
	}



	void CubeSelector::MoveSelector(const glm::vec3& deplacement) {
		m_selector->selectorPosition += deplacement;
	}

	void CubeSelector::AddToSelector() {
		this->Create(m_selector->selectorPosition, m_selector->selectorTexture, m_selector->selectorScale);
	}

	void CubeSelector::DeleteToSelector() {
		this->Delete(this->currentCube());
	}

}