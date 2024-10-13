#pragma once

#include "../atmath.h"
#include "../attypes.h"
#include "../athelpers.h"

typedef enum ATcamMode {
    FREELOOK_MODE=0,
    _CAM_MODE_COUNT,
} ATcamMode;

typedef struct ATcameraData {
    void* windowPtr;

    struct camState {
        ATmat4 proj;
        ATmat4 view;
        
        ATvec3 up;
        ATvec3 right;
        ATvec3 forward;
        
        ATvec3 location;
        float last_x, last_y;

        bool modeSet;
        ATcamMode mode;
    } camState;
    
    struct camSettings {
        float yaw;
        float pitch;
        
        float far;
        float near;
        
        float fov;
        float speed;
        float sensitivity;

        ATvec3 globalup;
    } camSettings;
} ATcameraData;
ATcameraData* _atGetCameraData(void);

void _atFreeLookCallback(GLFWwindow* win, double xpos, double ypos);

void _atSetCamMode(ATcameraData* cam, ATcamMode mode);

void _atCamMovUp(ATcameraData* cam, float delta_time);
void _atCamMovIn(ATcameraData* cam, float delta_time);
void _atCamMovOut(ATcameraData* cam, float delta_time);
void _atCamMovLeft(ATcameraData* cam, float delta_time);
void _atCamMovDown(ATcameraData* cam, float delta_time);
void _atCamMovRight(ATcameraData* cam, float delta_time);

ATerrorType _atPrepCamera(void* d);
ATerrorType _atMainCamera(void* d);
ATerrorType _atPostCamera(void* d);

