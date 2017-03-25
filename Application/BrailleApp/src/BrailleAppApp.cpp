#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "TextInput.h"
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
    po::scene::SceneRef         mScene;
    po::scene::NodeContainerRef mHolder;
    string                      mDisplayText;
};

void BrailleAppApp::setup()
{

    ci::app::setWindowSize(glm::ivec2(1440, 900));
//    getWindow()->setPos(0, 0);
//    getWindow()->setBorderless();
//    getWindow()->spanAllDisplays();
//    getWindow()->setAlwaysOnTop();
    mHolder = po::scene::NodeContainer::create();
    mScene = po::scene::Scene::create(mHolder);
    mTextInput = Braile::TextInput::create();
    mTextInput->setDrawBounds(true);
    mTextInput->setPosition(getWindowSize().x * 0.35f, getWindowSize().y * 0.35f);
    mHolder->addChild(mTextInput);
    mTextInput->getTextSubmitSignal().connect(std::bind(&BrailleAppApp::onSubmission,this, std::placeholders::_1));
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
    mDisplayText = strToSubmit;

}
void BrailleAppApp::update()
{
    mScene->update();
}

void BrailleAppApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    ci::gl::drawString( mDisplayText, ci::vec2( 100.f, 100.f ), ci::Color( 0.5f, 0.5f, 0.5f ) );
    mScene->draw();
}

CINDER_APP( BrailleAppApp, RendererGl )
