#pragma once
#include <core/utility/strings.h>

namespace controls
{
	class PaneHeader : public CEdit
	{
	public:
		virtual ~PaneHeader() = default;

		void SetLabel(const UINT uidLabel) { m_szLabel = strings::loadstring(uidLabel); }
		void SetLabel(const std::wstring szLabel) { m_szLabel = szLabel; }
		_NODISCARD bool empty() const noexcept { return m_szLabel.empty(); }

		void Initialize(_In_ CWnd* pParent, _In_opt_ HDC hdc, _In_ bool bCollapsible, _In_ UINT nid);
		void DeferWindowPos(_In_ HDWP hWinPosInfo, _In_ int x, _In_ int y, _In_ int width);

		int GetMinWidth();
		bool HandleChange(UINT nID);
		void OnToggleCollapse();

		void SetMargins(
			int iSideMargin,
			int iLabelHeight, // Height of the label
			int iButtonHeight); // Height of buttons below the control
		// Returns the height of our control, accounting for an expand/collapse button
		// Will return 0 if we have no label or button
		int GetFixedHeight() const noexcept
		{
			if (m_bCollapsible || !m_szLabel.empty()) return max(m_iButtonHeight, m_iLabelHeight);

			return 0;
		}
		bool collapsed() const noexcept { return m_bCollapsed; }

		void SetCount(const std::wstring szCount);

	protected:
		bool m_bInitialized{};
		std::wstring m_szLabel; // Text to push into UI in Initialize
		UINT m_nIDCollapse{}; // NID for collapse button.
		HWND m_hWndParent{};
		bool m_bCollapsible{};
		bool m_bCollapsed{};
		CButton m_CollapseButton;

		// Margins
		int m_iSideMargin{};
		int m_iLabelWidth{}; // The width of the label
		int m_iLabelHeight{}; // Height of the label
		int m_iButtonHeight{}; // Height of button

		CEdit m_Count; // The display of the count
		int m_iCountLabelWidth{0}; // The width of the string
	};
} // namespace controls