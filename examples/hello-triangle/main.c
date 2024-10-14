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
    "   fragColor = vec3(0.3f, 0.6f, 0.4f);\n"
    "}"
};

void main() {
    atInit();
    atSetCamMode(FREELOOK_MODE);
   
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
    atMakeUniform(UNIFORM_MAT4, shaderIndex, "uView", atGetCamView());
    atMakeUniform(UNIFORM_MAT4, shaderIndex, "uProj", atGetCamProj());

    atMainLoop(
        atClockTick();
        atProcEvents();
        
        atDrawCall(DRAW_CLEAR, TRIANGLE_MODE);
        
        if (atIsKeyPressed(KEY_ESCAPE) || atIsKeyPressed(KEY_F12)) atExit();

        // change the "background" color
        if (atIsKeyTriggered(KEY_R)) atClearColor(255, 0, 0, 255);
        if (atIsKeyTriggered(KEY_G)) atClearColor(0, 255, 0, 255);
        if (atIsKeyTriggered(KEY_B)) atClearColor(0, 0, 255, 255);
        
        // move the "camera"
        if (atIsKeyPressed(KEY_W)) atCamIn();
        if (atIsKeyPressed(KEY_S)) atCamOut();
        if (atIsKeyPressed(KEY_A)) atCamLeft();
        if (atIsKeyPressed(KEY_D)) atCamRight();
        if (atIsKeyPressed(KEY_SPACE)) atCamUp();
        if (atIsKeyPressed(KEY_LEFT_SHIFT)) atCamDown();

        // set shader uniforms before sending a draw call
        atSetUniform(UNIFORM_MAT4, shaderIndex, "uModel");
        atSetUniform(UNIFORM_MAT4, shaderIndex, "uView");
        atSetUniform(UNIFORM_MAT4, shaderIndex, "uProj");
        
        // draw user-selected data
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
