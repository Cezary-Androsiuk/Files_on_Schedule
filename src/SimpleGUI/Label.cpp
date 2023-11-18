#include "SimpleGUI/Label.hpp"





/*      INITIALIZE      */
void sgui::Label::initData(){
    this->color = __LD_COLOR;
    this->visible = __LD_VISIBLE;
}


void sgui::Label::buildTextures(){
    this->updateShape();
    this->updateColor();
}





/*      CONSTRUCTORS      */
sgui::Label::Label() : Label(__LD_POSITION, sf::Text(__LD_STRING, sf::Font(), __LD_CHARACTER_SIZE)) {}
sgui::Label::Label(sf::Vector2f position, sf::Text text){
    this->pos = position;
    this->string = text.getString();
    this->font = *text.getFont();
    this->characterSize = text.getCharacterSize();
    this->text = text;
    this->initData();
    this->buildTextures();
}
sgui::Label::~Label(){
}





/*      PRIVATE      */
void sgui::Label::updateShape(){
    this->text.setPosition(this->pos);
    this->text.setCharacterSize(this->characterSize);
    this->text.setString(this->string);
    this->text.setFont(this->font);
}


void sgui::Label::updateColor(){
    this->text.setFillColor(this->color);
}





/*      PUBLIC      */
void sgui::Label::event(const sf::Event& event){
}


void sgui::Label::update(){
}


void sgui::Label::render(sf::RenderTarget* window) const{
    if(!this->visible) return;
    
    window->draw(this->text);
}





/*      GETTERS      */
const sf::Vector2f& sgui::Label::getPosition() const{
    return this->pos;
}
const sf::Uint32& sgui::Label::getCharacterSize() const{
    return this->characterSize;
}
const sf::Font& sgui::Label::getFont() const{
    return this->font;
}
const sf::String& sgui::Label::getString() const{
    return this->string;
}
sf::Text& sgui::Label::getText(){
    return this->text;
}
const sf::Color& sgui::Label::getColor() const{
    return this->color;
}
const bool& sgui::Label::getVisible() const{
    return this->visible;
}





/*      SETTERS      */
void sgui::Label::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
    this->updateShape();
}
void sgui::Label::setCharacterSize(const sf::Uint32& characterSize){
    this->characterSize = characterSize;
    this->updateShape();
}
void sgui::Label::setFont(const sf::Font& font){
    this->font = font;
    this->updateShape();
}
void sgui::Label::setString(const sf::String& string){
    this->string = string;
    this->updateShape();
}
void sgui::Label::setText(const sf::Text& text){
    this->text = text;
    this->string = text.getString();
    this->font = *text.getFont();
    this->characterSize = text.getCharacterSize();
    this->updateShape();
    this->updateColor();
}
void sgui::Label::setColor(const sf::Color& color){
    this->color = color;
    this->updateColor();
}
void sgui::Label::setVisible(const bool& visible){
    this->visible = visible;
}

