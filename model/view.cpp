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
float max_image = 732;

void generate_pip(std::vector<pip> &pip_arr){

    float y1 = -10;
    float x = 1280;
    float diff_y = 230;
    std::uniform_real_distribution<float> dist(0, 2);
    float resize_pip1 = dist(rd);

    float pip1_max = image1_size * resize_pip1 + y1;
    float y2 = diff_y + pip1_max;
    float resize_pip2 = (max_image - y2) / image2_size;
    pip_arr.emplace_back(x, y1, path_image_pip1, resize_pip1);
    pip_arr.emplace_back(x, y2 ,path_image_pip2, resize_pip2);
}

float move_x = 0.7;
float diff_x = 500;
float sum_x = 500;
float start_x = 150;
float start_y = 300;


int  main(){
    
    sf::RenderWindow window(sf::VideoMode(1280,max_image),"Flappy Bird");
    bird Bird(start_x, start_y, "../../images/Bird.png");     
    std::vector<pip> pip_arr;
    sf::Texture background;
    float point = 0;
    float point_gain = 1;
    bool lose = false;
    if(!background.loadFromFile("../../images/background.png")){
        std::cout <<"image dont loaded"<< std::endl;
        return -1;
    }
    sf::Sprite image;
    image.setTexture(background);
    
    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
    sf::Text lose_text;
    lose_text.setFillColor(sf::Color::Red);
    lose_text.setCharacterSize(50);
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Green);
    sf::Text button_text;
    button_text.setFont(font);
    button_text.setString("Restart");
    button_text.setFillColor(sf::Color::Blue);

    sf::Clock clock;
    pip_arr.reserve(100);  
    while (window.isOpen()){
        sf::Event event;
        float dt = clock.restart().asSeconds(); 
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed &&event.key.code == sf::Keyboard::Up) {
                Bird.up();
            }
            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
                if(button.getGlobalBounds().contains(click)){
                    lose = false;
                    point = 0;
                    Bird.x = start_x;
                    Bird.y = start_y;
                    Bird.image.setPosition(Bird.x, Bird.y);
                    Bird.velocity = 0;   
                    Bird.started = false; 
                    pip_arr.clear();
                    sum_x = diff_x;
                    pip_arr.reserve(100);  
                }
            }
        }
        if(dt > 0.05){
            dt = 0.05;
        }

        if(!lose){                   
            Bird.down(dt);
            for(size_t i= 0; i < pip_arr.size() ; i++){
                pip_arr[i].move();         
            }
            sum_x += move_x;        
            if(sum_x > diff_x){
                generate_pip(pip_arr);
                sum_x = move_x;
            }
        }
        
        window.clear();
        
        window.draw(image);
        window.draw(Bird.image);
        
        for(int i = pip_arr.size() - 1; i >= 0; i--){
            
            if(pip_arr[i].x <= 0){
                pip_arr.erase(pip_arr.begin() + i);
                continue;
            }
            else{
                window.draw(pip_arr[i].image);
            }

            if(abs(Bird.x - pip_arr[i].x) < 10){
                lose = true;
            }
            if(lose == false){
                point += point_gain;
            }

                   
        }

        if(Bird.y <= 0 || Bird.y >= max_image){
            lose = true;
        }
        if (lose == true){
            lose_text.setPosition(1280/2, max_image/2);
            lose_text.setString("you lost your score is: "+std::to_string(point));
            button.setPosition(1280/2, max_image/2 + 80);
            button_text.setPosition(1280/2 + 10, max_image/2 + 90);
            lose_text.setFillColor(sf::Color::Blue);
            window.draw(lose_text);
            window.draw(button);
            window.draw(button_text);
        }

        
        window.display();

        
    }  
    return 0;  
}