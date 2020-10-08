#include "Interface.h"

namespace interaction {
	Interface::Interface(std::shared_ptr<renderer::CubeRenderer> renderer, std::shared_ptr<interaction::CubeSelector> selector, std::shared_ptr<TextureArray> textureArray, std::shared_ptr<camera::FreeflyCamera> camera, std::shared_ptr<interaction::LightManager> light, std::shared_ptr<glm::vec3> backgroundColor)
		:m_cubeRenderer(renderer) , m_cubeSelector(selector), m_textureArray(textureArray), 
		m_camera(camera), m_light(light), m_backgroundColor(backgroundColor)
	{
		this->findFiles();
	}

	Interface::~Interface() {
	}

	void Interface::findFiles()
	{
		#ifndef _WIN32
			std::string path = "res/scenes/";
			m_filePaths.clear();
			for (const auto & entry : std::filesystem::directory_iterator(path))
				m_filePaths.push_back(entry.path());
		#endif
	}


	/* MENUS */
	void Interface::MainActionMenu() {
		constexpr float height = (float)App::WINDOW_HEIGHT - 20 ;
		ImGui::SetNextWindowSizeConstraints({ 200.0f, height}, { 500.0f,  height });
		ImGui::Begin("ControllerWindow", &m_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
			m_actionMenuWitdh = ImGui::GetWindowWidth();
			ImGui::SetWindowPos(ImVec2((float)App::WINDOW_WIDTH - m_actionMenuWitdh, 20), true);

			if (ImGui::CollapsingHeader("World", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->WorldController();
			}
			if (ImGui::CollapsingHeader("RBF", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->RBFController();
			}
			if (ImGui::CollapsingHeader("Save Controller", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->SaveController();
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
		ImGui::End();

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
		if (ImGui::Button("Clean Scene")) {
			m_cubeSelector->DeleteAll();
		}
		if (ImGui::Button("Add ground")) {
			m_cubeSelector->initGround(10);
		}
	}


	void Interface::SaveController() {
		this->SceneFiles("Select scene");
		if (ImGui::Button("Load object")) m_cubeSelector->loadScene(m_filePaths[m_selectedFile]);
		ImGui::SameLine();
		if (ImGui::Button("Save object")) {
			m_cubeSelector->saveScene(m_newFile);
			this->findFiles();
		}
		#ifndef _WIN32
			char* newFile = m_newFile.data();
			ImGui::InputText("File Name", newFile, 20);
			m_newFile = std::string(newFile);
		#endif
	}


	void Interface::RBFController() {
		if (ImGui::Button("Apply RBF")) m_cubeSelector->ApplyRBF();
		ImGui::SameLine(); 
		if ( ImGui::Button("Refresh list") ) m_cubeSelector->getRBF().findRBFFiles();
		this->RBFFile(*m_cubeSelector, "Select a RBF file");
	}

	void Interface::CubeController() {
		if (ImGui::Button("Add Cube")) m_cubeSelector->AddToSelector();
		ImGui::SameLine();
		if (ImGui::Button("Delete Cube")) m_cubeSelector->DeleteToSelector();
		if (ImGui::Button("Cut")) m_cubeSelector->CutToSelector();
		ImGui::SameLine();
		if (ImGui::Button("Paste")) m_cubeSelector->PasteToSelector();
		if (ImGui::Button("Extrude")) m_cubeSelector->Extrude();
		ImGui::SameLine();
		if (ImGui::Button("Dig")) m_cubeSelector->Dig();
	}


	void Interface::CameraController() {

		ImGui::Text("Cam Position :");
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
			ImGui::InputInt("Scale Cube", m_cubeSelector->selector()->currentCube->scalePtr(), 1, 100);
		} else {
			ImGui::Text("No Cube Selected.");
		}
	}

	void Interface::InfosSelectorInterface() {
		ImGui::Text("Selector Infos : ");
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
		ImGui::InputInt("Selector Scale", &m_cubeSelector->selectorCube().scale(), 1, 100);
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
					RBF& rbf = cubeSelector.getRBF();
					std::vector<std::string> filepath_rbf = rbf.getFilePaths();
          std::vector<char*> filePaths(filepath_rbf.size() + 1);
          for ( size_t i = 0; i != filepath_rbf.size(); ++i) {
            filePaths[i] = &filepath_rbf[i][0];
          }

          ImGui::Combo(label, &rbf.CurrentFileIdAddress(), filePaths.data(), filepath_rbf.size());

	}
	void Interface::SceneFiles(const char* label) {
		std::vector<char*> filePaths(m_filePaths.size() + 1);
		for ( size_t i = 0; i != m_filePaths.size(); ++i) {
			filePaths[i] = &m_filePaths[i][0];
		}
		ImGui::Combo(label, &m_selectedFile, filePaths.data(), m_filePaths.size());
	}

	void Interface::ComboMultiTexture(std::vector<unsigned int>& textures, const char* label) {
		const char* labels[6]{
			"Front Face", "Right Face",
			"Back Face", "Bottom Face",
			"Left Face", "Top Face",
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
}
