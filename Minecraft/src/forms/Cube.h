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
        Cube(const glm::vec3& position, const char* texName = "default", const short& scale = 3);
        ~Cube();

		bool operator==(const form::Cube a);

        inline const glm::vec3 position() const { return m_position; };
        inline void position(const glm::vec3& position) { m_position = position; };
		inline const const char* texture() const { return m_texture; };
		inline const int scale() const { return m_scale; };

    public:
        static const int datas[];
        static const unsigned int indices[];

    private:
        glm::vec3 m_position;
        const char* m_texture;
        int m_scale;
    };
}

/* 
Dans le cube, j'ai c'est sur les datas du cubes.
    - Les positions.
    - Les normales.
    - Les indices des points.
    
    - Est ce que j'encapsule les index et tout dans le cude ou je laisse ça dans les modes ?
    - Si je prend le cas d'une cercle, ou d'une autre forme, la création des données peut être relative à des paramètres.
    - Où est ce que je stocke les textures et positions spécifiques à chaque cube spécifiques à chaque cubes ? 
    - Est ce que je stocke les cubes en fonction de leur texture ? 
    - Est ce que je fais une collection qui représentent toutes les cases de la map, ça ve dire parcourir une collection immense lorsque
    je veux dessiner un les cubes.
    - Sinon je stocke des cubes qui contiennent leur coordonnées, leur texture, leur scale, (et leur rotate). Comme ça je parcours
    directement cette collection pour chaque cube à faire.
    - Par contre quand je veux retrouver un cube c'est moins facile. Est ce que l'on fait un tableau de pointeur sur les cubes en parallère ?
    - Ensuite quand je dessine les cubes, est ce que le mieux est pas de les trier par texture dans la collection ?
    - Pour la selection, il faut que je vois comment le système de selection avec la souris fonctionne, pour voir si dans tous les cas j'ai besoin de parcourir tous les cubes.

    - Du coup je pense que le mieux c'est de faire des objets cubes qui ont en attributs static les données d'un cube et en attribut
    la texture, les coordonnées du cubes...
    - 




*/