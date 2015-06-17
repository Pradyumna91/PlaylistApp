#include "stdafx.h"
#include "UserInput.h"

UserInput::UserInput()
{
	this->command = UNDEFINED;
	this->param1 = -999;
	this->param2 = -999;
}

UserInput::UserInput(const UserInput^ obj)
{
	this->command = obj->command;
	this->param1 = obj->param1;
	this->param2 = obj->param2;
}

UserInput^ UserInput::parseUserInput(String^ input)
{
	UserInput^ parsedInput = gcnew UserInput();
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
				parsedInput->command = CREATE;
			}
			else if (textComm->Equals("delete"))
			{
				parsedInput->command = DELETE;
			}
			else
			{
				parsedInput->command = PLAY;
			}
			bool val = (params->Length == 2) && (Int32::TryParse(params[1], parsedInput->param1));
			if (!val || (parsedInput->param1 < 0))
			{
				throw gcnew ArgumentException("The inputs are not valid");
			}
		}
		else if (textComm->Equals("shuffle"))
		{
			parsedInput->command = SHUFFLE;
		}
		else if (textComm->Equals("insert"))
		{
			parsedInput->command = INSERT;
			bool val = (params->Length == 3) && (Int32::TryParse(params[1], parsedInput->param1)) && (Int32::TryParse(params[2], parsedInput->param2));
			if (!val || (parsedInput->param1 < 0) || (parsedInput->param2 < 0))
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