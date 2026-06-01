#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>
#include <string>
#include "bird.cpp"
#include "pip.cpp"


std::random_device rd;
float image1_size = 265;
float image2_size = 249;
std::string path_image_pip1 = "../../images/pipe1.png";
std::string path_image_pip2 = "../../images/pipe2.png";

void generate_pip(std::vector<pip> &pip_arr){

    float y1 = -10;
    float x = 1280;
    float diff_y = 230;
    std::uniform_real_distribution<float> dist(0, 2);
    float resize_pip1 = dist(rd);

    float pip1_max = image1_size * resize_pip1 + y1;
    float y2 = diff_y + pip1_max;
    float resize_pip2 = (732 - y2) / image2_size;
    std::cout << "h1 = " << image1_size * resize_pip1 << "\n";
    std::cout << "y2 = " << y2 << "\n";
    pip_arr.emplace_back(x, y1, path_image_pip1, resize_pip1);
    pip_arr.emplace_back(x, y2 ,path_image_pip2, resize_pip2);
}

float move_x = 0.7;
float diff_x = 500;
float sum_x = 500;


int main(){
    
    sf::RenderWindow window(sf::VideoMode(1280,732),"Flappy Bird");
    bird Bird(150, 300, "../../images/Bird.png");     
    std::vector<pip> pip_arr;
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
    sf::Clock clock;
    while (window.isOpen()){
        sf::Event event;
        float dt = clock.restart().asSeconds(); 
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Up) {
                Bird.up();
                std::cout<<"key preesed"<<std::endl;
            }
        }
        if(dt > 0.05){
            dt = 0.05;
        }
        Bird.down(dt);

        if(sum_x > diff_x){
            generate_pip(pip_arr);
            sum_x = move_x;
        }
        

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        text.setString("X: " + std::to_string(mousePos.x) +" Y: " + std::to_string(mousePos.y));
        text.setPosition(10, 10);
        window.clear();
        
        window.draw(image);
        window.draw(Bird.image);
        
        for(size_t i = 0; i < pip_arr.size() ; i++){
            window.draw(pip_arr[i].image);         
        }

        window.draw(text);
        
        window.display();

        for(size_t i= 0; i < pip_arr.size() ; i++){
            pip_arr[i].move();         
        }
        sum_x += move_x;
    }
    return 0;
    
}