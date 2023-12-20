#ifndef ENNEMY_H
#define ENNEMY_H

#include <SFML/Graphics.hpp>

#include "entity.hpp"

enum EnemyType { Enemy_Dragon, Enemy_Boar };

class Enemy : public Entity {
   public:
    Enemy(int hp);
    virtual ~Enemy();
    short int getAttackDamage();
    void update(float elapsedTime);
    EnemyType getEnemyType();
    virtual bool isDying();  // Called for dying animation (blinking or dragon's death)
    virtual EntityType getEntityType();
    virtual void stun();

   protected:
    sf::Clock clock;
    short int animation_state = 0;
    short int attack_damage = 0;
    EnemyType enemy_type;
    static int const DRAGON_HP = 20;
    static int const BOAR_HP = 3;
    int hp;

   private:
};

#endif  // ENNEMY_H
