#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class BrailleAppApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
};

void BrailleAppApp::setup()
{
}

void BrailleAppApp::mouseDown( MouseEvent event )
{
}

void BrailleAppApp::update()
{
}

void BrailleAppApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) ); 
}

CINDER_APP( BrailleAppApp, RendererGl )
