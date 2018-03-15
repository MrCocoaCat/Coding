//--------------------------------------------------------------
//	UIManager.cpp.
//	05/24/2013.		by bubo.
//	12/19/2013		Modified.
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "UIManager.h"
#include <commctrl.h>
#include <Mstcpip.h>
#include "resource.h"
#include "Commander.h"
#include "UserDialog.h"
#include <Shlobj.h>
#include "ProgressDialog.h"
#include "SettingsDialog.h"
#include "TransferIndicator.h"

//--------------------------------------------------------------
using namespace cinderella;

//--------------------------------------------------------------
//	Extern variables...
//--------------------------------------------------------------
extern const unsigned short UDP_TEXT_PORT;

//--------------------------------------------------------------
UIManager::UIManager () : m_hWndListView (nullptr), m_hInstance (nullptr),
	m_iCurrentValidIntex (0), m_bAcceptFile (false), 
	m_pGolbalUserDlg (nullptr), m_bGlobalDlg (false)
{
	//
	UserDialog::SetUIManager (this);
}

//--------------------------------------------------------------
void UIManager::SetMainWindow (HINSTANCE hInstance, HWND hMainWnd)
{
	m_hMainWindow = hMainWnd;
	m_hInstance = hInstance;
}

//--------------------------------------------------------------
void UIManager::SetCommander (Commander* pCommander)
{
	m_pCommander = pCommander;
}

//--------------------------------------------------------------
INT_PTR UIManager::ProcessEvent (int iEvent, LONG_PTR ulParameter)
{
	//Process messages...


	switch (iEvent)
	{
	case WM_NOTIFY:

		if (LVN_ITEMACTIVATE == ((reinterpret_cast<LPNMHDR>(ulParameter))->code))
		{

			//Get current selected user's IP from ListView control.
			in6_addr kIP = UserDialog::GetInfo(nullptr);

			wchar_t szAddrIPv6[50] = { 0 };

			// Convert the IPv6 address to wstring.
			::InetNtopW(AF_INET6, &(kIP), szAddrIPv6, 50);

			//Testing code...
			CreateInputDialog(wstring(szAddrIPv6));

			return true;
		}
		else if (BCN_DROPDOWN == ((reinterpret_cast<LPNMHDR>(ulParameter))->code))
		{
			NMBCDROPDOWN* pDropDown = (NMBCDROPDOWN*)ulParameter;
			if (pDropDown->hdr.hwndFrom = ::GetDlgItem(m_hMainWindow, IDC_BUTTONSENDALL))
			{

				// Get screen coordinates of the button.
				POINT pt;
				pt.x = pDropDown->rcButton.left;
				pt.y = pDropDown->rcButton.bottom;
				::ClientToScreen(pDropDown->hdr.hwndFrom, &pt);

				// Create a menu and add items.
				HMENU hSplitMenu = CreatePopupMenu();
				::AppendMenu(hSplitMenu, MF_BYPOSITION, IDC_BUTTONSENDALL, L"SEND MULTI SELECTed...");
				::AppendMenu(hSplitMenu, MF_BYPOSITION, MF_SEPARATOR, NULL);

				::AppendMenu(hSplitMenu, MF_BYPOSITION, IDC_SHOWALLPROGRESSES, L"显示所有进度盒...");
				::AppendMenu(hSplitMenu, MF_BYPOSITION, IDC_HIDEALLPROGRESSES, L"隐藏所有进度盒...");

				::AppendMenu(hSplitMenu, MF_BYPOSITION, IDC_SHOWTRANSFERINDICATOR, L"传送指示器...");

				::AppendMenu(hSplitMenu, MF_BYPOSITION, MF_SEPARATOR, NULL);
				::AppendMenu(hSplitMenu, MF_BYPOSITION, WM_SETTINGS, L"设置...");

				// Display the menu.
				::TrackPopupMenu(hSplitMenu, TPM_LEFTALIGN | TPM_TOPALIGN,
					pt.x, pt.y, 0, m_hMainWindow, nullptr);

				return true;
			}

		}

		break;

	case WM_SHOWDIALOGINPUT:

		// Executes codes in a private stack...
		{
			Communicator::UserData* pUserData = 
				reinterpret_cast<Communicator::UserData*>(ulParameter);

			in6_addr kIP = UserDialog::GetInfo (nullptr, pUserData);

			wchar_t szAddrIPv6[50] = { 0 };

			// Convert the IPv6 address to wstring.
			::InetNtopW(AF_INET6, &(kIP), szAddrIPv6, 50);

			//Testing code...
			CreateInputDialog(wstring(szAddrIPv6), pUserData);

		}

		return true;

	case WM_SHOWDIALOGPROGRESS:
		return reinterpret_cast<INT_PTR>(new ProgressDialog());

		/*return true;*/

	case IDOK:
		m_pCommander->GetCommunicator ()->BroadcastQueryInfo ();
		return true;

	case IDCANCEL:

		Commander::GetSingleton ()->Shutdown();
		::PostQuitMessage(0);
		return true;

	case IDC_BUTTONSENDALL:
		OnSelectAll ();
		return true;

	case IDC_SHOWALLPROGRESSES:

		ProgressDialog::ShowAllProgresses();

		return true;

	case IDC_HIDEALLPROGRESSES:

		ProgressDialog::HideAllProgresses();

		return true;

	case WM_SETTINGS:

		SettingsDialog::GetSingleton()->CreateUI();

		return true;

	case IDC_SHOWTRANSFERINDICATOR:
		TransferIndicator::GetSingleton()->ShowTransferIndicator();
		return true;

	default:
		break;
	}

	return false;
}

//--------------------------------------------------------------
void UIManager::UpdateContent ()
{
	//
	ListView_DeleteAllItems (m_hWndListView);
	const wchar_t* pChar[2];

	for (auto it : m_pCommander->GetCommunicator ()->GetUserContainer ())
	{
		//wchar_t* pTempChar = new wchar_t[50];

		wchar_t szAddrIPv6[50] = { 0 };

		// Convert the IPv6 address to wstring.
		::InetNtopW(AF_INET6, &((it.second->ClientAddr).sin6_addr), szAddrIPv6, 50);

		pChar[1] = szAddrIPv6;
		pChar[0] = it.second->GetUserNameW ();

		AddListViewItems (pChar);
	}
}

//--------------------------------------------------------------
void UIManager::ShowUserDialog(Communicator::UserDataText* pUserData)
{
	UserDialog* pUserDialog = nullptr;

	wchar_t szAddrIPv6[50] = { 0 };

	// Convert the IPv6 address to wstring.
	::InetNtopW(AF_INET6, &((pUserData->ClientAddr).sin6_addr), szAddrIPv6, 50);

	/*unsigned int ulIP = pUserData->ClientAddr.sin_addr.S_un.S_addr;*/

	::SendMessage(m_hMainWindow, WM_SHOWDIALOGINPUT, 0, LPARAM(pUserData));


	UserDialog::GetDlgPtrFromWindow(m_DialogsContainer[szAddrIPv6])->
		AddString (pUserData->GetUserData ());

}

//--------------------------------------------------------------
bool UIManager::InitListViewImageLists ()
{
	HICON hIconItem;     //  list-view items 
	HIMAGELIST hLarge;   // 
	HIMAGELIST hSmall;   //

	// set image list... 
	hLarge = ImageList_Create(::GetSystemMetrics(SM_CXICON),
		::GetSystemMetrics(SM_CYICON),
		ILC_MASK, 1, 1); 

	hSmall = ImageList_Create(::GetSystemMetrics(SM_CXSMICON),
		::GetSystemMetrics(SM_CYSMICON),
		ILC_MASK, 1, 1); 

	//Load icon to display on every line...
	hIconItem = ::LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_IFISHNEW));
	ImageList_AddIcon (hSmall, hIconItem);
	ImageList_AddIcon (hLarge, hIconItem);
	::DestroyIcon(hIconItem);

	ListView_SetImageList (m_hWndListView, hLarge, LVSIL_NORMAL); 
	ListView_SetImageList (m_hWndListView, hSmall, LVSIL_SMALL); 

	return true; 
}

//--------------------------------------------------------------
bool UIManager::InitlistViewColumns ()
{
	LVCOLUMN lvc;
	RECT rect = { 0 };

	::GetWindowRect(m_hWndListView, &rect);

	// Add columns.
	LPWSTR ColNames[] = {TEXT ("Name: "), TEXT ("IP address (IPv6): ")};

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.pszText = nullptr;
	lvc.iImage = 0;
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = (rect.right - rect.left) / 2.0f;
	
	for (int i = 0; i < 2; i++)
	{
		lvc.pszText = ColNames[i];
		lvc.iSubItem = i;
		
		ListView_InsertColumn(m_hWndListView, i, &lvc);
	}


	return true;
}

//--------------------------------------------------------------
bool UIManager::AddListViewItems (const wchar_t* tempChar[2])
{

	//
	DWORD dwIndexSort = 0;

	if (tempChar!= NULL)
	{

		//	LVINSERTMARK lvim;
		LVITEM lvI;

		ZeroMemory (&lvI, sizeof(lvI));

		lvI.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_IMAGE;
		lvI.state = 0;
		lvI.stateMask = 0;
		lvI.iItem = m_iCurrentValidIntex;
		lvI.iImage = 0;
		lvI.pszText = const_cast<LPWSTR>(tempChar[0]);
		lvI.cchTextMax = 50;

		dwIndexSort = ListView_InsertItem(m_hWndListView, &lvI);

		for (int i = 0; i < 1; i++)
		{
			lvI.pszText = const_cast<LPWSTR>(tempChar[i]);
			lvI.cchTextMax = ::lstrlen(lvI.pszText) + 2;
			
			ListView_SetItemText(m_hWndListView, dwIndexSort,
				i + 1, const_cast<LPWSTR>(tempChar[i + 1]));
		}

		m_iCurrentValidIntex++;
	}

	return true;

}

//--------------------------------------------------------------
void UIManager::Initialize ()
{
	CreateListView ();
	InitListViewImageLists ();
	InitlistViewColumns ();
	CreateMainButton();
	UserDialog::Initialize (m_hWndListView);
}

//--------------------------------------------------------------
void UIManager::CreateListView ()
{

	RECT rcl = { 0 };
	INITCOMMONCONTROLSEX icex;


	icex.dwSize = sizeof INITCOMMONCONTROLSEX;
	icex.dwICC = ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES;
	InitCommonControlsEx (&icex); 

	// Get the RECT of the main window.
	::GetClientRect (m_hMainWindow, &rcl); 

	m_hWndListView = ::CreateWindow (WC_LISTVIEW, 
		TEXT (""),  WS_CHILD | LVS_REPORT |WS_VISIBLE|WS_VSCROLL , 
		0, 
		0, 
		rcl.right - rcl.left, 
		rcl.bottom - rcl.top - 30, 
		m_hMainWindow, 
		reinterpret_cast<HMENU>(999), 
		m_hInstance, 
		nullptr);                             

	ListView_SetExtendedListViewStyle (m_hWndListView,
		LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

}

//--------------------------------------------------------------
void UIManager::SendMessage(wstring& szIP, wchar_t* szString)
{
	Communicator::UserDataText userDataText;

	userDataText.SetUserData(szString);
	userDataText.SetUserType(Communicator::TR_MSG);
	userDataText.SetUserNameW(m_pCommander->GetCommunicator()->GetLocalNameW());

	Communicator::UserDataText*  pUserData = static_cast<Communicator::UserDataText*>(
		m_pCommander->GetCommunicator()->GetUserData(szIP));

	if (!pUserData)
	{
		return;
	}

	sockaddr_in6 ClientAddrIn = pUserData->ClientAddr;
	ClientAddrIn.sin6_port = ::htons(UDP_TEXT_PORT);

	m_pCommander->GetCommunicator()->SendDataUDPText(&userDataText,
		&(ClientAddrIn));

}

//--------------------------------------------------------------
HWND UIManager::GetMainWindow ()
{
	return m_hMainWindow;
}

//--------------------------------------------------------------
bool UIManager::OnFileArrived(wchar_t* pFileName, wstring& szIP, 
	HANDLE* hEvent/* = nullptr*/)
{
	
	TransferIndicator::ItemInfo* pItemInfo = new TransferIndicator::ItemInfo;
	pItemInfo->SetFileName(wstring(pFileName));
	pItemInfo->SetItemFileType(TransferIndicator::ItemInfo::IFT_REGULARFILE);
	pItemInfo->SetTransferType(TransferIndicator::ItemInfo::TT_PENDING);
	pItemInfo->SetUserIP(szIP);
	if (m_pCommander->GetCommunicator()->GetUserData(szIP))
	{
		pItemInfo->SetUserName(wstring((m_pCommander->GetCommunicator()->GetUserData(szIP))->GetUserNameW()));
	}
	else
	{
		pItemInfo->SetUserName(wstring(L""));
	}

	*hEvent = TransferIndicator::GetSingleton()->AddTask(pItemInfo);

	::PostMessage(TransferIndicator::GetSingleton()->GetHWND(), WM_SHOWTRANSFERINDICATOR, 0ul, 0ul);

	::WaitForSingleObject(*hEvent, INFINITE);

	if (TransferIndicator::GetSingleton()->GetFileName(*hEvent) == L"")
	{
		return false;
	}
	else
	{
		::wcscpy(pFileName, TransferIndicator::GetSingleton()->GetFileName(*hEvent).c_str());
		return true;
	}
	
}

//--------------------------------------------------------------
bool UIManager::OnDirArrived(wchar_t* pDirName, wstring& szIP,
	HANDLE* hEvent /*= nullptr*/)
{

	TransferIndicator::ItemInfo* pItemInfo = new TransferIndicator::ItemInfo;
	pItemInfo->SetFileName(wstring(pDirName));
	pItemInfo->SetItemFileType(TransferIndicator::ItemInfo::IFT_DIRECTORY);
	pItemInfo->SetTransferType(TransferIndicator::ItemInfo::TT_PENDING);
	pItemInfo->SetUserIP(szIP);
	if (m_pCommander->GetCommunicator()->GetUserData(szIP))
	{
		pItemInfo->SetUserName(wstring((m_pCommander->GetCommunicator()->GetUserData(szIP))->GetUserNameW()));
	}
	else
	{
		pItemInfo->SetUserName(wstring(L"NONE*"));
	}

	*hEvent = TransferIndicator::GetSingleton()->AddTask(pItemInfo);

	::PostMessage(TransferIndicator::GetSingleton()->GetHWND(), WM_SHOWTRANSFERINDICATOR, 0ul, 0ul);

	::WaitForSingleObject(*hEvent, INFINITE);

	if (TransferIndicator::GetSingleton()->GetFileName(*hEvent) == L"")
	{
		return false;
	}
	else
	{
		::wcscpy(pDirName, TransferIndicator::GetSingleton()->GetFileName(*hEvent).c_str());
		return true;
	}

}

//--------------------------------------------------------------
void UIManager::OnSelectAll ()
{
	if (m_pGolbalUserDlg)
	{
		return;
	}

	//Temporary chars for containing data. 
	//wchar_t szTotalChar[256];
	wchar_t Char1[MAX_PATH];
	wchar_t Char2[MAX_PATH];
	wchar_t* pTempChar[2] = {Char1, Char2};

	int iSeleted = -1;
	LPLVITEM pitem;
	LVITEM lvItem;

	lvItem.cchTextMax = 50;
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_IMAGE;
	lvItem.iItem = 0;

	//clear the IP container...
	m_ulIPContainer.clear ();

	while (true)
	{
		iSeleted = ListView_GetNextItem (m_hWndListView, iSeleted, LVNI_SELECTED);
		if (iSeleted == -1)
			break;	

		lvItem.iItem = iSeleted;

		//Get information from ViewList control...
		for (DWORD32 j = 0; j < 2; j++)
		{
			lvItem.iSubItem = j;
			lvItem.pszText = pTempChar[j];
			ListView_GetItem (m_hWndListView, &lvItem);
		}

		//convert the IP string to unsigned long...
		/*IN_ADDR addrLocal;
		wchar_t buf[MAX_PATH];
		LPCTSTR pp = buf;
		LPCTSTR* Terminator = &pp;
		::RtlIpv4StringToAddress(pTempChar[1], true, Terminator, &addrLocal);*/

		m_ulIPContainer.insert(pTempChar[1]);
	}

	m_bGlobalDlg = true;
	m_pGolbalUserDlg = new UserDialog (m_hInstance, m_hMainWindow, nullptr, true);

}

//--------------------------------------------------------------
void UIManager::CreateInputDialog(wstring& szIP,
								  Communicator::UserData* pUserData /*= nullptr*/)
{
	UserDialog* pUserDialog = nullptr;

	auto it = m_DialogsContainer.find(szIP);

	// If the dialog box we want doesn't open, we create a new one...
	if (it == m_DialogsContainer.end ())
	{
		// Create a new UserDialog with Instance and MainWindow's handle as its parameters.
		pUserDialog = new UserDialog (m_hInstance, m_hMainWindow, pUserData);

		// Add the new Dialog box we just created into DialogsContainer.
		m_DialogsContainer[szIP] = pUserDialog->GetWindow();

		// Save the IP into UserDialog for using later...
		pUserDialog->SetIPString(szIP);

	}
	// If the handle of the Dialog in UserDialogContainer of UserDialog doesn't exist, 
	// We need to create a new one too...
	else if (!UserDialog::GetDlgPtrFromWindow (m_DialogsContainer[szIP]))
	{
		pUserDialog = new UserDialog (m_hInstance, m_hMainWindow, pUserData);
		m_DialogsContainer[szIP] = pUserDialog->GetWindow();
		pUserDialog->SetIPString (szIP);

	}

	return;
}

//--------------------------------------------------------------
void UIManager::CreateMainButton()
{
	RECT rcl = { 0 };
	::GetClientRect (m_hMainWindow, &rcl); 

	//--------------------------------------------------------------
	//	Create three buttons for the main window...
	//--------------------------------------------------------------
	HWND hwndMainBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"Refresh",				// Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles
		rcl.left,				// x position 
		rcl.bottom - 26,         // y position 
		1 * (rcl.right - rcl.left) / 4.0f,		// Button width
		26,					     // Button height
		m_hMainWindow,			 // Parent window
		reinterpret_cast<HMENU>(IDOK),       // 
		reinterpret_cast<HINSTANCE>(GetWindowLongPtr(m_hMainWindow, GWLP_HINSTANCE)), 
		nullptr);				// Pointer not needed

	::ShowWindow(hwndMainBtn, SW_SHOW);

	//--------------------------------------------------------------
	hwndMainBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"Send Multi...", /*◥*/        // Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_SPLITBUTTON,  // Styles
		1 * (rcl.right - rcl.left) / 4.0f,	// x position 
		rcl.bottom - 26,         // y position 
		2 * (rcl.right - rcl.left) / 4.0f,					 // Button width
		26,					     // Button height
		m_hMainWindow,			 // Parent window
		reinterpret_cast<HMENU>(IDC_BUTTONSENDALL),       // 
		reinterpret_cast<HINSTANCE>(GetWindowLongPtr(m_hMainWindow, GWLP_HINSTANCE)), 
		nullptr);				 // Pointer not needed

	::ShowWindow(hwndMainBtn, SW_SHOW);

	//--------------------------------------------------------------
	hwndMainBtn = ::CreateWindow(
		L"BUTTON",				// Predefined class; Unicode assumed
		L"Exit",				// Text will be defined later
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,  // Styles
		3 * (rcl.right - rcl.left) / 4.0f,			 // x position 
		rcl.bottom - 26,         // y position 
		1 * (rcl.right - rcl.left) / 4.0f + 1,		// Button width
		26,					     // Button height
		m_hMainWindow,			 // Parent window
		reinterpret_cast<HMENU>(IDCANCEL),       // 
		reinterpret_cast<HINSTANCE>(GetWindowLongPtr(m_hMainWindow, GWLP_HINSTANCE)), 
		nullptr);				// Pointer not needed

	::ShowWindow(hwndMainBtn, SW_SHOW);

	//--------------------------------------------------------------
	return;

}

//--------------------------------------------------------------




