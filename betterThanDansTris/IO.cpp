/*****************************************************************************************
/* File: IO.cpp
/* Desc: Class for handling inpung & drawing, it uses SDL for the rendering. Change the methods 
/* of this class in order to use a different renderer
/*       
/*
/* gametuto.com - Javier López López (javilop.com)
/*
/*****************************************************************************************
/*
/* Creative Commons - Attribution 3.0 Unported
/* You are free:
/*	to Share — to copy, distribute and transmit the work
/*	to Remix — to adapt the work
/*
/* Under the following conditions:
/* Attribution. You must attribute the work in the manner specified by the author or licensor 
/* (but not in any way that suggests that they endorse you or your use of the work).
/*
/*****************************************************************************************/

// ------ Includes -----

#include "stdafx.h"
#include "IO.h"
#include <iostream>

 static sf::RenderWindow *mScreen;									// Screen
 int x = 1;
 int y = 1;
//static Uint32 mColors [COLOR_MAX] = {0x000000ff,					// Colors
//                               0xff0000ff, 0x00ff00ff, 0x0000ffff,
//                               0x00ffffff, 0xff00ffff, 0xffff00ff,
//                               0xffffffff};

/* 
======================================									
Init
====================================== 
*/
IO::IO() 
{
	InitGraph();
}


/* 
======================================									
Clear the screen to black
====================================== 
*/
void IO::ClearScreen() 
{
	mScreen->clear();
}


/* 
======================================									
Draw a rectangle of a given color

Parameters:
>> pX1, pY1: 		Upper left corner of the rectangle
>> pX2, pY2: 		Lower right corner of the rectangle
>> pC				Rectangle color
====================================== 
*/
void IO::DrawRectangle (int pX1, int pY1, int pX2, int pY2, sf::Color pC)
{
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(pX2-pX1, pY2-pY1));
	rectangle.setPosition(pX1, pY1);
	rectangle.setFillColor(pC);
	rectangle.setOutlineColor(sf::Color::White);
	rectangle.setOutlineThickness(1);
	mScreen->draw(rectangle);
}


/* 
======================================									
Return the screen height
====================================== 
*/
int IO::GetScreenHeight()
{
	return mScreen->getSize().y;
}


/* 
======================================									
Update screen
====================================== 
*/
void IO::UpdateScreen()
{
	mScreen->display();
}


/* 
======================================									
Keyboard Input
====================================== 
*/
int IO::Pollkey()
{
	sf::Event event;
	while (mScreen->pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mScreen->close();
				break;
			case sf::Event::KeyPressed:
				return event.key.code;
				break;
			default:
				break;
		}
			
	}
	return sf::Keyboard::Key::Unknown;
}

/* 
======================================									
Keyboard Input
====================================== 
*/
int IO::Getkey()
{
	sf::Event event;
	while (true)
	{
		mScreen->waitEvent(event);
		if (event.type == event.KeyPressed)
			break;
		if (event.type == sf::Event::Closed)
			mScreen->close();
	};
	return event.KeyPressed;
}

/* 
======================================									
SDL Graphical Initialization
====================================== 
*/

int IO::InitGraph()
{
	mScreen = new sf::RenderWindow(sf::VideoMode(640, 480), "Better than Dantris");
	return 0;
}