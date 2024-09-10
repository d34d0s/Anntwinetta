#include "headers/LotusShapesEXT.h"

// 2D SHAPES
void lotusTriangleMesh(LotusEntity* e) {
    unsigned short lotusTriangleVertCount = 3;
    float lotusTriangleVerts[] = {
        -0.5f, -0.5f, 0.5f,     1.0, 0.0, 0.0,
        0.0f,  0.5f, 0.5f,      0.0, 1.0, 0.0,
        0.5f, -0.5f, 0.5f,      0.0, 0.0, 1.0
    };
    lotusSetMesh(e, lotusTriangleVerts, lotusTriangleVertCount, 1);
}

void lotusQuadMesh(LotusEntity* e) {
    unsigned short lotusQuadVertCount = 6;
    float lotusQuadVerts[] = {
        -0.5f, -0.5f, 0.5f,     1.0, 0.0, 0.0,
        -0.5f, 0.5f, 0.5f,      0.0, 1.0, 0.0,
        0.5f, 0.5f, 0.5f,       0.0, 0.0, 1.0,
        -0.5f, -0.5f, 0.5f,     0.0, 1.0, 1.0,
        0.5f, 0.5f, 0.5f,       1.0, 1.0, 0.0,
        0.5f, -0.5f, 0.5f,      1.0, 0.0, 1.0
    };
    lotusSetMesh(e, lotusQuadVerts, lotusQuadVertCount, 1);
}

void lotusLongQuadMesh(LotusEntity* e) {
    unsigned short lotusLongQuadVertCount = 6;
    float lotusLongQuadVerts[] = {
        -1.0f, -0.5f, 0.0f,
        -1.0f, 0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        -1.0f, -0.5f, 0.0f,
        1.0f, 0.5f, 0.0f,
        1.0f, -0.5f, 0.0f
    };
    lotusSetMesh(e, lotusLongQuadVerts, lotusLongQuadVertCount, 0);
}

void lotusCircleMesh(LotusEntity* e) {
    unsigned int segments = 36; // Number of segments for the circle
    float radius = 0.5f;
    unsigned short lotusCircleVertCount = segments * 3; // Each segment is a triangle
    float lotusCircleVerts[108 * 3];

    unsigned int vertIndex = 0;

    // Center of the circle
    for (unsigned int i = 0; i < segments; i++) {
        float angle1 = 2.0f * LM_PI * i / segments;
        float angle2 = 2.0f * LM_PI * (i + 1) / segments;

        // Center vertex
        lotusCircleVerts[vertIndex++] = 0.0f;
        lotusCircleVerts[vertIndex++] = 0.0f;
        lotusCircleVerts[vertIndex++] = 0.0f;

        // Edge vertex 1
        lotusCircleVerts[vertIndex++] = radius * cosf(angle1);
        lotusCircleVerts[vertIndex++] = radius * sinf(angle1);
        lotusCircleVerts[vertIndex++] = 0.0f;

        // Edge vertex 2
        lotusCircleVerts[vertIndex++] = radius * cosf(angle2);
        lotusCircleVerts[vertIndex++] = radius * sinf(angle2);
        lotusCircleVerts[vertIndex++] = 0.0f;
    }

    lotusSetMesh(e, lotusCircleVerts, lotusCircleVertCount, 0);
}


// 3D SHAPES
void lotusConeMesh(LotusEntity* e) {
    unsigned int segments = 36; // Number of segments for the cone base
    float radius = 0.5f;
    float height = 1.0f;
    unsigned short lotusConeVertCount = segments * 3 * 2; // Base + sides
    float lotusConeVerts[216 * 3];

    unsigned int vertIndex = 0;

    // Cone tip
    for (unsigned int i = 0; i < segments; i++) {
        float angle1 = 2.0f * LM_PI * i / segments;
        float angle2 = 2.0f * LM_PI * (i + 1) / segments;

        // Tip
        lotusConeVerts[vertIndex++] = 0.0f;
        lotusConeVerts[vertIndex++] = height;
        lotusConeVerts[vertIndex++] = 0.0f;

        // Base vertex 1 (rotated by 90 degrees around the X-axis)
        float x1 = radius * cosf(angle1);
        float z1 = radius * sinf(angle1);
        lotusConeVerts[vertIndex++] = x1;
        lotusConeVerts[vertIndex++] = 0.0f;
        lotusConeVerts[vertIndex++] = z1;

        // Base vertex 2 (rotated by 90 degrees around the X-axis)
        float x2 = radius * cosf(angle2);
        float z2 = radius * sinf(angle2);
        lotusConeVerts[vertIndex++] = x2;
        lotusConeVerts[vertIndex++] = 0.0f;
        lotusConeVerts[vertIndex++] = z2;
    }

    // Base center
    for (unsigned int i = 0; i < segments; i++) {
        float angle1 = 2.0f * LM_PI * i / segments;
        float angle2 = 2.0f * LM_PI * (i + 1) / segments;

        // Center
        lotusConeVerts[vertIndex++] = 0.0f;
        lotusConeVerts[vertIndex++] = 0.0f;
        lotusConeVerts[vertIndex++] = 0.0f;

        // Base vertex 1 (rotated by 90 degrees around the X-axis)
        float x1 = radius * cosf(angle1);
        float z1 = radius * sinf(angle1);
        lotusConeVerts[vertIndex++] = x1;
        lotusConeVerts[vertIndex++] = 0.0f;
        lotusConeVerts[vertIndex++] = z1;

        // Base vertex 2 (rotated by 90 degrees around the X-axis)
        float x2 = radius * cosf(angle2);
        float z2 = radius * sinf(angle2);
        lotusConeVerts[vertIndex++] = x2;
        lotusConeVerts[vertIndex++] = 0.0f;
        lotusConeVerts[vertIndex++] = z2;
    }

    lotusSetMesh(e, lotusConeVerts, lotusConeVertCount, 0);
}

void lotusTorusMesh(LotusEntity* e) {
    unsigned int segments = 36; // Number of segments for the torus
    unsigned int ringSegments = 36; // Number of segments per ring
    float innerRadius = 0.2f;
    float outerRadius = 0.5f;
    unsigned short lotusTorusVertCount = segments * ringSegments * 6; // Each quad is split into two triangles
    float lotusTorusVerts[7776 * 3];

    unsigned int vertIndex = 0;
    float thetaStep = 2.0f * LM_PI / segments;
    float phiStep = 2.0f * LM_PI / ringSegments;

    for (unsigned int i = 0; i < segments; i++) {
        float theta1 = i * thetaStep;
        float theta2 = (i + 1) * thetaStep;

        for (unsigned int j = 0; j < ringSegments; j++) {
            float phi1 = j * phiStep;
            float phi2 = (j + 1) * phiStep;

            float x1 = (outerRadius + innerRadius * cosf(phi1)) * cosf(theta1);
            float y1 = (outerRadius + innerRadius * cosf(phi1)) * sinf(theta1);
            float z1 = innerRadius * sinf(phi1);

            float x2 = (outerRadius + innerRadius * cosf(phi2)) * cosf(theta1);
            float y2 = (outerRadius + innerRadius * cosf(phi2)) * sinf(theta1);
            float z2 = innerRadius * sinf(phi2);

            float x3 = (outerRadius + innerRadius * cosf(phi2)) * cosf(theta2);
            float y3 = (outerRadius + innerRadius * cosf(phi2)) * sinf(theta2);
            float z3 = innerRadius * sinf(phi2);

            float x4 = (outerRadius + innerRadius * cosf(phi1)) * cosf(theta2);
            float y4 = (outerRadius + innerRadius * cosf(phi1)) * sinf(theta2);
            float z4 = innerRadius * sinf(phi1);

            // Triangle 1
            lotusTorusVerts[vertIndex++] = x1;
            lotusTorusVerts[vertIndex++] = y1;
            lotusTorusVerts[vertIndex++] = z1;

            lotusTorusVerts[vertIndex++] = x2;
            lotusTorusVerts[vertIndex++] = y2;
            lotusTorusVerts[vertIndex++] = z2;

            lotusTorusVerts[vertIndex++] = x3;
            lotusTorusVerts[vertIndex++] = y3;
            lotusTorusVerts[vertIndex++] = z3;

            // Triangle 2
            lotusTorusVerts[vertIndex++] = x1;
            lotusTorusVerts[vertIndex++] = y1;
            lotusTorusVerts[vertIndex++] = z1;

            lotusTorusVerts[vertIndex++] = x3;
            lotusTorusVerts[vertIndex++] = y3;
            lotusTorusVerts[vertIndex++] = z3;

            lotusTorusVerts[vertIndex++] = x4;
            lotusTorusVerts[vertIndex++] = y4;
            lotusTorusVerts[vertIndex++] = z4;
        }
    }

    lotusSetMesh(e, lotusTorusVerts, lotusTorusVertCount, 0);
}

void lotusCubeMesh(LotusEntity* e) {
    unsigned short lotusCubeVertCount = 36;
    float lotusCubeVerts[] = {
        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f,  0.5f, -0.5f,  
        0.5f,  0.5f, -0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f, -0.5f,  0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  

        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f, -0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  

        0.5f,  0.5f,  0.5f,  
        0.5f,  0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  

        -0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f, -0.5f,  
        0.5f, -0.5f,  0.5f,  
        0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f,  0.5f,  
        -0.5f, -0.5f, -0.5f,  

        -0.5f,  0.5f, -0.5f,  
        0.5f,  0.5f, -0.5f,  
        0.5f,  0.5f,  0.5f,  
        0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f,  0.5f,  
        -0.5f,  0.5f, -0.5f   
    }; lotusSetMesh(e, lotusCubeVerts, lotusCubeVertCount, 0);
}

void lotusPyramidMesh(LotusEntity* e) {
    float lotusPyramidVerts[] = {
        // Base (square)
        -0.5f,  0.0f, -0.5f,  // Bottom left
         0.5f,  0.0f, -0.5f,  // Bottom right
         0.5f,  0.0f,  0.5f,  // Top right
         0.5f,  0.0f,  0.5f,  // Top right
        -0.5f,  0.0f,  0.5f,  // Top left
        -0.5f,  0.0f, -0.5f,  // Bottom left

        // Side 1 (triangle)
        -0.5f,  0.0f, -0.5f,  // Bottom left of base
         0.0f,  1.0f,  0.0f,  // Apex of the pyramid
         0.5f,  0.0f, -0.5f,  // Bottom right of base

        // Side 2 (triangle)
         0.5f,  0.0f, -0.5f,  // Bottom right of base
         0.0f,  1.0f,  0.0f,  // Apex of the pyramid
         0.5f,  0.0f,  0.5f,  // Top right of base

        // Side 3 (triangle)
         0.5f,  0.0f,  0.5f,  // Top right of base
         0.0f,  1.0f,  0.0f,  // Apex of the pyramid
        -0.5f,  0.0f,  0.5f,  // Top left of base

        // Side 4 (triangle)
        -0.5f,  0.0f,  0.5f,  // Top left of base
         0.0f,  1.0f,  0.0f,  // Apex of the pyramid
        -0.5f,  0.0f, -0.5f   // Bottom left of base
    };

    lotusSetMesh(e, lotusPyramidVerts, 18, 0);
}

void lotusCylinderMesh(LotusEntity* e) {
    const unsigned short segmentCount = 16;  // Number of segments for the circular base
    unsigned short lotusCylinderVertCount = 192; // Each side of the cylinder has 2 triangles per segment (12 vertices per segment)
    float lotusCylinderVerts[192 * 3]; // Dynamically calculate the vertex array

    float angleStep = 2.0f * 3.14159f / (float)segmentCount;
    float radius = 0.5f;
    float height = 1.0f;
    
    int idx = 0;

    // Generate the vertices for the top and bottom circle
    for (unsigned short i = 0; i < segmentCount; i++) {
        float theta = i * angleStep;
        float nextTheta = (i + 1) % segmentCount * angleStep;

        // Bottom Circle
        lotusCylinderVerts[idx++] = radius * cosf(theta);  // x
        lotusCylinderVerts[idx++] = -height / 2;           // y (bottom)
        lotusCylinderVerts[idx++] = radius * sinf(theta);  // z

        lotusCylinderVerts[idx++] = 0.0f;                 // center point of bottom circle
        lotusCylinderVerts[idx++] = -height / 2;          // y (bottom)
        lotusCylinderVerts[idx++] = 0.0f;

        lotusCylinderVerts[idx++] = radius * cosf(nextTheta);  // x
        lotusCylinderVerts[idx++] = -height / 2;               // y (bottom)
        lotusCylinderVerts[idx++] = radius * sinf(nextTheta);  // z

        // Top Circle
        lotusCylinderVerts[idx++] = radius * cosf(theta);   // x
        lotusCylinderVerts[idx++] = height / 2;            // y (top)
        lotusCylinderVerts[idx++] = radius * sinf(theta);  // z

        lotusCylinderVerts[idx++] = 0.0f;                  // center point of top circle
        lotusCylinderVerts[idx++] = height / 2;            // y (top)
        lotusCylinderVerts[idx++] = 0.0f;

        lotusCylinderVerts[idx++] = radius * cosf(nextTheta);  // x
        lotusCylinderVerts[idx++] = height / 2;                // y (top)
        lotusCylinderVerts[idx++] = radius * sinf(nextTheta);  // z
    }

    // Generate the vertices for the sides
    for (unsigned short i = 0; i < segmentCount; i++) {
        float theta = i * angleStep;
        float nextTheta = (i + 1) % segmentCount * angleStep;

        // First triangle for this segment
        lotusCylinderVerts[idx++] = radius * cosf(theta);     // x (bottom left)
        lotusCylinderVerts[idx++] = -height / 2;             // y (bottom)
        lotusCylinderVerts[idx++] = radius * sinf(theta);    // z

        lotusCylinderVerts[idx++] = radius * cosf(theta);    // x (top left)
        lotusCylinderVerts[idx++] = height / 2;             // y (top)
        lotusCylinderVerts[idx++] = radius * sinf(theta);   // z

        lotusCylinderVerts[idx++] = radius * cosf(nextTheta);  // x (bottom right)
        lotusCylinderVerts[idx++] = -height / 2;               // y (bottom)
        lotusCylinderVerts[idx++] = radius * sinf(nextTheta);  // z

        // Second triangle for this segment
        lotusCylinderVerts[idx++] = radius * cosf(nextTheta);  // x (bottom right)
        lotusCylinderVerts[idx++] = -height / 2;               // y (bottom)
        lotusCylinderVerts[idx++] = radius * sinf(nextTheta);  // z

        lotusCylinderVerts[idx++] = radius * cosf(theta);    // x (top left)
        lotusCylinderVerts[idx++] = height / 2;             // y (top)
        lotusCylinderVerts[idx++] = radius * sinf(theta);   // z

        lotusCylinderVerts[idx++] = radius * cosf(nextTheta);  // x (top right)
        lotusCylinderVerts[idx++] = height / 2;                // y (top)
        lotusCylinderVerts[idx++] = radius * sinf(nextTheta);  // z
    } lotusSetMesh(e, lotusCylinderVerts, lotusCylinderVertCount, 0);
}

void lotusSphereMesh(LotusEntity* e) {
    const unsigned short longitudeSegments = 16;
    const unsigned short latitudeSegments = 16;
    const unsigned short sphereVertCount = longitudeSegments * latitudeSegments * 6;

    float radius = 0.5f;
    float lotusSphereVerts[256 * 6 * 3]; // Allocate enough space for all vertices (3 components per vertex)

    int idx = 0;
    for (unsigned short lat = 0; lat < latitudeSegments; lat++) {
        float theta1 = (float)lat / latitudeSegments * LM_PI;
        float theta2 = (float)(lat + 1) / latitudeSegments * LM_PI;

        for (unsigned short lon = 0; lon < longitudeSegments; lon++) {
            float phi1 = (float)lon / longitudeSegments * 2.0f * LM_PI;
            float phi2 = (float)(lon + 1) / longitudeSegments * 2.0f * LM_PI;

            // Coordinates of the four vertices of the quad
            float x1 = radius * sinf(theta1) * cosf(phi1);
            float y1 = radius * cosf(theta1);
            float z1 = radius * sinf(theta1) * sinf(phi1);

            float x2 = radius * sinf(theta2) * cosf(phi1);
            float y2 = radius * cosf(theta2);
            float z2 = radius * sinf(theta2) * sinf(phi1);

            float x3 = radius * sinf(theta2) * cosf(phi2);
            float y3 = radius * cosf(theta2);
            float z3 = radius * sinf(theta2) * sinf(phi2);

            float x4 = radius * sinf(theta1) * cosf(phi2);
            float y4 = radius * cosf(theta1);
            float z4 = radius * sinf(theta1) * sinf(phi2);

            // First triangle
            lotusSphereVerts[idx++] = x1;
            lotusSphereVerts[idx++] = y1;
            lotusSphereVerts[idx++] = z1;

            lotusSphereVerts[idx++] = x2;
            lotusSphereVerts[idx++] = y2;
            lotusSphereVerts[idx++] = z2;

            lotusSphereVerts[idx++] = x3;
            lotusSphereVerts[idx++] = y3;
            lotusSphereVerts[idx++] = z3;

            // Second triangle
            lotusSphereVerts[idx++] = x1;
            lotusSphereVerts[idx++] = y1;
            lotusSphereVerts[idx++] = z1;

            lotusSphereVerts[idx++] = x3;
            lotusSphereVerts[idx++] = y3;
            lotusSphereVerts[idx++] = z3;

            lotusSphereVerts[idx++] = x4;
            lotusSphereVerts[idx++] = y4;
            lotusSphereVerts[idx++] = z4;
        }
    }
    lotusSetMesh(e, lotusSphereVerts, sphereVertCount, 0);
}

