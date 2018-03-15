//--------------------------------------------------------------
//	SettingsDialog.cpp.
//	6/25/2013.		by bubo.
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "SettingsDialog.h"
#include "resource.h"

using namespace cinderella;

//--------------------------------------------------------------
//	Initialize static variables...
//--------------------------------------------------------------
SettingsDialog* SettingsDialog::ms_pkSettingsDialog = nullptr;
HINSTANCE SettingsDialog::ms_hInstance = nullptr;
HWND SettingsDialog::ms_hWndParent = nullptr;

//--------------------------------------------------------------
SettingsDialog::SettingsDialog()
{
	//
}

//--------------------------------------------------------------
SettingsDialog::SettingsDialog(SettingsDialog&)
{
	//
}

//--------------------------------------------------------------
SettingsDialog::~SettingsDialog()
{
	//
}

//--------------------------------------------------------------
SettingsDialog* SettingsDialog::GetSingleton()
{
	if (ms_pkSettingsDialog == nullptr)
	{
		ms_pkSettingsDialog = new SettingsDialog();
	}

	return ms_pkSettingsDialog;
}

//--------------------------------------------------------------
void SettingsDialog::DestroyInstance()
{
	if (ms_pkSettingsDialog)
	{
		delete ms_pkSettingsDialog;
		ms_pkSettingsDialog = nullptr;
	}
}

//--------------------------------------------------------------
bool SettingsDialog::Initialize(HWND hWndParent, HINSTANCE hInstance)
{
	ms_hWndParent = hWndParent;
	ms_hInstance = hInstance;

	HKEY hKey = nullptr;
	DWORD dwDisposition;
	int iInfo = 0;
	DWORD dwType = REG_SZ;
	DWORD dwSize = sizeof m_szName;

	if (::RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\LocalMessager",
		NULL, KEY_ALL_ACCESS, &hKey) != ERROR_SUCCESS)
	{
		// Create new keys...
		if ((iInfo = ::RegCreateKeyEx(
			HKEY_CURRENT_USER,          
			L"SOFTWARE\\LocalMessager",         
			0,             
			NULL,             
			REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS,
			NULL,           
			&hKey,          
			&dwDisposition 
			)) != ERROR_SUCCESS)
		{
			iInfo = GetLastError();
			// Will show Information later...
		}

		// Setup the default key values...
		if(::RegSetValueEx(hKey, L"Name", 0, REG_SZ, 
			reinterpret_cast<const BYTE*>(L"bubo"), 
			sizeof(L"bubo")) != ERROR_SUCCESS)
		{
			return false;
		}

		if(::RegSetValueEx(hKey, L"IPMask", 0, REG_SZ, 
			reinterpret_cast<const BYTE*>(L"255.255.255.255"), 
			sizeof(L"255.255.255.255")) != ERROR_SUCCESS)
		{
			return false;
		}

		if (::RegSetValueEx(hKey, L"IPMask_V6", 0, REG_SZ,
			reinterpret_cast<const BYTE*>(L"FF16::f"),
			sizeof(L"FF16::f")) != ERROR_SUCCESS)
		{
			return false;
		}

		::wcscpy(m_szName, L"bubo");
		::wcscpy(m_szIPMask, L"FF16::f");


		CreateUI();

	}
	else
	{
		// Retrieve values...
		RetrieveCurrentPosition();

		::RegQueryValueEx(hKey, L"Name", NULL, &dwType, 
			reinterpret_cast<LPBYTE>(m_szName), &dwSize);

		::RegQueryValueEx(hKey, L"IPMask_V6", NULL, &dwType, 
			reinterpret_cast<LPBYTE>(m_szIPMask), &dwSize);
	
	}

	/*::wcscpy(m_szIPMask, TEXT("FF16::f"));*/
	::RegCloseKey(hKey);

	return true;

}

//--------------------------------------------------------------
HWND SettingsDialog::CreateUI()
{
	//Create the Dialog box...
	/*m_hWndDlg = ::CreateDialog (ms_hInstance, MAKEINTRESOURCE (IDD_DIALOGSETTINGS),
		ms_hWndParent, fnSettingsDialog);*/

	::DialogBox (ms_hInstance, MAKEINTRESOURCE (IDD_DIALOGSETTINGS),
		ms_hWndParent, fnSettingsDialog);

	return m_hWndDlg;
}

//--------------------------------------------------------------
INT_PTR CALLBACK SettingsDialog::fnSettingsDialog(HWND hDlg, 
												  UINT message, 
												  WPARAM wParam, 
												  LPARAM lParam)
{
	POINT point;

	switch (message)
	{
	case WM_INITDIALOG:

		OnInitDialog (hDlg);

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
		::ClientToScreen(hDlg, &point);
		::PostMessage(hDlg, WM_NCLBUTTONUP, static_cast<WPARAM>(HTCAPTION),
			MAKELPARAM ( point.x, point.y ));

		return true;


	case WM_COMMAND:

		switch (LOWORD (wParam))
		{
		case IDOK:

			::AnimateWindow(hDlg, 600, AW_CENTER | AW_HIDE);
			::EndDialog(hDlg, 0);

			ms_pkSettingsDialog->WirteToRegister(hDlg);

			return true;

		case IDCANCEL:

			::AnimateWindow(hDlg, 600, AW_CENTER | AW_HIDE);
			::EndDialog(hDlg, 0);

			return true;

		}

		break;

	}

	return false;
}

//--------------------------------------------------------------
void SettingsDialog::OnInitDialog(HWND hDlg)
{
	HKEY hKey;
	int iInfo = 0;
	DWORD dwType = REG_SZ;
	DWORD dwSize = 200ul;
	HWND hWndName = nullptr, hWndIPMask = nullptr;

	hWndName = ::GetDlgItem(hDlg, IDC_EDITNAME);
	hWndIPMask = ::GetDlgItem(hDlg, IDC_EDITIPMASK);

	::RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\LocalMessager",
		NULL, KEY_ALL_ACCESS, &hKey);

	if (hWndIPMask && hWndName)
	{
		// Retrieve values...
		::RegQueryValueEx(hKey, L"Name", nullptr, &dwType, 
			reinterpret_cast<LPBYTE>(ms_pkSettingsDialog->m_szName), &dwSize);

		::RegQueryValueEx(hKey, L"IPMask_V6", nullptr, &dwType, 
			reinterpret_cast<LPBYTE>(ms_pkSettingsDialog->m_szIPMask), &dwSize);

		::SetWindowText(hWndName, ms_pkSettingsDialog->m_szName);
		::SetWindowText(hWndIPMask, ms_pkSettingsDialog->m_szIPMask);

	}
	
	::RegCloseKey(hKey);

	::AnimateWindow (hDlg, 600, AW_CENTER | AW_ACTIVATE );

}

//--------------------------------------------------------------
void SettingsDialog::WirteToRegister(HWND hDlg)
{
	HKEY hKey;
	int iInfo = 0;
	DWORD dwType = REG_SZ;
	DWORD dwSize = sizeof m_szName;
	HWND hWndName = nullptr, hWndIPMask = nullptr;

	hWndName = ::GetDlgItem(hDlg, IDC_EDITNAME);
	hWndIPMask = ::GetDlgItem(hDlg, IDC_EDITIPMASK);

	::GetWindowText(hWndName, ms_pkSettingsDialog->m_szName, 100);
	::GetWindowText(hWndIPMask, ms_pkSettingsDialog->m_szIPMask, 100);

	::RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\LocalMessager",
		NULL, KEY_ALL_ACCESS, &hKey);

	// Write the key values to register...
	::RegSetValueEx(hKey, L"Name", 0, REG_SZ, 
		reinterpret_cast<const BYTE*>(ms_pkSettingsDialog->m_szName), 
		sizeof(ms_pkSettingsDialog->m_szName));

	::RegSetValueEx(hKey, L"IPMask_V6", 0, REG_SZ, 
		reinterpret_cast<const BYTE*>(ms_pkSettingsDialog->m_szIPMask), 
		sizeof(ms_pkSettingsDialog->m_szIPMask));
	
	::RegCloseKey(hKey);

}

//--------------------------------------------------------------
const wchar_t* SettingsDialog::GetIPMask() const
{
	return m_szIPMask;
}

//--------------------------------------------------------------
const wchar_t* SettingsDialog::GetName() const
{
	return m_szName;
}

//--------------------------------------------------------------
bool SettingsDialog::SaveCurrentPosition()
{
	HKEY hKey;
	RECT kRect;
	::GetWindowRect(ms_hWndParent, &kRect);

	::RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\LocalMessager",
		NULL, KEY_ALL_ACCESS, &hKey);

	if(::RegSetValueEx(hKey, L"XPos", 0, REG_DWORD, 
		reinterpret_cast<const BYTE*>(&(kRect.left)), 
		sizeof(kRect.left)) != ERROR_SUCCESS)
	{
		return false;
	}

	if(::RegSetValueEx(hKey, L"YPos", 0, REG_DWORD, 
		reinterpret_cast<const BYTE*>(&(kRect.top)), 
		sizeof(kRect.top)) != ERROR_SUCCESS)
	{
		return false;
	}

	::RegCloseKey(hKey);

	return true;
}

//--------------------------------------------------------------
bool SettingsDialog::RetrieveCurrentPosition()
{
	HKEY hKey;
	int iInfo = 0;
	DWORD dwType = REG_DWORD;
	DWORD dwSize = sizeof(long);
	RECT kRect;
	long lWidth = 0l, lHeight = 0l;

	::GetWindowRect(ms_hWndParent, &kRect);
	lWidth = kRect.right - kRect.left;
	lHeight = kRect.bottom - kRect.top;

	::RegOpenKeyEx(HKEY_CURRENT_USER, L"SOFTWARE\\LocalMessager",
		NULL, KEY_ALL_ACCESS, &hKey);


	// Retrieve values...
	::RegQueryValueEx(hKey, L"XPos", NULL, &dwType, 
		reinterpret_cast<LPBYTE>(&(kRect.left)), &dwSize);

	

	::RegQueryValueEx(hKey, L"YPos", NULL, &dwType, 
		reinterpret_cast<LPBYTE>(&(kRect.top)), &dwSize);

	::RegCloseKey(hKey);

	// adjust values...
	if (kRect.left < -1000)
	{
		kRect.left = 0;
	}
	else if (kRect.left > 6000)
	{
		kRect.left = 0;
	}

	if (kRect.top < -10)
	{
		kRect.top = 0;
	}
	else if (kRect.top > 6000)
	{
		kRect.top = 0;
	}

	::MoveWindow(ms_hWndParent, kRect.left, kRect.top, 
		lWidth, lHeight, true);

	return true;

}

//--------------------------------------------------------------
bool SettingsDialog::IsDialogMsg(LPMSG pMsg)
{
	// Message loop...
	if (!ms_pkSettingsDialog)
	{
		return false;
	}
	else if (ms_pkSettingsDialog->m_hWndDlg)
	{
		if (::IsDialogMessage(ms_pkSettingsDialog->m_hWndDlg, pMsg))
			return true;
	}

	return false;
}

//--------------------------------------------------------------



