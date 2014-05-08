#include "ofApp.h"
#include "GetResoucesPath.h"


//--------------------------------------------------------------
void ofApp::setup(){
   // ofSetVerticalSync(true);
   // ofSetFrameRate(60);
    
    ofSetDataPathRoot(getResourcesPath() + "/Contents/Resources/");
    
    myImage.loadImage("dm1117omote.jpg");
    
    isKeyPressed = false;
    
    const unsigned char* pixels = myImage.getPixels();
    skip = 1;
    for( int i = 0; i < myImage.width; i++){
        for(int j = 0; j < myImage.height; j++){
                const float r = pixels[j * myImage.width*3 + i*3];
                const float g = pixels[j * myImage.width*3 + i*3 + 1];
                const float b = pixels[j * myImage.width*3 + i*3 + 2];
                color.push_back(ofColor((1.0-r),(1.0-g),(1.0-b),255));
            float brightness = (3.0-r+g+b)/3.0;
                gpos.push_back(ofPoint(i, j,brightness));
                cpos.push_back(ofPoint(ofRandom(0, i), ofRandom(0, j),brightness));
            vel.push_back(ofVec3f(ofRandom(-1, 1), ofRandom(-1, 1)));
        }
    }
    vbo.setColorData (&color[0],cpos.size(),GL_DYNAMIC_DRAW_ARB);
    vbo.setVertexData(&cpos[0], cpos.size(), GL_DYNAMIC_DRAW_ARB);
    
    mainOutputSyphonServer.setName("Main Output");
    
    img1.loadImage("1.jpg");
    const unsigned char* pix1 = img1.getPixels();
    tex1.loadData(pix1,img1.width,img1.height, GL_RGBA);
    
    img2.loadImage("2.jpg");
    const unsigned char* pix2 = img2.getPixels();
    tex2.loadData(pix2,img2.width,img2.height, GL_RGB);
    
    img3.loadImage("3.jpg");
    const unsigned char* pix3 = img3.getPixels();
    tex3.loadData(pix3,img3.width,img3.height, GL_RGB);
    
    img4.loadImage("4.jpg");
    const unsigned char* pix4 = img4.getPixels();
    tex4.loadData(pix4,img4.width,img4.height, GL_RGB);
    
    kinectImg.loadImage("face.jpg");
    const unsigned char* pix5 = kinectImg.getPixels();
    kinectBackImgTex.loadData(pix5, kinectImg.width, kinectImg.height, GL_RGB);
    
    kinectTex.allocate(1024,768,GL_RGB);
    
    cam.setDistance(600);
    
    ofBackground(0);
    
    player.loadMovie("marumoto.mov", OF_QTKIT_DECODE_TEXTURE_ONLY);
    player.play();
   
    
    soundStream.listDevices();
	
	int bufferSize = 1024;
	
	input1.assign(bufferSize, 0.0);
	input2.assign(bufferSize, 0.0);
    input3.assign(bufferSize, 0.0);
	input4.assign(bufferSize, 0.0);
    input5.assign(bufferSize, 0.0);
	input6.assign(bufferSize, 0.0);
    input7.assign(bufferSize, 0.0);
    input8.assign(bufferSize, 0.0);
    
	bufferCounter	= 0;
	drawCounter		= 0;
    
    Audio1.assign(bufferSize, 0.0);
	Audio2.assign(bufferSize, 0.0);
    Audio3.assign(bufferSize, 0.0);
	Audio4.assign(bufferSize, 0.0);
    Audio5.assign(bufferSize, 0.0);
	Audio6.assign(bufferSize, 0.0);
    Audio7.assign(bufferSize, 0.0);
    Audio8.assign(bufferSize, 0.0);
    Audio9.assign(bufferSize, 0.0);
    Audio10.assign(bufferSize, 0.0);
    Audio11.assign(bufferSize, 0.0);
    Audio12.assign(bufferSize, 0.0);
    
	soundStream.setup(this,20, 8, 44100, bufferSize, 4);
    
    for (int i = 0; i < 6; i++) {
        fboCpos.push_back(ofPoint(i+300/2,i+461/2));
        fboGpos.push_back(ofPoint(i+300/2,i+461/2));
        fboVel.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)));

        pos.push_back(ofPoint(i,i));
        
        smoothedVols.push_back(i);
        scaledVols.push_back(i);
    }
    
    fboCpos2.push_back(ofPoint(100,130));
    fboGpos2.push_back(ofPoint(100,130));
    fboVel2.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)));
    
    fboCpos3.push_back(ofPoint(50,70));
    fboGpos3.push_back(ofPoint(50,70));
    fboVel3.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)));
    
    fboCpos4.push_back(ofPoint(50,70));
    fboGpos4.push_back(ofPoint(50,70));
    fboVel4.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)));
    
    fboCpos5.push_back(ofPoint(50,70));
    fboGpos5.push_back(ofPoint(50,70));
    fboVel5.push_back(ofVec2f(ofRandom(-1,1),ofRandom(-1,1)));
    
    for (int i = 0; i < 2; i++) {
        smoothedVol78.push_back(i);
        scaledVol78.push_back(i);
    }
    
    for (int i = 0; i < 36; i++) {
        dist.push_back(i);
        channel.push_back(0.1+i);
    }
    
    pos[0] = ofPoint(270,60);
    pos[1] = ofPoint(270,230);
    pos[2] = ofPoint(270,400);
    pos[3] = ofPoint(30,60);
    pos[4] = ofPoint(30,230);
    pos[5] = ofPoint(30,400);
    
    for (int i = 0;i < 3; i++) {
        distZ.push_back(i);
        channelZVol.push_back(0.1+i);
        }
    
    sinCountZ = 0;
    
    posZ.push_back(ofPoint(30,sinCountZ));
    
    
    ofSetCircleResolution(120);
    
    radius = 160;
    
    for(int i=0; i<fboVel.size(); i++){
        
            fboVel[i].x = ofRandom(-5, 5);
            fboVel[i].y = ofRandom(-5, 5);
    }
    
    monoImg.loadImage("moto2.jpg");           //////////////////////
    colorImg.loadImage("moto.jpg");
    maskImg.loadImage("brush.png");
    
    string shaderProgram = "#version 120\n \
    #extension GL_ARB_texture_rectangle : enable\n \
    \
    uniform sampler2DRect tex0;\
    uniform sampler2DRect maskTex;\
    \
    void main (void){\
    vec2 pos = gl_TexCoord[0].st;\
    \
    vec3 src = texture2DRect(tex0, pos).rgb;\
    float mask = texture2DRect(maskTex, pos).r;\
    \
    gl_FragColor = vec4( src , mask);\
    }";
    
    maskFbo.allocate(300,461);
    fbo.allocate(300,461);
    
    maskFbo2_2.allocate(176,140);
    fbo2.allocate(176,140);
    
    maskFbo3.allocate(66,114);
    fbo3.allocate(66,114);
    
    maskFbo4.allocate(261,200);
    fbo4.allocate(261,200);
    
    maskFbo5.allocate(145,168);
    fbo5.allocate(145,168);
    
    shader.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader.linkProgram();
    
    shader2.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader2.linkProgram();
    
    shader3.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader3.linkProgram();
    
    shader4.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader4.linkProgram();
    
    shader5.setupShaderFromSource(GL_FRAGMENT_SHADER, shaderProgram);
    shader5.linkProgram();
    
    maskFbo.begin();
    ofClear(255,255,255,255);
    maskFbo.end();
    
    maskFbo2_2.begin();
    ofClear(255,255,255,255);
    maskFbo2_2.end();
    
    maskFbo3.begin();
    ofClear(255,255,255,255);
    maskFbo3.end();
    
    maskFbo4.begin();
    ofClear(255,255,255,255);
    maskFbo4.end();
    
    maskFbo5.begin();
    ofClear(255,255,255,255);
    maskFbo5.end();
    
    fbo.begin();
    ofClear(0,0,0,255);
    fbo.end();
    
    fbo2.begin();
    ofClear(0,0,0,255);
    fbo2.end();
    
    fbo3.begin();
    ofClear(0,0,0,255);
    fbo3.end();
    
    fbo4.begin();
    ofClear(0,0,0,255);
    fbo4.end();
    
    fbo5.begin();
    ofClear(0,0,0,255);
    fbo5.end();
                                    /////////////////////
    fboVol = true;
    ch1Vol = false;
    
    tranceZ= 1000.0;
    
	kinect.setRegistration(true);
    
	kinect.init(false,false);
	
	kinect.open();
    
    grayImage.allocate(kinect.width, kinect.height);
	grayThreshNear.allocate(kinect.width, kinect.height);
	grayThreshFar.allocate(kinect.width, kinect.height);
	
	nearThreshold = 255;
	farThreshold = 190;
	bThreshWithOpenCV = true;
    
    angle = 0;
	kinect.setCameraTiltAngle(angle);
    
    scene1 = false;
    scene2 = false;
    scene3 = false;
    scene4 = false;
    scene5 = false;
    bKinect = false;
    scene1Count=0;
    
    s2X =0.0;
    s3X= 2000.0;
    
    sender1.setup(HOST, PORT1);
    sender2.setup(HOST, PORT2);
    sender3.setup(HOST, PORT3);
    sender4.setup(HOST, PORT4);
    
    hoseiX = 1024.0/(float)kinect.width;
    hoseiY = 768.0/(float)kinect.height;

    ofHideCursor();

}
//--------------------------------------------------------------
void ofApp::update(){
    
    for( int i=0; i<cpos.size(); i++){
        
        if(isKeyPressed){
            if(abs(gpos[i].x - cpos[i].x) > abs(vel[i].x)){
                cpos[i].x += vel[i].x;
            }else{
                cpos[i].x = gpos[i].x;
                vel[i].x = 0;
            }
            
            if(abs(gpos[i].y - cpos[i].y) > abs(vel[i].y)){
                cpos[i].y += vel[i].y;
            }else{
                cpos[i].y = gpos[i].y;
                vel[i].y = 0;
            }
            
        }else{
            
            if(cpos[i].x > 300+ofRandom(-20,20)){
                cpos[i].x = 300+ofRandom(-20,20);
                vel[i].x *= (-1);
            }else if(cpos[i].x < 0){
                cpos[i].x = 0;
                vel[i].x *= (-1);
            }else{
                cpos[i].x += vel[i].x;
            }
            
            if(cpos[i].y > 200+ofRandom(-20,20)){
                cpos[i].y = 200+ofRandom(-20,20);
                vel[i].y *= (-1);
            }else if(cpos[i].y < 0){
                cpos[i].y = 0;
                vel[i].y *= (-1);
            }else{
                cpos[i].y += vel[i].y;
            }
            
        }
    }      /////vbo position
    
    vbo.updateVertexData(&cpos[0],cpos.size());
    
    player.update();
    
    for( int i=0; i<fboCpos.size(); i++){
        if(fboCpos[i].x > (300)){
            fboCpos[i].x = (300);
            fboVel[i].x *= (-1);
        }else if(fboCpos[i].x < 0){
            fboCpos[i].x = 0;
            fboVel[i].x *= (-1);
        }else{
            fboCpos[i].x += fboVel[i].x;
        }
        
        if(fboCpos[i].y > 461){
            fboCpos[i].y = 461;
            fboVel[i].y *= (-1);
        }else if(fboCpos[i].y < 0){
            fboCpos[i].y = 0;
            fboVel[i].y *= (-1);
        }else{
            fboCpos[i].y += fboVel[i].y;
        }
    }     //////fbo1
    
    for( int i=0; i<fboCpos2.size(); i++){
        if(fboCpos2[i].x > (176)){
            fboCpos2[i].x = (176);
            fboVel2[i].x *= (-1);
        }else if(fboCpos2[i].x < 0){
            fboCpos2[i].x = 0;
            fboVel2[i].x *= (-1);
        }else{
            fboCpos2[i].x += fboVel2[i].x;
        }
        
        if(fboCpos2[i].y > 140){
            fboCpos2[i].y = 140;
            fboVel2[i].y *= (-1);
        }else if(fboCpos2[i].y < 0){
            fboCpos2[i].y = 0;
            fboVel2[i].y *= (-1);
        }else{
            fboCpos2[i].y += fboVel2[i].y;
        }
    }    //////fbo2
    
    for( int i=0; i<fboCpos3.size(); i++){
        if(fboCpos3[i].x > (66)){
            fboCpos3[i].x = (66);
            fboVel3[i].x *= (-1);
        }else if(fboCpos3[i].x < 0){
            fboCpos3[i].x = 0;
            fboVel3[i].x *= (-1);
        }else{
            fboCpos3[i].x += fboVel3[i].x;
        }
        
        if(fboCpos3[i].y > 114){
            fboCpos3[i].y = 114;
            fboVel3[i].y *= (-1);
        }else if(fboCpos3[i].y < 0){
            fboCpos3[i].y = 0;
            fboVel3[i].y *= (-1);
        }else{
            fboCpos3[i].y += fboVel3[i].y;
        }
    }    //////fbo3
    
    for( int i=0; i<fboCpos4.size(); i++){
        if(fboCpos4[i].x > (261)){
            fboCpos4[i].x = (261);
            fboVel4[i].x *= (-1);
        }else if(fboCpos4[i].x < 0){
            fboCpos4[i].x = 0;
            fboVel4[i].x *= (-1);
        }else{
            fboCpos4[i].x += fboVel4[i].x;
        }
        
        if(fboCpos4[i].y > 200){
            fboCpos4[i].y = 200;
            fboVel4[i].y *= (-1);
        }else if(fboCpos4[i].y < 0){
            fboCpos4[i].y = 0;
            fboVel4[i].y *= (-1);
        }else{
            fboCpos4[i].y += fboVel4[i].y;
        }
    }    //////fbo4
    
    for( int i=0; i<fboCpos5.size(); i++){
        if(fboCpos5[i].x > (145)){
            fboCpos5[i].x = (145);
            fboVel5[i].x *= (-1);
        }else if(fboCpos5[i].x < 0){
            fboCpos5[i].x = 0;
            fboVel5[i].x *= (-1);
        }else{
            fboCpos5[i].x += fboVel5[i].x;
        }
        
        if(fboCpos5[i].y > 168){
            fboCpos5[i].y = 168;
            fboVel5[i].y *= (-1);
        }else if(fboCpos5[i].y < 0){
            fboCpos5[i].y = 0;
            fboVel5[i].y *= (-1);
        }else{
            fboCpos5[i].y += fboVel5[i].y;
        }
    }    //////fbo5
    
    count = count + 0.1f;
    
    for (int i = 0 ; i < 6; i++) {
        scaledVols[i] = ofMap(smoothedVols[i], 0.0, 0.17, 0.0, 1.0, true);
        
        for (int j = 0; j < 6; j++) {
            dist[i*6 + j]     = ofDist(pos[i].x,pos[i].y,fboCpos[j].x,fboCpos[j].y);
        }
    }
    for (int i = 0 ; i < 2; i++) {
        scaledVol78[i] = ofMap(smoothedVol78[i],  0.0, 0.17, 0.0, 1.0, true);
    }
    
    
    {
    maskFbo.begin();
    int cFGain = 1;
   
    for(int i = 0; i <fboCpos.size(); i++) {
        maskImg.draw((fboCpos[i].x-30)-(1500*scaledVols[i]*cFGain),(fboCpos[i].y-30)-(1500*scaledVols[i]*cFGain),60+(3000*scaledVols[i]*cFGain),60+(3000*scaledVols[i]*cFGain));
        
    }
    maskFbo.end();
    
    fbo.begin();
    ofClear(0, 0, 0, 0);
    
    shader.begin();
    shader.setUniformTexture("maskTex", maskFbo.getTextureReference(), 1 );
   
    if(contourFinder.nBlobs == 0) monoImg.draw(0,0,300,461);
    if (contourFinder.nBlobs > 0) colorImg.draw(0,0,300,461);
    
    shader.end();
    fbo.end();
    }    //fbo1
    
    {
    maskFbo2_2.begin();
    for(int i = 0; i <fboCpos2.size(); i++) {
        maskImg.draw((fboCpos2[i].x-30)-(2000*scaledVols[3]),(fboCpos2[i].y-30)-(2000*scaledVols[3]),60+(4000*scaledVols[3]),60+(4000*scaledVols[3]));
    }
    maskFbo2_2.end();


    fbo2.begin();
    ofClear(0, 0, 0, 0);
    shader2.begin();
    shader2.setUniformTexture("maskTex", maskFbo2_2.getTextureReference(), 1 );
    tex2.draw(0,0,176,140);
    shader2.end();
    fbo2.end();
    }    //fbo2

    {
    maskFbo3.begin();
    for(int i = 0; i <fboCpos3.size(); i++) {
        maskImg.draw((fboCpos3[i].x-30)-(2000*scaledVols[4]),(fboCpos3[i].y-30)-(2000*scaledVols[4]),60+(4000*scaledVols[4]),60+(4000*scaledVols[4]));
    }
    maskFbo3.end();
    fbo3.begin();
    ofClear(0, 0, 0, 0);
    shader3.begin();
    shader3.setUniformTexture("maskTex", maskFbo3.getTextureReference(), 1 );
    tex4.draw(0,0,66,114);
    shader3.end();
    fbo3.end();
    }    //fbo3
    
    {
    maskFbo4.begin();
    for(int i = 0; i <fboCpos4.size(); i++) {
        maskImg.draw((fboCpos4[i].x-30)-(2000*scaledVols[5]),(fboCpos4[i].y-30)-(2000*scaledVols[5]),60+(4000*scaledVols[5]),60+(4000*scaledVols[5]));
    }
    maskFbo4.end();
    fbo4.begin();
    ofClear(0, 0, 0, 0);
    shader4.begin();
    shader4.setUniformTexture("maskTex", maskFbo4.getTextureReference(), 1 );
    tex3.draw(0,0,261,200);
    shader4.end();
    fbo4.end();
    }    //fbo4
    
    {
        maskFbo5.begin();
        for(int i = 0; i <fboCpos5.size(); i++) {
            maskImg.draw((fboCpos5[i].x-30)-(2000*scaledVols[0]),(fboCpos5[i].y-30)-(2000*scaledVols[0]),60+(4000*scaledVols[0]),60+(4000*scaledVols[0]));
        }
        maskFbo5.end();
        fbo5.begin();
        ofClear(0, 0, 0, 0);
        shader5.begin();
        shader5.setUniformTexture("maskTex", maskFbo5.getTextureReference(), 1 );
        tex1.draw(0,0);
        shader5.end();
        fbo5.end();
    }    //fbo5
    
    if(scene1) {
        scene1Count = scene1Count + 0.1f;
        sinCountZ = 230*std::sin(scene1Count/5)+230;
    }
    if (scene3) {
        s3Count = s3Count +0.1f;
    }
    
    posZ[0] = ofPoint(30,sinCountZ);
    
    distZ[0] = ofDist(pos[3].x, pos[3].y, posZ[0].x, posZ[0].y);
    distZ[1] = ofDist(pos[4].x, pos[4].y, posZ[0].x, posZ[0].y);
    distZ[2] = ofDist(pos[5].x, pos[5].y, posZ[0].x, posZ[0].y);
    
    kinect.update();
	
	if(kinect.isFrameNew()) {
		grayImage.setFromPixels(kinect.getDepthPixels(), kinect.width, kinect.height);
		if(bThreshWithOpenCV) {
			grayThreshNear = grayImage;
			grayThreshFar = grayImage;
			grayThreshNear.threshold(nearThreshold, true);
			grayThreshFar.threshold(farThreshold);
			cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
		} else {
			unsigned char * pix = grayImage.getPixels();
			int numPixels = grayImage.getWidth() * grayImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] < nearThreshold && pix[i] > farThreshold) {
					pix[i] = 255;
				} else {
					pix[i] = 0;
				}
			}
		}
		grayImage.flagImageChanged();
		contourFinder.findContours(grayImage, 10, (kinect.width*kinect.height)/2, 20, false);
	}
    
    if (contourFinder.nBlobs > 0) {
        cFX = contourFinder.blobs[0].centroid.x;
        cFY = contourFinder.blobs[0].centroid.y;
        cFX2 = contourFinder.blobs[1].centroid.x;
        cFY2 = contourFinder.blobs[1].centroid.y;
        
        kinectDist = ofDist(kinect.width/2, kinect.height/2,cFX,cFY);
        
        ofxOscMessage m;
        m.setAddress("/mouse/position");
        m.addIntArg(cFX);
        m.addIntArg(cFY);
        sender1.sendMessage(m);
        sender2.sendMessage(m);
        sender3.sendMessage(m);
        sender4.sendMessage(m);


    }
    
    if (bKinect) {
        if (contourFinder.nBlobs > 0) {
    
            rotateKinectY = rotateKinectY+((kinect.height/2-cFY)/120);
            rotateKinectZ = rotateKinectZ+((kinect.width/2-cFX)/120);
            
            
            if(scene4){
                count = count+kinectDist/600;
                scene1Count = scene1Count+kinectDist/600;
            }
        }
    }
    
    const unsigned char* pixels = myImage.getPixels();
    skip = 1;
    for( int i = 0; i < myImage.width; i++){
        for(int j = 0; j < myImage.height; j++){
            const float r = pixels[j * myImage.width*3 + i*3];
            const float g = pixels[j * myImage.width*3 + i*3 + 1];
            const float b = pixels[j * myImage.width*3 + i*3 + 2];
            color[i*myImage.height+j] = ofColor((1.0-r),(1.0-g),(1.0-b),255*scaledVols[0]*1000);
        }
    }
    vbo.updateColorData (&color[0],cpos.size());
    
    enMove1X = std::cos(count*2)*200;    //rotation =2000
    enMove1Y = std::sin(count*2)*200;
    
    enMove2X = std::cos(count*2+400)*200;
    enMove2Y = std::sin(count*2+400)*200;
    
    enMove3X = std::cos(count*2+800)*200;
    enMove3Y = std::sin(count*2+800)*200;

}
//--------------------------------------------------------------
void ofApp::draw(){
    glPushMatrix();
    
    ofSetColor(255,180);
    if (bKinect == false) {
        kinectBackImgTex.draw(cFX*hoseiX-200,cFY*hoseiY-150,400,300);
        kinectBackImgTex.draw(cFX2*hoseiX-200,cFY2*hoseiY-150,400,300);
    }else{
        player.draw(cFX*hoseiX-200,cFY*hoseiY-150,400,300);
        player.draw(cFX2*hoseiX-200,cFY2*hoseiY-150,400,300);
    }
    glBlendFunc(GL_DST_COLOR, GL_ZERO);
    grayImage.draw(0,0,1024,768);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    
   /* if (scene5) {
        ofSetColor(255,200);
        ofSetLineWidth(3);
        ofLine(cFX*hoseiX,cFY*hoseiY,cFX*hoseiX+enMove1X*2, cFY*hoseiY+enMove1Y*2);
        ofLine(cFX*hoseiX,cFY*hoseiY,cFX*hoseiX+enMove2X*2, cFY*hoseiY+enMove2Y*2);
        ofLine(cFX*hoseiX,cFY*hoseiY,cFX*hoseiX+enMove3X*2, cFY*hoseiY+enMove3Y*2);
        ofLine(cFX2*hoseiX,cFY2*hoseiY,cFX2*hoseiX+enMove1X*2, cFY2*hoseiY+enMove1Y*2);
        ofLine(cFX2*hoseiX,cFY2*hoseiY,cFX2*hoseiX+enMove2X*2, cFY2*hoseiY+enMove2Y*2);
        ofLine(cFX2*hoseiX,cFY2*hoseiY,cFX2*hoseiX+enMove3X*2, cFY2*hoseiY+enMove3Y*2);
        
    }
    */
    glPopMatrix();
    kinectTex.loadScreenData(0,0,1024,768);
    
    ofBackground(0);
    kinectTex.draw(0,0,ofGetWidth(),ofGetHeight());
    
    if (scene5)
        ofBackgroundGradient(ofColor(cFX+cFY,cFX+cFY,cFX+cFY),ofColor(0,0,0));
    
    
    cam.begin();
    
    ofScale(1,-1, 1);
    
    if(scene3){
        ofRotateY(s3Count*5);
        ofRotateZ(std::sin(s3Count/5)*10);
    }
    if(scene3 && scene2){
    ofRotateZ(rotateKinectY);
    ofRotateY(rotateKinectZ);
    }
    
    if (scene1) {
        if (tranceZ > 250) {
            tranceZ -= 2;
        }
        ofTranslate(-150,-180,tranceZ);    //z= -200
        ofRotateX(-90);
    }
    
    if (scene1 == false) {
        if (tranceZ < 1000) {
            tranceZ += 2;
        }
        ofTranslate(-150,-180,tranceZ);
        ofRotateX(-90);
    }
    
    if (scene2){
        if (s2X < 91.0) {
            s2X += 1.0;
        }
        ofRotateX(s2X);
        ofTranslate(0,50*s2X/90,-400*s2X/90);
    }
    if (scene2 == false) {
        if (s2X > 0.0) {
            s2X -= 1.0;
        }
        ofRotateX(s2X);
        ofTranslate(0,50*s2X/90,-400*s2X/90);
    }
    
    
    
    glPushMatrix();
    if (fboVol) sinCountY = 100*std::sin(count/5)+100;
    if (scene2) {
        ofTranslate(0,sinCountY,0);
        ofRotateX(90);
    }else{
            ofTranslate(-150,-180,1000);
        }
    ofSetColor(255, 255, 255);
    maskFbo.begin();
    ofClear(0,0,0,255);
    maskFbo.end();
    fbo.draw(0,0);
    glPopMatrix();
   
    
    glPushMatrix();
    glEnable(GL_DEPTH_TEST);
    glPointSize(1);
    ofTranslate(0,0,sinCountZ);
    ofSetColor(125, 125, 255);
    vbo.draw(GL_POINTS, 0, (int)cpos.size());
    glDisable(GL_DEPTH_TEST);
    glPopMatrix();
    
    if(scene2){
        glPushMatrix();
        ofSetColor(123,123,255,170);
        glEnable(GL_DEPTH_TEST);
        ofLine(cpos[0].x,cpos[0].y,sinCountZ,fboCpos[0].x,sinCountY,461-fboCpos[0].y);
        ofLine(cpos[299].x,cpos[299].y,sinCountZ,fboCpos[1].x,sinCountY,461-fboCpos[1].y);
        ofLine(cpos[59699].x,cpos[59699].y,sinCountZ,fboCpos[2].x,sinCountY,461-fboCpos[2].y);
        ofLine(cpos[59999].x,cpos[59999].y,sinCountZ,fboCpos[3].x,sinCountY,461-fboCpos[3].y);
        ofLine(cpos[30150].x,cpos[30150].y,sinCountZ,fboCpos[4].x,sinCountY,461-fboCpos[4].y);
        ofLine(cpos[30000].x,cpos[30000].y,sinCountZ,fboCpos[5].x,sinCountY,461-fboCpos[5].y);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    
    
    ofSetColor(255,200);
    
    if(scene3){
        if (s3X >0) {
            s3X-=10;
        }
        ofTranslate(0,0,s3X);
    }
    if (scene3 == false) {
        if (s3X <2000) {
            s3X+=10;
        }
        ofTranslate(0,0,s3X);
    }
    
    {
        glPushMatrix();
        ofTranslate(300,0,0);
        ofRotateY(-90);
    
        glPushMatrix();
        ofTranslate(30,20);
        ofSetColor(255, 255, 255);
        maskFbo5.begin();
        ofClear(0,0,0,255);
        maskFbo5.end();
        fbo5.draw(0,0);
        glPopMatrix();
        
        ofTranslate(200, 20);
        ofSetColor(255, 255, 255);
        maskFbo2_2.begin();
        ofClear(0,0,0,255);
        maskFbo2_2.end();
        fbo2.draw(0,0);
        glPopMatrix();
        
        
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        ofRotateY(-90);
        
        glPushMatrix();
        ofTranslate(35, 0);
        ofSetColor(255, 255, 255);
        maskFbo3.begin();
        ofClear(0,0,0,255);
        maskFbo3.end();
        fbo3.draw(0,0);
        glPopMatrix();
        
        glPushMatrix();
        ofTranslate(200, 0);
        ofSetColor(255, 255, 255);
        maskFbo4.begin();
        ofClear(0,0,0,255);
        maskFbo4.end();
        fbo4.draw(0,0);
        glPopMatrix();
       
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    
   /* if (scene3) {
        glPushMatrix();
        ofEnableNormalizedTexCoords();
        glEnable(GL_DEPTH_TEST);
        
        ofNoFill;
        ofSetColor(255, 255, 255,120);
        tex1.bind();
        ofDrawBox(300, 20+(168-fboCpos5[0].y), 30 + fboCpos5[0].x,30);
        tex1.unbind();
        tex2.bind();
        ofDrawSphere(300, 20+(140-fboCpos2[0].y), 200 + fboCpos2[0].x,30);
        tex2.unbind();
        tex3.bind();
        ofDrawBox(0, (114-fboCpos3[0].y), 35 + fboCpos3[0].x,30);
        tex3.unbind();
        tex4.bind();
        ofDrawBox(0, (200-fboCpos4[0].y), 200 + fboCpos4[0].x,30);
        tex4.unbind();
        ofDisableNormalizedTexCoords();
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    */
    
    if (scene4) {
        glPushMatrix();
        ofEnableNormalizedTexCoords();
        glEnable(GL_DEPTH_TEST);
        ofNoFill;
        ofSetColor(255, 255, 255,180);
        
        tex1.bind();
        ofTranslate(0,0,461-sinCountZ);
        ofDrawSphere(150+enMove1X,100+enMove1Y,30);
        ofDrawSphere(150+enMove2X,100+enMove2Y,30);
        ofDrawSphere(150+enMove3X,100+enMove3Y,30);
        tex1.unbind();
        ofDisableNormalizedTexCoords();
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();
    }
    
    if (scene5) {
        ofSetColor(200,25,54,80);
        glBegin(GL_TRIANGLE_STRIP);
        glVertex3f(cFX*hoseiX, cFY*hoseiY,0);
        glVertex3f(300, 20+(168-fboCpos5[0].y), (30 + fboCpos5[0].x));
        glVertex3f(150+enMove1X,100+enMove1Y,461-sinCountZ);
        ofSetColor(55,255,20,80);
        glVertex3f(300,(20+(140-fboCpos2[0].y)), (200 + fboCpos2[0].x));
        glVertex3f(cpos[30000].x,cpos[30000].y,sinCountZ);
        glVertex3f(150+enMove3X,100+enMove3Y,461-sinCountZ);
        ofSetColor(10,110,140,80);
        glVertex3f(0, (114-fboCpos3[0].y), (35 + fboCpos3[0].x));
        glVertex3f(150+enMove2X,100+enMove2Y,461-sinCountZ);
        glVertex3f(0, (200-fboCpos4[0].y), (200 + fboCpos4[0].x));
        glEnd();
        
        glPushMatrix();
        glEnable(GL_DEPTH_TEST);
        ofSetColor(255,150);
        kinectTex.draw(0,0,300,200);
        glDisable(GL_DEPTH_TEST);
        glPopMatrix();

        
    }
    
    cam.end();
    
    
  /*  ofSetColor(255);
    ofDrawBitmapString(ofToString(ofGetFrameRate()),10,10);
    ofDrawBitmapString("distZ[0]= "+ofToString(distZ[0]),10,20);
    ofDrawBitmapString("distZ[1]= "+ofToString(distZ[1]),10,30);
    ofDrawBitmapString("distZ[2]= "+ofToString(distZ[2]),10,40);
    ofDrawBitmapString("fboVol= "+ofToString((int)fboVol),10,50);
    ofDrawBitmapString("sinCountZ= "+ofToString(sinCountZ),10,60);
    
   // mainOutputSyphonServer.publishScreen();
   */
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    const static int ftime= 60;
    
    switch(key){
        case 'f':
            ofToggleFullscreen();
            break;
        case 'a':
            isKeyPressed = !isKeyPressed;
            for(int i=0; i<vel.size(); i++){
                vel[i].x = (isKeyPressed) ? (gpos[i].x-cpos[i].x)/ftime : ofRandom(-5, 5);
                vel[i].y = (isKeyPressed) ? (gpos[i].y-cpos[i].y)/ftime : ofRandom(-5, 5);
            }
            break;
        case '7':
            fboVol = !fboVol;
            break;
        case '6':
            ch1Vol = !ch1Vol;
            break;
        case '1':
            scene1 = !scene1;
            break;
        case '2':
            scene2 = !scene2;
            break;
        case '3':
            scene3 = !scene3;
            break;
        case'4':
            scene4 = !scene4;
            break;
        case'5':
            scene5 = !scene5;
            break;
        case 'k':
            bKinect = !bKinect;
            break;
            
    }
}
//--------------------------------------------------------------
void ofApp::audioIn(float * input, int bufferSize, int nChannels){
	
	float curVol = 0.0;
    float curVol2 = 0.0;
    float curVol3 = 0.0;
    float curVol4 = 0.0;
    float curVol5 = 0.0;
    float curVol6 = 0.0;
    float curVol7 = 0.0;
    float curVol8 = 0.0;
	
	// samples are "interleaved"
	int numCounted = 0;
    int numCounted2 = 0;
    int numCounted3 = 0;
    int numCounted4 = 0;
    int numCounted5 = 0;
    int numCounted6 = 0;
    int numCounted7 = 0;
    int numCounted8 = 0;
    
	//lets go through each sample and calculate the root mean square which is a rough way to calculate volume
	for (int i = 0; i < bufferSize; i++){
		input1[i]	= input[i*nChannels];
		input2[i]	= input[i*nChannels+1];
        input3[i]	= input[i*nChannels+2];
        input4[i]	= input[i*nChannels+3];
        input5[i]	= input[i*nChannels+4];
        input6[i]	= input[i*nChannels+5];
        input7[i]	= input[i*nChannels+6];
        input8[i]	= input[i*nChannels+7];
               
		curVol += input1[i] * input1[i];
		curVol2 += input2[i] * input2[i];
        curVol3 += input3[i] * input3[i];
        curVol4 += input4[i] * input4[i];
        curVol5 += input5[i] * input5[i];
        curVol6 += input6[i] * input6[i];
        curVol7 += input7[i] * input7[i];
        
		numCounted+=6;
        numCounted2+=6;
        numCounted3+=6;
        numCounted4+=6;
        numCounted5+=6;
        numCounted6+=6;
        numCounted7+=6;
        numCounted8+=6;
	}
	
	//this is how we get the mean of rms :)
	curVol /= (float)numCounted;
    curVol2 /= (float)numCounted2;
    curVol3 /= (float)numCounted3;
    curVol4 /= (float)numCounted4;
    curVol5 /= (float)numCounted5;
    curVol6 /= (float)numCounted6;
    curVol7 /= (float)numCounted7;
    curVol8 /= (float)numCounted8;
	
	// this is how we get the root of rms :)
	curVol  = sqrt( curVol );
    curVol2 = sqrt( curVol2 );
    curVol3 = sqrt( curVol3 );
    curVol4 = sqrt( curVol4 );
    curVol5 = sqrt( curVol5 );
    curVol6 = sqrt( curVol6 );
    curVol7 = sqrt( curVol7 );
    curVol8 = sqrt( curVol8 );
    
    smoothedVols[0] *= 0.93;
	smoothedVols[0] += 0.07 * curVol;
    smoothedVols[1] *= 0.93;
	smoothedVols[1] += 0.07 * curVol2;
    smoothedVols[2] *= 0.93;
	smoothedVols[2] += 0.07 * curVol3;
    smoothedVols[3] *= 0.93;
	smoothedVols[3] += 0.07 * curVol4;
    smoothedVols[4] *= 0.93;
	smoothedVols[4] += 0.07 * curVol5;
    smoothedVols[5] *= 0.93;
	smoothedVols[5] += 0.07 * curVol6;
    smoothedVol78[0] *= 0.93;
	smoothedVol78[0] += 0.07 * curVol7;
    smoothedVol78[1] *= 0.93;
	smoothedVol78[1] += 0.07 * curVol8;
    
	bufferCounter++;
	
}
//--------------------------------------------------------------
void ofApp::audioOut(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < 36; i++) {
        channel[i] = ofMap(dist[i], 0, radius, 1.0, 0.0);
        
        if (channel[i] < 0) channel[i] = 0;
    }
    
    for (int i = 0; i < 3; i++) {
        channelZVol[i] = ofMap(distZ[i], 0, 10, 1.0,0.0);
    }
    
    if (scene1) {
        s1Vol2 = channelZVol[2];
        s1Vol0 = channelZVol[0];
        
        if(scene2 ||scene3 || scene4){
            s1Vol2 = 1.0;
            s1Vol0 = 1.0;
        }
    }
    
    if (scene1) {
        s1Vol0_2 = 1.0;
        s1Vol1_2 = 1.0;
        s1Vol2_2 = 1.0;
        if (scene2 ||scene3 || scene4) {
            s1Vol0_2 = channelZVol[0];
            s1Vol1_2 = channelZVol[1];
            s1Vol2_2 = channelZVol[2];
        }
    }
    
    volume = 20.0f;
    
    float yVolHigh=0.0;
    float yVolLow=0.0;
    
    if (scene2) {
        yVolLow = ofMap(sinCountY, 50.0, 150.0, 0.0, 1.0);
        yVolHigh = 1.0-yVolLow;
    }
    
    float s4Vol0 = (1.0 - channelZVol[0])*(float)scene4;
    float s4Vol1 = (channelZVol[1])*(float)scene4;
    float s4Vol2 = (1.0 - channelZVol[2])*(float)scene4;
    
    float vol4_1 =(std::sin(count/100.0    )*0.5+0.5);
    float vol4_2 =(std::sin(count/100.0+300)*0.5+0.5);
    float vol4_3 =(std::sin(count/100.0+600)*0.5+0.5);
    float vol4_4 =(std::sin(count/100.0+900)*0.5+0.5);
    
    
    for (int i = 0; i < bufferSize; i++){
        Audio1[i] =output[i*nChannels ] =
        (input2[i] * volume * channel[1]+input3[i]  * volume * channel[2]
        +(input4[i] * volume * channel[3]+input5[i]  * volume * channel[4]+input6[i] * volume * channel[5])*(int)scene3)*yVolHigh*fboVol +(input1[i] * volume/20 * s1Vol2 * s1Vol0_2) + (input7[i] * volume/20 * s4Vol2* vol4_1) + (input8[i] * volume/30 *(int)scene5);
        
        //--
        
        Audio2[i] =output[i*nChannels + 1] =
        (input2[i] * volume * channel[7]+input3[i]  * volume * channel[8]
        +(input4[i] * volume * channel[9]+input5[i]  * volume * channel[10]+input6[i] * volume * channel[11])*(int)scene3)*yVolHigh*fboVol + (input1[i] * volume/20 * s1Vol2 * s1Vol1_2)+ (input7[i] * volume/20 * s4Vol1* vol4_1) ;
        
        //--
        
        Audio3[i] =output[i*nChannels + 2] =
        (input2[i] * volume * channel[13]+input3[i] * volume * channel[14]
        +(input4[i] * volume * channel[15]+input5[i]  * volume * channel[16]+input6[i] * volume * channel[17])*(int)scene3)*yVolHigh*fboVol + (input1[i] * volume/20 * s1Vol2 * s1Vol2_2) + (input7[i] * volume/20 * s4Vol0* vol4_1) ;
        
        //--
        
        Audio4[i] =output[i*nChannels + 3] =
        (input2[i] * volume * channel[19]+input3[i] * volume * channel[20]
        +(input4[i] * volume * channel[21]+input5[i] * volume * channel[22]+input6[i] * volume * channel[23])*(int)scene3)*yVolHigh*fboVol +(input1[i] * volume/20 * s1Vol2 * s1Vol0_2)+ (input7[i] * volume/20 * s4Vol2* vol4_2) ;
        
        //--
        
        Audio5[i] =output[i*nChannels + 4] =
        (input2[i] * volume * channel[25]+input3[i] * volume * channel[26]
        +(input4[i] * volume * channel[27]+input5[i]  * volume * channel[28]+input6[i] * volume * channel[29])*(int)scene3)*yVolHigh*fboVol + (input1[i] * volume/20 * s1Vol2 * s1Vol1_2) + (input7[i] * volume/20 * s4Vol1* vol4_2) ;
        
        //--
        
        Audio6[i] =output[i*nChannels + 5] =
        (input2[i] * volume * channel[31]+input3[i] * volume * channel[32]
        +(input4[i] * volume * channel[33]+input5[i] * volume * channel[34]+input6[i] * volume * channel[35])*(int)scene3)*yVolHigh*fboVol + (input1[i] * volume/20 * s1Vol2 * s1Vol2_2) + (input7[i] * volume/20 * s4Vol0* vol4_2);
        
        //--
   
        Audio7[i] =output[i*nChannels +14] =
        (input2[i] * volume * channel[1]+input3[i]  * volume * channel[2]
        +(input4[i] * volume * channel[3]+input5[i]  * volume * channel[4]+input6[i] * volume * channel[5])*(int)scene3)*yVolLow*fboVol +(input1[i] * volume/20 * s1Vol0 * s1Vol0_2)+ (input7[i] * volume/20 * s4Vol2* vol4_3) ;
        
        //--
        
        Audio8[i] =output[i*nChannels + 15] =
        (input2[i] * volume * channel[7]+input3[i]  * volume * channel[8]
        +(input4[i] * volume * channel[9]+input5[i]  * volume * channel[10]+input6[i] * volume * channel[11])*(int)scene3)*yVolLow*fboVol + (input1[i] * volume/20 * s1Vol0 * s1Vol1_2)+ (input7[i] * volume/20 * s4Vol1* vol4_3) ;
        
        //--
        
        Audio9[i] =output[i*nChannels + 16] =
        (input2[i] * volume * channel[13]+input3[i] * volume * channel[14]
        +(input4[i] * volume * channel[15]+input5[i]  * volume * channel[16]+input6[i] * volume * channel[17])*(int)scene3)*yVolLow*fboVol + (input1[i] * volume/20 * s1Vol0 * s1Vol2_2)+ (input7[i] * volume/20 * s4Vol0* vol4_3) ;
        
        //--
        
        Audio10[i] =output[i*nChannels + 17] =
        (input2[i] * volume * channel[19]+input3[i] * volume * channel[20]
        +(input4[i] * volume * channel[21]+input5[i] * volume * channel[22]+input6[i] * volume * channel[23])*(int)scene3)*yVolLow*fboVol +(input1[i] * volume/20 * s1Vol0 * s1Vol0_2)+ (input7[i] * volume/20 * s4Vol2* vol4_4) ;
        
        //--
        
        Audio11[i] =output[i*nChannels + 18] =
        (input2[i] * volume * channel[25]+input3[i] * volume * channel[26]
        +(input4[i] * volume * channel[27]+input5[i]  * volume * channel[28]+input6[i] * volume * channel[29])*(int)scene3)*yVolLow*fboVol + (input1[i] * volume/20 * s1Vol0 * s1Vol1_2)+ (input7[i] * volume/20 * s4Vol1* vol4_4) ;
        
        //--
        
        Audio12[i] =output[i*nChannels + 19] =
        (input2[i] * volume * channel[31]+input3[i] * volume * channel[32]
        +(input4[i] * volume * channel[33]+input5[i] * volume * channel[34]+input6[i] * volume * channel[35])*(int)scene3)*yVolLow*fboVol + (input1[i] * volume/20 * s1Vol0 * s1Vol2_2)+ (input7[i] * volume/20 * s4Vol0* vol4_4) + (input8[i] * volume/30 *(int)scene5);
    }

}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){
}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
}
//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
}
//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
}
//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
}