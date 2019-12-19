#pragma once


#include <glm/glm.hpp>
#include <Texture.h>

namespace form {

	typedef struct CubeData {
		static const int datas[];
		static const unsigned int indices[];
	} CubeData;

    class Cube {
    public:
        Cube() = delete;
        Cube(const glm::vec3& position, const Texture* texture = nullptr, const short& scale = 3, const glm::vec3& color = glm::vec3(0.5f,0.5f,0.5f));
        ~Cube();

		bool operator==(const form::Cube a);

        inline const glm::vec3 position() const { return m_position; };
		inline glm::vec3 position() { return m_position; };
        inline void position(const glm::vec3& position) { m_position = position; };
		inline const Texture* texture() const { return m_texture; };
		inline int scale() { return m_scale; };
		inline const glm::vec3 color() const { return m_color; };
		inline glm::vec3 color() { return m_color; };

    public:
        static const int datas[];
        static const unsigned int indices[];

    private:
        glm::vec3 m_position;
        const Texture* m_texture;
        int m_scale;
		glm::vec3 m_color;
    };
}

/* 
Dans le cube, j'ai c'est sur les datas du cubes.
    - Les positions.
    - Les normales.
    - Les indices des points.
    
    - Est ce que j'encapsule les index et tout dans le cude ou je laisse �a dans les modes ?
    - Si je prend le cas d'une cercle, ou d'une autre forme, la cr�ation des donn�es peut �tre relative � des param�tres.
    - O� est ce que je stocke les textures et positions sp�cifiques � chaque cube sp�cifiques � chaque cubes ? 
    - Est ce que je stocke les cubes en fonction de leur texture ? 
    - Est ce que je fais une collection qui repr�sentent toutes les cases de la map, �a ve dire parcourir une collection immense lorsque
    je veux dessiner un les cubes.
    - Sinon je stocke des cubes qui contiennent leur coordonn�es, leur texture, leur scale, (et leur rotate). Comme �a je parcours
    directement cette collection pour chaque cube � faire.
    - Par contre quand je veux retrouver un cube c'est moins facile. Est ce que l'on fait un tableau de pointeur sur les cubes en parall�re ?
    - Ensuite quand je dessine les cubes, est ce que le mieux est pas de les trier par texture dans la collection ?
    - Pour la selection, il faut que je vois comment le syst�me de selection avec la souris fonctionne, pour voir si dans tous les cas j'ai besoin de parcourir tous les cubes.

    - Du coup je pense que le mieux c'est de faire des objets cubes qui ont en attributs static les donn�es d'un cube et en attribut
    la texture, les coordonn�es du cubes...
    - 




*/
