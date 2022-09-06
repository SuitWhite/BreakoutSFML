#ifndef BLOCKSFIELD_HPP_
#define BLOCKSFIELD_HPP_

#include <list>
#include "Ball.hpp"

class BlocksField
{
private:
    std::list<Block> blocks;

public:
    BlocksField(const sf::Vector2f & size, const sf::Vector2f & position, const sf::Color & color, int columns, int rows);

    void Update(Ball & ball);

    void Draw(sf::RenderWindow & window);
};

#endif // BLOCKSFIELD_HPP_
