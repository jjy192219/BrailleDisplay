#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "poNodeContainer.h"
#include "poScene.h"
#include "poTextBox.h"
#include "cinder/Serial.h"




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
    bool        bSending;
    SerialRef   mSerial;
    uint8_t     mSignal;
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
    bSending = false;
    
    
    for( const auto &dev : Serial::getDevices() )
        console() << "Device: " << dev.getName() << endl;
    
    try {
        Serial::Device dev = Serial::findDeviceByNameContains( "cu.usbmodem14" );
        mSerial = Serial::create( dev, 9600 );
    }
    catch( SerialExc &exc ) {
        ci::app::console()<<"can not initialize the device. "<<std::endl;
        exit( -1 );
    }
    
    mSerial->flush();
}

void TextboxTestApp::update()
{
    
    mScene->update();
}

void TextboxTestApp::keyDown(KeyEvent event){
    if (event.getCode() == KeyEvent::KEY_BACKSPACE ){
        if (mFileString.size()>0) {
            mString = mString.substr(0, mString.size()-1);
            mFileString = mFileString.substr(0, mFileString.size()-1);
        }
    }else {
        bStartTyping = true;
        const char character = event.getChar();
        mString += string( &character, 1 );
        mFileString += string( &character, 1 );
    }
    
    if (event.getCode() == KeyEvent::KEY_RETURN) {
        cout<<"sending: "<<mFileString<<std::endl;
        mSerial->writeString(mFileString);
        bSending= true;
        mFileString = "";
    }
    mCiTextBox.text(mString);
    mTextBox->setCiTextBox(mCiTextBox);
    
}

void TextboxTestApp::draw()
{
	gl::clear( Color( 1, 1, 1 ) );
    mScene->draw();
}

CINDER_APP( TextboxTestApp, RendererGl )
