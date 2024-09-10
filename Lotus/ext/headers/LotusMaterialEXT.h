// LOTUS DEFAULT-EXTENSION
// LotusMaterialEXT provides simple default materials, and shaders for developers to
// set up some nice visuals in a simple manner.

#ifndef LOTUSMATERIALEXT_H
#define LOTUSMATERIALEXT_H

#include "../../core/headers/LotusECS.h"
#include "../../core/headers/lotus_types.h"

static const char *vsrc001 = "#version 330 core\n"
    "layout(location = 0) in vec3 vLocation;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "void main() {\n"
    "   gl_Position = uproj * uview * umodel * vec4(vLocation, 1.0);\n"
    "}\n";

static const char *fsrc001 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0);\n"
    "}\n";

static const char *vsrc002 = "#version 330 core\n"
    "layout(location = 0) in vec3 vLocation;\n"
    "layout(location = 1) in vec3 vColor;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "out vec3 vColorOut;\n"
    "void main() {\n"
    "   gl_Position = uproj * uview * umodel * vec4(vLocation, 1.0);\n"
    "   vColorOut = vColor;\n"
    "}\n";

static const char *fsrc002 = "#version 330 core\n"
    "in vec3 vColorOut;\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(vColorOut, 1.0);\n"
    "}\n";

LOTUS_API unsigned char LotusDefaultMaterial_001(void);
LOTUS_API unsigned char LotusDefaultMaterial_002(void);


#endif