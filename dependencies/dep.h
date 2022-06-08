#pragma once
#include <stdint.h>

enum class HTTPReq : uint8_t
{
	None,
	Get,
	Post,
	Shutdown
};

enum class Result : uint8_t
{
	FailedToSend = 0,
	Succeeded = 1,
};

const int PackageSize = 2000;
