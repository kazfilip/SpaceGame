#include <valarray>
#include "Player.h"
#include "Bullet.h"


void Player::attack(const std::vector<Enemy>& enemies,std::vector<Bullet> &bullets) {
    if (playerTime.getElapsedTime()>=attackInterval){
        if (targets==1) {
            std::unique_ptr<Enemy> enemyToAttack = findClosestEnemy(enemies);
            if (enemyToAttack != nullptr) {
                bullets.emplace_back(this->getPosition().x, this->getPosition().y, enemyToAttack->getPosition().x,
                                     enemyToAttack->getPosition().y, &bulletTexture,
                                     Bullet::Owner::Player);
            }
            playerTime.restart();
        }else if (targets==2){
            std::unique_ptr<Enemy> enemyToAttack = findClosestEnemy(enemies);
            std::unique_ptr<Enemy> enemyToAttack2 = nullptr;
            float closest = std::numeric_limits<float>::max();
            for(const Enemy& enemy : closestTargets){
                sf::Vector2f enemyPos = {enemy.getPosition().x, enemy.getPosition().y};
                sf::Vector2f dist = enemyPos - getPosition();
                if (closest > std::sqrt(dist.x * dist.x + dist.y * dist.y) && closest != enemyToAttack->getDistance()) {
                    closest = std::sqrt(dist.x * dist.x + dist.y * dist.y);
                    enemyToAttack2 = std::make_unique<Enemy>(enemy);
                }
            }
            if (enemyToAttack != nullptr && enemyToAttack2 != nullptr ){
                bullets.emplace_back(this->getPosition().x, this->getPosition().y, enemyToAttack->getPosition().x,
                                     enemyToAttack->getPosition().y, &bulletTexture,
                                     Bullet::Owner::Player);
                bullets.emplace_back(this->getPosition().x, this->getPosition().y, enemyToAttack2->getPosition().x,
                                     enemyToAttack2->getPosition().y, &bulletTexture,
                                     Bullet::Owner::Player);
            }
            playerTime.restart();
        }
    }
    if (rockets.getElapsedTime()>=rocketInterval && attack2Unlocked){
        for (int i = 0; i < maxRockets; ++i) {
            bullets.emplace_back(this->getPosition().x,this->getPosition().y,enemies[rand()%enemies.size()].getPosition().x,enemies[rand()%enemies.size()].getPosition().y,
                                 &rocketTexture,Bullet::Owner::PlayerRocket,0);
        }
        rockets.restart();
    }
    if (attack3Unlocked && voidAttack.getElapsedTime()>=voidInterval){
        std::unique_ptr<Enemy> enemyToAttack = findClosestEnemy(enemies);
        if (enemyToAttack != nullptr){
            bullets.emplace_back(this->getPosition().x,this->getPosition().y,enemyToAttack->getPosition().x,enemyToAttack->getPosition().y,
                                 &voidTexture,Bullet::Owner::Void);
        }
        voidAttack.restart();
    }
}
std::unique_ptr<Enemy> Player::findClosestEnemy(const std::vector<Enemy>& enemies) {
    sf::Vector2f enemyPos;
    float closest = std::numeric_limits<float>::max();;
    sf::Vector2f playerPosition = {getPosition().x, getPosition().y};
    std::unique_ptr<Enemy> enemyToAttack;
    for (const Enemy& enemy: enemies) {
        if (!enemy.targeted) {
            enemyPos = {enemy.getPosition().x, enemy.getPosition().y};
            sf::Vector2f dist = enemyPos - playerPosition;
            if (closest > std::sqrt(dist.x * dist.x + dist.y * dist.y)) {
                closest = std::sqrt(dist.x * dist.x + dist.y * dist.y);
                enemyToAttack = std::make_unique<Enemy>(enemy);
                closestTargets.emplace_back(enemy);
            }
        }
    }
    return enemyToAttack;
}


void Player::setBulletTexture(const sf::Texture& texture1){
    bulletTexture = texture1;
}

void Player::loadTextures(){
    deathAnimation.clear();
    for (int i = 1; i <= 4; ++i) {
        sf::Texture texture;
        if (texture.loadFromFile("Textures/Animations/Explosion/explosion"+std::to_string(i)+".png")){
            deathAnimation.push_back(texture);
        }
    }
}

void Player::loseHealth(int damage){
    if (healthTimer.getElapsedTime()>=sf::seconds(4)){
        immune=true;
        health-=damage;
        healthTimer.restart();
    }
}
void Player::death() {
    if (health <= 0) {
        animating = true;
        alive = false;
        if (animation.getElapsedTime() >= frameDuration) {
            if (currentFrame < deathAnimation.size()) {
                setTexture(deathAnimation[currentFrame]);
                setScale(7, 7);
                currentFrame++;
                animation.restart();
            }else {
                animating = false;
            }
        }
    }
}

bool Player::xpCollect(Experience &exp) {
    if (getGlobalBounds().intersects(exp.getGlobalBounds())){
        if (exp.type == Experience::Utility::HEALTH && health<maxHealth){
            health++;
        }else currentXp++;
        levelUp(level);
        return true;
    }
    return false;
}
void Player::collect(std::vector<Experience> &exp,float deltaTime){
    sf::Vector2f movementDirection;
    float speed = 600;
    for (auto& xp : exp){
        sf::Vector2f direction = getPosition() - xp.getPosition();
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (distance <= collectDistance){
            movementDirection = direction/distance;
            xp.move(movementDirection * speed * deltaTime);
        }
    }
}
void Player::levelUp(int level){
    if (currentXp==xpToLevel){
        switch (level) {
            case 1:
                this->level++;
                currentXp=0;
                basicDamage++;
                xpIncrease();
                break;
            case 2:
                this->level++;
                currentXp=0;
                attackInterval = sf::seconds(0.3);
                xpIncrease();
                break;
            case 3:
                this->level++;
                currentXp=0;
                attackInterval = sf::seconds(0.1);
                xpIncrease();
                break;
            case 4:
                this->level++;
                currentXp=0;
                targets++;
                maxHealth +=3;
                collectDistance+=200;
                xpIncrease();
                break;
            case 5:
                this->level++;
                currentXp=0;
                ricochet = true;
                xpIncrease();
                break;
            case 6:
                attack2Unlocked = true;
                this->level++;
                currentXp=0;
                xpIncrease();
                break;
            case 7:
                this->level++;
                rocketInterval = sf::seconds(1.2);
                currentXp=0;
                xpIncrease();
                break;
            case 8:
                this->level++;
                maxRockets = 7;
                currentXp=0;
                xpIncrease();
                break;
            case 9:
                this->level++;
                currentXp=0;
                basicDamage++;
                maxHealth +=3;
                collectDistance+=200;
                xpIncrease();
                break;
            case 10:
                this->level++;
                currentXp=0;
                attack3Unlocked = true;
                xpIncrease();
                break;
            case 11:
                this->level++;
                currentXp=0;
                voidInterval = sf::seconds(4);
                xpIncrease();
                break;
            case 12:
                this->level++;
                currentXp=0;
                xpIncrease();
                break;
            case 13:
                this->level++;
                currentXp=0;
                voidInterval = sf::seconds(3.5);
                xpIncrease();
                break;
            case 14:
                this->level++;
                currentXp=0;
                maxLevel=true;
                maxHealth +=3;
                collectDistance+=200;
                xpIncrease();
                break;
        }
    }
}


void Player::xpIncrease(){
    xpToLevel+=10;
}

void Player::setRocketTexture(const sf::Texture &texture1) {
    rocketTexture = texture1;
}
void Player::setVoidTexture(const sf::Texture &texture1){
    voidTexture = texture1;
}
