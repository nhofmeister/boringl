//
//  Camera.h
//  boringl
//
//  Created by Nils Hofmeister on 07/05/14.
//  Copyright (c) 2014 Nils Hofmeister. All rights reserved.
//

#ifndef __boringl__Camera__
#define __boringl__Camera__

#define GLM_FORCE_RADIANS

#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/quaternion.hpp"

enum CameraType {
	ORTHO, FREE
};
enum CameraDirection {
	UP, DOWN, LEFT, RIGHT, FORWARD, BACK
};


class Camera
{
public:
    Camera();
    ~Camera();
    
    void Reset();
    void Update();
    void Move(CameraDirection dir);
    void ChangePitch(float degrees);
    void ChangeHeading(float degrees);
    void Move2D(int x, int y);
    void SetMode(CameraType cam_mode);
    void SetPosition(glm::vec3 pos);
    void SetLookAt(glm::vec3 pos);
    void SetFOV(double fov);
    void SetViewport(int loc_x, int loc_y, int width, int height);
    void SetClipping(double m_nearClip_distance, double m_farClip_distance);
    void SetDistance(double cam_dist);
    void SetPos(int button, int state, int x, int y);
    CameraType GetMode();
    void GetViewport(int &loc_x, int &loc_y, int &width, int &height);
    void GetMatricies(glm::mat4 &P, glm::mat4 &V, glm::mat4 &M);
    
private:
    CameraType m_cameraMode;
    int m_viewportX;
    int m_viewportY;
    int m_windowWidth;
    int m_windowHeight;
    double m_aspectRatio;
    double m_FOV;
    double m_nearClip;
    double m_farClip;
    float m_camScale;
    float m_heading;
    float m_pitch;
    float m_maxPitch;
    float m_maxHeading;
    bool m_moveCam;
    glm::vec3 m_vecCamPos;
    glm::vec3 m_vecCamPosDelta;
    glm::vec3 m_vecCamLookAt;
    glm::vec3 m_vecCamDir;
    glm::vec3 m_vecCamUp;
    glm::quat m_camRot;
    glm::vec3 m_vecMousePos;
    glm::mat4 m_matProj;
    glm::mat4 m_matView;
    glm::mat4 m_matModel;
    glm::mat4 m_matModelViewProj;
};

#endif /* defined(__boringl__Camera__) */
