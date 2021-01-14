#include "..\headers\Log.h"

template<typename ... Args>
void Log(
	char const* const _format,
	Args const & ... args
) noexcept
{
	printf(_format, Argument(args) ...);
}