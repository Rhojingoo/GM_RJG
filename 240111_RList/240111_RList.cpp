﻿#include <iostream>
#include <list>
#include <ConsoleEngine/EngineDebug.h>

typedef int DataType;

class MyList
{
private:
	class ListNode
	{
	public:
		DataType Data = DataType();
		ListNode* Next = nullptr;
		ListNode* Prev = nullptr;
	};


public:
	class iterator 
	{
		friend MyList;

	public:
		iterator()
		{
		}

		iterator(ListNode* _CurNode)
			: CurNode(_CurNode)
		{
		}

		bool operator!=(const iterator& _Other)
		{
			return CurNode != _Other.CurNode;
		}

		DataType& operator*()
		{
			return CurNode->Data;
		}

		
		// 연산자 겹지정 중에 
		virtual void operator++()
		{
			CurNode = CurNode->Next;
		}


	protected:
		ListNode* CurNode = nullptr;
	private:
	};


public:
	class Reverce_iterator : public iterator
	{
		friend MyList;

	public:
		Reverce_iterator()
		{
		}

		Reverce_iterator(ListNode* _CurNode)
			: iterator(_CurNode)
		{
		}

		// 연산자 겹지정 중에 
		void operator++() override
		{
			CurNode = CurNode->Prev;
		}
	};



	MyList()
	{
		Start->Next = End;
		End->Prev = Start;
	}

	~MyList()
	{
		ListNode* CurNode = Start;
		while (CurNode)
		{
			ListNode* Next = CurNode->Next;
			if (nullptr != CurNode)
			{
				delete CurNode;
				CurNode = Next;
			}
		}
	}


	iterator begin()
	{
		return iterator(Start->Next);
	}

	iterator end()
	{
		return iterator(End);
	}

	Reverce_iterator rbegin()
	{
		return Reverce_iterator(End->Prev);
	}

	Reverce_iterator rend()
	{
		return Reverce_iterator(Start);
	}


	// End의 Prev에 새로운 데이터를 넣겠다.
	void push_back(const DataType& _Data)
	{
		ListNode* NewNode = new ListNode();
		NewNode->Data = _Data;

		NewNode->Next = End;
		NewNode->Prev = End->Prev;

		ListNode* PrevNode = NewNode->Prev;
		ListNode* NextNode = NewNode->Next;

		PrevNode->Next = NewNode;
		NextNode->Prev = NewNode;
	}

	// Start의 Next에 새로운 데이터를 넣겠다.
	void push_front(const DataType& _Data)
	{
		// 역함수
		ListNode* NewNode = new ListNode();
		NewNode->Data = _Data;

		NewNode->Prev = Start;
		NewNode->Next = Start->Next;

		ListNode* PrevNode = NewNode->Prev;
		ListNode* NextNode = NewNode->Next;

		PrevNode->Next = NewNode;
		NextNode->Prev = NewNode;

	}

	iterator erase(iterator& _Iter)
	{
		if (_Iter.CurNode == Start)
		{
			MsgBoxAssert("Start를 삭제하려고 했습니다.");
		}

		if (_Iter.CurNode == End)
		{
			MsgBoxAssert("End를 삭제하려고 했습니다.");
		}

		iterator ReturnIter;

		if (nullptr != _Iter.CurNode)
		{
			ReturnIter = iterator(_Iter.CurNode->Next);

			ListNode* PrevNode = _Iter.CurNode->Prev;
			ListNode* NextNode = _Iter.CurNode->Next;

			PrevNode->Next = NextNode;
			NextNode->Prev = PrevNode;

			if (nullptr != _Iter.CurNode)
			{
				delete _Iter.CurNode;
				_Iter.CurNode = nullptr;
			}
		}

		return ReturnIter;
	}


protected:

private:

	ListNode* Start = new ListNode();
	ListNode* End = new ListNode();
};

int main()
{
	LeakCheck;

	{
		std::cout << "std 리스트" << std::endl;
		std::list<int> NewList = std::list<int>();
		// 0, 1, 2, 3, 4
		for (int i = 0; i < 5; i++)
		{
			NewList.push_back(i);
			// NewList.push_front();
		}

		std::list<int>::reverse_iterator rStartIter = NewList.rbegin();
		std::list<int>::reverse_iterator rEndIter = NewList.rend();

		for (/*std::list<int>::iterator StartIter = NewList.begin()*/
			; rStartIter != rEndIter
			; ++rStartIter)
		{
			std::cout << *rStartIter << std::endl;
		}
	}


	{
		std::cout << "내 리스트" << std::endl;
		MyList NewList = MyList();
		for (int i = 0; i < 10; i++)
		{
			NewList.push_back(i);
		}

		MyList::Reverce_iterator StartIter = NewList.rbegin();
		MyList::Reverce_iterator EndIter = NewList.rend();

		for (; StartIter != EndIter
			; ++StartIter)
		{
			std::cout << *StartIter << std::endl;
		}
	}
}
