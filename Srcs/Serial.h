#pragma once
#include "cinder/Serial.h"


namespace Braile{
    class Serial;
    typedef std::shared_ptr<Serial> SerialRef;
    class Serial {
    public:
        static SerialRef create();
        ~Serial();
        void sendString(std::string text);
    private:
        void setup();
        
        ci::SerialRef mSerial;
    };
}
