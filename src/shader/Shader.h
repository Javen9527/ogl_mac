//
//  Shader.cpp
//  src
//
//  Created by Qin, Jianbo on 2022/2/22.
//  Copyright © 2022 Qin, Jianbo. All rights reserved.
//

#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    Shader(const char* vPath, const char* fPath, const char* gPath = nullptr);

    void use();

private:
    void checkCompileErrors(GLuint shader, std::string type);

public:
    unsigned int m_id;
}; // Shader

