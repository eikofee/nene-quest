#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>


class Entity : public sf::Drawable
{
	public:
	    static int const DEPTH_DIFF = 130; //Maximal depth difference so that 2 entities can interact
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states = sf::RenderStates::Default) const;
		virtual void setPosition(int x, int y);
		sf::Vector2f getPosition();
		sf::Vector2f getSpriteSize();
		sf::RectangleShape getHitbox();
        virtual bool detectHit(Entity* entity);
        virtual float getDepth();
        virtual float getDrawDepth();


	protected:
		sf::RectangleShape hitbox;
		sf::Sprite sprite;
		sf::Texture texture;

		void updateHitboxSize();
		void updateHitboxPosition();

		void updateSpritePosition();


	private:
};

#endif // ENTITY_H
