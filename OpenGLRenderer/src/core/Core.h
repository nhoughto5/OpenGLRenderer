#pragma once

#ifdef OGLR_ENABLE_ASSERTS
#define OGLR_ASSERT(x, ...) { if(!(x)) { OGLR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define OGLR_CORE_ASSERT(x, ...) { if(!(x)) { OGLR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define OGLR_ASSERT(x, ...)
#define OGLR_CORE_ASSERT(x, ...)
#endif