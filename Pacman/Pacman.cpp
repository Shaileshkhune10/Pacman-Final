#include "Pacman.h"

#include <sstream>

#include<iostream>

Pacman::Pacman(int argc, char* argv[]) : Game(argc, argv), _cPacmanSpeed(0.1f), _cPamanFrameTime(250), _orangeFrameTime(250), _munchieFrameTime(250), _ghostsFrameTime(250)
{
	
	

	_pacmandead = false;
	_pacmanDirection = 0;
	_pacmanCurrentFrameTime = 0;
	_pacmanFrame = 0;
	
	//data for menu
	_paused = false;
	_pKeyDown = false;
	_startScreen = true;

	//data for ghost ai
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i] = new MovingEnemy();
		_ghosts[i]->direction = 0;
		_ghosts[i]->speed = 0.2f;
		_ghosts[i]->_ghostsFrame = 0;
		_ghosts[i]->_ghostsCurrentFrameTime = 0;

	}

		 int i = 0;

		 for (i = 0; i < MUNCHIECOUNT; i++)
		 {
			 munchies[i] = new collectible;
			 munchies[i]->_munchieDirection = 0;
			 munchies[i]->_munchieCurrentFrameTime = 0;
			 munchies[i]->_munchieFrame = 0;
			 munchies[i]->munchiedead = false;
			 
		 }

		 for (i = 0; i < ORANGECOUNT; i++)
		 {
			 oranges[i] = new collectible_2;
			 oranges[i]->_orangeDirection = 0;
			 oranges[i]->_orangeCurrentFrameTime = 0;
			 oranges[i]->_orangeFrame = 0;
			 oranges[i]->_orangedead = false;


		 }

	

	//Initialise important Game aspects
    Audio::Initialise();
	Graphics::Initialise(argc, argv, this, 1024, 768, false, 25, 25, "Pacman", 60);
	Input::Initialise();
	
	
	//audio data
	
	

	

	
	// Start the Game Loop - This calls Update and Draw in game loop
	Graphics::StartGameLoop();
}

Pacman::~Pacman()
{
	delete _pacmanTexture;
	delete _pacmanSourceRect;
	delete _pop;
	
	

}

void Pacman::LoadContent()
{


	


	// Load Pacman
	_pacmanDirection = 0;
	_pacmanTexture = new Texture2D();
	_pacmanTexture->Load("Textures/Pacman.tga", false);
	_pacmanPosition = new Vector2(350.0f, 350.0f);
	_pacmanSourceRect = new Rect(0.0f, 0.0f, 32, 32);

	// Load Munchie
	for (int i = 0; i < 25; i++)
	{
		munchies[i]->_munchieTexture = new Texture2D();
		munchies[i]->_munchieTexture->Load("Textures/Munchie.png", false);
		munchies[i]->_munchiePosition = new Vector2(i * 40, 40);
		munchies[i]->_munchieRect = new Rect(0.0f, 0.0f, 16.0f, 7.0f);
	}
	for (int i = 25; i < 50; i++)
	{
		munchies[i]->_munchieTexture = new Texture2D();
		munchies[i]->_munchieTexture->Load("Textures/Munchie.png", false);
		munchies[i]->_munchiePosition = new Vector2((i - 26) * 40, 600);
		munchies[i]->_munchieRect = new Rect(0.0f, 0.0f, 16.0f, 7.0f);
	}


	// Set string position
	_stringPosition = new Vector2(10.0f, 25.0f);

	//load orange
	for (int i = 0; i < ORANGECOUNT; i++)
	{
		oranges[i]->_orangeTexture = new Texture2D();
		oranges[i]->_orangeTexture->Load("Textures/orange.png", false);
		oranges[i]->_orangePosition = new Vector2(rand() % 1024, rand() % 768);
		oranges[i]->_orangeRect = new Rect(0.0f, 0.0f, 88.0f, 100.0f);
	}

	//loads ghosts
	for (int i = 0; i < GHOSTCOUNT; i++) 
	{
		_ghosts[i]->texture = new Texture2D();
		_ghosts[i]->texture->Load("Textures/ghost.png", false);
		_ghosts[i]->position = new Vector2((rand() % Graphics::GetViewportWidth()), (rand() % Graphics::GetViewportHeight()));
		_ghosts[i]->sourceRect = new Rect(0.0f, 0.0f, 35.0f, 50.0f);

	}

	_pop = new SoundEffect();
	_pacmanbeginning = new SoundEffect();

	_pacmaneatfruit = new SoundEffect();
	_pacmandeath = new SoundEffect();

	_pop->Load("Audio/pop.wav");
	_pacmanbeginning->Load("Audio/pacman_beginning.wav");
	_pacmandeath->Load("Audio/pacman_death.wav");
	_pacmaneatfruit->Load("Audio/pacman_eatfruit.wav");

	Audio::Play(_pacmanbeginning);

	//data for mentu
	_menuBackground = new Texture2D();

	_menuBackground->Load("Textures/Transperancy.jpg", false);

	_menuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());

	_menuStringPosition = new Vector2(Graphics::GetViewportWidth() / 2.0f, Graphics::GetViewportHeight() / 2.0f);

	// menu for the start screen
	_startmenuBackground = new Texture2D();

	_startmenuBackground->Load("Textures/pacmanstart.jpg", false);

	_startmenuRectangle = new Rect(0.0f, 0.0f, Graphics::GetViewportWidth(), Graphics::GetViewportHeight());

	

	
	
}

void Pacman::Update(int elapsedTime)
{
	Input::KeyboardState* keyboardState = Input::Keyboard::GetState();

	if (keyboardState->IsKeyDown(Input::Keys::SPACE))

	{

		

		_startScreen = false;

	}

	if (keyboardState->IsKeyDown(Input::Keys::P) && !_pKeyDown)

	{

		_pKeyDown = true;

		_paused = !_paused;

	}
	if (keyboardState->IsKeyUp(Input::Keys::P))

		_pKeyDown = false;
	

	if (!_paused) {
		Input(elapsedTime, keyboardState);
	}

	// Gets the current state of the keyboard
	//call the funcions here
	Input(elapsedTime, keyboardState);
	UpdateMunchie(elapsedTime);
	UpdateMunchie(elapsedTime);
	UpdatePacman(elapsedTime);
	UpdateOrange(elapsedTime);
	CheckGhostCollision();
	UpdateGhostAnimation(elapsedTime);
	CheckMunchieCollision();
	CheckOrangeCollision();

	for (int i = 0; i < GHOSTCOUNT; i++)
	{
	
	UpdateGhost(_ghosts[i], elapsedTime);
    }
}

void Pacman::UpdatePacman(int elapsedTime)
{
	//pacman mouth opening animation is here
	_pacmanCurrentFrameTime += elapsedTime;

	if (_pacmanCurrentFrameTime > _cPamanFrameTime)
	{
		_pacmanFrame++;
		if (_pacmanFrame >= 2)
			_pacmanFrame = 0;
		_pacmanCurrentFrameTime = 0;
	}

	_pacmanSourceRect->X = _pacmanSourceRect->Width * _pacmanFrame;

}


void Pacman::Input(int elapsedTime, Input::KeyboardState* state)
{
	//keyboard input to move the pacman

	// Checks if D key is pressed
	//pacman movement
	if (state->IsKeyDown(Input::Keys::D))
	{
		_pacmanPosition->X += 0.1f * elapsedTime; //Moves Pacman across X axis
		_pacmanDirection = 0;
	}
	else if (state->IsKeyDown(Input::Keys::A))
	{
		_pacmanPosition->X -= _cPacmanSpeed * elapsedTime;
		_pacmanDirection = 2;

	}
	else if (state->IsKeyDown(Input::Keys::W))
	{
		_pacmanPosition->Y -= _cPacmanSpeed * elapsedTime;
		_pacmanDirection = 3;
	}
	else if (state->IsKeyDown(Input::Keys::S))
	{
		_pacmanPosition->Y += _cPacmanSpeed * elapsedTime;
		_pacmanDirection = 1;
	}
	_pacmanSourceRect->Y = _pacmanSourceRect->Height * _pacmanDirection;
}

void Pacman::CheckViewPortCollision()
{
	//pacman wrapping 

	if (_pacmanPosition->X + _pacmanSourceRect->Width > 1024)
	{
		_pacmanPosition->X = 0 + _pacmanSourceRect->Width;
	}
	if (_pacmanPosition->X - _pacmanSourceRect->Width < 0)
	{
		_pacmanPosition->X = 1024 - _pacmanSourceRect->Width;
	}
	if (_pacmanPosition->Y + _pacmanSourceRect->Width > 768)
	{
		_pacmanPosition->Y = 0 + _pacmanSourceRect->Width;
	}
	if (_pacmanPosition->Y - _pacmanSourceRect->Width < 0)
	{
		_pacmanPosition->Y = 768 - _pacmanSourceRect->Width;
	}

}

void Pacman::UpdateMunchie(int elapsedTime)
{
	//munchie animation code
	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		munchies[i]->_munchieCurrentFrameTime += elapsedTime;

		if (munchies[i]->_munchieCurrentFrameTime > _munchieFrameTime)
		{
			munchies[i]->_munchieFrame++;
			if (munchies[i]->_munchieFrame >= 4)
				munchies[i]->_munchieFrame = 0;
			munchies[i]->_munchieCurrentFrameTime = 0;
		}


		munchies[i]->_munchieRect->X = munchies[i]->_munchieRect->Width * munchies[i]->_munchieFrame;
	}
}
void Pacman::UpdateOrange(int elapsedTime)
{
	//orange animation code
	for (int i = 0; i < ORANGECOUNT; i++)
	{
		oranges[i]->_orangeCurrentFrameTime += elapsedTime;

		if (oranges[i]->_orangeCurrentFrameTime > _orangeFrameTime)
		{
			oranges[i]->_orangeCurrentFrameTime += elapsedTime;

			oranges[i]->_orangeFrame++;
			if (oranges[i]->_orangeFrame >= 4)
				oranges[i]->_orangeFrame = 0;
			oranges[i]->_orangeCurrentFrameTime = 0;
		}

		oranges[i]->_orangeRect->Y = oranges[i]->_orangeRect->Height * oranges[i]->_orangeFrame;
	}
}
void Pacman::UpdateGhost(MovingEnemy* ghost, int elapsedTime)
{
	if (ghost->direction == 0) //Moves Right 
	{
		ghost->position->X += ghost->speed * elapsedTime;
	}
	else if (ghost->direction == 4) //Moves Left 
	{
		ghost->position->X -= ghost->speed * elapsedTime;
	}

	if (ghost->position->X + ghost->sourceRect->Width >=
		Graphics::GetViewportWidth()) //Hits Right edge 
	{
		ghost->direction = 4; //Change direction 
	}
	else if (ghost->position->X <= 0) //Hits left edge 
	{
		ghost->direction = 0; //Change direction 
	}
}
void Pacman::CheckGhostCollision()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacmanPosition->Y + _pacmanSourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacmanPosition->X;
	int left2 = 0;
	int right1 = _pacmanPosition->X + _pacmanSourceRect->Width;

	int right2 = 0;
	int top1 = _pacmanPosition->Y;
	int top2 = 0;

	for (i = 0; i < GHOSTCOUNT; i++)
	{
		// Populate variables with Ghost data
		bottom2 =_ghosts[i]->position->Y + _ghosts[i]->sourceRect->Height;
		left2 = _ghosts[i]->position->X;
		right2 =_ghosts[i]->position->X + _ghosts[i]->sourceRect->Width;
		top2 = _ghosts[i]->position->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2)
			&& (left1 < right2))
		{
			Audio::Play(_pacmandeath);
			_pacmandead = true;
			i = GHOSTCOUNT;
		}
	}
}
void Pacman::CheckMunchieCollision()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacmanPosition->Y + _pacmanSourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacmanPosition->X;
	int left2 = 0;
	int right1 = _pacmanPosition->X + _pacmanSourceRect->Width;

	int right2 = 0;
	int top1 = _pacmanPosition->Y;
	int top2 = 0;

	for (i = 0; i < MUNCHIECOUNT; i++)
	{
		// Populate variables with Ghost data
		bottom2 = munchies[i]->_munchiePosition->Y + munchies[i]->_munchieRect->Height;
		left2 = munchies[i]->_munchiePosition->X;
		right2 = munchies[i]->_munchiePosition->X + munchies[i]->_munchieRect->Width;
		top2 = munchies[i]->_munchiePosition->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2)
			&& (left1 < right2))
		{
			if(!munchies[i]->munchiedead)
			{
				Audio::Play(_pop);
			}
			munchies[i]->munchiedead = true;
			
		}
	}
}
void Pacman::CheckOrangeCollision()
{
	// Local Variables
	int i = 0;
	int bottom1 = _pacmanPosition->Y + _pacmanSourceRect->Height;
	int bottom2 = 0;
	int left1 = _pacmanPosition->X;
	int left2 = 0;
	int right1 = _pacmanPosition->X + _pacmanSourceRect->Width;

	int right2 = 0;
	int top1 = _pacmanPosition->Y;
	int top2 = 0;

	for (i = 0; i < ORANGECOUNT; i++)
	{
		// Populate variables with Ghost data
		bottom2 = oranges[i]->_orangePosition->Y + oranges[i]->_orangeRect->Height / 5.0f;
		left2 = oranges[i]->_orangePosition->X;
		right2 = oranges[i]->_orangePosition->X + oranges[i]->_orangeRect->Width / 4.5f;
		top2 = oranges[i]->_orangePosition->Y;

		if ((bottom1 > top2) && (top1 < bottom2) && (right1 > left2)
			&& (left1 < right2))
		{
			if (!oranges[i]->_orangedead)
			{
				Audio::Play(_pacmaneatfruit);
			}
			oranges[i]->_orangedead = true;

		}
	}
}

void Pacman::UpdateGhostAnimation(int elapsedTime)
{
	//ghost animation code
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		_ghosts[i]->_ghostsCurrentFrameTime += elapsedTime;

		if (_ghosts[i]->_ghostsCurrentFrameTime > _ghostsFrameTime)
		{
			_ghosts[i]->_ghostsFrame++;
			if (_ghosts[i]->_ghostsFrame >= 8)
				_ghosts[i]->_ghostsFrame = 0;
			_ghosts[i]->_ghostsCurrentFrameTime = 0;
		}

		_ghosts[i]->sourceRect->Y = _ghosts[i]->sourceRect->Height * _ghosts[i]->direction;
	}
}



void Pacman::Draw(int elapsedTime)
{
	// Allows us to easily create a string
	std::stringstream stream;
	
	stream << "Pacman X: " << _pacmanPosition->X << " Y: " << _pacmanPosition->Y;

	SpriteBatch::BeginDraw(); // Starts Drawing
	if (!_pacmandead) 
	{
		SpriteBatch::Draw(_pacmanTexture, _pacmanPosition, _pacmanSourceRect); // Draws Pacman
	}


	for (int i = 0; i < ORANGECOUNT; i++)
	{
		if (!oranges[i]->_orangedead)
		{
			SpriteBatch::Draw(oranges[i]->_orangeTexture, oranges[i]->_orangePosition, oranges[i]->_orangeRect, Vector2::Zero, 0.2f, 0.0f, Color::White, SpriteEffect::NONE); //draws orange
		}
	}

	

	for (int i = 0; i < MUNCHIECOUNT; i++)
	{
		if (!munchies[i]->munchiedead) 
		{
			SpriteBatch::Draw(munchies[i]->_munchieTexture, munchies[i]->_munchiePosition, munchies[i]->_munchieRect, Vector2::Zero, 2.0f, 0.0f, Color::White, SpriteEffect::NONE); //munchie
		}
	}
	//draws ghost
	for (int i = 0; i < GHOSTCOUNT; i++)
	{
		SpriteBatch::Draw(_ghosts[i]->texture, _ghosts[i]->position, _ghosts[i]->sourceRect); 
	}

	
	if (_paused)

	{

		std::stringstream menuStream; menuStream << "PAUSED!";

		SpriteBatch::Draw(_menuBackground, _menuRectangle, nullptr); 
		SpriteBatch::DrawString(menuStream.str().c_str(), _menuStringPosition, Color::Red);

	}
	if (_startScreen == true )

	{

		

		SpriteBatch::Draw(_startmenuBackground, _startmenuRectangle, nullptr);
		

	}
	// Draws String
	SpriteBatch::DrawString(stream.str().c_str(), _stringPosition, Color::Green);
	SpriteBatch::EndDraw(); // Ends Drawing
}