// ConsoleApplication2.cpp : main project file.

#include "stdafx.h"
#include "Playlist.h"
#include <iostream>
using namespace System;

enum Commands
{
	INSERT,
	DELETE,
	PLAY,
	SHUFFLE,
	CREATE
};

ref class UserInput
{
public:
	Commands command;
	int param1;
	int param2;


};

int main()
{
	Playlist playlist;
	String^ input;
	
	Console::WriteLine("Type in your commands below. Type \"exit\" to quit");
	do
	{
		input = Console::ReadLine();
		UserInput parsedInput = parseUserInput(input);

		switch (parsedInput.command)
		{
		case INSERT:
			break;
		case DELETE:
			break;
		case SHUFFLE:
			break;
		case PLAY:
			break;
		case CREATE:
			break;
		default:
			break;
		}

		
	} while (!input->Equals("exit"));

	/*playlist.create(5);
	playlist.playTrack(3);
	playlist.insertTrackAtPosition(2, 5);
	playlist.deleteTrackAtPosition(3);
	playlist.deleteTrackAtPosition(3);*/
	char c;
	std::cin >> c;
}

UserInput parseUserInput(String^ input)
{
	UserInput parsedInput;
	array<String^>^ params = input->Split(' ');
	if (params->Length > 0)
	{
		String^ textComm = params[0];
		if (textComm->Equals("create")
			|| textComm->Equals("delete")
			|| textComm->Equals("play"))
		{
			if (textComm->Equals("create"))
			{
				parsedInput.command = CREATE;
			}
			else if (textComm->Equals("delete"))
			{
				parsedInput.command = DELETE;
			}
			else
			{
				parsedInput.command = PLAY;
			}
			bool val = (params->Length == 2) && (Int32::TryParse(params[1], parsedInput.param1));
			if (!val)
			{
				throw gcnew ArgumentException("The inputs are not valid");
			}
		}
		else if (textComm->Equals("shuffle"))
		{
			parsedInput.command = SHUFFLE;
		}
		else if (textComm->Equals("insert"))
		{
			parsedInput.command = INSERT;
			bool val = (params->Length == 3) && (Int32::TryParse(params[1], parsedInput.param1)) && (Int32::TryParse(params[1], parsedInput.param2));
			if (!val)
			{
				throw gcnew ArgumentException("The inputs are not valid");
			}
		}
		else
		{
			throw gcnew ArgumentException("Invalid command provided");
		}
	}

	return parsedInput;
}