#ifndef CHECKBOX_HPP
#define CHECKBOX_HPP

#include "common.hpp"
#include "SguiObject.hpp"

// SimpleGUI
namespace sgui{
    namespace _dev{
        namespace cbs{ // CheckBoxState
            // CHECKBOX DEFAULT
            #define __CBD_POSITION sf::Vector2f(0.f, 0.f)
            #define __CBD_SIZE 30.f
            #define __CBD_CHECKED false
            #define __CBD_COLOR_BORDER sf::Color(10, 90, 210)
            #define __CBD_COLOR_BACKGROUND sf::Color(0, 0, 0, 0)
            #define __CBD_COLOR_HOVER_UNCHECKED sf::Color(10, 90, 210, 80)
            #define __CBD_COLOR_HOVER_CHECKED sf::Color(10, 90, 210, 220)
            #define __CBD_COLOR_CHECKED sf::Color(10, 90, 210)
            #define __CBD_COLOR_UNCHECKED sf::Color::Transparent

            #define __CBD_DISABLE_ALPHA_PCT 100.f/255.f
            #define __CBD_BORDER_RATIO 0.20f
            #define __CBD_BORDER_CHECKED_RATIO 0.50f
            
            enum{
                None    = 0     , // 0000 0000
                Hover   = 1 << 0, // 0000 0001
                Checked = 1 << 1, // 0000 0010

                ChangedON   = 1 << 4, // 0001 0000
                ChangedOFF  = 1 << 5, // 0010 0000
                ChangedCtrl = 1 << 6  // 0100 0000
            };
        }
    }

    class CheckBox : public SguiObject{
        
        sf::Vector2f pos;
        float size;
        sf::RectangleShape border;
        sf::Color colorBorder;
        sf::RectangleShape background;
        sf::Color colorBackground;

        sf::RectangleShape shapeChecked;
        sf::Color colorChecked;
        sf::Color colorUnchecked;
        sf::Color colorHoverChecked;
        sf::Color colorHoverUnchecked;

        uint8_t state;

        bool enable;
        bool visible;

        void initData();
        void buildTextures();

    public:
        CheckBox();
        CheckBox(sf::Vector2f pos, float size);
        CheckBox(sf::Vector2f pos, float size, bool checked);
        ~CheckBox();

    private:
        void updateShape();
        void updateColor();

    public:
        void event(const sf::Event& event);
        void update();
        void render(sf::RenderTarget* window) const;

        // getters
        const sf::Vector2f& getPosition() const;
        const float& getSize() const;
        bool getCheckedOn() const;
        bool getCheckedOff() const;
        bool getCheckedState() const;
        bool getHoverState() const;
        const sf::Color& getColorBorder() const;
        const sf::Color& getColorBackground() const;
        const sf::Color& getColorChecked() const;
        const sf::Color& getColorUnchecked() const;
        const sf::Color& getColorHoverChecked() const;
        const sf::Color& getColorHoverUnchecked() const;
        const bool& getEnable() const;
        const bool& getVisible() const;

        // setters
        void setPosition(const sf::Vector2f& pos);
        void setSize(const float& size);
        void setCheckedState(const bool& size);
        void setColorBorder(const sf::Color& color);
        void setColorBackground(const sf::Color& color);
        void setColorChecked(const sf::Color& color);
        void setColorUnchecked(const sf::Color& color);
        void setColorHoverChecked(const sf::Color& color);
        void setColorHoverUnchecked(const sf::Color& color);
        void setEnable(const bool& enable);
        void setVisible(const bool& visible);
    };
}




#endif