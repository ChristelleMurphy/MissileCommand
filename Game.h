/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// 
/// project comment in main.cpp
/// </summary>
#include <SFML/Graphics.hpp>
#include "MyVector2.h"
#include <stdlib.h>
#include <time.h>

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setUpRec();
	void processMouseReleaseEvents(sf::Event t_mouseEvent);
	void setUpAsteroid();
	void laserMove();
	void setupLaser();
	void setupExplosion();
	void increasePowerBar();
	void laserExplosion();


	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	sf::RectangleShape m_bottomRec; //bottom rectangle on screen
	sf::RectangleShape m_playerRec; //player rectangle
	sf::RectangleShape m_powerRec; //rectangle for altitude bar
	sf::CircleShape m_explosion;
    sf::Vector2f m_heading;
	sf::Vector2f m_velocity;
    sf::Vector2f m_laserStart{ 400.0f, 540.0f };
	sf::Vector2f m_mouseClick;
    sf::Vector2f m_laserEnd{ m_mouseClick };
	sf::Vector2f asteroidBeginning{};
	sf::Vector2f asteroidFin{};
	sf::Vector2f laserLocation;
	sf::Vertex lineStart;
	sf::Vertex lineEnd;
	sf::Vector2f m_laserTip;

	float m_maxAltitude{0};
	float m_explosionTime{ 0 };
	float m_laserRange{ 0 };
	bool m_laserReady = true;
	float m_laserPower{0};

	bool m_exitGame; // control exiting game

	float velocityCounter = 0.0f;
	float velocityIncrement = 0.25f;
	int m_velocityFrame = 0;

	sf::VertexArray m_line{ sf::Lines };
	sf::VertexArray m_line2{ sf::Lines };
};

#endif // !GAME_HPP

