Project: Geometry Dash
Names:

Eviatar Davidyan  207259755
Shir Yadid  208327957

Game instructions:
The goal of the game: to reach the end of the stage as quickly as possible with as many coins as possible.

The player moves by pressing space to jump or left and right arrows to move forward or backward. If the player crashes into an obstacle such as a thorn, a brick or a running enemy the stage restarts.

During the game there are gates that the player must enter through and they change states:

Gravity Gate - Changes the gravity in the game so that the player is pulled up or down.

Mode change gate (spaceship or normal player)-
Normal mode - a mode in which the player can move left or right at his own pace.
Spaceship mode - a mode in which the player's visibility changes to a spaceship and the movement is only forward at a constant rate, without the possibility of slowing down.
Even in this situation it is forbidden to touch different objects in the game except the ceiling and the floor.
 
In addition, there are bouncers in the game-
The bouncers give him a strong jump boost and help the player go over obstacles.

There are disappearing stairs-
The stairs disappear (turn red) for a few seconds the second the player touches them. And the player is not allowed to land on them as long as they "disappear".



Departments:

Game - the class that controls everything has the board, menu as main members.
Reasources- a singleton that holds all the textures, spritessheets, sounds.
Factory-a  template factory of game object.
Command- an abstract class of command in the menu.
 	These are the classes that inhert from this class:
		- HelpButton
		- GreyhoundButton
		- OnlyTheHorsesButton
		- PlayButton
		- ScoreTableButton
		- SpectreButton
		- WithoutYouButton
Menu-a class the perform a menu operation.
LevelMenu

Board- the board of the game holds the objects, has the box2d world that hols the bodies of each object.
MyContactLisener - the class that handles collision between 2 object.

GameObject- a base class of object in the game:

	StaticObject-the base of the static object:
		-Spikes
		-Brick
		-Gate
		-Jumper

	MovingObject-the base class of the moving object:
		-Player: the class of the player - it has state, score, few boolean
		-Enemy: the class of the eneny.

Data structure- 

std::map - for the factory saves std::pair(sf:Color, func) each color represent an object and has a lambda function which calls its c-tor.
std::map - for the multimethod design pattern.
std::vector - saves the object in the game (the moving, the static)


Noteworthy algorithms -


Known bugs -

the score table cant be filled with hebrew names, please dont write your name in hebrew at the end of the level.

Other notes -
Using Box2d, SFML STD libaries.