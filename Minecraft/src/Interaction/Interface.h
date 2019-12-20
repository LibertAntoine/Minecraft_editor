#pragma once
#include "ImGUI/imgui.h"
#include "SDL.h"
#include "Interaction/CubeSelector.h"
#include "Camera.h"
#include <iostream>


namespace interaction {

	class Interface
	{
	private:


	public:
		Interface();
		~Interface();
		void SelectorInterface(interaction::CubeSelector& cubeSelector);
		void CameraInterface(camera::FreeflyCamera& Camera);
	};

}
