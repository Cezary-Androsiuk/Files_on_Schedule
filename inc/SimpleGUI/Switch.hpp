#ifndef SWITCH_HPP
#define SWITCH_HPP

#include "common.hpp"
#include "SguiObject.hpp"

// SimpleGUI
namespace sgui{
    namespace _dev{
        namespace ss{ // SwitchState
            // SWITCH DEFAULT
            #define __SD_POSITION sf::Vector2f(0.f, 0.f)
            #define __SD_SIZE sf::Vector2f(43, 22)
            #define __SD_SWITCHED false
            #define __SD_BACKGROUND_COLOR_ON sf::Color(10, 90, 210)
            #define __SD_BACKGROUND_COLOR_ON_HOVER sf::Color(72, 108, 206)
            #define __SD_BACKGROUND_COLOR_OFF sf::Color(180, 180, 180)
            #define __SD_BACKGROUND_COLOR_OFF_HOVER sf::Color(152, 159, 190)
            #define __SD_SWITCH_COLOR sf::Color(255, 255, 255)
            #define __SD_SHADOW_COLOR sf::Color(100, 100, 100, 40)

            #define __SD_DISABLE_ALPHA_VALUE 100
            #define __SD_HANDLE_SIZE_RATIO 0.75f
            #define __SD_SHADOW_SIZE_RATIO 0.9f

            enum{
                None     = 0     , // 0000 0000
                Hover    = 1 << 0, // 0000 0001
                Switched = 1 << 1, // 0000 0010

                ChangedON   = 1 << 4, // 0001 0000
                ChangedOFF  = 1 << 5, // 0010 0000
                ChangedCtrl = 1 << 6  // 0100 0000
            };
        }
    }

    class Switch : public SguiObject{
        sf::Vector2f pos;
        sf::Vector2f size;
        struct Background{
            sf::RectangleShape shape;
            sf::Color colorOn;
            sf::Color colorOnHover;
            sf::Color colorOff;
            sf::Color colorOffHover;
        } background;

        struct _Switch{
            sf::RectangleShape shape;
            sf::Color color;
            sf::RectangleShape shadow;
            sf::Color shadowColor;

            struct MoveRange{
                sf::Vector2f left;
                sf::Vector2f right;
                sf::Vector2f shadowLeft;
                sf::Vector2f shadowRight;
            } moveRange;
        } _switch;

        uint8_t state;

        bool enable;
        bool visible;

        void initData();
        void buildTextures();

    public:
        Switch();
        Switch(sf::FloatRect bounds);
        Switch(sf::FloatRect bounds, bool switched);
        ~Switch();

    private:
        void updateShape();
        void updateSwitchState();
        void updateColor();

    public:
        void event(const sf::Event& event);
        void update();
        void render(sf::RenderTarget* window) const;

        // getters
        const sf::Vector2f& getPosition() const;
        const sf::Vector2f& getSize() const;
        bool getSwitchedOn() const;
        bool getSwitchedOff() const;
        bool getState() const;
        bool getHover() const;
        const sf::Color& getBackgroundColorOn() const;
        const sf::Color& getBackgroundColorOnHover() const;
        const sf::Color& getBackgroundColorOff() const;
        const sf::Color& getBackgroundColorOffHover() const;
        const sf::Color& getSwitchColor() const;
        const sf::Color& getShadowColor() const;
        const bool& getEnable() const;
        const bool& getVisible() const;

        // setters
        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);
        void setState(const bool& state);
        void setBackgroundColorOn(const sf::Color& color);
        void setBackgroundColorOnHover(const sf::Color& color);
        void setBackgroundColorOff(const sf::Color& color);
        void setBackgroundColorOffHover(const sf::Color& color);
        void setSwitchColor(const sf::Color& color);
        void setShadowColor(const sf::Color& color);
        void setEnable(const bool& enable);
        void setVisible(const bool& visible);
    };
}




#endif