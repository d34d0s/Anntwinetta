#include "../headers/atengine.h"

static Anntwinetta ENGINE;

atErrorType _atInitEngine(void) {
    // _atwin_log_init("~Annwinetta~ | %s", ATWIN.ver);
    
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS) < 0) {
        atLogFatal("failed to initialize SDL2"); return ERR_INIT;
    }

    ENGINE.resource.window = _atMakeWindow(800, 600, "~Anntwinetta~");
    #ifdef _ATWIN_GL_
        ENGINE.resource.context = atglCreateContext(ENGINE.resource.window->_sdlWin);
        if (!ENGINE.resource.context) {
            atLogError("failed to create engine OpenGL context");
            return ERR_INIT;
        }
    #endif
    
    ENGINE.internal.event_data.quit = 0;
    ENGINE.internal.event_data._sdlEvent = (SDL_Event*)malloc(sizeof(SDL_Event));
    if (!ENGINE.internal.event_data._sdlEvent) {
        atLogFatal("failed to allocate SDL event structure"); return ERR_MALLOC;
    };

    ENGINE.internal.event_proc = atMakeProcess(
        &ENGINE.internal.event_data,
        _atPrepEvent,
        _atMainEvent,
        _atPostEvent
    ); if (!ENGINE.internal.event_proc) {
        atLogFatal("failed to create engine event process"); return ERR_MALLOC;
    };

    ENGINE.internal.render_proc = atMakeProcess(
        &ENGINE.internal.render_data,
        _atPrepRender,
        _atMainRender,
        _atPostRender
    ); if (!ENGINE.internal.render_proc) {
        atLogFatal("failed to create engine render process"); return ERR_MALLOC;
    };

    
    #ifdef _ATWIN_GL_
        ENGINE.internal.render_data.glMode=GL_TRIANGLES;
    #else
        ENGINE.internal.render_data.glMode=0;
    #endif
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

    // resource data
    int rsrc_max = 100;
    
    ENGINE.resource.entity_data.count = 0;
    atInitIntArray(&ENGINE.resource.entity_data.state, rsrc_max, "entity data [state]");
    atInitIntArray(&ENGINE.resource.entity_data.components, rsrc_max, "entity data [components]");

    ENGINE.resource.mesh_data.count = 0;
    atInitIntArray(&ENGINE.resource.mesh_data.vbo, rsrc_max, "mesh data [vbo]");
    atInitIntArray(&ENGINE.resource.mesh_data.vao, rsrc_max, "mesh data [vao]");
    atInitIntArray(&ENGINE.resource.mesh_data.n_verts, rsrc_max, "mesh data [n verts]");
    
    ENGINE.resource.shader_data.count = 0;
    atInitIntArray(&ENGINE.resource.shader_data.program, rsrc_max, "shader data [program]");
    atInitIntArray(&ENGINE.resource.shader_data.n_uniforms, rsrc_max, "shader data [n uniforms]");
    atInitConstCharPointerArray(&ENGINE.resource.shader_data.vSrc, rsrc_max, 1024, "shader data [vSrc]");
    atInitConstCharPointerArray(&ENGINE.resource.shader_data.fSrc, rsrc_max, 1024, "shader data [fSrc]");
    
    ENGINE.resource.texture_data.count = 0;
    atInitCharPointerArray(&ENGINE.resource.texture_data.src, rsrc_max, 256, "texture data [src]");
    atInitIntArray(&ENGINE.resource.texture_data.n_channels, rsrc_max, "texture data [n channels]");
    atInitCharPointerArray(&ENGINE.resource.texture_data.title, rsrc_max, 256, "texture data [title]");
    atInitIntPointerArray(&ENGINE.resource.texture_data.dimensions, rsrc_max, 2, "texture data [dimensions]");

    atLogInfo("Platform:        %s", SDL_GetPlatform());
    atLogInfo("CPU Count:       %d", SDL_GetCPUCount());
    atLogInfo("System RAM:      %d MB", SDL_GetSystemRAM());

    return ERR_NONE;
}

atErrorType _atExitEngine(void) {
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
    
    free(ENGINE.resource.shader_data.program);
    free(ENGINE.resource.shader_data.n_uniforms);
    
    free(ENGINE.resource.texture_data.src);
    free(ENGINE.resource.texture_data.title);
    free(ENGINE.resource.texture_data.n_channels);
    free(ENGINE.resource.texture_data.dimensions);
    
    free(ENGINE.internal.event_data._sdlEvent);
    free(ENGINE.internal.render_data.drawCallArr);

    return ERR_NONE;
}


// internal getters/setters
Anntwinetta* _atGetEngine(void) {
    return &ENGINE;
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


