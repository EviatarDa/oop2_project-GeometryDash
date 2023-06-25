#pragma once

#include "Command.h"

class Game;

class WithoutYouButton : public Command
{
public:
	WithoutYouButton(Game*, sf::RenderWindow&);
	virtual void execute() override;

private:

};
