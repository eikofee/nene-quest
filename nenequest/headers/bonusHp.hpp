#ifndef BONUSHP_H
#define BONUSHP_H

#include "../headers/bonus.hpp"
#include <SFML/Graphics.hpp>


class BonusHp : public Bonus
{
    public:
        static const short int ONIGIRI = 1;
        BonusHp(short int bonusType, sf::Vector2f position);
        virtual ~BonusHp();
        short int getHealedAmount();

    protected:

    private:
        short int healed_amount;
};

#endif // BONUSHP_H
