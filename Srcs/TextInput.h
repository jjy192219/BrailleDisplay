#pragma once
#include "poNodeContainer.h"
#include "poTextBox.h"

namespace Braile {
    class TextInput;
    typedef std::shared_ptr<TextInput> TextInputRef;
    typedef ci::signals::Signal<void(std::string)> TextSubmitSignal;
    class TextInput : public po::scene::NodeContainer{
    public:
        static  TextInputRef create();
        ~TextInput();
        TextSubmitSignal& getTextSubmitSignal(){return mSubmitText;};
        void getKeys(ci::app::KeyEvent event);
    private:
        void setup() override;
        void update() override;
        void keyDown(ci::app::KeyEvent event);
        void textSubmit ();
        
        ci::TextBox                 mCiTextBox;
        ci::TextLayout              mTextLayout;
        po::scene::TextBoxRef       mTextBox;
        po::scene::TextBoxRef       mSubmitButton;
        std::string                 mStringOnScreen;
        std::string                 mBackgoundText;
        std::string                 mStringToArduino;
        TextSubmitSignal            mSubmitText;
        bool                        bSubmit;
        bool                        bFullText;
    };
}
