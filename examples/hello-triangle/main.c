#include <anntwinetta.h>

char vertexShader[] = {
    "#version 430 core\n"
    "layout(location = 0) in vec3 uLocation;\n"
    "uniform mat4 model;\n"
    "void main() {\n"
    "   gl_Position = model * vec4(uLocation, 1.0f);\n"
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
    ATmeshLayout* meshLayout = atGetMeshLayout(meshIndex) ;
    
    int shaderIndex = atMakeShader(vertexShader, fragShader);
    ATshaderLayout* shaderLayout = atGetShaderLayout(shaderIndex);

    atMat4 model = atIdentity();
    atMakeUniform(UNIFORM_MAT4, shaderIndex, "model", &model);

    while (atRunning()) {
        atDrawCall(DRAW_CLEAR, TRIANGLE_MODE);
        atPollEvents();
        
        if (atIsKeyPressed(atKeyboard.ESCAPE) || atIsKeyPressed(atKeyboard.F12)) atExit();

        if (atIsKeyTriggered(atKeyboard.R)) atClearColor(255, 0, 0, 255);
        if (atIsKeyTriggered(atKeyboard.G)) atClearColor(0, 255, 0, 255);
        if (atIsKeyTriggered(atKeyboard.B)) atClearColor(0, 0, 255, 255);

        atDrawCallSelect(
            DRAW_MESH,
            TRIANGLE_MODE,
            *shaderLayout->program,
            *meshLayout->vao,
            *meshLayout->n_verts
            );
        
        atSetUniform(UNIFORM_MAT4, shaderIndex, "model");

        atRender();
    }; atExit();
}
