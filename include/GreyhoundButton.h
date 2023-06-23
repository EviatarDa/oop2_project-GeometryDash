#pragma once

#include "Command.h"

class Game;

class GreyhoundButton : public Command
{
public:
	GreyhoundButton(Game*);
	virtual void execute() override;

private:

};