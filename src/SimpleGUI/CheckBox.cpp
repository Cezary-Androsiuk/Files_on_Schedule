#include "SimpleGUI/CheckBox.hpp"




/*      INITIALIZE      */
void sgui::CheckBox::initData(){
    this->enable = true;
    this->visible = true;
    _BITSET0(this->state, _dev::cbs::Hover);
    _BITSET0(this->state, _dev::cbs::ChangedON);
    _BITSET0(this->state, _dev::cbs::ChangedOFF);
    _BITSET0(this->state, _dev::cbs::ChangedCtrl); // if false starts with "checked_off" pulse

    this->colorBorder = __CBD_COLOR_BORDER;
    this->colorBackground = __CBD_COLOR_BACKGROUND;
    this->colorChecked = __CBD_COLOR_CHECKED;
    this->colorUnchecked = __CBD_COLOR_UNCHECKED;
    this->colorHoverChecked = __CBD_COLOR_HOVER_CHECKED;
    this->colorHoverUnchecked = __CBD_COLOR_HOVER_UNCHECKED;
}


void sgui::CheckBox::buildTextures(){
    this->border.setFillColor(sf::Color::Transparent);
    this->updateShape();
    this->updateColor();
}





/*      CONSTRUCTORS      */
sgui::CheckBox::CheckBox() : CheckBox(__CBD_POSITION, __CBD_SIZE, __CBD_CHECKED){}
sgui::CheckBox::CheckBox(sf::Vector2f pos, float size) : CheckBox(pos, size, __CBD_CHECKED){}
sgui::CheckBox::CheckBox(sf::Vector2f pos, float size, bool checked){
    this->pos = pos;
    this->size = size;
    this->state = (checked ? _dev::cbs::Checked : _dev::cbs::None);
    this->initData();
    this->buildTextures();
}
sgui::CheckBox::~CheckBox(){
    
}





/*      PRIVATE      */
void sgui::CheckBox::updateShape(){
    float x = this->pos.x, y = this->pos.y;
    float borderSize = this->size * __CBD_BORDER_RATIO;
    float checkedSize = this->size * __CBD_BORDER_CHECKED_RATIO;
    float checkedSizeOffset = this->size - checkedSize;

    this->background.setSize(sf::Vector2f(this->size, this->size));
    this->background.setPosition(x, y);

    this->border.setSize(sf::Vector2f(this->size - borderSize, this->size - borderSize));
    this->border.setPosition(x + borderSize/2, y + borderSize/2);
    this->border.setOutlineThickness(borderSize/2);

    this->shapeChecked.setSize(sf::Vector2f(checkedSize, checkedSize));
    this->shapeChecked.setPosition(x + checkedSizeOffset/2, y + checkedSizeOffset/2);
}


void sgui::CheckBox::updateColor(){
    sf::Color tmpColorBorder = this->colorBorder;
    sf::Color tmpColorBackground = this->colorBackground;
    sf::Color tmpColorCheck;

    if(this->enable){
        if(_BITGET(this->state, _dev::cbs::Hover)){
            if(_BITGET(this->state, _dev::cbs::Checked))
                tmpColorCheck = this->colorHoverChecked;
            else
                tmpColorCheck = this->colorHoverUnchecked;
        }
        else{
            if(_BITGET(this->state, _dev::cbs::Checked))
                tmpColorCheck = this->colorChecked;
            else
                tmpColorCheck = this->colorUnchecked;
        }
    }
    else{
        if(_BITGET(this->state, _dev::cbs::Checked))
            tmpColorCheck = this->colorChecked;
        else
            tmpColorCheck = this->colorUnchecked;
        
        tmpColorBorder.a = tmpColorBorder.a * __CBD_DISABLE_ALPHA_PCT;
        tmpColorBackground.a = tmpColorBackground.a * __CBD_DISABLE_ALPHA_PCT;
        tmpColorCheck.a = tmpColorCheck.a * __CBD_DISABLE_ALPHA_PCT;
    }

    this->border.setOutlineColor(tmpColorBorder);
    this->background.setFillColor(tmpColorBackground);
    this->shapeChecked.setFillColor(tmpColorCheck);
}





/*      PUBLIC      */
void sgui::CheckBox::event(const sf::Event& event){
    if(!this->enable) return;
    if(!this->visible) return;

    if(event.type == sf::Event::MouseMoved){
        if(sf::FloatRect(this->pos, sf::Vector2f(this->size, this->size)).contains(event.mouseMove.x, event.mouseMove.y))
            _BITSET1(this->state, _dev::cbs::Hover);
        else
            _BITSET0(this->state, _dev::cbs::Hover);
    }

    if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
        if(sf::FloatRect(this->pos, sf::Vector2f(this->size, this->size)).contains(event.mouseButton.x, event.mouseButton.y)){
            if(_BITGET(this->state, _dev::cbs::Checked))
                _BITSET0(this->state, _dev::cbs::Checked);
            else
                _BITSET1(this->state, _dev::cbs::Checked);
            _BITSET1(this->state, _dev::cbs::ChangedCtrl);
        }
    }

    this->updateColor();
}


void sgui::CheckBox::update(){
    if(!this->enable) return;
    if(!this->visible) return;

    if(_BITGET(this->state,_dev::cbs::Checked) && _BITGET(this->state,_dev::cbs::ChangedCtrl)){
        _BITSET1(this->state, _dev::cbs::ChangedON);
        _BITSET0(this->state, _dev::cbs::ChangedCtrl);
    }
    else
        _BITSET0(this->state, _dev::cbs::ChangedON);

    if(_BITGET(this->state,_dev::cbs::Checked) && _BITGET(this->state,_dev::cbs::ChangedCtrl)){
        _BITSET1(this->state, _dev::cbs::ChangedOFF);
        _BITSET0(this->state, _dev::cbs::ChangedCtrl);
    }
    else
        _BITSET0(this->state, _dev::cbs::ChangedOFF);
}


void sgui::CheckBox::render(sf::RenderTarget* window) const{
    if(!this->visible) return;

    window->draw(this->background);
    window->draw(this->border);
    window->draw(this->shapeChecked);
}





/*      GETTERS      */
const sf::Vector2f& sgui::CheckBox::getPosition() const{
    return this->pos;
}
const float& sgui::CheckBox::getSize() const{
    return this->size;
}
bool sgui::CheckBox::getCheckedOn() const{
    return _BITGET(this->state, _dev::cbs::ChangedON);
}
bool sgui::CheckBox::getCheckedOff() const{
    return _BITGET(this->state, _dev::cbs::ChangedOFF);
}
bool sgui::CheckBox::getCheckedState() const{
    return _BITGET(this->state, _dev::cbs::Checked);
}
bool sgui::CheckBox::getHoverState() const{
    return _BITGET(this->state, _dev::cbs::Hover);
}
const sf::Color& sgui::CheckBox::getColorBorder() const{
    return this->colorBorder;
}
const sf::Color& sgui::CheckBox::getColorBackground() const{
    return this->colorBackground;
}
const sf::Color& sgui::CheckBox::getColorChecked() const{
    return this->colorChecked;
}
const sf::Color& sgui::CheckBox::getColorUnchecked() const{
    return this->colorUnchecked;
}
const sf::Color& sgui::CheckBox::getColorHoverChecked() const{
    return this->colorHoverChecked;
}
const sf::Color& sgui::CheckBox::getColorHoverUnchecked() const{
    return this->colorHoverUnchecked;
}
const bool& sgui::CheckBox::getEnable() const{
    return this->enable;
}
const bool& sgui::CheckBox::getVisible() const{
    return this->visible;
}





/*      SETTERS      */
void sgui::CheckBox::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
}
void sgui::CheckBox::setSize(const float& size){
    this->size = size;
}
void sgui::CheckBox::setCheckedState(const bool& state){
    if(state) _BITSET1(this->state, _dev::cbs::Checked);
    else      _BITSET0(this->state, _dev::cbs::Checked);
    this->updateColor();
}
void sgui::CheckBox::setColorBorder(const sf::Color& color){
    this->colorBorder = color;
    this->updateColor();
}
void sgui::CheckBox::setColorBackground(const sf::Color& color){
    this->colorBackground = color;
    this->updateColor();
}
void sgui::CheckBox::setColorChecked(const sf::Color& color){
    this->colorChecked = color;
    this->updateColor();
}
void sgui::CheckBox::setColorUnchecked(const sf::Color& color){
    this->colorUnchecked = color;
    this->updateColor();
}
void sgui::CheckBox::setColorHoverChecked(const sf::Color& color){
    this->colorHoverChecked = color;
    this->updateColor();
}
void sgui::CheckBox::setColorHoverUnchecked(const sf::Color& color){
    this->colorHoverUnchecked = color;
    this->updateColor();
}
void sgui::CheckBox::setEnable(const bool& enable){
    this->enable = enable;
    this->updateColor();
}
void sgui::CheckBox::setVisible(const bool& visible){
    this->visible = visible;
}