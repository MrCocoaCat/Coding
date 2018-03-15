//--------------------------------------------------------------
//	Commander.cpp.
//	6/8/2013.		by bubo.
//	Modified		06/06/2014.
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "Commander.h"
#include "Communicator.h"
#include "SettingsDialog.h"


using namespace cinderella;

//--------------------------------------------------------------
//	Initialize global variables...
//--------------------------------------------------------------
HANDLE cinderella::g_hNamedMutex = nullptr;

//--------------------------------------------------------------
//	Initialize static variables...
//--------------------------------------------------------------
Commander* Commander::ms_pCommander = nullptr;

//--------------------------------------------------------------
Commander* Commander::GetSingleton ()
{
	if (ms_pCommander == nullptr)
	{
		ms_pCommander = new Commander ();
	}

	return ms_pCommander;
}

//--------------------------------------------------------------
void Commander::DestroySingleton ()
{
	if (g_hNamedMutex)
	{
		::CloseHandle(g_hNamedMutex);
		g_hNamedMutex = nullptr;
	}

	if (ms_pCommander)
	{
		if (ms_pCommander->m_pCommunicator)
		{
			delete ms_pCommander->m_pCommunicator;
			ms_pCommander->m_pCommunicator = nullptr;
		}

		if (ms_pCommander->m_pUIManager)
		{
			delete ms_pCommander->m_pUIManager;
			ms_pCommander->m_pUIManager = nullptr;
		}

		delete ms_pCommander;
		ms_pCommander = nullptr;
	}
}

//--------------------------------------------------------------
bool Commander::Initialize (HINSTANCE hInstance, HWND hWnd, int iPort)
{
	m_pCommunicator = new Communicator ();
	if (m_pCommunicator)
	{
		m_pCommunicator->SetCommander (this);

	}

	m_pUIManager = new UIManager ();

	if (m_pUIManager)
	{
		m_pUIManager->SetCommander(this);
		m_pUIManager->SetMainWindow (hInstance, hWnd);
		m_pUIManager->Initialize ();
	}

	ProgressDialog::Initialize(hWnd, hInstance);

	SettingsDialog::GetSingleton()->Initialize(hWnd, hInstance);

	Commander::GetSingleton ()->SetLocalNameW(
		const_cast<wchar_t*>(SettingsDialog::GetSingleton()->GetName()));
	Commander::GetSingleton ()->SetIPMask(
		const_cast<wchar_t*>(SettingsDialog::GetSingleton()->GetIPMask()));

	TransferIndicator::Initialize(hWnd, hInstance);
	TransferIndicator::GetSingleton()->CreateUI();

	if (!m_pCommunicator->Initialize(iPort))
		return false;

	return true;
}

//--------------------------------------------------------------
void Commander::RefreshData ()
{
	if (m_pUIManager)
	{
		m_pUIManager->UpdateContent ();
	}
}

//--------------------------------------------------------------
void Commander::SetCommunicator (Communicator* pCommunicator)
{
	m_pCommunicator = pCommunicator;
	pCommunicator->SetCommander (this);
}

//--------------------------------------------------------------
Commander::Commander () : m_pCommunicator (nullptr), m_pUIManager (nullptr)
{
	//
}

//--------------------------------------------------------------
void Commander::SetUIManager (UIManager* pUIManager)
{
	m_pUIManager = pUIManager;
	pUIManager->SetCommander (this);
}

//--------------------------------------------------------------
Communicator* Commander::GetCommunicator () const
{
	//
	return m_pCommunicator;
}

//--------------------------------------------------------------
UIManager* Commander::GetUIManager () const
{
	//
	return m_pUIManager;
}

//--------------------------------------------------------------
bool Commander::GetSavePath (wchar_t* pFileName)
{
	//
	return true;
}

//--------------------------------------------------------------
void Commander::SendFile(wstring& szIPString, wchar_t* szFileName,
						  bool bMultiFiles)
{
	//
	wchar_t szFullName[MAX_PATH];
	::memset(szFullName, 0, MAX_PATH);


	if (bMultiFiles)
	{
		wchar_t* pFile = szFileName;

		while (true)
		{ 
			// Get the next file...  
			pFile = ::wcschr(pFile, '\0');
			pFile++;

			if (*pFile == 0)
			{
				break;
			}

			swprintf(szFullName, L"%s\\%s", szFileName, pFile);
			m_pCommunicator->TransferDataTCP (szFullName, &(m_pCommunicator->
				GetUserData(szIPString)->ClientAddr), Communicator::FileHeader::FT_REGULAR);


		} 
	}
	else
	{
		m_pCommunicator->TransferDataTCP (szFileName, &(m_pCommunicator->
			GetUserData(szIPString)->ClientAddr), Communicator::FileHeader::FT_REGULAR);
	}

}


//--------------------------------------------------------------
void Commander::BroadcastInfo (bool bRegister/* = true*/)
{
	m_pCommunicator->BroadcastInfo (bRegister);
}


//--------------------------------------------------------------
void Commander::SetLocalNameW (wchar_t* pName)
{
	m_pCommunicator->SetLocalNameW (pName);
}

//--------------------------------------------------------------
void Commander::BroadcastQueryInfo ()
{
	m_pCommunicator->BroadcastQueryInfo ();
}

//--------------------------------------------------------------
void Commander::SetIPMask(wchar_t* szIPMask)
{
	m_pCommunicator->SetIPMask(szIPMask);
}

//--------------------------------------------------------------
void Commander::SendDir(wstring& szIPString, wchar_t* szDirName)
{
	//
	m_pCommunicator->TransferDataTCP (szDirName, &(m_pCommunicator->
		GetUserData(szIPString)->ClientAddr), Communicator::FileHeader::FT_DIRECTORY);
}

//--------------------------------------------------------------
void Commander::Shutdown()
{
	BroadcastInfo(false);
	::WSACleanup();
	SettingsDialog::GetSingleton()->SaveCurrentPosition();
	ProgressDialog::Shutdown();
	UserDialog::Shutdown();
	TransferIndicator::DestroySingleton();
}


//--------------------------------------------------------------
//	Global testing Singleton function.
//--------------------------------------------------------------
bool cinderella::TestSingleton()
{
	g_hNamedMutex = ::CreateMutex(nullptr, false, L"$FishMessenger$");

	if (g_hNamedMutex)
	{
		if (ERROR_ALREADY_EXISTS == ::GetLastError())
		{
			return false;
		}
	}

	return true;
}

//--------------------------------------------------------------



