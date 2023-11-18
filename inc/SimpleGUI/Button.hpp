#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "common.hpp"
#include "SguiObject.hpp"

// SimpleGUI
namespace sgui{
    namespace _dev{
        namespace bs{ // ButtonState
            // BUTTON DEFAULT
            #define __BD_NAME "Button"
            #define __BD_POSITION sf::Vector2f(0.f, 0.f)
            #define __BD_SIZE sf::Vector2f(130, 35)
            #define __BD_COLOR sf::Color(10, 110, 240)
            #define __BD_COLOR_HOVER sf::Color(30, 130, 255)
            #define __BD_COLOR_PRESS sf::Color(10, 90, 210)
            #define __BD_TEXT_COLOR sf::Color::Black

            #define __BD_DISABLE_ALPHA_VALUE 100
            
            enum{
                None  = 0     , // 0000 0000
                Hover = 1 << 0, // 0000 0001
                Press = 1 << 1, // 0000 0010

                Click     = 1 << 4, // 0001 0000
                ClickCtrl = 1 << 5  // 0010 0000
            };
        }
    }
    class Button : public SguiObject{
        sf::String name;
        sf::Vector2f pos;
        sf::Vector2f size;

        sf::RectangleShape shape;
        sf::Color color;
        sf::Color colorHover;
        sf::Color colorPress;

        sf::Text text;
        sf::Color colorText;

        uint8_t state;

        bool enable;
        bool visible;
        bool leftButtonPress;

        void initData();
        void buildTextures();

    public:
        Button();
        Button(sf::FloatRect bounds);
        Button(sf::FloatRect bounds, sf::String name);
        ~Button();

    private:
        void centerText();
        void updateShape();
        void updateColor();

    public:
        void event(const sf::Event& event);
        void update();
        void render(sf::RenderTarget* window) const;
        
        // getters
        const sf::Vector2f& getPosition() const;
        const sf::Vector2f& getSize() const;
        bool getClick() const;
        bool getPress() const;
        bool getHover() const;
        const bool& getButtonType() const;
        const sf::Color& getColor() const;
        const sf::Color& getColorHover() const;
        const sf::Color& getColorPress() const;
        const sf::Color& getColorText() const;
        const sf::Text& getText() const;
        const bool& getEnable() const;
        const bool& getVisible() const;
        const sf::String& getName() const;

        // setters
        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);
        void setColor(const sf::Color& color);
        void setColorHover(const sf::Color& color);
        void setColorPress(const sf::Color& color);
        void setColorText(const sf::Color& color);
        void setText(const sf::Text& text);
        void setEnable(const bool& enable);
        void setVisible(const bool& visible);
        void setName(const sf::String& name);
    };
}




#endif