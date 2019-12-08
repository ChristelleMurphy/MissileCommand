/// <summary>
/// simple game loop for SFML[2.5.1]
/// 
/// @author Christelle Murphy
/// @date November 2019
/// 
/// Estimated time 12 hrs
/// Actual time 20hrs
///				When :	Duration(min)
/// session 1: 100 mins
/// session 2: 50 mins
/// session 3: 70 mins
/// session 4: 100 mins
/// session 5: 40 mins
/// session 6: 20 mins
/// session 7: 60 mins
/// session 8: 90 mins
/// session 9: 100 mins
/// session 10: 50 mins
///Total: 11 hours 30 minutes
/// </summary>

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 


#include "Game.h"

/// <summary>
/// main enrtry point
/// </summary>
/// <returns>success or failure</returns>
int main()
{
	Game game;
	game.run();

	return 1; // success
}