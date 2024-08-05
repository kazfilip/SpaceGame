#ifndef PROJECT_2024_EXPERIENCE_H
#define PROJECT_2024_EXPERIENCE_H
#include "SFML/Graphics.hpp"

struct Experience:sf::CircleShape{
    int value = 1;
    enum class Utility {XP,HEALTH};
    Utility type;
    Experience(float x, float y,Utility utility){
        if(utility == Utility::HEALTH){
            setFillColor(sf::Color::Red);
            type = Utility::HEALTH;
        }else {
            setFillColor(sf::Color::Blue);
            type = Utility::XP;
        }
        setRadius(10);
        setPosition(x,y);
    }
};




#endif
