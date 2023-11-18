#include "SimpleGUI/GroupBox.hpp"




/*      INITIALIZE      */
void sgui::GroupBox::initData(){
    this->enable = true;
    this->visible = true;

    this->colorBackground = __GBD_COLOR_BACKGROUND;
}


void sgui::GroupBox::buildTextures(){
    this->updateTextureState();
}





/*      CONSTRUCTORS      */
sgui::GroupBox::GroupBox() : GroupBox(sf::FloatRect(__GBD_POSITION, __GBD_POSITION)){}
sgui::GroupBox::GroupBox(sf::FloatRect bounds){
    this->pos = sf::Vector2f(bounds.left, bounds.top);
    this->size = sf::Vector2f(bounds.width, bounds.height);
    this->initData();
    this->buildTextures();
}
sgui::GroupBox::~GroupBox(){
    for(const auto& o : this->objects)
        delete o;
}





/*      PRIVATE      */
void sgui::GroupBox::updateTextureState(){
    float xdiff = this->pos.x - this->background.getGlobalBounds().left;
    float ydiff = this->pos.y - this->background.getGlobalBounds().top;
    for(auto& o : this->objects){
        sf::Vector2f objPos(o->getPosition());
        o->setPosition(sf::Vector2f(objPos.x + xdiff, objPos.y + ydiff));
    }
    this->background.setPosition(this->pos.x, this->pos.y);

    this->background.setSize(sf::Vector2f(this->size.x, this->size.y));
        
    this->background.setFillColor(this->colorBackground);
}





/*      PUBLIC      */
void sgui::GroupBox::event(const sf::Event& event){
    if(!this->enable) return;
    if(!this->visible) return;

    for(auto& o : this->objects)
        o->event(event);
}


void sgui::GroupBox::update(){
    if(!this->enable) return;
    if(!this->visible) return;

    this->updateTextureState();
    for(auto& o : this->objects)
        o->update();
}


void sgui::GroupBox::render(sf::RenderTarget* window) const{
    if(!this->visible) return;

    window->draw(this->background);
    for(const auto& o : this->objects)
        o->render(window);
}





/*      GETTERS      */
const sf::Vector2f& sgui::GroupBox::getPosition() const{
    return this->pos;
}
const sf::Vector2f& sgui::GroupBox::getSize() const{
    return this->size;
}
const sf::Color& sgui::GroupBox::getColorBackground() const{
    return this->colorBackground;
}
const bool& sgui::GroupBox::getEnable() const{
    return this->enable;
}
const bool& sgui::GroupBox::getVisible() const{
    return this->visible;
}





/*      SETTERS      */
void sgui::GroupBox::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
    this->updateTextureState();
}
void sgui::GroupBox::setSize(const sf::Vector2f& size){
    this->size = size;
    this->updateTextureState();
}
void sgui::GroupBox::setColorBackground(const sf::Color& color){
    this->colorBackground = color;
    this->updateTextureState();
}
void sgui::GroupBox::setEnable(const bool& enable){
    this->enable = enable;
    this->updateTextureState();
}
void sgui::GroupBox::setVisible(const bool& visible){
    this->visible = visible;
    this->updateTextureState();
}





/*      OTHER      */
std::vector<sgui::SguiObject*>& sgui::GroupBox::getAllObjects(){
    return this->objects;
}
void sgui::GroupBox::addObject(sgui::SguiObject* object){
    sf::Vector2f objPos = object->getPosition();
    object->setPosition(sf::Vector2f(objPos.x + this->pos.x, objPos.y + this->pos.y));
    this->objects.push_back(object);
}