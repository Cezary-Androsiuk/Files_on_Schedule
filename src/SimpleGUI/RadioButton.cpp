#include "SimpleGUI/RadioButton.hpp"





/*      INITIALIZE      */
void sgui::RadioButton::initData(){
    _BITSET0(this->state, _dev::rbs::Selected);
    _BITSET0(this->state, _dev::rbs::ChangedON);
    _BITSET0(this->state, _dev::rbs::ChangedCtrl);
    _BITSET0(this->state, _dev::rbs::Hover);
    this->enable = true;
    this->visible = true;

    this->colorBorder = __RBD_COLOR_BORDER;
    this->colorBackground = __RBD_COLOR_BACKGROUND;
    this->colorHover = __RBD_COLOR_HOVER;
    this->colorChecked = __RBD_COLOR_CHECKED;
    this->colorUnchecked = __RBD_COLOR_UNCHECKED;
}


void sgui::RadioButton::buildTextures(){
    this->border.setFillColor(sf::Color::Transparent);
    this->updateShape();
    this->updateColor();
}





/*      CONSTRUCTORS      */
sgui::RadioButton::RadioButton() : RadioButton(__RBD_POSITION, __RBD_RADIUS) {}
sgui::RadioButton::RadioButton(sf::Vector2f pos, float radius) {
    this->pos = pos;
    this->radius = radius;
    this->initData();
    this->buildTextures();
}
sgui::RadioButton::~RadioButton(){
    
}





/*      PRIVATE      */
void sgui::RadioButton::updateShape(){
    float x = this->pos.x, y = this->pos.y;
    float radius = this->radius;
    this->background.setPosition(x, y);
    this->background.setRadius(radius);

    float borderSize = radius * __RBD_BORDER_RATIO;
    float borderCheckedSize = radius * __RBD_BORDER_CHECKED_RATIO;

    this->border.setRadius(radius - borderSize);
    this->border.setOutlineThickness(borderSize);
    this->border.setPosition(x + borderSize, y + borderSize);

    this->shapeChecked.setRadius(borderCheckedSize);
    this->shapeChecked.setPosition(x + radius/2, y + radius/2);
}


void sgui::RadioButton::updateColor(){
    sf::Color tmpBackColor(this->colorBackground);
    sf::Color tmpBorderColor(this->colorBorder);
    sf::Color tmpShapeColor;

    if(this->enable){
        if(_BITGET(this->state, _dev::rbs::Selected))
            tmpShapeColor = this->colorChecked;
        else{
            if(_BITGET(this->state, _dev::rbs::Hover))
                tmpShapeColor = this->colorHover;
            else 
                tmpShapeColor = this->colorUnchecked;
        }
    }
    else{
        if(_BITGET(this->state, _dev::rbs::Selected))
            tmpShapeColor = this->colorChecked;
        else
            tmpShapeColor = this->colorUnchecked;

        tmpBackColor.a = __RBD_DISABLE_ALPHA_VALUE;
        tmpBorderColor.a = __RBD_DISABLE_ALPHA_VALUE;
        tmpShapeColor.a = __RBD_DISABLE_ALPHA_VALUE;
    }

    this->background.setFillColor(tmpBackColor);
    this->border.setOutlineColor(tmpBorderColor);
    this->shapeChecked.setFillColor(tmpShapeColor);
}


bool sgui::RadioButton::contains(sf::Vector2f point) const{
    sf::Vector2f center(
        this->pos.x + this->radius,
        this->pos.y + this->radius
    );
    sf::Vector2f vector(
        center.x - point.x,
        center.y - point.y
    );
    float distance = sqrtf(powf(vector.x,2) + powf(vector.y,2));
    if(distance <= this->radius) 
        return true;
        
    return false;
}

void sgui::RadioButton::diselectGroup() const{
    for(auto& rb : this->group)
        rb->setState(false);
}





/*      PROTECTED      */
void sgui::RadioButton::setGroup(const std::vector<sgui::RadioButton *>& group){
    this->group = group;
}





/*      PUBLIC      */
void sgui::RadioButton::event(const sf::Event& event){
    if(!this->enable) return;
    if(!this->visible) return;

    if(event.type == sf::Event::MouseMoved){
        if(this->contains(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))
            _BITSET1(this->state, _dev::rbs::Hover);
        else
            _BITSET0(this->state, _dev::rbs::Hover);
    }

    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
        if(this->contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))){
            if(!_BITGET(this->state, _dev::rbs::Selected)){
                _BITSET1(this->state, _dev::rbs::Selected);
                _BITSET1(this->state, _dev::rbs::ChangedCtrl);
                this->diselectGroup();
            }
        }
    }
    this->updateShape();
    this->updateColor();
}


void sgui::RadioButton::update(){
    if(!this->enable) return;
    if(!this->visible) return;

    if(_BITGET(this->state, _dev::rbs::Selected) && _BITGET(this->state, _dev::rbs::ChangedCtrl)){
        _BITSET1(this->state, _dev::rbs::ChangedON);
        _BITSET0(this->state, _dev::rbs::ChangedCtrl);
    }
    else
        _BITSET0(this->state, _dev::rbs::ChangedON);
}


void sgui::RadioButton::render(sf::RenderTarget* window) const{
    if(!this->visible) return;

    window->draw(this->background);
    window->draw(this->border);
    window->draw(this->shapeChecked);
}





/*      GETTERS      */
const sf::Vector2f& sgui::RadioButton::getPosition() const{
    return this->pos;
}
const float& sgui::RadioButton::getRadius() const{
    return this->radius;
}
bool sgui::RadioButton::getCheckedOn() const{
    return _BITGET(this->state, _dev::rbs::ChangedON);
}
bool sgui::RadioButton::getState() const{
    return _BITGET(this->state, _dev::rbs::Selected);
}
bool sgui::RadioButton::getHover() const{
    return _BITGET(this->state, _dev::rbs::Hover);
}
const sf::Color& sgui::RadioButton::getColorBorder() const{
    return this->colorBorder;
}
const sf::Color& sgui::RadioButton::getColorBackground() const{
    return this->colorBackground;
}
const sf::Color& sgui::RadioButton::getColorHover() const{
    return this->colorHover;
}
const sf::Color& sgui::RadioButton::getColorChecked() const{
    return this->colorChecked;
}
const sf::Color& sgui::RadioButton::getColorUnchecked() const{
    return this->colorUnchecked;
}
const bool& sgui::RadioButton::getEnable() const{
    return this->enable;
}
const bool& sgui::RadioButton::getVisible() const{
    return this->visible;
}





/*      SETTERS      */
void sgui::RadioButton::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
    this->updateShape();
}
void sgui::RadioButton::setRadius(const float& radius){
    this->radius = radius;
    this->updateShape();
}
void sgui::RadioButton::setState(const bool& state){
    if(state){
        _BITSET1(this->state, _dev::rbs::Selected);
        this->diselectGroup();
    } 
    else 
        _BITSET0(this->state, _dev::rbs::Selected);
    this->updateColor();
}
void sgui::RadioButton::setColorBorder(const sf::Color& color){
    this->colorBorder = color;
    this->updateColor();
}
void sgui::RadioButton::setColorBackground(const sf::Color& color){
    this->colorBackground = color;
    this->updateColor();
}
void sgui::RadioButton::setColorHover(const sf::Color& color){
    this->colorHover = color;
    this->updateColor();
}
void sgui::RadioButton::setColorChecked(const sf::Color& color){
    this->colorChecked = color;
    this->updateColor();
}
void sgui::RadioButton::setColorUnchecked(const sf::Color& color){
    this->colorUnchecked = color;
    this->updateColor();
}
void sgui::RadioButton::setEnable(const bool& enable){
    this->enable = enable;
    this->updateColor();
}
void sgui::RadioButton::setVisible(const bool& visible){
    this->visible = visible;
}





/*      STATIC      */
void sgui::RadioButton::createGroup(const std::vector<sgui::RadioButton *>& group){
    for(auto& gi : group){
        gi->setState(false);
        std::vector<sgui::RadioButton *> singleGroup;
        for(auto& gj : group){
            if(gi != gj)
                singleGroup.push_back(gj);
        }
        gi->setGroup(singleGroup);
    }
}