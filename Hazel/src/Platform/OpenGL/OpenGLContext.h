#pragma once

#include "Hazel/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Hazel 
{
	// ������ͺ���
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}