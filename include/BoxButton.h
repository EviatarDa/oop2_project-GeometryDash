#pragma once

#include "Command.h"

class Game;

class BoxButton : public Command {
public:
	BoxButton(Game*, sf::RenderWindow&);
	virtual void execute() override;

private:

};
