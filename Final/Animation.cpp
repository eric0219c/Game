#include "Animation.h"

// 角色的動畫，向左向右會走動
Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
{
    this-> imageCount = imageCount;
    this-> switchTime = switchTime;
    totalTime = 0.0f;
    currentImage.x = 0;
    
    uvRect.width = texture->getSize().x / float(imageCount.x);
    uvRect.height = texture->getSize().y/ float(imageCount.y);
}

Animation::~Animation()
{
    
}

void Animation::Update(int row,float deltaTime, bool faceRight)
{
    currentImage.y = row;
    totalTime += deltaTime;
    
    if(totalTime > switchTime)
    {
        totalTime -= switchTime;
        currentImage.x++;
        
        if(currentImage.x >= imageCount.x)
        {
            currentImage.x = 0;
        }
    }
    
    uvRect.top = currentImage.y * uvRect.height;
    

    if (faceRight)
    {
        uvRect.left = currentImage.x * uvRect.width;            // 如果向右，圖形為第一個圖示，uvRect.left就是從左邊數過來
        uvRect.width = abs(uvRect.width);
    }
    else
    {
        uvRect.left = (currentImage.x +1) * abs(uvRect.width);      //如果向右，則把uvRect設在第一張圖的右邊，然後向左橫跨一張圖，就可以反轉圖片了
        uvRect.width = -abs(uvRect.width);
    }
    
}
