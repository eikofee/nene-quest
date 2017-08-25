#ifndef LIVING_ENTITY_HPP
#define LIVING_ENTITY_HPP


class LivingEntity {

    public:
        LivingEntity(int hp);
        bool isAlive();
        void take_damage(int amount);
    protected:
        int hp;
};

#endif // BOAR_HPP
