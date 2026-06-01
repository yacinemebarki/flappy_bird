#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

class pip{
    
    public: float x;
            float y;
            float image_size;
    public: sf::Sprite image;
            sf::Texture pip_image;
    
    public: pip(float x, float y,std::string path, float y_size){
        this->x = x;
        this->y = y;
        if(path.compare("../../images/pipe1.png") == 0){
            this->image_size = 265;
        }
        else if(path.compare("../../images/pipe2.png") == 0){
            this->image_size = 249;
        }
        else {
            std::cout <<"invalid image path"<< std::endl;
        }
        if(!pip_image.loadFromFile(path)){
            std::cout <<"fail to load image"<< std::endl;
            return;
        }
        image.setTexture(pip_image);
        image.setPosition(x, y);
        image.setScale(1.0f, y_size);
    }
    public: void move(){
        float move_x = 0.7;
        x -= move_x;
        image.setPosition(x, y);
    }
    
};