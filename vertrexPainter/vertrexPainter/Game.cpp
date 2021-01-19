/// <summary>
/// @author Peter Lowe
/// @date Jan 2021
///
/// "Simple " program to draw using vertex arrays
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
		if (sf::Event::MouseButtonPressed == newEvent.type)
		{
			processMouseClick(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
	if (sf::Keyboard::Num0 == t_event.key.code)
	{
		m_vertexArray.clear();
		m_vertexArray.setPrimitiveType(sf::Points);
	}
	if (sf::Keyboard::Num1 == t_event.key.code)
	{
		m_vertexArray.clear();
		m_vertexArray.setPrimitiveType(sf::Lines);
		std::cout << " Now drawing Lines" << std::endl;
	}
	if (sf::Keyboard::Num2 == t_event.key.code)
	{
		m_vertexArray.clear();
		m_vertexArray.setPrimitiveType(sf::Triangles);
		std::cout << "now Drawing triangles" << std::endl;
	}
	if (sf::Keyboard::Num3 == t_event.key.code)
	{
		m_vertexArray.clear();
		m_vertexArray.setPrimitiveType(sf::TriangleStrip);
	}
	if (sf::Keyboard::Num4 == t_event.key.code)
	{
		m_vertexArray.clear();
		m_vertexArray.setPrimitiveType(sf::Quads);
	}

	if (sf::Keyboard::R == t_event.key.code)
	{
		m_colour = sf::Color::Red;
		std::cout << "now drawing in Red" << std::endl;
	}
	if (sf::Keyboard::Slash == t_event.key.code
		&& sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		m_colour = sf::Color(128, 128, 128, 40);
	}
}

/// <summary>
/// take coo-iorindates from mouse cliock and use to
// create a new vertex suing current colour
// then add to vertex array
/// </summary>
/// <param name="t_event">windows system evewnt should be a mouse down press</param>
void Game::processMouseClick(sf::Event t_event)
{
	sf::Vertex nextVertex; // local variable
	nextVertex.color = m_colour;
	nextVertex.position.x = t_event.mouseButton.x;
	nextVertex.position.y = t_event.mouseButton.y;
	m_vertexArray.append(nextVertex); // makes a copy of the vertex
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_logoSprite);
	m_window.draw(m_vertexArray);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}
