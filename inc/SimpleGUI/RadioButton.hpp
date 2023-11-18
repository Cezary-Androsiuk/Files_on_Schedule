#ifndef RADIOBUTTON_HPP
#define RADIOBUTTON_HPP

#include <vector>
#include <cmath>

#include "common.hpp"
#include "SguiObject.hpp"

// SimpleGUI
namespace sgui{
    namespace _dev{
        namespace rbs{ // RadioButtonState
            // RADIOBUTTON DEFAULT
            #define __RBD_POSITION sf::Vector2f(0.f, 0.f)
            #define __RBD_RADIUS 15.f
            #define __RBD_COLOR_BORDER sf::Color(10, 90, 210)
            #define __RBD_COLOR_BACKGROUND sf::Color(255, 255, 255, 0)
            #define __RBD_COLOR_HOVER sf::Color(10, 90, 210, 80)
            #define __RBD_COLOR_CHECKED sf::Color(10, 90, 210)
            #define __RBD_COLOR_UNCHECKED sf::Color::Transparent

            #define __RBD_DISABLE_ALPHA_VALUE 100
            #define __RBD_BORDER_RATIO 0.20f
            #define __RBD_BORDER_CHECKED_RATIO 0.50f

            enum{
                None     = 0     , // 0000 0000
                Hover    = 1 << 0, // 0000 0001
                Selected = 1 << 1, // 0000 0010

                ChangedON   = 1 << 4, // 0001 0000
                ChangedCtrl = 1 << 5  // 0010 0000
            };
        }
    }
    class RadioButton : public SguiObject{
        
        sf::Vector2f pos;
        float radius;
        sf::CircleShape border;
        sf::Color colorBorder;
        sf::CircleShape background;
        sf::Color colorBackground;

        sf::CircleShape shapeChecked;
        sf::Color colorHover;
        sf::Color colorChecked;
        sf::Color colorUnchecked;

        std::vector<sgui::RadioButton *> group;

        uint8_t state;

        bool enable;
        bool visible;

        void initData();
        void buildTextures();

    public:
        RadioButton();
        RadioButton(sf::Vector2f pos, float radius);
        ~RadioButton();

    private:
        void updateShape();
        void updateColor();

        bool contains(sf::Vector2f point) const;
        void diselectGroup() const; // const because does not change THIS object

    protected:
        void setGroup(const std::vector<sgui::RadioButton *>& group);

    public:
        void event(const sf::Event& event);
        void update();
        void render(sf::RenderTarget* window) const;
        
        // getters
        const sf::Vector2f& getPosition() const;
        const float& getRadius() const;
        bool getCheckedOn() const;
        bool getState() const;
        bool getHover() const;
        const sf::Color& getColorBorder() const;
        const sf::Color& getColorBackground() const;
        const sf::Color& getColorHover() const;
        const sf::Color& getColorChecked() const;
        const sf::Color& getColorUnchecked() const;
        const bool& getEnable() const;
        const bool& getVisible() const;

        // setters
        void setPosition(const sf::Vector2f& pos);
        void setRadius(const float& radius);
        void setState(const bool& state);
        void setColorBorder(const sf::Color& color);
        void setColorBackground(const sf::Color& color);
        void setColorHover(const sf::Color& color);
        void setColorChecked(const sf::Color& color);
        void setColorUnchecked(const sf::Color& color);
        void setEnable(const bool& enable);
        void setVisible(const bool& visible);

        // static
        static void createGroup(const std::vector<sgui::RadioButton *>& group); // to create group that will contain up to one selected RadioButton
    };
}


#endif