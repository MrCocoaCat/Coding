//--------------------------------------------------------------
//	UserDialog.cpp.		Dialog Wrapper class. 
//	5/27/2013.			by bubo.
//	Modified			03/11/2014.
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include <WinSock2.h>
#include "UserDialog.h"
#include <commctrl.h>
#include <Mstcpip.h>
#include "UIManager.h"
#include "resource.h"
#include "Commander.h"
#include <Windowsx.h>
#include <Shlobj.h>
#include <Ws2tcpip.h>
#include <thread>


using namespace cinderella;

//--------------------------------------------------------------
//	Global variables...
//--------------------------------------------------------------
#if _WIN64
TCHAR szVersion[] = TEXT("v1.4  64Bit");
#else
TCHAR szVersion[] = TEXT("v1.4  32Bit");
#endif


//--------------------------------------------------------------
//	Initialize static variables...
//--------------------------------------------------------------
map<HWND, cinderella::UserDialog*> UserDialog::ms_pUserDialogContainer;
Communicator::UserData* UserDialog::ms_pUserData = nullptr;
HWND UserDialog::ms_hViewList = nullptr;
UIManager* UserDialog::ms_pUiManager = nullptr;
int UserDialog::ms_iDlgPosX = 0;
int UserDialog::ms_iDlgPosY = 0;
bool UserDialog::ms_bDlgPos = false;
bool UserDialog::ms_bLButtonDown = false;
HHOOK UserDialog::ms_hHook = nullptr;

//--------------------------------------------------------------
UserDialog::UserDialog (HINSTANCE hInstance, HWND hParent, 
					   Communicator::UserData* pUserData/* = nullptr*/, 
					   bool bGobal /*= false*/)
{
	m_bGlobal = bGobal;
	wchar_t szAddrIPv6[50] = { 0 };

	if (pUserData)
	{
		// Convert the IPv6 address to wstring.
		::InetNtopW(AF_INET6, &((pUserData->ClientAddr).sin6_addr), szAddrIPv6, 50);
		m_szIP = szAddrIPv6;
	}
	
	ms_pUserData = pUserData;

	//Create the Dialog box...
	m_hDlg = ::CreateDialog (hInstance, MAKEINTRESOURCE (IDD_DIALOGUSER),
		hParent, fnUserDialog);

	
	
	if (m_hDlg && !m_bGlobal)
	{
		ms_pUserDialogContainer [m_hDlg] = this;
	}
}

//--------------------------------------------------------------
UserDialog::~UserDialog ()
{
	auto it = ms_pUserDialogContainer.find (m_hDlg);

	if (it != ms_pUserDialogContainer.end ())
	{
		ms_pUserDialogContainer.erase (it);
	}

	if (ms_pUiManager->m_bGlobalDlg)
	{
		ms_pUiManager->m_bGlobalDlg = false;
	}	

}

//--------------------------------------------------------------
void UserDialog::Initialize (HWND hViewList)
{
	ms_hViewList = hViewList;

	//--------------------------------------------------------------
	//	Hook messages.
	//--------------------------------------------------------------
	ms_hHook = ::SetWindowsHookEx(WH_GETMESSAGE, fnGetMsgProc, nullptr, 
		::GetCurrentThreadId());

	//--------------------------------------------------------------

}

//--------------------------------------------------------------
INT_PTR CALLBACK UserDialog::fnUserDialog (HWND hDlg, UINT message, 
											  WPARAM wParam, 
											  LPARAM lParam)
{
	//Procedure for handling messages...
	POINT point = { 0 };
	TCHAR szFileName[MAX_PATH] = { 0 };

	switch (message)
	{
	case WM_INITDIALOG:

		OnInitDialog (hDlg);

		return true;

		//--------------------------------------------------------------
		//	Moving dialog window and hooking messages...
		//--------------------------------------------------------------
	case WM_LBUTTONDOWN:
		ms_bLButtonDown = true;

		return true;

	case WM_MOUSEMOVE:

		if ( wParam & MK_LBUTTON )
		{
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			::ClientToScreen(hDlg, &point);
			::PostMessage(hDlg, WM_NCLBUTTONDOWN, static_cast<WPARAM>(HTCAPTION), 
				MAKELPARAM( point.x, point.y ));

		}

		return true;

	case WM_LBUTTONUP:

		point.x = LOWORD (lParam);
		point.y = HIWORD (lParam);
		::ClientToScreen (hDlg, &point);
		::PostMessage (hDlg, WM_NCLBUTTONUP, static_cast<WPARAM>(HTCAPTION), 
			MAKELPARAM ( point.x, point.y ));

		return true;
		
		//--------------------------------------------------------------
		//	Drag and Drop...
		//--------------------------------------------------------------
	case WM_DROPFILES:
		// Retrieve the number and type of the file...
		for (int iI = 0; iI < ::DragQueryFile(
			reinterpret_cast<HDROP>(wParam), 0xFFFFFFFF, szFileName, MAX_PATH); iI++)
		{
			if (::DragQueryFile((HDROP)wParam, iI, szFileName, MAX_PATH) != 0)
			{
				// Error.
				if (INVALID_FILE_ATTRIBUTES == GetFileAttributes(szFileName))
				{
					return 0;
				}
				// Directory.
				else if (FILE_ATTRIBUTE_DIRECTORY & GetFileAttributes(szFileName))
				{
					if (ms_pUserDialogContainer.find(hDlg) != ms_pUserDialogContainer.end())
					{
						ms_pUserDialogContainer[hDlg]->OnSendDir(szFileName);
					}
					else if (ms_pUiManager->m_pGolbalUserDlg)
					{
						ms_pUiManager->m_pGolbalUserDlg->OnSendDir(szFileName);
					}
				}
				// File.
				else
				{
					if (ms_pUserDialogContainer.find(hDlg) != ms_pUserDialogContainer.end())
					{
						ms_pUserDialogContainer[hDlg]->OnSendFile(szFileName);
					}
					else if (ms_pUiManager->m_pGolbalUserDlg)
					{
						ms_pUiManager->m_pGolbalUserDlg->OnSendFile(szFileName);
					}
				}
	
				//--------------------------------------------------------------
				//	End of if of determining type of file.
				//--------------------------------------------------------------
			}

			//--------------------------------------------------------------
			//	End of if of determining number of file.
			//--------------------------------------------------------------
		}

		//--------------------------------------------------------------
		//	End of for statement.
		//--------------------------------------------------------------
	
		return true;

	case WM_COMMAND:

		switch (LOWORD (wParam))
		{
		case IDOK:

			if (ms_pUserDialogContainer.find (hDlg) != ms_pUserDialogContainer.end ())
			{
				ms_pUserDialogContainer[hDlg]->OnTransmit ();
			}
			else if (ms_pUiManager->m_pGolbalUserDlg)
			{
				ms_pUiManager->m_pGolbalUserDlg->OnTransmit ();
			}
			
			return true;

		case IDCANCEL:

			::AnimateWindow(hDlg, 600, AW_CENTER | AW_HIDE);
			::DestroyWindow(hDlg);
			
			if (ms_pUserDialogContainer.find (hDlg) != ms_pUserDialogContainer.end ())
			{
				delete ms_pUserDialogContainer[hDlg];
			}
			else if (ms_pUiManager->m_pGolbalUserDlg)
			{
				delete ms_pUiManager->m_pGolbalUserDlg;
				ms_pUiManager->m_pGolbalUserDlg = nullptr;
				
			}

			return true;

		case IDC_BUTTONSENDFILE:
			
			if (ms_pUserDialogContainer.find(hDlg) != ms_pUserDialogContainer.end ())
			{
				ms_pUserDialogContainer[hDlg]->OnSendFile ();
			}
			else if (ms_pUiManager->m_pGolbalUserDlg)
			{
				ms_pUiManager->m_pGolbalUserDlg->OnSendFile ();
			}
			
			return true;

		case IDC_BUTSENDDIR:

			if (ms_pUserDialogContainer.find(hDlg) != ms_pUserDialogContainer.end ())
			{
				ms_pUserDialogContainer[hDlg]->OnSendDir ();
			}
			else if (ms_pUiManager->m_pGolbalUserDlg)
			{
				ms_pUiManager->m_pGolbalUserDlg->OnSendDir ();
			}

			return true;

		}

		break;

	}

	return false;
}

//--------------------------------------------------------------
void UserDialog::OnInitDialog (HWND hDlg)
{
	RECT rect = { 0 };
	::GetWindowRect(hDlg, &rect);

	// Bring the window to the top.
	if (!ms_bDlgPos)
	{
		::SetWindowPos(hDlg, HWND_TOPMOST, (::GetSystemMetrics(SM_CXFULLSCREEN) -
			(rect.right - rect.left)) / 2, (::GetSystemMetrics(SM_CYFULLSCREEN) -
			(rect.bottom - rect.top)) / 2, 0, 0, SWP_NOSIZE);
	}
	else
	{
		::SetWindowPos(hDlg, HWND_TOPMOST, ms_iDlgPosX, ms_iDlgPosY, 0, 0, SWP_NOSIZE);
	}
	

	::SetDlgItemText(hDlg, IDC_STATICVERSION, szVersion);

	wchar_t szTotalChar[MAX_PATH];

	if (ms_pUiManager->m_bGlobalDlg)
	{
		::swprintf(szTotalChar, TEXT("BOX: TO ALL SELECTED USERs"));

		ms_pUiManager->m_bGlobalDlg = false;
	}
	else if (ms_pUserData)
	{
		GetInfo (szTotalChar, ms_pUserData);
	}
	else
	{
		GetInfo (szTotalChar);
	}
		
	::SetWindowText ( ::GetDlgItem ( hDlg, IDC_TITLE), szTotalChar);

	::AnimateWindow (hDlg, 600, AW_CENTER | AW_ACTIVATE );

	::SetWindowPos(hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
	
	::BringWindowToTop(hDlg);
	::SetForegroundWindow(hDlg);
	

	return;
}

//--------------------------------------------------------------
void UserDialog::OnExit ()
{
	// Testing code...
}

//--------------------------------------------------------------
void UserDialog::OnSendFile(TCHAR* pFileName)
{
	if (pFileName == nullptr)
	{
		bool bMultiFiles = false;

		const unsigned int MAXPATHSIZE = 1000;
		// buffer for file name
		wchar_t strFile[MAXPATHSIZE];
		// Set lpstrFile to '\0' so that GetOpenFileName does not 
		// use the contents of szFile to initialize itself.
		::memset(strFile, 0, MAXPATHSIZE);

		// common dialog box structure
		OPENFILENAME ofn;
		// Initialize OPENFILENAME
		::memset(&ofn, 0, sizeof OPENFILENAME);
		ofn.lStructSize = sizeof OPENFILENAME;
		//ofn.lpstrFilter = TEXT("All\0*.*\0Text\0*.TXT\0");
		ofn.hwndOwner = m_hDlg;
		ofn.lpstrFile = strFile;
		ofn.nMaxFile = MAXPATHSIZE;
		ofn.Flags = OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST |
			OFN_ALLOWMULTISELECT | OFN_EXPLORER;

		// Display the Open dialog box. 
		if (::GetOpenFileName(&ofn))
		{
			int iI = 0;
			wchar_t* pFile = ofn.lpstrFile;

			while (*pFile)
			{
				// Get the next file name. 
				pFile = ::wcschr(pFile, '\0');
				pFile++;
				iI++;

				if (iI > 2)
				{
					bMultiFiles = true;
					break;
				}
			}


			if (m_bGlobal)
			{
				for (auto it : ms_pUiManager->m_ulIPContainer)
				{
					if (bMultiFiles)
					{
						ms_pUiManager->m_pCommander->SendFile(it, strFile, true);
					}
					else
					{
						ms_pUiManager->m_pCommander->SendFile(it, strFile, false);
					}

				}

			}
			else
			{
				if (bMultiFiles)
				{
					ms_pUiManager->m_pCommander->SendFile(m_szIP, strFile, true);
				}
				else
				{
					ms_pUiManager->m_pCommander->SendFile(m_szIP, strFile, false);
				}

			}

		}
		// User cancel the process.
		else
		{
			return;
		}
	}
	// Send the file passed in the method as a parameter...
	else
	{
		if (m_bGlobal)
		{
			for (auto it : ms_pUiManager->m_ulIPContainer)
			{
				ms_pUiManager->m_pCommander->SendFile(it, pFileName, false);
			}

		}
		else
		{
			ms_pUiManager->m_pCommander->SendFile(m_szIP, pFileName, false);
		}
	}
	
	AddStringMyself(L"FILEs SENT :)");
	

	// Testing code...
	/*if (GetOpenFileName(&ofn)==TRUE) 
		hf = CreateFile(ofn.lpstrFile, 
		GENERIC_READ,
		0,
		(LPSECURITY_ATTRIBUTES) NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		(HANDLE) NULL);*/

}

//--------------------------------------------------------------
in6_addr UserDialog::GetInfo(wchar_t* szTotalString)
{
	DWORD i = 0;
	LVITEM lvItem;
	DWORD dwIndexInMem = 0;

	// Temporary chars for containing data. 
	// wchar_t szTotalChar[256];
	wchar_t Char1[MAX_PATH];
	wchar_t Char2[MAX_PATH];
	wchar_t* pTempChar[2] = {Char1, Char2};

	i = ListView_GetSelectionMark (ms_hViewList);

	lvItem.cchTextMax = 50;
	lvItem.state = 0;
	lvItem.stateMask = 0;
	lvItem.iImage = 0;
	lvItem.mask = LVIF_TEXT | LVIF_PARAM | LVIF_STATE | LVIF_IMAGE;
	lvItem.iItem = i;

	//Get information from ViewList control...
	for (DWORD32 j = 0; j < 2; j++)
	{
		lvItem.iSubItem = j;
		lvItem.pszText = pTempChar[j];
		ListView_GetItem (ms_hViewList, &lvItem);
	}

	if (szTotalString)
	{
		::swprintf (szTotalString, TEXT ("BOX: %s.     IP: %s"), 
			pTempChar[0], pTempChar[1]);
	}

	//convert the IP string to unsigned long...
	sockaddr_in6 addrLocal;
	/*wchar_t buf[MAX_PATH];
	LPCTSTR pp = buf;
	LPCTSTR* Terminator = &pp;*/
	::InetPtonW(AF_INET6, pTempChar[1], &addrLocal.sin6_addr);  // IPv6
	/*::RtlIpv6StringToAddressW(pTempChar[1], Terminator, &addrLocal.sin6_addr);*/
	
	return addrLocal.sin6_addr;

}

//--------------------------------------------------------------
in6_addr UserDialog::GetInfo(wchar_t* szTotalString,
								   Communicator::UserData* pUserData)
{
	if (szTotalString)
	{
		wchar_t* pTempChar = new wchar_t[50];
		::InetNtopW(AF_INET6, &((pUserData->ClientAddr).sin6_addr), pTempChar, 50);
		::swprintf(szTotalString, TEXT("BOX: %s.     IP: %s"),
			pUserData->GetUserNameW (), pTempChar);
	}

	return (pUserData->ClientAddr).sin6_addr;
}

//--------------------------------------------------------------
void UserDialog::OnTransmit ()
{
	//
	wchar_t* szTotalChar = new wchar_t[MAXDATASIZE]{0};
	::GetWindowText(GetDlgItem(m_hDlg, IDC_EDITINPUT), szTotalChar, MAXDATASIZE);
	szTotalChar[MAXDATASIZE - 1] = 0;

	::SetWindowText(::GetDlgItem(m_hDlg, IDC_EDITINPUT), TEXT(""));
	AddStringMyself(szTotalChar);

	if (m_bGlobal)
	{
		std::thread tSendMessages([&](wchar_t* szString)
		{
			for (auto it : ms_pUiManager->m_ulIPContainer)
			{
				ms_pUiManager->SendMessage(it, szString);
				::Sleep(15);
			}

			delete[] szString;

		}, szTotalChar);

		tSendMessages.detach();

	}
	else
	{
		ms_pUiManager->SendMessage (ms_pUserDialogContainer[m_hDlg]->GetIPString (), 
			szTotalChar);

		delete[] szTotalChar;
	}
		

	HWND hInputWnd = ::GetDlgItem (m_hDlg, IDC_EDITINPUT);	
	::SetFocus(hInputWnd);

	return;
}

//--------------------------------------------------------------
void UserDialog::AddString (const wchar_t* szString)
{
	::SetWindowPos(m_hDlg, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	::BringWindowToTop(m_hDlg);
	::SetForegroundWindow(m_hDlg);

	wchar_t szTemp[MAXDATASIZE * 16];
	wchar_t szTempIP[50];
	HWND hDisplayWnd = ::GetDlgItem (m_hDlg, IDC_EDITDISPLAY);

	//Retrieve the user's IP of string... 
	/*::InetNtopW(AF_INET6, &(ms_pUiManager->m_pCommander->GetCommunicator()
		->GetUserData (m_szIP)->ClientAddr.sin6_addr), szTempIP, 50);*/

	::GetWindowText(hDisplayWnd, szTemp, ::wcslen(szTemp));
	//wsprintf (szTemp, TEXT ("%sIP: %s: %s\r\n\r\n"), szTemp, szTempIP, szString);
	//::swprintf(szTemp, TEXT("IP: %s: %s\r\n"), szTempIP, szString);
	::swprintf(szTemp, TEXT("%s: %s\r\n"), ms_pUiManager->m_pCommander->GetCommunicator()
		->GetUserData(m_szIP)->GetUserNameW(), szString);
	Edit_SetSel (hDisplayWnd, -1, -1);
	Edit_ReplaceSel (hDisplayWnd, szTemp);

	::SetWindowPos(m_hDlg, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	return;
}

//--------------------------------------------------------------
void UserDialog::AddStringMyself(const wchar_t* szString)
{
	wchar_t szTemp[MAXDATASIZE * 16];
	wchar_t szTempIP[50];
	HWND hDisplayWnd = ::GetDlgItem (m_hDlg, IDC_EDITDISPLAY);

	//Retrieve the user's IP of string... 
	char szHostName[MAX_PATH];
	::gethostname(szHostName, MAX_PATH);
	ADDRINFOA kAddrInfo;
	ADDRINFOA hints;
	PADDRINFOA pkAddrInfo = & kAddrInfo;

	::memset(&hints, 0, sizeof (hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	//hints.ai_flags = /*AI_PASSIVE*/AI_NUMERICHOST;


	sockaddr_in6* pAddr;
	DWORD length = 50;

	::GetAddrInfoA(szHostName, nullptr, &hints, &pkAddrInfo);

	while (pkAddrInfo->ai_next)
	{
		pkAddrInfo = pkAddrInfo->ai_next;
		pAddr = (sockaddr_in6*)(pkAddrInfo->ai_addr);
		::InetNtopW(AF_INET6, &(pAddr->sin6_addr), szTempIP, 50);
	}
	
	freeaddrinfo(pkAddrInfo);
	//::WSAAddressToString(pAddr, pkAddrInfo->ai_addrlen, nullptr, szTempIP, &length);
	// Convert the IPv6 address to wstring.
	//::InetNtopW(AF_INET6, pAddr, szTempIP, 50);

	// Set the text...
	::GetWindowText(hDisplayWnd, szTemp, ::wcslen(szTemp));

	int i = ::wcslen(szString);

	//swprintf (szTemp, TEXT ("IP: %s: %s\r\n"), szTempIP, szString);
	swprintf(szTemp, TEXT("Me: %s\r\n"), /*szTempIP,*/ szString);

	i = ::wcslen(szTemp);
	Edit_SetSel (hDisplayWnd, -1, -1);
	Edit_ReplaceSel (hDisplayWnd, szTemp);

	return;
}

//--------------------------------------------------------------
void UserDialog::OnSendDir(TCHAR* pDirName)
{
	if (pDirName == nullptr)
	{
		wchar_t Buffer[MAX_PATH];

		BROWSEINFO bi;
		LPITEMIDLIST pIDList;


		bi.hwndOwner = m_hDlg;
		bi.pidlRoot = NULL;
		bi.pszDisplayName = Buffer;
		bi.lpszTitle = L"<:))))><®  -DIRECTORY";
		bi.ulFlags = BIF_RETURNONLYFSDIRS;
		bi.lpfn = NULL;
		//bi.iImage = IDI_ICON_MAIN;
		bi.lParam = 0;
		pIDList = ::SHBrowseForFolder(&bi);

		if (pIDList)
		{
			::SHGetPathFromIDList(pIDList, Buffer);

			if (m_bGlobal)
			{
				for (auto it : ms_pUiManager->m_ulIPContainer)
				{
					ms_pUiManager->m_pCommander->SendDir(it, Buffer);
				}

			}
			// User cancel the process.
			else
			{
				ms_pUiManager->m_pCommander->SendDir(m_szIP, Buffer);
			}

		}
		else
		{
			return;
		}
	}
	else
	{
		if (m_bGlobal)
		{
			for (auto it : ms_pUiManager->m_ulIPContainer)
			{
				ms_pUiManager->m_pCommander->SendDir(it, pDirName);
			}

		}
		else
		{
			ms_pUiManager->m_pCommander->SendDir(m_szIP, pDirName);
		}
	}
	
	AddStringMyself(L"DIRECTORies SENT :)");
}

//--------------------------------------------------------------
bool UserDialog::IsDialogMsg(LPMSG pMsg)
{
	//message loop...
	for (auto it : ms_pUserDialogContainer)
	{
		if(::IsDialogMessage(it.first, pMsg))
			return true;
	}

	if (ms_pUiManager->m_pGolbalUserDlg)
	{
		if(::IsDialogMessage(ms_pUiManager->m_pGolbalUserDlg->m_hDlg, pMsg))
			return true;
	}

	return false;
}

//--------------------------------------------------------------
//	Hook call back function.
//--------------------------------------------------------------
LRESULT CALLBACK UserDialog::fnGetMsgProc(int iCode, WPARAM wParam,
	LPARAM lParam)
{

	if (reinterpret_cast<LPMSG>(lParam)->message == WM_LBUTTONUP && ms_bLButtonDown)
	{
		RECT rect = { 0 };

		::GetWindowRect(reinterpret_cast<LPMSG>(lParam)->hwnd, &rect);
		ms_iDlgPosX = rect.left;
		ms_iDlgPosY = rect.top;
		ms_bDlgPos = true;
		ms_bLButtonDown = false;
	}

	//--------------------------------------------------------------
	//	Call the next hander...
	//--------------------------------------------------------------
	return ::CallNextHookEx(nullptr, iCode, wParam, lParam);

}

//--------------------------------------------------------------
void UserDialog::Shutdown()
{
	//--------------------------------------------------------------
	//	Unhook messages and set the handle to nullptr.
	//--------------------------------------------------------------
	if (ms_hHook)
	{
		::UnhookWindowsHookEx(ms_hHook);
		ms_hHook = nullptr;
	}

	//--------------------------------------------------------------

}

//--------------------------------------------------------------





