#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath) // each StudentWorld has one Peach, we have a pointer to this Peach called m_Peach
	: GameWorld(assetPath)
{
	m_Peach = nullptr;
	m_Yoshi = nullptr;
}

int StudentWorld::init()
{
	Board bd;
	string board_file = assetPath() + "board09.txt";
	Board::LoadResult result = bd.loadBoard(board_file);

	if (result == Board::load_fail_file_not_found)
		cerr << "Could not find board01.txt data file\n";
	else if (result == Board::load_fail_bad_format)
		cerr << "Your board was improperly formatted\n";
	else if (result == Board::load_success) {
		cerr << "Successfully loaded board\n";

		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				Board::GridEntry ge = bd.getContentsOf(x, y);
				switch (ge)
				{
				case Board::blue_coin_square:
					cerr << "Location " << x << " " << y << " has a blue coin square" << endl;
					actors.push_back(new BlueCoinSquare(this, x, y));
					squares.push_back(new BlueCoinSquare(this, x, y));
					break;

				case Board::red_coin_square:
					cerr << "Location " << x << " " << y << " has a red coin square" << endl;
					actors.push_back(new RedCoinSquare(this, x, y));
					squares.push_back(new RedCoinSquare(this, x, y));

					break;

				case Board::player:
					cerr << "Location " << x << " " << y << " has a blue coin square" << endl;
					cerr << "peach and yoshi Location " << x << " " << y << endl;
					m_Peach = new Peach(this, x, y);
					m_Yoshi = new Yoshi(this, x, y);
					actors.push_back(new BlueCoinSquare(this, x, y));
					squares.push_back(new BlueCoinSquare(this, x, y));
					break;

				case Board::bowser:
					cerr << "Location " << x << " " << y << " has a Bowser" << endl;
					actors.push_back(new Bowser(this, x, y));
					actors.push_back(new BlueCoinSquare(this, x, y));
					squares.push_back(new BlueCoinSquare(this, x, y));
					break;

				case Board::boo:
					cerr << "Location " << x << " " << y << " has a Boo" << endl;
					actors.push_back(new Boo(this, x, y));
					actors.push_back(new BlueCoinSquare(this, x, y));
					squares.push_back(new BlueCoinSquare(this, x, y));
					break;

				case Board::star_square:
					cerr << "Location " << x << " " << y << " has a star square" << endl;
					actors.push_back(new StarSquare(this, x, y));
					squares.push_back(new StarSquare(this, x, y));
					break;

				case Board::down_dir_square:
					cerr << "Location " << x << " " << y << " has a down directional square" << endl;
					actors.push_back(new DirectionalSquare(this, x, y, 270));
					squares.push_back(new DirectionalSquare(this, x, y, 270));
					directionals.push_back(new DirectionalSquare(this, x, y, 270));
					break;

				case Board::up_dir_square:
					cerr << "Location " << x << " " << y << " has a up directional square" << endl;
					actors.push_back(new DirectionalSquare(this, x, y, 90));
					squares.push_back(new DirectionalSquare(this, x, y, 90));
					directionals.push_back(new DirectionalSquare(this, x, y, 90));
					break;

				case Board::right_dir_square:
					cerr << "Location " << x << " " << y << " has a right directional square" << endl;
					actors.push_back(new DirectionalSquare(this, x, y, 0));
					squares.push_back(new DirectionalSquare(this, x, y, 0));
					directionals.push_back(new DirectionalSquare(this, x, y, 0));
					break;

				case Board::left_dir_square:
					cerr << "Location " << x << " " << y << " has a left directional square" << endl;
					actors.push_back(new DirectionalSquare(this, x, y, 180));
					squares.push_back(new DirectionalSquare(this, x, y, 180));
					directionals.push_back(new DirectionalSquare(this, x, y, 180));
					break;

				case Board::bank_square:
					cerr << "Location " << x << " " << y << " has a bank square" << endl;
					actors.push_back(new BankSquare(this, x, y));
					squares.push_back(new BankSquare(this, x, y));
					break;

				case Board::event_square:
					cerr << "Location " << x << " " << y << " has a event square" << endl;
					actors.push_back(new EventSquare(this, x, y));
					squares.push_back(new EventSquare(this, x, y));
					break;
					// etc…
				}
			}
		}
	}
	startCountdownTimer(99);

	return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
	// This code is here merely to allow the game to build, run, and terminate after you hit ESC.
	// Notice that the return value GWSTATUS_NOT_IMPLEMENTED will cause our framework to end the game.

	if (timeRemaining() == 0)
	{
		playSound(SOUND_GAME_FINISHED);
		if (m_Peach->getStars() > m_Yoshi->getStars())
		{
			setFinalScore(m_Peach->getStars(), m_Peach->getCoins());
			return GWSTATUS_PEACH_WON;
		}
		else if (m_Peach->getStars() < m_Yoshi->getStars())
		{
			setFinalScore(m_Yoshi->getStars(), m_Yoshi->getCoins());
			return GWSTATUS_YOSHI_WON;
		}
		else if ((m_Peach->getStars() == m_Yoshi->getStars()))
		{
			if (m_Peach->getCoins() > m_Yoshi->getCoins())
			{
				setFinalScore(m_Peach->getStars(), m_Peach->getCoins());
				return GWSTATUS_PEACH_WON;
			}
			else 
			{
				setFinalScore(m_Yoshi->getStars(), m_Yoshi->getCoins());
				return GWSTATUS_YOSHI_WON;
			}
		}

	}

	m_Peach->doSomething();
	m_Yoshi->doSomething();
	for (Actor* a : actors)
	{
		a->doSomething();
	}

	for (Vortex* v : vortexes)
	{
		v->doSomething();
	}

	ostringstream oss;

	oss << "P1 Roll: ";
	oss << m_Peach->getRoll();

	oss << " Stars: ";
	oss << m_Peach->getStars();

	oss << " $$ ";
	oss << m_Peach->getCoins();

	if (m_Peach->getProjectiles() > 0)
		oss << " VOR";

	oss << " | Time : ";
	oss << timeRemaining();

	oss << " Bank: ";
	oss << getBankBalance();

	oss << " P2 Roll: ";
	oss << m_Yoshi->getRoll();

	oss << " Stars: ";
	oss << m_Yoshi->getStars();

	oss << " $$ ";
	oss << m_Yoshi->getCoins();

	if (m_Yoshi->getProjectiles() > 0)
		oss << " VOR";

	setGameStatText(oss.str());


	return GWSTATUS_CONTINUE_GAME;
}
/*
bool StudentWorld::isValidPos(int x, int y)
{
	int x_loc = x / 16;
	int y_loc = y / 16;

	//if (ge(x,y)==blue_coin_square)
	return false;
}
*/


bool StudentWorld::canMoveLeft(double x, double y)
{

	if (x > 255 || y > 255 || x < 0 || y < 0)
		return false;

	for (auto a : actors)
	{
		if (a->isSteppable())
		{
			int x_min = a->getX();
			int match_y = a->getY();
			if (x >= x_min && (x - x_min <= 16 && x - x_min >= 0) && y == match_y)
				return true;
		}
	}
	return false;
}

bool StudentWorld::canMoveRight(double x, double y)
{

	if (x > 255 || y > 255 || x < 0 || y < 0)
		return false;

	for (auto a : actors)
	{
		if (a->isSteppable())
		{
			int x_max = a->getX();
			int match_y = a->getY();
			if (x <= x_max && (x_max - x <= 16 && x_max - x >= 0) && y == match_y)
				return true;
		}
	}
	return false;
}
bool StudentWorld::canMoveUp(double x, double y)
{

	if (x > 255 || y > 255 || x < 0 || y < 0)
		return false;

	for (auto a : actors)
	{
		if (a->isSteppable())
		{
			int y_max = a->getY();
			int match_x = a->getX();
			if (y <= y_max && (y_max - y <= 16 && y_max - y >= 0) && x == match_x)
				return true;
		}
	}
	return false;
}
bool StudentWorld::canMoveDown(double x, double y)
{
	bool valid = false;
	if (x > 255 || y > 255 || x < 0 || y < 0)
		return valid;
	for (auto a : actors)
	{
		if (a->isSteppable())
		{
			int y_min = a->getY();
			int match_x = a->getX();
			if (y >= y_min && (y - y_min <= 16 && y - y_min >= 0) && x == match_x)
			{
				valid = true;
				return valid;
			}
		}
	}
	return valid;
}

void StudentWorld::cleanUp()
{
	for (Actor* a : actors)
		delete a;
	actors.clear();

	for (Actor* s : squares)
		delete s;
	squares.clear();

	for (Vortex* v : vortexes)
		delete v;
	vortexes.clear();

	for (DirectionalSquare* d : directionals)
		delete d;
	directionals.clear();


	delete m_Peach;
	m_Peach = nullptr;

	delete m_Yoshi;
	m_Yoshi = nullptr;
}

StudentWorld::~StudentWorld() // just calls cleanUp
{
	cleanUp();
}

void StudentWorld::coinAdderPeach() // function to handle increment/decrement coins of peach & yoshi
{
	for (auto a : actors)
	{
		if (a->getX() == m_Peach->getX() && a->getY() == m_Peach->getY() && a->addsCoins())
		{
			m_Peach->incrementCoins(a->getAmountToAdd()); // +3 if blue, -3 if red
		}
		//add same thing for Yoshi
	}
}

void StudentWorld::coinAdderYoshi()
{
	for (auto a : actors)
	{
		if (a->getX() == m_Yoshi->getX() && a->getY() == m_Yoshi->getY() && a->addsCoins())
		{
			m_Yoshi->incrementCoins(a->getAmountToAdd()); // +3 if blue, -3 if red
		}
		//add same thing for Yoshi
	}
}

void StudentWorld::buyPeachStar()
{
	m_Peach->buyStar();
}
void StudentWorld::buyYoshiStar()
{
	m_Yoshi->buyStar();
}

void StudentWorld::givePeachCoin(int n)
{
	m_Peach->incrementCoinss(n);
}
void StudentWorld::giveYoshiCoin(int n)
{
	m_Yoshi->incrementCoinss(n);
}

void StudentWorld::takePeachCoins()
{
	m_Peach->loseAllCoins();
}
void StudentWorld::takeYoshiCoins()
{
	m_Yoshi->loseAllCoins();
}

bool StudentWorld::isDirectlyOn(Actor* me)
{
	for (auto a : actors)
	{
		if (a->getX() == me->getX() && a->getY() == me->getY() && a->isSteppable())
		{
			return true;
		}
	}
	return false;
}

bool StudentWorld::isOnBlue(Actor* me)
{
	for (auto a : actors)
	{
		if (a->getX() == me->getX() && a->getY() == me->getY() && a->isSteppable() && a->canAddThreeCoins())
		{
			return true;
		}
	}
	return false;
}

bool StudentWorld::canTeleportHere(double x, double y)
{
	for (auto s : squares)
	{
		if (s->getX() == x && s->getY() == y && s->isSteppable())
		{
			return true;
		}
	}
	return false;
}

int StudentWorld::numBlues()
{
	int sum = 0;
	for (auto a : actors)
	{
		if (a->isSteppable() && a->canAddThreeCoins())
		{
			sum++;
		}
	}
	return sum;
}

void StudentWorld::BowserSpecial(double x, double y, Actor* me)
{
	for (vector<Actor*>::iterator itr = actors.begin(); itr != actors.end(); )
	{
		if ((*itr)->isSteppable() && (*itr)->canAddThreeCoins() && (*itr)->getX() == me->getX() && (*itr)->getY() == me->getY())
		{
			delete* itr;
			itr = actors.erase(itr);
		}
		else
		{
			itr++;
		}
	}
	actors.push_back(new DroppingSquare(this, x/16, y/16));
}

void StudentWorld::spawnVortex(double x, double y, int dir)
{
	vortexes.push_back(new Vortex(this, x / 16, y / 16, dir));
}


void StudentWorld::destroyVortex(Vortex* me)
{
	for (vector<Vortex*>::iterator itr = vortexes.begin(); itr != vortexes.end(); )
	{
		if ((*itr)->getX() == me->getX() && (*itr)->getY() == me->getY())
		{
			delete* itr;
			itr = vortexes.erase(itr);
		}
		else
		{
			itr++;
		}
	}
}

Actor* StudentWorld::vortexOverlap(Vortex* me)
{
	int x_min = me->getX();
	int y_min = me->getY();

	for (vector<Actor*>::iterator itr = actors.begin(); itr != actors.end(); itr++)
	{
		if ((*itr)->isImpactable())
		{
			int x_minn = (*itr)->getX();
			int y_minn = (*itr)->getY();

			double x_dif = x_min - x_minn;
			double y_dif = y_min - y_minn;
			if (x_dif * y_dif <= 256 && abs(x_dif)<=16 && abs(y_dif)<=16) {
				return (*itr);
			}
		}

	}
	
	return nullptr;
}

bool StudentWorld::doesVortexOverlap(Vortex* me)
{
	int x_min = me->getX();
	int y_min = me->getY();

	for (vector<Actor*>::iterator itr = actors.begin(); itr != actors.end(); itr++)
	{
		if ((*itr)->isImpactable())
		{
			int x_minn = (*itr)->getX();
			int y_minn = (*itr)->getY();

			double x_dif = x_min - x_minn;
			double y_dif = y_min - y_minn;
			if (x_dif * y_dif <= 256 && abs(x_dif) <= 16 && abs(y_dif) <= 16) {
				return true;
			}
		}
	}

	return false;
}

int StudentWorld::isOnDirectional(Actor* me)
{
	for (vector<DirectionalSquare*>::iterator itr = directionals.begin(); itr != directionals.end(); itr++ )
	{
		if ((*itr)->getX() == me->getX() && (*itr)->getY() == me->getY())
		{
			int forcedDir = (*itr)->getForcingDir();
			return forcedDir;
		}
	}
	return 69;
}


bool StudentWorld::sameSquare(double x1, double y1, double x2, double y2) {
	if (x1 - x2 == 0 && y1 - y2 == 0)
		return true;
	return false;
}

bool StudentWorld::sameSquareActor(Actor* a, Actor* b) {
	return sameSquare(a->getX(), a->getY(), b->getX(), b->getY());
}

bool StudentWorld::sameSquarePeach(Actor* me) {
	if (sameSquareActor(me, m_Peach))
		return true;
	return false;
} // another one for Yoshi later
bool StudentWorld::sameSquareYoshi(Actor* me) {
	if (sameSquareActor(me, m_Yoshi))
		return true;
	return false;
}

void StudentWorld::switchCoins()
{
	int temp = m_Peach->getCoins();
	m_Peach->setCoins(m_Yoshi->getCoins());
	m_Yoshi->setCoins(temp);
}

void StudentWorld::switchStars()
{
	int temp = m_Peach->getStars();
	m_Peach->setStars(m_Yoshi->getStars());
	m_Yoshi->setStars(temp);
}

void StudentWorld::switchX()
{
	int temp = m_Peach->getX();
	m_Peach->moveTo(m_Yoshi->getX(), m_Peach->getY());
	m_Yoshi->moveTo(temp, m_Yoshi->getY());
}

void StudentWorld::switchY()
{
	int temp = m_Peach->getY();
	m_Peach->moveTo(m_Peach->getX(), m_Yoshi->getY());
	m_Yoshi->moveTo(m_Yoshi->getX(), temp);
}
void StudentWorld::switchTicks()
{
	int temp = m_Peach->getTicks();
	m_Peach->setTicks(m_Yoshi->getTicks());
	m_Yoshi->setTicks(temp);
}
void StudentWorld::switchWalkDir()
{
	int temp = m_Peach->getWalkDir();
	m_Peach->setWalkDir(m_Yoshi->getWalkDir());
	m_Yoshi->setWalkDir(temp);
}
void StudentWorld::switchSpriteDir()
{
	int curr_dirPeach = m_Peach->getWalkDir();
	if (curr_dirPeach == 180)
	{
		m_Peach->setDirection(180);
	}
	else
		m_Peach->setDirection(0); //setDirection to change sprite direction

	int curr_dirYoshi = m_Yoshi->getWalkDir();
	if (curr_dirYoshi == 180)
	{
		m_Yoshi->setDirection(180);
	}
	else
		m_Yoshi->setDirection(0); //setDirection to change sprite direction
}
void StudentWorld::switchState() 
{
	int temp = m_Peach->whatState();
	m_Peach->setState(m_Yoshi->whatState());
	m_Yoshi->setState(temp);
}

void StudentWorld::switchPlayer()
{
	switchX();
	switchY();
	switchTicks();
	switchWalkDir();
	switchSpriteDir();
	switchState();
	switchPlayer();
}

Peach* StudentWorld::givePeach() {
	return m_Peach;
}
Yoshi* StudentWorld::giveYoshi() {
	return m_Yoshi;
}

bool StudentWorld::intersecting(double x1, double y1, double x2, double y2) { // CHECK IF OFF BY 1 ERROR
	if (x1 + SPRITE_WIDTH > x2 && x1 < x2 + SPRITE_WIDTH)
		if (y1 + SPRITE_HEIGHT > y2 && y1 < y2 + SPRITE_HEIGHT)
			return true;
	return false;
}

bool StudentWorld::intersecting(Actor* a, Actor* b) {
	return intersecting(a->getX(), a->getY(), b->getX(), b->getY());
}

bool StudentWorld::isValidPos(double x, double y) { // USED TO SPAWN ITEMS IN // EXPECTS TO SEE INPUT COME 0-16
	return isValidPos(x * SPRITE_WIDTH, y * SPRITE_HEIGHT, nullptr);
}

bool StudentWorld::isValidPos(double x, double y, Actor* me) { // CHECK TO CONDENSE INTO FEWER EMBEDDED IFS // EXPECTS TO SEE INPUT COME 0-255
	for (auto a : actors)
		if (a != me)
			if (a->isSteppable() == true)
				if (intersecting(x, y, a->getX(), a->getY()))
					return false;
	return true;
}



