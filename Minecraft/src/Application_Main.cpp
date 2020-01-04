#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include <stdio.h>

#include <GL/glew.h>
#include <SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "App.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "modes/ModeEditor.h"
#include "modes/ModeImGUITest.h"

int main(int argc, char* args[])
{
 (void)argc;
 (void)args;


  App app;
  Renderer renderer;

  //Pass Auto in editor mode.
  modes::Mode* currentMode = new modes::ModeEditor;

  modes::ModeMenu* modeMenu = new modes::ModeMenu(currentMode);
  modeMenu->RegisterMode<modes::ModeEditor>("Cube");
  modeMenu->RegisterMode<modes::ModeImGUITest>("ImGUI Demo");


  /* Boucle principale */
  while (app.isRunning()) {
	  renderer.Clear();
	  app.beginFrame();
	  {
		  if (currentMode)
		  {
			  currentMode->OnUpdate(0.0f);
			  currentMode->OnRender();
			  SDL_Event e;
			  while (SDL_PollEvent(&e))
			  {
				  if (e.type == SDL_QUIT)
				  {
					  app.exit();
					  break;
				  }
				  currentMode->OnEvent(e);
				  ImGui_ImplSDL2_ProcessEvent(&e);
			  }
			  currentMode->OnImGuiRender();
		  }
		  ImGui::Render();
		  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		  app.endFrame();
	  }
  }
  if (currentMode != modeMenu) {
    delete modeMenu;
  }
  delete currentMode;
  return 0;
}
