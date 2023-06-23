#pragma once

#pragma once

#include "Command.h"

class Game;

class HelpButton : public Command {
public:
	HelpButton(Game*);
	virtual void execute() override;

private:
};

