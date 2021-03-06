/************************************************************
./webCam -c 0 -w 1920 -h 1080 -AppFps 60 -CamFps 60	// QuickTimeの動きは、ほぼ これ
./webCam -c 0 -w 1920 -h 1080 -AppFps 30 -CamFps 30	//
./webCam -c 0 -w 1920 -h 1080 -AppFps 20 -CamFps 20	// ★

./webCam -c 0 -w 1280 -h 720 -AppFps 60 -CamFps 60	// 解像度が許すなら、これもあり
./webCam -c 0 -w 1280 -h 720 -AppFps 30 -CamFps 30
************************************************************/
#include "ofMain.h"
#include "ofApp.h"

/************************************************************
************************************************************/
/******************************
******************************/
int main( int argc, char** argv ){
	ofSetupOpenGL(1024,768,OF_WINDOW);			// <-------- setup the GL context

	/********************
	********************/
	int CamWidth	= 1920;
	int CamHeight	= 1080;
	int Cam_id = -1;
	int CamFps = 30;
	int AppFps = 30;
	
	printf("---------------------------------\n");
	printf("> parameters\n");
	printf("\t-c      camera_id(-1)\n");
	printf("\t-w      cam_width(1920)\n");
	printf("\t-h      cam_height(1080)\n");
	printf("\t-AppFps AppFps(30)\n");
	printf("\t-CamFps CamFps(30)\n");
	printf("---------------------------------\n");
	
	for(int i = 1; i < argc; i++){
		if( strcmp(argv[i], "-c") == 0 ){
			if(i+1 < argc) Cam_id = atoi(argv[i+1]);
		}else if( strcmp(argv[i], "-w") == 0 ){
			if(i+1 < argc) CamWidth = atoi(argv[i+1]);
		}else if( strcmp(argv[i], "-h") == 0 ){
			if(i+1 < argc) CamHeight = atoi(argv[i+1]);
		}else if( strcmp(argv[i], "-AppFps") == 0 ){
			if(i+1 < argc) AppFps = atoi(argv[i+1]);
		}else if( strcmp(argv[i], "-CamFps") == 0 ){
			if(i+1 < argc) CamFps = atoi(argv[i+1]);
		}
	}
	
	/********************
	********************/
	printf("> parameters\n");
	printf("Cam_id    = %d\n", Cam_id);
	printf("CamWidth  = %d\n", CamWidth);
	printf("CamHeight = %d\n", CamHeight);
	printf("CamFps    = %d\n", CamFps);
	printf("AppFps    = %d\n", AppFps);
	fflush(stdout);
	
	/********************
	********************/
	ofRunApp(new ofApp(Cam_id, CamWidth, CamHeight, CamFps, AppFps));
}
