#include "GlobalObjects.hpp"

const float GlobalObjects::windowWidth = 512.f;
const float GlobalObjects::windowHeight = 512.f;
sf::RenderWindow GlobalObjects::window(sf::VideoMode(windowWidth, windowHeight), "Breakout", sf::Style::Close | sf::Style::Titlebar);
int GlobalObjects::score(0);
int GlobalObjects::playerLifes(3);