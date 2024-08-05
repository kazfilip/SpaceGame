#include "Bullet.h"
#include "Player.h"
Bullet::Bullet(float startX, float startY, float targetX, float targetY, const sf::Texture *texture,Owner owner)
    : bulletOwner(owner) {
    bulletShape.setTexture(texture);
    bulletShape.setScale(5,5);
    bulletShape.setSize(sf::Vector2f(10, 10));
    bulletShape.setPosition(startX, startY);
    sf::Vector2f direction = sf::Vector2f(targetX - startX, targetY - startY);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    bulletDirection = direction / length;
}
void Bullet::update(float deltaTime) {
    bulletShape.move(bulletDirection * bulletSpeed * deltaTime);
    travelDistance++;
}
void Bullet::render(sf::RenderWindow& window)  {
    window.draw(bulletShape);
}
bool Bullet::enemyHit(Enemy& enemy, Bullet::Owner enemyOwner){
    if (bulletOwner != enemyOwner && bulletShape.getGlobalBounds().intersects(enemy.getGlobalBounds()) && enemy.alive ){
        return true;
    }
    return false;
}
bool Bullet::playerHit(const Player& player, Bullet::Owner playerOwner){
    if (bulletOwner != playerOwner && bulletShape.getGlobalBounds().intersects(player.getGlobalBounds())){
        return true;
    }
    return false;
}
Bullet::Bullet(float startX, float startY, float targetX, float targetY, const sf::Texture *texture,
               Bullet::Owner owner, int bounces): bulletOwner(owner) {
    bulletShape.setTexture(texture);
    bulletShape.setScale(5,5);
    bulletShape.setSize(sf::Vector2f(10, 10));
    bulletShape.setPosition(startX, startY);
    if (owner == Bullet::Owner::Boss){
        bulletShape.setScale(20,20);
    }
    if (owner == Bullet::Owner::EnemyT3){
        bulletShape.setScale(10,10);
    }
    if (owner == Bullet::Owner::PlayerRocket){
        bulletShape.setScale(10,10);
    }
    bulletShape.setOrigin(bulletShape.getLocalBounds().width/2,bulletShape.getLocalBounds().height/2);
    sf::Vector2f direction = sf::Vector2f(targetX - startX, targetY - startY);
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    bulletDirection = direction / length;
    float angle = std::atan2(direction.y,direction.x) * 180 / M_PI;
    bulletShape.setRotation(angle + 90);
    enemyTier = bounces;
}

