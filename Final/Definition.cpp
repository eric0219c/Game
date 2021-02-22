#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <string>
#include"stdlib.h"

class MyMusic{
 public:
    MyMusic(){};
    MyMusic(const sf::String& fileName)
    {
        buffer.loadFromFile(fileName);
        music1.setBuffer(buffer);
    }
    ~MyMusic(){}
    void play(){music1.play();}
    void stop(){music1.stop();}
    
 private:
    sf::SoundBuffer buffer;
    sf::Sound music1;
};
/*
 //text------------------
 sf::Text scoreText;
 scoreText.setFont(font);
 scoreText.setString("SCORE: ");
 scoreText.setCharacterSize(40);
 scoreText.setPosition(sf::Vector2f(800, 20));
 scoreText.setFillColor(sf::Color::Black);
 */

