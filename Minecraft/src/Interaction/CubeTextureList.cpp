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

}