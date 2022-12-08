
#include "Game.h"

void setupLevel(sf::RenderWindow &window, std::string str, sf::Event &Event){
    sf::Texture Level;
    sf::Sprite LevelImage;
    str = "level" + str;
    Level.loadFromFile("pic/"+str+".png");
    LevelImage.setTexture(Level);



    while ( window.pollEvent( Event ) )
    {
        switch ( Event.type ) {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                window.clear();
                window.draw(LevelImage);
                window.display();
                break;
        }
    }
}