#pragma once

#include "Command.h"

class Game;

class SpectreButton : public Command
{
public:
	SpectreButton(Game*);
	virtual void execute() override;

private:

};