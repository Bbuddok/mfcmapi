#pragma once
#include <core/smartview/SmartViewParser.h>
#include <core/smartview/block/blockStringA.h>
#include <core/smartview/block/blockStringW.h>

namespace smartview
{
	// [MS-OXOTASK].pdf
	struct TaskAssigner
	{
		blockT<DWORD> cbAssigner{};
		blockT<ULONG> cbEntryID{};
		blockBytes lpEntryID;
		blockStringA szDisplayName;
		blockStringW wzDisplayName;
		blockBytes JunkData;

		TaskAssigner(std::shared_ptr<binaryParser>& parser);
	};

	class TaskAssigners : public SmartViewParser
	{
	private:
		void Parse() override;
		void ParseBlocks() override;

		blockT<DWORD> m_cAssigners;
		std::vector<std::shared_ptr<TaskAssigner>> m_lpTaskAssigners;
	};
} // namespace smartview