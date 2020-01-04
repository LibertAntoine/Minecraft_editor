/**
 * \file Application_Main.cpp
 * \brief Main - launching the main loop
 * \author Antoine Libert & Nicolas Lienart
 * Call the differents mode which compose the application and launch the main loop.
 *
 */

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include <iostream>
#include <GL/glew.h>
#include <SDL.h>

#include "App.h"
#include "GraphicEngine/Renderer.h"

#include "Modes/ModeEditor.h"
#include "Modes/ModeImGUITest.h"

int main(int argc, char* args[])
{
 (void)argc;
 (void)args;

  App app;
  Renderer renderer;

  //Pass Auto in editor mode.
  Modes::Mode* currentMode = new Modes::ModeEditor;

  Modes::ModeMenu* modeMenu = new Modes::ModeMenu(currentMode);
  modeMenu->RegisterMode<Modes::ModeEditor>("Cube");
  modeMenu->RegisterMode<Modes::ModeImGUITest>("ImGUI Demo");


  /* Main loop */
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

  //Closing of the program
  if (currentMode != modeMenu) {
    delete modeMenu;
  }
  delete currentMode;
  return 0;
}
