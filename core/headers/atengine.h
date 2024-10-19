#pragma once

#include "atds.h"
#include "atmath.h"
#include "attypes.h"
#include "athelpers.h"
#include "atprocess.h"
#include "atversion.h"

#include "resource/atclock.h"
#include "resource/atwindow.h"

#include "resource/atmesh.h"
#include "resource/atmodel.h"
#include "resource/atshader.h"
#include "resource/attexture.h"
#include "resource/atmaterial.h"

#include "processes/atevent.h"
#include "processes/atrender.h"
#include "processes/atcamera.h"

#include "backend/GL/atGLAPI.h"

typedef struct Anntwinetta {
    struct info {
        char version[100];
    } info;

    struct state {
        int init;
    } state;
    
    struct internal {
        int errors;
        ATprocess* event_proc;
        ATeventData event_data;
        
        ATprocess* render_proc;
        ATrenderData render_data;
        
        ATprocess* camera_proc;
        ATcameraData camera_data;
    } internal;

    struct resource {
        int total;
        ATclock clock;

        ATwindow* window;
        ATGLcontext* context;

        ATmeshData mesh_data;
        ATmodelData model_data;
        ATshaderData shader_data;
        ATtextureData texture_data;
        ATmaterialData material_data;
    } resource;

    struct component_data {
        struct transform_data {
            int count;
        } transform_data;

        struct physics2D_data {
            int count;
        } physics2D_data;

        struct physics3D_data {
            int count;
        } physics3D_data;

    } component_data;
} Anntwinetta;


// initialize the internal engine structure
ATerrorType _atInitEngine(void);
ATerrorType _atExitEngine(void);

// internal getters/setters
Anntwinetta* _atGetEngine(void);

ATclock* _atGetClock(void);
float _atGetDeltaTime(void);

ATeventData* _atGetEventData(void);
ATrenderData* _atGetRenderData(void);

ATmeshData* _atGetMeshData(void);
ATmodelData* _atGetModelData(void);
ATshaderData* _atGetShaderData(void);
ATtextureData* _atGetTextureData(void);
ATmaterialData* _atGetMaterialData(void);

