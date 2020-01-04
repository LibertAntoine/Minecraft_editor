#include "Interface.h"

namespace interaction {
	Interface::Interface(std::shared_ptr<renderer::CubeRenderer> renderer, std::shared_ptr<interaction::CubeSelector> selector, std::shared_ptr<TextureArray> textureArray, std::shared_ptr<camera::FreeflyCamera> camera, std::shared_ptr<interaction::LightManager> light, std::shared_ptr<glm::vec3> backgroundColor)
		:m_cubeRenderer(renderer) , m_cubeSelector(selector), m_textureArray(textureArray), 
		m_camera(camera), m_light(light), m_backgroundColor(backgroundColor)
	{
	}

	Interface::~Interface() {
	}


	/* MENUS */
	void Interface::MainActionMenu() {
		ImGui::SetNextWindowSizeConstraints({ 200.0f,  (float)App::WINDOW_HEIGHT - 20 }, { 500.0f,  (float)App::WINDOW_HEIGHT - 20 });
		ImGui::Begin("ControllerWindow", &m_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
			m_actionMenuWitdh = ImGui::GetWindowWidth();
			ImGui::SetWindowPos(ImVec2((float)App::WINDOW_WIDTH - m_actionMenuWitdh, 20), true);

			if (ImGui::CollapsingHeader("World", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->WorldController();
			}

			if (ImGui::CollapsingHeader("Cube Action", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->CubeController();
			}

			if (ImGui::CollapsingHeader("Camera Controller", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->CameraController();
			}

			if (ImGui::CollapsingHeader("Grid Controller", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->GridController();
			}

			if (ImGui::CollapsingHeader("Light Controller", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->LightController();
			}
			if (ImGui::CollapsingHeader("RBF", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->RBFController(*m_cubeSelector);
			}
		ImGui::End();

		/* Activation KeyBoard Controllers */
			
		this->CameraKeyBoard();
		this->CubeKeyBoard();
		this->SelectorKeyBoard();
		
	}

	void Interface::MenuBarInterface() {

		if (ImGui::BeginMainMenuBar())
		{

			if (ImGui::BeginMenu("File"))
			{
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Edit"))
			{
				ImGui::Separator();
				if (ImGui::MenuItem("Cut", "CTRL+X")) {}
				if (ImGui::MenuItem("Copy", "CTRL+C")) {}
				if (ImGui::MenuItem("Paste", "CTRL+V")) {}
				ImGui::EndMenu();
			}
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::SameLine();
			ImGui::Text("SCROLL WHEEL for zooming in/out, hold on SHIFT to look, hold on SPACE for camera shifting. Z Q S D to move");
			ImGui::EndMainMenuBar();
		}
	}

	void Interface::MenuInfosInterface() {

		ImGui::SetNextWindowSizeConstraints({ (float)App::WINDOW_WIDTH - m_actionMenuWitdh,  100.0f }, { (float)App::WINDOW_WIDTH - m_actionMenuWitdh,  300.0f });
		ImGui::Begin("Selector Infos", &m_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(0, (float)App::WINDOW_HEIGHT - ImGui::GetWindowHeight()), true);

		ImGui::Columns(2, "Infos");
		this->InfosCurrentCubeInterface();
		ImGui::NextColumn();
		this->InfosSelectorInterface();
		ImGui::End();
	}

	/* CONTROLLERS */


	void Interface::WorldController() {
		float color[3] = {
			m_backgroundColor->x,
			m_backgroundColor->y,
			m_backgroundColor->z };
		ImGui::Text("BackGround Color");
		if (ImGui::ColorEdit3("##BackgroundColor", color)) {
			*m_backgroundColor = glm::vec3(color[0], color[1], color[2]);
		};
	}

	void Interface::RBFController(interaction::CubeSelector& cubeSelector) {
		if (ImGui::Button("Apply RBF")) cubeSelector.ApplyRBF();
                std::vector<std::string> filePaths;
                filePaths.push_back("res/rbf.txt");
                this->RBFFile(cubeSelector, "Select a RBF file");
	}

	void Interface::CubeController() {
		if (ImGui::Button("Add Cube")) m_cubeSelector->AddToSelector();
		ImGui::SameLine();
		if (ImGui::Button("Delete Cube")) m_cubeSelector->DeleteToSelector();
		if (ImGui::Button("Select")) m_cubeSelector->MoveIn();
		ImGui::SameLine();
		if (ImGui::Button("Move Selection")) m_cubeSelector->MoveOut();
		if (ImGui::Button("Extrude")) m_cubeSelector->Extrude();
		ImGui::SameLine();
		if (ImGui::Button("Dig")) m_cubeSelector->Dig();
	}


	void Interface::CameraController() {

		ImGui::Text("Cam Position :");
		// TODO Check if the value is not to high with the input.
		if (ImGui::DragFloat3("##DragCameraPosition", &m_camera->position().x, 0.1f, -m_cubeSelector->sizeWorld() / 2, m_cubeSelector->sizeWorld() / 2))
		{
			if (m_camera->position().y < 0)
				m_camera->position().y = 0;
		};

		ImGui::Text("Rotate Up-Down :");
		if (ImGui::DragFloat("##DragCamRotateUD", &m_camera->fTheta(), 0.03f, -m_cubeSelector->sizeWorld() / 2, m_cubeSelector->sizeWorld() / 2)) {
			m_camera->computeDirectionVectors();
		};


		ImGui::Text("Rotate Right-Left :");
		if (ImGui::DragFloat("##DragCamRotateLR", &m_camera->fPhi(), 0.03f, -m_cubeSelector->sizeWorld() / 2, m_cubeSelector->sizeWorld() / 2)) {
			m_camera->computeDirectionVectors();
		};


	}

	void Interface::GridController() {
		ImGui::Checkbox("Origin Grid x", &m_cubeSelector->activeGrid()[0]);
		ImGui::Checkbox("Origin Grid y", &m_cubeSelector->activeGrid()[1]);
		ImGui::Checkbox("Origin Grid z", &m_cubeSelector->activeGrid()[2]);
	}


	void Interface::LightController() 
	{
		int r = m_light->currentLight();
		if (ImGui::RadioButton("No Light##1", &r, interaction::lightStatus::NONE)) {
			m_light->currentLight() = interaction::lightStatus::NONE;
		};
		ImGui::SameLine();
		if (ImGui::RadioButton("Directionnal##1", &r, interaction::lightStatus::DIRECTIONNAL)) {
			m_light->currentLight() = interaction::lightStatus::DIRECTIONNAL;
		};
		ImGui::SameLine();
		if (ImGui::RadioButton("Ponctual##1", &r, interaction::lightStatus::PONCTUAL)) {
			m_light->currentLight() = interaction::lightStatus::PONCTUAL;
		};
		if (m_light->currentLight() == interaction::lightStatus::DIRECTIONNAL) {
			ImGui::Text("Directive Light Controller : ");
			ImGui::DragFloat3("uKs##DirLight", &m_light->dirLight().uKs.x, 0.01f, 0, 1);
			ImGui::DragFloat3("uKd##DirLight", &m_light->dirLight().uKd.x, 0.01f, 0, 1);
			ImGui::DragFloat3("Light Direction##DirLight", &m_light->direction().x, 0.01f, -1, 1);
			ImGui::DragFloat3("Light Intensity##DirLight", &m_light->dirLight().lightIntensity.x, 0.01f, 0, 100);
			ImGui::DragFloat("Shininess##DirLight", &m_light->dirLight().shininess, 0.01f, 0, 1000);
		} else if (m_light->currentLight() == interaction::lightStatus::PONCTUAL) {
			ImGui::Text("Ponctual Light Controller : ");
			ImGui::DragFloat3("uKs##PosLight", &m_light->pointLightList()[0].uKs.x, 0.01f, 0, 1);
			ImGui::DragFloat3("uKd##PosLight", &m_light->pointLightList()[0].uKd.x, 0.01f, 0, 1);
			ImGui::DragFloat3("Light Direction##PosLight", &m_light->position().x, 0.01f);
			ImGui::DragFloat3("Light Intensity##PosLight", &m_light->pointLightList()[0].lightIntensity.x, 0.01f, 0, 100);
			ImGui::DragFloat("Shininess##PosLight", &m_light->pointLightList()[0].shininess, 0.01f, 0, 1000);
		}
	}


	/* INFOS - SELECTOR CONTROLLERS */
	void Interface::InfosCurrentCubeInterface() {
		if (m_cubeSelector->currentCube() != nullptr) {
			ImGui::Text("Current cube selected infos : ");
			ImGui::InputInt("Scale Cube", m_cubeSelector->selector()->currentCube->scalePtr(), 1, 100);
			ImGui::Text("Cube Position : ");
			if (ImGui::DragInt3("##DragCubePosition", &m_cubeSelector->selectorCube().position().x, 1, -m_cubeSelector->sizeWorld() / 2, m_cubeSelector->sizeWorld() / 2)) {
				if (m_cubeSelector->selectorCube().position().y < 0) {
					m_cubeSelector->selectorCube().position().y = 0;
				}
					m_cubeSelector->Move(m_cubeSelector->currentCube(), m_cubeSelector->selectorCube().position());
			};
			int r = m_cubeSelector->currentCube()->type();
			ImGui::Text("Type : "); ImGui::SameLine();
			if (ImGui::RadioButton("Colored##1", &r, Forms::COLORED)) { 
				m_cubeSelector->currentCube()->type() = Forms::COLORED;
				m_cubeRenderer->updateType(); 
			}
			ImGui::SameLine();
			if (ImGui::RadioButton("Textured##1", &r, Forms::TEXTURED)) { 
				m_cubeSelector->currentCube()->type() = Forms::TEXTURED;
				m_cubeRenderer->updateType();
			}
				ImGui::SameLine();
			if (ImGui::RadioButton("Multi-textured##1", &r, Forms::MULTI_TEXTURED)) { 
				m_cubeSelector->currentCube()->type() = Forms::MULTI_TEXTURED;
				m_cubeRenderer->updateType();
			}

			if (r == Forms::COLORED) {
				static float color[3] = { m_cubeSelector->currentCube()->color().x,
				m_cubeSelector->currentCube()->color().y,
				m_cubeSelector->currentCube()->color().z, };
				if (ImGui::ColorEdit3("Color Cube", color)) {
					m_cubeSelector->currentCube()->Setcolor(glm::vec3(color[0], color[1], color[2]));
					m_cubeRenderer->updateColor();
				};
			}
			else if (r == Forms::TEXTURED) {
				this->ComboTexture(m_cubeSelector->currentCube()->texture(), "Cube Texture");
			} else if (r == Forms::MULTI_TEXTURED) {
				this->ComboMultiTexture(m_cubeSelector->currentCube()->texture(), "Cube Multi-Texture");
			}

		} else {
			ImGui::Text("No Cube Selected.");
		}
	}

	void Interface::InfosSelectorInterface() {
		ImGui::Text("Selector Infos : ");
		ImGui::InputInt("Selector Scale", &m_cubeSelector->selectorCube().scale(), 1, 100);
		ImGui::Text("Position : ");
		if (ImGui::DragInt3("##DragSelectorPosition", &m_cubeSelector->selectorCube().position().x, 1, -m_cubeSelector->sizeWorld() /2, m_cubeSelector->sizeWorld() /2)) {
			if (m_cubeSelector->selectorCube().position().y < 0)
				m_cubeSelector->selectorCube().position().y = 0;
			m_cubeSelector->refresh();
		};
		static int e = 0;
		ImGui::Text("Type : "); ImGui::SameLine();
		ImGui::RadioButton("Colored##2", &e, Forms::COLORED); ImGui::SameLine();
		ImGui::RadioButton("Textured##2", &e, Forms::TEXTURED); ImGui::SameLine();
		ImGui::RadioButton("Multi-textured##2", &e, Forms::MULTI_TEXTURED);
		if (e == Forms::COLORED) {
			m_cubeSelector->selectorCube().type() = Forms::COLORED;
			static float color[3] = { m_cubeSelector->selectorCube().color().x,
			m_cubeSelector->selectorCube().color().y,
			m_cubeSelector->selectorCube().color().z, };
			if (ImGui::ColorEdit3("Selector Color", color)) {
				m_cubeSelector->selectorCube().Setcolor(glm::vec3(color[0], color[1], color[2]));
			};
		} else if (e == Forms::TEXTURED) {
			m_cubeSelector->selectorCube().type() = Forms::TEXTURED;
			this->ComboTexture(m_cubeSelector->selectorCube().texture(), "Selector Texture");
		}
		else if (e == Forms::MULTI_TEXTURED) {
			m_cubeSelector->selectorCube().type() = Forms::MULTI_TEXTURED;
			this->ComboMultiTexture(m_cubeSelector->selectorCube().texture(), "Selector Multi-Texture");
		}	
	}

	/* KEYBOARD CONTROLLERS */
	void Interface::CameraKeyBoard() {
		if (ImGui::IsKeyDown(SDL_SCANCODE_LALT) || ImGui::IsKeyDown(SDL_SCANCODE_RALT)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				m_camera->moveFront(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				m_camera->moveFront(-1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				m_camera->moveUp(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				m_camera->moveUp(-1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				m_camera->moveLeft(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				m_camera->moveLeft(-1.f);
		}

		if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				m_camera->rotateUp(2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				m_camera->rotateUp(-2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				m_camera->rotateLeft(2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				m_camera->rotateLeft(-2.f);
		}
	}

	void Interface::CubeKeyBoard() {
		if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_I))
				m_cubeSelector->AddToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_O))
				m_cubeSelector->DeleteToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_X))
				m_cubeSelector->MoveIn();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_V))
				m_cubeSelector->MoveOut();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				m_cubeSelector->Extrude();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				m_cubeSelector->Dig();
		}
	}

	void Interface::SelectorKeyBoard() {
		if ((!ImGui::IsAnyWindowFocused() &&
			!(ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)))
			&& !(ImGui::IsKeyDown(SDL_SCANCODE_LALT) || ImGui::IsKeyDown(SDL_SCANCODE_RALT)))
		{
			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				m_cubeSelector->MoveSelector(glm::vec3(0, 1, 0));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				m_cubeSelector->MoveSelector(glm::vec3(0, -1, 0));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				m_cubeSelector->MoveSelector(glm::vec3(0, 0, -1));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				m_cubeSelector->MoveSelector(glm::vec3(0, 0, 1));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				m_cubeSelector->MoveSelector(glm::vec3(-1, 0, 0));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				m_cubeSelector->MoveSelector(glm::vec3(1, 0, 0));
		}	
	}

	/* ImGui WIDGETS */
	void Interface::ComboTexture(std::vector<unsigned int>& textures, const char* label) {
		ImVec2 combo_pos = ImGui::GetCursorScreenPos();
		if (ImGui::BeginCombo(label, "")) {
			for (size_t i = 0; i < m_textureArray->nameList().size(); ++i)
			{
				bool is_selected = (textures[0] == m_textureArray->give(m_textureArray->nameList()[i]));
				ImGui::Image((void*)(intptr_t)m_textureArray->giveProxi(m_textureArray->nameList()[i])->GetTexId(), ImVec2(20, 20));
				ImGui::SameLine();
				bool selectable = ImGui::Selectable(m_textureArray->nameList()[i].c_str(), is_selected);
				if (selectable) {
					textures[0] = m_textureArray->give(m_textureArray->nameList()[i]);
				}
				m_cubeRenderer->updateTexture();
				if (is_selected) {
					ImGui::SetItemDefaultFocus();
				}
			}
			ImGui::EndCombo();
		}
		ImGui::SetCursorScreenPos(ImVec2(combo_pos.x + 3, combo_pos.y + 3));
		float h = ImGui::GetTextLineHeight();
		ImGui::Image((void*)(intptr_t)m_textureArray->giveProxi(m_textureArray->nameList()[textures[0]])->GetTexId(), ImVec2(h, h));
		ImGui::SameLine();
		ImGui::TextUnformatted(m_textureArray->nameList()[textures[0]].c_str());
	}

	void Interface::RBFFile(interaction::CubeSelector& cubeSelector, const char* label) {
          // TODO: Optimize transFormss between strig to char pointers
          // Don't do it on every frame, maybe store it as is in class
          std::vector<char*> filePaths(cubeSelector.m_rbf.m_FilePaths.size() + 1);
          for ( size_t i = 0; i != cubeSelector.m_rbf.m_FilePaths.size(); ++i) {
            filePaths[i] = &cubeSelector.m_rbf.m_FilePaths[i][0];
          }

          ImGui::Combo(label, &cubeSelector.m_rbf.m_RBFFileId, filePaths.data(), cubeSelector.m_rbf.m_FilePaths.size());

	}
	void Interface::ComboMultiTexture(std::vector<unsigned int>& textures, const char* label) {
		const char* labels[6]{
			"Front Face", "Back Face",
			"Right Face", "Left Face",
			"Top Face", "Bottom Face",
		};
		ImGui::TextUnformatted(label);
		for (int j = 0; j < 6; ++j) {
			ImVec2 combo_pos = ImGui::GetCursorScreenPos();
			if (ImGui::BeginCombo(labels[j], "")) {
				for (size_t i = 0; i < m_textureArray->nameList().size(); ++i)
				{
					bool is_selected = (textures[j] == m_textureArray->give(m_textureArray->nameList()[i]));
					ImGui::Image((void*)(intptr_t)m_textureArray->giveProxi(m_textureArray->nameList()[i])->GetTexId(), ImVec2(20, 20));
					ImGui::SameLine();
					bool selectable = ImGui::Selectable(m_textureArray->nameList()[i].c_str(), is_selected);
					if (selectable) {
						textures[j] = m_textureArray->give(m_textureArray->nameList()[i]);
					}
					m_cubeRenderer->updateTexture();
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}
			ImGui::SetCursorScreenPos(ImVec2(combo_pos.x + 3, combo_pos.y + 3));
			float h = ImGui::GetTextLineHeight();
			ImGui::Image((void*)(intptr_t)m_textureArray->giveProxi(m_textureArray->nameList()[textures[j]])->GetTexId(), ImVec2(h, h));
			ImGui::SameLine();
			ImGui::TextUnformatted(m_textureArray->nameList()[textures[j]].c_str());
		}
	}

	bool Interface::DragIntSameLine(const int& nb, int* value, const int& step, const int& min, const int& max, const char* symbol) {

		bool value_changed = false;
		ImGui::BeginGroup();

		for (int i = 0; i < nb; i++)
		{
			value_changed |= ImGui::DragInt("##v", &value[i], step, min, max, symbol);

			ImGui::SameLine(0, -1.0f);
		}

		ImGui::EndGroup();
		return value_changed;
	}




}
