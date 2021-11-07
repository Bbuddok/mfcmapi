#include <StdAfx.h>
#include <UI/ViewPane/TreePane.h>
#include <utility>
#include <core/utility/output.h>

namespace viewpane
{
	std::shared_ptr<TreePane> TreePane::Create(int paneID, UINT uidLabel, bool bReadOnly)
	{
		auto pane = std::make_shared<TreePane>();
		if (pane)
		{
			if (uidLabel)
			{
				pane->SetLabel(uidLabel);
				pane->makeCollapsible();
			}

			pane->SetReadOnly(bReadOnly);
			pane->m_paneID = paneID;
		}

		return pane;
	}

	void TreePane::Initialize(_In_ CWnd* pParent, _In_ HDC hdc)
	{
		ViewPane::Initialize(pParent, hdc);
		m_Tree.Create(pParent, m_bReadOnly);

		if (InitializeCallback) InitializeCallback(m_Tree);
		m_bInitialized = true;
	}

	int TreePane::GetFixedHeight()
	{
		auto iHeight = 0;
		if (0 != m_paneID) iHeight += m_iSmallHeightMargin; // Top margin

		const auto labelHeight = GetHeaderHeight();

		if (labelHeight)
		{
			iHeight += labelHeight;
		}

		iHeight += m_iSmallHeightMargin;

		return iHeight;
	}

	HDWP TreePane::DeferWindowPos(
		_In_ HDWP hWinPosInfo,
		_In_ const int x,
		_In_ const int y,
		_In_ const int width,
		_In_ const int height)
	{
		output::DebugPrint(
			output::dbgLevel::Draw, L"TreePane::DeferWindowPos x:%d y:%d width:%d height:%d \n", x, y, width, height);

		auto curY = y;
		const auto labelHeight = GetHeaderHeight();
		if (0 != m_paneID)
		{
			curY += m_iSmallHeightMargin;
		}

		WC_B_S(m_Tree.ShowWindow(collapsed() ? SW_HIDE : SW_SHOW));
		// Layout our label
		hWinPosInfo = EC_D(HDWP, ViewPane::DeferWindowPos(hWinPosInfo, x, curY, width, height - (curY - y)));

		if (labelHeight)
		{
			curY += labelHeight + m_iSmallHeightMargin;
		}

		auto treeHeight = height - (curY - y) - m_iSmallHeightMargin;

		hWinPosInfo =
			EC_D(HDWP, ::DeferWindowPos(hWinPosInfo, m_Tree.GetSafeHwnd(), nullptr, x, curY, width, treeHeight, SWP_NOZORDER));

		return hWinPosInfo;
	}
} // namespace viewpane