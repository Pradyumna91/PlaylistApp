#pragma once

using namespace System;

public enum Commands
{
	INSERT,
	DELETE,
	PLAY,
	SHUFFLE,
	CREATE,
	UNDEFINED
};

ref class UserInput
{
public:
	Commands command;
	int param1;
	int param2;

	UserInput();
	UserInput(const UserInput^);
	static UserInput^ parseUserInput(String^);
};