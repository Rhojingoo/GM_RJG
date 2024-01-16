#pragma once
//#include <ConsoleEngine/ConsoleObject.h>
#include </GM_RJG/ConsoleEngine/ConsoleObject.h>

class Part : public ConsoleObject
{
public:
	enum class Direction
	{
		Right,
		Left,
		Up,
		Down,
		End
	};

	Direction GetDir()
	{
		return mDirection;
	}

	int2 GetPrevePos()
	{
		return PrevePos;
	}

	Part* GetBack()
	{
		return Back;
	}

	static void SetOnMove()
	{
		Move = true;
	}

	static void SetOffMove()
	{
		Move = false;
	}

	static bool GetMove()
	{
		return Move;
	}


	Part* Back = nullptr;
protected:
	Part* Front = nullptr;
	Direction mDirection = {};
	Direction FrontDirection = {};
	int2 PrevePos = {};

private:
	static bool Move;
};

