#include "../../headers/processes/atrender.h"

ATdrawCall* _atMakeDrawCall(ATdrawCallType type, int glMode) {
    ATdrawCall* dc = (ATdrawCall*)malloc(sizeof(ATdrawCall));
    if (!dc) {
        atLogError("failed to allocate draw call");
        return (ATdrawCall*)ERR_MALLOC;
    }
    
    dc->vao=-1;
    dc->shader=-1;
    dc->n_verts=-1;

    dc->type=type;
    dc->glMode=glMode;

    return dc;
}

void _atDestroyDrawCall(ATdrawCall* dc) {
    dc->vao=-1;
    dc->type=-1;
    dc->glMode=-1;
    dc->shader=-1;
    dc->n_verts=-1;

    free(dc);
}


// render process
atErrorType _atPrepRender(void* d) {
    ATrenderData* render_data = atTypeCastPtr(ATrenderData, d);

    if (render_data->nCalls <= 0) { return ERR_NONE; }

    ATdrawCall* dc = render_data->drawCallArr[render_data->nCalls-1];
    if (!dc || dc->type == ERR_DRAW) { return ERR_DRAW; }

    #ifdef _ATWIN_GL_
    #endif

    return ERR_NONE;
}

atErrorType _atMainRender(void* d) {
    ATrenderData* render_data = atTypeCastPtr(ATrenderData, d);
    
    if (render_data->nCalls <= 0) {
        glClearColor(0.0f,0.0f,0.0f,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        return ERR_NONE;
    }
    
    int remaining = render_data->nCalls;
    atForRangeI(remaining) {
        ATdrawCall* dc = render_data->drawCallArr[i];

        switch (dc->type) {
            case(DRAW_CLEAR) :
                glClearColor(
                    render_data->clearColor[0],
                    render_data->clearColor[1],
                    render_data->clearColor[2],
                    render_data->clearColor[3]
                ); glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                break;
            case (DRAW_MESH) :
                if (dc->shader != 0) {
                    glUseProgram(dc->shader);
                }
                glBindVertexArray(dc->vao);
                glDrawArrays(GL_TRIANGLES, 0, dc->n_verts);
                glBindVertexArray(0);
                break;
            default : break;
        }
        _atDestroyDrawCall(dc);
        render_data->passes++;
        render_data->nCalls--;
    }
    
    return ERR_NONE;
}

atErrorType _atPostRender(void* d) {
    ATrenderData* render_data = atTypeCastPtr(ATrenderData, d);
    SDL_GL_SwapWindow(render_data->windowPtr->_sdlWin);
    return ERR_NONE;
}
