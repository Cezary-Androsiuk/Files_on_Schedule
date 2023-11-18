#ifndef GROUPBOX_HPP
#define GROUPBOX_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "SguiObject.hpp"

namespace sgui{
    class GroupBox : public SguiObject{
        // GROUPBOX DEFAULT
        #define __GBD_POSITION sf::Vector2f(0.f, 0.f)
        #define __GBD_SIZE sf::Vector2f(1280.f, 720.f)
        #define __GBD_COLOR_BACKGROUND sf::Color::Transparent

        #define __GBD_DISABLE_ALPHA_PCT 100.f/255.f
        
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::RectangleShape background;

        sf::Color colorBackground;
        
        //* Elements in GroupBox
        std::vector<sgui::SguiObject*> objects;
        //*/

        bool enable;
        bool visible;

        void initData();
        void buildTextures();

    public:
        GroupBox();
        GroupBox(sf::FloatRect bounds);
        ~GroupBox();

    private:
        void updateTextureState();

    public:
        void event(const sf::Event& event);
        void update();
        void render(sf::RenderTarget* window) const;
        
        // getters
        const sf::Vector2f& getPosition() const;
        const sf::Vector2f& getSize() const;
        const sf::Color& getColorBackground() const;
        const bool& getEnable() const;
        const bool& getVisible() const;

        // setters
        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);
        void setColorBackground(const sf::Color& color);
        void setEnable(const bool& enable);
        void setVisible(const bool& visible);

        // other
        // to remove/modify/getResponse from a single object 
        std::vector<sgui::SguiObject*>& getAllObjects();
        // to add object call for example: groupBox->addObject(new sgui::Button());
        // objects position is relative to groupBox and they will be deleted while deleting groupBox
        void addObject(sgui::SguiObject* object);
    };
}

#endif