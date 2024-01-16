#pragma once
#include "Part.h"

class Head : public Part
{
public:
	Head()
	{
		mDirection = Direction::Right;
	}

	Direction GetDirection()
	{
		return mDirection;
	}

protected:
	void Update() override;

private:

};

