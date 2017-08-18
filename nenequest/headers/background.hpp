#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "randomCloud.hpp"
#include <list>

class Background : public sf::Drawable, sf::Transformable {
    private:
        sf::RectangleShape sky;
        sf::RectangleShape ground;
		sf::Vector2u v;

		//cloud stuff
		static const int CLOUD_SPAWN_INTERVAL = 5;
		static const int CLOUD_SPAWN_INTERVAL_RANDOM = 2;
		static const int CLOUD_SPAWN_Y_TOP = 0;
		static const int CLOUD_SPAWN_Y_BOTTOM = 200;
		std::vector<RandomCloud*> clouds;
		float nextCloud;
		sf::Clock clock;

    public:
        Background(sf::Vector2u v);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(this->sky);
            target.draw(this->ground);
			for (auto rc : this->clouds) {
				target.draw(*rc);
			}
        }

        virtual void setPosition(float x, float y) {
            this->sky.setPosition(x, y);
            this->ground.setPosition(x, y);
        }

		void update();
		void createClouds();
};

#endif
