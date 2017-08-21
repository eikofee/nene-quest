#ifndef BACKGROUND_HPP_INCLUDED
#define BACKGROUND_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include "randomCloud.hpp"
#include "randomMountain.hpp"
#include <list>

class Background : public sf::Drawable, sf::Transformable {
    private:
        sf::RectangleShape sky;
        sf::RectangleShape ground;
		sf::Vector2u v;

		//cloud stuff
		static const int CLOUD_SPAWN_INTERVAL = 5;
		static const int CLOUD_SPAWN_INTERVAL_RANDOM = 2;
		static const int MOUNTAIN_SPAWN_INTERVAL = 2;
		static const int MOUNTAIN_SPAWN_INTERVAL_RANDOM = 1;
		static const int CLOUD_SPAWN_Y_TOP = 0;
		static const int CLOUD_SPAWN_Y_BOTTOM = 200;
		static const int MOUNTAIN_VAR_Y_OFFSET = 30;
		std::vector<RandomCloud*> clouds;
		std::vector<RandomMountain*> mountains;
		float nextCloud = 0;
		float nextMountain = 0;
		sf::Clock cloudClock;
		sf::Clock mountainClock;


    public:
        Background(sf::Vector2u v);

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const {
            target.draw(this->sky);
			for (auto rc : this->clouds)
				target.draw(*rc);

			for (auto rm : this->mountains)
				target.draw(*rm);

            target.draw(this->ground);
        }

        virtual void setPosition(float x, float y) {
            this->sky.setPosition(x, y);
            this->ground.setPosition(x, y);
        }
        float getSkyHeight();

		void update();
		void createClouds();
		void createMountains();
};

#endif
