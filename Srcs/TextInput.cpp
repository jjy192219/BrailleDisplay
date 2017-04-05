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
        mTextBox->setDrawBounds(false);
        ci::TextBox submit = ci::TextBox();
        submit.text("[ Press Shift to submit ]");
        submit.font(ci::Font("Arial", 15));
        submit.color(ci::Color(1, 0,0));
        mSubmitButton = po::scene::TextBox::create(submit);
        mSubmitButton->setAlignment(po::scene::Alignment::CENTER_RIGHT);
        mSubmitButton->setDrawBounds(true);
        addChild(mSubmitButton);
    }
    
    void TextInput::update(){
        mSubmitButton->setPosition(mTextBox->getPosition().x +430.f, mTextBox->getHeight()+50);
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
            textSubmit();
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
    
    void TextInput::getMousePos(ci::app::MouseEvent event){
        mouseDown(event);
    }
    
    void TextInput::mouseDown(ci::app::MouseEvent event){
        std::cout<<"moust position"<<event.getPos()<<std::endl;
        if ((event.getPos().y >= mSubmitButton->getPosition().y )&& (event.getPos().y <= mSubmitButton->getHeight())) {
            if((event.getPos().x>=mSubmitButton->getPosition().x) && (event.getPos().x<=mSubmitButton->getWidth())){
                textSubmit();
            }
        }
    }
    
    void TextInput::textSubmit(){
        bFullText= false;
        getTextSubmitSignal().emit(mStringToArduino);
        mStringToArduino = "";
        mStringOnScreen = "";
        mCiTextBox.size(0,0);
        mCiTextBox.text(mBackgoundText);
    }
}
