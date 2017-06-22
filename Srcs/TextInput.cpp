//
//  TextInput.cpp
//  BrailleApp
//
//  Created by Eric Jiang on 3/23/17.
//
//

#include "TextInput.h"

namespace Braile {
    TextInputRef TextInput::create(){
        TextInputRef ref = std::shared_ptr<TextInput>(new TextInput());
        ref ->setup();
        return ref;
    }
    
    TextInput::~TextInput(){}
    
    void TextInput::setup(){
        mBackgoundText = "Start typing";
        mCiTextBox = ci::TextBox();
        mCiTextBox.text(mBackgoundText);
        mCiTextBox.font(ci::Font(ci::app::loadAsset("DroidSansMono.ttf"), 16));
        mCiTextBox.color(ci::Color(0.7f,0.7f,0.7f));
        mCiTextBox.setPremultiplied(true);
        mCiTextBox.size(240.f, 110.f); //set size for textbox
        mTextBox = po::scene::TextBox::create(mCiTextBox);
        addChild(mTextBox);
        mTextBox->setAlignment(po::scene::Alignment::TOP_LEFT);
        mTextBox->setDrawBounds(false);
        ci::TextBox submit = ci::TextBox();
        submit.text("PRESS SHIFT TO SUBMIT");
        submit.font(ci::Font(ci::app::loadAsset("DroidSansMono.ttf"), 15));
        submit.color(ci::Color(0.7f, 0.7f, 0.7f));
        mSubmitButton = po::scene::TextBox::create(submit);
        mSubmitButton->setAlignment(po::scene::Alignment::TOP_LEFT);
        mSubmitButton->setPosition(mTextBox->getPosition().x,  mTextBox->getPosition().y + 120.f);
        mSubmitButton->setDrawBounds(false);
        addChild(mSubmitButton);
        mSubmitButton->setAlpha(0.f);
    }
    
    void TextInput::update(){
    }
    
    void TextInput::getKeys(ci::app::KeyEvent event){
        keyDown(event);
    }
    
    void TextInput::keyDown(ci::app::KeyEvent event){
        mSubmitButton->setAlpha(1.f);
        
        
        if(mStringToArduino.length() >= 105) { //max char number a user can input
            bFullText = true;
            mCiTextBox.color(ci::Color(0.7f, 0.7f, 0.7f));
        }else{
            bFullText = false;
            mCiTextBox.color(ci::Color(0.f, 0.f, 0.f));
        }
        
        if (event.getCode() == ci::app::KeyEvent::KEY_BACKSPACE ){
            if (mStringToArduino.size()>0) {
                mStringToArduino = mStringToArduino.substr(0, mStringToArduino.size()-1);
            }
        }else {
            if (!bFullText) {
                const char character = event.getChar();
                mStringToArduino += std::string( &character, 1 );
            }
        }
        if (event.getCode() == ci::app::KeyEvent::KEY_LSHIFT || event.getCode() == ci::app::KeyEvent::KEY_RSHIFT) {
            textSubmit();
            mCiTextBox.color(ci::Color(0.7f, 0.7f, 0.7f));
            mSubmitButton->setAlpha(0.f);
            mCiTextBox.size(240.f, 110.f );
        }
       else{
            mCiTextBox.text(mStringToArduino);
        }
        mTextBox->setCiTextBox(mCiTextBox);
    }
    
    
    void TextInput::textSubmit(){
        bFullText= false;
        getTextSubmitSignal().emit(mStringToArduino);
        mStringToArduino = "";
        mCiTextBox.size(0,0);
        mCiTextBox.text(mBackgoundText);
    }
}
