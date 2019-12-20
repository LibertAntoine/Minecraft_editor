#include "CubeTextureList.h"
#include <regex>

namespace interaction {
	CubeTextureList::CubeTextureList()
		:m_textSelector(std::make_unique<Texture>("res/textures/blocks/Texture_Selection.png", "Selection_Texture")),
		m_textSelected(std::make_unique<Texture>("res/textures/blocks/Texture_Selected.png", "Selected_Texture")),
		m_textCopy(std::make_unique<Texture>("res/textures/blocks/Texture_Selected.png", "Copy_Texture"))
	{}

	CubeTextureList::~CubeTextureList()
	{}
	
	void CubeTextureList::addToList(std::string path) {
		
		std::regex name_regex("[a-zA-Z0-9_]*\.png");
		std::smatch name_match;
		if (std::regex_search(path, name_match, name_regex)) {
			std::string name = name_match.str().substr(0, name_match.length() - 4);
			m_TextureList.insert(std::pair<std::string, Texture*>(name, new Texture(path, name)));
			m_NameList.push_back(name);
		}
		else {
			std::cerr << "Le nom de la texture fourni semble contenir des caractères spéciaux (autres que _ ), merci de les retirer." << std::endl;
			std::cerr << "Ou l'extension de la texture n'est pas en png." << std::endl;
			std::cerr << "Texture concerné : " << path << std::endl;
		}
	}

	Texture* CubeTextureList::give(std::string name) {
		if (m_TextureList.find(name) != m_TextureList.end()) {
			return m_TextureList[name];
		}
		else {
			return nullptr;
		}
	}
	
}