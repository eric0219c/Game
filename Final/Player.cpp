#include "Player.h"
#include "Animation.h"
#include <cmath>


Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight) :
    animation(texture,imageCount,switchTime)
{
    this-> speed = speed;
    this-> jumpHeight = jumpHeight;
    row = 0;
    faceRight = true;
    canJump = true;
    body.setSize(sf::Vector2f(80.0f, 120.0f));
    body.setOrigin(50.0f, 75.0f);
    body.setPosition(50.0f,100.0f);
    body.setTexture(texture);
}

Player::~Player()
{
   
}

void Player::resetSpeed()
{
    jumpHeight = 80.0f;
    velocity.y = sqrtf(2.0f * 500.0f * jumpHeight);
}

void Player::Update(float deltaTime, const float& increaseSpeed)
{
    velocity.x = 0.0f;
    
    
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
       velocity.x -= speed + ( 5 * increaseSpeed ) ;
   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
       velocity.x += speed + ( 5 * increaseSpeed ) ;

    // Jumping

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&& canJump)
    {
        velocity.y = -sqrtf(2.0f * 500.0f * jumpHeight);
        // square root(2.0f * gravity * jumpHeight)
        canJump = false;
    }

    // Gravity
    
        velocity.y += 500.0f * deltaTime + increaseSpeed * 0.7;
    //cout << "Gravity: " << velocity.y << endl;
    /*
    if(jumpHeight < 500.0f and velocity.y > 0){
        if(jumpHeight <= 120.0f)
            jumpHeight += velocity.y * 0.00016f;
        else if(jumpHeight > 120.0f and jumpHeight <= 160.0f)
            jumpHeight += velocity.y * 0.00032f;
        else if(jumpHeight > 160.0f and jumpHeight <= 200.0f)
            jumpHeight += velocity.y * 0.00048f;
        else if(jumpHeight > 200.0f and jumpHeight <= 240.0f)
            jumpHeight += velocity.y * 0.00060f;
        else if(jumpHeight > 240.0f and jumpHeight <= 300.0f)
            jumpHeight += velocity.y * 0.00066f;
        else
            jumpHeight += velocity.y * 0.0007f;
    }*/
    //cout << "JUMP Height: " << jumpHeight << endl;
    jumpHeight = increaseSpeed * 20;
   if(velocity.x == 0.0f)
   {
       row = 0;
   }
   
   else
   {
       row = 1;
       
       if(velocity.x > 0.0f)
       {
           faceRight = true;
       }
       else
       {
           faceRight = false;
       }
   }

       
   animation.Update(row, deltaTime, faceRight);
   body.setTextureRect(animation.uvRect);
   body.move(velocity * deltaTime);
}

void Player::Draw(sf::RenderWindow& window)
{
    window.draw(body);
}

void Player::OnCollision(sf::Vector2f direction)
{
    // collision on the left
    if(direction.x < 0.0f)
       velocity.x = 0.0f;
    
    else if(direction.x > 0.0f)
        velocity.x = 0.0f;
    
    // collision on the buttom
    if(direction.y < 0.0f)
    {
        canJump = true;
        velocity.y = 0.0f;
    }
    
    else if(direction.y > 0.0f)
    {
        velocity.y = 0.0f;
    }

}

