#ifndef RANDOMSHAPE_HPP_INCLUDED
#define RANDOMSHAPE_HPP_INCLUDED

class RandomShape : public sf::Drawable, sf::Transformable {
   public:
    void draw(sf::RenderTarget &target,
                      sf::RenderStates states) const override = 0;
    virtual void update() = 0;
    virtual bool isAlive() = 0;
    virtual void translate(float x, float y) = 0;
};
#endif
