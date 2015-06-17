// ConsoleApplication2.cpp : main project file.

#include "stdafx.h"
#include "Playlist.h"
#include "UserInput.h"
#include <iostream>
using namespace System;

int main()
{
	Playlist playlist;
	String^ input;
	UserInput^ parsedInput;
	
	Console::WriteLine("Type in your commands below. Type \"exit\" to quit");
	input = Console::ReadLine();

	while (!input->Equals("exit"))
	{
		try
		{
			parsedInput = UserInput::parseUserInput(input);
		}
		catch (ArgumentException^ e)
		{
			Console::WriteLine(e->Message);
			parsedInput = gcnew UserInput();
		}

		try
		{

			switch (parsedInput->command)
			{
			case INSERT:
				playlist.insertTrackAtPosition(parsedInput->param1, parsedInput->param2);
				break;
			case DELETE:
				playlist.deleteTrackAtPosition(parsedInput->param1);
				break;
			case SHUFFLE:
				playlist.shuffle();
				break;
			case PLAY:
				playlist.playTrack(parsedInput->param1);
				break;
			case CREATE:
				playlist.create(parsedInput->param1);
				break;
			default:
				break;
			}
		}
		catch (ArgumentException^ e)
		{
			Console::WriteLine(e->Message);
		}

		input = Console::ReadLine();
	} 

	/*playlist.create(5);
	playlist.playTrack(3);
	playlist.insertTrackAtPosition(2, 5);
	playlist.deleteTrackAtPosition(3);
	playlist.deleteTrackAtPosition(3);*/
}