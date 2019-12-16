#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace camera {

class FreeflyCamera {
private:
	glm::vec3 m_Position;
	float m_fPhi;
	float m_fTheta;

	glm::vec3 m_FrontVector; //vecteur F
	glm::vec3 m_LeftVector; //vecteur L
	glm::vec3 m_UpVector; //vecteur U
public:
	FreeflyCamera();
	void moveLeft(float t);
	void moveFront(float t);
	void rotateLeft(float degrees);
	void rotateUp(float degrees);
	glm::mat4 getViewMatrix() const;
private:
	void computeDirectionVectors();
};


class TrackballCamera {
private:
	float m_fDistance; //Distance du centre scène.
	float m_fAngleX; //Angle cam sur X.
	float m_fAngleY; //Angle cam sur Y.
public:
	TrackballCamera();
	void moveFront(float delta);
	void rotateLeft(float degrees);
	void rotateUp(float degrees);
	glm::mat4 getViewMatrix() const;
};

}