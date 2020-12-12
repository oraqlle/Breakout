#include "..\headers\Log.h"

template<typename ... Args>
Log<Args...>::Log(
	char const* const _format,
	Args const & ... args
) noexcept
{
	printf(_format, Argumants(args) ...)
}