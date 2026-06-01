#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

float y_up = 400;
class bird{
    
    public: float x;
    public: float y;
            float velocity = 0;
            float gravity = 800;
    public: sf::Sprite image;
            sf::Texture bird_image;
            bool started = false;

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
        velocity = -y_up;
        started = true;
    }
    public: void down(float dt){
        if (!started){
            return;
        }
        velocity += gravity * dt;
        y += velocity * dt;  
        if(y < 0 || y >732){
            y = 0;
            velocity = 0;
        }

        image.setPosition(x, y);
    }
};