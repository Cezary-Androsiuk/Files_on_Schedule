#include "SimpleGUI/Button.hpp"





/*      INITIALIZE      */
void sgui::Button::initData(){
    _BITSET0(this->state, _dev::bs::Hover);
    _BITSET0(this->state, _dev::bs::Press);
    _BITSET0(this->state, _dev::bs::Click);
    _BITSET1(this->state, _dev::bs::ClickCtrl);
    this->enable = true;
    this->visible = true;

    this->color = __BD_COLOR;
    this->colorHover = __BD_COLOR_HOVER;
    this->colorPress = __BD_COLOR_PRESS;
    this->colorText = __BD_TEXT_COLOR;
}


void sgui::Button::buildTextures(){
    this->updateShape();
    this->updateColor();
}





/*      CONSTRUCTORS      */
sgui::Button::Button() : Button(sf::FloatRect(__BD_POSITION, __BD_SIZE)) {}
sgui::Button::Button(sf::FloatRect bounds) : Button(sf::FloatRect(__BD_POSITION, __BD_SIZE), sf::String(__BD_NAME)){}
sgui::Button::Button(sf::FloatRect bounds, sf::String name){
    this->leftButtonPress = true;
    this->name = name;
    this->pos = sf::Vector2f(bounds.left, bounds.top);
    this->size = sf::Vector2f(bounds.width, bounds.height);
    this->initData();
    this->buildTextures();
}
sgui::Button::~Button(){

}





/*      PRIVATE      */
void sgui::Button::centerText(){
    sf::FloatRect sfr = this->shape.getGlobalBounds();
    sf::FloatRect tfr = this->text.getGlobalBounds();
    this->text.setPosition(sf::Vector2f(
        sfr.left + (sfr.width - tfr.width)/2,
        sfr.top + (sfr.height - this->text.getCharacterSize())/2
    ));
    tfr = this->text.getGlobalBounds();
    sf::Vector2f error(tfr.left - this->text.getPosition().x, tfr.top - this->text.getPosition().y);
    sf::Vector2f tpos(
        std::roundf(this->text.getPosition().x - error.x),
        std::roundf(this->text.getPosition().y - error.y)
    );
    this->text.setPosition(tpos);

}


void sgui::Button::updateShape(){
    // SET SIZE AND POSITION
    this->shape.setSize(size);
    this->shape.setPosition(pos);
    this->centerText();
}


void sgui::Button::updateColor(){
    if(this->enable){
        this->text.setFillColor(this->colorText);

        if(_BITGET(this->state, _dev::bs::Press))
            this->shape.setFillColor(this->colorPress);
        else if(_BITGET(this->state, _dev::bs::Hover))
            this->shape.setFillColor(this->colorHover);
        else
            this->shape.setFillColor(this->color);
    }
    else{
        // set standard color to avoid keeping disable while button is pressed
        this->shape.setFillColor(sf::Color(
            this->color.r,
            this->color.g,
            this->color.b,
            __BD_DISABLE_ALPHA_VALUE
        ));
        
        this->text.setFillColor(sf::Color(
            this->colorText.r,
            this->colorText.g,
            this->colorText.b,
            __BD_DISABLE_ALPHA_VALUE
        ));
    }
}





/*      PUBLIC      */
void sgui::Button::event(const sf::Event& event){
    if(!this->enable) return;
    if(!this->visible) return;

    if(event.type == sf::Event::MouseMoved){
        if(sf::FloatRect(this->pos, this->size).contains(event.mouseMove.x, event.mouseMove.y))
            _BITSET1(this->state, _dev::bs::Hover);
        else
            _BITSET0(this->state, _dev::bs::Hover);
    }


    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
        if(sf::FloatRect(this->pos, this->size).contains(event.mouseButton.x, event.mouseButton.y)){
            _BITSET1(this->state, _dev::bs::Press);
        this->leftButtonPress = true;
        }
    }
    if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right){
        if(sf::FloatRect(this->pos, this->size).contains(event.mouseButton.x, event.mouseButton.y)){
            _BITSET1(this->state, _dev::bs::Press);
        this->leftButtonPress = false;
        }
    }
    else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
        _BITSET0(this->state, _dev::bs::Press);
        _BITSET0(this->state, _dev::bs::Click);
        _BITSET1(this->state, _dev::bs::ClickCtrl);
        this->leftButtonPress = true;
    }
    else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right){
        _BITSET0(this->state, _dev::bs::Press);
        _BITSET0(this->state, _dev::bs::Click);
        _BITSET1(this->state, _dev::bs::ClickCtrl);
        this->leftButtonPress = false;
    }
}


void sgui::Button::update(){
    if(!this->enable) return;
    if(!this->visible) return;

    if(_BITGET(this->state, _dev::bs::Press) && _BITGET(this->state, _dev::bs::ClickCtrl)){
        _BITSET1(this->state, _dev::bs::Click);
        _BITSET0(this->state, _dev::bs::ClickCtrl);
    }
    else
        _BITSET0(this->state, _dev::bs::Click);

    this->updateShape();
    this->updateColor();
}


void sgui::Button::render(sf::RenderTarget* window) const{
    if(!this->visible) return;

    window->draw(this->shape);
    window->draw(this->text);
}





/*      GETTERS      */
const sf::Vector2f& sgui::Button::getPosition() const{
    return this->pos;
}
const sf::Vector2f& sgui::Button::getSize() const{
    return this->size;
}
bool sgui::Button::getClick() const{
    return _BITGET(this->state, _dev::bs::Click);
}
bool sgui::Button::getPress() const{
    return _BITGET(this->state, _dev::bs::Press);
}
bool sgui::Button::getHover() const{
    return _BITGET(this->state, _dev::bs::Hover);
}
const bool& sgui::Button::getButtonType() const{
    return this->leftButtonPress;
}
const sf::Color& sgui::Button::getColor() const{
    return this->color;
}
const sf::Color& sgui::Button::getColorHover() const{
    return this->colorHover;
}
const sf::Color& sgui::Button::getColorPress() const{
    return this->colorPress;
}
const sf::Color& sgui::Button::getColorText() const{
    return this->colorText;
}
const sf::Text& sgui::Button::getText() const{
    return this->text;
}
const bool& sgui::Button::getEnable() const{
    return this->enable;
}
const bool& sgui::Button::getVisible() const{
    return this->visible;
}
const sf::String& sgui::Button::getName() const{
    return this->name;
}





/*      SETTERS      */
void sgui::Button::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
    this->updateShape();
}
void sgui::Button::setSize(const sf::Vector2f& size){
    this->size = size;
    this->updateShape();
}
void sgui::Button::setColor(const sf::Color& color){
    this->color = color;
    this->updateColor();
}
void sgui::Button::setColorHover(const sf::Color& color){
    this->colorHover = color;
    this->updateColor();
}
void sgui::Button::setColorPress(const sf::Color& color){
    this->colorPress = color;
    this->updateColor();
}
void sgui::Button::setColorText(const sf::Color& color){
    this->colorText = color;
    this->updateColor();
}
void sgui::Button::setText(const sf::Text& text){
    this->text = text;
    this->centerText();
}
void sgui::Button::setEnable(const bool& enable){
    this->enable = enable;
    this->updateColor();
}
void sgui::Button::setVisible(const bool& visible){
    this->visible = visible;
}
void sgui::Button::setName(const sf::String& name){
    this->name = name;
}