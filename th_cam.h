/************************************************************
■ofThread and ofVideoGrabber
	https://forum.openframeworks.cc/t/ofthread-and-ofvideograbber/10392/5
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"
#include "sj_common.h"

/************************************************************
************************************************************/

/**************************************************
**************************************************/
struct CAM_PARAM{
	int Cam_id;
	int width;
	int height;
	int fps;
	
	CAM_PARAM()
	{
	}
	
	CAM_PARAM(int _Cam_id, int _width, int _height, int _fps)
	: Cam_id(_Cam_id), width(_width), height(_height), fps(_fps)
	{
	}
	
	
};

/**************************************************
**************************************************/
class THREAD_CAM : public ofThread{
private:
	/****************************************
	****************************************/
	enum{
		THREAD_SLEEP_MS = 1,
	};
	
	/****************************************
	****************************************/
	ofVideoGrabber cam;
	bool b_FrameNew = false;
	CAM_PARAM CamParam_ToSet;
	float Cam_ActualFps = 0;
	
	float alpha_CamFps = 0.05;
	
	int t_LastCamUpdate;
	
public:
	/****************************************
	****************************************/
	THREAD_CAM(int Cam_id, int CAM_WIDTH, int CAM_HEIGHT, int CamFps);
	~THREAD_CAM();
	
	void threadedFunction();
	void setup();
	void update(ofImage& img, bool b_mirror = false);
	void update(ofTexture& tex);
	float get_FrameRate();
	float getWidth();
	float getHeight();
	int get_Cam_id();
	void alloc_texture_to_match_camera(ofImage& img);
	void alloc_texture_to_match_camera(ofTexture& tex);
	void update_alpha_of_Fps(float _alpha);
};



