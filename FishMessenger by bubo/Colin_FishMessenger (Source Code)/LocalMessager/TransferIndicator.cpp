//--------------------------------------------------------------
//	TransferIndicator.cpp.
//	05/28/2014.		by bubo.
//	Modified		06/06/2014.
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "TransferIndicator.h"
#include "Messages.h"
#include "resource.h"
#include <commctrl.h>
#include <Shlobj.h>
#include <thread>
#include <gdiplus.h>
#include "resource.h"

using namespace Gdiplus;
using namespace cinderella;

//--------------------------------------------------------------
//	Initialize static variables...
//--------------------------------------------------------------
HWND TransferIndicator::ms_hDlg = nullptr;
HWND TransferIndicator::ms_hWndParent = nullptr;
HINSTANCE TransferIndicator::ms_hInstance = nullptr;
TransferIndicator* TransferIndicator::ms_pTransferIndicator = nullptr;

//--------------------------------------------------------------
TransferIndicator::TransferIndicator() : m_hWndListView(nullptr), 
m_iCurrentValidIntex(0), m_pMultiFileCoordinator(nullptr)
{
	ms_pTransferIndicator = this;
	m_hMutex = ::CreateMutex(nullptr, false, nullptr);
}

//--------------------------------------------------------------
bool TransferIndicator::IsDialogMsg(LPMSG pMsg)
{
	// Message loop...
	if (ms_hDlg)
	{
		if (::IsDialogMessage(ms_hDlg, pMsg))
			return true;
	}

	return false;
}

//--------------------------------------------------------------
TransferIndicator* TransferIndicator::GetSingleton()
{
	//
	if (ms_pTransferIndicator == nullptr)
	{
		ms_pTransferIndicator = new TransferIndicator;
	}

	return ms_pTransferIndicator;
}

//--------------------------------------------------------------
void TransferIndicator::DestroySingleton()
{
	//
	if (ms_pTransferIndicator)
	{
		delete ms_pTransferIndicator;
		ms_pTransferIndicator = nullptr;
	}
}

//--------------------------------------------------------------
void TransferIndicator::Initialize(HWND hWndParent, HINSTANCE hInstance)
{
	//
	ms_hWndParent = hWndParent;
	ms_hInstance = hInstance;
}

//--------------------------------------------------------------
TransferIndicator::~TransferIndicator()
{
	//
	if (m_hMutex)
	{
		::CloseHandle(m_hMutex);
	}

	if (m_pMultiFileCoordinator)
	{
		delete m_pMultiFileCoordinator;
		m_pMultiFileCoordinator = nullptr;
	}
}

//--------------------------------------------------------------
bool TransferIndicator::CreateUI()
{
	// Create the modeless dialog box...
	ms_hDlg = ::CreateDialog(ms_hInstance, MAKEINTRESOURCE(IDD_DIALOGTRANSFER),
		ms_hWndParent, fnTransferIndicator);

	if (ms_hDlg)
	{
		CreateListView();
		InitlistViewColumns();
		CreateControlButton();
		
		return true;
	}

	return false;
}

//--------------------------------------------------------------
INT_PTR CALLBACK TransferIndicator::fnTransferIndicator(HWND hDlg,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	POINT point;

	switch (message)
	{
	case WM_INITDIALOG:

		if (ms_pTransferIndicator)
		{
			ms_pTransferIndicator->OnInitDialog(hDlg);
		}

		return true;

	case WM_MOUSEMOVE:

		if (wParam & MK_LBUTTON)
		{
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			::ClientToScreen(hDlg, &point);
			::PostMessage(hDlg, WM_NCLBUTTONDOWN, static_cast<WPARAM>(HTCAPTION),
				MAKELPARAM(point.x, point.y));
		}

		return true;

	case WM_LBUTTONUP:

		point.x = LOWORD(lParam);
		point.y = HIWORD(lParam);
		::ClientToScreen(hDlg, &point);
		::PostMessage(hDlg, WM_NCLBUTTONUP, static_cast<WPARAM>(HTCAPTION),
			MAKELPARAM(point.x, point.y));

		return true;

	case WM_SHOWTRANSFERINDICATOR:
		if (ms_pTransferIndicator)
		{
			ms_pTransferIndicator->ShowTransferIndicator();
		}

		return true;

	case WM_TRANSFERINDICATORUPDATE:
		if (ms_pTransferIndicator)
		{
			ms_pTransferIndicator->Update();
		}

		return true;

	case WM_COMMAND:

		switch (LOWORD(wParam))
		{

		case IDC_CLOSE:
			if (ms_pTransferIndicator)
			{
				ms_pTransferIndicator->HideTransferIndicator();
			}
			

			return true;

		case IDC_TRANALL:
			if (ms_pTransferIndicator)
			{
				ms_pTransferIndicator->OnTransferALL();
			}

			return true;

		case IDC_TRANSEL:
			if (ms_pTransferIndicator)
			{
				ms_pTransferIndicator->OnTransferSelected();
			}

			return true;

		case IDC_CANLSEL:
			if (ms_pTransferIndicator)
			{
				ms_pTransferIndicator->OnCancelSelected();
			}

			return true;

		case IDC_CANLALL:
			if (ms_pTransferIndicator)
			{
				ms_pTransferIndicator->OnCancelALL();
			}

			return true;

		}

		break;

	}

	return false;
}

//--------------------------------------------------------------
void TransferIndicator::OnInitDialog(HWND hDlg)
{
	//
}

//--------------------------------------------------------------
void TransferIndicator::CreateListView()
{
	RECT rcl = { 0 };
	INITCOMMONCONTROLSEX icex;

	icex.dwSize = sizeof INITCOMMONCONTROLSEX;
	icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES;
	//InitCommonControlsEx(&icex);

	// Get the RECT of the main window.
	::GetClientRect(ms_hDlg, &rcl);

	m_hWndListView = ::CreateWindow(WC_LISTVIEW,
		L"", WS_CHILD | LVS_REPORT | WS_VISIBLE | WS_VSCROLL,
		0,
		40,
		rcl.right - rcl.left,
		rcl.bottom - rcl.top - 70,
		ms_hDlg,
		reinterpret_cast<HMENU>(998),
		ms_hInstance,
		nullptr);

	ListView_SetExtendedListViewStyle(m_hWndListView,
		LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

}

//--------------------------------------------------------------
bool TransferIndicator::InitlistViewColumns()
{
	LVCOLUMN lvc;
	RECT rect = { 0 };

	::GetWindowRect(m_hWndListView, &rect);

	//add columns.
	wchar_t* ColNames[] = { L"TYPE: ", L"STATUS: ", 
		L"USER NAME: ", L"FILE NAME: ", L"IP ADDRESS (IPv6):"};

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.pszText = nullptr;
	
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = (rect.right - rect.left) / 8;

	for (int i = 0; i < 5; i++)
	{
		if (i > 1)
		{
			lvc.cx = (rect.right - rect.left) / 4;
		}

		lvc.pszText = ColNames[i];
		lvc.iSubItem = i;

		ListView_InsertColumn(m_hWndListView, i, &lvc);
	}


	return true;
}

//--------------------------------------------------------------
HANDLE TransferIndicator::AddTask(ItemInfo* pItemInfo)
{
	//
	if (!pItemInfo)
	{
		return nullptr;
	}

	HANDLE hUserEvent = ::CreateEvent(nullptr, false, false, nullptr);

	if (!hUserEvent)
	{
		return nullptr;
	}

	pItemInfo->SetupUserEvent(hUserEvent);

	ms_kItemContainer[pItemInfo->GetUserEvent()] = pItemInfo;

	return hUserEvent;
}

//--------------------------------------------------------------
void TransferIndicator::CreateControlButton()
{
	// Rectangle for this dialog.
	RECT rcl = { 0 };
	::GetClientRect(ms_hDlg, &rcl);

	//--------------------------------------------------------------
	//	Create buttons for the TransferIndicator window...
	//--------------------------------------------------------------
	HWND hWndBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"接收所有",				// Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
		rcl.left,				// x position 
		rcl.bottom - 26,         // y position 
		static_cast<int>(9.0 * (rcl.right - rcl.left) / 40.0f),		// Button width
		26,					     // Button height
		ms_hDlg,			 // Parent window
		reinterpret_cast<HMENU>(IDC_TRANALL),       // 
		ms_hInstance,
		nullptr);				// Pointer not needed

	//--------------------------------------------------------------
	hWndBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"接收选择",				// Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles
		static_cast<int>(1 * 9.0 * (rcl.right - rcl.left) / 40.0f),	// x position 
		rcl.bottom - 26,         // y position 
		static_cast<int>(9.0 * (rcl.right - rcl.left) / 40.0f),		// Button width
		26,					     // Button height
		ms_hDlg,			 // Parent window
		reinterpret_cast<HMENU>(IDC_TRANSEL),       // 
		ms_hInstance,
		nullptr);				// Pointer not needed


	//--------------------------------------------------------------
	hWndBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"取消选择",				// Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles
		static_cast<int>(2 * 9.0 * (rcl.right - rcl.left) / 40.0f),	// x position 
		rcl.bottom - 26,         // y position 
		static_cast<int>(9 * (rcl.right - rcl.left) / 40.0f),		// Button width
		26,					     // Button height
		ms_hDlg,			 // Parent window
		reinterpret_cast<HMENU>(IDC_CANLSEL),       // 
		ms_hInstance,
		nullptr);				// Pointer not needed

	//--------------------------------------------------------------
	hWndBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"取消所有",				// Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles
		static_cast<int>(3 * 9.0 * (rcl.right - rcl.left) / 40.0f),	// x position 
		rcl.bottom - 26,         // y position 
		static_cast<int>(9 * (rcl.right - rcl.left) / 40.0f),		// Button width
		26,					     // Button height
		ms_hDlg,			 // Parent window
		reinterpret_cast<HMENU>(IDC_CANLALL),       // 
		ms_hInstance,
		nullptr);				// Pointer not needed


	//--------------------------------------------------------------
	hWndBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"Close",				// Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles
		static_cast<int>(4 * 9.0 * (rcl.right - rcl.left) / 40.0f),	// x position 
		rcl.bottom - 26,         // y position 
		static_cast<int>(1 * (rcl.right - rcl.left) / 10.0f),		// Button width
		26,					     // Button height
		ms_hDlg,			 // Parent window
		reinterpret_cast<HMENU>(IDC_CLOSE),       // 
		ms_hInstance,
		nullptr);				// Pointer not needed

	//--------------------------------------------------------------

}

//--------------------------------------------------------------
void TransferIndicator::Update()
{
	ListView_DeleteAllItems(m_hWndListView);

	m_iCurrentValidIntex = 0;

	for (auto it : ms_kItemContainer)
	{
		AddListViewItems(it.second);
	}

	DrawCircleNumber();
}

//--------------------------------------------------------------
HWND TransferIndicator::GetHWND()
{
	return ms_hDlg;
}

//--------------------------------------------------------------
bool TransferIndicator::AddListViewItems(ItemInfo* pItemInfo)
{

	// Returned current position.
	DWORD dwIndexSort = 0ul;

	if (pItemInfo != nullptr)
	{
		wchar_t szFileName[MAX_PATH] = { 0 };
		wchar_t szUserName[100] = { 0 };
		wchar_t szIP[50] = { 0 };

		::wcscpy(szFileName, pItemInfo->GetFileName().c_str());
		::wcscpy(szUserName, pItemInfo->GetUserNameW().c_str());
		::wcscpy(szIP, pItemInfo->GetUserIP().c_str());

		//	LVINSERTMARK lvim;
		LVITEM lvI = { 0 };

		ZeroMemory(&lvI, sizeof(lvI));

		lvI.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_PARAM;
		lvI.state = 0;
		lvI.stateMask = 0;
		lvI.iItem = m_iCurrentValidIntex;
		lvI.iImage = 0;
		lvI.lParam = reinterpret_cast<LPARAM>(pItemInfo->GetUserEvent());
		//lvI.pszText = const_cast<LPWSTR>(tempChar[0]);
		lvI.pszText = pItemInfo->GetItemFileType() == 
			TransferIndicator::ItemInfo::IFT_REGULARFILE ? L"FILE" : L"DIRECTORY";
		lvI.cchTextMax = MAX_PATH;

		// Insert a line.
		dwIndexSort = ListView_InsertItem(m_hWndListView, &lvI);

		// Change texts.
		ListView_SetItemText(m_hWndListView, dwIndexSort,
			1, pItemInfo->GetTransferType() == TransferIndicator::ItemInfo::TT_FINISH ? 
			L"FINISHed" : pItemInfo->GetTransferType() == TransferIndicator::ItemInfo::TT_PENDING ? 
			L"PENDing" : pItemInfo->GetTransferType() == TransferIndicator::ItemInfo::TT_FAILED ? 
			L"FAILed" : L"TRANSFERing");

		ListView_SetItemText(m_hWndListView, dwIndexSort,
			2, szUserName);

		ListView_SetItemText(m_hWndListView, dwIndexSort,
			3, szFileName/*const_cast<wchar_t*>(pItemInfo->GetFileName().c_str())*/);

		ListView_SetItemText(m_hWndListView, dwIndexSort,
			4, szIP);
	
		// Increase the index number.
		m_iCurrentValidIntex++;
	}

	return true;

}

//--------------------------------------------------------------
bool TransferIndicator::OnTransferALL()
{
	// String for IP address.
	wchar_t szState[20];

	int iSeleted = -1;
	//LPLVITEM pitem;
	LVITEM lvItem;

	lvItem.cchTextMax = MAX_PATH;
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_PARAM;
	lvItem.iItem = 0;

	//clear the IP container...
	m_ulIPContainer.clear();

	while (true)
	{
		iSeleted = ListView_GetNextItem(m_hWndListView, iSeleted, LVNI_ALL);
		if (iSeleted == -1)
			break;

		lvItem.iItem = iSeleted;

		// Get information from ViewList control...
		lvItem.iSubItem = 1;
		lvItem.pszText = szState;
		ListView_GetItem(m_hWndListView, &lvItem);

		if (::wcscmp(szState, L"PENDing") != 0)
		{
			continue;
		}

		m_ulIPContainer.insert(reinterpret_cast<HANDLE>(lvItem.lParam));
	}

	if (m_ulIPContainer.size() == 0)
	{
		return true;
	}
	else if (m_ulIPContainer.size() == 1)
	{
		for (auto it : m_ulIPContainer)
		{
			if (ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE)
			{
				// Enable event and show File box...
				bool bResult = false;
				wchar_t szTempFileName[MAX_PATH] = { 0 };
				::wcscpy(szTempFileName, ms_kItemContainer[it]->GetFileName().c_str());

				//Custom FileDialog...
				OPENFILENAME Ofn;

				::memset(&Ofn, 0, sizeof OPENFILENAME);

				// Initialize the OPENFILENAME members.  
				Ofn.lStructSize = sizeof OPENFILENAME;
				Ofn.hwndOwner = ms_hDlg;
				//Ofn.lpstrFilter = szFilter; 
				Ofn.lpstrFile = szTempFileName;
				Ofn.nMaxFile = MAX_PATH;

				bResult = static_cast<bool>(::GetSaveFileName(&Ofn));

				if (bResult)
				{
					SetFileName(it, wstring(szTempFileName));
					ms_kItemContainer[it]->SetTransferType(TransferIndicator::ItemInfo::TT_TRANSFERING);
					Update();
					::SetEvent(it);
				}


			}
			else
				goto TransAllTarget;
		}
	}
	else
	{
	TransAllTarget:
		// Enable events and show Directory box...
		wchar_t szTempDirName[MAX_PATH] = { 0 };
		bool bAlreadyHasName = false;
		bool bHasFiles = false;

		for (auto it : m_ulIPContainer)
		{		
			BROWSEINFO bi = { 0 };
			LPITEMIDLIST pIDList = nullptr;

			// No name.
			if (!bAlreadyHasName)
			{
				bi.hwndOwner = ms_hDlg;
				bi.pidlRoot = nullptr;
				bi.pszDisplayName = szTempDirName;
				ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE ?
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE FILEs" :
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE DIRECTORies";
				bi.ulFlags = BIF_RETURNONLYFSDIRS;
				bi.lpfn = nullptr;
				pIDList = ::SHBrowseForFolder(&bi);
			}	
			// Regular file.
			else if ((ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE) &&
				bAlreadyHasName)
			{
				bHasFiles = true;
				SetFileName(it, wstring(szTempDirName));
				GetMultiFileCoordinator()->AddSingleFile(it);
				continue;
			}
			// Directory.
			else
			{
				ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE ?
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE FILEs" :
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE DIRECTORies";

				SetFileName(it, wstring(szTempDirName));

				ms_kItemContainer[it]->SetTransferType(TransferIndicator::ItemInfo::TT_TRANSFERING);
				Update();
				::SetEvent(it);
				continue;
			}

			// First time process.
			if (pIDList)
			{
				::SHGetPathFromIDList(pIDList, szTempDirName);
				SetFileName(it, wstring(szTempDirName));
				
				if (ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE)
				{
					bHasFiles = true;
					GetMultiFileCoordinator()->AddSingleFile(it);
				}
				else
				{
					ms_kItemContainer[it]->SetTransferType(TransferIndicator::ItemInfo::TT_TRANSFERING);
					Update();
					::SetEvent(it);
				}

				bAlreadyHasName = true;
				
			}
			else
			{
				break;
			}

		}

		// Check if need to open the Multi-file transferring mechanism.
		if (bHasFiles)
		{
			GetMultiFileCoordinator()->BeginToProcess();
		}
		
	}

	// Clear all items.
	m_ulIPContainer.clear();

	return true;
}

//--------------------------------------------------------------
bool TransferIndicator::OnTransferSelected()
{
	// String for IP address.
	wchar_t szState[20];

	int iSeleted = -1;
	LVITEM lvItem;

	lvItem.cchTextMax = MAX_PATH;
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_PARAM;
	lvItem.iItem = 0;

	//clear the IP container...
	m_ulIPContainer.clear();

	while (true)
	{
		iSeleted = ListView_GetNextItem(m_hWndListView, iSeleted, LVNI_SELECTED);
		if (iSeleted == -1)
			break;

		lvItem.iItem = iSeleted;

		// Get information from ViewList control...
		lvItem.iSubItem = 1;
		lvItem.pszText = szState;
		ListView_GetItem(m_hWndListView, &lvItem);

		if (::wcscmp(szState, L"PENDing") != 0)
		{
			continue;
		}

		m_ulIPContainer.insert(reinterpret_cast<HANDLE>(lvItem.lParam));
	}

	if (m_ulIPContainer.size() == 0)
	{
		return true;
	}
	else if (m_ulIPContainer.size() == 1)
	{
		for (auto it : m_ulIPContainer)
		{
			if (ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE)
			{
				// Enable event and show File box...
				bool bResult = false;
				wchar_t szTempFileName[MAX_PATH] = { 0 };
				::wcscpy(szTempFileName, ms_kItemContainer[it]->GetFileName().c_str());

				//Custom FileDialog...
				OPENFILENAME Ofn;

				::memset(&Ofn, 0, sizeof OPENFILENAME);

				// Initialize the OPENFILENAME members.  
				Ofn.lStructSize = sizeof OPENFILENAME;
				Ofn.hwndOwner = ms_hDlg;
				//Ofn.lpstrFilter = szFilter; 
				Ofn.lpstrFile = szTempFileName;
				Ofn.nMaxFile = MAX_PATH;

				bResult = static_cast<bool>(::GetSaveFileName(&Ofn));

				if (bResult)
				{
					SetFileName(it, wstring(szTempFileName));
					ms_kItemContainer[it]->SetTransferType(TransferIndicator::ItemInfo::TT_TRANSFERING);
					Update();
					::SetEvent(it);
				}


			}
			else
				goto TransSelectTarget;
		}
	}
	else
	{
	TransSelectTarget:
		// Enable events and show Directory box...
		wchar_t szTempDirName[MAX_PATH] = { 0 };
		bool bAlreadyHasName = false;
		bool bHasFiles = false;

		for (auto it : m_ulIPContainer)
		{
			BROWSEINFO bi = { 0 };
			LPITEMIDLIST pIDList = nullptr;

			// No name.
			if (!bAlreadyHasName)
			{
				bi.hwndOwner = ms_hDlg;
				bi.pidlRoot = nullptr;
				bi.pszDisplayName = szTempDirName;
				ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE ?
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE FILEs" :
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE DIRECTORies";
				bi.ulFlags = BIF_RETURNONLYFSDIRS;
				bi.lpfn = nullptr;
				pIDList = ::SHBrowseForFolder(&bi);
			}
			// Regular file.
			else if ((ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE) &&
				bAlreadyHasName)
			{
				bHasFiles = true;
				SetFileName(it, wstring(szTempDirName));
				GetMultiFileCoordinator()->AddSingleFile(it);
				continue;
			}
			// Directory.
			else
			{
				ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE ?
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE FILEs" :
					bi.lpszTitle = L"<:))))><®  -SELECT WHERE TO SAVE DIRECTORies";

				SetFileName(it, wstring(szTempDirName));

				ms_kItemContainer[it]->SetTransferType(TransferIndicator::ItemInfo::TT_TRANSFERING);
				Update();
				::SetEvent(it);
				continue;
			}

			// First time process.
			if (pIDList)
			{
				::SHGetPathFromIDList(pIDList, szTempDirName);
				SetFileName(it, wstring(szTempDirName));

				if (ms_kItemContainer[it]->GetItemFileType() == TransferIndicator::ItemInfo::IFT_REGULARFILE)
				{
					bHasFiles = true;
					GetMultiFileCoordinator()->AddSingleFile(it);
				}
				else
				{
					ms_kItemContainer[it]->SetTransferType(TransferIndicator::ItemInfo::TT_TRANSFERING);
					Update();
					::SetEvent(it);
				}

				bAlreadyHasName = true;

			}
			else
			{
				break;
			}

		}

		// Check if need to open the Multi-file transferring mechanism.
		if (bHasFiles)
		{
			GetMultiFileCoordinator()->BeginToProcess();
		}

	}

	// Clear all items.
	m_ulIPContainer.clear();

	return true;
}

//--------------------------------------------------------------
bool TransferIndicator::OnCancelSelected()
{
	wchar_t szState[20];

	int iSeleted = -1;
	
	LVITEM lvItem;

	lvItem.cchTextMax = MAX_PATH;
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_PARAM;
	lvItem.iItem = 0;

	//clear the IP container...
	m_ulIPContainer.clear();

	while (true)
	{
		iSeleted = ListView_GetNextItem(m_hWndListView, iSeleted, LVNI_SELECTED);
		if (iSeleted == -1)
			break;

		lvItem.iItem = iSeleted;

		// Get information from ViewList control...
		lvItem.iSubItem = 1;
		lvItem.pszText = szState;
		ListView_GetItem(m_hWndListView, &lvItem);

		if (::wcscmp(szState, L"FAILed") == 0 ||
			::wcscmp(szState, L"FINISHed") == 0)
		{
			auto item = ms_kItemContainer.find(reinterpret_cast<HANDLE>(lvItem.lParam));
			if (item != ms_kItemContainer.end())
			{
				delete ms_kItemContainer[reinterpret_cast<HANDLE>(lvItem.lParam)];
				ms_kItemContainer.erase(item);
			}

			auto it = ms_kFileNameContainer.find(reinterpret_cast<HANDLE>(lvItem.lParam));

			if (it != ms_kFileNameContainer.end())
			{
				ms_kFileNameContainer.erase(it);
			}

			/*Update();*/

			continue;
		}
		else if (::wcscmp(szState, L"PENDing") != 0)
		{
			continue;
		}

		m_ulIPContainer.insert(reinterpret_cast<HANDLE>(lvItem.lParam));
	}

	Update();

	if (m_ulIPContainer.size() == 0)
	{
		return true;
	}
	else
	{
		// Enable events and set strings to nil...
		for (auto it : m_ulIPContainer)
		{	
			SetFileName(it, wstring(L""));
			::SetEvent(it);

		}
	}

	// Clear all items.
	m_ulIPContainer.clear();

	return true;
}

//--------------------------------------------------------------
bool TransferIndicator::OnCancelALL()
{
	wchar_t szState[20];

	int iSeleted = -1;
	LVITEM lvItem;

	lvItem.cchTextMax = MAX_PATH;
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_PARAM;
	lvItem.iItem = 0;

	//clear the IP container...
	m_ulIPContainer.clear();

	while (true)
	{
		iSeleted = ListView_GetNextItem(m_hWndListView, iSeleted, LVNI_ALL);
		if (iSeleted == -1)
			break;

		lvItem.iItem = iSeleted;

		// Get information from ViewList control...
		lvItem.iSubItem = 1;
		lvItem.pszText = szState;
		ListView_GetItem(m_hWndListView, &lvItem);

		if (::wcscmp(szState, L"FAILed") == 0 ||
			::wcscmp(szState, L"FINISHed") == 0)
		{
			auto item = ms_kItemContainer.find(reinterpret_cast<HANDLE>(lvItem.lParam));
			if (item != ms_kItemContainer.end())
			{
				delete ms_kItemContainer[reinterpret_cast<HANDLE>(lvItem.lParam)];
				ms_kItemContainer.erase(item);
			}

			auto it = ms_kFileNameContainer.find(reinterpret_cast<HANDLE>(lvItem.lParam));

			if (it != ms_kFileNameContainer.end())
			{
				ms_kFileNameContainer.erase(it);
			}
			
			Update();
			iSeleted--;

			continue;
		}
		else if (::wcscmp(szState, L"PENDing") != 0)
		{
			continue;
		}

		m_ulIPContainer.insert(reinterpret_cast<HANDLE>(lvItem.lParam));
	}

	if (m_ulIPContainer.size() == 0)
	{
		return true;
	}
	else
	{
		// Enable events and set strings to nil...
		for (auto it : m_ulIPContainer)
		{
			SetFileName(it, wstring(L""));
			::SetEvent(it);

		}
	}

	// Clear all items.
	m_ulIPContainer.clear();

	return true;
}

//--------------------------------------------------------------
wstring TransferIndicator::GetFileName(HANDLE hEvent)
{
	
	if (hEvent == nullptr)
	{
		return wstring(L"");
	}

	::WaitForSingleObject(m_hMutex, INFINITE);
	auto it = ms_kFileNameContainer.find(hEvent);

	if (it == ms_kFileNameContainer.end())
	{
		::ReleaseMutex(m_hMutex);
		return wstring(L"");
	}
	else
	{
		wstring szTempName = ms_kFileNameContainer[hEvent];
		::ReleaseMutex(m_hMutex);
		return szTempName;
		
	}

}

//--------------------------------------------------------------
void TransferIndicator::SetFinish(HANDLE hEvent, bool bNormal /*= true*/)
{
	if (hEvent == nullptr)
	{
		return;
	}


	auto item = ms_kItemContainer.find(hEvent);

	if (item != ms_kItemContainer.end())
	{
		ms_kItemContainer[hEvent]->SetTransferType(TransferIndicator::ItemInfo::TT_FINISH);
		::CloseHandle(hEvent);

		if (!bNormal)
		{
			delete ms_kItemContainer[hEvent];
			ms_kItemContainer.erase(item);

			// Delete the filename item in 'FileNameContainer'.
			auto it = ms_kFileNameContainer.find(hEvent);

			if (it != ms_kFileNameContainer.end())
			{
				ms_kFileNameContainer.erase(it);
			}
		}
		
		//Update();
		::SendMessage(ms_hDlg, WM_TRANSFERINDICATORUPDATE, 0, 0);
	}
}

//--------------------------------------------------------------
void TransferIndicator::SetFailed(HANDLE hEvent)
{
	if (hEvent == nullptr)
	{
		return;
	}

	auto item = ms_kItemContainer.find(hEvent);

	if (item != ms_kItemContainer.end())
	{
		ms_kItemContainer[hEvent]->SetTransferType(TransferIndicator::ItemInfo::TT_FAILED);
		::CloseHandle(hEvent);
		::SendMessage(ms_hDlg, WM_TRANSFERINDICATORUPDATE, 0, 0);
	}

}

//--------------------------------------------------------------
void TransferIndicator::SetFileName(HANDLE hEvent, wstring& szFileName)
{
	//
	
	if (!hEvent)
	{
		return;
	}

	::WaitForSingleObject(m_hMutex, INFINITE);
	ms_kFileNameContainer[hEvent] = szFileName;
	::ReleaseMutex(m_hMutex);
	
}

//--------------------------------------------------------------
void TransferIndicator::ShowTransferIndicator()
{
	//
	if (ms_hDlg)
	{
		::SetWindowPos(ms_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
		::AnimateWindow(ms_hDlg, 600, AW_CENTER | AW_ACTIVATE);
		Update();
		::SetWindowPos(ms_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

		::BringWindowToTop(ms_hDlg);
		::SetForegroundWindow(ms_hDlg);
	}
}

//--------------------------------------------------------------
void TransferIndicator::HideTransferIndicator()
{
	//
	if (ms_hDlg)
	{
		::AnimateWindow(ms_hDlg, 600, AW_CENTER | AW_HIDE);
	}
}

//--------------------------------------------------------------
TransferIndicator::MultiFileCoordinator* TransferIndicator::GetMultiFileCoordinator()
{
	//
	if (m_pMultiFileCoordinator == nullptr)
	{
		m_pMultiFileCoordinator = new MultiFileCoordinator;
	}

	return m_pMultiFileCoordinator;
}

//--------------------------------------------------------------
void TransferIndicator::DrawCircleNumber()
{
	HWND hPendWnd = ::GetDlgItem(ms_hDlg, IDC_STATIC_PENDS);
	wchar_t szText[50];

	int iPendingNum = 0;
	for (auto it : ms_kItemContainer)
	{
		if (it.second->GetTransferType() == ItemInfo::TT_PENDING)
		{
			iPendingNum++;
		}
	}

	swprintf(szText, L"PENDing | TOTAL ITEMs:  %d | %d", iPendingNum, 
		ms_kItemContainer.size());
	::SetDlgItemText(ms_hDlg, IDC_STATIC_PENDS, szText);
}

//--------------------------------------------------------------
//	Inner class: ItemInfo.
//--------------------------------------------------------------
TransferIndicator::ItemInfo::ItemInfo()
{
	//
}

//--------------------------------------------------------------
wstring TransferIndicator::ItemInfo::GetFileName()
{
	return m_szFileName;
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::SetFileName(wstring& szFileName)
{
	m_szFileName = szFileName;
}

//--------------------------------------------------------------
wstring TransferIndicator::ItemInfo::GetUserName()
{
	//
	return m_szUserName;
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::SetUserName(wstring& szUserName)
{
	//
	m_szUserName = szUserName;
}

//--------------------------------------------------------------
wstring TransferIndicator::ItemInfo::GetUserIP()
{
	//
	return m_szUserIP;
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::SetUserIP(wstring& szUserIP)
{
	//
	m_szUserIP = szUserIP;
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::SetUserEvent()
{
	//
	if (!m_hUserEvent)
	{
		return;
	}

	::SetEvent(m_hUserEvent);
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::ResetUserEvent()
{
	//
	if (!m_hUserEvent)
	{
		return;
	}

	::ResetEvent(m_hUserEvent);
}

//--------------------------------------------------------------
HANDLE TransferIndicator::ItemInfo::GetUserEvent()
{
	//
	return m_hUserEvent;
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::SetupUserEvent(HANDLE hEvent)
{
	//
	m_hUserEvent = hEvent;
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::SetTransferType(TransferType
	eTransferType)
{
	//
	m_eTransferType = eTransferType;
}

//--------------------------------------------------------------
TransferIndicator::ItemInfo::TransferType TransferIndicator::
ItemInfo::GetTransferType()
{
	//
	return m_eTransferType;
}

//--------------------------------------------------------------
void TransferIndicator::ItemInfo::SetItemFileType(ItemFileType
	eItemFileType)
{
	//
	m_eItemFileType = eItemFileType;
}

//--------------------------------------------------------------
TransferIndicator::ItemInfo::ItemFileType TransferIndicator::
ItemInfo::GetItemFileType()
{
	//
	return m_eItemFileType;
}

//--------------------------------------------------------------
//	Inner class: MultiFileCoordinator.
//--------------------------------------------------------------
TransferIndicator::MultiFileCoordinator::MultiFileCoordinator() :
m_bWorking(false), m_pProgressPtr(nullptr), m_hCurrentWorkingEvent(nullptr)
{
	//
	m_hWaitEvent = ::CreateEvent(nullptr, false, false, nullptr);
}

//--------------------------------------------------------------
void TransferIndicator::MultiFileCoordinator::AddSingleFile(HANDLE hEvent)
{
	//
	if (!hEvent)
	{
		return;
	}

	m_kEventQueue.push_back(hEvent);
}

//--------------------------------------------------------------
void TransferIndicator::MultiFileCoordinator::BeginToProcess()
{
	//
	if (!m_bWorking && (m_kEventQueue.size() > 0))
	{
		m_bWorking = true;

		// New thread.
		thread t1([&]()
		{
			//
			HANDLE hEvent = nullptr;

			m_CurrentWorkingMutex.lock();

			for (auto it = m_kEventQueue.begin(); it != m_kEventQueue.end(); m_CurrentWorkingMutex.lock())
			{			
				hEvent = *it;
				m_hCurrentWorkingEvent = hEvent;
				m_CurrentWorkingMutex.unlock();

				::ResetEvent(m_hWaitEvent);

				wstring szFullFileName;
				szFullFileName = TransferIndicator::ms_pTransferIndicator->GetFileName(hEvent);
				szFullFileName += L"\\";
				szFullFileName += TransferIndicator::ms_pTransferIndicator->ms_kItemContainer[hEvent]->GetFileName();
				TransferIndicator::ms_pTransferIndicator->SetFileName(hEvent, szFullFileName);
				TransferIndicator::ms_pTransferIndicator->ms_kItemContainer[hEvent]->
					SetTransferType(TransferIndicator::ItemInfo::TT_TRANSFERING);
				//TransferIndicator::ms_pTransferIndicator->Update();
				::PostMessage(ms_hDlg, WM_TRANSFERINDICATORUPDATE, 0, 0);	
				::SetEvent(hEvent);

				WaitForEvent();

				m_mutex.lock();
				for (auto item = m_kEventQueue.begin(); item != m_kEventQueue.end(); item++)
				{
					if (*it == *item)
					{
						it = m_kEventQueue.erase(it);
						break;
					}
				}
				m_mutex.unlock();
			}

			m_CurrentWorkingMutex.unlock();
			m_pProgressPtr = nullptr;
			m_bWorking = false;
		});

		t1.detach();
	}
}

//--------------------------------------------------------------
bool TransferIndicator::MultiFileCoordinator::TestCurWorkingEvent(HANDLE hEvent)
{
	bool bResult = false;

	m_CurrentWorkingMutex.lock();
	if (m_hCurrentWorkingEvent == hEvent)
	{
		bResult = true;
		::SetEvent(m_hWaitEvent);
	}	
	m_CurrentWorkingMutex.unlock();

	return bResult;
}

//--------------------------------------------------------------
void TransferIndicator::MultiFileCoordinator::StopAndClearPipeline()
{
	//
	m_pProgressPtr = nullptr;
	m_kEventQueue.clear();
	SetWaitEvent();
}

//--------------------------------------------------------------
void TransferIndicator::MultiFileCoordinator::RemoveFile(HANDLE hEvent)
{
	//
	for (auto it = m_kEventQueue.begin(); it != m_kEventQueue.end(); it++)
	{
		if (*it == hEvent)
		{
			m_kEventQueue.erase(it);
			break;
		}
	}
}

//--------------------------------------------------------------
bool TransferIndicator::MultiFileCoordinator::HasFile(HANDLE hEvent)
{
	//
	bool bResult = false;

	m_mutex.lock();
	if (m_kEventQueue.size() > 0)
	{
		for (auto it : m_kEventQueue)
		{
			bResult = true;
			break;
		}
	}
	m_mutex.unlock();

	return bResult;
}

//--------------------------------------------------------------
bool TransferIndicator::MultiFileCoordinator::HasNext()
{
	//
	bool bResult = false;

	m_mutex.lock();

	if (m_bWorking)
	{
		if (m_kEventQueue.size() > 1)
		{
			bResult = true;
		}
	}
	else
	{
		if (m_kEventQueue.size() > 0)
		{
			bResult = true;
		}
	}
		
	m_mutex.unlock();

	return bResult;
}

//--------------------------------------------------------------
void* TransferIndicator::MultiFileCoordinator::GetProgressDlgPtr()
{
	return m_pProgressPtr;
}

//--------------------------------------------------------------
void TransferIndicator::MultiFileCoordinator::SetProgressDlgPtr(
	void* pProgressPtr)
{
	m_pProgressPtr = pProgressPtr;
}

//--------------------------------------------------------------
void TransferIndicator::MultiFileCoordinator::WaitForEvent()
{
	::WaitForSingleObject(m_hWaitEvent, INFINITE);
}

//--------------------------------------------------------------
void TransferIndicator::MultiFileCoordinator::SetWaitEvent()
{
	::SetEvent(m_hWaitEvent);
}

//--------------------------------------------------------------


