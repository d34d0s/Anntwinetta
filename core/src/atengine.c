#include "../headers/atengine.h"

static Anntwinetta ENGINE;

ATerrorType _atInitEngine(void) {
    sprintf(ENGINE.info.version, "%d.%d.%d+%d",
        ATWIN_VERSION_MAJOR,
        ATWIN_VERSION_MINOR,
        ATWIN_VERSION_YEAR,
        ATWIN_VERSION_PATCH
    );
    
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

    // event data init
    ENGINE.internal.event_data.quit = 0;
    _atInitEventData(&ENGINE.internal.event_data);
    ENGINE.internal.event_data.windowPtr = ENGINE.resource.window->_glfwWin;


    // camera data init
    // TODO: make _atInitCameraData()!!!
    ENGINE.internal.camera_data.windowPtr = ENGINE.resource.window;
    
    ENGINE.internal.camera_data.camState.last_x = 0.0f;
    ENGINE.internal.camera_data.camState.last_y = 0.0f;
    
    ENGINE.internal.camera_data.camSettings.yaw = -90.0f;
    ENGINE.internal.camera_data.camSettings.pitch = 0.0f;
    ENGINE.internal.camera_data.camSettings.far = 1000.0f;
    ENGINE.internal.camera_data.camSettings.near = 0.1f;
    ENGINE.internal.camera_data.camSettings.fov = atToRadians(45.0f);
    ENGINE.internal.camera_data.camSettings.speed = 2.5f;
    ENGINE.internal.camera_data.camSettings.sensitivity = 0.1f;
    ENGINE.internal.camera_data.camSettings.globalup = atNewVec3(0, 1, 0);
    
    ENGINE.internal.camera_data.camState.forward = atNewVec3(0.0f, 0.0f, -1.0f);
    ENGINE.internal.camera_data.camState.location = atNewVec3(0, 0, 3);
    
    int w = ENGINE.resource.window->dimensions[0];
    int h = ENGINE.resource.window->dimensions[1];
    ENGINE.internal.camera_data.camState.proj = atPerspective(ENGINE.internal.camera_data.camSettings.fov, w / h, ENGINE.internal.camera_data.camSettings.near, ENGINE.internal.camera_data.camSettings.far);
    ENGINE.internal.camera_data.camState.view = atLookAt(ENGINE.internal.camera_data.camState.location, atAddVec3(ENGINE.internal.camera_data.camState.location, ENGINE.internal.camera_data.camState.forward), ENGINE.internal.camera_data.camState.up);
    
    // render data init
    // TODO: make _atInitRenderData()!!!
    ENGINE.internal.render_data.glMode=TRIANGLE_MODE;
    ENGINE.internal.render_data.passes=0;
    ENGINE.internal.render_data.nCalls = 0;
    ENGINE.internal.render_data.clearColor[0] = 0.4;
    ENGINE.internal.render_data.clearColor[1] = 0.2;
    ENGINE.internal.render_data.clearColor[2] = 0.6;
    ENGINE.internal.render_data.clearColor[3] = 1.0;
    ENGINE.internal.render_data.windowPtr = ENGINE.resource.window;
    ENGINE.internal.render_data.drawCallArr = (ATdrawCall**)malloc(DRAW_CALL_MAX*sizeof(ATdrawCall*));
    if (!ENGINE.internal.render_data.drawCallArr) {
        atLogError("failed to allocate engine draw call array");
        return ERR_MALLOC;
    }

    // TODO: dynamic arrays!!!!
    // resource data array size
    int rsrc_max = 100;
    
    ENGINE.resource.entity_data.count = 0;
    atInitIntArray(&ENGINE.resource.entity_data.state, rsrc_max, "entity data [state]");
    atInitIntArray(&ENGINE.resource.entity_data.components, rsrc_max, "entity data [components]");

    ENGINE.resource.mesh_data.count = 0;
    atInitIntArray(&ENGINE.resource.mesh_data.vbo, rsrc_max, "mesh data [vbo]");
    atInitIntArray(&ENGINE.resource.mesh_data.vao, rsrc_max, "mesh data [vao]");
    atInitIntArray(&ENGINE.resource.mesh_data.n_verts, rsrc_max, "mesh data [n verts]");
    
    ENGINE.resource.shader_data.count = 0;
    
    ENGINE.resource.shader_data.uniforms = (AThashmap**)malloc(rsrc_max * sizeof(AThashmap*));
    if (!ENGINE.resource.shader_data.uniforms) {
        atLogError("failed to allocate shader data uniform hashmap array");
        return ERR_MALLOC;
    }

    atInitIntArray(&ENGINE.resource.shader_data.program, rsrc_max, "shader data [program]");
    atInitIntArray(&ENGINE.resource.shader_data.n_uniforms, rsrc_max, "shader data [n uniforms]");
    atInitConstCharPointerArray(&ENGINE.resource.shader_data.vSrc, rsrc_max, 1024, "shader data [vSrc]");
    atInitConstCharPointerArray(&ENGINE.resource.shader_data.fSrc, rsrc_max, 1024, "shader data [fSrc]");
    
    ENGINE.resource.texture_data.count = 0;
    atInitCharPointerArray(&ENGINE.resource.texture_data.src, rsrc_max, 256, "texture data [src]");
    atInitIntArray(&ENGINE.resource.texture_data.n_channels, rsrc_max, "texture data [n channels]");
    atInitCharPointerArray(&ENGINE.resource.texture_data.title, rsrc_max, 256, "texture data [title]");
    atInitIntPointerArray(&ENGINE.resource.texture_data.dimensions, rsrc_max, 2, "texture data [dimensions]");

    atLogInit("~Annwinetta~ | %s", ENGINE.info.version);
    atLogInfo("Platform:        %s", SDL_GetPlatform());
    atLogInfo("CPU Count:       %d", SDL_GetCPUCount());
    atLogInfo("System RAM:      %d MB", SDL_GetSystemRAM());

    return ERR_NONE;
}

ATerrorType _atExitEngine(void) {
    SDL_Quit();
    
    _atDestroyWindow(ENGINE.resource.window);
    atDestroyProcess(ENGINE.internal.event_proc);
    atDestroyProcess(ENGINE.internal.render_proc);
    
    #ifdef _ATWIN_GL_
        atglDestroyContext(ENGINE.resource.context);
    #endif

    free(ENGINE.resource.entity_data.state);
    free(ENGINE.resource.entity_data.components);

    free(ENGINE.resource.mesh_data.vbo);
    free(ENGINE.resource.mesh_data.vao);
    free(ENGINE.resource.mesh_data.n_verts);
    
    free(ENGINE.resource.shader_data.vSrc);
    free(ENGINE.resource.shader_data.fSrc);
    free(ENGINE.resource.shader_data.program);
    atForRangeI(ENGINE.resource.shader_data.count) {
        atDestroyHashmap(ENGINE.resource.shader_data.uniforms[i]);
    }; free(ENGINE.resource.shader_data.n_uniforms);
    
    free(ENGINE.resource.texture_data.src);
    free(ENGINE.resource.texture_data.title);
    free(ENGINE.resource.texture_data.n_channels);
    free(ENGINE.resource.texture_data.dimensions);
    
    free(ENGINE.internal.render_data.drawCallArr);

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

ATmeshData* _atGetMeshData(void) {
    return &ENGINE.resource.mesh_data;
}

ATshaderData* _atGetShaderData(void) {
    return &ENGINE.resource.shader_data;
}

ATcameraData* _atGetCameraData(void) {
    return &ENGINE.internal.camera_data;
}

