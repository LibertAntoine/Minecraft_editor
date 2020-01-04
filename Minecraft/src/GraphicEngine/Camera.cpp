#include "Camera.h"

namespace camera {


	// FREEFLY CAMERA //

	FreeflyCamera::FreeflyCamera()
		: m_Position(-2, 3, 5),
		m_fPhi(glm::pi<float>() + glm::radians(-30.f)),
		m_fTheta(glm::radians(-20.f))
	{
		computeDirectionVectors();
	};

	void FreeflyCamera::computeDirectionVectors()
	{
		m_FrontVector = glm::vec3(
			glm::cos(m_fTheta) * glm::sin(m_fPhi),
			glm::sin(m_fTheta),
			glm::cos(m_fTheta) * glm::cos(m_fPhi)
		);

		m_LeftVector = glm::vec3(
			glm::sin(m_fPhi + glm::pi<float>() / 2),
			0.f,
			glm::cos(m_fPhi + glm::pi<float>() / 2)
		);

		m_UpVector = glm::cross(m_FrontVector, m_LeftVector);
	};

	void FreeflyCamera::moveLeft(float t)
	{
		m_Position += t * m_LeftVector;
		if (m_Position.y < 0)
			m_Position.y = 0;
	};


	void FreeflyCamera::moveFront(float t)
	{
		m_Position += t * m_FrontVector;
		if (m_Position.y < 0)
			m_Position.y = 0;
	};

	void FreeflyCamera::moveUp(float t)
	{
		m_Position += t * m_UpVector;
		if (m_Position.y < 0)
			m_Position.y = 0;
	};

	void FreeflyCamera::rotateLeft(float degrees)
	{
		m_fPhi += glm::radians(degrees);
		computeDirectionVectors();
	};

	void FreeflyCamera::rotateUp(float degrees)
	{
		m_fTheta += glm::radians(degrees);
		computeDirectionVectors();
	};

	glm::mat4 FreeflyCamera::getViewMatrix() const
	{
		return glm::lookAt(m_Position, m_Position + m_FrontVector, m_UpVector);
	};



	// TRACKBALL CAMERA //

	TrackballCamera::TrackballCamera()
		: m_fDistance(5), m_fAngleX(0), m_fAngleY(0)
	{};


	void TrackballCamera::moveFront(float delta)
	{
		m_fDistance += delta;
	};

	void TrackballCamera::rotateLeft(float degrees)
	{
		m_fAngleX += degrees;
	};

	void TrackballCamera::rotateUp(float degrees)
	{
		m_fAngleY += degrees;
	};

	glm::mat4 TrackballCamera::getViewMatrix() const
	{
		glm::mat4 ViewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -m_fDistance));
		ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleX), glm::vec3(0, 1, 0));
		ViewMatrix = glm::rotate(ViewMatrix, glm::radians(m_fAngleY), glm::vec3(1, 0, 0));
		return ViewMatrix;
	};


}