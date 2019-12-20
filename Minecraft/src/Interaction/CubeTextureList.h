#pragma once

#include <iostream>
#include <map>
#include <vector>
#include "Texture.h"
#include <string>

namespace interaction {

	class CubeTextureList
	{
	private:
		std::map<std::string,Texture*> m_TextureList;
		std::vector<std::string> m_NameList;
		std::shared_ptr<Texture> m_textSelector;
		std::shared_ptr<Texture> m_textSelected;
		std::shared_ptr<Texture> m_textCopy;

	public:
		CubeTextureList();
		~CubeTextureList();
		void addToList(std::string path);
		Texture* give(std::string name);

		inline const std::shared_ptr<Texture> selector() { return m_textSelector; };
		inline const std::shared_ptr<Texture> selected() { return m_textSelected; };
		inline const std::shared_ptr<Texture> copy() { return m_textCopy; };
		inline const std::vector<std::string>& nameList() { return m_NameList; };
	};

}