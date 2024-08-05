#include <iostream>
#include <chrono>
#include <thread>
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Graphics/CircleShape.hpp"
#include "Bullet.h"
#include "Enemy.h"
#include "Player.h"
#include "optional"
#include "Experience.h"



void loadEnemyTextures(){
    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture;
        if (texture.loadFromFile("Textures/Animations/Explosion/explosion"+std::to_string(i)+".png")){
            Enemy::deathAnimation.push_back(texture);
        }
    }
    for (int i = 1; i <= 5; ++i) {
        sf::Texture texture;
        if (texture.loadFromFile("Textures/Enemy/Attacks/T2Attack/explosion_"+std::to_string(i)+".png")){
            Enemy::explosion.push_back(texture);
        }
    }
    sf::Texture up;
    sf::Texture down;
    sf::Texture left;
    sf::Texture right;
    if (up.loadFromFile("Textures/Enemy/EnemyT1/Gray1_up.png")
        && left.loadFromFile("Textures/Enemy/EnemyT1/Gray1_left.png")
        && right.loadFromFile("Textures/Enemy/EnemyT1/Gray1_right.png")
        && down.loadFromFile("Textures/Enemy/EnemyT1/Gray1_down.png")){
        Enemy::movementTexturesT1.push_back(up);
        Enemy::movementTexturesT1.push_back(down);
        Enemy::movementTexturesT1.push_back(left);
        Enemy::movementTexturesT1.push_back(right);
    }
    if (up.loadFromFile("Textures/Enemy/EnemyT2/EnemyT2_up.png")
        && left.loadFromFile("Textures/Enemy/EnemyT2/EnemyT2_left.png")
        && right.loadFromFile("Textures/Enemy/EnemyT2/EnemyT2_right.png")
        && down.loadFromFile("Textures/Enemy/EnemyT2/EnemyT2_down.png")){
        Enemy::movementTexturesT2.push_back(up);
        Enemy::movementTexturesT2.push_back(down);
        Enemy::movementTexturesT2.push_back(left);
        Enemy::movementTexturesT2.push_back(right);
    }
    if (up.loadFromFile("Textures/Enemy/EnemyT3/EnemyT3_up.png")
        && left.loadFromFile("Textures/Enemy/EnemyT3/EnemyT3_left.png")
        && right.loadFromFile("Textures/Enemy/EnemyT3/EnemyT3_right.png")
        && down.loadFromFile("Textures/Enemy/EnemyT3/EnemyT3_down.png")){
        Enemy::movementTexturesT3.push_back(up);
        Enemy::movementTexturesT3.push_back(down);
        Enemy::movementTexturesT3.push_back(left);
        Enemy::movementTexturesT3.push_back(right);
    }

    if (up.loadFromFile("Textures/Enemy/Bosses/Boss1/Nairan - Dreadnought - Base_up.png")
        && left.loadFromFile("Textures/Enemy/Bosses/Boss1/Nairan - Dreadnought - Base_left.png")
        && right.loadFromFile("Textures/Enemy/Bosses/Boss1/Nairan - Dreadnought - Base_right.png")
        && down.loadFromFile("Textures/Enemy/Bosses/Boss1/Nairan - Dreadnought - Base_down.png")){
        Enemy::boss1Textures.push_back(up);
        Enemy::boss1Textures.push_back(down);
        Enemy::boss1Textures.push_back(left);
        Enemy::boss1Textures.push_back(right);
    }
    if (up.loadFromFile("Textures/Enemy/Bosses/Boss2/Nairan - Battlecruiser - Base_up.png")
        && left.loadFromFile("Textures/Enemy/Bosses/Boss2/Nairan - Battlecruiser - Base_left.png")
        && right.loadFromFile("Textures/Enemy/Bosses/Boss2/Nairan - Battlecruiser - Base_right.png")
        && down.loadFromFile("Textures/Enemy/Bosses/Boss2/Nairan - Battlecruiser - Base_down.png")){
        Enemy::boss2Textures.push_back(up);
        Enemy::boss2Textures.push_back(down);
        Enemy::boss2Textures.push_back(left);
        Enemy::boss2Textures.push_back(right);
    }
    if (up.loadFromFile("Textures/Enemy/Bosses/Boss3/Nautolan Ship - Battlecruiser - Base_up.png")
        && left.loadFromFile("Textures/Enemy/Bosses/Boss3/Nautolan Ship - Battlecruiser - Base_left.png")
        && right.loadFromFile("Textures/Enemy/Bosses/Boss3/Nautolan Ship - Battlecruiser - Base_right.png")
        && down.loadFromFile("Textures/Enemy/Bosses/Boss3/Nautolan Ship - Battlecruiser - Base_down.png")){
        Enemy::boss3Textures.push_back(up);
        Enemy::boss3Textures.push_back(down);
        Enemy::boss3Textures.push_back(left);
        Enemy::boss3Textures.push_back(right);
    }
    if (up.loadFromFile("Textures/Enemy/Bosses/Boss4/Nautolan Ship - Dreadnought - Base_up.png")
        && left.loadFromFile("Textures/Enemy/Bosses/Boss4/Nautolan Ship - Dreadnought - Base_left.png")
        && right.loadFromFile("Textures/Enemy/Bosses/Boss4/Nautolan Ship - Dreadnought - Base_right.png")
        && down.loadFromFile("Textures/Enemy/Bosses/Boss4/Nautolan Ship - Dreadnought - Base_down.png")){
        Enemy::boss4Textures.push_back(up);
        Enemy::boss4Textures.push_back(down);
        Enemy::boss4Textures.push_back(left);
        Enemy::boss4Textures.push_back(right);
    }


}
sf::Vector2f randomLocation(Player &player,auto &window){
    int width = window.getSize().x;
    int height = window.getSize().y;
    int playerX = player.getPosition().x;
    int playerY = player.getPosition().y;
    float x ;
    float y;
    int leftBoundary = playerX - width ;
    int rightBoundary = playerX + width ;
    int topBoundary = playerY - height ;
    int bottomBoundary = playerY + height ;
    int side = rand() % 4;
    switch (side) {
        case 0:
            x = leftBoundary;
            y = rand() % (bottomBoundary - topBoundary + 1) + topBoundary;
            break;
        case 1:
            x = rightBoundary;
            y = rand() % (bottomBoundary - topBoundary + 1) + topBoundary;
            break;
        case 2:
            x = rand() % (rightBoundary - leftBoundary + 1) + leftBoundary;
            y = topBoundary;
            break;
        case 3:
            x = rand() % (rightBoundary - leftBoundary + 1) + leftBoundary;
            y = bottomBoundary;
            break;
    }
    return {x,y};
}
void generateEnemies(std::vector<Enemy> &enemies, int &maxEnemies,Player &player,auto &window){
    if (enemies.size()<maxEnemies){
        for (int i = 0; i < maxEnemies/2; ++i) {
            enemies.emplace_back(randomLocation(player,window),1);
            int tier = rand()&10;
            if(tier <2){
                enemies.emplace_back(randomLocation(player,window),3);
            }else if (tier <=5){
                enemies.emplace_back(randomLocation(player,window),2);
            }
        }
        maxEnemies++;
    }
}
void spawnBoss(std::vector<Enemy> &enemies, float deltaTime, Player &player, auto &window){
    Enemy::bossCounter++;
    enemies.emplace_back(randomLocation(player,window),4);
}
int main() {
    const int windowWidth = 1200;
    const int windowHeight = 800;

    auto window = sf::RenderWindow(
            sf::VideoMode(windowWidth,windowHeight),"Space Survivors",
            sf::Style::Default, sf::ContextSettings(0,0,8)
    );
    window.setFramerateLimit(120);

    loadEnemyTextures();

    sf::Texture playerTexture;
    auto player = Player();
    sf::View player_view(sf::FloatRect(0,0,window.getSize().x,window.getSize().y));
    player_view.zoom(1.5);


    sf::Texture bulletTexture;
    if (!bulletTexture.loadFromFile("Textures/Attacks/bullet1.png")){
        return -1;
    }

    sf::Texture playerRocket;
    if (!playerRocket.loadFromFile("Textures/Attacks/rocket_attack.png")){
        return -1;
    }

    sf::Texture enemyBulletTexture;
    if (!enemyBulletTexture.loadFromFile("Textures/Enemy/Attacks/enemy_attack.png")){
        return -1;
    }

    sf::Texture rocket;
    if (!rocket.loadFromFile("Textures/Enemy/Attacks/T3Attack/rocket_attacks.png")){
        return -1;
    }

    sf::Texture voidTexture;
    if (!voidTexture.loadFromFile("Textures/Attacks/Void.png")){
        return -1;
    }

    player.setVoidTexture(voidTexture);
    player.setRocketTexture(rocket);
    player.setBulletTexture(bulletTexture);

    sf::Clock clock;

    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<Experience> xp;
    const float moveSpeed = 300.0f;

    sf::Time frameDuration = sf::seconds(0.1f);

    sf::Clock bossSpawner;
    sf::Time bossTimer = sf::seconds(10);

    sf::Font font;
    font.loadFromFile("Font/Pixellettersfull-BnJ5.ttf");

    sf::Text health;
    health.setFont(font);
    health.setCharacterSize(90);

    sf::Text kills;
    kills.setFont(font);
    kills.setCharacterSize(90);
    sf::Text level;
    level.setFont(font);
    level.setCharacterSize(90);

    sf::Text test;
    test.setFont(font);
    test.setPosition(100,100);
    test.setString("100,100");

    sf::Clock clockTime;
    sf::Text timeClock;
    timeClock.setFont(font);
    timeClock.setCharacterSize(90);

    int maxEnemies = 7;
    srand(static_cast<unsigned>(time(0)));

    while(window.isOpen()){
        auto event = sf::Event();
        while(window.pollEvent(event)){
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

            health.setString("Health: " + std::to_string(player.health));
            health.setPosition(player.getPosition().x - 900, player.getPosition().y - 630);
            health.setFillColor(sf::Color::Cyan);
            health.setOutlineThickness(10);
            health.setOutlineColor(sf::Color::Blue);
            kills.setString("Kills: " + std::to_string(player.kills));
            kills.setPosition(player.getPosition().x - 900, player.getPosition().y - 560);
            kills.setOutlineThickness(10);
            kills.setOutlineColor(sf::Color::Blue);
            kills.setFillColor(sf::Color::Cyan);

            timeClock.setPosition(player.getPosition().x, player.getPosition().y - 630);
            timeClock.setString(std::to_string(clockTime.getElapsedTime().asSeconds()));

            level.setString("Level: " + std::to_string(player.level));
            level.setPosition(player.getPosition().x - 900, player.getPosition().y - 490);
            level.setOutlineThickness(10);
            level.setOutlineColor(sf::Color::Blue);
            level.setFillColor(sf::Color::Cyan);

            window.clear(sf::Color::Black);
            float frameTime = clock.getElapsedTime().asSeconds();

            float deltaTime = clock.restart().asSeconds();
            if (player.alive) {
                player.attack(enemies, bullets);
                player.collect(xp, deltaTime);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    if (!playerTexture.loadFromFile("Textures/Player/green_right.png")) {
                        return -1;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        player.move(moveSpeed * frameTime + 20, 0);
                    }
                    player.setTexture(playerTexture);
                    player.move({moveSpeed * frameTime, 0});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    if (!playerTexture.loadFromFile("Textures/Player/green_left.png")) {
                        return -1;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        player.move(moveSpeed * frameTime - 20, 0);
                    }
                    player.setTexture(playerTexture);
                    player.move({-moveSpeed * frameTime, 0});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    if (!playerTexture.loadFromFile("Textures/Player/green_up.png")) {
                        return -1;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        player.move(0, -moveSpeed * frameTime - 20);
                    }
                    player.setTexture(playerTexture);
                    player.move({0, -moveSpeed * frameTime});
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    if (!playerTexture.loadFromFile("Textures/Player/green_down.png")) {
                        return -1;
                    }
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                        //zrobic cooldown
                        player.move(0, moveSpeed * frameTime + 20);
                    }
                    player.setTexture(playerTexture);
                    player.move({0, moveSpeed * frameTime});
                }
                if (player.immune && player.healthTimer.getElapsedTime() >= sf::seconds(4)) {
                    player.immune = false;
                }
                if (player.kills % 100 == 0 && player.kills != 0 && bossSpawner.getElapsedTime() >= bossTimer) {
                    spawnBoss(enemies, deltaTime, player, window);
                    bossSpawner.restart();
                }
            }else {
                player.death();
            }
            generateEnemies(enemies, maxEnemies, player, window);
            for (int i = 0; i < enemies.size(); i++) {
                enemies[i].setTarget(player);
                for (int j = i + 1; j < enemies.size(); ++j) {
                    if (enemies[i].checkCollision(enemies[j]) || enemies[i].checkCollisionT3(enemies[j])) {
                        enemies[i].collision(enemies[j]);
                    }
                }
                if (enemies[i].tier == 1) {
                    enemies[i].update(deltaTime, xp, Enemy::movementTexturesT1);
                    enemies[i].attack(bullets, bulletTexture);
                } else if (enemies[i].tier == 2) {
                    enemies[i].checkExplosionDistance();
                    if (enemies[i].exploding) {
                        player.loseHealth(2);
                    }
                    enemies[i].update(deltaTime, xp, Enemy::movementTexturesT2);
                } else if (enemies[i].tier == 3) {
                    enemies[i].update(deltaTime, xp, Enemy::movementTexturesT3);
                    enemies[i].attack(bullets, rocket);
                } else if (enemies[i].tier == 4) {
                    switch (enemies[i].bossType) {
                        case 0:
                            enemies[i].update(deltaTime, xp, Enemy::boss1Textures);
                            break;
                        case 1:
                            enemies[i].update(deltaTime, xp, Enemy::boss2Textures);
                            break;
                        case 2:
                            enemies[i].update(deltaTime, xp, Enemy::boss3Textures);
                            break;
                        case 3:
                            enemies[i].update(deltaTime, xp, Enemy::boss4Textures);
                            break;
                    }
                    enemies[i].bossAttack(bullets, enemyBulletTexture, enemies);
                }
            }
            for (auto &bullet: bullets) {
                if (bullet.bulletOwner == Bullet::Owner::Enemy) {
                    bullet.bulletShape.setTexture(&enemyBulletTexture);
                } else if (bullet.bulletOwner == Bullet::Owner::EnemyT3) {
                    bullet.bulletShape.setTexture(&rocket);
                    bullet.bulletSpeed = 1500.0f;
                } else if (bullet.bulletOwner == Bullet::Owner::Boss) {
                    bullet.bulletShape.setTexture(&enemyBulletTexture);
                } else if (bullet.bulletOwner == Bullet::Owner::PlayerRocket) {
                    bullet.bulletShape.setTexture(&playerRocket);
                    bullet.bulletShape.setScale(10, 10);
                } else if (bullet.bulletOwner == Bullet::Owner::Void) {
                    bullet.bulletShape.setTexture(&voidTexture);
                    bullet.bulletShape.setScale(40, 40);
                } else bullet.bulletShape.setTexture(&bulletTexture);
                bullet.update(deltaTime);
            }
            bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [&](Bullet &bullet) {
                if (bullet.playerHit(player, Bullet::Owner::Player)) {
                    if (player.health > 0 && !player.immune) {
                        if (bullet.bulletOwner == Bullet::Owner::Boss) {
                            player.loseHealth(3);
                        } else if (bullet.bulletOwner == Bullet::Owner::EnemyT3) {
                            player.loseHealth(2);
                        } else player.loseHealth(1);
                        player.death();
                        return true;
                    }
                }
                if (bullet.travelDistance >= bullet.maxTravelDistance) {
                    return true;
                }
                for (auto &enemy: enemies) {
                    if (bullet.enemyHit(enemy, Bullet::Owner::Enemy) && bullet.enemyHit(enemy, Bullet::Owner::EnemyT3)
                        && bullet.enemyHit(enemy, Bullet::Owner::Boss)) {
                        if (bullet.bulletOwner == Bullet::Owner::PlayerRocket) {
                            enemy.loseHealth(player.basicAttack, player.basicDamage * 2);
                        } else if (bullet.bulletOwner == Bullet::Owner::Void) {
                            enemy.loseHealth(player.basicAttack, player.basicDamage * 3);
                            if (enemy.health <= 0 && enemy.alive) {
                                player.kills++;
                                enemy.death();
                            }
                            return false;
                        } else {
                            enemy.loseHealth(player.basicAttack, player.basicDamage);
                        }
                        if (enemy.health <= 0 && enemy.alive) {
                            player.kills++;
                            enemy.death();
                        }
                        return true;
                    }
                }
                return false;
            }), bullets.end());
            enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [&](Enemy &enemy) {
                return !enemy.alive && !enemy.animating && !enemy.exploding;
            }), enemies.end());
            xp.erase(std::remove_if(xp.begin(), xp.end(), [&](Experience &exp) {
                if (player.xpCollect(exp)) {
                    return true;
                }
                return false;
            }), xp.end());

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
            player_view.setCenter(player.getPosition());
            window.setView(player_view);

            for (auto &exp: xp) {
                window.draw(exp);
            }
            if (player.alive || player.animating) {
                window.draw(player);
            }
            for (const auto &enemy: enemies) {
                window.draw(enemy);
            }
            for (auto &bullet: bullets) {
                bullet.render(window);
            }
            window.draw(health);
            window.draw(kills);
            if (player.maxLevel) {
                level.setString("Level: " + std::to_string(player.level) + " (MAX)");
            }
            window.draw(level);
        if (player.alive){
            window.draw(timeClock);
        }
            window.display();
    }
}

