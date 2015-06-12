#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>

struct ShaderProgram
{
	GLuint pid;
	GLuint vid;
	GLuint fid;
};

ShaderProgram * createShaderProgram(const char * vertFile, const char * fragFile);
void loadShaderSource(GLuint shader, const char * filePath);
void checkCompilation(GLuint shader);
void errorCheck(GLuint id, bool isProgram);
void useProgram(ShaderProgram * program);
void destroyShaderProgram(ShaderProgram * program);
void setUniform1f(GLuint prog, const char * name, float val);
void setUniform2f(GLuint prog, const char *name, float v1, float v2);
void setUniform1i(GLuint prog, const char * name, int val);

#endif
