#pragma once
#include <string>
#include <GL/glew.h>

class Shader
{
public:
    Shader(const std::string& vertexPath, const std::string& fragmentPath);
    ~Shader();

    void Use() const;
    GLuint GetProgram() const;

private:
    GLuint Program;

    std::string LoadSource(const std::string& path);
    GLuint CompileShader(GLenum type, const std::string& source);
};
