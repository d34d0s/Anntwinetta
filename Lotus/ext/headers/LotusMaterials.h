// LOTUS DEFAULT-EXTENSION
// LotusMaterialEXT provides simple default materials, and shaders for developers to
// set up some nice visuals in a simple manner.

#ifndef LOTUSMATERIALS_H
#define LOTUSMATERIALS_H

#include "../../engine/headers/core/LotusECS.h"
#include "../../engine/headers/core/lotus_types.h"

static const char *vsrcMVP = "#version 330 core\n"
    "layout(location = 0) in vec3 vLocation;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "void main() {\n"
    "   gl_Position = uproj * uview * umodel * vec4(vLocation, 1.0);\n"
    "}\n";

static const char *fsrcMVP = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0);\n"
    "}\n";


static const char *vsrcMVPC = "#version 330 core\n"
    "layout(location = 0) in vec3 vLocation;\n"
    "layout(location = 1) in vec3 vColor;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "out vec3 vColorOut;\n"
    "void main() {\n"
    "   vColorOut = vColor;\n"
    "   gl_Position = uproj * uview * umodel * vec4(vLocation, 1.0);\n"
    "}\n";

static const char *fsrcMVPC = "#version 330 core\n"
    "in vec3 vColorOut;\n"
    "in vec2 vTextureOut;\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(vColorOut, 1.0);\n"
    "}\n";


static const char *vsrcMVPT = "#version 330 core\n"
    "layout(location = 0) in vec3 vLocation;\n"
    "layout(location = 1) in vec2 vTexture;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "out vec2 vTextureOut;\n"
    "void main() {\n"
    "   vTextureOut = vTexture;\n"
    "   gl_Position = uproj * uview * umodel * vec4(vLocation, 1.0);\n"
    "}\n";

static const char *fsrcMVPT = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec2 vTextureOut;\n"
    "uniform sampler2D texUnit;\n"
    "void main() {\n"
    "   FragColor = texture(texUnit, vTextureOut) * vec4(1.0);\n"
    "}\n";


static const char *vsrcMVPCT = "#version 330 core\n"
    "layout(location = 0) in vec3 vLocation;\n"
    "layout(location = 1) in vec3 vColor;\n"
    "layout(location = 2) in vec2 vTexture;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "out vec3 vColorOut;\n"
    "out vec2 vTextureOut;\n"
    "void main() {\n"
    "   vColorOut = vColor;\n"
    "   vTextureOut = vTexture;\n"
    "   gl_Position = uproj * uview * umodel * vec4(vLocation, 1.0);\n"
    "}\n";

static const char *fsrcMVPCT = "#version 330 core\n"
    "in vec3 vColorOut;\n"
    "in vec2 vTextureOut;\n"
    "out vec4 FragColor;\n"
    "uniform sampler2D texUnit;"
    "void main() {\n"
    "   FragColor = texture(texUnit, vTextureOut) * vec4(vColorOut, 1.0);\n"
    "}\n";

LOTUS_API unsigned char LotusDefaultMaterial_MVP(void);
LOTUS_API unsigned char LotusDefaultMaterial_MVPC(void);
LOTUS_API unsigned char LotusDefaultMaterial_MVPT(void);
LOTUS_API unsigned char LotusDefaultMaterial_MVPN(void);
LOTUS_API unsigned char LotusDefaultMaterial_MVPCT(void);
LOTUS_API unsigned char LotusDefaultMaterial_MVPCN(void);
LOTUS_API unsigned char LotusDefaultMaterial_MVPTN(void);
LOTUS_API unsigned char LotusDefaultMaterial_MVPCTN(void);


#endif