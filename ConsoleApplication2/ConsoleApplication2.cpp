// ConsoleApplication2.cpp : main project file.

#include "stdafx.h"
#include "Playlist.h"
#include <iostream>
using namespace System;

ref class UserInput
{
public:
	String^ command;
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
		array<String^>^ params = input->Split(' ');

		
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
		parsedInput.command = params[0];
		if (parsedInput.command->Equals("create"))
		{
			if (params->Length == 2 && (Int32::TryParse(params[1], parsedInput.param1)))
			{
				
			}
		}
	}
}