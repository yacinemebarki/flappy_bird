#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class pip{
    
    public: float x;
            float y;
    public: sf::Sprite image;
            sf::Texture pip_image;
    
    public: pip(float x, float y,std::string path){
        this->x = x;
        this->y = y;
        if(!pip_image.loadFromFile(path)){
            std::cout <<"fail to load image"<< std::endl;
            return;
        }
        image.setTexture(pip_image);
        image.setPosition(x, y);
    }
    
};