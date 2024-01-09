#include <iostream>
#include <ConsoleEngine/EngineDebug.h>

class IntArray
{
public:
    IntArray(int _Size)
    {
        ReSize(_Size);
    }

    IntArray(const IntArray& _Other)
    {
        Copy(_Other);
    }
    ~IntArray()
    {
        Release();
    }
    void operator=(const IntArray& _Other)
    {
        Copy(_Other);
    }

    int& operator[](int _Count)
    {
        return ArrPtr[_Count];
    }

    int& Test(int _Count)
    {
        return ArrPtr[_Count];
    }

    int Num()
    {
        return NumValue;
    }

    void Copy(const IntArray& _Other)
    {
        NumValue = _Other.NumValue;

        // 깊은 복사를 해줘야 합니다.
        ReSize(NumValue);
        for (int i = 0; i < NumValue; i++)
        {
            ArrPtr[i] = _Other.ArrPtr[i];
        }
    }

    void ReSize(int _Size)
    {
        if (0 >= _Size)
        {
            MsgBoxAssert("배열의 크기가 0일수 없습니다");
        }

        NumValue = _Size;     


        if (nullptr != ArrPtr)
        {
            ArrPtr2 = new int[NumValue];
            for (int i = 0; i < NumValue; i++)
            {
                ArrPtr2[i] = ArrPtr[i];
            }
            Release();       
        }  
        ArrPtr = new int[_Size];
        if (nullptr != ArrPtr2)
        {
            for (size_t i = 0; i < NumValue; i++)
            {
                ArrPtr[i] = ArrPtr2[i];
            }
            delete ArrPtr2;
            ArrPtr2 = nullptr;
        }
    }

    void Release()
    {
        if (nullptr != ArrPtr)
        {
            delete[] ArrPtr;
            ArrPtr = nullptr;
        }
    }

private:
    int NumValue = 0;
    int* ArrPtr = nullptr;
    int* ArrPtr2 = nullptr;
};

int main()
{
    IntArray NewArray = IntArray(5);

    for (int i = 0; i < NewArray.Num(); i++)
    {
        NewArray[i] = i;
    }

    NewArray.ReSize(1);

    for (size_t i = 0; i < NewArray.Num(); i++)
    {
        std::cout << NewArray[i] << std::endl;
    }
}