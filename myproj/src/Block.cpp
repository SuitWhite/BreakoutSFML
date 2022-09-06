#include "Block.hpp"

Block::Block(const sf::Vector2f & size, const sf::Vector2f & position, const sf::Color & color, const int &lifes)
{
    rect.setSize(size);
    rect.setPosition(position);
    rect.setFillColor(color);
    this->lifes = lifes;
}

void Block::Draw(sf::RenderWindow & window)
{
    window.draw(rect);
}

void Block::Hit()
{
    this->lifes -= 1;
}
