#include "App.h"


bool App::m_instanciated = false;
const char* App::m_glsl_version = "#version 130";



App::App() {
	m_instanciated = true;

	initSDL();
	initGlew();
	initImGUI();
	glEnable(GL_DEPTH_TEST);
	std::cout << "OpenGL Version : " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLEW Version : " << glewGetString(GLEW_VERSION) << std::endl;
	m_running = true;
}

App::~App() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	SDL_GL_DeleteContext(m_glContext);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void App::beginFrame() const {
	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_window);
	ImGui::NewFrame();
}

void App::endFrame() const {
	SDL_GL_SwapWindow(m_window);
}



bool App::isRunning() const { return m_running; }
void App::exit() { m_running = false; }


void App::initSDL() {
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		std::cerr << "Can't init SDL : " << SDL_GetError() << std::endl;
	}

	// Use OpenGL 3.3
	SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	// Various attributes
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	// Create Window
	m_window = SDL_CreateWindow("Minecraft Editor",
		SDL_WINDOWPOS_CENTERED,           // initial x position
		SDL_WINDOWPOS_CENTERED,           // initial y position
		WINDOW_WIDTH,                               // width, in pixels
		WINDOW_HEIGHT,                               // height, in pixels
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL                  // flags - see below
	);

	if (m_window == nullptr) {
		std::cerr << "Could not create window: " << SDL_GetError() << std::endl;
	}

	m_glContext = SDL_GL_CreateContext(m_window);
	if (m_glContext == nullptr) {
		std::cerr << "Unable to create GL context:" << SDL_GetError() << std::endl;
	}

	SDL_GL_MakeCurrent(m_window, m_glContext);
	SDL_GL_SetSwapInterval(1); // Enable vsync

}

void App::initGlew() {
	const auto result = glewInit();
	if (result != GLEW_OK)
	{
		const auto* error = glewGetErrorString(result);
		std::cout << "Error glew init: " << error << std::endl;
	}
}


void App::initImGUI() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
	ImGui::StyleColorsDark();
	io.Fonts->AddFontFromFileTTF("res/fonts/Lato/Lato-Medium.ttf", 15);
	ImGui_ImplSDL2_InitForOpenGL(m_window, m_glContext);
	ImGui_ImplOpenGL3_Init(m_glsl_version);

	ImGui::PushStyleColor(ImGuiCol_ResizeGrip, 0);
	ImGui::PushStyleColor(ImGuiCol_ResizeGripActive, 0); 
	ImGui::PushStyleColor(ImGuiCol_ResizeGripHovered, 0); 
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 0.f);
}
