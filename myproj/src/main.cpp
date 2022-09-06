#include <SFML/Graphics.hpp>
#include "GlobalObjects.hpp"
#include "BlocksField.hpp"
#include "Paddle.hpp"
#include "Game.hpp"
#include "Menu.hpp"

void mainMenu(){
    sf::Event event;
    Menu menu(300,400);
    while(GlobalObjects::window.isOpen()){
        while (GlobalObjects::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GlobalObjects::window.close();
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            menu.MoveUp();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            menu.MoveDown();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            if (menu.GetPressedItem() == 0){
                break;
            }
            else{
                GlobalObjects::window.close();
            }
        }
        menu.draw(GlobalObjects::window);
        GlobalObjects::window.display();
    }
}

void gameProccess(){
    GlobalObjects::score = 0;
    GlobalObjects::playerLifes = 3;

    sf::Event event;
    float deltaTime;

    BlocksField blocksField(sf::Vector2f(GlobalObjects::windowWidth, 200.f), sf::Vector2f(0.f, 0.f), sf::Color::Yellow, 9, 7);

    Game::createBall(Ball(10.f, sf::Vector2f(425.0710f, 400.f), sf::Color::Red, 180.f, 110.f));

    //Paddle paddle(sf::Vector2f(100.f, 10.f), sf::Vector2f(256.f, 450.f), sf::Color::Green, 200.f);
    Game::createPaddle(Paddle(sf::Vector2f(100.f, 10.f), sf::Vector2f(256.f, 450.f), sf::Color::Green, 200.f));

    sf::Clock pauseClock;
    sf::Time time = pauseClock.getElapsedTime();
    while(time.asSeconds() < 3){
        time = pauseClock.getElapsedTime();

        while (GlobalObjects::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GlobalObjects::window.close();
        }


        GlobalObjects::window.clear(sf::Color::Black);

        sf::Text toStart;
        sf::Font font;
        font.loadFromFile("resources/cheeseburger.ttf");

        toStart.setFont(font);
        toStart.setColor(sf::Color::White);
        toStart.setString(std::to_string((int)(3 - time.asSeconds())));
        toStart.setPosition(sf::Vector2f(GlobalObjects::windowWidth / 2, GlobalObjects::windowHeight /  2));

        GlobalObjects::window.draw(toStart);

        blocksField.Draw(GlobalObjects::window);
        Game::Draw(GlobalObjects::window);

        GlobalObjects::window.display();
    }

    sf::Clock clock;

    while (GlobalObjects::window.isOpen())
    {
        time = pauseClock.getElapsedTime();
        sf::Text timeFromStart;
        sf::Text scoreText;
        sf::Text lifesText;
        sf::Font font;
        font.loadFromFile("resources/cheeseburger.ttf");

        timeFromStart.setFont(font);
        timeFromStart.setColor(sf::Color::White);
        timeFromStart.setString("Time: " + std::to_string((int)(time.asSeconds() - 3)));
        timeFromStart.setPosition(sf::Vector2f(GlobalObjects::windowWidth / 8, GlobalObjects::windowHeight /  1.1));

        scoreText.setFont(font);
        scoreText.setColor(sf::Color::White);
        scoreText.setString("Score: " + std::to_string(GlobalObjects::score));
        scoreText.setPosition(sf::Vector2f(GlobalObjects::windowWidth / 2.5, GlobalObjects::windowHeight /  1.1));

        lifesText.setFont(font);
        lifesText.setColor(sf::Color::White);
        lifesText.setString("Lifes: " + std::to_string(GlobalObjects::playerLifes));
        lifesText.setPosition(sf::Vector2f(GlobalObjects::windowWidth / 1.5, GlobalObjects::windowHeight /  1.1));

        deltaTime = clock.restart().asSeconds();

        while (GlobalObjects::window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                GlobalObjects::window.close();
        }

        Game::Update(deltaTime, blocksField);

        GlobalObjects::window.clear(sf::Color::Black);

        blocksField.Draw(GlobalObjects::window);
        Game::Draw(GlobalObjects::window);

        GlobalObjects::window.draw(timeFromStart);
        GlobalObjects::window.draw(scoreText);
        GlobalObjects::window.draw(lifesText);

        GlobalObjects::window.display();

        if (Game::getBallPositionY() > GlobalObjects::windowHeight - 25){
            GlobalObjects::playerLifes -= 1;
            Game::createBall(Ball(10.f, sf::Vector2f(425.0710f, 400.f), sf::Color::Red, 180.f, 110.f));
            if (GlobalObjects::playerLifes <= 0){
                break;
            }
        }
    }
    GlobalObjects::window.clear(sf::Color::Black);

    sf::Text toStart;
    sf::Font font;
    font.loadFromFile("resources/cheeseburger.ttf");

    toStart.setFont(font);
    toStart.setColor(sf::Color::White);
    toStart.setString("Your score: " + std::to_string(GlobalObjects::score));
    toStart.setPosition(sf::Vector2f(GlobalObjects::windowWidth / 4, GlobalObjects::windowHeight /  2));

    GlobalObjects::window.draw(toStart);

    GlobalObjects::window.display();

    pauseClock.restart();
    time = pauseClock.getElapsedTime();
    while(time.asSeconds() < 3){
        time = pauseClock.getElapsedTime();
    }

    GlobalObjects::window.clear(sf::Color::Black);
}

int main()
{
    while (GlobalObjects::window.isOpen()){
        mainMenu();

        gameProccess();
    }

    return 0;
}