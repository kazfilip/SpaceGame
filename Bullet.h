#pragma once
#ifndef PROJECT_2024_BULLET_H
#define PROJECT_2024_BULLET_H
#include <SFML/Graphics.hpp>
#include <cmath>
#include <vector>
#include <iostream>
#include "Player.h"

class Enemy;
class Bullet {
public:
    enum class Owner {Player,Enemy,EnemyT3,Boss,PlayerRocket,Void};
    Owner bulletOwner;
    int enemyTier = 0;
    float travelDistance = 0;
    float maxTravelDistance = 500;
    Bullet(float startX, float startY, float targetX, float targetY, const sf::Texture *texture, Owner owner);
    Bullet(float startX, float startY, float targetX, float targetY, const sf::Texture *texture, Owner owner,int bounces);
    void update(float deltaTime);
    void render(sf::RenderWindow& window) ;
    bool enemyHit(Enemy& enemy, Bullet::Owner bulletOwner);
    sf::RectangleShape bulletShape;
    int bounces=0;
    bool playerHit(const Player& player, Owner playerOwner);
    float bulletSpeed = 750.0f;

private:

    sf::Vector2f bulletDirection;
};

#endif
