#include<iostream>
#include<vector>
#include"My2DShape.h"
#include"Window.h"

using crustgames::My2DShape;
using crustgames::Bullet;
using crustgames::Person;

Person::Person() {
	if (!texture.loadFromFile("asset/sample_character_04.png")) {
		std::cout << "load sample_character_01 error" << std::endl;
	}
	else {
		//«–∏Ó÷° 64/4=16 96/3=32
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
	if (clock.getElapsedTime().asMilliseconds() > 100) // øÿ÷∆÷°¬ 
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
	std::cout << "¿¨ª¯ªÿ ’" << std::endl;
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
		//std::cout << "person_x " << person.x << " person_y" << person.y << " mouse_x " << mouse_x << " mouse_y" << mouse_y << std::endl;
		bullets.push_back(bullet);
	}
}

void My2DShape::Render() {
	static std::vector<int> vec_x;
	static std::vector<int> vec_y;
	if (x < Window::Instance().Get().getSize().x) {
		x+=100;
	}
	else {
		x = 0;
		y++;
		if (y < Window::Instance().Get().getSize().y) {
			y+=10;
		}
		else {
			//ToDone();
			//return;
			x = 0;
			y = 0;
			vec_x.clear();
			vec_y.clear();
		}
	}
	vec_x.push_back(x);
	vec_y.push_back(y);
	for (int i = 0; i < vec_x.size(); ++i) {
		const int x = vec_x[i];
		const int y = vec_y[i];
		sf::CircleShape shape((x+y)%10);
		sf::Color color;
		color.r = (x%255*y%255)%255;
		color.g = (x % 255 + y % 255) % 255;
		color.b = (x % 255 + y *2) % 255;
		shape.setFillColor(color);
		shape.setPosition(x, y);
		Window::Instance().Get().draw(shape);
	}
	//fps
	fps.Show();
	text.setString(sf::String(std::string("FPS: ") + std::to_string(fps.Get())));
	Window::Instance().Get().draw(text);
	//◊”µØ‰÷»æ
	for (auto iter = bullets.begin(); iter != bullets.end();) {
		bool bRet=iter->Render();
		if (!bRet) {
			iter=bullets.erase(iter);
		}
		else {
			++iter;
		}
	}
	//»ÀŒÔ‰÷»æ
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
	double v = 2;
	double length = sqrt((mouse_x - start_x) * (mouse_x - start_x) + (mouse_y - start_y) * (mouse_y - start_y));
	double u_x = (mouse_x - start_x) / length;
	double u_y = (mouse_y - start_y) / length;
	x = x + v * u_x;
	y = y + v * u_y;
}

bool Bullet::Render() {
	if (clock.getElapsedTime().asMilliseconds() > 5) // øÿ÷∆÷°¬ 
	{
		Next();
		clock.restart();
	}
	if (x < 0 || y < 0 || x>Window::Instance().Get().getSize().x || y>Window::Instance().Get().getSize().y) {
		return false;
	}
	else {
		//‰÷»æ
		sf::CircleShape shape(5);
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