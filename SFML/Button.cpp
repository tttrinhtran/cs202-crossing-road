#include "Header.h"
#include "Button.h"


void menu(sf::RenderWindow &window, sf::Event &Event, sf::Text &startText, sf::Text &loadText, sf::Text &settingsText, int &current){
    while ( window.pollEvent( Event ) )
    {
        switch ( Event.type )
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                if (settingsText.getGlobalBounds().contains(mousePosF))
                    settingsText.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    settingsText.setFillColor( sf::Color( 0, 0, 0 ) );

                if (loadText.getGlobalBounds().contains(mousePosF))
                    loadText.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    loadText.setFillColor( sf::Color( 0, 0, 0 ) );

                if (startText.getGlobalBounds().contains(mousePosF))
                    startText.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    startText.setFillColor( sf::Color( 0, 0, 0 ) );
            }
                break;
            case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                if (startText.getGlobalBounds().contains(mousePosF))
                    current = 1;
                if (loadText.getGlobalBounds().contains(mousePosF))
                    std::cout << "load\n";
                if (settingsText.getGlobalBounds().contains(mousePosF))
                    std::cout << "setting\n";
            }
                break;
        }
    }
}

void setupText(sf::Text &text, std::string str, sf::Font &font, int size, int x, int y){
    text.setFont( font );
    text.setStyle( sf::Text::Bold );
    text.setString( str );
    text.setFillColor( sf::Color::Black );
    text.setCharacterSize( size );
    text.setPosition( x, y );
}

void setupLevel(sf::RenderWindow &window, sf::Font &font, sf::Event &Event){
    sf::Texture Level;
    sf::Sprite LevelImage;

    Level.loadFromFile("pic/Level.png");
    LevelImage.setTexture(Level);

    sf::Text L1;
    setupText(L1, "1", font, 100, 330, 220);

    sf::Text L2;
    setupText(L2, "2", font, 100, 640, 550);

    sf::Text L3;
    setupText(L3, "3", font, 100, 930, 220);

    sf::Text L4;
    setupText(L4, "4", font, 100, 1250, 550);

    sf::Text L5;
    setupText(L5, "5", font, 100, 1570, 220);

    while ( window.pollEvent( Event ) )
    {
        switch ( Event.type )
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseMoved:
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                if (L1.getGlobalBounds().contains(mousePosF))
                    L1.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    L1.setFillColor( sf::Color( 0, 0, 0 ) );

                if (L2.getGlobalBounds().contains(mousePosF))
                    L2.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    L2.setFillColor( sf::Color( 0, 0, 0 ) );

                if (L3.getGlobalBounds().contains(mousePosF))
                    L3.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    L3.setFillColor( sf::Color( 0, 0, 0 ) );

                if (L4.getGlobalBounds().contains(mousePosF))
                    L4.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    L4.setFillColor( sf::Color( 0, 0, 0 ) );

                if (L5.getGlobalBounds().contains(mousePosF))
                    L5.setFillColor( sf::Color( 232, 152, 93 ) );
                else
                    L5.setFillColor( sf::Color( 0, 0, 0 ) );
            }
                break;
            case sf::Event::MouseButtonPressed:
            {
                sf::Vector2i mousePos = sf::Mouse::getPosition( window );
                sf::Vector2f mousePosF( static_cast<float>( mousePos.x ), static_cast<float>( mousePos.y ) );
                if (L1.getGlobalBounds().contains(mousePosF)) {
                    setupLevel(window, "1", Event);
                }
            }
                break;
        }
    }
    window.draw(LevelImage);
    window.draw(L1);
    window.draw(L2);
    window.draw(L3);
    window.draw(L4);
    window.draw(L5);
    window.display();

}