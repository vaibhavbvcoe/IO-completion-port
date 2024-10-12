// IOCP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include"CompletionPort.h"

int main()
{
#pragma region SENDDATA
    CompletionPort port;
    HRESULT result =  port.Create(1);
    if (FAILED(result))
    {
        return HRESULT_FROM_WIN32(::GetLastError());
    }
    result = port.QueuePacket(2, 1, 0);
    if (FAILED(result))
    {
        return HRESULT_FROM_WIN32(::GetLastError());
    }
#pragma endregion SENDDATA
#pragma region RECEIVEDATA

    DWORD bytesCopied = 0;
    ULONG_PTR completionKey = 0;
    OVERLAPPED* overlapped = 0;
    result = port.DequeuePacket(0, // don't wait
        bytesCopied,
        completionKey,
        overlapped);
    if (FAILED(result))
    {
        return HRESULT_FROM_WIN32(::GetLastError());
    }

    ASSERT(2 == bytesCopied);
    ASSERT(1 == completionKey);
    ASSERT(0 == overlapped);
    std::cout << bytesCopied << " " << completionKey << " " << overlapped << std::endl;
#pragma endregion RECEIVEDATA

}