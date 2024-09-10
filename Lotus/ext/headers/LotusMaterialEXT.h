// LOTUS DEFAULT-EXTENSION
// LotusMaterialEXT provides simple default materials, and shaders for developers to
// set up some nice visuals in a simple manner.

#ifndef LOTUSMATERIALEXT_H
#define LOTUSMATERIALEXT_H

#include "../../core/headers/LotusECS.h"
#include "../../core/headers/lotus_types.h"

static const char *vsrc001 = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "void main() {\n"
    "   gl_Position = uproj * uview * umodel * vec4(aPos, 1.0);\n"
    "}\n";

static const char *fsrc001 = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0, 0.2, 0.5, 1.0);\n"
    "}\n";

static unsigned char LotusDefaultMaterial_001;

LOTUS_API void lotusInitMaterialEXT(void);

#endif