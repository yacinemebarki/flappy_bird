#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>


class pip{
    
    public: float x;
            float y;
            float image_size;
            bool up;
            float scale;
    public: sf::Sprite image;
            std::shared_ptr<sf::Texture> pip_image;
    
    public: pip(float x, float y,std::string path, float y_size){
        this->x = x;
        this->y = y;
        this->scale = y_size;
        if(path.compare("../../images/pipe1.png") == 0){
            this->image_size = 265;
            this->up = true;
        }
        else if(path.compare("../../images/pipe2.png") == 0){
            this->image_size = 249;
            this->up = false;
        }
        else {
            std::cout <<"invalid image path"<< std::endl;
        }
        pip_image = std::make_shared<sf::Texture>();
        if(!pip_image->loadFromFile(path)){
            std::cout <<"fail to load image"<< std::endl;
            return;
        }
        image.setTexture(*pip_image);
        image.setPosition(x, y);
        image.setScale(1.0f, y_size);
    }
    public: void move(){
        float move_x = 1.5;
        x -= move_x;
        image.setPosition(x, y);
    }
    
};