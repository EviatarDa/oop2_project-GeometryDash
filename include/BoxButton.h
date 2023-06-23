#pragma once

#include "Command.h"

class Game;

class BoxButton : public Command {
public:
	BoxButton(Game*);
	virtual void execute() override;

private:

};
