#include<iostream>
#include<vector>
#include"My2DShape.h"
#include"Window.h"

using crustgames::My2DShape;
using crustgames::Bullet;

My2DShape::My2DShape():Object2D() {
	if (!texture.loadFromFile("asset/sample_character_01.png")) {
		std::cout << "load sample_character_01 error" << std::endl;
	}
	else {
		//ÇÐ¸îÖ¡ 64/4=16 96/3=32
		int frameWidth = 16;
		int frameHeight = 32;
		for (int y = 0; y < texture.getSize().y; y += frameHeight)
		{
			for (int x = 0; x < texture.getSize().x; x += frameWidth)
			{
				frames.push_back(sf::IntRect(x, y, frameWidth, frameHeight));
			}
		}
		sprite.setTexture(texture);
	}
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
	std::cout << "À¬»ø»ØÊÕ" << std::endl;
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

}

void My2DShape::Render() {
	static std::vector<int> vec_x;
	static std::vector<int> vec_y;
	if (x < 1920) {
		x+=100;
	}
	else {
		x = 0;
		y++;
		if (y < 1080) {
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

	if (clock.getElapsedTime().asMilliseconds() > 100) // ¿ØÖÆÖ¡ÂÊ
	{
		currentFrame++;
		if (currentFrame >= frames.size())
			currentFrame = 0;
		clock.restart();
	}
	sprite.setTextureRect(frames[currentFrame]);
	sprite.setPosition(sf::Vector2f(person_x, person_y));
	sprite.setScale(sf::Vector2f(2, 2));
	Window::Instance().Get().draw(sprite);

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
	//×Óµ¯äÖÈ¾
	for (auto iter = bullets.begin(); iter != bullets.end();) {
		if (iter->clock.getElapsedTime().asMilliseconds() > 5) // ¿ØÖÆÖ¡ÂÊ
		{
			iter->Next();
			iter->clock.restart();
		}
		if (iter->x < 0 || iter->y < 0 || iter->x>1920 || iter->y>1080) {
			iter = bullets.erase(iter);
		}
		else {
			//äÖÈ¾
			sf::CircleShape shape(10);
			sf::Color color;
			color.r = 0;
			color.g = 0;
			color.b = 255;
			shape.setFillColor(color);
			shape.setPosition(iter->x, iter->y);
			Window::Instance().Get().draw(shape);
			++iter;
		}
	}
}

void My2DShape::MouseButtonPressed(sf::Event& event) {
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		music.setPlayingOffset(sf::Time());
		music.play();
		int mouse_x = sf::Mouse::getPosition(Window::Instance().Get()).x;
		int mouse_y = sf::Mouse::getPosition(Window::Instance().Get()).y;
		Bullet bullet;
		bullet.mouse_x = mouse_x;
		bullet.mouse_y = mouse_y;
		bullet.start_x = person_x;
		bullet.start_y = person_y;
		bullet.x = bullet.start_x;
		bullet.y = bullet.start_y;
		
		std::cout << "person_x " << person_x << " person_y" << person_y << " mouse_x " << mouse_x << " mouse_y" << mouse_y << std::endl;
		bullets.push_back(bullet);
	}
}

void My2DShape::KeyPressed(sf::Event& event) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Top();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Left();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Down();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Right();
	}
}

void My2DShape::Left() {
	person_x -= 5;
	if (person_x < 0) {
		person_x = 0;
	}
}

void My2DShape::Right() {
	person_x += 5;
	if (person_x > 1920) {
		person_y = 1920;
	}
}

void My2DShape::Top() {
	person_y -= 5;
	if (person_y < 0) {
		person_y = 0;
	}
}

void My2DShape::Down() {
	person_y += 5;
	if (person_y > 1080) {
		person_y = 1080;
	}
}

Bullet::Bullet()
{

}

void Bullet::Next() {
	if (mouse_x >= start_x) {
		x+=2;
	}
	else {
		x-=2;
	}
	if (start_y == mouse_y) {
		start_y = mouse_y + 1;
	}
	const float m = (float)(start_y - mouse_y) / (float)(start_x - mouse_x);
	const float c = start_y - m*start_x;
	y = m*x + c;
}