#include <vector>
#include <memory>
#include <curses.h>

using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::shared_ptr;
using std::make_shared;

//Constants 
//Keys
constexpr int KEY_ESC = 27;

enum class Height : int {
	GROUND = 0,
	ON_GROUND,
	IN_AIR
};

// static, nonmoving element for stationary objects
class GameElement {
protected:
	int y;
	int x;
	char symbol;
	bool passable;
	Height height;

	// constructor protected to prevent instantiation
	GameElement(int y, int x, char symbol, bool passable, Height height)
		: y(y), x(x), symbol(symbol), passable(passable), height(height) {}
public:
	virtual int getY() { return y; }

	virtual int getX() { return x; }

	virtual char getSymbol() { return symbol; }

	virtual void setPosition(int newY, int newX) {
		y = newY;
		x = newX;
	}

	virtual void setX(int newX) {
		x = newX;
	}

	virtual void setY(int newY) {
		y = newY;
	}
};

// nonstatic, moving element for moving objects
class MovingElement : public GameElement {
protected:
	MovingElement(int y, int x, char symbol, bool passable, Height height)
		: GameElement(y, x, symbol, passable, height) {}

public:
	virtual void move(int dy, int dx) {
		y += dy;
		x += dx;
	}
};

// moving, creature elements
class Creature : public MovingElement {
protected:
	static const int MAX_HP = 100;
	static const int MIN_HP = 0;
	int health;

	Creature(int y, int x, char symbol, int health)
		: MovingElement(y, x, symbol, false, Height::ON_GROUND), health(health) {}
};

class Human : public Creature {
protected:
	Human(int y, int x, char symbol, int health)
		: Creature(x, y, symbol, health) {}
};

class Player : public Human {
public:
	Player(int y, int x, int health)
		: Human(y, x, 'P', health) {}
};

// structures and unmoving elements
class Tile : public GameElement {
public:
	Tile(int y, int x)
		: GameElement(y, x, '.', true, Height::GROUND) {}
};
