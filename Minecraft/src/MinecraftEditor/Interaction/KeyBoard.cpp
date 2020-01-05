#include "KeyBoard.h"

namespace interaction {

	KeyBoard::KeyBoard(std::shared_ptr<renderer::CubeRenderer> cubeRenderer, std::shared_ptr<interaction::CubeSelector> selector, std::shared_ptr<camera::FreeflyCamera> camera, FrameBuffer* frameBufferSelection)
		: m_cubeRenderer(cubeRenderer), m_cubeSelector(selector), m_camera(camera), m_frameBufferSelection(frameBufferSelection)
	{
	}

	KeyBoard::~KeyBoard(){

	}

	void KeyBoard::CameraShortCut() {
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

	void KeyBoard::CubeShortCut() {
		if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
			if (ImGui::IsKeyPressed(SDL_SCANCODE_I))
				m_cubeSelector->AddToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_O))
				m_cubeSelector->DeleteToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_X))
				m_cubeSelector->CutToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_V))
				m_cubeSelector->PasteToSelector();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEUP))
				m_cubeSelector->Extrude();

			if (ImGui::IsKeyPressed(SDL_SCANCODE_PAGEDOWN))
				m_cubeSelector->Dig();
		}
	}

	void KeyBoard::SelectorShortCut() {
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

	void KeyBoard::MouseShortCut() {
		if (!ImGui::IsAnyWindowHovered() && !ImGui::IsAnyWindowFocused()) {
			
			if (ImGui::IsMouseClicked(1) || ImGui::IsMouseDragging(1)) {
				m_cubeSelector->MoveSelectorToClick(ImGui::GetMousePos().x, App::WINDOW_HEIGHT - ImGui::GetMousePos().y - 1, *m_frameBufferSelection);
				if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
					if ((abs(ImGui::GetMouseDragDelta(1).x) > 6 || abs(ImGui::GetMouseDragDelta(1).y) > 6) || ImGui::IsMouseClicked(1)) {
					m_cubeSelector->DeleteToSelector();
					ImGui::ResetMouseDragDelta(1);
					}
				}
			}
			else if (ImGui::IsMouseDragging(0) || ImGui::IsMouseClicked(0)) {
				m_cubeSelector->MoveSelectorToClick(ImGui::GetMousePos().x, App::WINDOW_HEIGHT - ImGui::GetMousePos().y - 1, *m_frameBufferSelection);
				if (ImGui::IsKeyDown(SDL_SCANCODE_LALT) || ImGui::IsKeyDown(SDL_SCANCODE_RALT)) {
					if (!(ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL))) {
						m_cubeSelector->MoveSelectorToClickFace(ImGui::GetMousePos().x, App::WINDOW_HEIGHT - ImGui::GetMousePos().y - 1, *m_frameBufferSelection);
					}
					if ((abs(ImGui::GetMouseDragDelta(0).x) > 6 || abs(ImGui::GetMouseDragDelta(0).y) > 6) || ImGui::IsMouseClicked(0)) {
						m_cubeSelector->AddToSelector();
						ImGui::ResetMouseDragDelta(0);
					}
				}
				if (ImGui::IsKeyDown(SDL_SCANCODE_LCTRL) || ImGui::IsKeyDown(SDL_SCANCODE_RCTRL)) {
					m_cubeSelector->MoveSelectorToClick(ImGui::GetMousePos().x, App::WINDOW_HEIGHT - ImGui::GetMousePos().y - 1, *m_frameBufferSelection);
					if (m_cubeSelector->currentCube()) {
						Forms::CubeType cubeStyle = m_cubeSelector->selectorCube().type();
						if (m_cubeSelector->currentCube()->type() != cubeStyle) {
							m_cubeSelector->currentCube()->type() = cubeStyle;
							m_cubeRenderer->updateType();
						}
						if (cubeStyle == Forms::COLORED) {
							m_cubeSelector->currentCube()->Setcolor(glm::vec3(m_cubeSelector->selectorCube().color()));
							m_cubeRenderer->updateColor();
						}
						else if (cubeStyle == Forms::TEXTURED) {
							m_cubeSelector->currentCube()->texture() = m_cubeSelector->selectorCube().texture();
							m_cubeRenderer->updateTexture();
						}
						else if (cubeStyle == Forms::MULTI_TEXTURED) {
							m_cubeSelector->currentCube()->texture() = m_cubeSelector->selectorCube().texture();
							m_cubeRenderer->updateTexture();
						}
						// TODO: check if necessary
						//m_CubeSelector->refresh();
					}
				}
			}
		}

	}



}


