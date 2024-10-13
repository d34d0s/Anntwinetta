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
#include "resource/atshader.h"
#include "resource/attexture.h"

#include "processes/atevent.h"
#include "processes/atrender.h"
#include "processes/atcamera.h"

#include "../backend/headers/atGLAPI.h"

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
        ATshaderData shader_data;

        struct texture_data {
            int count;
            char** src;
            char** title;
            int* n_channels;
            int** dimensions;
        } texture_data;
        
        struct entity_data {
            int count;
            int* state;
            int* components;
        } entity_data;
    } resource;

    struct component_data {
        struct model_data {
            int count;
        } model_data;

        struct material_data {
            int count;
        } material_data;

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
ATclock* _atGetClock(void);
Anntwinetta* _atGetEngine(void);
ATmeshData* _atGetMeshData(void);
ATshaderData* _atGetShaderData(void);
float _atGetDeltaTime(void);
