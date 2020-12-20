#pragma once

#ifdef OGLR_ENABLE_ASSERTS
#define OGLR_ASSERT(x, ...) { if(!(x)) { OGLR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define OGLR_CORE_ASSERT(x, ...) { if(!(x)) { OGLR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
#define OGLR_ASSERT(x, ...)
#define OGLR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
#define OGLR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }