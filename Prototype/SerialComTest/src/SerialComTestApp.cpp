#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "cinder/Serial.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class SerialComTestApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
    
    SerialRef   mSerial;
    uint8_t     mSignal;
};

void SerialComTestApp::setup()
{
    mSignal = '*';
    for( const auto &dev : Serial::getDevices() )
        console() << "Device: " << dev.getName() << endl;
    
    try {
        Serial::Device dev = Serial::findDeviceByNameContains( "cu.usbmodem1411" );
        mSerial = Serial::create( dev, 9600 );
    }
    catch( SerialExc &exc ) {
        ci::app::console()<<"can not initialize the device. "<<std::endl;
        exit( -1 );
    }
    
    mSerial->flush();

}

void SerialComTestApp::mouseDown( MouseEvent event )
{
    mSerial -> writeByte(mSignal);
}

void SerialComTestApp::update()
{
}

void SerialComTestApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( SerialComTestApp, RendererGl )
