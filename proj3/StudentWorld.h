#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Board.h"
#include "Actor.h"
#include <string>
#include <vector>


// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
	StudentWorld(std::string assetPath);
	virtual int init();
	virtual int move();
	virtual void cleanUp();
	~StudentWorld();
	StudentWorld();

	void coinAdderPeach();
	void coinAdderYoshi();
	bool canMoveLeft(double x, double y);
	bool canMoveRight(double x, double y);
	bool canMoveUp(double x, double y);
	bool canMoveDown(double x, double y);

	bool isValidPos(double x, double y, Actor* me);
	bool isValidPos(double x, double y);
	bool sameSquare(double x1, double y1, double x2, double y2);
	bool sameSquarePeach(Actor* me);
	bool sameSquareYoshi(Actor* me);
	bool sameSquareActor(Actor* a, Actor* b);
	void switchCoins();
	void switchStars();
	void switchX();
	void switchY();
	void switchTicks();
	void switchWalkDir();
	void switchSpriteDir();
	void switchState();
	void switchPlayer();
	Peach* givePeach();
	Yoshi* giveYoshi();
	void givePeachCoin(int n);
	void giveYoshiCoin(int n);
	void buyPeachStar();
	void buyYoshiStar();
	void takePeachCoins();
	void takeYoshiCoins();
	bool isDirectlyOn(Actor* me);
	bool isOnBlue(Actor* me);
	void BowserSpecial(double x, double y, Actor* me);
	int numBlues();
	void addToBank(int n) { bankBalance += n; };
	int getBankBalance() { return bankBalance; };
	void setBank(int n) { bankBalance = n; };
	bool canTeleportHere(double x, double y);
	void destroyVortex(Vortex* me);
	Actor* vortexOverlap(Vortex* me);
	bool doesVortexOverlap(Vortex* me);
	void spawnVortex(double x, double y, int dir);
	int isOnDirectional(Actor* me);

private:
	Peach* m_Peach;
	Yoshi* m_Yoshi;
	std::vector<Actor*> actors;
	std::vector<Actor*> squares;
	std::vector<Vortex*> vortexes;
	std::vector<DirectionalSquare*> directionals;
	bool intersecting(double x1, double y1, double x2, double y2);
	bool intersecting(Actor* a, Actor* b);
	int bankBalance = 0;
};

#endif // STUDENTWORLD_H_


