#ifndef IMAGEBOX_HPP
#define IMAGEBOX_HPP

#include <SFML/Graphics.hpp>

#include "SguiObject.hpp"

// SimpleGUI
namespace sgui{
    class ImageBox : public SguiObject{
        // IMAGEBOX DEFAULT
        #define __IBD_POSITION sf::Vector2f(0.f, 0.f)
        #define __IBD_SIZE sf::Vector2f(0.f, 0.f)
        #define __IBD_IMAGE sf::String("./res/images/default.png")
        #define __IBD_COLOR_IMAGE sf::Color(255, 255, 255)
        #define __IBD_COLOR_BACKGROUND sf::Color(0, 0, 0)
        
        sf::Vector2f pos;
        sf::Vector2f size;
        sf::Sprite image;
        sf::RectangleShape background;
        sf::Vector2f imageScale;

        sf::String imagePath;
        sf::Texture imageTexture;
        sf::IntRect imageTextureTrim;

        sf::Color colorImage;
        sf::Color colorBackground;

        bool freeze;
        bool visible;

        void initData();
        void buildTextures();

    public:
        ImageBox();
        ImageBox(const sf::String& imagePath);
        ImageBox(const sf::String& imagePath, sf::FloatRect bounds);
        ~ImageBox();

    private:
        void updateTextureState();

    public:
        void event(const sf::Event& event);
        void update();
        void render(sf::RenderTarget* window) const;
        
        // getters
        const sf::Vector2f& getPosition() const;
        const sf::Vector2u getSize() const;
        const sf::String& getImagePath() const;
        const sf::IntRect& getImageTextureTrim() const;
        const sf::Color& getColorImage() const;
        const sf::Color& getColorBackground() const;
        const bool& getVisible() const;

        // setters
        void setPosition(const sf::Vector2f& pos);
        void setSize(const sf::Vector2f& size);
        void setImagePath(const sf::String& imagePath);
        void setImageTextureTrim(const sf::IntRect& imageTextureTrim);
        void setColorImage(const sf::Color& color);
        void setColorBackground(const sf::Color& color);
        void setVisible(const bool& visible);
    };
}


#endif