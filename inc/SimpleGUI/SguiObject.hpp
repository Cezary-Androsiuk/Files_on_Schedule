#ifndef SGUIOBJECT_HPP
#define SGUIOBJECT_HPP

#include <SFML/Graphics.hpp>

namespace sgui{
    class SguiObject{
    public:
        virtual ~SguiObject();
        virtual void event(const sf::Event& event) = 0;
        virtual void update() = 0;
        virtual void render(sf::RenderTarget* window) const = 0;

        // getters
        virtual const sf::Vector2f& getPosition() const = 0;

        // setters
        virtual void setPosition(const sf::Vector2f& pos) = 0;
    };
}


#endif