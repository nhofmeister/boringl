//
//  Camera.h
//  boringl
//
//  Created by Nils Hofmeister on 07/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#ifndef __boringl__Camera__
#define __boringl__Camera__

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/quaternion.hpp"

class Camera
{
public:
    Camera();
    ~Camera();
    
private:
    
    glm::vec3 m_camPos;
    glm::quat m_camRot;
};

#endif /* defined(__boringl__Camera__) */
