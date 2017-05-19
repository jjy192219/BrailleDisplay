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
        mCiTextBox.font(ci::Font(ci::app::loadAsset("DroidSansMono.ttf"), 17));
        mCiTextBox.color(ci::Color(0,0,0));
        mCiTextBox.setPremultiplied(true);
        mTextBox = po::scene::TextBox::create(mCiTextBox);
        addChild(mTextBox);
        mTextBox->setAlignment(po::scene::Alignment::TOP_LEFT);
        
        ci::TextBox playing = ci::TextBox();
        playing.text("PLAYING");
        playing.font(ci::Font(ci::app::loadAsset("DroidSansMono.ttf"), 14));
        playing.color(ci::Color(0.65f, 0.65f, 0.65f));
        mPlaySign = po::scene::TextBox::create(playing);
        mPlaySign->setAlignment(po::scene::Alignment::TOP_LEFT);
        mPlaySign->setPosition(mTextBox->getPosition().x - 100, mTextBox->getPosition().y);
        mPlaySign->setDrawBounds(false);
        addChild(mPlaySign);
        mPlaySign->setAlpha(0.f);

    }
    
    void TextDisplay::update(){
    
    }
    
    void TextDisplay::display(std::string result){
        mResult = result;
        mPlaySign->setAlpha(1.f);
        mCiTextBox.size(240,160);
        mCiTextBox.text(mResult);
        mTextBox->setCiTextBox(mCiTextBox);
    }
}
