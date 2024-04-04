#pragma once

namespace Hazel
{
	class GraphicsContext
	{
	public:
		virtual void Init() = 0;//初始化函数
		virtual void SwapBuffers() = 0;//交换缓冲区
	};
}