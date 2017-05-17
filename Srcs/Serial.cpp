//
//  Serial.cpp
//  BrailleApp
//
//  Created by Eric Jiang on 5/17/17.
//
//

#include "Serial.h"

namespace Braile{
    SerialRef Serial::create(){
        SerialRef ref = std::shared_ptr<Serial>(new Serial());
        ref->setup();
        return ref;
    }
    
    void Serial::setup(){
        for( const auto &dev : ci::Serial::getDevices() )
            ci::app::console() << "Device: " << dev.getName() << std::endl;
        
        try {
            ci::Serial::Device dev = ci::Serial::findDeviceByNameContains( "cu.usbmodem14" );
            mSerial = ci::Serial::create( dev, 9600 );
        }
        catch( ci::SerialExc &exc ) {
            ci::app::console()<<"can not initialize the device. "<<std::endl;
            exit( -1 );
        }
        
        mSerial->flush();
    }
    
    void Serial::sendString(std::string text){
        mSerial->writeString(text);
    }
}
