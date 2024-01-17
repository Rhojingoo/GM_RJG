#include "Head.h"
#include <conio.h>
//#include <ConsoleEngine/EngineCore.h>
#include </GM_RJG/ConsoleEngine/EngineCore.h>
#include "BodyManager.h"
#include "Body.h"

// 
// 1. ���� Ư�� �������� �����ߴٸ� ���� �Է¶��� �� �ݴ�������δ� ������ ����.
//    ���� �̵��ϴ� ������ �ݴ�������δ� ���� �ȵȴ�.
// 2. ���� �̵��� �ؼ� CurBody�� ȹ���ߴٸ� �� �������� �� �ٵ�� ���� ����;� �Ѵ�.

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
		MsgBoxAssert("������ �ִ� �ٵ� �������� �ʽ��ϴ�.");
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