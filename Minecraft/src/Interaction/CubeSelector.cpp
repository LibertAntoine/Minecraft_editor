#include "CubeSelector.h"


namespace interaction {

  CubeSelector::CubeSelector(renderer::CubeRenderer& renderer, TextureArray& textureArray, const int& capacity)
    :m_Cuberenderer(&renderer), m_TextureArray(&textureArray), m_SizeWorld(capacity), m_CubeWorld(capacity * 2, nullptr),
      m_textSelector(std::make_unique<Texture>("res/textures/Cube/Texture_Selection.png", "Selection_Texture")),
      m_textSelected(std::make_unique<Texture>("res/textures/Cube/Texture_Selected.png", "Selected_Texture")),
      m_textCopy(std::make_unique<Texture>("res/textures/Cube/Texture_Selected.png", "Copy_Texture"))
  {
    m_activeGrid[0] = true;
    m_activeGrid[1] = false;
    m_activeGrid[2] = false;

    m_selector = new interaction::Selector();
    m_selector->selectedPosition = glm::vec3(0, 1, 0);
    m_selector->currentSelected = false;
    m_selector->currentCopy = false;
    m_selector->selectorCube = form::Cube(glm::ivec3(0, 0, 0), 1, glm::vec3(0, 0.5, 0.5), form::COLORED, { 0,0,0,0,0,0 });

    this->Create(m_selector->selectorCube);
    this->refresh();
  }	

  CubeSelector::~CubeSelector() {
    delete m_selector;
  }

  void CubeSelector::Create(const form::Cube& NewCube) {
    {
      m_selector->currentSelected = false;
      form::Cube* cube = m_CubeWorld.at(NewCube.position().x + m_SizeWorld, NewCube.position().y + m_SizeWorld, NewCube.position().z + m_SizeWorld);
      if (cube != nullptr) {
        this->Delete(cube);
      }
      m_CubeWorld.set(
          NewCube.position().x + m_SizeWorld,
          NewCube.position().y + m_SizeWorld,
          NewCube.position().z + m_SizeWorld,
          m_Cuberenderer->add(NewCube)
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
    m_selector->currentCube = m_CubeWorld.at(
        m_selector->selectorCube.position().x + m_SizeWorld,
        m_selector->selectorCube.position().y + m_SizeWorld, 
        m_selector->selectorCube.position().z + m_SizeWorld);
  }

  form::Cube* CubeSelector::currentSelected() {
    return m_CubeWorld.at(m_selector->selectedPosition.x + m_SizeWorld, 
        m_selector->selectedPosition.y + m_SizeWorld,
        m_selector->selectedPosition.z + m_SizeWorld);
  }

  void CubeSelector::Show(glm::mat4 view, glm::mat4 projection) {
    if (m_selector->currentSelected == true)
      m_Cuberenderer->drawSelector(m_selector->selectedPosition, 
          m_selector->selectorCube.scale(),
          m_textSelected, view, projection);
    m_Cuberenderer->drawSelector(m_selector->selectorCube.position(),
        m_selector->selectorCube.scale(), m_textSelector,
        view, projection);
  }

  void CubeSelector::MoveIn() {
    if (m_selector->currentCube != nullptr) {
      m_selector->currentSelected = true;
      m_selector->selectedPosition = m_selector->selectorCube.position();
      this->refresh();
    }
  }

  void CubeSelector::MoveOut() {
    if (m_selector->currentSelected == true) {
      this->DeleteToSelector();
      m_selector->currentSelected = false;
      this->Move(this->currentSelected(), m_selector->selectorCube.position());
    }
  }

  void CubeSelector::Move(form::Cube* cube, const glm::vec3& newPosition) {
    if (cube != nullptr) {
      m_CubeWorld.erase(cube->position().x + m_SizeWorld, cube->position().y + m_SizeWorld, cube->position().z + m_SizeWorld);
      m_CubeWorld.set(newPosition.x + m_SizeWorld, newPosition.y + m_SizeWorld, newPosition.z + m_SizeWorld, cube);
      cube->position(newPosition);
      m_Cuberenderer->updatePosition();
    }
  }


  void  CubeSelector::Extrude() {
    form::Cube* cube = nullptr;
    glm::vec3 NewPosition;
    int size = m_SizeWorld * 2;
    for (int i = 1; cube == nullptr && i <= size; ++i) {
      cube = m_CubeWorld.at(m_selector->selectorCube.position().x + m_SizeWorld, 
          size - i, m_selector->selectorCube.position().z + m_SizeWorld);
    }
    if (cube == nullptr) {
      NewPosition = glm::vec3(m_selector->selectorCube.position().x, 
          0, m_selector->selectorCube.position().z);
      this->Create(form::Cube(NewPosition, m_selector->selectorCube.scale(), 
            m_selector->selectorCube.color(), m_selector->selectorCube.type(), m_selector->selectorCube.texture()));
    } else {
      NewPosition = glm::vec3(cube->position().x, cube->position().y + cube->scale(), cube->position().z);
      this->Create(form::Cube(NewPosition, cube->scale(), cube->color(), cube->type(), cube->texture()));

    }
    this->SetSelector(NewPosition);
  }

  void CubeSelector::Dig() {
    form::Cube* cube = nullptr;
    glm::vec3 position;
    int size = m_SizeWorld * 2;
    for (int i = 1; cube == nullptr && i <= size; ++i) {
      cube = m_CubeWorld.at(m_selector->selectorCube.position().x + 
          m_SizeWorld, size - i, m_selector->selectorCube.position().z + m_SizeWorld);
    }
    if (cube == nullptr) {
      position = glm::vec3(m_selector->selectorCube.position().x, 
          0, m_selector->selectorCube.position().z), 
               m_selector->selectorCube.texture(), m_selector->selectorCube.scale();
    }
    else {
      position = glm::vec3(cube->position().x, cube->position().y - cube->scale(), cube->position().z);
      this->Delete(cube);
    }
    this->SetSelector(position);
  }

  void CubeSelector::MoveSelector(const glm::ivec3& deplacement) {
    m_selector->selectorCube.position() += deplacement;
    if (m_selector->selectorCube.position().y < 0)
      m_selector->selectorCube.position().y = 0;
    this->refresh();
  }

  void CubeSelector::SetSelector(const glm::ivec3& NewPosition) {
    m_selector->selectorCube.position() = NewPosition;
    if (m_selector->selectorCube.position().y < 0)
      m_selector->selectorCube.position().y = 0;
    this->refresh();
  }

  void CubeSelector::AddToSelector() {
    this->Create(m_selector->selectorCube);
  }

  void CubeSelector::DeleteToSelector() {
    this->Delete(m_selector->currentCube);
  }

  // TODO: make boundaries dynamic
  // TODO: Optimise rendering for large scenes
  /// @brief Generate the world using the current RBF
  void CubeSelector::ApplyRBF()
  {
    m_rbf.parseSelectedRBFFile();
    m_rbf.solveOmegas();
    for ( int x = -20; x < 20; x++ ) {
      for ( int z = -10; z < 10; z++ ) {
        for ( int y = 0; y < 10; y++ ) {
          glm::vec3 position(x, y, z);
          if ( m_rbf.isThereACubeHere(position) ) {
            form::Cube newCube(position, 1, m_selector->selectorCube.color(), m_selector->selectorCube.type(), m_selector->selectorCube.texture());
            this->Create(newCube);
          }
        }
      }
    }
  }

	void CubeSelector::MoveSelectorToClick(int x, int y, const FrameBuffer& framebufferSelection)
	{
		/* NOTE: check which FrameBuffer is currently bound
			 GLint drawFboId = 0, readFboId = 0;
			 glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFboId);
			 glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFboId);
		//std::cout << "checking current FBO. Draw:" << drawFboId << ", Read: " << readFboId << std::endl;
		*/
		framebufferSelection.Bind();
		GLuint data[4];
		framebufferSelection.getDataAtPosition4ui(x, y, data, GL_COLOR_ATTACHMENT0);
		// NOTE: Check if a cube has been selected
		if ( data[3] != 0 ) {
			form::Cube* selectionAddress;
			// NOTE: Rebuild the pointer address (64-bit) using two 32-bit values
			selectionAddress = (form::Cube*)( (intptr_t( data[0] ) << 32 & 0xFFFFFFFF00000000) | ( intptr_t( data[1] ) & 0xFFFFFFFF ) );

			this->SetSelector(glm::ivec3(selectionAddress->position()));
		}
		// NOTE: No cube is under the position so check the ground
		else {
			GLint position[4];
			framebufferSelection.getDataAtPosition4i(x, y, position, GL_COLOR_ATTACHMENT1);
			if ( position[3] != 0 ) this->SetSelector(glm::ivec3(position[0], 0, position[1]));
		}

    framebufferSelection.Unbind();        
	}
}
