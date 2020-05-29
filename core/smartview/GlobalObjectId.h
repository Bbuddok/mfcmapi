#pragma once
#include <core/smartview/block/smartViewParser.h>
#include <core/smartview/block/blockBytes.h>
#include <core/smartview/block/blockT.h>

namespace smartview
{
	class GlobalObjectId : public smartViewParser
	{
	private:
		void parse() override;
		void parseBlocks() override;

		std::shared_ptr<blockBytes> m_Id = emptyBB(); // 16 bytes
		std::shared_ptr<blockT<WORD>> m_Year = emptyT<WORD>();
		std::shared_ptr<blockT<BYTE>> m_Month = emptyT<BYTE>();
		std::shared_ptr<blockT<BYTE>> m_Day = emptyT<BYTE>();
		std::shared_ptr<blockT<FILETIME>> m_CreationTime = emptyT<FILETIME>();
		std::shared_ptr<blockT<LARGE_INTEGER>> m_X = emptyT<LARGE_INTEGER>();
		std::shared_ptr<blockT<DWORD>> m_dwSize = emptyT<DWORD>();
		std::shared_ptr<blockBytes> m_lpData = emptyBB();
	};
} // namespace smartview