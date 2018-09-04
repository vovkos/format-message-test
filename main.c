#include <windows.h>
#include <stdio.h>

void printSystemMessage (
	DWORD code,
	DWORD langId,
	const WCHAR* langDesc
	)
{
	DWORD result;
	WCHAR* message = NULL;

	wprintf (L"FormatMessage (%d, %s) -> ", code, langDesc);

	result = FormatMessageW (
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_MAX_WIDTH_MASK, // no line breaks please
		NULL,
		code,
		langId,
		(LPWSTR) &message,
		0,
		NULL
		);

	if (!result)
	{
		wprintf (L"failed (%d)\n", GetLastError ());
		return;
	}

	wprintf (L"%s\n", message);
	LocalFree (message);
}

int main ()
{
	static const DWORD codeTable [] =
	{
		ERROR_FILE_NOT_FOUND,
		ERROR_ACCESS_DENIED,
		ERROR_NOACCESS,
		// ...
	};

	static const struct
	{
		DWORD m_id;
		const WCHAR* m_desc;
	}
	langTable [] =
	{
		{ MAKELANGID (LANG_NEUTRAL, SUBLANG_NEUTRAL),     L"LANG_NEUTRAL, SUBLANG_NEUTRAL" },
		{ MAKELANGID (LANG_NEUTRAL, SUBLANG_DEFAULT),     L"LANG_NEUTRAL, SUBLANG_DEFAULT" },
		{ MAKELANGID (LANG_NEUTRAL, SUBLANG_SYS_DEFAULT), L"LANG_NEUTRAL, SUBLANG_SYS_DEFAULT" },
		{ MAKELANGID (LANG_INVARIANT, SUBLANG_NEUTRAL),   L"LANG_INVARIANT, SUBLANG_NEUTRAL" },
		{ MAKELANGID (LANG_ENGLISH, SUBLANG_DEFAULT),     L"LANG_ENGLISH, SUBLANG_DEFAULT" },
		{ MAKELANGID (LANG_ENGLISH, SUBLANG_ENGLISH_US),  L"LANG_ENGLISH, SUBLANG_ENGLISH_US" },
	};

	UINT i, j;

	for (i = 0; i < _countof (codeTable); i++)
	{
		for (j = 0; j < _countof (langTable); j++)
			printSystemMessage (codeTable [i], langTable [j].m_id, langTable [j].m_desc);

		wprintf (L"\n");
	}

	return 0;
}
