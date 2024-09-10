#include "headers/LotusProc.h"
#include "headers/LotusCamera.h"

void _lotusInitRenderer(LotusRenderer* r, GLFWwindow* ref) {
    r->ref=ref;
    r->ncalls=0;
    r->passes=0;
    r->calls = (LotusDrawCall*)malloc(sizeof(LotusDrawCall)*LOTUS_MAX_DRAW_QUEUE);
    if (!r->calls) {
        _lotusLogError("Error Allocating Memory For Lotus Renderer DrawCall Queue");
        return;
    }
    r->clearColor=(LMvec4){0.07f, 0.088, 0.126f, 1.0f};
    glClearColor(r->clearColor.x, r->clearColor.y, r->clearColor.z, r->clearColor.w);
}

// TODO: profile the DrawCall queue!
void _lotusPreProcessing(LotusRenderer* r) {
    if (r->ncalls >= LOTUS_MAX_DRAW_QUEUE) return;
    
    static LMmat4 identity;
    identity = lmIdentity();
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    LotusEntity* ents = *_lotusGetEntityArray();
    unsigned short nents = _lotusGetEntityCount();
    for (int e = 0; e < nents; e++) {
        LotusMesh_itf* mesh = lotusGetMesh(&ents[e]);
        if (!mesh) continue;
        LotusDrawCall* dc = &r->calls[r->ncalls++];
        LotusMaterial_itf* material = lotusGetMaterial(&ents[e]);
        // printf("PRE-PROCESSING ENTITY: %d | MAID: %d\n", e, material->MAID);
        LotusTransform_itf* transform = lotusGetTransform(&ents[e]);
        
        if (transform != NULL) {
            *transform->model = lmIdentity();
            
            // Apply Scaling
            *transform->model = lmMulMat4(*transform->model, lmScaleMat4(transform->scale->x, transform->scale->y, transform->scale->z));

            // Apply Rotations
            *transform->model = lmMulMat4(*transform->model, lmRotMat4(1, 0, 0, transform->rotation->x));
            *transform->model = lmMulMat4(*transform->model, lmRotMat4(0, 1, 0, transform->rotation->y));
            *transform->model = lmMulMat4(*transform->model, lmRotMat4(0, 0, 1, transform->rotation->z));
            
            // Apply Translations
            *transform->model = lmMulMat4(*transform->model, lmTransMat4(transform->location->x, transform->location->y, transform->location->z));
        }
        
        if (material != NULL) {
            dc->nuniforms = material->nuniforms;
            _lotusSetUniformValue(&material->shader, UMODEL_INDEX, (!transform) ? &identity : transform->model);
            _lotusSetUniformValue(&material->shader, UVIEW_INDEX, lotusGetViewMatrix());
            _lotusSetUniformValue(&material->shader, UPROJ_INDEX, lotusGetProjMatrix());
        }

        dc->type = LOTUS_DRAW_MONO;
        dc->vao = mesh->vao;
        dc->vbo = mesh->vbo;
        dc->nverts = mesh->nverts;
        dc->material = (material == NULL) ? NULL : material;
    }
}

void _lotusPostProcessing(LotusRenderer* r) {
    // TODO: shift down r->calls array
    r->ncalls = 0;
    glfwSwapBuffers(r->ref);
}

