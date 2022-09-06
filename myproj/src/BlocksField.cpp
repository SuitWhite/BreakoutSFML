#include <iostream>
#include <random>
#include "BlocksField.hpp"

BlocksField::BlocksField(const sf::Vector2f & size, const sf::Vector2f & position, const sf::Color & color, int columns, int rows)
{
    sf::Vector2f blockSize(size.x / columns, size.y / rows);

    std::srand(time(NULL));

    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {  
            
            sf::Color colorToPush = color;
            if (std::rand()%5==0){
                colorToPush.r += 30;
                blocks.push_back(Block(blockSize - sf::Vector2f(4.f, 4.f), position + sf::Vector2f(blockSize.x * i + 2.f, blockSize.y * j + 2.f), colorToPush, 3));
            } else if (std::rand()%4==0){
                colorToPush.b += 30;
                blocks.push_back(Block(blockSize - sf::Vector2f(4.f, 4.f), position + sf::Vector2f(blockSize.x * i + 2.f, blockSize.y * j + 2.f), colorToPush, 2));
            } else{
                colorToPush.g += 30;
                blocks.push_back(Block(blockSize - sf::Vector2f(4.f, 4.f), position + sf::Vector2f(blockSize.x * i + 2.f, blockSize.y * j + 2.f), colorToPush, 1));
            }
        }
    }
}

void BlocksField::Update(Ball & ball)
{
    for (auto & block: blocks){
        if (ball.checkColission(block)){
            block.Hit();
            GlobalObjects::score += 3;
        }
    }
    
    blocks.remove_if([&ball, this](const Block & block)->bool { return block.getLifes() <= 0; });
}

void BlocksField::Draw(sf::RenderWindow & window)
{
    for (auto &block : blocks)
    {
       block.Draw(window);
    }
}
