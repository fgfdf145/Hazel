#include "hzpch.h"
#include "Shader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel 
{

	Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc)
	{
		// �����µĶ�����ɫ����GLuint��gl�Դ���int����
		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

		// ����ɫ�����͵�Opengl
		// ��ע�⣬std::string �� .c_str �� NULL �ַ���β��
		const GLchar* source = vertexSrc.c_str();
		glShaderSource(vertexShader, 1, &source, 0);

		// ������ɫ��
		glCompileShader(vertexShader);

		GLint isCompiled = 0;
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength����Null
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

			// ������ɺ�ɾ��Shader
			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Vertex shader compilation failure!");
			return;
		}

		// ����֡��ɫ��
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		// ����֡��ɫ����OpenGL
		// ��ע�⣬std::string �� .c_str �� NULL �ַ���β��
		source = fragmentSrc.c_str();
		glShaderSource(fragmentShader, 1, &source, 0);

		// ����֡��ɫ��
		glCompileShader(fragmentShader);

		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength����Null
			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

			// ������ɺ�ɾ��֡��ɫ������Ҫ����
			glDeleteShader(fragmentShader);
			glDeleteShader(vertexShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Fragment shader compilation failure!");
			return;
		}

		// ������ɫ����֡��ɫ���ڴ�ʱ�������
		// ��������ɫ������Ŀ����
		// �����Ŀ
		m_RendererID = glCreateProgram();
		GLuint program = m_RendererID;

		// ������Ŀ
		glAttachShader(program, vertexShader);
		glAttachShader(program, fragmentShader);

		// ������Ŀ
		glLinkProgram(program);

		//  ��glGetProgram* ������ glGetShader*.
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// maxLength����Null
			std::vector<GLchar> infoLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

			// ������ɺ�ɾ��֡��ɫ������Ҫ����
			glDeleteProgram(program);
			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);

			HZ_CORE_ERROR("{0}", infoLog.data());
			HZ_CORE_ASSERT(false, "Shader link failure!");
			return;
		}

		// ���ӳ�������api
		glDetachShader(program, vertexShader);
		glDetachShader(program, fragmentShader);
	}

	Shader::~Shader()
	{
		glDeleteProgram(m_RendererID);
	}

	void Shader::Bind() const
	{
		glUseProgram(m_RendererID);
	}

	void Shader::Unbind() const
	{
		glUseProgram(0);
	}

	void Shader::UploadUniformMat4(const std::string& name, const glm::mat4& matrix)
	{
		GLint location = glGetUniformLocation(m_RendererID, name.c_str());// ��ָ��ͱ�������
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}