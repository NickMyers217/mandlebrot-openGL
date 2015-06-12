#include "shader.h"
#include <iostream>
#include <fstream>
#include <string>


ShaderProgram * createShaderProgram(const char * vertFile, const char * fragFile)
{
	ShaderProgram * program = new ShaderProgram;

	program->vid = glCreateShader(GL_VERTEX_SHADER);
	program->fid = glCreateShader(GL_FRAGMENT_SHADER);
	loadShaderSource(program->vid, vertFile);
	loadShaderSource(program->fid, fragFile);
	glCompileShader(program->vid);
	glCompileShader(program->fid);
	errorCheck(program->vid, false);
	errorCheck(program->fid, false);
	program->pid = glCreateProgram();
	glAttachShader(program->pid, program->vid);
	glAttachShader(program->pid, program->fid);
	glLinkProgram(program->pid);
	errorCheck(program->pid, true);

	return program;
}


void destroyShaderProgram(ShaderProgram * program)
{
	glDetachShader(program->pid, program->fid);
	glDetachShader(program->pid, program->vid);
	glDeleteProgram(program->pid);
	glDeleteShader(program->fid);
	glDeleteShader(program->vid);
	delete program;
}


void useProgram(ShaderProgram * program)
{
	glUseProgram(program->pid);
}


void loadShaderSource(GLuint shader, const char * filePath)
{
	std::string source, line;
	std::ifstream file(filePath);

	if (file.is_open())
	{
		while (getline(file, line))
		{
			source += line;
		}
		file.close();
	}
	else std::cout << "Unable to open file"; 

	GLchar * helper1 = (GLchar *) source.c_str();
	GLint helper2 = (GLint) source.length();
	glShaderSource(shader, 1, &helper1, &helper2);
}


void errorCheck(GLuint id, bool isProgram)
{
	GLint error = 0;
	if(isProgram) glGetProgramiv(id, GL_LINK_STATUS, (int *)&error);
	else glGetShaderiv(id, GL_COMPILE_STATUS, &error);

	if(error == GL_FALSE)
	{
		GLint maxLength = 0;
		if(isProgram) glGetProgramiv(id, GL_INFO_LOG_LENGTH, &maxLength);
		else glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		GLchar * errorLog = new GLchar[maxLength];
		if(isProgram) glGetProgramInfoLog(id, maxLength, &maxLength, &errorLog[0]);
		else glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		std::cerr << errorLog << std::endl;
		delete [] errorLog;
	}
}


void setUniform1f(GLuint prog, const char * name, float val)
{
	GLint loc = glGetUniformLocation(prog, name);
	if(loc != -1) glUniform1f(loc, val);
}


void setUniform2f(GLuint prog, const char *name, float v1, float v2)
{
	GLint loc = glGetUniformLocationARB(prog, name);
	if(loc != -1) glUniform2f(loc, v1, v2);
}


void setUniform1i(GLuint prog, const char * name, int val)
{
	GLint loc = glGetUniformLocationARB(prog, name);
	if(loc != -1) glUniform1i(loc, val);
}
