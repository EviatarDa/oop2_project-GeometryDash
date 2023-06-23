#pragma once

#include "Command.h"

class Game;

class ScoreTableButton : public Command {
public:
	ScoreTableButton(Game*);
	virtual void execute() override;

private:

};
