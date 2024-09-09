#ifndef LOTUSCAMERA_H
#define LOTUSCAMERA_H

#include "LotusMath.h"
#include "lotus_types.h"
#include "../../backend/headers/LotusGL.h"

typedef enum LotusCameraMode {
    CAM_MODE_FREELOOK=0,
    _CAM_MODE_COUNT,
} LotusCameraMode;

typedef struct LotusCamera {
    LMvec3 up;
    LMmat4 view;
    LMmat4 proj;
    LMvec3 right;
    LMvec3 location;
    LMvec3 forward;
    LMvec3 globalup;
    float fov;
    float yaw;
    float far;
    float near;
    float pitch;
    float speed;
    float sensitivity;
    float last_x, last_y;
} LotusCamera;
static LotusCamera _LOTUS_CAMERA;

void _lotusCamMovUp(float delta_time);
void _lotusCamMovIn(float delta_time);
void _lotusCamMovOut(float delta_time);
void _lotusCamMovLeft(float delta_time);
void _lotusCamMovDown(float delta_time);
void _lotusCamMovRight(float delta_time);
void _lotusUpdateCam(GLFWwindow* window);
void _lotusFreeLookCallback(GLFWwindow* window, double xpos, double ypos);
LotusCamera* _lotusMakeCamera(GLFWwindow* window, LMvec3 location, LMvec3 up, float fov, float near, float far, unsigned int lookMode);

LOTUS_API LMmat4* lotusGetViewMatrix(void);
LOTUS_API LMmat4* lotusGetProjMatrix(void);

#endif