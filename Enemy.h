#pragma once

#ifndef PROJECT_2024_ENEMY_H
#define PROJECT_2024_ENEMY_H


#include <iostream>
#include <memory>
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "Experience.h"
#include "Collider.h"
class Bullet;

struct Enemy:sf::Sprite{
    Enemy(sf::Vector2f location, int tier);

    sf::Sprite target;
    std::string name;
    int health = 3;
    int currentFrame = 0;
    bool alive = true;
    bool targetfound = false;
    bool animating = false;
    float speed = 350.0f;
    float stopDistance = 500;
    bool targeted = false;

    sf::Texture enemyTextureRight;
    sf::Texture enemyTextureLeft;
    sf::Texture enemyTextureUp;
    sf::Texture enemyTextureDown;
    sf::Vector2f movementDirection;
    static std::vector<sf::Texture> deathAnimation;
    static std::vector<sf::Texture> movementTexturesT1;
    static std::vector<sf::Texture> movementTexturesT2;
    static std::vector<sf::Texture> movementTexturesT3;
    static std::vector<sf::Texture> boss1Textures;
    static std::vector<sf::Texture> boss2Textures;
    static std::vector<sf::Texture> boss3Textures;
    static std::vector<sf::Texture> boss4Textures;
    static std::vector<sf::Texture> explosion;


    sf::Clock explodeTime;
    sf::Time explodeDuration = sf::seconds(0.1f);
    int explodeFrame = 0;
    bool exploded = false;
    bool exploding = false;

    bool killed = false;
    static int bossCounter ;
    int bossType;
    sf::Clock series;
    sf::Time seriesInterval = sf::seconds(0.1f);
    sf::Time bossAttackInterval = sf::seconds(0.5f);
    int currentShots = 0;
    int seriesShots = 5;


    sf::Time spawnTime = sf::seconds(0.2f);
    sf::Clock spawner;
    int enemiesSpawned = 0;
    bool spawning = false;


    int maxSpawnedBombs = 20;
    int spawnedBombs = 0;

    float cos = 0.5f;

    sf::Clock animation;
    sf::Time frameDuration = sf::seconds(0.1f);
    sf::Clock attackClock;
    sf::Time attackInterval = sf::seconds(1.5);
    sf::Time rocketInterval = sf::seconds(2.5);
    float separationRadius = 50;
    int tier;
    sf::RectangleShape body;


    int direction;


    auto attack(std::vector<Bullet>& bullets,sf::Texture bulletTexture)->void;
    auto loseHealth(std::string& attack, int damage) -> void;
    void death();
    auto setTarget(const sf::Sprite& target)->void;

    Collider getCollider() {return Collider(body);};

    virtual ~Enemy(){}
public:
    float distance(const sf::Vector2f& point1, const sf::Vector2f& point2);
    void collision(Enemy &enemy);
    bool checkCollision(Enemy two);
    void update(float deltaTime, std::vector<Experience> &xp, std::vector<sf::Texture> &movementTexture);
    float getDistance();
    void checkExplosionDistance();
    bool checkCollisionT3(Enemy two);
    void bossAttack(std::vector<Bullet> &bullets, const sf::Texture& bulletTexture, std::vector<Enemy> &enemies);
};


#endif
