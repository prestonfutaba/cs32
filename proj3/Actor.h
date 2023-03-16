#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include <cstdlib>

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class StudentWorld;


class Actor : public GraphObject {
public:
	Actor(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size) :
		GraphObject(imageID, startX, startY, dir, depth, size),
		m_world(world) {};

	virtual void doSomething() = 0;
	StudentWorld* getWorld() { return m_world; };
	virtual bool addsCoins() { return 0; };
	virtual int getAmountToAdd() { return 0; };
	virtual int isImpactable() { return 0; };
	virtual int isSteppable() { return 0; };
	virtual bool canAddThreeCoins() { return 0; };
	virtual bool canTakeThreeCoins() { return 0; };
	bool getHit() { return wasHit; };
	void resetHit() { wasHit = 0; };
	void setHit() { wasHit = 1; };


private:
	StudentWorld* m_world;
	bool wasHit = 0;

};

class PlayerAvatar : public Actor {
public:
	PlayerAvatar(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size, int walkDir) :
		Actor(world, imageID, startX, startY, dir, depth, size),
		walkDirection(walkDir),
		m_State(0),
		coins(0), stars(0), projectiles(0) {};

	bool whatState() { return m_State; };
	void toWaitingState() { m_State = 0; };
	void toWalkingState() { m_State = 1; };
	void setState(int n) { m_State = n; };


	void moveLeft(double x, double y);
	void moveRight(double x, double y);
	void moveUp(double x, double y);
	void moveDown(double x, double y);
	int getWalkDir() { return walkDirection; };
	void setWalkDir(int direction) { walkDirection = direction; };
	bool hasRolledYet() { return hasRolled; };
	void setRolled(int x) { hasRolled = x; };

	void incrementCoins(int n) { coins += n; };
	virtual int getCoins() { return coins; };
	virtual int getStars() { return stars; };
	virtual int getProjectiles() { return projectiles; };
	void incrementCoinss(int n);
	void decrementCoinss(int n);
	void buyStar();
	void loseAllCoins() { coins = 0; };
	void setCoins(int n) { coins = n; };
	void setStars(int n) { stars = n; };
	void decrementStars(int n) { stars = stars - n; };
	void giveProjectile() { projectiles = projectiles + 1; };
	void takeProjectile() { projectiles = projectiles - 1; };


	bool isAtFork(int dir);
	bool canMoveForward(int dir);
	bool getTeleported() { return teleported; };
	void wasTeleported() { teleported = 1; };
	void resetTeleported() { teleported = 0; };
	int getTimesRolled() { return timesRolled; };
	void incrementTimesRolled() { timesRolled++; };

	int getPrevDir() { return prevDirection; };
	void setPrevDir(int direction) { prevDirection = direction; };

	bool justChangedDir();

private:
	bool m_State; //0 for waiting to roll, 1 for walking state
	int walkDirection;
	bool hasRolled = 0; //
	int coins, stars, projectiles;
	bool teleported = 0;
	int timesRolled = 0;
	int prevDirection = 0;

};

class Peach : public PlayerAvatar {
public:
	Peach(StudentWorld* world, int level_x, int level_y) :
		PlayerAvatar(world, IID_PEACH, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 0, 1.0, right),
		ticks_to_move(0), die_roll(0) {};

	virtual void doSomething();
	int getTicks() { return ticks_to_move; };
	void setTicks(int n) { ticks_to_move = n; };
	int getRoll() { return die_roll; };

private:
	int ticks_to_move;
	int die_roll;
};

class Yoshi : public PlayerAvatar {
public:
	Yoshi(StudentWorld* world, int level_x, int level_y) :
		PlayerAvatar(world, IID_YOSHI, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 0, 1.0, right),
		ticks_to_move(0), die_roll(0) {};

	virtual void doSomething();
	int getTicks() { return ticks_to_move; };
	void setTicks(int n) { ticks_to_move = n; };
	int getRoll() { return die_roll; };

private:
	int ticks_to_move;
	int die_roll;
};

class Vortex : public PlayerAvatar {
public:
	Vortex(StudentWorld* world, int level_x, int level_y, int dir) :
		PlayerAvatar(world, IID_VORTEX, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 0, 1.0, right),
		ticks_to_move(0), die_roll(0), vortexState(1), shootDir(dir) {};

	virtual void doSomething();
	int getTicks() { return ticks_to_move; };
	void setTicks(int n) { ticks_to_move = n; };
	int getRoll() { return die_roll; };
	bool getVortexState() { return vortexState; };
	void killVortex() { vortexState = 0; };

private:
	int shootDir;
	int ticks_to_move;
	int die_roll;
	bool vortexState; // 1 = active, 0 is dead/inactive
};

class Baddie : public Actor {
public:
	Baddie(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size, int walkDir) :
		Actor(world, imageID, startX, startY, dir, depth, size),
		walkDirection(walkDir), PauseCounter(180),
		m_State(0) {};

	bool whatState() { return m_State; };
	void toPausedState() { m_State = 0; };
	void toWalkingState() { m_State = 1; };

	virtual bool hasPauseCounter() { return 1; };

	void moveLeft(double x, double y);
	void moveRight(double x, double y);
	void moveUp(double x, double y);
	void moveDown(double x, double y);
	int getWalkDir() { return walkDirection; };
	void setWalkDir(int direction) { walkDirection = direction; };

	virtual int isImpactable() { return 1; };
	virtual bool canKillSquares() { return 0; };

	virtual bool isActivePeach() { return activePeach; };
	virtual bool isActiveYoshi() { return activeYoshi; };
	virtual void setActivePeach(int x) { activePeach = x; };
	virtual void setActiveYoshi(int x) { activeYoshi = x; };
	
	int getPauseCounter() { return PauseCounter; };
	void setPauseCounter() { PauseCounter = 180; };
	void decrementPause() { PauseCounter -= 1; };
	bool isAtFork(int dir);
	bool canMoveForward(int dir);

private:
	bool activePeach = 1; //1 for active
	bool activeYoshi = 1; //1 for active

	bool m_State; //0 for paused, 1 for walking state
	int walkDirection;
	int PauseCounter;

};

class Bowser : public Baddie {
public:
	Bowser(StudentWorld* world, int level_x, int level_y) :
		Baddie(world, IID_BOWSER, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 0, 1.0, right),
		ticks_to_move(0) {};

	virtual void doSomething();
	virtual bool canKillSquares() { return 1; }; // Bowsers can kill squares but Boo can't 


private:
	void goTo(double x, double y);
	int ticks_to_move;
};

class Boo : public Baddie {
public:
	Boo(StudentWorld* world, int level_x, int level_y) :
		Baddie(world, IID_BOO, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 0, 1.0, right),
		ticks_to_move(0) {};

	virtual void doSomething();

private:
	void goTo(double x, double y);
	int ticks_to_move;
};

class BoardSquare : public Actor {
public:
	BoardSquare(StudentWorld* world, int imageID, int startX, int startY, int dir, int depth, double size) :
		Actor(world, imageID, startX, startY, dir, depth, size) {};

	virtual int isSteppable() { return 1; };
	virtual bool isActivePeach() { return activePeach; };
	virtual bool isActiveYoshi() { return activeYoshi; };
	virtual void setActivePeach(int x) { activePeach = x; };
	virtual void setActiveYoshi(int x) { activeYoshi = x; };


private:
	bool activePeach = 1; //1 for active
	bool activeYoshi = 1; //1 for active
};

class CoinSquare : public BoardSquare {
public:
	CoinSquare(StudentWorld* world, int imageID, double level_X, double level_Y, int dir, int depth, double size) :
		BoardSquare(world, imageID, level_X, level_Y, right, 1, 1.0),
		alive(true) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual int getAmountToAdd() { return amountCoinsToAdd; };
	virtual bool addsCoins() { return 0; };


private:
	bool alive;
	int amountCoinsToAdd;

};


class BlueCoinSquare : public CoinSquare {
public:
	BlueCoinSquare(StudentWorld* world, double level_x, double level_y) :
		CoinSquare(world, IID_BLUE_COIN_SQUARE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 1, 1.0),
		alive(true), amountCoinsToAdd(3) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual bool addsCoins() { return 1; };
	virtual bool canAddThreeCoins() { return 1; };
	virtual int getAmountToAdd() { return amountCoinsToAdd; };


private:
	bool alive;
	int amountCoinsToAdd = 3;
};

class RedCoinSquare : public CoinSquare {
public:
	RedCoinSquare(StudentWorld* world, double level_x, double level_y) :
		CoinSquare(world, IID_RED_COIN_SQUARE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 1, 1.0),
		alive(true), amountCoinsToAdd(-3) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual bool addsCoins() { return 1; };
	virtual bool canTakeThreeCoins() { return 1; };
	virtual int getAmountToAdd() { return amountCoinsToAdd; };


private:
	bool alive;
	int amountCoinsToAdd;
};

class StarSquare : public BoardSquare {
public:
	StarSquare(StudentWorld* world, double level_x, double level_y) :
		BoardSquare(world, IID_STAR_SQUARE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 1, 1.0),
		alive(true) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual bool canAddThreeCoins() { return 0; };
	bool canGiveStars() { return 1; };
	void giveStars();


private:
	bool alive;

};

class DirectionalSquare : public BoardSquare {
public:
	DirectionalSquare(StudentWorld* world, double level_x, double level_y, int dir) :
		BoardSquare(world, IID_DIR_SQUARE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, dir, 1, 1.0),
		alive(true), ForcingDir(dir) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual bool canAddThreeCoins() { return 0; };
	int getForcingDir() { return ForcingDir; };


private:
	bool alive;
	int ForcingDir;

};

class BankSquare : public BoardSquare {
public:
	BankSquare(StudentWorld* world, double level_x, double level_y) :
		BoardSquare(world, IID_BANK_SQUARE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 1, 1.0),
		alive(true) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual bool canAddThreeCoins() { return 0; };
	virtual bool deductFiveCoins() { return 1; };
	virtual bool addCoinsFromBank() { return 1; };


private:
	bool alive;

};

class EventSquare : public BoardSquare {
public:
	EventSquare(StudentWorld* world, double level_x, double level_y) :
		BoardSquare(world, IID_EVENT_SQUARE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 1, 1.0),
		alive(true) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual bool canAddThreeCoins() { return 0; };


private:
	bool alive;

};

class DroppingSquare : public BoardSquare {
public:
	DroppingSquare(StudentWorld* world, double level_x, double level_y) :
		BoardSquare(world, IID_DROPPING_SQUARE, SPRITE_WIDTH* level_x, SPRITE_HEIGHT* level_y, right, 1, 1.0),
		alive(true) {};

	virtual void doSomething();
	virtual void killSquare() { alive = false; return; };
	virtual bool isAlive() { return alive; };
	virtual bool canAddThreeCoins() { return 0; };


private:
	bool alive;

};


#endif // ACTOR_H_


