#pragma once

/**
 * \file Application_Main.h
 * \brief Manage the camera view system
 * \author Antoine Libert & Nicolas Lienart
 * Manage the modification relative to the camera (translation, rotation) 
 * Can return the actual camera view matrix
 */

#include <glm/glm.hpp>

namespace camera {

	/**
	* \brief Freefly Camera system : can move in a 3D environnement, and rotate compared to the camera position
	*/
	class FreeflyCamera {
	private:
		
		// Position vectors //
		glm::vec3 m_Position;
		glm::vec3 m_FrontVector; 
		glm::vec3 m_LeftVector; 
		glm::vec3 m_UpVector;

		// Rotation attributes //
		float m_fPhi;
		float m_fTheta;


	public:
		FreeflyCamera();

		/**
		* \brief Translate the camera position horizontally.
		* \param t the distance translated on the left (can be a negative float).
		*/
		void moveLeft(float t);

		/**
		* \brief Translate the camera position in depth.
		* \param t the distance translated in depth (can be a negative float).
		*/
		void moveFront(float t);

		/**
		* \brief Translate the camera position vertically.
		* \param t the distance translated on up (can be a negative float).
		*/
		void moveUp(float t);

		/**
		* \brief Rotate the camera horizontally.
		* \param degrees angle in degree of the rotation on the left (can be a negative float).
		*/
		void rotateLeft(float degrees);

		/**
		* \brief Rotate the camera vertically.
		* \param degrees angle in degree of the rotation on up (can be a negative float).
		*/
		void rotateUp(float degrees);

		/**
		* \brief compute the Direction Vector after a rotation
		*/
		void computeDirectionVectors();

		// GETTERS - SETTERS //
		/**
		* \brief Return the camera view matrix associate to the camera 
		* \return Camera view matrix (4x4).
		*/
		glm::mat4 getViewMatrix() const;

		inline const glm::vec3 position() const { return m_Position; };
		inline glm::vec3& position() { return m_Position; };
		inline float& fPhi() { return m_fPhi; };
		inline float& fTheta() { return m_fTheta; };
	};
}
