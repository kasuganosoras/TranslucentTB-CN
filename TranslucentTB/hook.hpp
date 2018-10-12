#pragma once
#include "arch.h"
#include <utility>
#include <WinBase.h>
#include <windef.h>
#include <WinUser.h>

#include "ttberror.hpp"

class TTBHook {
private:
	HHOOK m_hook;

public:
	inline TTBHook(HHOOK hook) : m_hook(hook) { }

	inline TTBHook(TTBHook &&other)
	{
		m_hook = std::exchange(other.m_hook, nullptr);
	}

	inline TTBHook &operator =(TTBHook &&other)
	{
		m_hook = std::exchange(other.m_hook, nullptr);
		return *this;
	}

	inline TTBHook(const TTBHook &other) = delete;
	inline TTBHook &operator =(const TTBHook &other) = delete;

	inline ~TTBHook()
	{
		if (m_hook && !UnhookWindowsHookEx(m_hook))
		{
			LastErrorHandle(Error::Level::Log, L"Failed to remove hook.");
		}
	}
};