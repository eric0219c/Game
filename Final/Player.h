#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include"Collider.h"
#include <iostream>
#include <time.h>
#include <cmath>
using namespace std;
class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imagaCount, float switchTime, float speed, float jumpHeight);
    ~Player();
    
    void Update(float deltaTime, const float&);
    void Draw(sf::RenderWindow& window);
    void OnCollision(sf::Vector2f direction);
    
    sf::Vector2f GetPosition(){return body.getPosition();}
    Collider GetCollider(){ return Collider(body);}
    void jump(){velocity.y = -sqrtf(2.0f * 500.0f * jumpHeight);}
    void downjump(){velocity.y = sqrtf(2.0f * 500.0f * jumpHeight);}
    void setCanJump(){canJump = true;}
    void resetPosition()
    {
        srand(time(NULL));
        int x = body.getPosition().x;
        x = (abs((rand() * 10294)) % 700 + 200 );
        body.setPosition(x * 1.0f ,75.0f);
        velocity.y = 1.0f;
    }
    void setPosition(int x, int y){ body.setPosition(x * 1.0f, y * 1.0f);}
    void resetSpeed();
private:
    sf::RectangleShape body;
    Animation animation;
    unsigned int row;
    float speed;
    bool faceRight;
    
    // 跳躍
    sf::Vector2f velocity;
    bool canJump;
    float jumpHeight;
};
