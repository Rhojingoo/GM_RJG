#include "Head.h"
#include <conio.h>
//#include <ConsoleEngine/EngineCore.h>
#include </GM_RJG/ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. 내가 특정 방향으로 진행했다면 다음 입력때는 그 반대방향으로는 갈수가 없다.
//    내가 이동하는 방향의 반대방향으로는 가면 안된다.
// 2. 내가 이동을 해서 CurBody를 획득했다면 그 다음부터 그 바디는 나를 따라와야 한다.

void Head::Update()
{
	int InputCount = _kbhit();
	if (0 == InputCount)
	{
		return;
	}

	PrevePos = GetPos();
	int Select = _getch();
	

	if (mDirection == Direction::Right)
	{
		if (Select == 'A' || Select == 'a')
			return;
	}
	else if (mDirection == Direction::Left)
	{
		if (Select == 'D' || Select == 'd')
			return;
	}
	else if (mDirection == Direction::Up)
	{
		if (Select == 'S' || Select == 's')
			return;
	}
	else if (mDirection == Direction::Down)
	{
		if (Select == 'W' || Select == 'w')
			return;
	}

	switch (Select)
	{
	case 'D':
	case 'd':
	{
		mDirection = Direction::Right;
		AddPos(Right);
		SetOnMove();
	}
	break;

	case 'A':
	case 'a':
	{
		mDirection = Direction::Left;
		AddPos(Left);
		SetOnMove();
	}
	break;
	case 'S':
	case 's':
	{
		mDirection = Direction::Down;
		AddPos(Down);
		SetOnMove();
	}
	break;

	case 'W':
	case 'w':
	{
		mDirection = Direction::Up;
		AddPos(Up);
		SetOnMove();
	}
	break;

	case '1':
		GetCore()->EngineEnd();
		break;
	default:		
		SetOffMove();
		break;
	}
		

	if (nullptr == BodyManager::GetCurBody())
	{
		MsgBoxAssert("먹을수 있는 바디가 존재하지 않습니다.");
		return;
	}

	Body* CurBody = BodyManager::GetCurBody();

	if (Body::GetFirstBody() == false)
	{
		if (CurBody->GetPos() == GetPos())
		{
			Back = CurBody;
			CurBody->SetColcheck(this);
			Body::Set_GetFirstBody();
			BodyManager::ResetBody();
		}
	}
	else
	{
		if (CurBody->GetPos() == GetPos())
		{
			Part* check = Back;
			while (check->GetBack() != nullptr)
			{
				check = check->GetBack();
			}			
			check->SetBack(CurBody);
			CurBody->SetColcheck(check);
			BodyManager::ResetBody();
		}
	}
}