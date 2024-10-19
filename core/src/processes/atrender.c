#include "../../headers/processes/atrender.h"

void _atDestroyRenderData(ATrenderData* d) {
    d->glMode = 0;
    d->passes=0;
    d->nCalls = 0;
    d->windowPtr = NULL;
    free(d->drawCallArr);
    free(d);
}

ATerrorType _atInitRenderData(ATrenderData* d, ATwindow* w) {
    d->glMode=TRIANGLE_MODE;
    d->passes=0;
    d->nCalls = 0;
    d->clearColor[0] = 0.4;
    d->clearColor[1] = 0.2;
    d->clearColor[2] = 0.6;
    d->clearColor[3] = 1.0;
    d->windowPtr = w;
    
    d->drawCallArr = (ATdrawCall**)malloc(DRAW_CALL_MAX*sizeof(ATdrawCall*));
    if (!d->drawCallArr) {
        atLogError("failed to allocate engine draw call array");
        return ERR_MALLOC;
    }

    return ERR_NONE;
}

ATdrawCall* _atMakeDrawCall(ATdrawCallType type) {
    ATdrawCall* dc = (ATdrawCall*)malloc(sizeof(ATdrawCall));
    if (!dc) {
        atLogError("failed to allocate draw call");
        return (ATdrawCall*)ERR_MALLOC;
    }
    
    dc->vao=-1;
    dc->shader=-1;
    dc->n_verts=-1;
    dc->type=type;

    return dc;
}

void _atDestroyDrawCall(ATdrawCall* dc) {
    dc->vao=-1;
    dc->type=-1;
    dc->shader=-1;
    dc->n_verts=-1;
    free(dc);
}


// render process
ATerrorType _atPrepRender(void* d) {
    ATrenderData* render_data = atTypeCastPtr(ATrenderData, d);

    if (render_data->nCalls <= 0) { return ERR_NONE; }

    ATdrawCall* dc = render_data->drawCallArr[render_data->nCalls-1];
    if (!dc || dc->type == ERR_DRAW) { return ERR_DRAW; }

    #ifdef _ATWIN_GL_
    #endif

    return ERR_NONE;
}

ATerrorType _atMainRender(void* d) {
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
            case (DRAW_MODEL) :
                if (dc->shader != 0) {
                    glUseProgram(dc->shader);
                }
                glBindVertexArray(dc->vao);
                glDrawArrays(render_data->glMode, 0, dc->n_verts);
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

ATerrorType _atPostRender(void* d) {
    ATrenderData* render_data = atTypeCastPtr(ATrenderData, d);
    glfwSwapBuffers(render_data->windowPtr->_glfwWin);
    return ERR_NONE;
}
