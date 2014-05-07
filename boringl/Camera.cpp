//
//  Camera.cpp
//  boringl
//
//  Created by Nils Hofmeister on 07/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#include "Camera.h"

Camera::Camera()
: m_camPos( 0.0f, 0.0f, 0.0f )
, m_camRot( 0.0f, glm::vec3( 0.0f, 0.0f, 1.0f ) )
{
}

Camera::~Camera()
{
}