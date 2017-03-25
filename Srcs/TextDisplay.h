#pragma once
#include "poNodeContainer.h"
#include "poTextBox.h"


namespace Braile {
    class TextDisplay;
    typedef std::shared_ptr<TextDisplay> TextDisplayRef;
    class TextDisplay : public po::scene::NodeContainer{
    public:
        static TextDisplayRef create();
        ~TextDisplay();
        void display(std::string result);
    private:
        void setup() override;
        void update() override;
        
        ci::TextBox                 mCiTextBox;
        po::scene::TextBoxRef       mTextBox;
        std::string                 mResult;

    };
}
