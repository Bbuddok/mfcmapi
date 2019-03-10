#pragma once
#include <core/smartview/SmartViewParser.h>
#include <core/smartview/block/blockStringA.h>
#include <core/smartview/block/blockStringW.h>

namespace smartview
{
	struct FolderFieldDefinitionCommon
	{
		blockT<GUID> PropSetGuid;
		blockT<DWORD> fcapm;
		blockT<DWORD> dwString;
		blockT<DWORD> dwBitmap;
		blockT<DWORD> dwDisplay;
		blockT<DWORD> iFmt;
		blockT<WORD> wszFormulaLength;
		blockStringW wszFormula;

		void parse(std::shared_ptr<binaryParser>& parser);
	};

	struct FolderFieldDefinitionA
	{
		blockT<DWORD> FieldType;
		blockT<WORD> FieldNameLength;
		blockStringA FieldName;
		FolderFieldDefinitionCommon Common;

		FolderFieldDefinitionA(std::shared_ptr<binaryParser>& parser);
	};

	struct FolderFieldDefinitionW
	{
		blockT<DWORD> FieldType;
		blockT<WORD> FieldNameLength;
		blockStringW FieldName;
		FolderFieldDefinitionCommon Common;

		FolderFieldDefinitionW(std::shared_ptr<binaryParser>& parser);
	};

	class FolderUserFieldStream : public SmartViewParser
	{
	private:
		void Parse() override;
		void ParseBlocks() override;

		blockT<DWORD> m_FolderUserFieldsAnsiCount;
		std::vector<std::shared_ptr<FolderFieldDefinitionA>> m_FieldDefinitionsA;
		blockT<DWORD> m_FolderUserFieldsUnicodeCount;
		std::vector<std::shared_ptr<FolderFieldDefinitionW>> m_FieldDefinitionsW;
	};
} // namespace smartview