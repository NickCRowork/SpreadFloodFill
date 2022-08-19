#include "SFML/Graphics.hpp"
/// <summary>
/// Attempt to do flood fill in SFML. Does not work because sf::Image.getPixel() does not return foreground pixel colors of an image.
/// </summary>

sf::Vector2f viewSize(1024, 768);//The view of the screen
sf::VideoMode vm(viewSize.x, viewSize.y);//Sets view to the screen
sf::RenderTexture canvas;
sf::Texture canvasTexture;
sf::Sprite drawingSprite;
sf::Image pixelImage = sf::Image();
sf::Color pixelColor;
sf::RenderWindow window(vm, "Spread Flood Fill", sf::Style::Default);//Renders to the screen
sf::RectangleShape rect(sf::Vector2f(500.0f, 300.0f));
sf::CircleShape circle(100);
sf::RectangleShape rect2(sf::Vector2f(500.0f, 300.0f));
bool canvasModified = false;

void init()
{
	//Create drawing canvas
	canvas.create(1024, 768);
	canvas.clear(sf::Color::Magenta);
	//Rectangle
	rect.setFillColor(sf::Color::Yellow);
	rect.setPosition(viewSize.x / 2, viewSize.y / 2 + 50);
	rect.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
	//Circle
	circle.setFillColor(sf::Color::Green);
	circle.setPosition(viewSize.x / 2, viewSize.y / 2 + 98);
	circle.setOrigin(sf::Vector2f(circle.getRadius(), circle.getRadius()));
	//Different Rectangle
	rect2.setFillColor(sf::Color::Blue);
	rect2.setPosition(viewSize.x / 2, viewSize.y / 2);
	rect2.setOrigin(sf::Vector2f(rect.getSize().x / 2, rect.getSize().y / 2));
	canvas.draw(rect);
	canvas.draw(rect2);
	canvas.draw(circle);
	canvas.display();
	canvasTexture = canvas.getTexture();
	drawingSprite.setTexture(canvasTexture, true);
	pixelImage = canvasTexture.copyToImage();
}

void updateInput()
{
	sf::Event event;

	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}
		}
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.key.code == sf::Mouse::Left)
			{
				sf::Vector2i pos = sf::Mouse::getPosition();
				auto translatedPos = canvas.mapCoordsToPixel(sf::Vector2f(pos.x, pos.y));
				if (translatedPos.x >= 0 && translatedPos.x <= canvas.getSize().x && translatedPos.y >= 0 && translatedPos.y <= canvas.getSize().y)
				{
					pixelColor = pixelImage.getPixel(translatedPos.x, translatedPos.y);
				}

			}
		}
		if (event.type == sf::Event::KeyReleased)
		{

		}
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
	}
}

void update(float dt)
{

}

void draw()
{
	window.draw(drawingSprite);
}

int main()
{
	//Initialize Game Objects
	init();
	sf::Clock clock;
	//Main game loop
	while (window.isOpen())
	{
		//Handle Keyboard Events
		updateInput();

		//Update game
		sf::Time dt = clock.restart();
		update(dt.asMilliseconds());
		//Update Game Objects
		window.clear(sf::Color::Red);
		//Render Game Objects
		draw();
		window.display();
	}
	return 0;
}