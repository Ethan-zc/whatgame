#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !LayerColor::initWithColor(Color4B(0, 0, 0, 255)) )
    {
        return false;
    }
    
	/*
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0
	*/

	auto   screenSize = Director::getInstance()->getWinSize();
	auto player = Sprite::create("player.png");
    player ->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
	this->addChild(player);

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);

	MenuItemFont * item1 = MenuItemFont::create("Start",
		CC_CALLBACK_1(HelloWorld::menuItem1Callback, this));

	/*
	MenuItemAtlasFont * item2 = MenuItemAtlasFont::create("Help",
		"weixin.png", 48, 65, ' ',
		CC_CALLBACK_1(HelloWorld::menuItem2Callback, this));
	item2->setPosition(ccp(screenSize.width / 2, screenSize.height / 2 - 10));
	this->addChild(item2);
	*/

	Menu * mn = Menu::create(item1,  NULL);
	mn->alignItemsVertically();
	this->addChild(mn);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::menuItem1Callback(Ref * pSender) {
	
	auto sc = GameStartPage::createNewScene();
	Director::getInstance()->pushScene(sc);

}

void GameStartPage::menuItemCallback(Ref * pSender) {

	auto sc = HelloWorld::createScene();
	Director::getInstance()->pushScene(sc);
}


Scene* GameStartPage::createNewScene() {
	auto scene = Scene::create();

	auto layer = GameStartPage::create();
	
	scene->addChild(layer);

	return scene;
}

bool GameStartPage::init() {
	if (!LayerColor::initWithColor(Color4B(255, 255, 255, 255)))
		return false;

	MenuItemFont::setFontName("Times New Roman");
	MenuItemFont::setFontSize(86);
    
    /*
    //another menu
	auto item1 = MenuItemFont::create("Back",
		CC_CALLBACK_1(GameStartPage::menuItemCallback, this));
    */
     //another sprite
    auto screenSize = Director::getInstance()->getVisibleSize();
    auto  qqSprite = Sprite::create("HelloWorld.png");
    
    qqSprite->setPosition(Vec2(screenSize.width / 2, screenSize.height / 2));
    qqSprite->setScale(0.3);
    this->addChild(qqSprite);
    qqSprite->setTag(12);
    
    //Menu * mn = Menu::create(item1,  NULL);
    //mn->alignItemsVertically();
    //this->addChild(mn);

    
    //create a keyboard listener to move the object.
    auto eventListener = EventListenerKeyboard::create();
    
    /*
    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        
        switch (keyCode) {
            case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            case EventKeyboard::KeyCode::KEY_A:
                event->getCurrentTarget()->setPosition(loc.x -=10, loc.y);
                break;
                
            case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            case EventKeyboard::KeyCode::KEY_D:
                event->getCurrentTarget()->setPosition(loc.x += 10, loc.y);
                break;
                
            case EventKeyboard::KeyCode::KEY_UP_ARROW:
            case EventKeyboard::KeyCode::KEY_W:
                event->getCurrentTarget()->setPosition(loc.x, loc.y += 10);
                break;
                
            case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            case EventKeyboard::KeyCode::KEY_S:
                event->getCurrentTarget()->setPosition(loc.x, loc.y -= 10);
                break;
        };
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority
    (eventListener, qqSprite);
    */
    label = cocos2d::Label::createWithSystemFont("Press the CTRL Key","Arial",32);
    label->setPosition(this->getBoundingBox().getMidX(),this->getBoundingBox().getMidY());
    //addChild(label);
    
    //here is implementation of keyboard scene from game from scratch
    Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);
    eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // If a key already exists, do nothing as it will already have a time stamp
        // Otherwise, set's the timestamp to now
        if(keys.find(keyCode) == keys.end()){
            keys[keyCode] = std::chrono::high_resolution_clock::now();
        }
    };
    eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        // remove the key.  std::map.erase() doesn't care if the key doesnt exist
        keys.erase(keyCode);
    };
    
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener,this);
    
    // Let cocos know we have an update function to be called.
    // No worries, ill cover this in more detail later on
    this->scheduleUpdate();
    return true;
}

bool GameStartPage::isKeyPressed(EventKeyboard::KeyCode code) {
    // Check if the key is currently pressed by seeing it it's in the std::map keys
    // In retrospect, keys is a terrible name for a key/value paried datatype isnt it?
    if(keys.find(code) != keys.end())
        return true;
    return false;
}

double GameStartPage::keyPressedDuration(EventKeyboard::KeyCode code) {
    if(!isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL))
        return 0;  // Not pressed, so no duration obviously
    
    // Return the amount of time that has elapsed between now and when the user
    // first started holding down the key in milliseconds
    // Obviously the start time is the value we hold in our std::map keys
    return std::chrono::duration_cast<std::chrono::milliseconds>
    (std::chrono::high_resolution_clock::now() - keys[code]).count();
}

void GameStartPage::update(float delta) {
    // Register an update function that checks to see if the CTRL key is pressed
    // and if it is displays how long, otherwise tell the user to press it
    auto sprite = this->getChildByTag(12);
    if (isKeyPressed(EventKeyboard::KeyCode::KEY_A)){
        sprite->setPositionX(sprite->getPositionX() - delta* 1000);
    }else if (isKeyPressed(EventKeyboard::KeyCode::KEY_D)){
        sprite->setPositionX(sprite->getPositionX() + delta* 1000);
    }else if(isKeyPressed(EventKeyboard::KeyCode::KEY_S)){
        sprite->setPositionY(sprite->getPositionY() - delta* 1000);
    }else if (isKeyPressed(EventKeyboard::KeyCode::KEY_W)){
        sprite->setPositionY(sprite->getPositionY() + delta* 1000);
    }
    /*
    Node::update(delta);
    
    if(isKeyPressed(EventKeyboard::KeyCode::KEY_CTRL)) {
         std::stringstream ss;
        ss << "Control key has been pressed for " <<
        keyPressedDuration(EventKeyboard::KeyCode::KEY_CTRL) << " ms";
        label->setString(ss.str().c_str());
     
    }    else {
        label->setString("Press the CTRL Key");
    }
    */
}
// Because cocos2d-x requres createScene to be static, we need to make other non-pointer members static
std::map<cocos2d::EventKeyboard::KeyCode, std::chrono::high_resolution_clock::time_point> GameStartPage::keys;
