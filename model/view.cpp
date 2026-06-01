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



float move_x = 1.5;
float diff_x = 500;
float sum_x = 500;
float start_x = 150;
float start_y = 300;
bool start = false;

void resetGame(bird &Bird, std::vector<pip> &pip_arr,int &point, bool &lose, bool &start,float &sum_x, sf::Clock &clock){
    lose = false;
    start = false;
    point = 0;
    Bird.x = start_x;
    Bird.y = start_y;
    Bird.velocity = 0;
    Bird.started = false;
    Bird.image.setPosition(Bird.x, Bird.y);
    pip_arr.clear();
    sum_x = 0;         
    clock.restart();    
}

int  main(){
    
    sf::RenderWindow window(sf::VideoMode(1280,max_image),"Flappy Bird");
    bird Bird(start_x, start_y, "../../images/Bird.png");     
    std::vector<pip> pip_arr;
    sf::Texture background;
    int point = 0;
    int point_gain = 1;
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
    lose_text.setFont(font);
    sf::RectangleShape button(sf::Vector2f(200, 50));
    button.setFillColor(sf::Color::Green);
    sf::Text button_text;
    button_text.setFont(font);
    button_text.setString("Restart");
    button_text.setFillColor(sf::Color::Blue);
    

    sf::Text point_text;
    point_text.setFont(font);
    point_text.setFillColor(sf::Color::Green);
    point_text.setCharacterSize(50); 
    point_text.setPosition(sf::Vector2f(1280/2, 10));

    sf::Clock clock;
    pip_arr.reserve(100);  
    point_text.setString("0");

    while (window.isOpen()){
        sf::View view(sf::FloatRect(0, 0,window.getSize().x,window.getSize().y));
        window.setView(view);
        sf::Event event;
        float dt = clock.restart().asSeconds(); 
        image.setScale(1280.f / image.getTexture()->getSize().x,732.f / image.getTexture()->getSize().y);
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                Bird.up();
                start = true;
            }
            if(event.type == sf::Event::MouseButtonPressed){
                sf::Vector2f click(event.mouseButton.x, event.mouseButton.y);
                std::cout<<event.mouseButton.x<<event.mouseButton.y<<std::endl;

                if(button.getGlobalBounds().contains(click) && lose){
                    resetGame(Bird, pip_arr, point, lose, start, sum_x, clock);
                }
            }
            
        }
        if(dt > 0.05 && start){
            dt = 0.05;
        }
        sf::Vector2u winSize = window.getSize();

        float centerX = winSize.x / 2.0f - 100;
        float centerY = winSize.y / 2.0f;
        button.setPosition(centerX, centerY + 80);
        button_text.setPosition(centerX + 10, centerY + 90);
        lose_text.setPosition(centerX, centerY);    
        if(!lose && start){                   
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
                if(pip_arr[i].up == true && Bird.y < pip_arr[i].image_size * pip_arr[i].scale){
                    lose = true;
                }
                if(pip_arr[i].up == false && Bird.y > pip_arr[i].y){
                    lose = true;
                }
                if(lose == false){
                    point += point_gain;
                    point_text.setString(std::to_string(point/26));

                }
            }
            

                   
        }
        window.draw(point_text);
        if(Bird.y <= 0 || Bird.y >= max_image){
            lose = true;
        }
        if (lose == true){
            lose_text.setPosition(1280/2, max_image/2);
            lose_text.setString("you lost your score is: "+std::to_string(point/26));
            lose_text.setFillColor(sf::Color::Blue);
            window.draw(lose_text);
            window.draw(button);
            window.draw(button_text);
        }

        
        window.display();

        
    }  
    return 0;  
}