#pragma once

// If Windows and not in Debug, this will run without a console window
// You can use this to output information when debugging using cout or cerr
#define MUNCHIECOUNT 50
#define ORANGECOUNT 10
#define GHOSTCOUNT 2
#ifdef WIN32 
	#ifndef _DEBUG
		#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
	#endif
#endif

// Just need to include main header file
#include "S2D/S2D.h"

// Reduces the amount of typing by including all classes in S2D namespace
using namespace S2D;

struct collectible
{
	Texture2D* _munchieTexture;
	Vector2* _munchiePosition;
	Rect* _munchieRect;
	int _munchieDirection;
	int _munchieFrame;
	int _munchieCurrentFrameTime;
	bool munchiedead;
	
};
struct collectible_2
{
	Texture2D* _orangeTexture;
	Vector2* _orangePosition;
	Rect* _orangeRect;
	int _orangeDirection;
	int _orangeFrame;
	int _orangeCurrentFrameTime;
	bool _orangedead;
};

struct MovingEnemy
{
	Vector2* position;
	Texture2D* texture;
	Rect* sourceRect;
	int direction;
	float speed;
	int _ghostsFrame;
	int _ghostsCurrentFrameTime;
	
};

// Declares the Pacman class which inherits from the Game class.
// This allows us to overload the Game class methods to help us
// load content, draw and update our game.
class Pacman : public Game
{
private:
	// Data to represent Pacman
	Vector2* _pacmanPosition;
	Rect* _pacmanSourceRect;
	Texture2D* _pacmanTexture;
	int _pacmanDirection;
	int _pacmanFrame;
	int _pacmanCurrentFrameTime;
	const int _cPamanFrameTime;
	bool _pacmandead;

	


	// Position for String
	Vector2* _stringPosition;

	//constant data for game variables 
	const float _cPacmanSpeed;




	const int _orangeFrameTime;

	//data to represent muchie
	
	const int _munchieFrameTime;

	const int _ghostsFrameTime;
	
	collectible* munchies[MUNCHIECOUNT];
	collectible_2* oranges[ORANGECOUNT];
	MovingEnemy* _ghosts[GHOSTCOUNT];

	//sound data
	SoundEffect* _pop;
	SoundEffect* _pacmanbeginning;
	SoundEffect* _pacmandeath;
	SoundEffect* _pacmaneatfruit;

	// Data for Menu

	Texture2D* _menuBackground; 
	Rect* _menuRectangle; 
	Vector2* _menuStringPosition; 
	bool _paused;
	bool _pKeyDown;
	bool _startScreen;
	Texture2D* _startmenuBackground;
	Rect* _startmenuRectangle;

public:
	/// <summary> Constructs the Pacman class. </summary>
	Pacman(int argc, char* argv[]);

	/// <summary> Destroys any data associated with Pacman class. </summary>
	virtual ~Pacman();

	/// <summary> All content should be loaded in this method. </summary>
	void virtual LoadContent();

	/// <summary> Called every frame - update game logic here. </summary>
	void virtual Update(int elapsedTime);

	/// <summary> Called every frame - draw game here. </summary>
	void virtual Draw(int elapsedTime);

	//input methods
	void Input(int elapsedTime, Input::KeyboardState* state);

	//check methods
	void CheckViewPortCollision();

	//update methods(animation)
	void UpdatePacman(int elapsedTime);
	void UpdateMunchie(int elapsedTime);
	void UpdateOrange(int elapsedTime);
	void UpdateGhostAnimation(int elapsedTime);
	void CheckGhostCollision();
	void UpdateGhost(MovingEnemy*, int elapsedTime);
	void CheckMunchieCollision();
	void CheckOrangeCollision();

};