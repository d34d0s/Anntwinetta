#include "../../headers/resource/atwindow.h"
#include "../../headers/processes/atcamera.h"

// Internal Camera API
void _atFreeLookCallback(GLFWwindow* win, double xpos, double ypos) {
    ATcameraData* cam = _atGetCameraData();
    
    float xoffset = xpos - cam->camState.last_x;
    cam->camState.last_x = xpos;
    xoffset *= cam->camSettings.sensitivity;
    cam->camSettings.yaw += xoffset;

    float yoffset = cam->camState.last_y - ypos; 
    cam->camState.last_y = ypos;
    yoffset *= cam->camSettings.sensitivity;
    cam->camSettings.pitch += yoffset;

    if (cam->camSettings.pitch > 89.0f) {
        cam->camSettings.pitch = 89.0f;
    }
    if (cam->camSettings.pitch < -89.0f) {
        cam->camSettings.pitch = -89.0f;
    }
}

void _atSetCamMode(ATcameraData* cam, ATcamMode mode) {
    cam->camState.modeSet = 0;
    cam->camState.mode = mode;
}

// Move the camera forward (along the forward vector)
void _atCamMovIn(ATcameraData* cam, float delta_time) {
    cam->camState.location = atAddVec3(cam->camState.location, atScaleVec3(cam->camState.forward, cam->camSettings.speed * delta_time));
}

// Move the camera backward (along the forward vector)
void _atCamMovOut(ATcameraData* cam, float delta_time) {
    cam->camState.location = atSubVec3(cam->camState.location, atScaleVec3(cam->camState.forward, cam->camSettings.speed * delta_time));
}

// Move the camera to the left (perpendicular to the forward vector)
void _atCamMovLeft(ATcameraData* cam, float delta_time) {
    ATvec3 left = atNormVec3(atCrossVec3(cam->camState.forward, cam->camState.up));
    cam->camState.location = atSubVec3(cam->camState.location, atScaleVec3(left, cam->camSettings.speed * delta_time));
}

// Move the camera to the right (perpendicular to the forward vector)
void _atCamMovRight(ATcameraData* cam, float delta_time) {
    ATvec3 right = atNormVec3(atCrossVec3(cam->camState.forward, cam->camState.up));
    cam->camState.location = atAddVec3(cam->camState.location, atScaleVec3(right, cam->camSettings.speed * delta_time));
}

// Move the camera up (along the up vector)
void _atCamMovUp(ATcameraData* cam, float delta_time) {
    cam->camState.location = atAddVec3(cam->camState.location, atScaleVec3(cam->camState.up, cam->camSettings.speed * delta_time));
}

// Move the camera down (along the up vector)
void _atCamMovDown(ATcameraData* cam, float delta_time) {
    cam->camState.location = atSubVec3(cam->camState.location, atScaleVec3(cam->camState.up, cam->camSettings.speed * delta_time));
}

ATerrorType _atPrepCamera(void* d) {
    ATcameraData* cam = atTypeCastPtr(ATcameraData, d);
    ATwindow* win = atTypeCastPtr(ATwindow, cam->windowPtr);

    if (cam->camState.modeSet) return ERR_NONE;

    switch (cam->camState.mode) {
        case FREELOOK_MODE:
            glfwSetCursorPosCallback(win->_glfwWin, _atFreeLookCallback);
            glfwSetInputMode(win->_glfwWin, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            cam->camState.modeSet = 1; break;
        default: break;
    }

    return ERR_NONE;
}

ATerrorType _atMainCamera(void* d) {
    ATcameraData* cam = atTypeCastPtr(ATcameraData, d);
    ATwindow* win = atTypeCastPtr(ATwindow, cam->windowPtr);

    ATvec3 forward;
    forward.x = cosf(atToRadians(cam->camSettings.yaw)) * cosf(atToRadians(cam->camSettings.pitch));
    forward.y = sinf(atToRadians(cam->camSettings.pitch));
    forward.z = sinf(atToRadians(cam->camSettings.yaw)) * cosf(atToRadians(cam->camSettings.pitch));
    cam->camState.forward = atNormVec3(forward);
    cam->camState.right = atNormVec3(atCrossVec3(cam->camState.forward, cam->camSettings.globalup));
    cam->camState.up = atNormVec3(atCrossVec3(cam->camState.right, cam->camState.forward));

    cam->camState.proj = atPerspective(cam->camSettings.fov, win->dimensions[0] / win->dimensions[1], cam->camSettings.near, cam->camSettings.far);
    cam->camState.view = atLookAt(cam->camState.location, atAddVec3(cam->camState.location, cam->camState.forward), cam->camState.up);

    return ERR_NONE;
}

ATerrorType _atPostCamera(void* d) {
    return ERR_NONE;
}
