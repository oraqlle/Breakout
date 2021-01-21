#pragma once
#include <stdio.h>
#include <string>

template<typename ... Args>
void Log(
		char const* const _format,
		Args const & ... args
	) noexcept;

template<typename _Ty>
_Ty Argument(_Ty val) noexcept { return val; }

template<typename _Ty>
_Ty const* Argument(std::basic_string<_Ty> const& val) noexcept { return val.c_str(); }