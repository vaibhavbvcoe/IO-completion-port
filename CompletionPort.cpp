#include "CompletionPort.h"

CompletionPort& CompletionPort::operator=(CompletionPort&)
{
	return *this;
	// TODO: insert return statement here
}

CompletionPort::CompletionPort()
{
	m_closeHandle = true;
}

CompletionPort::CompletionPort(bool closeHandle)
{
	m_closeHandle = closeHandle;
}

CompletionPort::CompletionPort(bool closeHandle, HANDLE handle):CHandle(handle)
{
	m_closeHandle = closeHandle;
	
}

CompletionPort::~CompletionPort()
{
	if (!m_closeHandle)
	{
		Detach();
	}
}

HRESULT CompletionPort::Create(DWORD threadCount)
{
	Attach(::CreateIoCompletionPort(INVALID_HANDLE_VALUE,0, 0,threadCount));
	if (0 == m_h)
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}
	return S_OK;
}

HRESULT CompletionPort::AssociateFile(HANDLE file, ULONG_PTR completionKey)
{
	ASSERT(0 != file && INVALID_HANDLE_VALUE != file);
	ASSERT(0 != m_h);

	if (0 == ::CreateIoCompletionPort(file,m_h,completionKey,0)) // ignored
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	return S_OK;
}

HRESULT CompletionPort::QueuePacket(DWORD bytesCopied, ULONG_PTR completionKey, OVERLAPPED* overlapped)
{
	ASSERT(0 != m_h);

	if (!::PostQueuedCompletionStatus(m_h,bytesCopied,completionKey,overlapped))
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}

	return S_OK;
}

HRESULT CompletionPort::DequeuePacket(DWORD milliseconds, DWORD& bytesCopied, ULONG_PTR& completionKey, OVERLAPPED*& overlapped)
{
	ASSERT(0 != m_h);

	if (!::GetQueuedCompletionStatus(m_h,&bytesCopied,&completionKey,&overlapped,milliseconds))
	{
		return HRESULT_FROM_WIN32(::GetLastError());
	}
	return S_OK;
}
