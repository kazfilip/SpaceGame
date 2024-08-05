#ifndef PROJECT_2024_PLAYER_H
#define PROJECT_2024_PLAYER_H

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "Enemy.h"

struct Player:sf::Sprite{
    const float movement_speed = 250.0f;
    sf::Texture texture;
    float range = 50;
    float stopDistance = 150;
    sf::Texture bulletTexture;
    sf::Clock playerTime;
    sf::Time attackInterval = sf::seconds(0.5);
    int health = 10;
    int maxHealth = 10;
    int currentXp=0;
    int xpToLevel = 10;
    int level = 1;
    int basicDamage = 1;
    std::string basicAttack = "basic";
    float collectDistance = 200;
    int targets = 1;
    bool ricochet = false;
    std::vector<sf::Texture> deathAnimation;
    std::vector<std::string> attacks;
    sf::Clock animation;
    sf::Time frameDuration = sf::seconds(0.1f);
    int currentFrame = 0;
    bool animating = false;
    bool alive = true;
    sf::Clock healthTimer;
    bool immune = false;
    int kills = 0;
    bool maxLevel=false;

    bool attack2Unlocked = false;
    int maxRockets = 5;
    sf::Clock rockets;
    sf::Time rocketInterval = sf::seconds(1.5);
    sf::Texture rocketTexture;

    bool attack3Unlocked = false;
    sf::Clock voidAttack;
    sf::Time voidInterval = sf::seconds(0.3);
    sf::Texture voidTexture;

    std::vector<Enemy> closestTargets;
public:
    Player(){
        if (texture.loadFromFile("Textures/Player/green.png")){
            setTexture(texture);
            setPosition(100,100);
            setScale(0.5,0.5);
            loadTextures();
        }
    }
    void setRocketTexture(const sf::Texture& texture1);
    void setBulletTexture(const sf::Texture& texture1);
    void attack(const std::vector<Enemy>& enemies,std::vector<Bullet>& bullets);
    bool xpCollect(Experience& exp);
    void levelUp(int level);
    void collect(std::vector<Experience> &exp,float deltaTime);
    void death();
    void loadTextures();
    void xpIncrease();
    std::unique_ptr<Enemy> findClosestEnemy(const std::vector<Enemy>& enemies);
    void setVoidTexture(const sf::Texture &texture1);

    void loseHealth(int damage);
};
#endif
