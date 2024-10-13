#pragma once

#include "../atmath.h"
#include "../attypes.h"
#include "../athelpers.h"

typedef enum LotusCameraMode {
    CAM_MODE_FREELOOK=0,
    _CAM_MODE_COUNT,
} LotusCameraMode;

typedef struct ATcameraData {
    void* window;
    ATvec3 up;
    ATmat4 view;
    ATmat4 proj;
    ATvec3 right;
    ATvec3 location;
    ATvec3 forward;
    ATvec3 globalup;
    float fov;
    float yaw;
    float far;
    float near;
    float pitch;
    float speed;
    float sensitivity;
    float last_x, last_y;
} ATcameraData;

void _atCamMovUp(ATcameraData* cam, float delta_time);
void _atCamMovIn(ATcameraData* cam, float delta_time);
void _atCamMovOut(ATcameraData* cam, float delta_time);
void _atCamMovLeft(ATcameraData* cam, float delta_time);
void _atCamMovDown(ATcameraData* cam, float delta_time);
void _atCamMovRight(ATcameraData* cam, float delta_time);

void _atFreeLookCallback(ATcameraData* cam, double xpos, double ypos);

atErrorType _atPrepCamera(void* d);
atErrorType _atMainCamera(void* d);
atErrorType _atPostCamera(void* d);

