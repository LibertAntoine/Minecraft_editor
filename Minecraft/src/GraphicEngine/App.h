#pragma once

/**
 * \file App.h
 * \brief Main - Manage the SDL, GLEW and ImGUI context and the program states.
 * \author Antoine Libert & Nicolas Lienart
 *
 */

#include "ImGUI/imgui.h"
#include "ImGUI/imgui_impl_sdl.h"
#include "ImGUI/imgui_impl_opengl3.h"

#include <GL/glew.h>
#include <SDL.h>
#include <GraphicEngine/Renderer.h>
#include <iostream>

/**
 * \brief Base root of the app
 */
class App {
public:
	// CONST RESOLUTION //
	static const unsigned int WINDOW_HEIGHT = 720;
	static const unsigned int WINDOW_WIDTH = 1080;

	App();
	~App();

	/**
	 * \brief Prepare for a new frame
	 * \note Must be called after handling SDL events
	 */
	void beginFrame() const;

	/**
	 * \brief Render the preparred frame
	 */
	void endFrame() const;

	/**
	* \brief say if the programm have to run yet.
	* \return true if program have to continue.
	*/
	bool isRunning() const;

	/**
	* \brief causes the program closure.
	*/
	void exit();

	// GETTERS - SETTERS //
	inline SDL_Window* window() const { return m_window; }
	inline SDL_GLContext glContext() const { return m_glContext; }
	inline const char* glsl_version() const { return m_glsl_version; }


private:

	/**
	* \brief Initialize the SDL Constext.
	*/
	void initSDL();

	/**
	* \brief Initialize the GLEW Constext.
	*/
	void initGlew();

	/**
	* \brief Initialize the ImGUI Constext.
	*/
	void initImGUI();

private:
	SDL_Window* m_window;
	SDL_GLContext m_glContext;
	static const char* m_glsl_version;
	static bool m_instanciated;
	bool m_running;
};
