#include <valarray>
#include "Enemy.h"
#include "Bullet.h"
#include "Experience.h"

std::vector<sf::Texture> Enemy::deathAnimation = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::movementTexturesT1 = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::movementTexturesT2 = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::movementTexturesT3 = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::boss1Textures = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::boss2Textures = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::boss3Textures = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::boss4Textures = std::vector<sf::Texture>();
std::vector<sf::Texture> Enemy::explosion = std::vector<sf::Texture>();
int Enemy::bossCounter = 0;
auto Enemy::loseHealth(std::string& attack, int damage) -> void{
    if (health>0){
        if (attack=="basic"){
            health-=damage;
        }
    }
}
auto Enemy::death() -> void {
    targetfound = false;
    alive = false;
    killed = true;
    animating = true;
    animation.restart();
}
auto Enemy::setTarget(const sf::Sprite& target) -> void {
    targetfound = true;
    this->target = target;
}
auto Enemy::attack(std::vector<Bullet> &bullets, const sf::Texture bulletTexture) -> void {
    if (targetfound && attackClock.getElapsedTime() >= attackInterval && tier == 1){
        sf::Vector2f playerPosition = target.getPosition();
        if (distance(target.getPosition(),getPosition())>=stopDistance
                    && distance(target.getPosition(),getPosition()) <= 1000
                    ){
            bullets.emplace_back(Bullet(this->getPosition().x,this->getPosition().y,
                                        playerPosition.x,playerPosition.y,
                                        &bulletTexture,Bullet::Owner::Enemy,tier));
            attackClock.restart();
        }
    }else if (targetfound && attackClock.getElapsedTime() >= rocketInterval && tier == 3){
        sf::Vector2f playerPosition = target.getPosition();
        if (distance(target.getPosition(),getPosition())>=stopDistance){
            bullets.emplace_back(Bullet(this->getPosition().x,this->getPosition().y,
                                        playerPosition.x,playerPosition.y,
                                        &bulletTexture,Bullet::Owner::EnemyT3,tier));
            attackClock.restart();
        }
    }
}
void Enemy::bossAttack(std::vector<Bullet> &bullets, const sf::Texture& bulletTexture, std::vector<Enemy> &enemies){
    if (targetfound && attackClock.getElapsedTime() >= bossAttackInterval){
        int attack = rand()%4;
        switch (attack) {
            case 0: {
                sf::Vector2f playerPosition = target.getPosition();
                if (direction == 0) {
                    if (distance(target.getPosition(),getPosition())>=stopDistance
                        && tier == 4) {
                            if (series.getElapsedTime() >= seriesInterval){
                                if (currentShots<seriesShots) {
                                    bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                playerPosition.x + 20, playerPosition.y,
                                                                &bulletTexture, Bullet::Owner::Boss, tier));
                                    bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                playerPosition.x, playerPosition.y,
                                                                &bulletTexture, Bullet::Owner::Boss, tier));
                                    bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                playerPosition.x - 20, playerPosition.y,
                                                                &bulletTexture, Bullet::Owner::Boss, tier));
                                    series.restart();
                                    currentShots++;
                                }else {
                                    currentShots=0;
                                    attackClock.restart();
                                }
                            }
                        }
                } else if (direction == 1) {
                    if (distance(target.getPosition(),getPosition())>=stopDistance
                        && tier == 4) {
                        if (series.getElapsedTime() >= seriesInterval){
                            if (currentShots<seriesShots) {
                                bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                            playerPosition.x + 20, playerPosition.y+20,
                                                            &bulletTexture, Bullet::Owner::Boss, tier));
                                bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                            playerPosition.x, playerPosition.y,
                                                            &bulletTexture, Bullet::Owner::Boss, tier));
                                bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                            playerPosition.x - 20, playerPosition.y-20,
                                                            &bulletTexture, Bullet::Owner::Boss, tier));
                                series.restart();
                                currentShots++;
                            }else {
                                currentShots=0;
                                attackClock.restart();
                            }
                        }
                    }
                }
            }
                break;
            case 1: {
                spawning = true;
                if (spawning && spawner.getElapsedTime() >= spawnTime){
                    enemies.emplace_back(getPosition(),2);
                    enemiesSpawned++;
                    spawner.restart();
                }
                if (enemiesSpawned == 5){
                    spawning=false;
                    enemiesSpawned=0;
                }
            }
                break;
            case 2: {
                int tpDirection = rand()%4;
                sf::Vector2f playerPosition = target.getPosition();
                switch (tpDirection) {
                    case 0:{
                        setPosition(target.getPosition().x-800,target.getPosition().y);
                        if (direction == 0) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        } else if (direction == 1) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y+20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y-20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        }
                    }
                        break;
                    case 1:{
                        setPosition(target.getPosition().x+800,target.getPosition().y);
                        if (direction == 0) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        } else if (direction == 1) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y+20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y-20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        }
                    }
                        break;
                    case 2:{
                        setPosition(target.getPosition().x,target.getPosition().y-800);
                        if (direction == 0) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        } else if (direction == 1) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y+20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y-20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        }
                    }
                        break;
                    case 3:{
                        setPosition(target.getPosition().x,target.getPosition().y+800);
                        if (direction == 0) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        } else if (direction == 1) {
                            if (distance(target.getPosition(),getPosition())>=stopDistance
                                && tier == 4) {
                                if (series.getElapsedTime() >= seriesInterval){
                                    if (currentShots<seriesShots) {
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x + 20, playerPosition.y+20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x, playerPosition.y,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        bullets.emplace_back(Bullet(this->getPosition().x, this->getPosition().y,
                                                                    playerPosition.x - 20, playerPosition.y-20,
                                                                    &bulletTexture, Bullet::Owner::Boss, tier));
                                        series.restart();
                                        currentShots++;
                                    }else {
                                        currentShots=0;
                                        attackClock.restart();
                                    }
                                }
                            }
                        }
                    }
                        break;
                }
            }
                break;
            case 3: {
                if (spawnedBombs<maxSpawnedBombs-5){
                    //spawnuje bomby
                }
            }
            break;
        }
        attackClock.restart();
    }
}
void Enemy::checkExplosionDistance(){
    if (distance(this->getPosition(),target.getPosition())<=50 && !exploding){
        alive=false;
        animating=false;
        exploding = true;
    }
}
void Enemy::update(float deltaTime,std::vector<Experience> &xp,std::vector<sf::Texture>&movementTexture){
    if (alive) {
        if (targetfound) {
            sf::Vector2f direction = target.getPosition() - getPosition();
            if (distance(target.getPosition(), getPosition()) >= stopDistance) {
                float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
                movementDirection = direction / length;
                if (movementDirection.y<movementDirection.x && movementDirection.y<0){
                    sf::IntRect textureRect(0, 0, movementTexture[0].getSize().x, movementTexture[0].getSize().y);
                    setTextureRect(textureRect);
                    setTexture(movementTexture[0]);
                    this->direction = 0;
                }else if (movementDirection.x<movementDirection.y && movementDirection.x<0){
                    sf::IntRect textureRect(0, 0, movementTexture[2].getSize().x, movementTexture[2].getSize().y);
                    setTextureRect(textureRect);
                    setTexture(movementTexture[2]);
                    this->direction = 1;
                }else if (movementDirection.x>movementDirection.y){
                    sf::IntRect textureRect(0, 0, movementTexture[3].getSize().x, movementTexture[3].getSize().y);
                    setTextureRect(textureRect);
                    setTexture(movementTexture[3]);
                    this->direction = 1;
                }else if(movementDirection.x<movementDirection.y){
                    sf::IntRect textureRect(0, 0, movementTexture[1].getSize().x, movementTexture[1].getSize().y);
                    setTextureRect(textureRect);
                    setTexture(movementTexture[1]);
                    this->direction = 0;
                }
                move(movementDirection * speed * deltaTime);
            }
        }
    } else if (animating) {
        if (animation.getElapsedTime() >= frameDuration) {
            if (currentFrame < deathAnimation.size()) {
                setTexture(deathAnimation[currentFrame]);
                setScale(7,7);
                currentFrame++;
                animation.restart();
            } else {
                xp.emplace_back(getPosition().x,getPosition().y,Experience::Utility::XP);
                if (rand()%10 == 0){
                    xp.emplace_back(getPosition().x,getPosition().y,Experience::Utility::HEALTH);
                }
                animating = false;
            }
        }
    } else if(exploding){
        if (explodeTime.getElapsedTime() >= explodeDuration){
            if (explodeFrame < explosion.size()){
                setScale(7, 7);
                setTexture(explosion[explodeFrame]);
                setTextureRect(sf::IntRect(0,0,explosion[explodeFrame].getSize().x,explosion[explodeFrame].getSize().y));
                explodeFrame++;
                explodeTime.restart();
            }else{
                exploded=true;
                exploding=false;
            }
        }
    }
}
float Enemy::distance(const sf::Vector2f& point1, const sf::Vector2f& point2) {
    return std::sqrt(std::pow(point1.x - point2.x, 2) + std::pow(point1.y - point2.y, 2));
}
bool Enemy::checkCollision(Enemy two){
    return this->getGlobalBounds().intersects(two.getGlobalBounds()) && this->tier==1 && two.tier==1;
}
bool Enemy::checkCollisionT3(Enemy two) {
    return this->getGlobalBounds().intersects(two.getGlobalBounds()) && this->tier==3 && two.tier==3;
}
void Enemy::collision(Enemy& enemy){
            float dx = (this->getGlobalBounds().left + this->getGlobalBounds().width/2) -
                    (enemy.getGlobalBounds().left + enemy.getGlobalBounds().width/2);
            float dy = (this->getGlobalBounds().top + this->getGlobalBounds().height/2) -
                    (enemy.getGlobalBounds().top + enemy.getGlobalBounds().height/2);
            float intersectX = std::abs(dx) - (this->getGlobalBounds().width/2 + enemy.getGlobalBounds().width/2);
            float intersectY = std::abs(dy) - (this->getGlobalBounds().height/2 + enemy.getGlobalBounds().height/2);
            if(intersectX < 0.0f && intersectY < 0.0f){
                if(std::abs(intersectX) > std::abs(intersectY)){
                    if (dx>0){
                        this->move(-intersectX/2,0);
                        enemy.move(intersectX/2,0);
                    }else{
                        this->move(intersectX/2,0);
                        enemy.move(-intersectX/2,0);
                    }
                }else{
                    if (dy>0){
                        this->move(0,-intersectY/2);
                        enemy.move(0,intersectY/2);
                    }else{
                        this->move(0,intersectY/2);
                        enemy.move(0,-intersectY/2);
                    }
                }
            }
}
Enemy::Enemy(sf::Vector2f location, int tier){
    switch(tier){
        case 1:
            setPosition(location);
            setScale(5,5);
            body.setPosition(location);
            body.setSize(sf::Vector2f(getGlobalBounds().width,getGlobalBounds().height));
            this->tier = tier;
            break;
        case 2:
            health = 1;
            speed = 500.0f;
            setPosition(location);
            setScale(0.5,0.5);
            body.setPosition(location);
            body.setSize(sf::Vector2f(getGlobalBounds().width,getGlobalBounds().height));
            stopDistance = 0;
            this->tier=tier;
            break;
        case 3:
            health = 5;
            speed = 150.0f;
            setPosition(location);
            setScale(4,4);
            body.setPosition(location);
            body.setSize(sf::Vector2f(getGlobalBounds().width,getGlobalBounds().height));
            stopDistance = 750;
            this->tier=tier;
            break;
        case 4:
            setTextureRect(sf::IntRect(41,34,43,82));
            bossType = rand()%4;
            health = 100 * bossCounter;
            speed = 250.0f;
            setPosition(location);
            setScale(4,4);
            setOrigin(getLocalBounds().width/2,getLocalBounds().height/2);
            body.setPosition(location);
            body.setSize(sf::Vector2f(getLocalBounds().width,getLocalBounds().height));
            stopDistance = 500;
            this->tier=tier;
            break;
    }
};
float Enemy::getDistance(){
    sf::Vector2f dist = getPosition() - target.getPosition();
    return std::sqrt(dist.x * dist.x + dist.y * dist.y);
}
