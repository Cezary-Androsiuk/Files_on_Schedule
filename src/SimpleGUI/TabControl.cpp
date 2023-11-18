#include "SimpleGUI/TabControl.hpp"




/*      INITIALIZE      */
void sgui::TabControl::initData(){
    this->colorTabButton = __TCD_COLOR_TAB_BUTTON;
    this->colorTabButtonHover = __TCD_COLOR_TAB_BUTTON_HOVER;
    this->colorTabButtonPress = __TCD_COLOR_TAB_BUTTON_PRESS;
    this->colorBackground = __TCD_COLOR_BACKGROUND;
    this->tabButtonSize = __TCD_TAB_BUTTON_SIZE;
    this->tabButtonsOuter = __TCD_TAB_BUTTON_OUTER;

    this->fontSize = __TCD_TAB_BUTTON_TEXT_SIZE;
    this->fontLoaded = false;

    this->enable = true;
    this->visible = true;
}


void sgui::TabControl::buildTextures(){

}





/*      CONSTRUCTORS      */
sgui::TabControl::TabControl() : TabControl(sf::FloatRect(__TCD_POSITION, __TCD_SIZE), __TCD_TAB_BUTTON_NAME) {}
sgui::TabControl::TabControl(sf::FloatRect bounds, std::string tabName){
    this->pos = bounds.getPosition();
    this->size = bounds.getSize();
    this->initData();
    this->createTab(tabName);
    this->currentTab = tabName;
    this->updateColors();
    this->updateShapes();
    this->updatePosition();
    this->buildTextures();
}
sgui::TabControl::~TabControl(){
    for(auto& [key, gb] : this->tabs)
        delete gb;
    for(auto& [key, b] : this->tabButtons)
        delete b;
}





/*      PRIVATE      */
void sgui::TabControl::createTab(std::string tabName){
    // this->tabNames.push_back(tabName);
    sgui::GroupBox* gb = new sgui::GroupBox(sf::FloatRect(this->pos, this->size));
    gb->setColorBackground(this->colorBackground);
    this->tabs.insert(std::pair<std::string, sgui::GroupBox*>(
        tabName, gb
    ));
    this->createTabButton(tabName);
}


void sgui::TabControl::createTabButton(std::string tabName){
    sgui::Button* b = new sgui::Button();
    b->setColor(this->colorTabButton);
    b->setColorHover(this->colorTabButtonHover);
    b->setColorPress(this->colorTabButtonPress);

    if(!this->fontLoaded)
        this->font.loadFromFile(__TCD_TAB_BUTTON_TEXT_FONT_PATH);

    b->setText(sf::Text(tabName, this->font, this->fontSize));

    this->tabButtons.insert(std::pair<std::string, sgui::Button*>(tabName, b));
}


void sgui::TabControl::updateShapes(){
    for(auto& [key, gb] : this->tabs){
        gb->setSize((this->tabButtonsOuter ? this->size : sf::Vector2f(this->size.x, this->size.y - this->tabButtonSize.y)));
    }
    for(auto& [key, b] : this->tabButtons){
        if(b->getVisible()){
            b->setSize(this->tabButtonSize);
        }
    }
    
}


void sgui::TabControl::updateColors(){
    for(auto& [key, gb] : this->tabs){
        gb->setColorBackground(this->colorBackground);
    }
    for(auto& [key, b] : this->tabButtons){
        if(key == this->currentTab){
            b->setColor(this->colorTabButtonPress);
            b->setColorHover(this->colorTabButtonPress);
            b->setColorPress(this->colorTabButtonPress);
        }
        else{
            b->setColor(this->colorTabButton);
            b->setColorHover(this->colorTabButtonHover);
            b->setColorPress(this->colorTabButtonPress);
        }
    }
}


void sgui::TabControl::updatePosition(){
    for(auto& [key, gb] : this->tabs){
        gb->setPosition((this->tabButtonsOuter ? this->pos : sf::Vector2f(this->pos.x, this->pos.y + this->tabButtonSize.y)));
    }
    int i=0;
    for(auto& [key, b] : this->tabButtons){
        if(b->getVisible()){
            b->setPosition((
                this->tabButtonsOuter ? 
                sf::Vector2f(this->pos.x + i * this->tabButtonSize.x, this->pos.y - this->tabButtonSize.y) : 
                sf::Vector2f(this->pos.x + i * this->tabButtonSize.x, this->pos.y)
            ));
            i++;
        }
    }
}





/*      PUBLIC      */
void sgui::TabControl::event(const sf::Event& event){
    if(!this->enable) return;
    if(!this->visible) return;

    //* //////////// TMP 
    if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num1)
        this->setCurrentTab(this->getTabs()[0]);
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num2)
        this->setCurrentTab(this->getTabs()[1]);
    else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Num3)
        this->setCurrentTab(this->getTabs()[2]);
    //* //////////// TMP 

    for(auto& [key, b] : this->tabButtons)
        b->event(event);
    this->tabs.at(this->currentTab)->event(event);

}


void sgui::TabControl::update(){
    if(!this->enable) return;
    if(!this->visible) return;

    for(auto& [key, b] : this->tabButtons){
        b->update();
        if(b->getClick() && key != this->currentTab){
            this->currentTab = key;
            this->update();
            return;
        }
    }
    this->tabs.at(this->currentTab)->update();
    
    this->updateShapes();
    this->updateColors();
    this->updatePosition();

}


void sgui::TabControl::render(sf::RenderTarget* window) const{
    if(!this->visible) return;
    
    this->tabs.at(this->currentTab)->render(window);
    for(auto& [key, b] : this->tabButtons)
        b->render(window);
}





/*      GETTERS      */
const sf::Vector2f& sgui::TabControl::getPosition() const{
    return this->pos;
}
const bool& sgui::TabControl::getTabButtonsOuterDisplay() const{
    return this->tabButtonsOuter;
}
// const sf::Vector2f& sgui::TabControl::getSize() const{
//     return this->size;
// }
// const sf::Color& sgui::TabControl::getColorTab() const{
//     return this->colorTab;
// }
// const sf::Color& sgui::TabControl::getColorTabHover() const{
//     return this->colorTabHover;
// }
// const sf::Color& sgui::TabControl::getColorTabChecked() const{
//     return this->colorTabChecked;
// }
const sf::Color& sgui::TabControl::getColorBackground() const{
    return this->colorBackground;
}
// const sf::Vector2f& sgui::TabControl::getTabButtonSize() const{
//     return this->tabButtonSize;
// }
const std::string& sgui::TabControl::getCurrentTab() const{
    return this->currentTab;
}
// const bool& sgui::TabControl::getTabEnable(std::string tabName) const{
//     return this->tabEnable.at(tabName);
// }
// const bool& sgui::TabControl::getTabVisible(std::string tabName) const{
//     return this->tabVisible.at(tabName);
// }
// const bool& sgui::TabControl::getEnable() const{
//     return this->enable;
// }
// const bool& sgui::TabControl::getVisible() const{
//     return this->visible;
// }





/*      SETTERS      */
void sgui::TabControl::setPosition(const sf::Vector2f& pos){
    this->pos = pos;
    this->updatePosition();
}
void sgui::TabControl::getTabButtonsOuterDisplay(const bool& display){
    this->tabButtonsOuter = display;
    this->updatePosition();
    this->updateShapes();
}
// void sgui::TabControl::setSize(const sf::Vector2f& size){
//     this->size = size;
//     this->updateShapes();
//     this->updatePosition();
// }
// void sgui::TabControl::setColorTab(const sf::Color& color){
//     this->colorTab = color;
//     this->updateColors();
// }
// void sgui::TabControl::setColorTabHover(const sf::Color& color){
//     this->colorTabHover = color;
//     this->updateColors();
// }
// void sgui::TabControl::setColorTabChecked(const sf::Color& color){
//     this->colorTabChecked = color;
//     this->updateColors();
// }
void sgui::TabControl::setColorBackground(const sf::Color& color){
    this->colorBackground = color;
    
    this->updateColors();
}
// void sgui::TabControl::setTabButtonSize(const sf::Vector2f& size){
//     this->tabButtonSize = size;
//     this->updateShapes();
//     this->updatePosition();
// }
bool sgui::TabControl::setCurrentTab(const std::string& tabName){
    if(this->tabs.find(tabName) != this->tabs.end()){
        this->currentTab = tabName;
        this->updateColors();
        this->updateShapes();
        this->updatePosition();
        return true;
    }
    else{
        return false;
    }
}
// void sgui::TabControl::setTabEnable(std::string tabName, const bool& enable){
//     this->tabEnable.at(tabName) = enable;
//     this->updateColors();
// }
// void sgui::TabControl::setTabVisible(std::string tabName, const bool& visible){
//     this->tabVisible.at(tabName) = visible;
//     this->updateColors();
//     this->updateShapes();
//     this->updatePosition();
// }
// void sgui::TabControl::setEnable(const bool& enable){
//     this->enable = enable;
//     this->updateColors();
// }
// void sgui::TabControl::setVisible(const bool& visible){
//     this->visible = visible;
//     this->updateColors();
// }
void sgui::TabControl::setFont(sf::Font& font){
    this->font = font;
    this->fontLoaded = true;
}





/*      OTHER      */
bool sgui::TabControl::addTab(std::string tabName){
    // check if tab already exist
    for(const auto& [key, gb] : this->tabs)
        if(key == tabName)
            return false;
    
    this->createTab(tabName);
    this->updateColors();
    this->updateShapes();
    this->updatePosition();
    return true;
}


std::vector<std::string> sgui::TabControl::getTabs() const{
    std::vector<std::string> keys;
    for(const auto& [key, gb] : this->tabs)
        keys.push_back(key);
    return keys;
}


std::vector<sgui::SguiObject*>& sgui::TabControl::getAllObjects(std::string tabName){
    return this->tabs.at(tabName)->getAllObjects();
}


bool sgui::TabControl::addObject(std::string tabName, sgui::SguiObject* object){
    this->updateShapes();
    this->updatePosition();
    for(const auto& [key, gb] : this->tabs){
        if(key == tabName){
            gb->addObject(object);
            return true;
        }
    }
    return false;
}