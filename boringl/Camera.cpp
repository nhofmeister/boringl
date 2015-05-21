//
//  Camera.cpp
//  boringl
//
//  Created by Nils Hofmeister on 07/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

Camera::Camera() {
	m_cameraMode = FREE;
	m_vecCamUp = glm::vec3(0, 1, 0);
	m_FOV = 45;
	m_camRot = glm::quat(1, 0, 0, 0);
	m_vecCamPosDelta = glm::vec3(0, 0, 0);
	m_camScale = .5f;
	m_maxPitch = 5;
	m_maxHeading = 5;
	m_moveCam = false;
    m_cameraMode = FREE;
    m_aspectRatio = .6f;
    m_nearClip = .1f;
    m_farClip = 100.0f;
}

Camera::~Camera() {
}

void Camera::Reset() {
	m_vecCamUp = glm::vec3(0, 1, 0);
}

void Camera::Update() {
	m_vecCamDir = glm::normalize(m_vecCamLookAt - m_vecCamPos);
	//need to set the matrix state. this is only important because lighting doesn't work if this isn't done
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(m_viewportX, m_viewportY, m_windowWidth, m_windowHeight);
    
	if (m_cameraMode == ORTHO) {
		//our projection matrix will be an orthogonal one in this case
		//if the values are not floating point, this command does not work properly
		//need to multiply by m_aspectRatio!!! (otherise will not scale properly)
		m_matProj = glm::ortho(-1.5f * float(m_aspectRatio), 1.5f * float(m_aspectRatio), -1.5f, 1.5f, -10.0f, 10.f);
	} else if (m_cameraMode == FREE) {
		m_matProj = glm::perspective(m_FOV, m_aspectRatio, m_nearClip, m_farClip);
		//detmine axis for pitch rotation
		glm::vec3 axis = glm::cross(m_vecCamDir, m_vecCamUp);
		//compute quaternion for pitch based on the camera pitch angle
		glm::quat pitch_quat = glm::angleAxis(m_pitch, axis);
		//determine heading quaternion from the camera up vector and the heading angle
		glm::quat heading_quat = glm::angleAxis(m_heading, m_vecCamUp);
		//add the two quaternions
		glm::quat temp = glm::cross(pitch_quat, heading_quat);
		temp = glm::normalize(temp);
		//update the direction from the quaternion
		m_vecCamDir = glm::rotate(temp, m_vecCamDir);
		//add the camera delta
		m_vecCamPos += m_vecCamPosDelta;
		//set the look at to be infront of the camera
		m_vecCamLookAt = m_vecCamPos + m_vecCamDir * 1.0f;
		//damping for smooth camera
		m_heading *= .5;
		m_pitch *= .5;
		m_vecCamPosDelta = m_vecCamPosDelta * .8f;
	}
	//compute the MVP
	m_matProj = glm::lookAt(m_vecCamPos, m_vecCamLookAt, m_vecCamUp);
	m_matModel = glm::mat4(1.0f);
	m_matModelViewProj = m_matProj * m_matProj * m_matModel;
	glLoadMatrixf(glm::value_ptr(m_matModelViewProj));
}

//Setting Functions
void Camera::SetMode(CameraType cam_mode) {
	m_cameraMode = cam_mode;
	m_vecCamUp = glm::vec3(0, 1, 0);
	m_camRot = glm::quat(1, 0, 0, 0);
}

void Camera::SetPosition(glm::vec3 pos) {
	m_vecCamPos = pos;
}

void Camera::SetLookAt(glm::vec3 pos) {
	m_vecCamLookAt = pos;
}
void Camera::SetFOV(double fov) {
	m_FOV = fov;
}
void Camera::SetViewport(int loc_x, int loc_y, int width, int height) {
	m_viewportX = loc_x;
	m_viewportY = loc_y;
	m_windowWidth = width;
	m_windowHeight = height;
	//need to use doubles division here, it will not work otherwise and it is possible to get a zero m_aspectRatio ratio with integer rounding
	m_aspectRatio = double(width) / double(height);
	;
}
void Camera::SetClipping(double m_nearClip_distance, double m_farClip_distance) {
	m_nearClip = m_nearClip_distance;
	m_farClip = m_farClip_distance;
}

void Camera::Move(CameraDirection dir) {
	if (m_cameraMode == FREE) {
		switch (dir) {
			case UP:
				m_vecCamPosDelta += m_vecCamUp * m_camScale;
				break;
			case DOWN:
				m_vecCamPosDelta -= m_vecCamUp * m_camScale;
				break;
			case LEFT:
				m_vecCamPosDelta -= glm::cross(m_vecCamDir, m_vecCamUp) * m_camScale;
				break;
			case RIGHT:
				m_vecCamPosDelta += glm::cross(m_vecCamDir, m_vecCamUp) * m_camScale;
				break;
			case FORWARD:
				m_vecCamPosDelta += m_vecCamDir * m_camScale;
				break;
			case BACK:
				m_vecCamPosDelta -= m_vecCamDir * m_camScale;
				break;
		}
	}
}
void Camera::ChangePitch(float degrees) {
	//Check bounds with the max pitch rate so that we aren't moving too fast
	if (degrees < -m_maxPitch) {
		degrees = -m_maxPitch;
	} else if (degrees > m_maxPitch) {
		degrees = m_maxPitch;
	}
	m_pitch += degrees;
    
	//Check bounds for the camera pitch
	if (m_pitch > 360.0f) {
		m_pitch -= 360.0f;
	} else if (m_pitch < -360.0f) {
		m_pitch += 360.0f;
	}
}
void Camera::ChangeHeading(float degrees) {
	//Check bounds with the max heading rate so that we aren't moving too fast
	if (degrees < -m_maxHeading) {
		degrees = -m_maxHeading;
	} else if (degrees > m_maxHeading) {
		degrees = m_maxHeading;
	}
	//This controls how the heading is changed if the camera is pointed straight up or down
	//The heading delta direction changes
	if ((m_pitch > 90 && m_pitch < 270) || (m_pitch < -90 && m_pitch > -270)) {
		m_heading -= degrees;
	} else {
		m_heading += degrees;
	}
	//Check bounds for the camera heading
	if (m_heading > 360.0f) {
		m_heading -= 360.0f;
	} else if (m_heading < -360.0f) {
		m_heading += 360.0f;
	}
}
void Camera::Move2D(int x, int y) {
	//compute the mouse delta from the previous mouse position
	glm::vec3 mouse_delta = m_vecMousePos - glm::vec3(x, y, 0);
	//if the camera is moving, meaning that the mouse was clicked and dragged, change the pitch and heading
	if (m_moveCam) {
		ChangeHeading(.08f * mouse_delta.x);
		ChangePitch(.08f * mouse_delta.y);
	}
	m_vecMousePos = glm::vec3(x, y, 0);
}

void Camera::SetPos(int button, int state, int x, int y) {
	if (button == 3 && state == GLUT_DOWN) {
		m_vecCamPosDelta += m_vecCamUp * .05f;
	} else if (button == 4 && state == GLUT_DOWN) {
		m_vecCamPosDelta -= m_vecCamUp * .05f;
	} else if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		m_moveCam = true;
	} else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
		m_moveCam = false;
	}
	m_vecMousePos = glm::vec3(x, y, 0);
}

CameraType Camera::GetMode() {
	return m_cameraMode;
}

void Camera::GetViewport(int &loc_x, int &loc_y, int &width, int &height) {
	loc_x = m_viewportX;
	loc_y = m_viewportY;
	width = m_windowWidth;
	height = m_windowHeight;
}

void Camera::GetMatricies(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M) {
	P = m_matProj;
	V = m_matProj;
	M = m_matModel;
}