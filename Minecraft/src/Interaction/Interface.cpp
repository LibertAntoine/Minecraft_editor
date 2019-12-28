#include "Interface.h"

namespace interaction {
	Interface::Interface() {
	}

	Interface::~Interface() {
	}


	/* MENUS */
	void Interface::MainActionMenu(interaction::CubeSelector& cubeSelector, camera::FreeflyCamera& camera, interaction::LightManager& lightManager, glm::vec3& backgroundColor) {
		ImGui::SetNextWindowSizeConstraints({ 200.0f,  (float)WINDOW_HEIGHT - 20 }, { 500.0f,  (float)WINDOW_HEIGHT - 20 });
		ImGui::Begin("ControllerWindow", &m_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
			m_actionMenuWitdh = ImGui::GetWindowWidth();
			ImGui::SetWindowPos(ImVec2((float)WINDOW_WIDTH - m_actionMenuWitdh, 20), true);

			if (ImGui::CollapsingHeader("World", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->WorldController(backgroundColor);
			}

			if (ImGui::CollapsingHeader("Cube Action", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->CubeController(cubeSelector);
			}

			if (ImGui::CollapsingHeader("Camera Controller", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->CameraController(cubeSelector, camera);
			}

			if (ImGui::CollapsingHeader("Grid Controller", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->GridController(cubeSelector);
			}

			if (ImGui::CollapsingHeader("Light Controller", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->LightController(cubeSelector, lightManager);
			}
			if (ImGui::CollapsingHeader("RBF", ImGuiTreeNodeFlags_DefaultOpen)) {
				this->RBFController(cubeSelector);
			}
		ImGui::End();

		/* Activation KeyBoard Controllers */
			
		this->CameraKeyBoard(camera);
		this->CubeKeyBoard(cubeSelector);
		this->SelectorKeyBoard(cubeSelector);
		
	}

	void Interface::MenuBarInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector) {

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

	void Interface::MenuInfosInterface(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector) {

		ImGui::SetNextWindowSizeConstraints({ (float)WINDOW_WIDTH - m_actionMenuWitdh,  100.0f }, { (float)WINDOW_WIDTH - m_actionMenuWitdh,  300.0f });
		ImGui::Begin("Selector Infos", &m_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
		ImGui::SetWindowPos(ImVec2(0, (float)WINDOW_HEIGHT - ImGui::GetWindowHeight()), true);

		ImGui::Columns(2, "Infos");
		this->InfosCurrentCubeInterface(cubeSelector);
		ImGui::NextColumn();
		this->InfosSelectorInterface(cubeSelector);
		ImGui::End();
	}

	/* CONTROLLERS */


	void Interface::WorldController(glm::vec3& backgroundColor) {
		float color[3] = {
			backgroundColor.x,
			backgroundColor.y,
			backgroundColor.z };
		ImGui::Text("BackGround Color");
		if (ImGui::ColorEdit3("##BackgroundColor", color)) {
			backgroundColor = glm::vec3(color[0], color[1], color[2]);
		};
	}

	void Interface::RBFController(interaction::CubeSelector& cubeSelector) {
		if (ImGui::Button("Apply RBF")) cubeSelector.ApplyRBF();
                std::vector<std::string> filePaths;
                filePaths.push_back("res/rbf.txt");
                this->RBFFile(cubeSelector, "Select a RBF file");
	}

	void Interface::CubeController(interaction::CubeSelector& cubeSelector) {
		if (ImGui::Button("Add Cube")) cubeSelector.AddToSelector();
		ImGui::SameLine();
		if (ImGui::Button("Delete Cube")) cubeSelector.DeleteToSelector();
		if (ImGui::Button("Select")) cubeSelector.MoveIn();
		ImGui::SameLine();
		if (ImGui::Button("Move Selection")) cubeSelector.MoveOut();
		if (ImGui::Button("Extrude")) cubeSelector.Extrude();
		ImGui::SameLine();
		if (ImGui::Button("Dig")) cubeSelector.Dig();
	}


	void Interface::CameraController(interaction::CubeSelector& cubeSelector, camera::FreeflyCamera& Camera) {

		ImGui::Text("Cam Position :");
		// TODO Check if the value is not to high with the input.
		if (ImGui::DragFloat3("##DragCameraPosition", &Camera.position().x, 0.1f, -cubeSelector.sizeWorld() / 2, cubeSelector.sizeWorld() / 2))
		{
			if (Camera.position().y < 0)
				Camera.position().y = 0;
		};

		ImGui::Text("Rotate Up-Down :");
		if (ImGui::DragFloat("##DragCamRotateUD", &Camera.fTheta(), 0.03f, -cubeSelector.sizeWorld() / 2, cubeSelector.sizeWorld() / 2)) {
			Camera.computeDirectionVectors();
		};


		ImGui::Text("Rotate Right-Left :");
		if (ImGui::DragFloat("##DragCamRotateLR", &Camera.fPhi(), 0.03f, -cubeSelector.sizeWorld() / 2, cubeSelector.sizeWorld() / 2)) {
			Camera.computeDirectionVectors();
		};


	}

	void Interface::GridController(interaction::CubeSelector& cubeSelector) {
		ImGui::Checkbox("Origin Grid x", &cubeSelector.activeGrid()[0]);
		ImGui::Checkbox("Origin Grid y", &cubeSelector.activeGrid()[1]);
		ImGui::Checkbox("Origin Grid z", &cubeSelector.activeGrid()[2]);
	}


	void Interface::LightController(interaction::CubeSelector& cubeSelector, interaction::LightManager& lightManager) {
		ImGui::Text("Directive Light Controller : ");
		ImGui::DragFloat3("uKs", &lightManager.dirLight().uKs.x, 0.01f);
		ImGui::DragFloat3("uKd", &lightManager.dirLight().uKd.x, 0.01f);
		ImGui::DragFloat3("Light Direction", &lightManager.dirLight().lightDirection.x, 0.01f);
		ImGui::DragFloat3("Light Intensity", &lightManager.dirLight().lightIntensity.x, 0.01f);
		ImGui::DragFloat("Shininess", &lightManager.dirLight().shininess, 0.01f);

	}


	/* INFOS - SELECTOR CONTROLLERS */
	void Interface::InfosCurrentCubeInterface(interaction::CubeSelector& cubeSelector) {
		if (cubeSelector.currentCube() != nullptr) {
			ImGui::Text("Current cube selected infos : ");
			ImGui::InputInt("Scale Cube", cubeSelector.selector()->currentCube->scalePtr(), 1, 100);
			ImGui::Text("Cube Position : ");
			if (ImGui::DragInt3("##DragCubePosition", &cubeSelector.selectorCube().position().x, 1, -cubeSelector.sizeWorld() / 2, cubeSelector.sizeWorld() / 2)) {
				if (cubeSelector.selectorCube().position().y < 0) 
					cubeSelector.selectorCube().position().y = 0;
				cubeSelector.Move(cubeSelector.currentCube(), cubeSelector.selectorCube().position());
			};
			int r = cubeSelector.currentCube()->type();
			ImGui::Text("Type : "); ImGui::SameLine();
			ImGui::RadioButton("Colored##1", &r, form::COLORED); ImGui::SameLine();
			ImGui::RadioButton("Textured##1", &r, form::TEXTURED); ImGui::SameLine();
			ImGui::RadioButton("Multi-textured##1", &r, form::MULTI_TEXTURED);
			if (r == form::COLORED) {
				cubeSelector.currentCube()->type() = form::COLORED;
				static float color[3] = { cubeSelector.currentCube()->color().x,
				cubeSelector.currentCube()->color().y,
				cubeSelector.currentCube()->color().z, };
				if (ImGui::ColorEdit3("Color Cube", color)) {
					cubeSelector.currentCube()->Setcolor(glm::vec3(color[0], color[1], color[2]));
				};
			}
			else if (r == form::TEXTURED) {
				cubeSelector.currentCube()->type() = form::TEXTURED;
				this->ComboTexture(cubeSelector, cubeSelector.currentCube()->texture(), "Cube Texture");
			} else if (r == form::MULTI_TEXTURED) {
				cubeSelector.currentCube()->type() = form::MULTI_TEXTURED;
				this->ComboMultiTexture(cubeSelector, cubeSelector.currentCube()->texture(), "Cube Multi-Texture");
			}

		} else {
			ImGui::Text("No Cube Selected.");
		}
	}

	void Interface::InfosSelectorInterface(interaction::CubeSelector& cubeSelector) {
		ImGui::Text("Selector Infos : ");
		ImGui::InputInt("Selector Scale", &cubeSelector.selectorCube().scale(), 1, 100);
		ImGui::Text("Position : ");
		if (ImGui::DragInt3("##DragSelectorPosition", &cubeSelector.selectorCube().position().x, 1, -cubeSelector.sizeWorld() /2, cubeSelector.sizeWorld() /2)) {
			if (cubeSelector.selectorCube().position().y < 0)
				cubeSelector.selectorCube().position().y = 0;
			cubeSelector.refresh();
		};
		static int e = 0;
		ImGui::Text("Type : "); ImGui::SameLine();
		ImGui::RadioButton("Colored##2", &e, form::COLORED); ImGui::SameLine();
		ImGui::RadioButton("Textured##2", &e, form::TEXTURED); ImGui::SameLine();
		ImGui::RadioButton("Multi-textured##2", &e, form::MULTI_TEXTURED);
		if (e == form::COLORED) {
			cubeSelector.selectorCube().type() = form::COLORED;
			static float color[3] = { cubeSelector.selectorCube().color().x,
			cubeSelector.selectorCube().color().y,
			cubeSelector.selectorCube().color().z, };
			if (ImGui::ColorEdit3("Selector Color", color)) {
				cubeSelector.selectorCube().Setcolor(glm::vec3(color[0], color[1], color[2]));
			};
		} else if (e == form::TEXTURED) {
			cubeSelector.selectorCube().type() = form::TEXTURED;
			this->ComboTexture(cubeSelector, cubeSelector.selectorCube().texture(), "Selector Texture");
		}
		else if (e == form::MULTI_TEXTURED) {
			cubeSelector.selectorCube().type() = form::MULTI_TEXTURED;
			this->ComboMultiTexture(cubeSelector, cubeSelector.selectorCube().texture(), "Selector Multi-Texture");
		}	
	}

	/* KEYBOARD CONTROLLERS */
	void Interface::CameraKeyBoard(camera::FreeflyCamera& camera) {
		if (ImGui::IsKeyDown(SDL_SCANCODE_LALT) || ImGui::IsKeyDown(SDL_SCANCODE_RALT)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				camera.moveFront(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				camera.moveFront(-1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				camera.moveUp(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				camera.moveUp(-1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				camera.moveLeft(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				camera.moveLeft(-1.f);
		}

		if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				camera.rotateUp(2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				camera.rotateUp(-2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				camera.rotateLeft(2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				camera.rotateLeft(-2.f);
		}
	}

	void Interface::CubeKeyBoard(interaction::CubeSelector& cubeSelector) {
		if ((!ImGui::IsAnyWindowFocused() &&
			!(ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)))
			&& !(ImGui::IsKeyDown(SDL_SCANCODE_LALT) || ImGui::IsKeyDown(SDL_SCANCODE_RALT)))
		{
			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				cubeSelector.MoveSelector(glm::vec3(0, 1, 0));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				cubeSelector.MoveSelector(glm::vec3(0, -1, 0));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				cubeSelector.MoveSelector(glm::vec3(0, 0, -1));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				cubeSelector.MoveSelector(glm::vec3(0, 0, 1));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				cubeSelector.MoveSelector(glm::vec3(-1, 0, 0));

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				cubeSelector.MoveSelector(glm::vec3(1, 0, 0));
		}
	}

	void Interface::SelectorKeyBoard(interaction::CubeSelector& cubeSelector) {
		if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_I))
				cubeSelector.AddToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_O))
				cubeSelector.DeleteToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_X))
				cubeSelector.MoveIn();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_V))
				cubeSelector.MoveOut();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				cubeSelector.Extrude();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				cubeSelector.Dig();
		}
	}

	/* ImGui WIDGETS */
	void Interface::ComboTexture(interaction::CubeSelector& cubeSelector, std::vector<Texture*>& textures, const char* label) {
		ImVec2 combo_pos = ImGui::GetCursorScreenPos();
		if (ImGui::BeginCombo(label, "")) {
			for (int i = 0; i < cubeSelector.textureList()->nameList().size(); ++i)
			{
				bool is_selected = (textures[0]->name() == cubeSelector.textureList()->nameList()[i]);
				ImGui::Image((void*)(intptr_t)cubeSelector.textureList()->give(cubeSelector.textureList()->nameList()[i])->GetTexId(), ImVec2(20, 20));
				ImGui::SameLine();
				bool selectable = ImGui::Selectable(cubeSelector.textureList()->nameList()[i].c_str(), is_selected);
				if (selectable)
					textures[0] = cubeSelector.textureList()->give(cubeSelector.textureList()->nameList()[i]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::SetCursorScreenPos(ImVec2(combo_pos.x + 3, combo_pos.y + 3));
		float h = ImGui::GetTextLineHeight();
		ImGui::Image((void*)(intptr_t)textures[0]->GetTexId(), ImVec2(h, h));
		ImGui::SameLine();
		ImGui::Text(textures[0]->name().c_str());
	}

	void Interface::RBFFile(interaction::CubeSelector& cubeSelector, const char* label) {
          // TODO: Optimize transforms between strig to char pointers
          // Don't do it on every frame, maybe store it as is in class
          std::vector<char*> filePaths(cubeSelector.m_rbf.m_FilePaths.size() + 1);
          for ( size_t i = 0; i != cubeSelector.m_rbf.m_FilePaths.size(); ++i) {
            filePaths[i] = &cubeSelector.m_rbf.m_FilePaths[i][0];
          }

          ImGui::Combo(label, &cubeSelector.m_rbf.m_RBFFileId, filePaths.data(), cubeSelector.m_rbf.m_FilePaths.size());

	}

	void Interface::ComboMultiTexture(interaction::CubeSelector& cubeSelector, std::vector<Texture*>& textures, const char* label) {
		const char* labels[6]{
			"Front Face", "Back Face",
			"Right Face", "Left Face",
			"Top Face", "Bottom Face",
		};
		ImGui::Text(label);
		for (int j = 0; j < 6; ++j) {
			ImVec2 combo_pos = ImGui::GetCursorScreenPos();
			if (ImGui::BeginCombo(labels[j], "")) {
				for (int i = 0; i < cubeSelector.textureList()->nameList().size(); ++i)
				{
					bool is_selected = (textures[j]->name() == cubeSelector.textureList()->nameList()[i]);
					ImGui::Image((void*)(intptr_t)cubeSelector.textureList()->give(cubeSelector.textureList()->nameList()[i])->GetTexId(), ImVec2(20, 20));
					ImGui::SameLine();
					bool selectable = ImGui::Selectable(cubeSelector.textureList()->nameList()[i].c_str(), is_selected);
					if (selectable)
						textures[j] = cubeSelector.textureList()->give(cubeSelector.textureList()->nameList()[i]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::SetCursorScreenPos(ImVec2(combo_pos.x + 3, combo_pos.y + 3));
			float h = ImGui::GetTextLineHeight();
			ImGui::Image((void*)(intptr_t)textures[j]->GetTexId(), ImVec2(h, h));
			ImGui::SameLine();
			ImGui::Text(textures[j]->name().c_str());
		}
	}

	bool Interface::DragIntSameLine(const char* label, const int& nb, int* value, const int& step, const int& min, const int& max, const char* symbol) {

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
