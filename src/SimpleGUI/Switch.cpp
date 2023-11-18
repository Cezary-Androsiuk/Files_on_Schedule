#include "SimpleGUI/Switch.hpp"





/*      INITIALIZE      */
void sgui::Switch::initData(){
    this->enable = true;
    this->visible = true;
    _BITSET0(this->state, _dev::ss::Hover);
    _BITSET0(this->state, _dev::ss::ChangedON);
    _BITSET0(this->state, _dev::ss::ChangedOFF);
    _BITSET0(this->state, _dev::ss::ChangedCtrl); // if false starts with "switched_off" pulse

    this->background.colorOn = __SD_BACKGROUND_COLOR_ON;
    this->background.colorOnHover = __SD_BACKGROUND_COLOR_ON_HOVER;
    this->background.colorOff = __SD_BACKGROUND_COLOR_OFF;
    this->background.colorOffHover = __SD_BACKGROUND_COLOR_OFF_HOVER;
    this->_switch.color = __SD_SWITCH_COLOR;
    this->_switch.shadowColor = __SD_SHADOW_COLOR;
}


void sgui::Switch::buildTextures(){
    this->updateShape();
    this->updateSwitchState();
    this->updateColor();
}





/*      CONSTRUCTORS      */
sgui::Switch::Switch() : Switch(sf::FloatRect(__SD_POSITION, __SD_SIZE), __SD_SWITCHED) {}
sgui::Switch::Switch(sf::FloatRect bounds) : Switch(bounds, __SD_SWITCHED) {}
sgui::Switch::Switch(sf::FloatRect bounds, bool switched){
    this->pos = bounds.getPosition();
    this->size = bounds.getSize();
    this->state = (switched ? _dev::ss::Switched : _dev::ss::None);

    this->initData();
    this->buildTextures();
}
sgui::Switch::~Switch(){
}





/*      PRIVATE      */
void sgui::Switch::updateShape(){
    // COMPUTING
    float x = this->pos.x, y = this->pos.y;
    float width = this->size.x, height = this->size.y;
    float switchHeight = height * __SD_HANDLE_SIZE_RATIO;
    float switchShadowHeight = height * __SD_SHADOW_SIZE_RATIO;
    float diffHeight = (switchShadowHeight - switchHeight)/2;
    float borderSize = (height - switchHeight)/2;

    this->_switch.moveRange.left = sf::Vector2f(
        x + borderSize,
        y + borderSize
    );
    this->_switch.moveRange.right = sf::Vector2f(
        (x + width - switchHeight - borderSize),
        y + borderSize 
    );

    this->_switch.moveRange.shadowLeft = sf::Vector2f(
        x + borderSize - diffHeight,
        y + borderSize - diffHeight
    );
    this->_switch.moveRange.shadowRight = sf::Vector2f(
        (x + width - switchHeight - borderSize) - diffHeight,
        y + borderSize - diffHeight
    );

    // SET SIZE AND POSITION
    this->background.shape.setSize(sf::Vector2f(width, height));
    this->background.shape.setPosition(sf::Vector2f(x, y));

    this->_switch.shape.setSize(sf::Vector2f(switchHeight, switchHeight));
    this->_switch.shape.setFillColor(this->_switch.color);

    this->_switch.shadow.setSize(sf::Vector2f(switchShadowHeight, switchShadowHeight));
    this->_switch.shadow.setFillColor(this->_switch.shadowColor);
}


void sgui::Switch::updateSwitchState(){
    if(_BITGET(this->state, _dev::ss::Switched)){
        this->_switch.shape.setPosition(this->_switch.moveRange.right);
        this->_switch.shadow.setPosition(this->_switch.moveRange.shadowRight);
    }
    else{
        this->_switch.shape.setPosition(this->_switch.moveRange.left);
        this->_switch.shadow.setPosition(this->_switch.moveRange.shadowLeft);
    }
}


void sgui::Switch::updateColor(){
    sf::Color tmpBackgroundColor;
    sf::Color tmpSwitchColor(this->_switch.color);
    sf::Color tmpShadowColor(this->_switch.shadowColor);

    if(this->enable){
        if(_BITGET(this->state, _dev::ss::Hover)){
            if(_BITGET(this->state, _dev::ss::Switched))
                tmpBackgroundColor = this->background.colorOnHover;
            else
                tmpBackgroundColor = this->background.colorOffHover;
        }
        else{
            if(_BITGET(this->state, _dev::ss::Switched))
                tmpBackgroundColor = this->background.colorOn;
            else
                tmpBackgroundColor = this->background.colorOff;
        }
    }
    else{
        if(_BITGET(this->state, _dev::ss::Switched))
            tmpBackgroundColor = this->background.colorOn;
        else
            tmpBackgroundColor = this->background.colorOff;

        tmpBackgroundColor.a = __SD_DISABLE_ALPHA_VALUE;
        tmpSwitchColor.a = __SD_DISABLE_ALPHA_VALUE;
        tmpShadowColor.a = __SD_DISABLE_ALPHA_VALUE;
    }

    this->background.shape.setFillColor(tmpBackgroundColor);
    this->_switch.shape.setFillColor(tmpSwitchColor);
    this->_switch.shadow.setFillColor(tmpShadowColor);
}





/*      PUBLIC      */
void sgui::Switch::event(const sf::Event& event){
    if(!this->enable) return;
    if(!this->visible) return;

    if(event.type == sf::Event::MouseMoved){
        if(sf::FloatRect(this->pos, this->size).contains(event.mouseMove.x, event.mouseMove.y))
            _BITSET1(this->state, _dev::ss::Hover);
        else
            _BITSET0(this->state, _dev::ss::Hover);
    }

    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
        if(sf::FloatRect(this->pos, this->size).contains(event.mouseButton.x, event.mouseButton.y)){
            if(_BITGET(this->state, _dev::ss::Switched)){
                _BITSET0(this->state, _dev::ss::Switched);
                _BITSET1(this->state, _dev::ss::ChangedCtrl);
            }
            else{
                _BITSET1(this->state, _dev::ss::Switched);
                _BITSET1(this->state, _dev::ss::ChangedCtrl);
            }
        }
    }
    this->updateShape();
    this->updateSwitchState();
    this->updateColor();
}


void sgui::Switch::update(){
    if(!this->enable) return;
    if(!this->visible) return;

    // update Switched ON to send just single frame info
    if(_BITGET(this->state, _dev::ss::Switched) && _BITGET(this->state, _dev::ss::ChangedCtrl)){
        _BITSET1(this->state, _dev::ss::ChangedON);
        _BITSET0(this->state, _dev::ss::ChangedCtrl);
    }
    else
        _BITSET0(this->state, _dev::ss::ChangedON);

    // update Switched OFF to send just single frame info
    if(!_BITGET(this->state, _dev::ss::Switched) && _BITGET(this->state, _dev::ss::ChangedCtrl)){
        _BITSET1(this->state, _dev::ss::ChangedOFF);
        _BITSET0(this->state, _dev::ss::ChangedCtrl);
    }
    else
        _BITSET0(this->state, _dev::ss::ChangedOFF);
}


void sgui::Switch::render(sf::RenderTarget* window) const{
    if(!this->visible) return;
    
    window->draw(this->background.shape);
    window->draw(this->_switch.shadow);
    window->draw(this->_switch.shape);
}





/*      GETTERS      */
const sf::Vector2f& sgui::Switch::getPosition() const{
    return this->pos;
}
const sf::Vector2f& sgui::Switch::getSize() const{
    return this->size;
}
bool sgui::Switch::getSwitchedOn() const{
    return _BITGET(this->state, _dev::ss::ChangedON);
}
bool sgui::Switch::getSwitchedOff() const{
    return _BITGET(this->state, _dev::ss::ChangedOFF);
}
bool sgui::Switch::getState() const{
    return _BITGET(this->state, _dev::ss::Switched);
}
bool sgui::Switch::getHover() const{
    return _BITGET(this->state, _dev::ss::Hover);
}
const sf::Color& sgui::Switch::getBackgroundColorOn() const{
    return this->background.colorOn;
}
const sf::Color& sgui::Switch::getBackgroundColorOnHover() const{
    return this->background.colorOnHover;
}
const sf::Color& sgui::Switch::getBackgroundColorOff() const{
    return this->background.colorOff;
}
const sf::Color& sgui::Switch::getBackgroundColorOffHover() const{
    return this->background.colorOffHover;
}
const sf::Color& sgui::Switch::getSwitchColor() const{
    return this->_switch.color;
}
const sf::Color& sgui::Switch::getShadowColor() const{
    return this->_switch.shadowColor;
}
const bool& sgui::Switch::getEnable() const{
    return this->enable;
}
const bool& sgui::Switch::getVisible() const{
    return this->visible;
}





/*      SETTERS      */
void sgui::Switch::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
    this->updateShape();
    this->updateSwitchState();
}
void sgui::Switch::setSize(const sf::Vector2f& size){
    this->size = size;
    this->updateShape();
    this->updateSwitchState();
}
void sgui::Switch::setState(const bool& state){
    if(state) _BITSET1(this->state, _dev::ss::Switched);
    else      _BITSET0(this->state, _dev::ss::Switched);
    this->updateSwitchState();
    this->updateColor();
}
void sgui::Switch::setBackgroundColorOn(const sf::Color& color){
    this->background.colorOn = color;
    this->updateColor();
}
void sgui::Switch::setBackgroundColorOnHover(const sf::Color& color){
    this->background.colorOnHover = color;
    this->updateColor();
}
void sgui::Switch::setBackgroundColorOff(const sf::Color& color){
    this->background.colorOff = color;
    this->updateColor();
}
void sgui::Switch::setBackgroundColorOffHover(const sf::Color& color){
    this->background.colorOffHover = color;
    this->updateColor();
}
void sgui::Switch::setSwitchColor(const sf::Color& color){
    this->_switch.color = color;
    this->updateColor();
}
void sgui::Switch::setShadowColor(const sf::Color& color){
    this->_switch.shadowColor = color;
    this->updateColor();
}
void sgui::Switch::setEnable(const bool& enable){
    this->enable = enable;
    this->updateColor();
}
void sgui::Switch::setVisible(const bool& visible){
    this->visible = visible;
}

