/************************************************************
参考URL
	■ofVideoGrabber
		https://openframeworks.cc/documentation/video/ofVideoGrabber/
	
	■ofVideoDevice
		https://openframeworks.cc/documentation/video/ofVideoDevice/
			vector formatsは、vector<ofVideoFormat> formats;
		
	■ofVideoFormat
		https://openframeworks.cc/documentation/video/ofVideoFormat/
	
	■ofVideoBaseTypes.h
		https://gitlab.doc.gold.ac.uk/jtasn001/pm_jtasn001_lab1234/blob/8dfcfea04c40c477c5fe1ffa643dd88c3e2a940b/libs/openFrameworks/video/ofVideoBaseTypes.h
		
		contents
			/// \brief Unique identifier for the device if it has one.
			std::string serialID;
		
			/// \brief A list of video device formats provided by the device.
			/// \sa ofVideoFormat
			std::vector<ofVideoFormat> formats;
	
	■Question on ofVideoDevice + identify webcams of same model
		https://forum.openframeworks.cc/t/question-on-ofvideodevice-identify-webcams-of-same-model/15191
		
	■UVC camera control on OF0.10
		https://forum.openframeworks.cc/t/uvc-camera-control-on-of0-10/30971
		
	■openFrameworksでWebカメラを自動的に接続する
		https://miso-engine.hatenablog.com/entry/2017/06/02/132805
		
	■List available webcam resolutions?
		https://forum.openframeworks.cc/t/list-available-webcam-resolutions/28420
************************************************************/
#pragma once

/************************************************************
************************************************************/
#include "ofMain.h"

#include "sj_common.h"
#include "th_cam.h"

/************************************************************
************************************************************/
class ofApp : public ofBaseApp{
private:
	/****************************************
	****************************************/
	enum DRAW_BY{
		DRAW_BY__IMG,
		DRAW_BY__TEXTURE,
	};
	
	/****************************************
	****************************************/
	/********************
	********************/
	const int AppFps;
	THREAD_CAM th_cam;
	
	DRAW_BY DrawBy = DRAW_BY__TEXTURE;
	ofImage img_Cam;
	ofTexture tex_Cam;
	
	int now = 0;
	ofTrueTypeFont font;

	/********************
	********************/
	bool b_CamSearchFailed = false;
	
	bool b_draw_info = false;
	bool b_mirror = false;
	
	/****************************************
	****************************************/
	void drawMessage_CamSearchFailed();
	void setup_Gui();

public:
	/****************************************
	****************************************/
	ofApp(int _Cam_id, int _CamWidth, int _CamHeight, int _CamFps, int _AppFps);
	~ofApp();
	
	void setup();
	void update();
	void draw();
	void exit();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
};
