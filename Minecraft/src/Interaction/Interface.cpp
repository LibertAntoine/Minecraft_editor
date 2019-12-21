#include "Interface.h"

namespace interaction {
	Interface::Interface() {
	}

	Interface::~Interface() {
	}

	void Interface::MainActionMenu(camera::FreeflyCamera& Camera, interaction::CubeSelector& cubeSelector) {
		ImGui::SetNextWindowSizeConstraints({ 200.0f,  (float)WINDOW_HEIGHT }, { 500.0f,  (float)WINDOW_HEIGHT });
		ImGui::Begin("Test", &m_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar);
		m_actionMenuWitdh = ImGui::GetWindowWidth();
		ImGui::SetWindowPos(ImVec2((float)WINDOW_WIDTH - m_actionMenuWitdh, 18), true);

		
		this->CameraInterface(Camera);

		if (ImGui::Button("Add Cube")) cubeSelector.AddToSelector();
		if (ImGui::Button("Delete Cube")) cubeSelector.DeleteToSelector();
		if (ImGui::Button("Select")) cubeSelector.MoveIn();
		if (ImGui::Button("Move Selection")) cubeSelector.MoveOut();
		if (ImGui::Button("Extrude")) cubeSelector.Extrude();
		if (ImGui::Button("Dig")) cubeSelector.Dig();



		if (ImGui::Button("MoveLeft")) cubeSelector.MoveSelector(glm::vec3(-1, 0, 0));
		if (ImGui::Button("MoveRight")) cubeSelector.MoveSelector(glm::vec3(1, 0, 0));
		if (ImGui::Button("MoveUp")) cubeSelector.MoveSelector(glm::vec3(0, 1, 0));
		if (ImGui::Button("MoveDown")) cubeSelector.MoveSelector(glm::vec3(0, -1, 0));
		if (ImGui::Button("MoveFront")) cubeSelector.MoveSelector(glm::vec3(0, 0, -1));
		if (ImGui::Button("MoveBack")) cubeSelector.MoveSelector(glm::vec3(0, 0, 1));


		

		ImGui::End();

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

	void Interface::CameraInterface(camera::FreeflyCamera& Camera) {

		if (ImGui::Button("RotateUp")) Camera.rotateUp(1.f);
		if (ImGui::Button("RotateDown")) Camera.rotateUp(-1.f);
		if (ImGui::Button("RotateLeft")) Camera.rotateLeft(1.f);
		if (ImGui::Button("RotateRight")) Camera.rotateLeft(-1.f);
		if (ImGui::Button("ZoomIn")) Camera.moveFront(1.f);
		if (ImGui::Button("ZoomOut")) Camera.moveFront(-1.f);
		if (ImGui::Button("MoveLeft")) Camera.moveLeft(1.f);
		if (ImGui::Button("MoveRight")) Camera.moveLeft(-1.f);
		if (ImGui::Button("MoveUp")) Camera.moveUp(1.f);
		if (ImGui::Button("MoveDown")) Camera.moveUp(-1.f);

		if (ImGui::IsKeyDown(SDL_SCANCODE_LALT) || ImGui::IsKeyDown(SDL_SCANCODE_RALT)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				Camera.moveFront(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				Camera.moveFront(-1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				Camera.moveUp(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				Camera.moveUp(-1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				Camera.moveLeft(1.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				Camera.moveLeft(-1.f);
		}

		if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_UP))
				Camera.rotateUp(2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_DOWN))
				Camera.rotateUp(-2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_LEFT))
				Camera.rotateLeft(2.f);

			if (ImGui::IsKeyPressed(SDL_SCANCODE_RIGHT))
				Camera.rotateLeft(-2.f);
		}
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
		ImGui::Begin("Selector Infos", &m_open, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
		ImGui::SetWindowPos(ImVec2(0, (float)WINDOW_HEIGHT - ImGui::GetWindowHeight()), true);

		ImGui::Columns(2, "Infos");
		this->InfosSelectorInterface(cubeSelector);
		ImGui::NextColumn();
		this->InfosCurrentCubeInterface(cubeSelector);

		ImGui::End();
	}


	void Interface::InfosCurrentCubeInterface(interaction::CubeSelector& cubeSelector) {
		if (cubeSelector.selector()->currentCube != nullptr) {
			ImGui::Text("Current cube selected infos : ");
			ImGui::Text("Cube Scale : ");
			ImGui::InputInt("scalec", cubeSelector.selector()->currentCube->scalePtr(), 1, 100);
			if (cubeSelector.selector()->currentCube->texture() != nullptr) {
				ImGui::Text("Cube Texture : ");
				ImGui::Text(cubeSelector.selector()->currentCube->texture()->name().c_str());
				if (ImGui::BeginCombo("Texture Cube", cubeSelector.selector()->currentCube->texture()->name().c_str())) {
					for (int i = 0; i < cubeSelector.textureList()->nameList().size(); ++i)
					{
						bool is_selected = (cubeSelector.selector()->currentCube->texture()->name() == cubeSelector.textureList()->nameList()[i]);
						if (ImGui::Selectable(cubeSelector.textureList()->nameList()[i].c_str(), is_selected))
							cubeSelector.selector()->currentCube->texture(cubeSelector.textureList()->give(cubeSelector.textureList()->nameList()[i]));
						if (is_selected)
							ImGui::SetItemDefaultFocus();
					}
					ImGui::EndCombo();
				}
			}
			else {
				ImGui::Text("Cube Color : ");
				float r = cubeSelector.selector()->currentCube->color().x;
				float g = cubeSelector.selector()->currentCube->color().y;
				float b = cubeSelector.selector()->currentCube->color().z;
				if (ImGui::InputFloat("r", &r, 0.01f, 0.1f, "%.3f") || ImGui::InputFloat("g", &g, 0.01f, 0.1f, "%.3f") || ImGui::InputFloat("b", &b, 0.01f, 0.1f, "%.3f")) {
					cubeSelector.selector()->currentCube->Setcolor(glm::vec3(r, g, b));
				};
			}

			ImGui::Text("Cube Position : ");
			int xc = cubeSelector.selector()->currentCube->position().x;
			int yc = cubeSelector.selector()->currentCube->position().y;
			int zc = cubeSelector.selector()->currentCube->position().z;
			if (ImGui::InputInt("x", &xc, 1, 100) || ImGui::InputInt("y", &yc, 1, 100) || ImGui::InputInt("z", &zc, 1, 100)) {
				cubeSelector.selector()->selectorPosition = glm::vec3(xc, yc, zc);
				cubeSelector.Move(cubeSelector.selector()->currentCube, glm::vec3(xc, yc, zc));
			};
		}
		else {
			ImGui::Text("No Cube Selected.");
		}
	}


	void Interface::InfosSelectorInterface(interaction::CubeSelector& cubeSelector) {
		ImGui::Text("Selector Infos : ");
		ImGui::InputInt("scale", &cubeSelector.selector()->selectorScale, 1, 100);
		static std::string current_texture = cubeSelector.selector()->selectorTexture->name();
		if (ImGui::BeginCombo("Texture Selector", cubeSelector.selector()->selectorTexture->name().c_str())) {
			for (int i = 0; i < cubeSelector.textureList()->nameList().size(); ++i)
			{
				bool is_selected = (cubeSelector.selector()->selectorTexture->name() == cubeSelector.textureList()->nameList()[i]);
				if (ImGui::Selectable(cubeSelector.textureList()->nameList()[i].c_str(), is_selected))
					cubeSelector.selector()->selectorTexture = cubeSelector.textureList()->give(cubeSelector.textureList()->nameList()[i]);
				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}
		ImGui::Text("Position : ");
		if (ImGui::InputInt("x", &cubeSelector.selector()->selectorPosition.x, 1, 100) ||
			ImGui::InputInt("y", &cubeSelector.selector()->selectorPosition.y, 1, 100) ||
			ImGui::InputInt("z", &cubeSelector.selector()->selectorPosition.z, 1, 100)) {
			cubeSelector.refresh();
		};
	}

}