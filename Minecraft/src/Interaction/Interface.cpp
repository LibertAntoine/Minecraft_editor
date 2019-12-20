#include "Interface.h"

namespace interaction {
	Interface::Interface() {
	}

	Interface::~Interface() {
	}

	void Interface::SelectorInterface(interaction::CubeSelector& cubeSelector) {
		ImGui::Begin("Selector Menu");
		if (ImGui::Button("Add Cube")) cubeSelector.AddToSelector();
		if (ImGui::Button("Delete Cube")) cubeSelector.DeleteToSelector();
		if (ImGui::Button("Select")) cubeSelector.MoveIn();
		if (ImGui::Button("Move Selection")) cubeSelector.MoveOut();
		if (ImGui::Button("Extrude")) cubeSelector.Extrude();
		if (ImGui::Button("Dig")) cubeSelector.Dig();
		ImGui::End();

		ImGui::Begin("Selector Move");
		if (ImGui::Button("MoveLeft")) cubeSelector.MoveSelector(glm::vec3(-1, 0, 0));
		if (ImGui::Button("MoveRight")) cubeSelector.MoveSelector(glm::vec3(1, 0, 0));
		if (ImGui::Button("MoveUp")) cubeSelector.MoveSelector(glm::vec3(0, 1, 0));
		if (ImGui::Button("MoveDown")) cubeSelector.MoveSelector(glm::vec3(0, -1, 0));
		if (ImGui::Button("MoveFront")) cubeSelector.MoveSelector(glm::vec3(0, 0, -1));
		if (ImGui::Button("MoveBack")) cubeSelector.MoveSelector(glm::vec3(0, 0, 1));
		ImGui::End();

		ImGui::Begin("Infos Selector");
		ImGui::Text("Selector Scale : ");
		ImGui::InputInt("scale", &cubeSelector.selector()->selectorScale, 1, 100);
		ImGui::Text("Selector Texture : ");
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
		ImGui::Text("Selector Position : ");
		if (ImGui::InputInt("x", &cubeSelector.selector()->selectorPosition.x, 1, 100) ||
			ImGui::InputInt("y", &cubeSelector.selector()->selectorPosition.y, 1, 100) ||
			ImGui::InputInt("z", &cubeSelector.selector()->selectorPosition.z, 1, 100)) {
			cubeSelector.refresh();
		};
		ImGui::End();

		if (!ImGui::IsAnyWindowFocused() && 
			!(ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)))
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

		if ((ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL))
			&& ImGui::IsKeyPressed(SDL_SCANCODE_I))
			cubeSelector.AddToSelector();

		if ((ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL))
			&& ImGui::IsKeyPressed(SDL_SCANCODE_O))
			cubeSelector.DeleteToSelector();

		if ((ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL))
			&& ImGui::IsKeyPressed(SDL_SCANCODE_X))
			cubeSelector.MoveIn();

		if ((ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL))
			&& ImGui::IsKeyPressed(SDL_SCANCODE_V))
			cubeSelector.MoveOut();

		if ((ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL))
			&& ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP)) {
			cubeSelector.MoveSelector(glm::vec3(0, 1, 0));
			cubeSelector.Extrude();
		}
		if ((ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL))
			&& ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN)) {
			cubeSelector.MoveSelector(glm::vec3(0, -1, 0));
			cubeSelector.Dig();
		}
	}
}