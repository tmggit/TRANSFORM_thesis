#pragma once
#define KINECT

#include "ofMain.h"
#include "baseVideoPlayer.h"
#include "ShapeIOManager.h"
#include "KinectTracker.h"
#include "ofImage.h"
#include "ofxMovieExporter.h"
#include "KinectVideoPlayer.h"
#include "MachineAnimationVideoPlayer.h"
#include "videoRecorder.h"
#include "TableSimulator.h"
#include <memory>
#include "ImageWarper.h"
#include "KinectShapeObject.h"
#include "MachineAnimationShapeObject.h"
#include "CalmShapeObject.h"
#include "FadeLoopShapeObject.h"
#include "ImageShapeObject.h"
#include "GUIShapeObject.h"
#include "ofxUI.h"
#include "TCPClient.h"

// @todo see https://github.com/danomatika/ofxAppUtils for alternate quad wrapper, openGL based?

class ReliefApplication : public ofBaseApp  {
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    // buffer rendering
    void renderPinDisplayBuffer(); // render pin display to buffer
    void renderHeightMapBuffer(); // render height map to buffer
    
    void drawGeneralMessage();
    
    void keyPressed(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    
    
    
    bool useLiveKinect;
    bool useRecording;
    bool useTable = true;
    bool drawTableSimulation = true;
    
    // table config variables
    float                       gain_P;
    float                       gain_I;
    int                         max_I;
    int                         deadZone;
    int                         maxSpeed;
    
    ImageWarper                 * mImageWarper; // warps images from one coordinate system to another
    ShapeObject                 * mCurrentShapeObject;
    
    //vector                      <ShapeObject*> mCurrentShapeObjects;
    vector                      <ShapeObject*> allShapeObjects;
    vector                      <string> allsShapeObjectsNames;
    
    bool                        controlManual = true;
    bool                        controlTimeline = false;
    bool                        isVideoLoaded = false;
    
    
    // this is the kinect image thresholded and rendered
    KinectShapeObject           * mKinectShapeObject;
    MachineAnimationShapeObject * mMachineAnimationShapeObject;
    CalmShapeObject             * mCalmShapeObject; // calm shape object, does nothing but used to reset
    ImageShapeObject            * mImageShapeObject;;
    GUIShapeObject              * mGUIShapeObject;;
    TCPClient                   * mTCPShapeObject;
    
    ofxCvColorImage             cvColorImage;
    ofxCvColorImage             cvWarpedImage;
    
    ShapeIOManager              * mIOManager; // manages communication with the pin display
    
    ofFbo                       pinDisplayImage; //FBO where we render graphics for pins
    ofFbo                       pinHeightMapImageForGraphic; //FBO where we render height map for Graphic display
    ofFbo                       pinHeightMapImageForTable; //FBO where we render height map for Table
    ofFbo                       pinHeightMapImage2;
    
    KinectTracker               mKinectTracker;
    ofRectangle                 guiIn;
       
    KinectVideoPlayer           kinectVideoPlayer;
    VideoRecorder               recorder;
    
    unsigned char* compPixels;
    unsigned char* targetPixels;
    
    // setup available screens
    // this is more robust then setting by integer
    // to reorder the screens change order in array.
    TableSimulator              * tableSimulation;
    
    ofxUICanvas                 * easyGui;
    ofxUICanvas                 * imagesDropdown;
    ofxUICanvas                 * videosDropdown;
    ofxUICanvas                 * kinectRecordingsDropdown;
    ofxUICanvas                 * pinMatrixManipulator;
    
    void guiEvent(ofxUIEventArgs &e); // kinect uses this too
    void tableGuiEvent(ofxUIEventArgs &e); // seperate table callback
    void setupVideosDropdown();
    void setupKinectRecordingsDropdown();
    void setupPinMatrixManipulator();
    void setupImagesDropdown();
    
    void pauseApp();
    void resumeApp();
    
    // setup available screens
    // this is more robust then setting by integer
    // to reorder the screens change order in array.
    string                      screens[3] = {"shapeobject", "kinect", "tcp"};
    int                         maxScreens = 3;
    int                         screenIndex = 0; // starting screen
    string                      currentScreen = screens[0];    bool                        bAnimationLooping = false;

private:
    Apex::ofxMovieExporter      movieExporter;
    void incrementAndSetCurrentScreen();
    void drawActualPinHeightImageFromTable(int x, int y, int w, int h);
    void setupEasyGui();
    void drawBitmapString(string _message, int _x, int _y);
    void connectTable();
    
    void initalizeShapeObjects();
    void registerShapeObjectNamesForGui();
    bool isPaused = false;

    void blendCurrentShapeObjectsByHighestValue();
    
    ofxUIToggleMatrix *pinMatrix0, *pinMatrix1, *pinMatrix2;
    ofxUIWidget *activePinMatrixManipulator;
    void updateActivePinMatrixManipulator(ofxUIWidget *manipulator);
};
