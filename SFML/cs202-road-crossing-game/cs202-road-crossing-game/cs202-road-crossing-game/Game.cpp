
#include "Game.h"

void UpdateMove( sf::Sprite &rect){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        rect.move(-30.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        rect.move(0.f,-30.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        rect.move(0.f,30.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) ){
        rect.move(30.f,0.f);
    }
}

void setupGame(sf::RenderWindow &window, std::string str, sf::Event &Event, sf::Sprite &rect){
    sf::Texture Level;
    sf::Sprite LevelImage;
    str = "level" + str;
    Level.loadFromFile("pic/"+str+".png");
    LevelImage.setTexture(Level);

    while (window.isOpen()) {
        while (window.pollEvent(Event)) {
            switch (Event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:
                    UpdateMove(rect);
                    break;
            }
        }

        window.clear();
        window.draw(LevelImage);
        //rect.move(-5.f, -5.f);
        window.draw(rect);
        window.display();
    }
}