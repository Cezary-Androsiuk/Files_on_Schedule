#include "SimpleGUI/ImageBox.hpp"





/*      INITIALIZE      */
void sgui::ImageBox::initData(){
    this->freeze = false;
    this->visible = true;
    
    if(!this->imageTexture.loadFromFile(this->imagePath))
        this->imageTexture.loadFromFile(__IBD_IMAGE);
    this->imageTextureTrim.width = this->imageTexture.getSize().x;
    this->imageTextureTrim.height = this->imageTexture.getSize().y;
    
    
    this->colorImage = __IBD_COLOR_IMAGE;
    this->colorBackground = __IBD_COLOR_BACKGROUND;
}


void sgui::ImageBox::buildTextures(){
    this->updateTextureState();
}





/*      CONSTRUCTORS      */
sgui::ImageBox::ImageBox() : ImageBox(__IBD_IMAGE, sf::FloatRect(__IBD_POSITION, __IBD_SIZE)) {}
sgui::ImageBox::ImageBox(const sf::String& imagePath) : ImageBox(imagePath, sf::FloatRect(__IBD_POSITION, __IBD_SIZE)) {}
sgui::ImageBox::ImageBox(const sf::String& imagePath, sf::FloatRect bounds) {
    this->imagePath = imagePath;
    this->pos = sf::Vector2f(bounds.left, bounds.top);
    // this->size = sf::Vector2f(bounds.width, bounds.height);
    this->initData();
    this->buildTextures();
}
sgui::ImageBox::~ImageBox(){
    
}





/*      PRIVATE      */
void sgui::ImageBox::updateTextureState(){
    sf::Vector2u psize = this->imageTexture.getSize();
    // float xscale = this->size.x / psize.x, yscale = this->size.y / psize.y;
    
    this->imageTextureTrim.width = this->imageTexture.getSize().x;
    this->imageTextureTrim.height = this->imageTexture.getSize().y;
    
    this->image.setPosition(this->pos);
    this->image.setTexture(this->imageTexture);
    this->image.setTextureRect(this->imageTextureTrim);
    this->image.setColor(this->colorImage);
    // this->image.setScale(xscale, yscale);
    
    this->background.setPosition(this->pos);
    this->background.setSize(sf::Vector2f(this->image.getGlobalBounds().width, this->image.getGlobalBounds().height));
    this->background.setFillColor(this->colorBackground);
}





/*      PUBLIC      */
void sgui::ImageBox::event(const sf::Event& event){
    /* NONE */
}


void sgui::ImageBox::update(){
    // if(this->freeze) return;
    // this->updateTextureState();
    // this->freeze = true; // if there are not any changes in setters then do not update data
}


void sgui::ImageBox::render(sf::RenderTarget* window) const{
    if(!this->visible) return;

    window->draw(this->background);
    window->draw(this->image);
}





/*      GETTERS      */
const sf::Vector2f& sgui::ImageBox::getPosition() const{
    return this->pos;
}
const sf::Vector2u sgui::ImageBox::getSize() const{
    return this->imageTexture.getSize();
}
const sf::String& sgui::ImageBox::getImagePath() const{
    return this->imagePath;
}
const sf::IntRect& sgui::ImageBox::getImageTextureTrim() const{
    return this->imageTextureTrim;
}
const sf::Color& sgui::ImageBox::getColorImage() const{
    return this->colorImage;
}
const sf::Color& sgui::ImageBox::getColorBackground() const{
    return this->colorBackground;
}
const bool& sgui::ImageBox::getVisible() const{
    return this->visible;
}





/*      SETTERS      */
void sgui::ImageBox::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
    this->updateTextureState();
}
void sgui::ImageBox::setSize(const sf::Vector2f& size){
    this->size = size;
    this->updateTextureState();
}
void sgui::ImageBox::setImagePath(const sf::String& imagePath){
    this->imagePath = imagePath;
    this->imageTexture.loadFromFile(this->imagePath);
    this->updateTextureState();
}
void sgui::ImageBox::setImageTextureTrim(const sf::IntRect& imageTextureTrim){
    this->imageTextureTrim = imageTextureTrim;
    this->updateTextureState();
}
void sgui::ImageBox::setColorImage(const sf::Color& color){
    this->colorImage = color;
    this->updateTextureState();
}
void sgui::ImageBox::setColorBackground(const sf::Color& color){
    this->colorBackground = color;
    this->updateTextureState();
}
void sgui::ImageBox::setVisible(const bool& visible){
    this->visible = visible;
    this->updateTextureState();
}