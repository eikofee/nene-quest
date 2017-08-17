#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable
{
	public:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
		void setPosition(int x, int y);
		sf::RectangleShape getHitbox();
        bool detectHit(Entity entity);

	protected:
		sf::RectangleShape hitbox;
		sf::Sprite sprite;
		sf::Texture texture;

	private:
};

#endif // ENTITY_H
