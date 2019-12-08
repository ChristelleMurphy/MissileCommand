/// <summary>
/// @author Christelle Murphy
/// @date November 2019
///
///
/// project comment in main.cpp
/// </summary>

#include "Game.h"
#include <iostream>
#include "MyVector2.h"


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
	setUpRec();//function for drawing rectangle
	//setupSprite(); // load texture
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
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseReleaseEvents(newEvent); // keep code tidy		
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
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	laserMove();
	setUpAsteroid();
	setupExplosion();
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
	m_window.clear(sf::Color::Black);
	
	m_window.draw(m_logoSprite);
	m_window.draw(m_bottomRec);
	m_window.draw(m_playerRec);
	m_window.draw(m_powerRec);
	m_window.draw(m_line2);
	
	m_window.draw(m_line);
	m_window.draw(m_explosion);
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
	m_welcomeMessage.setString("");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(10.0f, 560.0f);
	m_welcomeMessage.setCharacterSize(30U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// sets up rectangle shapes
/// </summary>

void Game::setUpRec()
{
	m_bottomRec.setFillColor(sf::Color::Green);
	m_bottomRec.setOutlineColor(sf::Color::Green);
	m_bottomRec.setSize(sf::Vector2f(800.0f, 40.0f));
	m_bottomRec.setPosition(sf::Vector2f(0.0f, 560.0f));

	m_playerRec.setFillColor(sf::Color::Red);
	m_playerRec.setOutlineColor(sf::Color::Red);
	m_playerRec.setSize(sf::Vector2f(40.0f, 40.0f));
	m_playerRec.setPosition(sf::Vector2f(380.0f, 520.0f));

	m_powerRec.setFillColor(sf::Color::Yellow);
	m_powerRec.setOutlineColor(sf::Color::Yellow);
	m_powerRec.setSize(sf::Vector2f(300.0f, 30.0f));
	m_powerRec.setPosition(sf::Vector2f(40.0f, 565.0f ));

}

void Game::processMouseReleaseEvents(sf::Event t_mouseEvent)
{
	if (sf::Mouse::Left == t_mouseEvent.mouseButton.button)
	{
		if (m_laserReady)
		{
			m_mouseClick = sf::Vector2f{ static_cast<float>(t_mouseEvent.mouseButton.x), static_cast<float>(t_mouseEvent.mouseButton.y) };
			
		}
	}
	setupLaser();
}

/// <summary>
/// Determines start and end of asteroid vector using a randomly generated x co-ordinate for each top and bottom destination.
/// </summary>

void Game::setUpAsteroid()
{
	srand(time(nullptr));

	float x_coOrd = rand() % 800+1;
	float bottomXCoOrd = rand() % 800+1;
  
    asteroidBeginning = {x_coOrd, 0.0f};
	sf::Vertex asteroidStart{asteroidBeginning, sf::Color::Cyan };
    m_line2.append(asteroidBeginning);

	asteroidFin = { bottomXCoOrd, 560.0f };
	sf::Vertex asteroidEnd{asteroidFin, sf::Color::Red };
    m_line2.append(asteroidEnd);

}

void Game::setupLaser()
{
	m_line.clear();
	m_heading = m_mouseClick - lineStart.position; //sets destination to mouseclick minus start of vector
	m_heading = vectorUnitVector(m_heading); //regulates speed despite the distance, increments by one
	m_laserTip = lineStart.position;//
	lineStart = sf::Vertex{ m_laserStart , sf::Color::Green };//vertex begins at laser start

	lineEnd = sf::Vertex{ m_mouseClick, sf::Color::Red };
	
	m_line.append(lineStart);
	m_line.append(lineEnd);


}


void Game::laserMove()
{

	float missileSpeed = { 2.0f };
	m_velocity = m_heading * missileSpeed;//value of velocity given the value of heading by speed;
	m_laserTip += m_heading;
	lineStart = sf::Vertex{ m_laserStart , sf::Color::Green };//vertex begins at laser start
	lineEnd = sf::Vertex{ static_cast<sf::Vector2f>(m_laserTip), sf::Color::Red };//vertex begins at laser start

	m_line.clear();
	m_line.append(lineStart);
	m_line.append(lineEnd);

    	if (m_laserTip.y <= m_mouseClick.y)
	{
		m_line.clear();
	}
    //m_maxAltitude = 400 - m_laserPower;//maximum altitude is equal to 
    
}


void Game::setupExplosion()
{
	m_explosion.setRadius(40.0f);
	m_explosion.setPosition(m_mouseClick);
    m_explosion.setFillColor(sf::Color::Red);
	m_explosion.setOutlineColor(sf::Color::Red);
	m_explosion.setOutlineThickness(1.0f);
}

//void Game::increasePowerBar()
//{
//	float barHeight(20.0f);
//
//	if (m_laserPower < 400)
//	{
//		m_laserPower++;
//		m_powerRec.setSize(sf::Vector2f(static_cast<float>(m_laserPower), barHeight));
//	}
//}

//void Game::laserExplosion()
//{
//	m_explosionTime
//}


