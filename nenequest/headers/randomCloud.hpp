#ifndef RANDOMCLOUD_HPP_INCLUDED
#define RANDOMCLOUD_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <list>
#include <stdlib.h>
#include <time.h>

class RandomCloud : public sf::Drawable, sf::Transformable {
	private:
		static const int MAX_WIDTH = 200;
		static const int MAX_HEIGHT = 100;
		static const int BORDER_SIZE_MIN = 30;
		static const int BORDER_SIZE_MAX = 45;
		static const int BORDER_NUMBER = 12;
		static const int BORDER_VARI = 10;
		static const int LIFETIME = 10;
		sf::RectangleShape* cloudBody;
		std::list<sf::CircleShape*> cloudBorder;
		sf::Clock clock;
		bool alive = true;

	public:
		RandomCloud();
		~RandomCloud();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
			target.draw(*(this->cloudBody));
			for (sf::CircleShape* var : this->cloudBorder) {
				target.draw(*var);
			}
		}

		virtual void setPosition(float x, float y) {
			this->setPosition(sf::Vector2f(x, y));
		}

		virtual void setPosition(sf::Vector2f v) {
			this->cloudBody->setPosition(v);
			for (sf::CircleShape* var : this->cloudBorder) {
				var->setPosition(v);
			}
		}

		void generateBorder();
		void update();
		bool isAlive();
		void translate(float x, float y);
};

#endif