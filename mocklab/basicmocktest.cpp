#include "stdafx.h"
#include <gmock\gmock.h>
class Turtle
{
public:
	Turtle();
	virtual ~Turtle();
	virtual void PenUp() = 0;
	virtual void PenDown() = 0;
	virtual bool Forward(int distance = 10) = 0;
	virtual void Turn(int degrees) = 0;
	virtual void GoTo(int x, int y) = 0;
	virtual int GetX() const = 0;
	virtual int GetY() const = 0;
	virtual bool SetName(const TCHAR* name = L"Mooki") = 0;
private:

};

Turtle::Turtle()
{
}

Turtle::~Turtle()
{
}

class MockTurtle: public Turtle
{
public:
	MockTurtle();
	~MockTurtle();
	MOCK_METHOD0(PenUp, void());
	MOCK_METHOD0(PenDown, void());
	MOCK_METHOD1(Forward, bool(int distance));
	MOCK_METHOD1(Turn, void(int degrees));
	MOCK_METHOD2(GoTo, void(int x, int y));
	MOCK_CONST_METHOD0(GetX, int());
	MOCK_CONST_METHOD0(GetY, int());
	MOCK_METHOD1(SetName, bool(const TCHAR* name));
private:

};

MockTurtle::MockTurtle()
{
}

MockTurtle::~MockTurtle()
{
}

class SeaTurtule: public Turtle
{
public:
	SeaTurtule();
	~SeaTurtule();
	void PenUp() {
		std::cout << "Sea turtule penup" << std::endl;
	}
	void PenDown() {
		std::cout << "Sea turtule pendown" << std::endl;
	}
	bool Forward(int distance) {
		std::cout << "Sea turtule forward:"<<distance << std::endl;
		return true;
	}
	void Turn(int degrees) {
		std::cout << "Sea turtule turn" << std::endl;
	}
	void GoTo(int x, int y) {
		std::cout << "Sea turtule going to:"<< x <<","<< y << std::endl;
	}
	int GetX() const {
		std::cout << "Sea turtule x is" << std::endl;
		return 1;
	}
	int GetY() const {
		std::cout << "Sea turtule y is" << std::endl;
		return 1;
	}
private:

};

SeaTurtule::SeaTurtule()
{
}

SeaTurtule::~SeaTurtule()
{
}

class Painter
{
public:
	Painter(Turtle* turtule);
	~Painter();
	bool DrawCircle(int x, int y, int r);
private:
	Turtle* tut;
};

Painter::Painter(Turtle* turtule):
	tut(turtule)
{
}

Painter::~Painter()
{
}

bool Painter::DrawCircle(int x, int y, int r)
{
	tut->SetName();
	return true;
}

TEST(PainterTest, CanDrawSomething) {
	MockTurtle turtle;                          // #2
	EXPECT_CALL(turtle, SetName(testing::_))              // #3
		.Times(testing::AtLeast(1)).WillOnce(testing::Return(true));

	Painter painter(&turtle);                   // #4

	EXPECT_TRUE(painter.DrawCircle(0, 0, 10));
}