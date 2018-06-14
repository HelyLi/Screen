#include "AppDelegate.h"
#include "HelloWorldScene.h"

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC)
        || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("Screen", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("Screen");
#endif
        director->setOpenGLView(glview);
    }
    
    // turn on display FPS
    director->setDisplayStats(true);
    
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
    
#if 0
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
#else
    Size frameSize = glview->getFrameSize();
    Size lsSize = Size(480, 320);
    
    float scaleX = (float) frameSize.width / lsSize.width;
    float scaleY = (float) frameSize.height / lsSize.height;
    
    float scale = MAX(scaleX, scaleY);
    if (scaleX > scaleY)
        scale = scaleX / scaleY;//(frameSize.height / (float) lsSize.height);
    else
        scale = scaleY / scaleX;//(frameSize.width / (float) lsSize.width);
    
    log("x: %f; y: %f; scale: %f", scaleX, scaleY, scale);
    
    glview->setDesignResolutionSize(lsSize.width * scale, lsSize.height * scale, ResolutionPolicy::NO_BORDER);
    
//    glview->setDesignResolutionSize(lsSize.width , lsSize.height , ResolutionPolicy::NO_BORDER);
//    director->setContentScaleFactor(scale);
    
    Size winSize = director->getWinSize();
    Size visibleSize = director->getVisibleSize();
    Point visibleOrigin = director->getVisibleOrigin();
    
    log("FrameSize: width[%f], height[%f]", frameSize.width,
          frameSize.height);
    log("WinSize: width[%f], height[%f]", winSize.width, winSize.height);
    log("VisibleSize: width[%f], height[%f]", visibleSize.width,
          visibleSize.height);
    log("VisibleOrigin: x[%f], y[%f]", visibleOrigin.x, visibleOrigin.y);
    
    log("XScale: %f, YScale: %f", glview->getScaleX(),
          glview->getScaleY());

#endif
    register_all_packages();
    
    // create a scene. it's an autorelease object
    auto scene = HelloWorld::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
