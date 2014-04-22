// betterThanDansTris.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include "IO.h"

int main()
{
	// ----- Vars -----

	// Class for drawing staff, it uses SDL for the rendering. Change the methods of this class
	// in order to use a different renderer
	IO mIO;
	int mScreenHeight = mIO.GetScreenHeight();

	// Pieces
	Pieces mPieces;

	// Board
	Board mBoard(&mPieces, mScreenHeight);

	// Game
	Game mGame(&mBoard, &mPieces, &mIO, mScreenHeight);

	sf::Clock clock;

	while (true) {
		// ----- Draw -----

		mIO.ClearScreen(); 		// Clear screen
		mGame.DrawScene();			// Draw staff
		mIO.UpdateScreen();		// Put the graphic context in the screen

		// ----- Input -----

		int mKey = mIO.Pollkey();

		switch (mKey)
		{
		case (sf::Keyboard::Key::Right) :
		{
							  if (mBoard.IsPossibleMovement(mGame.mPosX + 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
								  mGame.mPosX++;
							  break;
		}

		case (sf::Keyboard::Key::Left) :
		{
							 if (mBoard.IsPossibleMovement(mGame.mPosX - 1, mGame.mPosY, mGame.mPiece, mGame.mRotation))
								 mGame.mPosX--;
							 break;
		}

		case (sf::Keyboard::Key::Down) :
		{
							 if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
								 mGame.mPosY++;
							 break;
		}

		case (sf::Keyboard::Key::X) :
		{
						  // Check collision from up to down
						  while (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation)) { mGame.mPosY++; }

						  mBoard.StorePiece(mGame.mPosX, mGame.mPosY - 1, mGame.mPiece, mGame.mRotation);

						  mBoard.DeletePossibleLines();

						  if (mBoard.IsGameOver())
						  {
							  mIO.Getkey();
							  exit(0);
						  }

						  mGame.CreateNewPiece();

						  break;
		}

		case (sf::Keyboard::Key::Z) :
		{
						  if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY, mGame.mPiece, (mGame.mRotation + 1) % 4))
							  mGame.mRotation = (mGame.mRotation + 1) % 4;

						  break;
		}
		}

		// ----- Vertical movement -----

		sf::Time elapsed = clock.getElapsedTime();
		

		if (elapsed > sf::milliseconds(WAIT_TIME))
		{
			if (mBoard.IsPossibleMovement(mGame.mPosX, mGame.mPosY + 1, mGame.mPiece, mGame.mRotation))
			{
				mGame.mPosY++;
			}
			else
			{
				mBoard.StorePiece(mGame.mPosX, mGame.mPosY, mGame.mPiece, mGame.mRotation);

				mBoard.DeletePossibleLines();

				if (mBoard.IsGameOver())
				{
					mIO.Getkey();
					exit(0);
				}

				mGame.CreateNewPiece();
			}
			elapsed = clock.restart();
		}
	}

	return 0;
}