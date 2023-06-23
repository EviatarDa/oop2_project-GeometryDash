#pragma once

#include "Command.h"

class Game;

class WithoutYouButton : public Command
{
public:
	WithoutYouButton(Game*);
	virtual void execute() override;

private:

};
