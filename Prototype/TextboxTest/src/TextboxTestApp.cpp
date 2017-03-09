#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "poNodeContainer.h"
#include "poScene.h"
#include "poTextBox.h"



using namespace ci;
using namespace ci::app;
using namespace std;
using namespace po::scene;

class TextboxTestApp : public App {
  public:
	void setup() override;
    void keyDown( KeyEvent event ) override;
	void update() override;
	void draw() override;
    SceneRef mScene;
    NodeContainerRef mHolder;
    ci::TextBox mCiTextBox;
    TextBoxRef  mTextBox;
    string      mString;
    string      mStartString;
    string      mFileString;
    bool        bStartTyping;
};

void TextboxTestApp::setup()
{
    mHolder = po::scene::NodeContainer::create();
    mScene = Scene::create(mHolder);
    
    mString = "";
    mFileString = "";
    mStartString = "type something";
    mCiTextBox = ci::TextBox();
    mCiTextBox.text(mStartString);
    mCiTextBox.font(ci::Font("Arial", 20));
    mCiTextBox.color(Color(0,0,0));
    mTextBox = po::scene::TextBox::create(mCiTextBox);
    mHolder->addChild(mTextBox);
    mHolder->setDrawBounds(true);
    mTextBox->setAlignment(po::scene::Alignment::CENTER_CENTER);
    mTextBox->setPosition(getWindowSize().x * 0.35f, getWindowSize().y * 0.35f);
    mCiTextBox.size(mTextBox->getPosition().x+100, 200);
    mTextBox->setDrawBounds(true);
}

void TextboxTestApp::update()
{
    if (bStartTyping) {
        mCiTextBox.text(mString);
        mTextBox->setCiTextBox(mCiTextBox);
    }
    mScene->update();
}

void TextboxTestApp::keyDown(KeyEvent event){
    if (event.getChar()) {
        bStartTyping = true;
        mString.append(1, event.getChar());
        mFileString.append(1,event.getChar());
    }
    
    if (event.getCode() == KeyEvent::KEY_UP && !mString.empty()){
        mString.erase(mString.end()-1);
    }
    
    if (event.getCode() == KeyEvent::KEY_RETURN) {
        cout<<"sending: "<<mFileString<<std::endl;
        mFileString = "";
        cout<<"mfileString now: "<<mFileString<<std::endl;
    }

    
    
    
}

void TextboxTestApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    mScene->draw();
}

CINDER_APP( TextboxTestApp, RendererGl )
