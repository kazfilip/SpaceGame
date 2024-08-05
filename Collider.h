#ifndef PROJECT_2024_COLLIDER_H
#define PROJECT_2024_COLLIDER_H


#include "SFML/Graphics.hpp"

class Collider {
public:
    Collider(sf::RectangleShape& body);
    void move(float dx,float dy){body.move(dx,dy);};
    bool checkCollision(Collider other, float push);
    sf::Vector2f getPosition(){return body.getPosition();};
    sf::Vector2f getHalfSize(){return body.getSize()/2.0f;};

private:
    sf::RectangleShape& body;
};

#endif