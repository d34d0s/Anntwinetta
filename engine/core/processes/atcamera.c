#include "../../headers/resource/atwindow.h"
#include "../../headers/processes/atcamera.h"

// Internal Camera API
void _atFreeLookCallback(ATcameraData* cam, double xpos, double ypos) {

    float xoffset = xpos - cam->last_x;
    float yoffset = cam->last_y - ypos; 
    cam->last_x = xpos;
    cam->last_y = ypos;

    xoffset *= cam->sensitivity;
    yoffset *= cam->sensitivity;

    // Correct pitch and yaw assignment
    cam->yaw += xoffset;
    cam->pitch += yoffset;

    // Constrain pitch
    if (cam->pitch > 89.0f)
        cam->pitch = 89.0f;
    if (cam->pitch < -89.0f)
        cam->pitch = -89.0f;
}

// Move the camera forward (along the forward vector)
void _atCamMovIn(ATcameraData* cam, float delta_time) {
    cam->location = atAddVec3(cam->location, atScaleVec3(cam->forward, cam->speed * delta_time));
}

// Move the camera backward (along the forward vector)
void _atCamMovOut(ATcameraData* cam, float delta_time) {
    cam->location = atSubVec3(cam->location, atScaleVec3(cam->forward, cam->speed * delta_time));
}

// Move the camera to the left (perpendicular to the forward vector)
void _atCamMovLeft(ATcameraData* cam, float delta_time) {
    ATvec3 left = atNormVec3(atCrossVec3(cam->forward, cam->up));
    cam->location = atSubVec3(cam->location, atScaleVec3(left, cam->speed * delta_time));
}

// Move the camera to the right (perpendicular to the forward vector)
void _atCamMovRight(ATcameraData* cam, float delta_time) {
    ATvec3 right = atNormVec3(atCrossVec3(cam->forward, cam->up));
    cam->location = atAddVec3(cam->location, atScaleVec3(right, cam->speed * delta_time));
}

// Move the camera up (along the up vector)
void _atCamMovUp(ATcameraData* cam, float delta_time) {
    cam->location = atAddVec3(cam->location, atScaleVec3(cam->up, cam->speed * delta_time));
}

// Move the camera down (along the up vector)
void _atCamMovDown(ATcameraData* cam, float delta_time) {
    cam->location = atSubVec3(cam->location, atScaleVec3(cam->up, cam->speed * delta_time));
}

atErrorType _atPrepCamera(void* d) {
    return ERR_NONE;
}

atErrorType _atMainCamera(void* d) {
    ATcameraData* cam = atTypeCastPtr(ATcameraData, d);
    ATwindow* win = atTypeCastPtr(ATwindow, cam->window);

    ATvec3 forward;
    forward.x = cosf(atToRadians(cam->yaw)) * cosf(atToRadians(cam->pitch));
    forward.y = sinf(atToRadians(cam->pitch));
    forward.z = sinf(atToRadians(cam->yaw)) * cosf(atToRadians(cam->pitch));
    cam->forward = atNormVec3(forward);
    cam->right = atNormVec3(atCrossVec3(cam->forward, cam->globalup));
    cam->up = atNormVec3(atCrossVec3(cam->right, cam->forward));

    int w, h; SDL_GetWindowSize(win->_sdlWin, &w, &h);
    cam->proj = atPerspective(cam->fov, w / h, cam->near, cam->far);
    cam->view = atLookAt(cam->location, atAddVec3(cam->location, cam->forward), cam->up);

    return ERR_NONE;
}

atErrorType _atPostCamera(void* d) {
    return ERR_NONE;
}
