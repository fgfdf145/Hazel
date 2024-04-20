#pragma once

#include <string>
#include <glm/glm.hpp>

namespace Hazel 
{
	//功能与名称一致
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		
		static Shader* Create(const std::string& vertexSrc, const std::string& fragmentSrc);
	};
}