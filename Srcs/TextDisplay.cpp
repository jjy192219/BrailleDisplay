//
//  TextDisplay.cpp
//  BrailleApp
//
//  Created by Eric Jiang on 3/23/17.
//
//

#include "TextDisplay.h"

namespace Braile {
    TextDisplayRef TextDisplay::create(){
        TextDisplayRef ref = std::shared_ptr<TextDisplay>(new TextDisplay());
        ref -> setup();
        return ref;
    }
    
    TextDisplay::~TextDisplay(){};
    
    void TextDisplay::setup(){
        mResult = "";
        mCiTextBox = ci::TextBox();
        mCiTextBox.text(mResult);
        mCiTextBox.font(ci::Font("Arial", 20));
        mCiTextBox.color(ci::Color(0,0,0));
        mTextBox = po::scene::TextBox::create(mCiTextBox);
        addChild(mTextBox);
        mTextBox->setAlignment(po::scene::Alignment::CENTER_CENTER);
    }
    
    void TextDisplay::update(){
    
    }
    
    void TextDisplay::display(std::string result){
        mResult = result;
        mCiTextBox.size(500,200);
        mCiTextBox.text(mResult);
        mTextBox->setCiTextBox(mCiTextBox);
    }
}
