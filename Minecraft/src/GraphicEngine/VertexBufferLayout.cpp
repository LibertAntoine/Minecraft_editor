#include "VertexBufferLayout.h"


namespace details {
	template<typename T>
	GLenum getGLenum() {
		//static_assert(false);
                // https://stackoverflow.com/questions/52137187/static-assert-in-template-specialization-fails-even-if-it-is-not-instantiated
		return GL_FLOAT;
	}

	template<>
	GLenum getGLenum<float>() {
		return GL_FLOAT;
	}

	template<>
	GLenum getGLenum<unsigned int>() {
		return GL_UNSIGNED_INT;
	}

	template<>
	GLenum getGLenum<int>() {
		return GL_INT;
	}

	template<>
	GLenum getGLenum<unsigned char>() {
		return GL_UNSIGNED_BYTE;
	}

	template<typename T>
	unsigned char getGLbool() {
		//static_assert(false);
		return GL_FALSE;
	}

	template<>
	unsigned char getGLbool<float>() {
		return GL_FALSE;
	}

	template<>
	unsigned char getGLbool<unsigned int>() {
		return GL_FALSE;
	}

	template<>
	unsigned char getGLbool<int>() {
		return GL_FALSE;
	}

	template<>
	unsigned char getGLbool<unsigned char>() {
		return GL_TRUE;
	}
}
