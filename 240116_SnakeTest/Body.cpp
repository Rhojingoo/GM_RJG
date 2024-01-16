#include "Body.h"
#include <conio.h>

bool Body::HeadBackSetting = false;
void Body::Update()
{
	if (Colcheck)
	{					

		if (Back == nullptr)
		{
			SetOffMove();
			//return;
		}

		if (GetMove() == true)
		{
			SetOnMove();
			PrevePos = GetPos();	
		}
		mPos = Front->GetPrevePos();
		SetRenderChar('X');
		SetPos(mPos);
	}
}


