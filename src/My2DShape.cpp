#include<iostream>
#include<vector>
#include"My2DShape.h"
#include"Window.h"
#include"Utils.h"

using crustgames::My2DShape;
using crustgames::Bullet;
using crustgames::Person;
using crustgames::Ball;
using crustgames::Utils;

Person::Person() {
    if (!texture.loadFromFile("asset/sample_character_04.png")) {
        std::cout << "load sample_character_01 error" << std::endl;
    }
    else {
        //切割帧 64/4=16 96/3=32
        int frameWidth = texture.getSize().x/4;
        int frameHeight = texture.getSize().y/3;
        //LEFT DOWN TOP RIGHT
        std::cout << "person testure x=" << texture.getSize().x << " y= " << texture.getSize().y << std::endl;
        for (int x = 0; x < texture.getSize().x; x += frameWidth) {
            std::vector<sf::IntRect> vec;
            for (int y = 0; y < texture.getSize().y; y += frameHeight) {
                sf::IntRect rect(x, y, frameWidth, frameHeight);
                vec.push_back(rect);
            }
            frames.push_back(vec);
        }
        sprite.setTexture(texture);
    }
    currentFrame = DOWN;
    currentFrameIndex = 0;
}

void Person::Render() {
    if (clock.getElapsedTime().asMilliseconds() > 100) // 控制帧率
    {
        currentFrameIndex++;
        if (currentFrameIndex >= frames[currentFrame].size())
            currentFrameIndex = 0;
        clock.restart();
    }
    sprite.setTextureRect(frames[currentFrame][currentFrameIndex]);
    sprite.setPosition(sf::Vector2f(x, y));
    sprite.setScale(sf::Vector2f(2, 2));
    Window::Instance().Get().draw(sprite);
}

void Person::Left() {
    moveTarget = LEFT;
    currentFrame = LEFT;
    Next();
}

void Person::Right() {
    moveTarget = RIGHT;
    currentFrame = RIGHT;
    Next();
}

void Person::Top() {
    moveTarget = TOP;
    currentFrame = TOP;
    Next();
}

void Person::Down() {
    moveTarget = DOWN;
    currentFrame = DOWN;
    Next();
}

void Person::Next() {
    switch (moveTarget)
    {
    case TOP:y-=5; break;
    case RIGHT:x+=5; break;
    case DOWN:y+=5; break;
    case LEFT:x-=5; break;
    default:
        break;
    }
    TouchTest();
}

void Person::TouchTest() {
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x > Window::Instance().Get().getSize().x) {
        x = Window::Instance().Get().getSize().x;
    }
    if (y > Window::Instance().Get().getSize().y) {
        y = Window::Instance().Get().getSize().y;
    }
}

My2DShape::My2DShape():Object2D() {
    if (!music.openFromFile("asset/shoot.ogg"))
    {
        std::cout << "log shoot error" << std::endl;
    }
    if (!bgm.openFromFile("asset/Path_to_Lake_Land.ogg"))
    {
        std::cout << "log bgm error" << std::endl;
    }
    else {
        bgm.setLoop(true);
        bgm.play();
    }
}

My2DShape::~My2DShape() {
    std::cout << "垃圾回收" << std::endl;
}

void My2DShape::WindowInitBefore() {
    if (!font.loadFromFile("asset/waltographUI.ttf"))
    {
        std::cout << "load ttf error" << std::endl;
        return;
    }
    text.setFont(font);
    text.setCharacterSize(16);
    text.setFillColor(sf::Color::Red);
    text.setStyle(sf::Text::Bold | sf::Text::Underlined);
    text.setPosition(0, 0);
}

void My2DShape::WindowInitAfter() {

}

void My2DShape::EventNotifyBefore() {
    
}

void My2DShape::EventNotifyAfter() {
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        music.setPlayingOffset(sf::Time());
        music.play();
        int mouse_x = sf::Mouse::getPosition(Window::Instance().Get()).x;
        int mouse_y = sf::Mouse::getPosition(Window::Instance().Get()).y;
        Bullet bullet;
        bullet.mouse_x = mouse_x;
        bullet.mouse_y = mouse_y;
        bullet.start_x = person.x+10;
        bullet.start_y = person.y+20;
        bullet.x = bullet.start_x;
        bullet.y = bullet.start_y;
        bullet.radius = 5;
        //std::cout << "person_x " << person.x << " person_y" << person.y << " mouse_x " << mouse_x << " mouse_y" << mouse_y << std::endl;
        bullets.push_back(bullet);
    }
}

void My2DShape::Render() {
    {//添加一个球
        if (autoBallX < Window::Instance().Get().getSize().x) {
            autoBallX += 100;
        }
        else {
            autoBallX = 0;
            autoBallY += 8;
        }
        if (autoBallY >= Window::Instance().Get().getSize().y) {
            autoBallX = 0;
            autoBallY = 0;
            balls.clear();
        }
        Ball ball{};
        ball.x = autoBallX;
        ball.y = autoBallY;
        ball.r = (autoBallX % 255 * autoBallY % 255) % 255;
        ball.g = (autoBallX % 255 + autoBallY % 255) % 255;
        ball.b = (autoBallX % 255 + autoBallY * 2) % 255;
        ball.radius = 5;
        //std::cout << "(" << autoBallX << "," << autoBallY << ")" <<" radius="<<ball.radius<< std::endl;
        balls.push_back(ball);
    }

    //球与子弹碰撞检测,然后进行球渲染
    for (auto iter = balls.begin(); iter != balls.end(); ) {
        //遍历所有子弹
        bool boom=false;//标记是否碰撞
        //遍历子弹
        for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();) {
            boom=iter->CollisionAABB(bulletIter->x - bulletIter->radius, bulletIter->y - bulletIter->radius, bulletIter->radius*2, bulletIter->radius*2);
            if (boom) {
                //删除子弹
                bullets.erase(bulletIter);
                //删除球
                iter = balls.erase(iter);
                break;
            }
            ++bulletIter;
        }
        if (boom) {
            continue;
        }
        //画球
        iter->Render();
        ++iter;
    }

    //fps
    fps.Show();
    text.setString(sf::String(std::string("FPS: ") + std::to_string(fps.Get())));
    Window::Instance().Get().draw(text);

    //子弹渲染
    for (auto iter = bullets.begin(); iter != bullets.end();) {
        bool bRet=iter->Render();
        if (!bRet) {
            iter=bullets.erase(iter);
        }
        else {
            ++iter;
        }
    }
    //人物渲染
    person.Render();
}

void My2DShape::MouseButtonPressed(sf::Event& event) {
    if (event.mouseButton.button == sf::Mouse::Left)
    {

    }
}

void My2DShape::KeyPressed(sf::Event& event) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        person.Top();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        person.Left();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        person.Down();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        person.Right();
    }
}

Bullet::Bullet()
{

}

void Bullet::Next() {
    double v = 5;
    double length = sqrt((mouse_x - start_x) * (mouse_x - start_x) + (mouse_y - start_y) * (mouse_y - start_y));
    double u_x = (mouse_x - start_x) / length;
    double u_y = (mouse_y - start_y) / length;
    x = x + v * u_x;
    y = y + v * u_y;
}

bool Bullet::Render() {
    if (clock.getElapsedTime().asMilliseconds() > 5) // 控制帧率
    {
        Next();
        clock.restart();
    }
    if (x < 0 || y < 0 || x>Window::Instance().Get().getSize().x || y>Window::Instance().Get().getSize().y) {
        return false;
    }
    else {
        //渲染
        sf::CircleShape shape(radius);
        sf::Color color;
        color.r = 0;
        color.g = 0;
        color.b = 255;
        shape.setFillColor(color);
        shape.setPosition(x, y);
        Window::Instance().Get().draw(shape);
    }
    return true;
}

bool Ball::CollisionAABB(int otherX, int otherY, int width, int height) {
    //A otherX,otherY,width height
    //B x y radius*2 radius*2
    //std::cout<< x << " " << y << " " << radius * 2 << " " << radius * 2 << " " << otherX << " " << otherY << " " << width<<" " << height << std::endl;
    return Utils::CollisionAABB(x-radius, y-radius, radius*2 , radius*2 , otherX, otherY, width, height);
}

void Ball::Render() {
    sf::CircleShape shape(radius);
    sf::Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    shape.setFillColor(color);
    shape.setPosition(x,y);
    Window::Instance().Get().draw(shape);
}