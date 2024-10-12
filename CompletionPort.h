#pragma once
#include<afxwin.h>

class CompletionPort:public CHandle
{
	CompletionPort(CompletionPort&);
	CompletionPort& operator=(CompletionPort&);
	bool m_closeHandle;
public:
	CompletionPort();
	explicit CompletionPort(__in bool closeHandle);
	CompletionPort(__in bool closeHandle,		__in_opt HANDLE handle);
	~CompletionPort();
	__checkReturn HRESULT Create(__in DWORD threadCount);
	__checkReturn HRESULT AssociateFile(__in HANDLE file, __in ULONG_PTR completionKey);
	__checkReturn HRESULT QueuePacket(__in DWORD bytesCopied, __in ULONG_PTR completionKey, __in OVERLAPPED* overlapped);
	__checkReturn HRESULT DequeuePacket(__in DWORD milliseconds, __out DWORD& bytesCopied, __out ULONG_PTR& completionKey, __out OVERLAPPED*& overlapped);

};

