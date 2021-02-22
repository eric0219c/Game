#pragma once
#include<SFML/Graphics.hpp>
#include "Collider.h"

class Platform
{
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position);
    ~Platform();
    
    void Update(float deltaTime, float increaseSpeed);
    void Draw(sf::RenderWindow& window);
    void pop()
    {
        sf::Vector2f a(0.0f,0.0f);
        body.setSize(a);
        sf::Vector2f b(10000.0f, 0.0f);
        body.setPosition(b);
    }
    Collider GetCollider(){ return Collider(body);}
    void setPosition(sf::Vector2f position);
    
private:
    sf::RectangleShape body;
};
