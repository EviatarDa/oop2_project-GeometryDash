#pragma once

#include "Command.h"

class Game;

class OnlyTheHorsesButton : public Command
{
public:
	OnlyTheHorsesButton(Game*);
	virtual void execute() override;

private:

};