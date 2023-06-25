#pragma once

#pragma once

#include "Command.h"

class Game;

class HelpButton : public Command {
public:
	HelpButton(Game*, sf::RenderWindow&);
	virtual void execute() override;

private:
};

