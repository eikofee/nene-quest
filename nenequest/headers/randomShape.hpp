#ifndef RANDOMSHAPE_HPP_INCLUDED
#define RANDOMSHAPE_HPP_INCLUDED

class RandomShape : public sf::Drawable, sf::Transformable {
   public:
    virtual void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const = 0;
    virtual void update() = 0;
    virtual bool isAlive() = 0;
    virtual void translate(float x, float y) = 0;
};
#endif