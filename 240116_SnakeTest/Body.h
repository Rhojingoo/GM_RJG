#pragma once
#include "Part.h"

class Body : public Part
{
public :
	void SetColcheck(Part* _OBJ)
	{
		FrontObj = _OBJ;
		Front = FrontObj;
		Colcheck = true;
	}
	void Update() override;

	static bool GetFirstBody()
	{
		return HeadBackSetting;
	}
	static void Set_GetFirstBody()
	{
		HeadBackSetting = true;
	}

private:
	int2 mPos = {};
	static bool HeadBackSetting;
	bool Colcheck = false;
	Part* FrontObj = nullptr;
};

