#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "ofxTrueTypeFontUC.h"
#include "GetResoucesPath.h"
#include "ofxHapPlayer.h"
#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT1 1111
#define PORT2 2222
#define PORT3 3333
#define PORT4 4444
#define PORT5 5555
#define PORT6 6666


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut(float * output, int bufferSize, int nChannels);
    
    ofVbo vbo,vboImg1,vboImg2,vboImg3,vboImg4,vboImg5,vboImg6;
    
    vector<ofFloatColor> color,imgColor1,imgColor2,imgColor3,imgColor4,imgColor5,imgColor6; //パーティクルの色
    vector<ofPoint> cpos,imgCpos1,imgCpos2,imgCpos3,imgCpos4,imgCpos5,imgCpos6;  //パーティクルの現在位置
    vector<ofPoint> gpos,imgGpos1,imgGpos2,imgGpos3,imgGpos4,imgGpos5,imgGpos6;  //パーティクルの目標位置
   
    vector<ofVec2f> vel;   //パーティクルの速度
    
    bool isKeyPressed;           //キーを押下した/していない
    
    ofImage myImage; //画像データ
    
    int skip;
    ofxSyphonServer mainOutputSyphonServer;
    
    ofEasyCam cam;
    
    float count,sinCountY,sinCountZ,scene1Count;
    
    ofImage img1,img2,img3,img4,maskImg,monoImg,colorImg,kinectImg;
    ofTexture tex1,tex2,tex3,tex4,tex5,kinectBackImgTex,kinectTex;
    
    ofxHapPlayer player;
    
    vector <float> input1;
    vector <float> input2;
    vector <float> input3;
    vector <float> input4;
    vector <float> input5;
    vector <float> input6;
    vector <float> input7;
    vector <float> input8;
    
    int 	bufferCounter;
    int 	drawCounter;
    
    ofSoundStream soundStream;
    
    int		sampleRate;
    float 	volume;
    
    vector <float> Audio1;
    vector <float> Audio2;
    vector <float> Audio3;
    vector <float> Audio4;
    vector <float> Audio5;
    vector <float> Audio6;
    vector <float> Audio7;
    vector <float> Audio8;
    vector <float> Audio9;
    vector <float> Audio10;
    vector <float> Audio11;
    vector <float> Audio12;
    
    int angle,PositionX,PositionY;
    
    float hoseiX,hoseiY,tranceZ;
    
    ofFbo       maskFbo,maskFbo2_2,maskFbo3,maskFbo4,maskFbo5;
    ofFbo       fbo,fbo2,fbo3,fbo4,fbo5;
    
    ofShader    shader,shader2,shader3,shader4,shader5;
    
    vector<ofPoint> fboCpos,fboGpos,fboCpos2,fboGpos2,fboCpos3,fboGpos3,fboCpos4,fboGpos4,fboCpos5,fboGpos5;
    vector<ofVec2f> fboVel,fboVel2,fboVel3,fboVel4,fboVel5;
    
    deque<ofVec2f> current;
    
    vector<ofPoint>pos;
    vector<int>dist;
    vector<int>distZ;
    vector<ofPoint>posZ;
    vector<float>channel;
    vector<float>channelZVol;
    
    vector<float>smoothedVols;
    vector<float>scaledVols;
    
    vector<float>smoothedVol78;
    vector<float>scaledVol78;
    
    int radius;
    bool fboVol,ch1Vol,scene1,scene2,scene3,scene4,bKinect,scene5;
    
    ofxKinect kinect;
    
    ofxCvColorImage cvColorImg;
	
	ofxCvGrayscaleImage grayImage; // grayscale depth image
	ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
	ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
	
	ofxCvContourFinder contourFinder;
	
	bool bThreshWithOpenCV;
	bool bDrawPointCloud;
	
	int nearThreshold;
	int farThreshold;
    int rotateKinectY,rotateKinectZ;
    
    float s2X,s3X,s3Count,s1Vol1,s1Vol2,s1Vol0,s1Vol1_2,s1Vol0_2,s1Vol2_2,kinectDist;
    int cFX,cFY,cFX2,cFY2;
    
     ofxOscSender sender1,sender2,sender3,sender4,sender5,sender6;
    
    int enMove1X,enMove1Y,enMove2X,enMove2Y,enMove3X,enMove3Y;
    
};
