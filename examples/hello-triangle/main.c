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

    // make a model
    int modelID = atMakeModel(3, vertices);
    
    // make a material
    int materialID = atMakeMaterial(vertexShader, fragShader);

    // set the material to the model
    atSetModelMaterial(modelID, materialID);

    ATmat4 uModel = atIdentity();
    atMakeMaterialUniform(materialID, UNIFORM_MAT4, "uModel", &uModel);
    atMakeMaterialUniform(materialID, UNIFORM_MAT4, "uView", atGetCamView());
    atMakeMaterialUniform(materialID, UNIFORM_MAT4, "uProj", atGetCamProj());

    atMainLoop(
        atClockTick();
        atProcEvents();
        
        // queue a clear call
        atDrawCall(DRAW_CLEAR);
        
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

        // send shader uniforms before issuing a draw call
        atSendMaterialUniform(materialID, UNIFORM_MAT4, "uView");
        atSendMaterialUniform(materialID, UNIFORM_MAT4, "uProj");

        // queue a model draw
        atSetMaterialUniform(materialID, UNIFORM_MAT4, "uModel", &uModel);
        atSendMaterialUniform(materialID, UNIFORM_MAT4, "uModel");        
        atDrawModel(modelID);

        atProcCamera();
        
        // TODO: re-factor render pipeline to be programmable
        // drawModel() should queue a drawcall and the 
        // render process main method should send uniforms before drawArrays/Elements
        atProcRender();
    ); atExit();
}