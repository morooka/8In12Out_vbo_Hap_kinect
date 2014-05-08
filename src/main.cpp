#include "ofMain.h"
#include "ofApp.h"

#include "ofAppGLFWWindow.h"
#include "ofAppGlutWindow.h"
#include "ofAppNoWindow.h"


//========================================================================
int main( ){
   // ofAppGLFWWindow window;
    ofAppGlutWindow window;
   // ofAppBaseWindow window;
    //ofAppNoWindow window;

	//ofSetupOpenGL(&window,600,406, OF_WINDOW);			// <-------- setup the GL context
    ofSetupOpenGL(&window,1024,768, OF_WINDOW);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

}
