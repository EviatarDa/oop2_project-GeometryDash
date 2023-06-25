#pragma once

#include "Command.h"

class Game;

class ScoreTableButton : public Command
{
public:
	ScoreTableButton(Game*, sf::RenderWindow&);
	virtual void execute() override;

private:

};
