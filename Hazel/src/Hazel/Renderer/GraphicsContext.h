#pragma once

namespace Hazel
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;//��ʼ������
		virtual void SwapBuffers() = 0;//����������
	};
}