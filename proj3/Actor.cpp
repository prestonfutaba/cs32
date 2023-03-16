#include "Actor.h"
#include "StudentWorld.h"
using namespace std;


// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp

void PlayerAvatar::moveLeft(double dest_x, double dest_y)
{
	if (getWorld()->canMoveLeft(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

void PlayerAvatar::moveRight(double dest_x, double dest_y)
{
	if (getWorld()->canMoveRight(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

void PlayerAvatar::moveUp(double dest_x, double dest_y)
{
	if (getWorld()->canMoveUp(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

void PlayerAvatar::moveDown(double dest_x, double dest_y)
{
	if (getWorld()->canMoveDown(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

void Baddie::moveLeft(double dest_x, double dest_y)
{
	if (getWorld()->canMoveLeft(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

void Baddie::moveRight(double dest_x, double dest_y)
{
	if (getWorld()->canMoveRight(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

void Baddie::moveUp(double dest_x, double dest_y)
{
	if (getWorld()->canMoveUp(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

void Baddie::moveDown(double dest_x, double dest_y)
{
	if (getWorld()->canMoveDown(dest_x, dest_y))
		moveTo(dest_x, dest_y);
}

bool PlayerAvatar::justChangedDir()
{
	if (getWalkDir() != getPrevDir())
		return true;
	return false;
}

void Peach::doSomething()
{
	if (whatState() == false) // waiting to roll state
	{	
		if (!canMoveForward(getWalkDir()) && getTeleported()) //invalid dir due to tp, 1a
		{
			getWorld()->givePeach()->resetTeleported();
			int randomDir = (rand() % 4) + 1; //1-4 , 1 = up 2 = right, 3 = down, 4 = left
			if (randomDir == 1)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(up);
				}
				else
					randomDir = 2 + (rand() % 3);; // get new 2-4 int if current roll is illegal
			}
			else if (randomDir == 2)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(right);
				}
				else
					randomDir = 3 + (rand() % 2); // 3-4
			}
			else if (randomDir == 3)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setPrevDir(getWalkDir());					
					setWalkDir(down);
				}
				else
					randomDir = 4;
			}
			else if (randomDir == 4)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(left);
				}
			}
			int curr_dir = getWalkDir();
			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction
		}
		
		int ch = getWorld()->getAction(1); 
		if (ch) // see if user pressed key, take key input as ch
		{
			// user hit a key during this tick!
			switch (ch)
			{
				/*
			case 1:
				moveLeft(getX() - 2, getY());
				cout << getX() << " " << getY() << endl;
				break;
			case 2:
				moveRight(getX() + 2, getY());
				cout << getX() << " " << getY() << endl;
				break;
			case 3:
				moveUp(getX(), getY() + 2);
				cout << getX() << " " << getY() << endl;
				break;
			case 4:
				moveDown(getX(), getY() - 2);
				cout << getX() << " " << getY() << endl;
				break;
				*/
			case 5: // ACTION_ROLL
				if (whatState() == 0)
				{
					die_roll = 1 + (rand() % 10); // 1 to 10 roll
					ticks_to_move = die_roll * 8;
					setRolled(1); // 
					toWalkingState(); // PlayerAvatar in walking state
					incrementTimesRolled();
					/*if (ticks_to_move == 0)
					{
						toWaitingState(); // avatar is waiting to roll
						//getWorld()->coinAdder();
					}
					*/
				}
				break;
			case 6: // if ACTION_FIRE, spawn in vortex tile next, play sound, take vortex away
				if (getProjectiles() > 0)
				{
					//spawn in new vortex then 
					int curr_dir = getWalkDir();
					int spawn_x = getX();
					int spawn_y = getY();
					if (curr_dir == right)
					{
						spawn_x += 16;
					}
					if (curr_dir == left)
					{
						spawn_x -= 16;
					}
					if (curr_dir == up)
					{
						spawn_y += 16;
					}
					if (curr_dir == down)
					{
						spawn_y -= 16;
					}
					getWorld()->spawnVortex(spawn_x, spawn_y, curr_dir);
					getWorld()->playSound(SOUND_PLAYER_FIRE);
					takeProjectile();
				}
				break;
			default:
				return; //return if other action
			}
		}
	}

	//if (whatState() == true && !isAtFork(getWalkDir()) && timesRolled > 1)
	if (whatState() == true) // in walking state
	{
		// check if on top of directional square
		int tempDirectional = getWorld()->isOnDirectional(this);
		if (tempDirectional != 69)
		{
			setWalkDir(tempDirectional);
			int curr_dir = getWalkDir();
			if (getWalkDir() == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction

			if (curr_dir == right)
				moveTo(getX() + 2, getY());
			if (curr_dir == left)
				moveTo(getX() - 2, getY());
			if (curr_dir == up)
				moveTo(getX(), getY() + 2);
			if (curr_dir == down)
				moveTo(getX(), getY() - 2);

			ticks_to_move--;
			if (ticks_to_move == 0)
			{
				toWaitingState();
			}

		}
		if (!isAtFork(getWalkDir())) 
		{

			int curr_dir = getWalkDir();
			
			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction


			if (curr_dir == right)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					moveRight(getX() + 2, getY());
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(down);
				}
			}

			if (curr_dir == up)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					moveUp(getX(), getY() + 2);
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(left);					
				}
			}

			if (curr_dir == left)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					moveLeft(getX() - 2, getY());
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(down);
				}
			}

			if (curr_dir == down)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					moveDown(getX(), getY() - 2);
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(left);
				}
			}

			if (ticks_to_move == 0)
			{
				toWaitingState();
			}

		}
		/*
		else if (canMoveForward(getWalkDir()))
		{
			int temp = getWalkDir();
			if (temp == right)
			{
				moveRight(getX() + 2, getY());
				ticks_to_move--;
			}
			else if (temp == left)
			{
				moveLeft(getX() - 2, getY());
				ticks_to_move--;
			}
			else if (temp == up)
			{
				moveUp(getX(), getY() + 2);
				ticks_to_move--;
			}
			else if (temp == down)
			{
				moveDown(getX(), getY() - 2);
				ticks_to_move--;
			}

			if (ticks_to_move == 0)
			{
				toWaitingState();
			}
		}
		*/

		//else if (isAtFork(getWalkDir()))
		if (isAtFork(getWalkDir()))
		{
			int ch2 = getWorld()->getAction(1);
			if (ch2)
			{
				switch (ch2)
				{
				case 1:
					setPrevDir(getWalkDir());
					setWalkDir(left);
					moveLeft(getX() - 2, getY());
					ticks_to_move--;
					break;
				case 2:
					setPrevDir(getWalkDir());
					setWalkDir(right);
					moveRight(getX() + 2, getY());
					ticks_to_move--;
					break;
				case 3:
					setPrevDir(getWalkDir());
					setWalkDir(up);
					moveUp(getX(), getY() + 2);
					ticks_to_move--;
					break;
				case 4:
					setPrevDir(getWalkDir());
					setWalkDir(down);
					moveDown(getX(), getY() - 2);
					ticks_to_move--;
					break;

				default:
					break;
				}
			}
		}
	}

	return;
}

void Yoshi::doSomething()
{
	if (whatState() == false) // waiting to roll state
	{
		if (!canMoveForward(getWalkDir()) && getTeleported()) //invalid dir due to tp, 1a
		{
			getWorld()->givePeach()->resetTeleported();
			int randomDir = (rand() % 4) + 1; //1-4 , 1 = up 2 = right, 3 = down, 4 = left
			if (randomDir == 1)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(up);
				}
				else
					randomDir = 2 + (rand() % 3);; // get new 2-4 int if current roll is illegal
			}
			else if (randomDir == 2)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(right);
				}
				else
					randomDir = 3 + (rand() % 2); // 3-4
			}
			else if (randomDir == 3)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(down);
				}
				else
					randomDir = 4;
			}
			else if (randomDir == 4)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(left);
				}
			}
			int curr_dir = getWalkDir();
			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction
		}

		int ch = getWorld()->getAction(2);
		if (ch) // see if user pressed key, take key input as ch
		{
			// user hit a key during this tick!
			switch (ch)
			{
				/*
			case 1:
				moveLeft(getX() - 2, getY());
				cout << getX() << " " << getY() << endl;
				break;
			case 2:
				moveRight(getX() + 2, getY());
				cout << getX() << " " << getY() << endl;
				break;
			case 3:
				moveUp(getX(), getY() + 2);
				cout << getX() << " " << getY() << endl;
				break;
			case 4:
				moveDown(getX(), getY() - 2);
				cout << getX() << " " << getY() << endl;
				break;
				*/
			case 5: // ACTION_ROLL
				if (whatState() == 0)
				{
					die_roll = 1 + (rand() % 10); // 1 to 10 roll
					ticks_to_move = die_roll * 8;
					setRolled(1); // 
					toWalkingState(); // PlayerAvatar in walking state
					incrementTimesRolled();
					/*if (ticks_to_move == 0)
					{
						toWaitingState(); // avatar is waiting to roll
						//getWorld()->coinAdder();
					}
					*/
				}
				break;
			case 6: // if ACTION_FIRE, spawn in vortex tile next, play sound, take vortex away
				if (getProjectiles() > 0)
				{
					//spawn in new vortex then 
					int curr_dir = getWalkDir();
					int spawn_x = getX();
					int spawn_y = getY();
					if (curr_dir == right)
					{
						spawn_x += 16;
					}
					if (curr_dir == left)
					{
						spawn_x -= 16;
					}
					if (curr_dir == up)
					{
						spawn_y += 16;
					}
					if (curr_dir == down)
					{
						spawn_y -= 16;
					}
					getWorld()->spawnVortex(spawn_x, spawn_y, curr_dir);
					getWorld()->playSound(SOUND_PLAYER_FIRE);
					takeProjectile();
				}
				break;
			default:
				return; //return if other action
			}
		}
	}

	//if (whatState() == true && !isAtFork(getWalkDir()) && timesRolled > 1)
	if (whatState() == true) // in walking state
	{
		// check if on top of directional square
		int tempDirectional = getWorld()->isOnDirectional(this);
		if (tempDirectional != 69)
		{
			setWalkDir(tempDirectional);
			int curr_dir = getWalkDir();
			if (getWalkDir() == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction

			if (curr_dir == right)
				moveTo(getX() + 2, getY());
			if (curr_dir == left)
				moveTo(getX() - 2, getY());
			if (curr_dir == up)
				moveTo(getX(), getY() + 2);
			if (curr_dir == down)
				moveTo(getX(), getY() - 2);

			ticks_to_move--;
			if (ticks_to_move == 0)
			{
				toWaitingState();
			}

		}
		if (!isAtFork(getWalkDir()))
		{
			int curr_dir = getWalkDir();

			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction


			if (curr_dir == right)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					moveRight(getX() + 2, getY());
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(down);
				}
			}

			if (curr_dir == up)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					moveUp(getX(), getY() + 2);
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(left);
				}
			}

			if (curr_dir == left)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					moveLeft(getX() - 2, getY());
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setPrevDir(getWalkDir());
					setWalkDir(down);
				}
			}

			if (curr_dir == down)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					moveDown(getX(), getY() - 2);
					setPrevDir(getWalkDir());
					ticks_to_move--;
				}
				else if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setPrevDir(getWalkDir());
					setWalkDir(left);
				}
			}

			if (ticks_to_move == 0)
			{
				toWaitingState();
			}

		}
		/*
		else if (canMoveForward(getWalkDir()))
		{
			int temp = getWalkDir();
			if (temp == right)
			{
				moveRight(getX() + 2, getY());
				ticks_to_move--;
			}
			else if (temp == left)
			{
				moveLeft(getX() - 2, getY());
				ticks_to_move--;
			}
			else if (temp == up)
			{
				moveUp(getX(), getY() + 2);
				ticks_to_move--;
			}
			else if (temp == down)
			{
				moveDown(getX(), getY() - 2);
				ticks_to_move--;
			}

			if (ticks_to_move == 0)
			{
				toWaitingState();
			}
		}
		*/

		//else if (isAtFork(getWalkDir()))
		if (isAtFork(getWalkDir()))
		{
			int ch2 = getWorld()->getAction(2);
			if (ch2)
			{
				switch (ch2)
				{
				case 1:
					setPrevDir(getWalkDir());
					setWalkDir(left);
					moveLeft(getX() - 2, getY());
					ticks_to_move--;
					break;
				case 2:
					setPrevDir(getWalkDir());
					setWalkDir(right);
					moveRight(getX() + 2, getY());
					ticks_to_move--;
					break;
				case 3:
					setPrevDir(getWalkDir());
					setWalkDir(up);
					moveUp(getX(), getY() + 2);
					ticks_to_move--;
					break;
				case 4:
					setPrevDir(getWalkDir());
					setWalkDir(down);
					moveDown(getX(), getY() - 2);
					ticks_to_move--;
					break;

				default:
					break;
				}
			}
		}
	}

	return;
}

void BlueCoinSquare::doSomething()
{
	if (isAlive() == false)
		return;

	if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach() && !getWorld()->givePeach()->whatState())
	{
		if (getWorld()->givePeach()->hasRolledYet())
		{
			getWorld()->coinAdderPeach();
			setActivePeach(0);
			getWorld()->playSound(SOUND_GIVE_COIN);
		}
	}
	if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
		setActivePeach(1);

	if (getWorld()->giveYoshi()->getX() == getX() && getWorld()->giveYoshi()->getY() == getY() && isActiveYoshi() && !getWorld()->giveYoshi()->whatState())
	{
		if (getWorld()->giveYoshi()->hasRolledYet())
		{
			getWorld()->coinAdderYoshi();
			setActiveYoshi(0);
			getWorld()->playSound(SOUND_GIVE_COIN);
		}
	}
	if (!isActiveYoshi() && getWorld()->giveYoshi()->getX() != getX() && getWorld()->giveYoshi()->getY() != getY())
		setActiveYoshi(1);

}

void PlayerAvatar::incrementCoinss(int n)
{
	coins = coins + n;
}

void PlayerAvatar::decrementCoinss(int n)
{
	coins = coins - n;
}

void RedCoinSquare::doSomething()
{
	if (isAlive() == false)
		return;

	if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach() && !getWorld()->givePeach()->whatState())
	{
		if (getWorld()->givePeach()->hasRolledYet())
		{
			getWorld()->coinAdderPeach(); // subtract 3 not add 3, make new func later
			setActivePeach(0);
			getWorld()->playSound(SOUND_TAKE_COIN);

		}
	}
	if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
		setActivePeach(1);

}

void CoinSquare::doSomething()
{
	if (isAlive() == false)
		return;
}

void Bowser::doSomething()
{
	if (getHit() == 1)
	{
		bool teleported = 0;
		while (teleported == 0)
		{
			int randX = (rand() % 15) * 16;
			int randY = (rand() % 15) * 16;
			if (getWorld()->canTeleportHere(randX, randY))
			{
				moveTo(randX, randY);
				teleported = 1;
				setWalkDir(right);
				setDirection(right);
				toPausedState();
				setPauseCounter();
				resetHit();
			}
		}
	}

	int squares_to_move;
	if (!whatState()) // in paused
	{
		if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach() && !getWorld()->givePeach()->whatState())
		{
			if (getWorld()->givePeach()->hasRolledYet())
			{
				//
				int random = (rand() % 2);
				if (random % 2 == 0)
				{
					getWorld()->takePeachCoins();
					getWorld()->playSound(SOUND_BOWSER_ACTIVATE);
				}
				setActivePeach(0);
			}
		}
		if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
			setActivePeach(1);

		decrementPause();
		if (getPauseCounter() == 0)
		{
			squares_to_move = 1 + (rand() % 10); // 1 to 10 roll
			ticks_to_move = squares_to_move * 8;
			// pick new random walk direction
			int randomDir = (rand() % 4) + 1; //1-4 , 1 = up 2 = right, 3 = down, 4 = left
			if (randomDir == 1)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
					setWalkDir(up);
				else
					randomDir = 2 + (rand() % 3);; // get new 2-4 int if current roll is illegal
			}
			else if (randomDir == 2)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
					setWalkDir(right);
				else
					randomDir = 3 + (rand() % 2); // 3-4
			}
			else if (randomDir == 3)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
					setWalkDir(down);
				else
					randomDir = 4;
			}
			else if (randomDir == 4)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
					setWalkDir(left);
			}
			int curr_dir = getWalkDir();
			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction

			toWalkingState();
		}
	}
	if (whatState()) // in walking state
	{
		if (getWorld()->isDirectlyOn(this) && isAtFork(getWalkDir()))
		{
			// pick new random walk direction
			int randomDir = (rand() % 4) + 1; //1-4 , 1 = up 2 = right, 3 = down, 4 = left
			if (randomDir == 1)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
					setWalkDir(up);
				else
					randomDir = (rand() % 4) + 1; // get new 1-4 int if current roll is illegal
			}
			else if (randomDir == 2)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
					setWalkDir(right);
				else
					randomDir = (rand() % 4) + 1;
			}
			else if (randomDir == 3)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
					setWalkDir(down);
				else
					randomDir = (rand() % 4) + 1;
			}
			else if (randomDir == 4)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
					setWalkDir(left);
				else
					randomDir = (rand() % 4) + 1;
			}
			int curr_dir = getWalkDir();
			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction
		}
		//else if (getWorld()->isDirectlyOn(this) && !canMoveForward(getWalkDir()))
		else if (getWorld()->isDirectlyOn(this) && !canMoveForward(getWalkDir()))
		{
			int curr_dir = getWalkDir();
			if (curr_dir == right)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setWalkDir(down);
				}
			}

			if (curr_dir == up)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setWalkDir(left);
				}
			}

			if (curr_dir == left)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setWalkDir(down);
				}
			}

			if (curr_dir == down)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setWalkDir(left);
				}
			}

			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction
		}

		int curr_dir = getWalkDir();
		if (curr_dir == 180)
		{
			setDirection(left);
		}
		else
			setDirection(right); //setDirection to change sprite direction
		if (curr_dir == up)
		{
			if (getWorld()->canMoveUp(getX(), getY() + 2))
			{
				moveUp(getX(), getY() + 2);
				ticks_to_move--;
			}
		}
		else if (curr_dir == down)
		{
			if (getWorld()->canMoveDown(getX(), getY() - 2))
			{
				moveDown(getX(), getY() - 2);
				ticks_to_move--;
			}
		}
		else if (curr_dir == right)
		{
			if (getWorld()->canMoveRight(getX() + 2, getY()))
			{
				moveRight(getX() + 2, getY());
				ticks_to_move--;
			}
		}
		else if (curr_dir == left)
		{
			if (getWorld()->canMoveLeft(getX() - 2, getY()))
			{
				moveLeft(getX() - 2, getY());
				ticks_to_move--;
			}
		}

		if (ticks_to_move == 0)
		{
			toPausedState();
			setPauseCounter();
			int randomInt = (rand() % 4) + 1; //1-4 
			if (randomInt == 1) // 1 out of 4, 25% chance
			{
				if (getWorld()->isOnBlue(this))
				{
					getWorld()->BowserSpecial(getX(), getY(), this);
					getWorld()->playSound(SOUND_DROPPING_SQUARE_CREATED);
				}
			}
		}

	}
	return;
}

bool Baddie::isAtFork(int dir)
{
	int numDirs = 0;
	int oppDir = 0;
	if (dir == 0)
		oppDir = 180;
	else if (dir == 90)
		oppDir = 270;
	else if (dir == 180)
		oppDir = 0;
	else if (dir == 270)
		oppDir = 90;


	if (getWorld()->canMoveRight(getX() + 2, getY()) && oppDir != 0)
		numDirs++;

	if (getWorld()->canMoveLeft(getX() - 2, getY()) && oppDir != 180)
		numDirs++;

	if (getWorld()->canMoveUp(getX(), getY() + 2) && oppDir != 90)
		numDirs++;

	if (getWorld()->canMoveDown(getX(), getY() - 2) && oppDir != 270)
		numDirs++;
	
	if (numDirs > 1)
		return true;
	return false;
}

bool PlayerAvatar::isAtFork(int dir)
{
	if (getTimesRolled() <= 1 || justChangedDir())
	{
		return false;
	}

	int numDirs = 0;
	int oppDir = 0;
	if (dir == 0)
		oppDir = 180;
	else if (dir == 90)
		oppDir = 270;
	else if (dir == 180)
		oppDir = 0;
	else if (dir == 270)
		oppDir = 90;

	if (getWorld()->canMoveRight(getX() + 2, getY()) && oppDir != 0)
	{
		numDirs++;
	}
	if (getWorld()->canMoveLeft(getX() - 2, getY()) && oppDir != 180)
	{
		numDirs++;
	}
	if (getWorld()->canMoveUp(getX(), getY() + 2) && oppDir != 90)
	{
		numDirs++;
	}
	if (getWorld()->canMoveDown(getX(), getY() - 2) && oppDir != 270)
	{
		numDirs++;
	}
	if (numDirs > 1)
		return true;
	return false;
}

bool Baddie::canMoveForward(int dir)
{
	if (dir == up)
	{
		if (getWorld()->canMoveUp(getX(), getY() + 2))
			return true;
	}
	if (dir == down)
	{
		if (getWorld()->canMoveDown(getX(), getY() - 2))
			return true;
	}
	if (dir == right)
	{
		if (getWorld()->canMoveRight(getX() + 2, getY()))
			return true;
	}
	if (dir == left)
	{
		if (getWorld()->canMoveLeft(getX() - 2, getY()))
			return true;
	}
	return false;
}

bool PlayerAvatar::canMoveForward(int dir)
{
	if (dir == up)
	{
		if (getWorld()->canMoveUp(getX(), getY() + 2))
			return true;
	}
	if (dir == down)
	{
		if (getWorld()->canMoveDown(getX(), getY() - 2))
			return true;
	}
	if (dir == right)
	{
		if (getWorld()->canMoveRight(getX() + 2, getY()))
			return true;
	}
	if (dir == left)
	{
		if (getWorld()->canMoveLeft(getX() - 2, getY()))
			return true;
	}
	return false;
}

void Boo::doSomething()
{
	if (getHit() == 1)
	{
		bool teleported = 0;
		while (teleported == 0)
		{
			int randX = (rand() % 15) * 16;
			int randY = (rand() % 15) * 16;
			if (getWorld()->canTeleportHere(randX, randY))
			{
				moveTo(randX, randY);
				teleported = 1;
				setWalkDir(right);
				setDirection(right);
				toPausedState();
				setPauseCounter();
				resetHit();
			}
		}
	}
	int squares_to_move;
	if (!whatState()) // in paused
	{
		if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach() && !getWorld()->givePeach()->whatState())
		{
			if (getWorld()->givePeach()->hasRolledYet())
			{
				int random = (rand() % 2);
				if (random % 2 == 0)
				{
					getWorld()->switchCoins();
					getWorld()->playSound(SOUND_BOO_ACTIVATE);
				}
				else
				{
					getWorld()->switchStars();
					getWorld()->playSound(SOUND_BOO_ACTIVATE);
				}
				setActivePeach(0);
			}
		}
		if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
			setActivePeach(1);

		decrementPause();
		if (getPauseCounter() == 0)
		{
			squares_to_move = 1 + (rand() % 10); // 1 to 10 roll
			ticks_to_move = squares_to_move * 8;
			// pick new random walk direction
			int randomDir = (rand() % 4) + 1; //1-4 , 1 = up 2 = right, 3 = down, 4 = left
			if (randomDir == 1)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
					setWalkDir(up);
				else
					randomDir = 2 + (rand() % 3);; // get new 2-4 int if current roll is illegal
			}
			else if (randomDir == 2)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
					setWalkDir(right);
				else
					randomDir = 3 + (rand() % 2); // 3-4
			}
			else if (randomDir == 3)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
					setWalkDir(down);
				else
					randomDir = 4;
			}
			else if (randomDir == 4)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
					setWalkDir(left);
			}
			int curr_dir = getWalkDir();
			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction

			toWalkingState();
		}
	}
	if (whatState()) // in walking state
	{
		if (getWorld()->isDirectlyOn(this) && isAtFork(getWalkDir()))
		{
			// pick new random walk direction
			int randomDir = (rand() % 4) + 1; //1-4 , 1 = up 2 = right, 3 = down, 4 = left
			if (randomDir == 1)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
					setWalkDir(up);
				else
					randomDir = (rand() % 4) + 1; // get new 1-4 int if current roll is illegal
			}
			else if (randomDir == 2)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
					setWalkDir(right);
				else
					randomDir = (rand() % 4) + 1;
			}
			else if (randomDir == 3)
			{
				if (getWorld()->canMoveDown(getX(), getY() - 2))
					setWalkDir(down);
				else
					randomDir = (rand() % 4) + 1;
			}
			else if (randomDir == 4)
			{
				if (getWorld()->canMoveLeft(getX() - 2, getY()))
					setWalkDir(left);
				else
					randomDir = (rand() % 4) + 1;
			}
			int curr_dir = getWalkDir();
			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction
		}
		//else if (getWorld()->isDirectlyOn(this) && !canMoveForward(getWalkDir()))
		else if (getWorld()->isDirectlyOn(this) && !canMoveForward(getWalkDir()))
		{
			int curr_dir = getWalkDir();
			if (curr_dir == right)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setWalkDir(down);
				}
			}

			if (curr_dir == up)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setWalkDir(left);
				}
			}

			if (curr_dir == left)
			{
				if (getWorld()->canMoveUp(getX(), getY() + 2))
				{
					setWalkDir(up);
				}
				else if (getWorld()->canMoveDown(getX(), getY() - 2))
				{
					setWalkDir(down);
				}
			}

			if (curr_dir == down)
			{
				if (getWorld()->canMoveRight(getX() + 2, getY()))
				{
					setWalkDir(right);
				}
				else if (getWorld()->canMoveLeft(getX() - 2, getY()))
				{
					setWalkDir(left);
				}
			}

			if (curr_dir == 180)
			{
				setDirection(left);
			}
			else
				setDirection(right); //setDirection to change sprite direction
		}

		int curr_dir = getWalkDir();
		if (curr_dir == 180)
		{
			setDirection(left);
		}
		else
			setDirection(right); //setDirection to change sprite direction
		if (curr_dir == up)
		{
			if (getWorld()->canMoveUp(getX(), getY() + 2))
			{
				moveUp(getX(), getY() + 2);
				ticks_to_move--;
			}
		}
		else if (curr_dir == down)
		{
			if (getWorld()->canMoveDown(getX(), getY() - 2))
			{
				moveDown(getX(), getY() - 2);
				ticks_to_move--;
			}
		}
		else if (curr_dir == right)
		{
			if (getWorld()->canMoveRight(getX() + 2, getY()))
			{
				moveRight(getX() + 2, getY());
				ticks_to_move--;
			}
		}
		else if (curr_dir == left)
		{
			if (getWorld()->canMoveLeft(getX() - 2, getY()))
			{
				moveLeft(getX() - 2, getY());
				ticks_to_move--;
			}
		}

		if (ticks_to_move == 0)
		{
			toPausedState();
			setPauseCounter();
		}

	}
	return;
}

void StarSquare::doSomething()	
{
	if (isAlive() == false)
		return;

	if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach())
	{
		if (getWorld()->givePeach()->hasRolledYet())
		{
			if (getWorld()->givePeach()->getCoins() >= 20)
			{
				getWorld()->buyPeachStar(); // subtract 3 not add 3, make new func later
				setActivePeach(0);
				getWorld()->playSound(SOUND_GIVE_STAR);
			}
		}
	}
	if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
		setActivePeach(1);

	if (getWorld()->giveYoshi()->getX() == getX() && getWorld()->giveYoshi()->getY() == getY() && isActiveYoshi())
	{
		if (getWorld()->giveYoshi()->hasRolledYet())
		{
			if (getWorld()->giveYoshi()->getCoins() >= 20)
			{
				getWorld()->buyYoshiStar(); // subtract 3 not add 3, make new func later
				setActiveYoshi(0);
				getWorld()->playSound(SOUND_GIVE_STAR);
			}
		}
	}
	if (!isActiveYoshi() && getWorld()->giveYoshi()->getX() != getX() && getWorld()->giveYoshi()->getY() != getY())
		setActiveYoshi(1);
	return;
}

void PlayerAvatar::buyStar()
{
	coins -= 20;
	stars += 1;
}

void DirectionalSquare::doSomething()
{
	if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach())
	{
		if (getWorld()->givePeach()->hasRolledYet())
		{
			getWorld()->givePeach()->setWalkDir(getForcingDir());
		}
	}
	if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
		setActivePeach(1);

	if (getWorld()->giveYoshi()->getX() == getX() && getWorld()->giveYoshi()->getY() == getY() && isActiveYoshi())
	{
		if (getWorld()->giveYoshi()->hasRolledYet())
		{
			getWorld()->giveYoshi()->setWalkDir(getForcingDir());
		}
	}
	if (!isActivePeach() && getWorld()->giveYoshi()->getX() != getX() && getWorld()->giveYoshi()->getY() != getY())
		setActiveYoshi(1);
}

void BankSquare::doSomething()
{
	if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach())
	{
		if (getWorld()->givePeach()->hasRolledYet() && !getWorld()->givePeach()->whatState()) // didn't spawn on square and is waiting to roll and landed on square	
		{
			int temp = getWorld()->getBankBalance();
			getWorld()->givePeachCoin(temp);
			getWorld()->setBank(0);
			setActivePeach(0);
			getWorld()->playSound(SOUND_WITHDRAW_BANK);
		}

		if (getWorld()->givePeach()->hasRolledYet() && getWorld()->givePeach()->whatState()) // didn't spawn on square and is walking over square
		{
			if (getWorld()->givePeach()->getCoins() >= 5)
			{
				getWorld()->addToBank(5);
				getWorld()->givePeach()->decrementCoinss(5);
				setActivePeach(0);
				getWorld()->playSound(SOUND_DEPOSIT_BANK);
			}
			else if (getWorld()->givePeach()->getCoins() < 5)
			{
				int temp = getWorld()->givePeach()->getCoins();
				getWorld()->addToBank(temp);
				getWorld()->givePeach()->decrementCoinss(temp);
				setActivePeach(0);
				getWorld()->playSound(SOUND_DEPOSIT_BANK);
			}
		}

	}
	if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY()) // reset ActivePeach
		setActivePeach(1);

	if (getWorld()->giveYoshi()->getX() == getX() && getWorld()->giveYoshi()->getY() == getY() && isActiveYoshi())
	{
		if (getWorld()->giveYoshi()->hasRolledYet() && !getWorld()->giveYoshi()->whatState()) // didn't spawn on square and is waiting to roll and landed on square	
		{
			int temp = getWorld()->getBankBalance();
			getWorld()->giveYoshiCoin(temp);
			getWorld()->setBank(0);
			setActiveYoshi(0);
			getWorld()->playSound(SOUND_WITHDRAW_BANK);
		}

		if (getWorld()->giveYoshi()->hasRolledYet() && getWorld()->giveYoshi()->whatState()) // didn't spawn on square and is walking over square
		{
			if (getWorld()->giveYoshi()->getCoins() >= 5)
			{
				getWorld()->addToBank(5);
				getWorld()->giveYoshi()->decrementCoinss(5);
				setActiveYoshi(0);
				getWorld()->playSound(SOUND_DEPOSIT_BANK);
			}
			else if (getWorld()->giveYoshi()->getCoins() < 5)
			{
				int temp = getWorld()->giveYoshi()->getCoins();
				getWorld()->addToBank(temp);
				getWorld()->giveYoshi()->decrementCoinss(temp);
				setActiveYoshi(0);
				getWorld()->playSound(SOUND_DEPOSIT_BANK);
			}
		}

	}
	if (!isActiveYoshi() && getWorld()->giveYoshi()->getX() != getX() && getWorld()->giveYoshi()->getY() != getY()) // reset ActiveYoshi
		setActiveYoshi(1);



	return;
}

void EventSquare::doSomething()
{
	if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach() && !getWorld()->givePeach()->whatState())
	{
		if (getWorld()->givePeach()->hasRolledYet())
		{
			int random = (rand() % 3) + 1;
			if (random == 1) // option 1, teleport
			{
				bool teleported = 0;
				while (teleported == 0)
				{
					int randX = (rand() % 15) * 16;
					int randY = (rand() % 15) * 16;
					if (getWorld()->canTeleportHere(randX, randY))
					{
						getWorld()->givePeach()->moveTo(randX, randY);
						getWorld()->playSound(SOUND_PLAYER_TELEPORT);
						setActivePeach(0);
						teleported = 1;
						getWorld()->givePeach()->wasTeleported();
					}
				}
			}
			else if (random == 2) // option 2, swap players
			{
				getWorld()->switchX();
				getWorld()->switchY();
				getWorld()->switchTicks();
				getWorld()->switchWalkDir();
				getWorld()->switchState();
				getWorld()->switchTicks();
				getWorld()->switchWalkDir();
				getWorld()->switchSpriteDir();
				getWorld()->switchState();
				setActivePeach(0);
				setActiveYoshi(0);
				getWorld()->givePeach()->setRolled(0);
				getWorld()->giveYoshi()->setRolled(0);
				getWorld()->playSound(SOUND_PLAYER_TELEPORT);
			}
			else if (random == 3) // option 3, give vortex
			{
				if (getWorld()->givePeach()->getProjectiles() == 0)
				{
					getWorld()->givePeach()->giveProjectile();
					setActivePeach(0);
					getWorld()->playSound(SOUND_GIVE_VORTEX);
				}
				// else case, don't do anything bc can have 1 projectile max
			}

		}
	}
	if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
		setActivePeach(1);

	if (getWorld()->giveYoshi()->getX() == getX() && getWorld()->giveYoshi()->getY() == getY() && isActiveYoshi() && !getWorld()->giveYoshi()->whatState())
	{
		if (getWorld()->giveYoshi()->hasRolledYet())
		{
			int random = (rand() % 3) + 1;
			if (random == 1) // option 1, teleport
			{
				bool teleported = 0;
				while (teleported == 0)
				{
					int randX = (rand() % 15) * 16;
					int randY = (rand() % 15) * 16;
					if (getWorld()->canTeleportHere(randX, randY))
					{
						getWorld()->giveYoshi()->moveTo(randX, randY);
						getWorld()->playSound(SOUND_PLAYER_TELEPORT);
						setActiveYoshi(0);
						teleported = 1;
						getWorld()->giveYoshi()->wasTeleported();
					}
				}
			}
			else if (random == 2) // option 2, swap players
			{
				getWorld()->switchX();
				getWorld()->switchY();
				getWorld()->switchTicks();
				getWorld()->switchWalkDir();
				getWorld()->switchState();
				getWorld()->switchTicks();
				getWorld()->switchWalkDir();
				getWorld()->switchSpriteDir();
				getWorld()->switchState();
				setActiveYoshi(0);
				setActivePeach(0);
				getWorld()->givePeach()->setRolled(0);
				getWorld()->giveYoshi()->setRolled(0);
				getWorld()->playSound(SOUND_PLAYER_TELEPORT);
			}
			else if (random == 3) // option 3, give vortex
			{
				if (getWorld()->giveYoshi()->getProjectiles() == 0)
				{
					getWorld()->giveYoshi()->giveProjectile();
					setActiveYoshi(0);
					getWorld()->playSound(SOUND_GIVE_VORTEX);
				}
				// else case, don't do anything bc can have 1 projectile max
			}

		}
	}
	if (!isActiveYoshi() && getWorld()->giveYoshi()->getX() != getX() && getWorld()->giveYoshi()->getY() != getY())
		setActiveYoshi(1);




	return;
}

void DroppingSquare::doSomething()
{
	if (getWorld()->givePeach()->getX() == getX() && getWorld()->givePeach()->getY() == getY() && isActivePeach() && !getWorld()->givePeach()->whatState())
	{
		if (getWorld()->givePeach()->hasRolledYet())
		{
			getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
			int random = (rand() % 2) + 1;
			if (random == 1) // option 1, deduct 10 coins
			{
				if (getWorld()->givePeach()->getCoins() >= 10)
				{
					getWorld()->givePeach()->decrementCoinss(10);
					setActivePeach(0);
				}
				else if (getWorld()->givePeach()->getCoins() < 10)
				{
					int temp = getWorld()->givePeach()->getCoins();
					getWorld()->givePeach()->decrementCoinss(temp);
					setActivePeach(0);
				}
			}
			else if (random == 2) // option 2, deduct star
			{
				if (getWorld()->givePeach()->getStars() >= 1)
				{
					getWorld()->givePeach()->decrementStars(1);
					setActivePeach(0);
				}
			}
		}
	}
	if (!isActivePeach() && getWorld()->givePeach()->getX() != getX() && getWorld()->givePeach()->getY() != getY())
		setActivePeach(1);

	if (getWorld()->giveYoshi()->getX() == getX() && getWorld()->giveYoshi()->getY() == getY() && isActiveYoshi() && !getWorld()->giveYoshi()->whatState())
	{
		if (getWorld()->giveYoshi()->hasRolledYet())
		{
			getWorld()->playSound(SOUND_DROPPING_SQUARE_ACTIVATE);
			int random = (rand() % 2) + 1;
			if (random == 1) // option 1, deduct 10 coins
			{
				if (getWorld()->giveYoshi()->getCoins() >= 10)
				{
					getWorld()->giveYoshi()->decrementCoinss(10);
					setActiveYoshi(0);
				}
				else if (getWorld()->giveYoshi()->getCoins() < 10)
				{
					int temp = getWorld()->giveYoshi()->getCoins();
					getWorld()->giveYoshi()->decrementCoinss(temp);
					setActiveYoshi(0);
				}
			}
			else if (random == 2) // option 2, deduct star
			{
				if (getWorld()->giveYoshi()->getStars() >= 1)
				{
					getWorld()->giveYoshi()->decrementStars(1);
					setActiveYoshi(0);
				}
			}
		}
	}
	if (!isActiveYoshi() && getWorld()->giveYoshi()->getX() != getX() && getWorld()->giveYoshi()->getY() != getY())
		setActiveYoshi(1);



	return;
}

void Vortex::doSomething()
{
	if (getVortexState() == 0)
		return;
	
	int curr_dir = shootDir;

	if (curr_dir == right)
		moveTo(getX() + 2, getY());
	if (curr_dir == left)
		moveTo(getX() - 2, getY());
	if (curr_dir == up)
		moveTo(getX(), getY() + 2);
	if (curr_dir == down)
		moveTo(getX(), getY() - 2);
	
	if (getX() > 255 || getY() > 255 || getX() < 0 || getY() < 0) // check if vortex leaves boundaries of screen
	{
		getWorld()->destroyVortex(this);
		return;
	}

	//if (getWorld()->doesVortexOverlap(this) == 1)
	//	cout << "overlaps!";
	
	if (getWorld()->doesVortexOverlap(this))
	{
		Actor* tempActor = getWorld()->vortexOverlap(this);
		if (tempActor != nullptr)
		{
			tempActor->setHit(); // tell object it has been impacted
			//killVortex();
			getWorld()->playSound(SOUND_HIT_BY_VORTEX);
			getWorld()->destroyVortex(this);
			return;
		}
	}
	
	

	return;
}
