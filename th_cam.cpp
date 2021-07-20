/************************************************************
************************************************************/
#include "th_cam.h"

/************************************************************
************************************************************/

/******************************
******************************/
THREAD_CAM::THREAD_CAM(int Cam_id, int CAM_WIDTH, int CAM_HEIGHT, int CamFps)
: CamParam_ToSet(Cam_id, CAM_WIDTH, CAM_HEIGHT, CamFps)
{
}

/******************************
******************************/
THREAD_CAM::~THREAD_CAM()
{
}

/******************************
******************************/
void THREAD_CAM::threadedFunction()
{
	while(isThreadRunning()) {
		/********************
		********************/
		int now = ofGetElapsedTimeMillis();
		
		/********************
		********************/
		lock();
			cam.update();
			if(cam.isFrameNew()){
				b_FrameNew = true;
				float Cam_CurrentFps = 1000.0/(float)(now - t_LastCamUpdate);
				
				Cam_ActualFps = alpha_CamFps * Cam_CurrentFps + (1 - alpha_CamFps) * Cam_ActualFps;
				
				t_LastCamUpdate = now;
			}
		unlock();
		
		/********************
		********************/
		sleep(THREAD_SLEEP_MS);
	}
}

/******************************
******************************/
void THREAD_CAM::setup()
{
	/********************
	********************/
	printf("> setup camera\n");
	fflush(stdout);
	
	/********************
	細かく情報出してもらう
	********************/
	ofSetLogLevel(OF_LOG_VERBOSE);
    cam.setVerbose(true);
	
	vector< ofVideoDevice > Devices = cam.listDevices();// 上 2行がないと、List表示されない.
	
	/********************
	********************/
	if(CamParam_ToSet.Cam_id == -1){
		ofExit();
		return;
	}else{
		if(Devices.size() <= CamParam_ToSet.Cam_id) { ERROR_MSG(); ofExit(); return; }
		
		cam.setDeviceID(CamParam_ToSet.Cam_id);
		printf("\n> cam set device id = %d\n", CamParam_ToSet.Cam_id);
		printf("> DeviceID     = %d\n", Devices[CamParam_ToSet.Cam_id].id);
		printf("> CamName      = %s\n", Devices[CamParam_ToSet.Cam_id].deviceName.c_str());
		printf("> HardwareName = %s\n", Devices[CamParam_ToSet.Cam_id].hardwareName.c_str());
		printf("> serialID     = %s\n", Devices[CamParam_ToSet.Cam_id].serialID.c_str());
		
		printf( "\n> Cam size asked  = (%d, %d)\n", int(CamParam_ToSet.width), int(CamParam_ToSet.height) );
		/*
			https://openframeworks.cc/documentation/video/ofVideoGrabber/#show_setDesiredFrameRate
				Set's the desired frame rate of the grabber. This should be called before initGrabber(), which will try to initialize at the desired frame rate. 
				Not all frame rates will be supported, but this at least gives you some abilitity to try grab at different rates.
		*/
		cam.setDesiredFrameRate(CamParam_ToSet.fps);
		// cam.initGrabber(CAM_WIDTH, CAM_HEIGHT);
		cam.initGrabber(CamParam_ToSet.width, CamParam_ToSet.height, false); // bool ofVideoGrabber::initGrabber(int w, int h, bool setUseTexture){
		printf( "> Cam size actual = (%d, %d)\n\n", int(cam.getWidth()), int(cam.getHeight()) );
		fflush(stdout);
	}
}

/******************************
******************************/
void THREAD_CAM::alloc_texture_to_match_camera(ofImage& img){
	lock();
		ofImageType imageType = OF_IMAGE_COLOR_ALPHA;
		switch(cam.getPixels().getPixelFormat()){
			case OF_PIXELS_RGB:
				imageType = OF_IMAGE_COLOR;
				break;
			case OF_PIXELS_RGBA:
			case OF_PIXELS_BGRA:
				imageType = OF_IMAGE_COLOR_ALPHA;
				break;
			case OF_PIXELS_MONO:
				imageType = OF_IMAGE_GRAYSCALE;
				break;
		}
		
		img.allocate(cam.getPixels().getWidth(), cam.getPixels().getHeight(), imageType);
	unlock();
}

/******************************
******************************/
void THREAD_CAM::alloc_texture_to_match_camera(ofTexture& tex){
	lock();
		tex.allocate(cam.getPixels());
	unlock();
}

/******************************
******************************/
void THREAD_CAM::update(ofImage& img, bool b_mirror)
{
	lock();
	if(b_FrameNew){
		/********************
		実は、
			img = cam.getPixels();
		は、未allocの場合、自動でallocしてくれるのだが、事前にaloocしない姿勢は、Programmerとして、好ましくない
		********************/
		if(img.isAllocated()){
			img = cam.getPixels();
			if(b_mirror) img.mirror(false, true);
		}
		
		b_FrameNew = false;
	}
	unlock();
}

/******************************
******************************/
void THREAD_CAM::update(ofTexture& tex)
{
	lock();
	if(b_FrameNew){
		/********************
		実は、
			tex.loadData(cam.getPixels());
		は、未allocの場合、自動でallocしてくれるのだが、事前にaloocしない姿勢は、Programmerとして、好ましくない
		********************/
		if(tex.isAllocated()){
			tex.loadData(cam.getPixels());
		}
		
		b_FrameNew = false;
	}
	unlock();
}

/******************************
******************************/
void THREAD_CAM::update_alpha_of_Fps(float _alpha)
{
	lock();
		alpha_CamFps = _alpha;
	unlock();
}

/******************************
******************************/
int THREAD_CAM::get_Cam_id(){
	int ret;
	lock();
		ret = CamParam_ToSet.Cam_id;
	unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_CAM::get_FrameRate(){
	float ret = 0;
	lock();
		ret = Cam_ActualFps;
	unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_CAM::getWidth(){
	float ret = 0;
	lock();
		ret = cam.getWidth();
	unlock();
	
	return ret;
}

/******************************
******************************/
float THREAD_CAM::getHeight(){
	float ret = 0;
	lock();
		ret = cam.getHeight();
	unlock();
	
	return ret;
}

