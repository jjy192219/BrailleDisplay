#pragma once
#include "poNodeContainer.h"

namespace Braile {
    class TextInput;
    typedef std::shared_ptr<TextInput> TextInputRef;
    class TextInput : public po::scene::NodeContainer{
    public:
        static  TextInputRef create();
        ~TextInput();
    private:
        void setup() override;
        void update() override;
        void keyDown(ci::app::KeyEvent event);
    };
}
