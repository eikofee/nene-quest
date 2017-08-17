#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable
{
	public:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
		void setPosition(int x, int y);
		sf::RectangleShape getHitbox();
        void move(float elapsedTime);
		void move(sf::Vector2f g_speed, float elapsedTime);
		void setSpeed(sf::Vector2f g_speed);
		sf::Vector2f getSpeed();


	protected:
		sf::RectangleShape hitbox;
		bool detectHit(Entity entity);
		sf::Vector2f speed;
		sf::Sprite sprite;
		sf::Texture texture;

	private:
};

#endif // ENTITY_H
