#include "ModeEditor.h"
#include <stdint.h>
#include "ImGUI/imgui.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <SDL.h>
#include <string>
#include "stb_image/stb_image.h"

namespace modes {

    ModeEditor::ModeEditor()
    :m_ProjMatrix(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)),
    m_GridRenderer(200, glm::vec3(0.5f, 0.5f, 0.5f)), m_CubeRenderer(),
    m_textureArray(32, 32),
    m_CubeSelector(m_CubeRenderer, m_textureArray, 2048), // Obligatoirement une puissance de deux.
    m_backgroundColor(0.3f, 0.3f, 0.3f),
    m_GroundSelectionRenderer(200),
    m_Interface(m_CubeRenderer, m_CubeSelector, m_textureArray, m_FreeCam, m_LightManager, m_backgroundColor)
  {
    constexpr float fov = glm::radians(70.f);
    float ratio = 1080. / 720.;
    m_ProjMatrix = glm::perspective(fov, ratio, 0.1f, 100.f);


    m_textureArray.AddTexture("res/textures/Cube/log_acacia_top.png", "res/textures/Cube/log_acacia_top_proxi.png");
    m_textureArray.AddTexture("res/textures/Cube/piston_bottom.png", "res/textures/Cube/piston_bottom_proxi.png");
    m_textureArray.AddTexture("res/textures/Cube/lava_placeholder.png", "res/textures/Cube/lava_placeholder_proxi.png");
    
    /*
    int Width;
    int Height;
    int BPP;


    unsigned char* LocalBuffer = stbi_load("res/textures/blocks/log_acacia_top.png", &Width, &Height, &BPP, 4);


    GLCall(glGenTextures(1, &m_textureArray));
    GLCall(glActiveTexture(GL_TEXTURE0));
    GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArray));
    GLCall(glTexStorage3D(GL_TEXTURE_2D_ARRAY,
        1,                    //5 mipmaps
        GL_RGBA8,               //Internal format
        Width, Height,           //width,height
        4                  //Number of layers
    ));

    GLubyte color[3] = { 0, 0,255};
    



   
    GLCall(glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
        0,                      //Mipmap number
        0, 0, 0, //xoffset, yoffset, zoffset
        Width , Height , 1,          //width, height, depth
        GL_RGBA,                 //format
        GL_UNSIGNED_BYTE,       //type
        LocalBuffer)); //pointer to data

    GLubyte color2[12] = { 255, 0, 0,  255, 0, 0, 255, 0, 0, 255, 0, 0, };

    GLCall(glTexSubImage3D(GL_TEXTURE_2D_ARRAY,
        0,                      //Mipmap number
        0, 0, 1, //xoffset, yoffset, zoffset
        1, 1, 1,         //width, height, depth
        GL_RGB,                 //format
        GL_UNSIGNED_BYTE,       //type
        color2)); //pointer to data


    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));



  

    */



    

    //GLCall(glBindTexture(GL_TEXTURE_2D_ARRAY, m_textureArray));
    //GLCall(glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));

    //GLCall(glGenerateMipmap(GL_TEXTURE_2D_ARRAY));



    // TODO: check the following if necessary
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

    /* 
       m_CubeSelector.Create(glm::vec3(0, 0, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 2, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 4, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 6, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 8, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 10, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 12, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 14, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 16, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 18, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 20, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 22, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       m_CubeSelector.Create(glm::vec3(0, 24, 0), &m_textureSelection, 1, glm::vec3(1,1,1));
       */

    // TODO: check the following if necessary
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // NOTE: Selection related stuff
    m_textureSelectionCube.EmptyTextureUI();
    m_textureSelectionGround.EmptyTextureI();

    m_frameBufferSelection.Bind();

    m_depthBufferSelection.Bind();
		GLCall( glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, App::WINDOW_WIDTH, App::WINDOW_HEIGHT); );
		GLCall( glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthBufferSelection.getDepthBufferId()); );

    m_textureSelectionCube.SimpleBind();

    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureSelectionCube.GetTextureID(), 0););

    m_textureSelectionCube.SimpleBind();
    GLCall(glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, m_textureSelectionGround.GetTextureID(), 0););

    //GLenum DrawBuffers[2] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1};
    //GLCall(glDrawBuffers(2, DrawBuffers););

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) 
      std::cout << "Problem with the framebuffer" << std::endl;

    m_textureSelectionGround.Unbind();
    m_frameBufferSelection.Unbind();
    m_depthBufferSelection.Unbind();

    m_CubeRenderer.updateColor();
    m_CubeRenderer.updateTexture();
    m_CubeRenderer.updateType();
    m_CubeRenderer.updateCubeId();
  }

  ModeEditor::~ModeEditor() {}

  void ModeEditor::OnUpdate(float ) {}

  void ModeEditor::OnRender()
  {

    GLCall(glClearColor(m_backgroundColor.x, m_backgroundColor.y,
          m_backgroundColor.z, 1.0f));
    // TODO: Check if necessary (redundancy) because of App.cpp beginFrame()
    GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

    m_GridRenderer.draw(m_FreeCam, m_ProjMatrix, m_CubeSelector.activeGrid());
	m_LightManager.dirLight().lightDirection = glm::vec3(glm::mat4(1.0f) * glm::vec4(m_LightManager.direction(), 0));
    m_LightManager.pointLightList()[0].lightPosition = glm::vec3(glm::mat4(1.0f) * glm::vec4(m_LightManager.position(), 0));
    m_CubeRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix, m_LightManager, m_textureArray);
    m_CubeSelector.Show(m_FreeCam.getViewMatrix(), m_ProjMatrix);

    // NOTE: Generating offscreen selection texture
    m_frameBufferSelection.Bind();
    //m_CubeSelectionRenderer.draw(m_FreeCam.getViewMatrix(), m_ProjMatrix, m_CubeRenderer.m_CubeList); // NOTE: old draw calls
		m_CubeRenderer.drawSelectionTexture(m_FreeCam.getViewMatrix(), m_ProjMatrix);
    m_GroundSelectionRenderer.draw(m_FreeCam, m_ProjMatrix);
    m_frameBufferSelection.Unbind();

  }

  void ModeEditor::OnEvent(const SDL_Event &e)
  {
		if ( ImGui::IsAnyWindowHovered() == false ) {
			switch(e.type) {
				case SDL_MOUSEWHEEL:
					m_FreeCam.moveFront(e.wheel.y);
					break;

				case SDL_MOUSEBUTTONDOWN:
					if ( e.button.button == SDL_BUTTON_MIDDLE ) m_middleClick = true;
					else if ( e.button.button == SDL_BUTTON_LEFT ) {
						m_leftClick = true;
						m_CubeSelector.MoveSelectorToClick(e.button.x, App::WINDOW_HEIGHT -e.button.y -1, m_frameBufferSelection);
					}
					break;

				case SDL_MOUSEBUTTONUP:
					if ( e.button.button == SDL_BUTTON_MIDDLE ) m_middleClick = false;
					if ( e.button.button == SDL_BUTTON_LEFT ) m_leftClick = false;
					break;

				case SDL_MOUSEMOTION:
					if ( m_middleClick && m_shiftKey ) {

						if ( e.motion.xrel != 0 ) m_FreeCam.moveLeft( float(e.motion.xrel) * 0.01);
						if ( e.motion.yrel != 0 ) m_FreeCam.moveUp( float(e.motion.yrel) * 0.01);

					}
					else if ( m_middleClick ) {

						if ( e.motion.xrel != 0 ) m_FreeCam.rotateLeft( float(e.motion.xrel) * 0.5);
						if ( e.motion.yrel != 0 ) m_FreeCam.rotateUp( float(e.motion.yrel) * 0.5);

					} 
					else if ( m_ctrlKey && m_leftClick ) {
						// TODO: draw
						m_CubeSelector.MoveSelectorToClick(e.motion.x, App::WINDOW_HEIGHT -e.motion.y -1, m_frameBufferSelection);
						if ( m_CubeSelector.currentCube() ) {
							int cubeStyle = m_CubeSelector.selectorCube().type();
							m_CubeRenderer.updateType();
							m_CubeSelector.currentCube()->type() = m_CubeSelector.selectorCube().type();
							if (cubeStyle == form::COLORED) {
								static float color[3] = { m_CubeSelector.selectorCube().color().x, m_CubeSelector.selectorCube().color().y, m_CubeSelector.selectorCube().color().z, };
								m_CubeSelector.currentCube()->Setcolor(glm::vec3(color[0], color[1], color[2]));
								m_CubeRenderer.updateColor();
							}
							else if (cubeStyle == form::TEXTURED) {
								m_CubeSelector.currentCube()->texture() = m_CubeSelector.selectorCube().texture();
								m_CubeRenderer.updateTexture();
							} else if (cubeStyle == form::MULTI_TEXTURED) {
								m_CubeSelector.currentCube()->texture() = m_CubeSelector.selectorCube().texture();
								m_CubeRenderer.updateTexture();
							}
							// TODO: check if necessary
							m_CubeSelector.refresh();
						}
						else if ( m_altKey ) {
							m_CubeSelector.AddToSelector();
						}
					}
					else if ( m_altKey && m_leftClick ) {
						m_CubeSelector.MoveSelectorToClick(e.motion.x, App::WINDOW_HEIGHT -e.motion.y -1, m_frameBufferSelection);
						if ( m_CubeSelector.currentCube() ) {
							// TODO: check face somehow
						}
						else {
							m_CubeSelector.AddToSelector();
						}
					}
					break;

				case SDL_KEYDOWN:
					if ( e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT ) m_shiftKey = true;
					else if ( e.key.keysym.sym == SDLK_LCTRL || e.key.keysym.sym == SDLK_RCTRL ) m_ctrlKey = true;
					else if ( e.key.keysym.sym == SDLK_LALT || e.key.keysym.sym == SDLK_RALT ) m_altKey = true;
					break;

				case SDL_KEYUP:
					if ( e.key.keysym.sym == SDLK_LSHIFT || e.key.keysym.sym == SDLK_RSHIFT ) m_shiftKey = false;
					else if ( e.key.keysym.sym == SDLK_LCTRL || e.key.keysym.sym == SDLK_RCTRL ) m_ctrlKey = false;
					else if ( e.key.keysym.sym == SDLK_LALT || e.key.keysym.sym == SDLK_RALT ) m_altKey = false;
					break;
			}
		}
  }



  void ModeEditor::OnImGuiRender()
  {
    m_Interface.MenuBarInterface();
    m_Interface.MainActionMenu();
    m_Interface.MenuInfosInterface();
  }
} // namespace modes
