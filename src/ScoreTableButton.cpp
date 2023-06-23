#pragma once

#include "ScoreTableButton.h"
#include "Game.h"

ScoreTableButton::ScoreTableButton(Game* game)
	:Command(game)
{
}

void ScoreTableButton::execute()
{
	m_game->scoreTable();
}
