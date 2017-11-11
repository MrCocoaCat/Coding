//--------------------------------------------------------------
//	UserDialog.inl.
//	6/9/2013.		by bubo.
//--------------------------------------------------------------
using namespace cinderella;

//--------------------------------------------------------------
inline HWND UserDialog::GetWindow() const
{
	return m_hDlg;
};

//--------------------------------------------------------------
inline UserDialog* UserDialog::GetDlgPtrFromWindow(HWND hWnd)
{
	auto it = ms_pUserDialogContainer.find(hWnd);

	if (it == ms_pUserDialogContainer.end())
	{
		return nullptr;
	}
	else
	{
		return ms_pUserDialogContainer[hWnd];
	}
}

//--------------------------------------------------------------
inline void UserDialog::SetUIManager(UIManager* pUIManager)
{
	ms_pUiManager = pUIManager;
}

//--------------------------------------------------------------
inline UIManager* UserDialog::GetUIManager()
{
	return ms_pUiManager;
}

//--------------------------------------------------------------
inline wstring UserDialog::GetIPString()
{
	//
	return m_szIP;
}

//--------------------------------------------------------------
inline void UserDialog::SetIPString(wstring& IPString)
{
	//
	m_szIP = IPString;
}

//--------------------------------------------------------------

