#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include"stdlib.h"
#include"time.h"
#include"Player.h"
#include"Collider.h"
#include"Platform.h"
#include "Definition.cpp"

#define SCREEN_WIDTH 1024.0f
#define SCREEN_HEIGHT 1024.0f

using namespace std;

void restart(float& deltaTime, bool& relife, float& countRelifeTime, float& countTime, float& speedTime, int& testForMusic
             , int& score, int& blood, float& increaseSpeed);
void setText(sf::Text& scoreText, sf::Text& scoreNum, sf::Text& bloodText, sf::Text& bloodNum,
sf::Text& gameOver,sf::Text& totalScore, sf::Text& dead, sf::Text& countDead, sf::Text& guide,
             sf::Font& font, sf::Font& font1);
int main()
{
 
    sf::RenderWindow window( sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT),"Running Game", sf::Style::Default);
    sf::Texture player1Texture;
    sf::Texture upperBoundTexture;
    sf::Texture platformsTexture;
    sf::Texture platformsBadTexture, maInNineTexture, tsaiTexture, wangTexture, kerTexture, hanTexture;
    sf::Texture startPlatformTexture;
    player1Texture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/fox.png");
    upperBoundTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/SpearsUp.png");
    platformsTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/floatingBar.png");
    startPlatformTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/startBar.png");
    platformsBadTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/badBar.png");
    tsaiTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/IMG_5692.png");
    wangTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/IMG_5699.png");
    kerTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/IMG_5695.png");
    hanTexture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/IMG_5691.png");
//--//MUSIC----------------------------------------------------------------------------------
    
    MyMusic wangMusic("/Users/guolian/Desktop/Final/SFML template/SFML template/wang.wav");
    MyMusic tsai1("/Users/guolian/Desktop/Final/SFML template/SFML template/tsai1.wav");
    MyMusic tsai2("/Users/guolian/Desktop/Final/SFML template/SFML template/tsai2.wav");
    MyMusic tsai3("/Users/guolian/Desktop/Final/SFML template/SFML template/tsai3.wav");
    MyMusic tsai4("/Users/guolian/Desktop/Final/SFML template/SFML template/tsai4.wav");
    MyMusic han1("/Users/guolian/Desktop/Final/SFML template/SFML template/han1.wav");
    MyMusic han2("/Users/guolian/Desktop/Final/SFML template/SFML template/han5.wav");
    MyMusic han3("/Users/guolian/Desktop/Final/SFML template/SFML template/han3.wav");
    MyMusic han4("/Users/guolian/Desktop/Final/SFML template/SFML template/han4.wav");
    MyMusic ker1("/Users/guolian/Desktop/Final/SFML template/SFML template/ker1.wav");
    MyMusic ker2("/Users/guolian/Desktop/Final/SFML template/SFML template/ker2.wav");
    MyMusic ker3("/Users/guolian/Desktop/Final/SFML template/SFML template/ker3.wav");
    MyMusic ker4("/Users/guolian/Desktop/Final/SFML template/SFML template/ker4.wav");
    MyMusic ker5("/Users/guolian/Desktop/Final/SFML template/SFML template/ker5.wav");
    MyMusic wang1("/Users/guolian/Desktop/Final/SFML template/SFML template/wang1.wav");
    MyMusic wang2("/Users/guolian/Desktop/Final/SFML template/SFML template/wang2.wav");
    MyMusic wang3("/Users/guolian/Desktop/Final/SFML template/SFML template/wang3.wav");
    MyMusic wang4("/Users/guolian/Desktop/Final/SFML template/SFML template/wang4.wav");
    MyMusic music("/Users/guolian/Desktop/Final/SFML template/SFML template/iceOut.wav");
    MyMusic beat("/Users/guolian/Desktop/Final/SFML template/SFML template/iceOutBeat.wav");
    MyMusic dead1("/Users/guolian/Desktop/Final/SFML template/SFML template/dead1.wav");
    MyMusic dead2("/Users/guolian/Desktop/Final/SFML template/SFML template/dead2.wav");
    MyMusic dead3("/Users/guolian/Desktop/Final/SFML template/SFML template/dead3.wav");
    MyMusic dead4("/Users/guolian/Desktop/Final/SFML template/SFML template/dead4.wav");
    MyMusic dead5("/Users/guolian/Desktop/Final/SFML template/SFML template/dead5.wav");
    MyMusic dead6("/Users/guolian/Desktop/Final/SFML template/SFML template/dead6.wav");
    
//--//分數---------------------------------------------------------------
    int score = 0;
    int blood = 3;
    int countDeadNum = 3;
    bool deadOk = false;
    bool dying = false;
    //宣告字體
    sf::Font font;
    sf::Font font1;
    font1.loadFromFile("/Users/guolian/Desktop/Final/SFML template1/Resources/arial.ttf");
    //讀字體檔案
    if( !font.loadFromFile("/Users/guolian/Desktop/Final/SFML template1/Resources/FlappyFont.ttf"))
    {
        std::cout << "Error loading file" << std::endl;
        system("pause");
    }
    //text------------------
    sf::Text scoreText, scoreNum, bloodText, bloodNum, gameOver, totalScore, guide, dead, countDead;
    setText(scoreText, scoreNum, bloodText, bloodNum, gameOver, totalScore, dead, countDead, guide, font, font1);
    //player---------------------------
    Player player(&player1Texture, sf::Vector2u(3,9), 0.3f, 200.0f, 80.0f);
    
    // vector for platforms
    std::vector<Platform> platforms, platformsBad, upperBounds, frame, maInNume, tsai, wang, ker, han;

    // 遊戲開始的平台
    Platform platformStart(&startPlatformTexture,sf::Vector2f(150.0f,25.0f), sf::Vector2f(100.0f,350.0f));
    
    // 框架
    frame.push_back(Platform(nullptr,sf::Vector2f(2.0f,SCREEN_HEIGHT), sf::Vector2f(-1.0f,SCREEN_HEIGHT/2.0f)));
    frame.push_back(Platform(nullptr,sf::Vector2f(2.0f,SCREEN_HEIGHT), sf::Vector2f(SCREEN_WIDTH + 1.0f,SCREEN_HEIGHT/2.0f)));
    frame.push_back(Platform(nullptr,sf::Vector2f(SCREEN_WIDTH,2.0f), sf::Vector2f(SCREEN_WIDTH/2.0f, -1.0f)));
    //frame.push_back(Platform(nullptr,sf::Vector2f(SCREEN_WIDTH,2.0f), sf::Vector2f(SCREEN_WIDTH/2.0f, SCREEN_HEIGHT+1.0f)));

    // 刀片
    for(int i = 0 ; i < 16 ; i ++)
        upperBounds.push_back(Platform(&upperBoundTexture,sf::Vector2f(64.0f,18.0f), sf::Vector2f(32.0f+ i * 64.0f, 9.0f )));
    
    // 上升的平台
    int random;
    srand(time(NULL));
    for(int i = 0 ; i < 1000 ; i ++)
    {
        random = (rand() % 14);
        platforms.push_back(Platform(&platformsTexture,sf::Vector2f(120.0f,20.0f), sf::Vector2f(75.0f+random * 50.0f, 600.0f + 170.0f * i)));
        platformsBad.push_back(Platform(&platformsBadTexture,sf::Vector2f(120.0f,20.0f), sf::Vector2f(75.0f+random * 50.0f,900.0f + 870.0f * i)));
        random = rand() * 7;
        if(i < 20){
            int tsaiR = (random * 10000) % 1024;
            tsai.push_back(Platform(&tsaiTexture,sf::Vector2f(90.0f,135.0f), sf::Vector2f(tsaiR * 1.0f,900.0f + 550.0f * i)));
            int wangR = (random * 10359) % 1024;
            wang.push_back(Platform(&wangTexture,sf::Vector2f(180.0f,240.0f), sf::Vector2f(wangR * 1.0f,1300.0f + 500.0f * i)));
            int kerR = (random * 20681) % 1024;
            ker.push_back(Platform(&kerTexture,sf::Vector2f(70.0f,120.0f), sf::Vector2f(kerR * 1.0f,1500.0f + 600.0f * i)));
            int hanR = (random * 11159) % 1024;
            han.push_back(Platform(&hanTexture,sf::Vector2f(90.0f,135.0f), sf::Vector2f(hanR * 1.0f,1000.0f + 480.0f * i)));
        }
        else{
            int tsaiR = (random * 10000) % 1024;
            tsai.push_back(Platform(&tsaiTexture,sf::Vector2f(90.0f,135.0f), sf::Vector2f(tsaiR * 1.0f,900.0f + 850.0f * i)));
            int wangR = (random * 10359) % 1024;
            wang.push_back(Platform(&wangTexture,sf::Vector2f(180.0f,240.0f), sf::Vector2f(wangR * 1.0f,1300.0f + 900.0f * i)));
            int kerR = (random * 20681) % 1024;
            ker.push_back(Platform(&kerTexture,sf::Vector2f(70.0f,120.0f), sf::Vector2f(kerR * 1.0f,1500.0f + 800.0f * i)));
            int hanR = (random * 11159) % 1024;
            han.push_back(Platform(&hanTexture,sf::Vector2f(90.0f,135.0f), sf::Vector2f(hanR * 1.0f,1000.0f + 750.0f * i)));
        }
    }

    float testForBeat = 0;
    float deltaTime = 0.0f;
    sf::Clock clock;
    bool relife = false;
    float countRelifeTime = 0;
    float countTime = 0;
    float countAngel = 0;
    float speedTime = 1;
    float scoreTime = 0;
    int testForMusic = 0;
    float increaseSpeed = 5.0f;
    float badTime = 0;
 while( window.isOpen( ))
     {
         if(testForBeat == 0 and blood > 0){
             beat.play();
             testForBeat = 100;
         }
         player.Update(deltaTime, increaseSpeed);
         deltaTime = clock.restart().asSeconds();
         scoreTime++;
         if(scoreTime >= 300 and blood > 0){
             if(increaseSpeed <= 10)
                 score += 10;
             else if(increaseSpeed > 10 and increaseSpeed <= 15)
                 score += 20;
             else if(increaseSpeed > 15 and increaseSpeed <= 20)
                 score += 30;
             else if(increaseSpeed > 20 and increaseSpeed <= 25)
                 score += 40;
             else
                 score += 50;
             scoreTime = 0;
         }
         countTime ++;
         if(countTime >= 300 / speedTime and blood > 0)
         {
             countTime = 0;
             speedTime += 0.15;
             if(increaseSpeed <= 27.5f)
                 increaseSpeed += 0.55f;
         }
         
         // handle input/event
         sf::Event evnt;
         
         while(window.pollEvent( evnt ))
         {
             
             switch ( evnt.type )
             {
                 case sf::Event::Closed:
                     window.close( );
                     break;
             }
         }
         
         //music.play();
         
         sf::Vector2f direction;
         
        // check if hit a object
         Collider playerC = player.GetCollider();
         
         if(platformStart.GetCollider().CheckCollision(playerC, direction, 1.0f))
            player.OnCollision(direction);
         platformStart.Update(deltaTime, increaseSpeed);
         
         for(Platform& platform : platforms){
             if(platform.GetCollider().CheckCollision(playerC, direction, 1.0f))
                 player.OnCollision(direction);
             platform.Update(deltaTime, increaseSpeed);
         }
         for(Platform& platformsBad : platformsBad){
             if(platformsBad.GetCollider().CheckCollision(playerC, direction, 1.0f)){
                 player.OnCollision(direction);
                 badTime ++;
                 if(badTime == 50){
                     badTime = 0;
                     score -= 10;
                 }
             }
             platformsBad.Update(deltaTime, increaseSpeed);
         }
         
         
         for(Platform& tsai : tsai){
             if(tsai.GetCollider().CheckCollision(playerC, direction, 1.0f)){
                 int random = rand()% 4;
                 if(random == 0) tsai1.play();
                 else if(random == 1) tsai2.play();
                 else if(random == 2) tsai3.play();
                 else if(random == 3) tsai4.play();
                 player.OnCollision(direction);
                 tsai.pop();
                 score+=10;
                 player.jump();
                 continue;
             }
             tsai.Update(deltaTime, 4.8 + increaseSpeed * 1.2);
         }
         
         for(Platform& wang : wang){
             if(wang.GetCollider().CheckCollision(playerC, direction, 1.0f)){
                 srand(time(NULL));
                 int random = rand() % 4;
                 if(random == 0) wangMusic.play();
                 else if(random == 1) wang1.play();
                 else if(random == 2) wang2.play();
                 else if(random == 3) wang3.play();
                 
                 player.OnCollision(direction);
                 wang.pop();
                 score += 10;
                 player.jump();
                 continue;
             }
             int randSpeed = rand() % 25;
             wang.Update(deltaTime, 6.9 + increaseSpeed * 1.2);
         }
         
         for(Platform& ker : ker){
             if(ker.GetCollider().CheckCollision(playerC, direction, 1.0f)){
                 int random = rand() % 5;
                 if(random == 0) ker1.play();
                 else if(random == 1) ker2.play();
                 else if(random == 2) ker3.play();
                 else if(random == 3) ker4.play();
                 else if(random == 4) ker5.play();
                 player.OnCollision(direction);
                 ker.pop();
                 score += 10;
                 player.jump();
                 continue;
             }
             int randSpeed = rand() % 35;
             ker.Update(deltaTime, 5.7 + increaseSpeed * 1.2);
         }
         
         for(Platform& han : han){
             if(han.GetCollider().CheckCollision(playerC, direction, 1.0f)){
                 int random = rand() % 4;
                 if(random == 0) han1.play();
                 else if(random == 1) han2.play();
                 else if(random == 2) han3.play();
                 else if(random == 3) han4.play();
                 
                 player.OnCollision(direction);
                 han.pop();
                 score += 10;
                 player.jump();
                 continue;
             }
             int randSpeed = rand() % 30;
             han.Update(deltaTime, 4.5 + increaseSpeed * 1.2);
         }
         
         for(Platform& upperBound : upperBounds){
             if(upperBound.GetCollider().CheckCollision(playerC, direction, 1.0f)){
                 player.downjump();
                 if(relife == false){
                     blood -= 1;
                     player.setPosition(2050, 100);
                     platformStart.setPosition(sf::Vector2f(2100.0f,350.0f));
                     dying = true;
                     relife = true;
                     if(blood != 0){
                         srand(time(NULL));
                         int random = rand() % 4;
                         if(random == 0)      dead1.play();
                         else if(random == 1) dead2.play();
                         else if(random == 2) dead6.play();
                         else if(random == 3) dead4.play();
                     }
                     
                 }
             }
         }
         if(player.GetPosition().y > 900.f and dying == false){
             srand(time(NULL));
             blood -= 1;
             player.setPosition(2050, 100);
             platformStart.setPosition(sf::Vector2f(2100.0f,350.0f));
             dying = true;
             relife = true;
             if(blood != 0){
                 srand(time(NULL));
                 int random = rand() % 4;
                 if(random == 0)      dead1.play();
                 else if(random == 1) dead2.play();
                 else if(random == 2) dead6.play();
                 else if(random == 3) dead4.play();
             }
         }
         
         if(dying){
             countRelifeTime ++;
                 if(countRelifeTime == 60) countDeadNum --;
                 else if(countRelifeTime == 120) countDeadNum --;
                 else if(countRelifeTime == 180){
                     countDeadNum--;
                     countRelifeTime = 0;
                     player.resetPosition();
                     dying = false;
                 }
             player.setCanJump();
         }
         
         if(relife == true and dying == false){
             countDeadNum = 3;
             countAngel ++;
             if(countAngel >= 300){
                 countAngel = 0;
                 relife = false;
             }
         }
                 
         for(Platform& frame : frame)
             frame.GetCollider().CheckCollision(playerC, direction, 1.0f);
         
         if(dying){         // to stop the character's music while dying
             ker1.stop(); ker2.stop(); ker3.stop();ker4.stop();ker5.stop();
             han1.stop(); han2.stop(); han3.stop();han4.stop();
             wangMusic.stop();wang1.stop();wang2.stop();wang3.stop();wang4.stop();
             tsai1.stop();tsai2.stop();tsai3.stop();tsai4.stop();
         }

         // update game logic
         sf::Texture texture;
             texture.loadFromFile("/Users/guolian/Desktop/Final/SFML template/SFML template/city.jpg");

         sf::Sprite sprite;
         sprite.setScale(sf::Vector2f(1.38f,1.38f));
         sprite.setTexture(texture);
         sprite.setPosition(0,0);
         window.draw(sprite);
         //window.clear(sf::Color(200,100,0));
         
         //draw players
         player.Draw(window);
         
         //draw platforms
         platformStart.Draw(window);
         for(Platform& platform : platforms)
             platform.Draw(window);
         for(Platform& platformsBad : platformsBad)
                   platformsBad.Draw(window);
         for(Platform& upperBound : upperBounds)
             upperBound.Draw(window);
         for(Platform& frame : frame)
             frame.Draw(window);
         
         for(Platform& tsai : tsai)
             tsai.Draw(window);
         for(Platform& wang : wang)
             wang.Draw(window);
         for(Platform& ker : ker)
             ker.Draw(window);
         for(Platform& han : han)
             han.Draw(window);
          
         //畫生命
         if(blood > 0)
         {
             if(dying == true){
             countDead.setString(std::to_string(countDeadNum));
             window.draw(countDead);
             window.draw(dead);
             }
             
             window .draw(bloodText);
             bloodNum.setString(std::to_string(blood));
             window. draw(bloodNum);
             
             window.draw(scoreText);
             
             scoreNum.setString(std::to_string(score));
             window.draw(scoreNum);
             window.display();
         }
         if(blood <= 0)
         {
             if(testForMusic == 0)
                 music.play();
             testForMusic = 100;
             beat.stop();
             totalScore.setString("Your Score: " + std::to_string(score));
             window.draw(totalScore);
             window.draw(gameOver);
             window.draw(guide);
             window.draw(bloodText);
             bloodNum.setString(std::to_string(0));
             window. draw(bloodNum);
             window.draw(scoreText);
             
             scoreNum.setString(std::to_string(score));
             window.draw(scoreNum);
             window.display();
             player.setPosition(10000, 500);
             
             if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
             {
                 restart(deltaTime, relife, countRelifeTime, countTime, speedTime, testForMusic, score, blood, increaseSpeed);
                 testForBeat = 0;
                 player.setPosition(50, 100);
                 platformStart.setPosition(sf::Vector2f(100.0f,350.0f));
                 countRelifeTime = 0;
                 player.resetSpeed();
                 music.stop();
                 relife = true;
                 dying = false;
             }
             if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
             {
                 window.close();
             }
         }
     }
 return EXIT_SUCCESS;
 }



void restart(float& deltaTime, bool& relife, float& countRelifeTime, float& countTime, float& speedTime, int& testForMusic
             , int& score, int& blood, float& increaseSpeed)
{
    deltaTime = 0.0f;
    relife = true;
    countRelifeTime = 0;
    countTime = 0;
    speedTime = 1;
    testForMusic = 0;
    score = 0;
    blood = 3;
    increaseSpeed = 5.0f;
}


void setText(sf::Text& scoreText, sf::Text& scoreNum, sf::Text& bloodText, sf::Text& bloodNum,
             sf::Text& gameOver,sf::Text& totalScore, sf::Text& dead, sf::Text& countDead, sf::Text& guide,
             sf::Font& font, sf::Font& font1)
{
     //text------------------
        scoreText.setFont(font);
        scoreText.setString("SCORE: ");
        scoreText.setCharacterSize(40);
        scoreText.setPosition(sf::Vector2f(800, 20));
        scoreText.setFillColor(sf::Color::Black);
        //score_text----------------------------
        scoreNum.setFont(font);
        scoreNum.setString("0");
        scoreNum.setCharacterSize(40);
        scoreNum.setPosition(sf::Vector2f(940, 20));
        scoreNum.setFillColor(sf::Color::Black);
        //scoreText.setFillColor(sf::Color::Black);
        //bloodText------------------

        bloodText.setFont(font);
        bloodText.setString("BLOOD: ");
        bloodText.setCharacterSize(40);
        bloodText.setPosition(sf::Vector2f(800, 60));
        bloodText.setFillColor(sf::Color::Red);
        //bloodNum------------------

        bloodNum.setFont(font);
        bloodNum.setString("3");
        bloodNum.setCharacterSize(40);
        bloodNum.setPosition(sf::Vector2f(940, 60));
        bloodNum.setFillColor(sf::Color::Red);
        //GameOverText------------------
        gameOver.setFont(font);
        gameOver.setString("Game Over!");
        gameOver.setCharacterSize(120);
        gameOver.setPosition(sf::Vector2f(160, 270));
        gameOver.setFillColor(sf::Color::Black);
        //GameOverText------------------

        totalScore.setFont(font);
        totalScore.setString("Your Score: " + std::to_string(0));
        totalScore.setCharacterSize(90);
        totalScore.setPosition(sf::Vector2f(160, 420));
        totalScore.setFillColor(sf::Color::Black);
        //GameOverText------------------

        guide.setFont(font1);
        guide.setString("Type R to restart.\nType E to exit.");
        guide.setCharacterSize(30);
        guide.setPosition(sf::Vector2f(780, 710));
        guide.setFillColor(sf::Color::Black);
        //DeadText------------------

        dead.setFont(font);
        dead.setString("You Dead!");
        dead.setCharacterSize(120);
        dead.setPosition(sf::Vector2f(260, 270));
        dead.setFillColor(sf::Color::Black);
        //DeadText------------------

        countDead.setFont(font);
        countDead.setString("3");
        countDead.setCharacterSize(120);
        countDead.setPosition(sf::Vector2f(500, 420));
        countDead.setFillColor(sf::Color::Black);
    //--//-------------------------------------------------------------------
}
