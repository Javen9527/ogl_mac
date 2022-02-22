
#include "Shader.h"

//////// IMPLEMENTATION ////////

Shader::Shader(const char* vPath, const char* fPath, const char* gPath)
{
    std::string vCode, fCode, gCode;
    std::ifstream vFile, fFile, gFile;
    vFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    gFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        std::stringstream vStream, fStream;
        vFile.open(vPath);
        fFile.open(fPath);
        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();
        vFile.close();
        fFile.close();
        vCode = vStream.str();
        fCode = fStream.str();

        if(gPath)
        {
            std::stringstream gStream;
            gFile.open(gPath);
            gStream << gFile.rdbuf();
            gFile.close();
            gCode = gStream.str();
        }
    }
    catch(std::ifstream::failure& e)
    {
        std::cout << "E::Shader::file not successfully read: " << e.what() << std::endl;
    }

    // compile
    const char* vTex = vCode.c_str();
    const char* fTex = fCode.c_str();
    unsigned int v, f, g;
    v = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(v, 1, &vTex, nullptr);
    glCompileShader(v);
    checkCompileErrors(v, "VERTEX");
    f = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(f, 1, &fTex, nullptr);
    glCompileShader(f);
    checkCompileErrors(f, "FRAGMENT");
    if(gPath)
    {
        const char* gTex = gCode.c_str();
        g = glCreateShader(GL_GEOMETRY_SHADER);
        glShaderSource(g, 1, &gTex, nullptr);
        glCompileShader(g);
        checkCompileErrors(g, "GEOMETRY");
    }
    // link
    m_id = glCreateProgram();
    glAttachShader(m_id, v);
    glAttachShader(m_id, f);
    if(gPath)
    {
        glAttachShader(m_id, g);
    }
    glLinkProgram(m_id);
    checkCompileErrors(m_id, "PROGRAM");

    glDeleteShader(v);
    glDeleteShader(f);
    if(gPath)
    {
        glDeleteShader(g);
    }
}

void Shader::use()
{
    glUseProgram(m_id);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "E::Shader::compile error: " << type << " | " << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cout << "E::Program::compile error: " << type << " | " << infoLog << std::endl;
        }
    }
}
