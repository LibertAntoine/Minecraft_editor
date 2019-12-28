#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "Texture.h"
#include <string>
#include <memory>

namespace interaction {

	class CubeTextureList
	{
	private:
		std::shared_ptr<Texture> m_textSelector;
		std::shared_ptr<Texture> m_textSelected;
		std::shared_ptr<Texture> m_textCopy;

	public:
		CubeTextureList();
		~CubeTextureList();


		inline const std::shared_ptr<Texture> selector() { return m_textSelector; };
		inline const std::shared_ptr<Texture> selected() { return m_textSelected; };
		inline const std::shared_ptr<Texture> copy() { return m_textCopy; };
	};

}
