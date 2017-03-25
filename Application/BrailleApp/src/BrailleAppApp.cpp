#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "TextInput.h"
#include "TextDisplay.h"
#include "poScene.h"
#include "poNodeContainer.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BrailleAppApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
private:
    void toggleFullScreen();
    void onSubmission(string strToSubmit);
    
    bool                        mIsFullScreen;
    Braile::TextInputRef        mTextInput;
    Braile::TextDisplayRef      mTextDisplay;
    po::scene::SceneRef         mScene;
    po::scene::NodeContainerRef mHolder;
    string                      mDisplayText;
};

void BrailleAppApp::setup()
{

    getWindow()->setPos(0, 0);
    getWindow()->setBorderless();
    getWindow()->spanAllDisplays();
    getWindow()->setAlwaysOnTop();

    mHolder = po::scene::NodeContainer::create();
    mScene = po::scene::Scene::create(mHolder);
    mTextInput = Braile::TextInput::create();
    mTextInput->setDrawBounds(false);
    mTextInput->setPosition(getWindowSize().x * 0.2f, getWindowSize().y * 0.35f);
    mHolder->addChild(mTextInput);
    mTextInput->getTextSubmitSignal().connect(std::bind(&BrailleAppApp::onSubmission,this, std::placeholders::_1));
    
    mTextDisplay = Braile::TextDisplay::create();
    mTextDisplay->setPosition(glm::ivec2(getWindowWidth()*0.65, getWindowHeight()*0.45 ));
    mHolder->addChild(mTextDisplay);
    
}

void BrailleAppApp::mouseDown( MouseEvent event )
{
}

void BrailleAppApp::toggleFullScreen(){
    mIsFullScreen = !mIsFullScreen;
//    if (mIsFullScreen) {
//        ci::app::setWindowSize(glm::ivec2(1680, 1050));
//    }else{
//        ci::app::setWindowSize(glm::ivec2(1680*0.25f, 1050*0.25f));
//    }
}

void BrailleAppApp::keyDown(KeyEvent event){
    mTextInput->getKeys(event);
//    switch (event.getCode()) {
//        case KeyEvent::KEY_SPACE:
//            toggleFullScreen();
//            break;
//            
//        default:
//            break;
//    }
}

void BrailleAppApp::onSubmission(string strToSubmit){
    mTextDisplay->display(strToSubmit);
}
void BrailleAppApp::update()
{
    mScene->update();
}

void BrailleAppApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    mScene->draw();
}

CINDER_APP( BrailleAppApp, RendererGl )
