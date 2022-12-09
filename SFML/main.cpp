#include "Header.h"
#include "Button.h"

int width = 1920, height = 1080, current = 0;

int main(){
    sf::Texture santa;
    sf::Sprite rect;
    santa.loadFromFile("pic/santa.png");
    rect.setTexture(santa);
    rect.setScale(0.4,0.4);
    rect.setPosition(900,900);

    sf::Texture background;
    sf::Sprite backgroundImage;

    background.loadFromFile( "pic/background.png" );

    sf::RenderWindow window(sf::VideoMode(width,height), "Crossing road");
    window.setFramerateLimit(60);
    backgroundImage.setTexture( background );

    sf::Font font;
    font.loadFromFile( "ARCADECLASSIC.TTF" );

    sf::Text startText;
    sf::Text loadText;
    sf::Text settingsText;

    setupText(startText, "Create New Game", font, 80, 700, 400);
    setupText(loadText, "Load Game", font, 80, 700, 480);
    setupText(settingsText, "Settings", font, 80, 700, 560);

    while ( window.isOpen() )
    {
        sf::Event Event;

        menu(window, Event, startText, loadText, settingsText, current);

        window.clear();
        if (current == 0) {
            window.draw(backgroundImage);
            window.draw(startText);
            window.draw(loadText);
            window.draw(settingsText);
            window.display();
        }
        else if (current == 1){
            setupLevel(window, font, Event, current, rect);
        }
    }
    return 0;
}

