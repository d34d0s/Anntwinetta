#include <anntwinetta.h>

char vertexShader[] = {
    "#version 430 core\n"
    "layout(location = 0) in vec3 uLocation;\n"
    "uniform mat4 uModel;\n"
    "uniform mat4 uView;\n"
    "uniform mat4 uProj;\n"
    "void main() {\n"
    "   gl_Position = uProj * uView * uModel * vec4(uLocation, 1.0f);\n"
    "}"
};

char fragShader[] = {
    "#version 430 core\n"
    "out vec3 fragColor;\n"
    "void main() {\n"
    "   fragColor = vec3(1.0f, 1.0f, 1.0f);\n"
    "}"
};

void main() {
    atInit();
   
    float vertices[] = {
        -0.5, -0.5, 0.5,
         0.5, -0.5, 0.5,
         0.0,  0.5, 0.5,
    };

    int meshIndex = atMakeMesh(3, vertices);
    ATmeshLayout* meshLayout = atGetMeshLayout(meshIndex);
    
    int shaderIndex = atMakeShader(vertexShader, fragShader);
    ATshaderLayout* shaderLayout = atGetShaderLayout(shaderIndex);

    ATmat4 model = atIdentity();
    atMakeUniform(UNIFORM_MAT4, shaderIndex, "uModel", &model);
    atMakeUniform(UNIFORM_MAT4, shaderIndex, "uView", atGetViewMatrix());
    atMakeUniform(UNIFORM_MAT4, shaderIndex, "uProj", atGetProjMatrix());

    atMainLoop(
        atDrawCall(DRAW_CLEAR, TRIANGLE_MODE);
        atProcEvents();
        
        if (atIsKeyPressed(atKeyboard.ESCAPE) || atIsKeyPressed(atKeyboard.F12)) atExit();

        if (atIsKeyTriggered(atKeyboard.R)) atClearColor(255, 0, 0, 255);
        if (atIsKeyTriggered(atKeyboard.G)) atClearColor(0, 255, 0, 255);
        if (atIsKeyTriggered(atKeyboard.B)) atClearColor(0, 0, 255, 255);

        atSetUniform(UNIFORM_MAT4, shaderIndex, "uModel");
        atSetUniform(UNIFORM_MAT4, shaderIndex, "uView");
        atSetUniform(UNIFORM_MAT4, shaderIndex, "uProj");
        atDrawCallSelect(
            DRAW_MESH,
            TRIANGLE_MODE,
            meshLayout,
            shaderLayout
        );
        
        atProcCamera();
        atProcRender();
    ); atExit();
}
