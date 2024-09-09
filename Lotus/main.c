#include "lotus.h"

const char *vertex_shader_source = "#version 330 core\n"
    "layout(location = 0) in vec3 aPos;\n"
    "uniform mat4 umodel;\n"
    "uniform mat4 uview;\n"
    "uniform mat4 uproj;\n"
    "void main() {\n"
    "   gl_Position = uproj * uview * umodel * vec4(aPos, 1.0);\n"
    "}\n";

const char *fragment_shader_source = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    "   FragColor = vec4(1.0, 0.2, 0.5, 1.0);\n"
    "}\n";

int main() {
    lotusInit();
    lotusInitCamera(CAM_MODE_FREELOOK);

    float vertices[] = {
       -0.5f, -0.5f, 0.5f,
        0.0f,  0.5f, 0.5f,
        0.5f, -0.5f, 0.5f
    };

    unsigned char materialID = lotusMakeMaterial(
        vertex_shader_source,
        fragment_shader_source,
        3,
        (const char*[]){"umodel", "uview", "uproj"},
        (unsigned int[]){UTYPE_MAT4, UTYPE_MAT4, UTYPE_MAT4},
        (void*[]){NULL, NULL, NULL}
    );
    
    LotusEntity* e1 = lotusMakeEntity();
    lotusSetMesh(e1, vertices, 3); lotusSetMaterial(e1, materialID);
    lotusSetTransform(
        e1,
        (LMvec3){1.0, 1.0, 1.0},
        (LMvec3){0.0, 0.0, 0.0},
        (LMvec3){0.0, 0.0, 0.0}
    ); LotusTransform_itf* t1 = lotusGetTransform(e1);

    LotusEntity* e2 = lotusMakeEntity();
    lotusSetMesh(e2, vertices, 3); lotusSetMaterial(e2, materialID);
    lotusSetTransform(
        e2,
        (LMvec3){1.0, 1.0, 1.0},
        (LMvec3){0.0, 0.0, 0.0},
        (LMvec3){0.0, 0.0, 0.0}
    ); LotusTransform_itf* t2 = lotusGetTransform(e2);

    while(lotusRunning()) {
        lotusPollEvents();

        if (lotusIsKeyPressed(KEY_W)) lotusCamMovIn();
        if (lotusIsKeyPressed(KEY_S)) lotusCamMovOut();
        if (lotusIsKeyPressed(KEY_A)) lotusCamMovLeft();
        if (lotusIsKeyPressed(KEY_D)) lotusCamMovRight();
        if (lotusIsKeyPressed(KEY_SPACE)) lotusCamMovUp();
        if (lotusIsKeyPressed(KEY_LEFT_SHIFT)) lotusCamMovDown();
        if (lotusIsKeyTriggered(KEY_ESCAPE) || lotusIsKeyTriggered(KEY_F12)) lotusExit();

        t1->location->x += 0.1 * lotusGetDeltaTime();
        t2->location->x -= 0.1 * lotusGetDeltaTime();

        lotusPreProcess();
        lotusProcess();
        lotusPosProcess();
    }
    lotusReleaseTransform(t1);
    lotusReleaseTransform(t2);
    lotusCleanup(); return 0;
}