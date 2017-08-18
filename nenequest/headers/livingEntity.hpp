#ifndef LIVING_ENTITY_HPP
#define LIVING_ENTITY_HPP


class LivingEntity {

    public:
        LivingEntity(int life);
        bool isAlive();
        virtual void take_damage(int dmg) {
            this->hp -= dmg;
        }
        int getHp();

    private:
        int hp;


};

#endif // BOAR_HPP
