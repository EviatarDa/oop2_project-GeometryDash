#pragma once

#include "Command.h"

class Game;

class GreyhoundButton : public Command
{
public:
	GreyhoundButton(Game*, sf::RenderWindow&);
	virtual void execute() override;

private:

};