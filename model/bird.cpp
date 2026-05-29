#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

class bird{
    
    public: float x;
    public: float y;
    public: sf::Sprite image;
            sf::Texture bird_image;

    public: bird(float x, float y, std::string path){
        this->x = x;
        this->y = y;
        if(!bird_image.loadFromFile(path)){
            std::cout <<"fail to load image"<< std::endl;
            return;
        }
        image.setTexture(bird_image);
        image.setPosition(x, y);
    }
    public: void up(){
        this->y += 30;
    }
    public: void down(){
        this->y -= 30;
    }
};