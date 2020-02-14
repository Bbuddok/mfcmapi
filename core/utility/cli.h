#pragma once
#include <core/utility/strings.h>

// MrMAPI command line
namespace cli
{
	struct OPTIONS
	{
		int mode{};
		int flags{};
	};

	class option
	{
	private:
		bool seen{false};
		std::vector<std::wstring> args;
		LPCWSTR szSwitch{};

	public:
		const int mode{};
		const size_t minArgs{};
		const size_t maxArgs{};
		const int flags{};

		option(LPCWSTR _szSwitch, int _mode, UINT _minArgs, UINT _maxArgs, int _optionFlags)
			: szSwitch{_szSwitch}, mode{_mode}, minArgs{_minArgs}, maxArgs{_maxArgs}, flags{_optionFlags}
		{
		}

		LPCWSTR name() const noexcept { return szSwitch; }
		bool isSet() const noexcept { return seen; }
		size_t size() const noexcept { return args.size(); }
		bool empty() const noexcept { return args.empty(); }
		bool has(const size_t _Pos) const noexcept { return size() > _Pos; }
		bool hasULONG(size_t _Pos, int radix = 10) const noexcept
		{
			ULONG num{};
			return _Pos < size() && strings::tryWstringToUlong(num, args[_Pos], radix, true);
		}

		void clear()
		{
			seen = false;
			args.clear();
		}
		std::wstring at(const size_t _Pos) const noexcept { return size() > _Pos ? args[_Pos] : std::wstring{}; }
		std::wstring operator[](const size_t _Pos) const noexcept { return at(_Pos); }

		ULONG atULONG(const size_t _Pos, const int radix = 10) const noexcept
		{
			return size() > _Pos ? strings::wstringToUlong(args[_Pos], radix) : 0;
		}

		_Check_return_ bool
		scanArgs(std::deque<std::wstring>& args, OPTIONS& options, const std::vector<option*>& optionsArray);
	};

	enum modeEnum
	{
		cmdmodeUnknown = 0,
		cmdmodeHelp,
		cmdmodeHelpFull,
		cmdmodeFirstMode, // When extending modes, use this as the value of the first mode
	};

	enum flagsEnum
	{
		OPT_NOOPT = 0x0000,
		OPT_INITMFC = 0x0001,
		OPT_NEEDNUM = 0x0002, // Any arguments must be decimal numbers. No strings.
	};

	extern option switchUnswitched;
	extern option switchInvalid;
	extern option switchHelp;
	extern option switchVerbose;

	// Checks if szArg is an option, and if it is, returns which option it is
	// We return the first match, so switches should be ordered appropriately
	// The first switch should be our "no match" switch
	option* GetOption(const std::wstring& szArg, const std::vector<option*>& optionsArray);

	// If the mode isn't set (is 0), then we can set it to any mode
	// If the mode IS set (non 0), then we can only set it to the same mode
	// IE trying to change the mode from anything but unset will fail
	bool bSetMode(_In_ int& pMode, _In_ int targetMode) noexcept;

	std::deque<std::wstring> GetCommandLine(_In_ int argc, _In_count_(argc) const char* const argv[]);

	// Parses command line arguments and fills out OPTIONS
	void ParseArgs(OPTIONS& options, std::deque<std::wstring>& args, const std::vector<option*>& optionsArray);

	void PrintArgs(_In_ const OPTIONS& ProgOpts, const std::vector<option*>& optionsArray);
} // namespace cli