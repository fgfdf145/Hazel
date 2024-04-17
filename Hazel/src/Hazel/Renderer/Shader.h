#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Hazel 
{
	//功能与名称一致
	class Shader
	{
	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		~Shader();

		void Bind() const;
		void Unbind() const;
		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);// 绑定uniform，使用matrix4
	private:
		uint32_t m_RendererID;
	};

}