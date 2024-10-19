#include "../headers/atengine.h"

static Anntwinetta ENGINE;

ATerrorType _atInitEngine(void) {
    sprintf(ENGINE.info.version, "%d.%d.%d+%d",
        ATWIN_VERSION_MAJOR,
        ATWIN_VERSION_MINOR,
        ATWIN_VERSION_YEAR,
        ATWIN_VERSION_PATCH
    );
    
    atLogInit("~Annwinetta~ | %s", ENGINE.info.version);
    atLogInfo("Platform:        %s", SDL_GetPlatform());
    atLogInfo("CPU Count:       %d", SDL_GetCPUCount());
    atLogInfo("System RAM:      %d MB", SDL_GetSystemRAM());

    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0) {
        atLogFatal("failed to initialize SDL2"); return ERR_INIT;
    }

    if (!glfwInit()) {
        atLogFatal("failed to initialize GLFW");
        return ERR_INIT;
    }

    ENGINE.resource.clock = _atMakeClock();
    ENGINE.resource.window = _atMakeWindow(800, 600, "~Anntwinetta~");
    
    ENGINE.resource.context = atglCreateContext(ENGINE.resource.window->_glfwWin);
    if (!ENGINE.resource.context) {
        atLogError("failed to create engine OpenGL context");
        return ERR_INIT;
    }
    
    // event data init
    if(_atInitEventData(&ENGINE.internal.event_data, ENGINE.resource.window)) {
        atLogError("failed to allocate event data");
        return ERR_INIT;
    }

    // camera data init
    if (_atInitCameraData(&ENGINE.internal.camera_data, ENGINE.resource.window)) {
        atLogError("failed to allocate camera data");
        return ERR_INIT;
    }
    
    // render data init
   if (_atInitRenderData(&ENGINE.internal.render_data, ENGINE.resource.window)) {
        atLogError("failed to allocate camera data");
        return ERR_INIT;
   }

    // TODO: dynamic arrays!!!!
    // resource data array size
    int nResources = 1000;

    // mesh data init
    if (_atInitMeshData(&ENGINE.resource.mesh_data, nResources)) {
        atLogError("failed to allocate mesh data");
        return ERR_INIT;
    }
    
    // model data init
    if (_atInitModelData(&ENGINE.resource.model_data, nResources)) {
        atLogError("failed to allocate model data");
        return ERR_INIT;
    }

    // shader data init
    if (_atInitShaderData(&ENGINE.resource.shader_data, nResources)) {
        atLogError("failed to allocate shader data");
        return ERR_INIT;
    }

    // texture data init
    if (_atInitTextureData(&ENGINE.resource.texture_data, nResources)) {
        atLogError("failed to allocate texture data");
        return ERR_INIT;
    }

    // material data init
    if (_atInitMaterialData(&ENGINE.resource.material_data, nResources)) {
        atLogError("failed to allocate material data");
        return ERR_INIT;
    }

    // event process
    ENGINE.internal.event_proc = atMakeProcess(
        &ENGINE.internal.event_data,
        _atPrepEvent,
        _atMainEvent,
        _atPostEvent
    ); if (!ENGINE.internal.event_proc) {
        atLogFatal("failed to create engine event process"); return ERR_MALLOC;
    };

    // render process
    ENGINE.internal.render_proc = atMakeProcess(
        &ENGINE.internal.render_data,
        _atPrepRender,
        _atMainRender,
        _atPostRender
    ); if (!ENGINE.internal.render_proc) {
        atLogFatal("failed to create engine render process"); return ERR_MALLOC;
    };

    // camera process
    ENGINE.internal.camera_proc = atMakeProcess(
        &ENGINE.internal.camera_data,
        _atPrepCamera,
        _atMainCamera,
        _atPostCamera
    ); if (!ENGINE.internal.camera_proc) {
        atLogFatal("failed to create engine camera process"); return ERR_MALLOC;
    };

    return ERR_NONE;
}

ATerrorType _atExitEngine(void) {
    SDL_Quit();
    
    _atDestroyWindow(ENGINE.resource.window);
    _atDestroyEventData(&ENGINE.internal.event_data);
    _atDestroyRenderData(&ENGINE.internal.render_data);
    _atDestroyCameraData(&ENGINE.internal.camera_data);

    atDestroyProcess(ENGINE.internal.event_proc);
    atDestroyProcess(ENGINE.internal.render_proc);
    
    #ifdef _ATWIN_GL_
        atglDestroyContext(ENGINE.resource.context);
    #endif

    _atDestroyMeshData(&ENGINE.resource.mesh_data);
    _atDestroyModelData(&ENGINE.resource.model_data);
    _atDestroyShaderData(&ENGINE.resource.shader_data);
    _atDestroyTextureData(&ENGINE.resource.texture_data);
    _atDestroyMaterialData(&ENGINE.resource.material_data);

    return ERR_NONE;
}


// internal getters/setters
Anntwinetta* _atGetEngine(void) {
    return &ENGINE;
}

ATclock* _atGetClock(void) {
    return &ENGINE.resource.clock;
}

float _atGetDeltaTime(void) {
    return ENGINE.resource.clock.delta;
}

ATeventData* _atGetEventData(void) {
    return &ENGINE.internal.event_data;
}

ATrenderData* _atGetRenderData(void) {
    return &ENGINE.internal.render_data;
}

ATcameraData* _atGetCameraData(void) {
    return &ENGINE.internal.camera_data;
}

ATmeshData* _atGetMeshData(void) {
    return &ENGINE.resource.mesh_data;
}

ATshaderData* _atGetShaderData(void) {
    return &ENGINE.resource.shader_data;
}

ATmodelData* _atGetModelData(void) {
    return &ENGINE.resource.model_data;
}

ATtextureData* _atGetTextureData(void) {
    return &ENGINE.resource.texture_data;
}

ATmaterialData* _atGetMaterialData(void) {
    return &ENGINE.resource.material_data;
}

