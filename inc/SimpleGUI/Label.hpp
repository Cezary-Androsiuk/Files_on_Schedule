#ifndef LABEL_HPP
#define LABEL_HPP

#include "common.hpp"
#include "SguiObject.hpp"

// SimpleGUI
namespace sgui{
    namespace _dev{
        namespace ls{ // LabelState
            // LABEL DEFAULT
            #define __LD_POSITION sf::Vector2f(0.f, 0.f)
            #define __LD_CHARACTER_SIZE sf::Uint32(32)
            #define __LD_FONT_PATH _DEFAULT_TEXT_FONT_PATH
            #define __LD_STRING sf::String("Label")
            #define __LD_COLOR sf::Color::White
            #define __LD_VISIBLE true

            #define __LD_DISABLE_ALPHA_VALUE 100
        }
    }
    class Label : public SguiObject{
        sf::Vector2f pos;

        sf::Uint32 characterSize;
        sf::Font font;
        sf::String string;
        sf::Text text;

        sf::Color color;

        bool visible;

        void initData();
        void buildTextures();

    public:
        Label();
        Label(sf::Vector2f position, sf::Text text);
        ~Label();

    private:
        void updateShape();
        void updateColor();

    public:
        void event(const sf::Event& event);
        void update();
        void render(sf::RenderTarget* window) const;
        
        // getters
        const sf::Vector2f& getPosition() const;
        const sf::Uint32& getCharacterSize() const;
        const sf::Font& getFont() const;
        const sf::String& getString() const;
        sf::Text& getText();
        const sf::Color& getColor() const;
        const bool& getVisible() const;

        // setters
        void setPosition(const sf::Vector2f& pos);
        void setCharacterSize(const sf::Uint32& characterSize);
        void setFont(const sf::Font& font);
        void setString(const sf::String& string);
        void setText(const sf::Text& text);
        void setColor(const sf::Color& color);
        void setVisible(const bool& visible);
    };
}




#endif