#include <SFML/Graphics.hpp>
#include <iostream>
#include "bird.cpp"

int main(){
    
    sf::RenderWindow window(sf::VideoMode(1280,732),"Flappy Bird");
    bird Bird(150, 300, "../../images/Bird.png");   
    sf::Texture background;
    if(!background.loadFromFile("../../images/background.png")){
        std::cout <<"image dont loaded"<< std::endl;
        return -1;
    }
    sf::Sprite image;
    image.setTexture(background);
    
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(20);
    text.setFillColor(sf::Color::White);

    while (window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
        }
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        text.setString("X: " + std::to_string(mousePos.x) +" Y: " + std::to_string(mousePos.y));
        text.setPosition(10, 10);
        window.clear();
        window.draw(image);
        window.draw(Bird.image);
        window.draw(text);
        window.display();
    }
    return 0;
    
}