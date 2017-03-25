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
        mStringOnScreen = "";
        mBackgoundText = "type somtnhing";
        mCiTextBox = ci::TextBox();
        mCiTextBox.text(mBackgoundText);
        mCiTextBox.font(ci::Font("Arial", 20));
        mCiTextBox.color(ci::Color(0.5f,0.5f,0.5f));
        mTextBox = po::scene::TextBox::create(mCiTextBox);
        addChild(mTextBox);
        mTextBox->setAlignment(po::scene::Alignment::CENTER_CENTER);
    }
    
    void TextInput::update(){
        
    }
    
    ci::TextBox &TextInput::getCiTextBox(){
        return mCiTextBox;
    }
    
    void TextInput::getKeys(ci::app::KeyEvent event){
        keyDown(event);
    }
    
    void TextInput::keyDown(ci::app::KeyEvent event){
        
        if (mTextBox->getWidth()>=500) {
            if (mTextBox->getHeight()>=200) {
                mCiTextBox.size(500, 200);
                bFullText = true;
            }else{
                bFullText= false;
                mCiTextBox.size(500, mCiTextBox.getSize().y);
            }
        }
        
        if (event.getCode() == ci::app::KeyEvent::KEY_BACKSPACE ){
            if (mStringToArduino.size()>0) {
                if (bFullText) {
                    mCiTextBox.size(0,0);
                    mCiTextBox.text(mStringOnScreen);
                }
                mStringOnScreen = mStringOnScreen.substr(0, mStringOnScreen.size()-1);
                mStringToArduino = mStringToArduino.substr(0, mStringToArduino.size()-1);
            }
            
        }else {
            if (!bFullText) {
                const char character = event.getChar();
                mStringOnScreen += std::string( &character, 1 );
                mStringToArduino += std::string( &character, 1 );
            }
            
        }
        if (event.getCode() == ci::app::KeyEvent::KEY_LSHIFT) {
            bFullText= false;
            getTextSubmitSignal().emit(mStringToArduino);
            mStringToArduino = "";
            mStringOnScreen = "";
            if (mTextBox && mTextBox->hasParent()) {
                removeChild(mTextBox);
            }
            mTextBox.reset();
            mCiTextBox.size(0,0);
            mCiTextBox.text(mBackgoundText);
            mCiTextBox.color(ci::Color(0.5f, 0.5f, 0.5f));
            mTextBox = po::scene::TextBox::create(mCiTextBox);
            addChild(mTextBox);
            mTextBox->setAlignment(po::scene::Alignment::CENTER_CENTER);

        }else{
            mCiTextBox.text(mStringOnScreen);
            if (!bFullText) {
                mCiTextBox.color(ci::Color(0.f, 0.f, 0.f));
            }else{
                mCiTextBox.color(ci::Color(0.5f, 0.5f, 0.5f));
            }
        }
        mTextBox->setCiTextBox(mCiTextBox);
        
    }
}
