/************************************************************
************************************************************/
#include "ofApp.h"

/************************************************************
************************************************************/

/******************************
******************************/
ofApp::ofApp(int _Cam_id, int _CamWidth, int _CamHeight, int _CamFps, int _AppFps)
: th_cam(_Cam_id, _CamWidth, _CamHeight, _CamFps)
, AppFps(_AppFps)
{
	font.load("font/RictyDiminished-Regular.ttf", 15, true, true, true);
	
	fp_Log = fopen("../../../data/Log.csv", "w");
}

/******************************
******************************/
ofApp::~ofApp(){
	fclose(fp_Log);
	delete Gui_Global;
}

/******************************
******************************/
void ofApp::exit()
{
	/********************
	********************/
	try{
		/********************
		********************/
		if(th_cam.isThreadRunning()){
			th_cam.waitForThread(true); // means call stopThread() inside the function, then wait for thread to Stop.
		}
		
	}catch(...){
		printf("Thread exiting Error\n");
	}
	
	/********************
	********************/
	printf("> Good bye\n");
}

/******************************
******************************/
void ofApp::setup(){
	/********************
	********************/
	ofSetWindowTitle("WebCam");
	
	ofSetWindowShape( WINDOW_WIDTH, WINDOW_HEIGHT );
	ofSetVerticalSync(false);	// trueとどっちがいいんだろう？
	ofSetFrameRate(AppFps);
	
	ofSetEscapeQuitsApp(false);
	
	/********************
	********************/
	setup_Gui();
	
	th_cam.setup();
	
	if(th_cam.get_Cam_id() != -1){
		th_cam.alloc_texture_to_match_camera(img_Cam);
		th_cam.alloc_texture_to_match_camera(tex_Cam);
		
		th_cam.startThread();
	}
}

/******************************
description
	memoryを確保は、app start後にしないと、
	segmentation faultになってしまった。
******************************/
void ofApp::setup_Gui()
{
	/********************
	********************/
	Gui_Global = new GUI_GLOBAL;
	Gui_Global->setup("param", "gui.xml", 10, 10);
}

/******************************
******************************/
void ofApp::update(){
	if(DrawBy == DRAW_BY__IMG){
		th_cam.update(img_Cam, b_mirror);
	}else{
		th_cam.update(tex_Cam);
	}
	
	th_cam.update_alpha_of_Fps(Gui_Global->alpha_CamFps);
}

/******************************
******************************/
void ofApp::draw(){
	/********************
	********************/
	ofBackground(0);
	ofSetColor(255);
	
	if(DrawBy == DRAW_BY__IMG){
		if(img_Cam.isAllocated()){
			img_Cam.draw(0, 0, ofGetWidth(), ofGetHeight());
		}
	}else{
		if(tex_Cam.isAllocated()){
			tex_Cam.draw(0, 0, ofGetWidth(), ofGetHeight());
		}
	}
	
	
	/********************
	********************/
	if(b_draw_info){
		// ofSetColor(0, 100, 255, 255);
		ofSetColor(255, 0, 0, 255);
		
		/********************
		Cam : xxx.x
		Size: (xxxxx.x, xxxxx.x)
		App : xxx.x
		draw: image
		********************/
		char buf[512];
		if(DrawBy == DRAW_BY__IMG)	sprintf(buf, "Cam : %5.1f[fps]\nSize: (%7.1f, %7.1f)\nApp : %5.1f[fps]\ndraw: image", th_cam.get_FrameRate(), th_cam.getWidth(), th_cam.getHeight(), ofGetFrameRate());
		else						sprintf(buf, "Cam : %5.1f[fps]\nSize: (%7.1f, %7.1f)\nApp : %5.1f[fps]\ndraw: texture", th_cam.get_FrameRate(), th_cam.getWidth(), th_cam.getHeight(), ofGetFrameRate());
		font.drawString(buf, 10, 30);
	}
	
	/********************
	********************/
	if(Gui_Global->b_Disp){
		Gui_Global->gui.draw();
	}
}

/******************************
******************************/
void ofApp::drawMessage_CamSearchFailed(){
	ofBackground(0);
	ofSetColor(255, 0, 0, 255);
	
	char buf[512];
	sprintf(buf, "USB Camera not Exsist");
	font.drawString(buf, ofGetWidth()/2 - font.stringWidth(buf)/2, ofGetHeight()/2);
}

/******************************
******************************/
void ofApp::keyPressed(int key){
	switch(key){
		case ' ':
			b_draw_info = !b_draw_info;
			break;
			
		case 'i':
			DrawBy = DRAW_BY__IMG;
			printf("> Draw by image\n");
			fflush(stdout);
			break;
			
		case 't':
			DrawBy = DRAW_BY__TEXTURE;
			printf("> Draw by texture\n");
			fflush(stdout);
			break;
			
		case 'm':
			b_mirror = !b_mirror;
			break;
			
		case 'd':
			Gui_Global->b_Disp = !Gui_Global->b_Disp;
			break;
			
	}
}

/******************************
******************************/
void ofApp::keyReleased(int key){

}

/******************************
******************************/
void ofApp::mouseMoved(int x, int y ){

}

/******************************
******************************/
void ofApp::mouseDragged(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mousePressed(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseReleased(int x, int y, int button){

}

/******************************
******************************/
void ofApp::mouseEntered(int x, int y){

}

/******************************
******************************/
void ofApp::mouseExited(int x, int y){

}

/******************************
******************************/
void ofApp::windowResized(int w, int h){

}

/******************************
******************************/
void ofApp::gotMessage(ofMessage msg){

}

/******************************
******************************/
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
