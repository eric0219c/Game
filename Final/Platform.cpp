#include "Platform.h"
#include "Animation.h"
#include "stdlib.h"


Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position)
{
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);
}

Platform::~Platform()
{
    
}

void Platform::setPosition(sf::Vector2f position)
{
    body.setPosition(position);
}
void Platform::Update(float deltaTime, float increaseSpeed)
{
    body.move(0.0f,-0.17f * increaseSpeed);
}

void Platform::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}
