//--------------------------------------------------------------
//	Communicator.cpp.
//	05/23/2013.		by bubo.
//	06/07/2014.		Modified.
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "Commander.h"
#include "Communicator.h"
#include <fstream>
#include <iostream>
#include <Shlwapi.h>
#include <thread>
#include <queue>
#include <strsafe.h>
#include <cstring>
#include "ProgressDialog.h"
#include "Messages.h"

//--------------------------------------------------------------
//	Themes...
//--------------------------------------------------------------
#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

//--------------------------------------------------------------
using namespace cinderella;

//--------------------------------------------------------------
//	Initialize static variables...
//--------------------------------------------------------------
map<wstring, Communicator::UserData*> Communicator::ms_UsersContainer;
Commander* Communicator::ms_pCommander = nullptr;
const unsigned int Communicator::ms_uiSOCKETBUFSIZE = 1024 * 64;	// 64 kilobytes.
const unsigned int Communicator::ms_uiFILEBUFFERSIZE = 1024 * 1024;	// 1 Megabyte.

//--------------------------------------------------------------
//	Extern variables...
//--------------------------------------------------------------
extern const unsigned short UDP_TEXT_PORT;

//--------------------------------------------------------------
bool Communicator::Initialize (int iPort)
{
	m_iPort = iPort;

	//--------------------------------------------------------------
	//	initialize winsock2 library... 
	//--------------------------------------------------------------
	WSADATA wsaData;

	if (::WSAStartup (MAKEWORD (2, 2), &wsaData) != 0) 
	{
		return false;
	}

	//--------------------------------------------------------------
	//	Create sockets...
	//--------------------------------------------------------------
	m_sSocketTCP = ::socket(PF_INET6, SOCK_STREAM, 0);
	m_sSocketUDP = ::socket(PF_INET6, SOCK_DGRAM, 0);
	m_sSocketUDPText = ::socket(PF_INET6, SOCK_DGRAM, 0);

	if (m_sSocketTCP == INVALID_SOCKET || m_sSocketUDP == INVALID_SOCKET ||
		m_sSocketUDPText == INVALID_SOCKET)
	{
		return false;
	}


	//--------------------------------------------------------------
	// Bind sockets to local IP and Port...
	//--------------------------------------------------------------
	sockaddr_in6 addrLocal = { 0 };
	addrLocal.sin6_addr = in6addr_any;
	//	Testing code...
	//InetPtonW(AF_INET6, L"fec0::34/64", &addrLocal.sin6_addr);  // IPv6
	addrLocal.sin6_family = AF_INET6;
	addrLocal.sin6_port = ::htons (iPort);
	

	/* bind local address... */
	if (
		(SOCKET_ERROR == ::bind(m_sSocketTCP,
		reinterpret_cast<SOCKADDR*>(&addrLocal), sizeof sockaddr_in6)) ||
		(SOCKET_ERROR == ::bind(m_sSocketUDP,
		reinterpret_cast<SOCKADDR*>(&addrLocal), sizeof sockaddr_in6)))
	{
		return false;
	}

	// UDP_Text port number.
	addrLocal.sin6_port = ::htons(UDP_TEXT_PORT);

	/* bind local address for UDP_Text */
	if (SOCKET_ERROR == ::bind(m_sSocketUDPText,
		reinterpret_cast<SOCKADDR*>(&addrLocal), sizeof sockaddr_in6))
	{
		return false;
	}

	//--------------------------------------------------------------
	// Set Multi casting...
	//--------------------------------------------------------------
	ipv6_mreq mcast;

	::memset(reinterpret_cast<void*>(&mcast), 0, sizeof mcast);
	mcast.ipv6mr_multiaddr = m_kIPMask;
	//::InetPtonW(AF_INET6, L"FF16::f", &mcast.ipv6mr_multiaddr);  // IPv6

	int iResult = ::setsockopt(m_sSocketUDP, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP,
		reinterpret_cast<char*>(&mcast), sizeof mcast);

	if (iResult == SOCKET_ERROR)
	{
		return false;
	}

	//--------------------------------------------------------------
	// Listen for TCP...
	//--------------------------------------------------------------
	if (::listen (m_sSocketTCP, SOMAXCONN) == SOCKET_ERROR)
	{
		return false;
	}

	//--------------------------------------------------------------
	// Pass the m_sSocketTCP as parameter to the TCP thread...
	//--------------------------------------------------------------
	m_hThreadTCP = ::CreateThread (nullptr, 0, fnThreadTCPAccept, 
		reinterpret_cast<LPVOID>(m_sSocketTCP), 0, nullptr);

	//--------------------------------------------------------------
	// Pass the m_sSocketUDP as parameter to the UDP thread...
	//--------------------------------------------------------------
	m_hThreadUDP = ::CreateThread (nullptr, 0, fnThreadUDPReceive, 
		reinterpret_cast<LPVOID>(m_sSocketUDP), 0, nullptr);

	//--------------------------------------------------------------
	// Pass the m_sSocketUDPText as parameter to the UDPText thread...
	//--------------------------------------------------------------
	m_hThreadUDPText = ::CreateThread(nullptr, 0, fnThreadUDPTextReceive,
		reinterpret_cast<LPVOID>(m_sSocketUDPText), 0, nullptr);

	//--------------------------------------------------------------
	// Create threads failed...
	//--------------------------------------------------------------
	if ( (m_hThreadTCP == nullptr) || (m_hThreadUDP == nullptr) ||
		(m_hThreadUDPText == nullptr))
	{
		return false;
	}

	//--------------------------------------------------------------

	return true;
}

//--------------------------------------------------------------
unsigned long WINAPI Communicator::fnThreadTCPAccept (LPVOID lpParameter)
{
	// Cast the socket.
	SOCKET hThreadTCP = reinterpret_cast<SOCKET>(lpParameter);
	
	sockaddr_in6 addrClient;
	int len = sizeof sockaddr_in6;

	while (true)
	{
		SOCKET sockClient = ::accept (hThreadTCP, 
			reinterpret_cast<LPSOCKADDR>(&addrClient), &len);

		if (sockClient == INVALID_SOCKET)
		{
			continue;
		}

		// Convert the IPv6 address to wstring.
		wchar_t szAddrIPv6[50] = { 0 };
		::InetNtopW(AF_INET6, &addrClient.sin6_addr, szAddrIPv6, 50);

		IP_SOCKET* ip_socket = new IP_SOCKET;
		ip_socket->m_Socket = sockClient;
		ip_socket->m_szIP = szAddrIPv6;

		HANDLE hReceiveThreadTCP = ::CreateThread (nullptr, 0, fnThreadTCPReceive, 
			reinterpret_cast<LPVOID>(ip_socket), 0, nullptr);

		::CloseHandle (hReceiveThreadTCP);
	}
	

	return 0;
}



//--------------------------------------------------------------
unsigned long WINAPI Communicator::fnThreadUDPReceive (LPVOID lpParameter)
{
	// Receive from remote client and process it.
	SOCKET hThreadUDP = reinterpret_cast<SOCKET>(lpParameter);

	sockaddr_in6 addrClient;
	int len = sizeof sockaddr_in6;

	char buffer[sizeof UserData] = { 0 };
	int iRecieveSize = 0;

	while (true)
	{
		// Set the total size to 0.
		iRecieveSize = 0;
		::memset(buffer, 0, sizeof buffer);

		// Receive the UDP data recursively.
	RecvUDPData:
		iRecieveSize += ::recvfrom (hThreadUDP, buffer + iRecieveSize, (sizeof buffer) - iRecieveSize, 0, 
			reinterpret_cast<LPSOCKADDR>(&addrClient), &len);

		// Error occurs.
		if (iRecieveSize < 0)
		{
			break;
		}
		//	Not enough for the entire 'UserData' structure.
		else if (iRecieveSize < sizeof (UserData))
		{
			goto RecvUDPData;
		}
		
		if (!ms_pCommander)
		{
			break;
		}
		
		reinterpret_cast<UserData*>(buffer)->ClientAddr = addrClient;

		switch (reinterpret_cast<UserData*>(buffer)->GetUserType ())
		{
		case TR_REGISTER:
			AddUser(reinterpret_cast<UserData*>(buffer));
			ms_pCommander->RefreshData ();
			break;

		case TR_UNREGISTER:
			DeleteUser(reinterpret_cast<UserData*>(buffer));
			ms_pCommander->RefreshData ();
			break;

		case TR_QUERY:
			SendInfoToUser(ms_pCommander->GetCommunicator(),
				reinterpret_cast<UserData*>(buffer));
			break;

			// Move to the 'fnThreadUDPTextReceive' method...
			/*case TR_MSG:
				ms_pCommander->GetUIManager ()->ShowUserDialog(
				reinterpret_cast<UserData*>(buffer));
				break;*/

		default:
			break;
		}
	}

	return 0;
}

//--------------------------------------------------------------
unsigned long WINAPI Communicator::fnThreadUDPTextReceive(LPVOID lpParameter)
{
	// Receive from remote client and process it.
	SOCKET hThreadUDP = reinterpret_cast<SOCKET>(lpParameter);

	sockaddr_in6 addrClient;
	int len = sizeof sockaddr_in6;

	char buffer[sizeof UserDataText];
	int iReceiveSize = 0;
	int iCurrentReceived = 0;

	while (true)
	{
		// Set the total size to 0.
		iReceiveSize = 0;
		iCurrentReceived = 0;

		// Receive the UDP data recursively.
	RecvUDPData:
		iCurrentReceived = ::recvfrom(hThreadUDP, buffer + iReceiveSize,
			sizeof buffer - iReceiveSize, 0,
			reinterpret_cast<LPSOCKADDR>(&addrClient), &len);

		// Accumulate the received data to 'iReceiveSize' variable.
		iReceiveSize += iCurrentReceived;

		// Error occurs.
		if (iCurrentReceived < 0)
		{
			continue;
		}
		//	Not enough for the entire 'UserData' structure.
		else if (iReceiveSize < sizeof (UserDataText))
		{
			goto RecvUDPData;
		}


		reinterpret_cast<UserDataText*>(buffer)->ClientAddr = addrClient;

		// Check if the user in our container.
		wchar_t szAddrIPv6[50] = { 0 };
		// Convert the IPv6 address to wstring.
		::InetNtopW(AF_INET6, &addrClient, szAddrIPv6, 50);
		auto it = ms_UsersContainer.find(szAddrIPv6);

		if (it == ms_UsersContainer.end())
		{
			// Add the current user into user container first.
			AddUser(reinterpret_cast<UserData*>(buffer));
			ms_pCommander->RefreshData();
		}

		ms_pCommander->GetUIManager()->ShowUserDialog(
			reinterpret_cast<UserDataText*>(buffer));

	}

	return 0;
}

//--------------------------------------------------------------
void Communicator::AddUser (UserData* pUserData)
{
	wchar_t szAddrIPv6[50] = { 0 };
	
	// Convert the IPv6 address to wstring.
	::InetNtopW(AF_INET6, &((pUserData->ClientAddr).sin6_addr), szAddrIPv6, 50);

	auto it = ms_UsersContainer.find (
		wstring(szAddrIPv6));
	
	if (it == ms_UsersContainer.end ())
	{		
		auto pCurrentUserDate = new UserData();
		
		pCurrentUserDate->SetUserNameW(pUserData->GetUserNameW ());
		pCurrentUserDate->ClientAddr = pUserData->ClientAddr;
		
		ms_UsersContainer[wstring(szAddrIPv6)] = pCurrentUserDate;
	}
	else
	{
		ms_UsersContainer[wstring(szAddrIPv6)]->SetUserNameW(
			pUserData->GetUserNameW ());
	}
}


//--------------------------------------------------------------
void Communicator::DeleteUser (UserData* pUserData)
{
	wchar_t szAddrIPv6[50] = { 0 };

	// Convert the IPv6 address to wstring.
	::InetNtopW(AF_INET6, &((pUserData->ClientAddr).sin6_addr), szAddrIPv6, 50);

	auto it = ms_UsersContainer.find(
		wstring(szAddrIPv6));

	if (it != ms_UsersContainer.end())
	{
		delete (*it).second;
		ms_UsersContainer.erase(it);
	}
}


//--------------------------------------------------------------
void Communicator::SetCommander (Commander* pCommander)
{
	ms_pCommander = pCommander;
}

//--------------------------------------------------------------
const map<wstring, Communicator::UserData*>&
	Communicator::GetUserContainer () const
{
		return ms_UsersContainer; 
}

//--------------------------------------------------------------
Communicator::Communicator () : m_iPort(0)/*, m_ulIPMask (0ul)*/
{
	// None, so far.
}

//--------------------------------------------------------------
void Communicator::BroadcastInfo (bool bRegister /* = true*/)
{
	// Define the target address...
	sockaddr_in6 addrRecv = { 0 };

	addrRecv.sin6_family = AF_INET6;
	addrRecv.sin6_port = ::htons (m_iPort);
	addrRecv.sin6_addr = m_kIPMask;
	//::InetPtonW(AF_INET6, L"FF16::f", &addrRecv.sin6_addr);  // IPv6

	UserData userData;

	if (bRegister == true)
	{
		userData.SetUserType (TR_REGISTER);
	}
	else
	{
		userData.SetUserType (TR_UNREGISTER);
	}

	userData.SetUserNameW (m_szName);
	
	SendDataUDP (&userData, &addrRecv);	
}

//--------------------------------------------------------------
void Communicator::BroadcastQueryInfo ()
{
	// Define the target address...
	sockaddr_in6 addrRecv = { 0 };

	addrRecv.sin6_family = AF_INET6;
	addrRecv.sin6_port = ::htons(m_iPort);
	addrRecv.sin6_addr = m_kIPMask;
	//::InetPtonW(AF_INET6, L"FF16::f", &RecvAddr.sin6_addr);  // IPv6

	UserData userData;

	userData.SetUserType(TR_QUERY);

	userData.SetUserNameW (m_szName);

	SendDataUDP(&userData, &addrRecv);
	
}

//--------------------------------------------------------------
void Communicator::SendInfoToUser(Communicator* pCommunictor,
	UserData* pUserData)
{
	pUserData->SetUserType(TR_REGISTER);
	pUserData->SetUserNameW(pCommunictor->m_szName);

	pCommunictor->SendDataUDP(pUserData, &(pUserData->ClientAddr));

}

//--------------------------------------------------------------
bool Communicator::SendDataUDP(UserData* pUserData, sockaddr_in6* pRecvAddr)
{
	int iResult = 0;
	
	iResult = ::sendto (m_sSocketUDP, reinterpret_cast<const char*>(pUserData), 
		sizeof UserData, 0, reinterpret_cast<LPSOCKADDR>(pRecvAddr), 
		sizeof sockaddr_in6);

	if (iResult == SOCKET_ERROR)
	{
		// Testing code.
		int i = GetLastError();
		return false;
	}

	return true;
}

//--------------------------------------------------------------
bool Communicator::SendDataUDPText(UserDataText* pUserData, 
	sockaddr_in6* pRecvAddr)
{
	int iResult = 0;

	iResult = ::sendto(m_sSocketUDPText, reinterpret_cast<const char*>(pUserData),
		sizeof UserDataText, 0, reinterpret_cast<LPSOCKADDR>(pRecvAddr),
		sizeof sockaddr_in6);

	if (iResult == SOCKET_ERROR)
	{
		return false;
	}

	return true;
}

//--------------------------------------------------------------
void Communicator::SetLocalNameW (wchar_t* pszName)
{
	::wcscpy (m_szName, pszName);
}

//--------------------------------------------------------------
bool Communicator::TransferDataTCP(wchar_t* pszName, sockaddr_in6* pRecvAddr,
									FileHeader::FILETYPE eFileType)
{
	//--------------------------------------------------------------
	//	Used for C++ 11 or later only!
	//--------------------------------------------------------------
	std::thread tTcp([&](wchar_t* pszName, sockaddr_in6* pRecvAddr,
		FileHeader::FILETYPE eFileType)
	{
		wchar_t szFileName[MAX_PATH];
		::wcscpy (szFileName, pszName);

		SOCKET sockToClient = ::socket ( PF_INET6, SOCK_STREAM, 0);


		if (::connect(sockToClient, (SOCKADDR*)pRecvAddr, sizeof sockaddr_in6)
			== SOCKET_ERROR )
		{
			// error: 10061 : No connection could be made because the target 
			// machine actively refused it. 
			int i = GetLastError ();
			::closesocket (sockToClient);
			return false;
		}
		else
		{
			FileHeader::FILECONFIRM eFileConfirm = FileHeader::FC_DIRECTORY;

			if (eFileType == FileHeader::FT_DIRECTORY)
			{
				eFileConfirm = FileHeader::FC_DIRECTORY;


			}
			else if (eFileType == FileHeader::FT_REGULAR)
			{

				eFileConfirm = FileHeader::FC_REGULAR;

			}

			int iResult = 0;
			iResult = ::send (sockToClient, reinterpret_cast<const char*>(&eFileConfirm), 
				sizeof eFileConfirm, 0);
			if (iResult <= 0)
			{
				::closesocket (sockToClient);	
				return false;
			}

			if (eFileType == FileHeader::FT_DIRECTORY)
			{
				wchar_t szOnlyFileName[MAX_PATH];
				::wcscpy(szOnlyFileName, szFileName);
				// Removes the path portion of a fully qualified path and file.
				::PathStripPath(szOnlyFileName);

				// Send to Client...
				FileHeader fileHeader;
				fileHeader.SetContinueState(true);
				fileHeader.SetFileType(FileHeader::FT_DIRECTORY);
				fileHeader.SetFileName(szOnlyFileName);

				// Send Directory information to Client...
				int iResult = 0;
				iResult = ::send(sockToClient, reinterpret_cast<const char*>(&fileHeader),
					sizeof FileHeader, 0);

				if (iResult < 0)
				{
					return false;
				}

				iResult = ::recv (sockToClient, reinterpret_cast<char*>(&eFileConfirm),
					sizeof eFileConfirm, 0);

				if (iResult <= 0)
				{
					::closesocket (sockToClient);	
					return false;
				}
				else if (eFileConfirm == FileHeader::FC_CANCLE)
				{
					::closesocket (sockToClient);
					return true;
				}
			}


			ProcessSendFile(sockToClient, szFileName, eFileType);

			::closesocket (sockToClient);		
		}

		return true;

	}, pszName, pRecvAddr, eFileType);

	::Sleep (10);

	tTcp.detach();

	return true;
}

//--------------------------------------------------------------
bool Communicator::ProcessSendFile_Directory(SOCKET sockConn, 
								   wchar_t* szFileName)
{
	std::queue<wchar_t*> DirectoryQueue;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;
	
	wchar_t szCurrentDir[MAX_PATH];
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0ul;
	const unsigned long ulBUFFERSIZE = ms_uiSOCKETBUFSIZE;
	char buffer[ulBUFFERSIZE];


	// Prepare string for use with FindFile functions.  First, copy the
	// string to a buffer, then append '\*' to the directory name.

	wchar_t szOnlyFileName[MAX_PATH];
	::wcscpy (szOnlyFileName, szFileName);
	// Removes the path portion of a fully qualified path and file.
	::PathStripPath (szOnlyFileName);

	// Send to Client...
	FileHeader fileHeader;
	fileHeader.SetContinueState(true);
	fileHeader.SetFileType(FileHeader::FT_DIRECTORY);
	fileHeader.SetFileName(szOnlyFileName);

	// Send Directory information to Client...
	int iResult = 0;
	iResult = ::send (sockConn, reinterpret_cast<const char*>(&fileHeader), 
		sizeof FileHeader, 0);

	if (iResult < 0)
	{
		return false;
	}

	

	// Push back the first current directory...
	wchar_t* pTempDir = new wchar_t[MAX_PATH];
	::wcscpy(pTempDir, szFileName);
	DirectoryQueue.push(pTempDir);
	wchar_t szDirName[MAX_PATH];
	::wcscpy(szDirName, szFileName);
	::wcsrchr(szDirName, '\\')[0] = 0;
	
	//unsigned int uiProcessTimes = 0u;

	//--------------------------------------------------------------
	// BFS files...
	//--------------------------------------------------------------
	while (DirectoryQueue.size() > 0)
	{
		//uiProcessTimes++;

		// Pop up the first directory in the queue...
		::wcscpy(szCurrentDir, DirectoryQueue.front());

		delete[] DirectoryQueue.front();
		DirectoryQueue.pop();

		wchar_t szCurrentDirFind[MAX_PATH];
		::wcscpy(szCurrentDirFind, szCurrentDir);
		::StringCchCat(szCurrentDirFind, MAX_PATH,  L"\\*");

		// Find the first file in this directory.
		hFind = ::FindFirstFile(szCurrentDirFind, &ffd);

		if (INVALID_HANDLE_VALUE == hFind) 
		{
			while (DirectoryQueue.size() > 0)
			{
				delete[] DirectoryQueue.front();
				DirectoryQueue.pop();
			}

			return false;
		} 

		//--------------------------------------------------------------
		// List all the files in the directory with some info about them.
		//--------------------------------------------------------------
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // if[1]
			{
				// Skip current '.' and parent '..' directory level.
				if ( ::wcscmp(ffd.cFileName, L".") == 0 || 
					::wcscmp(ffd.cFileName, L"..") == 0)
				{
					continue;
				}
				else
				{
					wchar_t* pszDirName = new wchar_t[MAX_PATH];
					::swprintf(pszDirName, L"%s\\%s", szCurrentDir, ffd.cFileName);
					DirectoryQueue.push(pszDirName);

					// Send to Client...
					FileHeader fileHeader;
					fileHeader.SetContinueState(true);
					fileHeader.SetFileType(FileHeader::FT_DIRECTORY);
					// Including '//' to the directory name.
					fileHeader.SetFileName(pszDirName + wcslen(szDirName));

					// Send Directory information to Client...
					int iResult = 0;
					iResult = ::send (sockConn, reinterpret_cast<const char*>(&fileHeader), 
						sizeof FileHeader, 0);

					// Testing code...
					if (!fileHeader.GetContinueState())
					{
						while (DirectoryQueue.size() > 0)
						{
							delete[] DirectoryQueue.front();
							DirectoryQueue.pop();
						}

						goto Endfile;
					}


					if (iResult < 0)
					{
						while (DirectoryQueue.size() > 0)
						{
							delete[] DirectoryQueue.front();
							DirectoryQueue.pop();
						}

						goto Endfile;
					}


				}


			}
			// File type is regular file...
			else
			{
				// Get long long file size...
				filesize.LowPart = ffd.nFileSizeLow;
				filesize.HighPart = ffd.nFileSizeHigh;

				// Current file name with full path...
				wchar_t szCurrentFile[MAX_PATH];
				::swprintf(szCurrentFile, L"%s\\%s", szCurrentDir, ffd.cFileName);

				// Fill out the FileHeader class...
				FileHeader fileHeader;
				fileHeader.SetContinueState(true);
				fileHeader.SetFileType(FileHeader::FT_REGULAR);
				fileHeader.SetFileName(szCurrentFile + wcslen(szDirName));
				// FileHeader.SetFileSize(filesize.QuadPart);

				// Send File information to Client...

				// Open file...
				std::fstream fs;
				fs.open(szCurrentFile, std::fstream::in | std::fstream::binary, _SH_DENYNO);
				if ( fs.fail() )
				{
					while (DirectoryQueue.size() > 0)
					{
						delete[] DirectoryQueue.front();
						DirectoryQueue.pop();
					}

					goto Endfile;
				}

				// Get file size using C++...
				fs.seekg( 0, ios::end );
				fileHeader.SetFileSize(fs.tellg());
				fs.seekg(0, ios::beg );

				int iResult = 0;
				iResult = ::send (sockConn, reinterpret_cast<const char*>(&fileHeader), 
					sizeof FileHeader, 0);

				if (iResult < 0)
				{
					fs.close();
					while (DirectoryQueue.size() > 0)
					{
						delete[] DirectoryQueue.front();
						DirectoryQueue.pop();
					}


					goto Endfile;
				}

				
				//--------------------------------------------------------------
				//	Send File to client...
				//--------------------------------------------------------------
				while (true)
				{
					fs.read(buffer, ulBUFFERSIZE);

					if ((iResult = ::send(sockConn, reinterpret_cast<const char*>(buffer),
						fs.gcount(), 0)) == SOCKET_ERROR)
					{
						int i = GetLastError();
						while (DirectoryQueue.size() > 0)
						{
							delete[] DirectoryQueue.front();
							DirectoryQueue.pop();
						}

						fs.close();

						goto Endfile;
					}


					if (fs.eof())
					{
						fs.close();
						break;
					}

				}	// End of While.			

			} // End of if[1].

		}
		while (::FindNextFile(hFind, &ffd) != 0);	//end of do-while.


		// Check if any errors occurs...
		dwError = GetLastError();

		if (dwError != ERROR_NO_MORE_FILES) 
		{
			while (DirectoryQueue.size() > 0)
			{
				delete[] DirectoryQueue.front();
				DirectoryQueue.pop();
			}
			
			goto Endfile;
		}


	}	// End of while.


	//--------------------------------------------------------------
	//	End and error handing...
	//--------------------------------------------------------------
Endfile:
	// Fill out the FileHeader class...
	fileHeader.SetContinueState(false);

	// Send File information to Client...
	iResult = 0;
	iResult = ::send (sockConn, reinterpret_cast<const char*>(&fileHeader), 
		sizeof FileHeader, 0);

	if (iResult < 0)
	{
		::FindClose(hFind);
		return false;
	}

	::FindClose(hFind);

	return true;
}

//--------------------------------------------------------------
bool Communicator::ProcessSendFile_Files(SOCKET sockConn, 
											 wchar_t* szFileName)
{
	// Variables...
	const unsigned long ulBUFFERSIZE = ms_uiSOCKETBUFSIZE;
	char buffer[ulBUFFERSIZE];
	int iResult = 0;


	// Open file...
	std::fstream fs;
	fs.open(szFileName, std::fstream::in | std::fstream::binary);

	if ( fs.fail() )
	{
		return false;
	}


	wchar_t szOnlyFileName[MAX_PATH];
	::wcscpy (szOnlyFileName, szFileName);

	// Removes the path portion of a fully qualified path and file.
	::PathStripPath (szOnlyFileName);

	// Fill out the FileHeader class...
	FileHeader fileHeader;
	fileHeader.SetContinueState(true);
	fileHeader.SetFileType(FileHeader::FT_REGULAR);
	fileHeader.SetFileName(szOnlyFileName);

	// Get file size using C++...
	fs.seekg( 0, ios::end );
	fileHeader.SetFileSize(fs.tellg());
	fs.seekg(0, ios::beg );

	// Send information of file to client...
	iResult = ::send (sockConn, reinterpret_cast<const char*>(&fileHeader), 
		sizeof FileHeader, 0);

	if (iResult <= 0)
	{
		fs.close();
		return false;
	}

	FileHeader::FILECONFIRM eFileConfirm;

	iResult = ::recv (sockConn, reinterpret_cast<char*>(&eFileConfirm), 
		sizeof eFileConfirm, 0);

	if (iResult <= 0)
	{
		fs.close();
		/*::closesocket (sockConn);	*/
		return false;
	}
	else if (eFileConfirm == FileHeader::FC_CANCLE)
	{
		fs.close();
		/*::closesocket (sockConn);*/
		return true;
	}

	//--------------------------------------------------------------
	//	Send File to client...
	//--------------------------------------------------------------
	while (true)
	{
		fs.read(buffer, ulBUFFERSIZE);

		if ((iResult = ::send(sockConn, reinterpret_cast<const char*>(buffer),
			fs.gcount(), 0)) == SOCKET_ERROR)
		{

			fs.close();
			/*::closesocket(sockConn);*/
			return false;
		}


		if (fs.eof())
			break;
			
	}				

	fs.close();

	return true;
}

//--------------------------------------------------------------
bool Communicator::ProcessSendFile(SOCKET sockConn, 
								   wchar_t* szFileName,
								   FileHeader::FILETYPE eFileType)
{
	if (eFileType == FileHeader::FT_DIRECTORY)
	{
		return ProcessSendFile_Directory(sockConn, szFileName);
	}
	/*else if (eFileConf == FileHeader::FC_REGULARMULTI)
	{
	return ProcessSendFile_Files(sockConn, szFileName, true);
	}*/
	else if (eFileType == FileHeader::FT_REGULAR)
	{
		return ProcessSendFile_Files(sockConn, szFileName);
	}

	return false;
	
}

//-------------------------------------------------------------
bool Communicator::ProcessRecvFile(SOCKET sockConn, 
								   wchar_t* szFileName,
								   HANDLE hEvent)
{
	//-------------------------------------------------------------
	//	Variable declarations...
	//-------------------------------------------------------------
	int cbBytes = 0;
	const unsigned long ulBUFFERSIZE = ms_uiSOCKETBUFSIZE / 8;
	char buffer[ulBUFFERSIZE];	
	long long llTotle = 0ll;
	unsigned long ulRecvingSize = 0ul;

	char* pFileBuffer = new char[ms_uiFILEBUFFERSIZE];
	int iFileBufferPos = 0;
	int iCurrentCapacity = ms_uiFILEBUFFERSIZE;

	//-------------------------------------------------------------
	ProgressDialog* pkProgressDlg = reinterpret_cast<ProgressDialog*>(SendMessage(
		ms_pCommander->GetUIManager()->GetMainWindow(), 
		WM_SHOWDIALOGPROGRESS, NULL, NULL));

	while (true)
	{
		llTotle = 0ll;
		ulRecvingSize = sizeof FileHeader;
		char tempBuffer[sizeof FileHeader];

		::memset(buffer, 0, ulBUFFERSIZE);

		// Make sure that we can receive the entire FileHeader information...
		while (true)
		{
			cbBytes = ::recv (sockConn, tempBuffer, ulRecvingSize, 0);

			if (cbBytes < 0)
			{
				if (pFileBuffer)
				{
					delete[] pFileBuffer;
					pFileBuffer = nullptr;
				}

				TransferIndicator::GetSingleton()->SetFailed(hEvent);
				return false;
			}

			llTotle += cbBytes;

			if (llTotle == sizeof FileHeader)
			{
				::memcpy(buffer + llTotle - cbBytes, tempBuffer, cbBytes);
				break;
			}
			else
			{
				ulRecvingSize = sizeof FileHeader - llTotle;
				::memcpy(buffer + llTotle - cbBytes, tempBuffer, cbBytes);
			}

		}

		FileHeader kFileHeader = *(reinterpret_cast<FileHeader*>(buffer));

		if (kFileHeader.GetContinueState() == false)
		{
			break;
		}

		// Process files...
		if (kFileHeader.GetFileType() == FileHeader::FT_DIRECTORY)
		{
			wchar_t szCurrentDir[MAX_PATH];
			::swprintf(szCurrentDir, L"%s\\%s", szFileName, 
				kFileHeader.GetFileName());

			// Create a sub directory.
			if (::CreateDirectory(szCurrentDir, nullptr) == 0)
			{
				if (ERROR_ALREADY_EXISTS != GetLastError())
				{
					pkProgressDlg->SetText(L"Transfer Failed!");
					pkProgressDlg->SetFinish(true);

					if (pFileBuffer)
					{
						delete[] pFileBuffer;
						pFileBuffer = nullptr;
					}

					TransferIndicator::GetSingleton()->SetFailed(hEvent);
					return false;
				}
				
			}

		}
		else if (kFileHeader.GetFileType() == FileHeader::FT_REGULAR)
		{
			wchar_t szCurrentFile[MAX_PATH];
			::swprintf(szCurrentFile, L"%s\\%s", szFileName, 
				kFileHeader.GetFileName());

			// Create a new file in current directory...
			std::fstream fs;
			fs.open (szCurrentFile, std::fstream::out | 
				std::fstream::binary | std::fstream::trunc);	

			// For showing information in a ProgressDialog...
			wchar_t szOnlyFileName[MAX_PATH];
			::wcscpy (szOnlyFileName, kFileHeader.GetFileName());
			// Removes the path portion of a fully qualified path and file.
			::PathStripPath (szOnlyFileName);

			pkProgressDlg->SetText(szOnlyFileName);
			pkProgressDlg->SetRange(0, kFileHeader.GetFileSize());

			if ( fs.fail() )
			{
				pkProgressDlg->SetText(L"Transfer Failed!");
				pkProgressDlg->SetFinish(true);

				if (pFileBuffer)
				{
					delete[] pFileBuffer;
					pFileBuffer = nullptr;
				}

				TransferIndicator::GetSingleton()->SetFailed(hEvent);
				return false;
			}

			if (ms_uiFILEBUFFERSIZE > kFileHeader.GetFileSize())
			{
				iCurrentCapacity = kFileHeader.GetFileSize();
			}
			else
			{
				iCurrentCapacity = ms_uiFILEBUFFERSIZE;
			}

			llTotle = 0ll;

			//--------------------------------------------------------------
			//	Read data from server then write to file...
			//--------------------------------------------------------------
			while ((cbBytes = ::recv(sockConn, pFileBuffer + iFileBufferPos, 
				iCurrentCapacity, 0)) > 0)
			{
				llTotle += cbBytes;
				iFileBufferPos += cbBytes;
				iCurrentCapacity -= cbBytes;

				pkProgressDlg->SetCurrentValue(llTotle);
				pkProgressDlg->Update();

				if (pkProgressDlg->IsCanceled())
				{
					fs.close();
					pkProgressDlg->Exit();

					if (pFileBuffer)
					{
						delete[] pFileBuffer;
						pFileBuffer = nullptr;
					}

					TransferIndicator::GetSingleton()->SetFailed(hEvent);
					return true;
				}

				//Write the received partial file data to the hard disk...
				if (iCurrentCapacity <= 0 || llTotle >= kFileHeader.GetFileSize())
				{
					fs.write(pFileBuffer, iFileBufferPos);

					if (fs.bad())
					{
						fs.close();

						if (pFileBuffer)
						{
							delete[] pFileBuffer;
							pFileBuffer = nullptr;
						}

						TransferIndicator::GetSingleton()->SetFailed(hEvent);
						return false;
					}

					// Reset values.
					iFileBufferPos = 0;
					
					if ((kFileHeader.GetFileSize() - llTotle) < ms_uiFILEBUFFERSIZE)
					{
						iCurrentCapacity = kFileHeader.GetFileSize() - llTotle;
					}
					else
					{
						iCurrentCapacity = ms_uiFILEBUFFERSIZE;
					}

				}

				// Check if the file is end...
				if (llTotle >= kFileHeader.GetFileSize())
				{
					//fs.close();
					break;
				}


			}

			fs.close();

			// If receive failed.
			if (cbBytes < 0)
			{
				pkProgressDlg->SetText(L"Transfer Failed!");
				pkProgressDlg->SetFinish(true);

				if (pFileBuffer)
				{
					delete[] pFileBuffer;
					pFileBuffer = nullptr;
				}
	
				TransferIndicator::GetSingleton()->SetFailed(hEvent);
				return true;
			}

		} // End of if.


	} // End of While.

	pkProgressDlg->SetFinish(true);


	if (pFileBuffer)
	{
		delete[] pFileBuffer;
		pFileBuffer = nullptr;
	}

	TransferIndicator::GetSingleton()->SetFinish(hEvent);

	return true;
}

//--------------------------------------------------------------
unsigned long WINAPI Communicator::fnThreadTCPReceive (LPVOID lpParameter)
{
	IP_SOCKET* ip_socket = reinterpret_cast<IP_SOCKET*>(lpParameter);

	SOCKET sockConn = ip_socket->m_Socket;
	wstring szIP = ip_socket->m_szIP;
	delete ip_socket;
	ip_socket = nullptr;

	HANDLE hEvent = nullptr;

	FileHeader::FILECONFIRM eFileConfirm = FileHeader::FC_DIRECTORY;
	int cbBytes = 0;
	unsigned long ulBtyesRead = 0;
	wchar_t pszName[MAX_PATH];
	::memset(pszName, 0, MAX_PATH * sizeof (wchar_t));

	if ((cbBytes = ::recv(sockConn, reinterpret_cast<char*>(&eFileConfirm),
		sizeof eFileConfirm, 0)) > 0)
	{

		// Retrieve the filename to get a full path...
		if (eFileConfirm == FileHeader::FC_DIRECTORY)
		{
			FileHeader kFileHeader;
			if (::recv(sockConn, reinterpret_cast<char*>(&kFileHeader),
				sizeof kFileHeader, 0) > 0)
			{
				::wcscpy(pszName, kFileHeader.GetFileName());

				if (ms_pCommander->GetUIManager()->OnDirArrived(pszName, szIP, &hEvent))
				{
					eFileConfirm = FileHeader::FC_OK;
					if (::send(sockConn, reinterpret_cast<const char*>(&eFileConfirm),
						sizeof eFileConfirm, 0) > 0)
					{
						ProcessRecvFile(sockConn, pszName, hEvent);
					}
					else
					{
						TransferIndicator::GetSingleton()->SetFailed(hEvent);
					}
						
				}
				else
				{
					eFileConfirm = FileHeader::FC_CANCLE;
					::send(sockConn, reinterpret_cast<const char*>(&eFileConfirm),
						sizeof eFileConfirm, 0);

					TransferIndicator::GetSingleton()->SetFailed(hEvent);
				}
			}
		
		}
		else
		{
			FileHeader kFileHeader;
			eFileConfirm = FileHeader::FC_OK;

			if (::recv(sockConn, reinterpret_cast<char*>(&kFileHeader), 
				sizeof kFileHeader, 0) > 0)
			{
				::wcscpy(pszName, kFileHeader.GetFileName());
				if (ms_pCommander->GetUIManager()->OnFileArrived(pszName, szIP, &hEvent))
				{
					if (::send(sockConn, reinterpret_cast<const char*>(&eFileConfirm), 
						sizeof eFileConfirm, 0) > 0)
					{
						// testing code...
						//ProcessRecvFile(sockConn, pszName);
						RecvingSingleFile(sockConn, pszName, kFileHeader.GetFileSize(), hEvent);
					}
					else
					{
						TransferIndicator::GetSingleton()->SetFailed(hEvent);
						TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->TestCurWorkingEvent(hEvent);
						//TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->RemoveFile(hEvent);			
					}
				}
				else
				{
					eFileConfirm = FileHeader::FC_CANCLE;
					::send(sockConn, reinterpret_cast<const char*>(&eFileConfirm), 
						sizeof eFileConfirm, 0);
					TransferIndicator::GetSingleton()->SetFailed(hEvent);
					TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->StopAndClearPipeline();
				}
			}


		}

	}

	::closesocket(sockConn);

	return 0;
}


//--------------------------------------------------------------
bool Communicator::RecvingSingleFile(SOCKET sockConn, wchar_t* pszName,
									 long long llFileSize, HANDLE hEvent)
{
	//-------------------------------------------------------------
	//	Variable declarations...
	//-------------------------------------------------------------
	int cbBytes = 0;
	long long llTotle = 0ll;
	unsigned long ulRecvingSize = 0ul;
	char* pFileBuffer = new char[ms_uiFILEBUFFERSIZE];
	int iFileBufferPos = 0;
	int iCurrentCapacity = ms_uiFILEBUFFERSIZE;

	//-------------------------------------------------------------
	ProgressDialog* pkProgressDlg = nullptr;

	if (TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->HasFile(hEvent))
	{
		if ((pkProgressDlg = reinterpret_cast<ProgressDialog*>(
			TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->GetProgressDlgPtr())) == nullptr)
		{
			pkProgressDlg = reinterpret_cast<ProgressDialog*>(SendMessage(
				ms_pCommander->GetUIManager()->GetMainWindow(),
				WM_SHOWDIALOGPROGRESS, NULL, NULL));

			TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->SetProgressDlgPtr(pkProgressDlg);
		}
	}
	else
	{
		pkProgressDlg = reinterpret_cast<ProgressDialog*>(SendMessage(
			ms_pCommander->GetUIManager()->GetMainWindow(),
			WM_SHOWDIALOGPROGRESS, NULL, NULL));
	}
		 

	//-------------------------------------------------------------
	// Create a new file in current directory...
	//-------------------------------------------------------------
	std::fstream fs;
	fs.open (pszName, std::fstream::out | std::fstream::binary 
		| std::fstream::trunc);	

	wchar_t szOnlyFileName[MAX_PATH];
	::wcscpy(szOnlyFileName, pszName);
	// Removes the path portion of a fully qualified path and file.
	::PathStripPath (szOnlyFileName);

	pkProgressDlg->SetText(szOnlyFileName);
	pkProgressDlg->SetRange(0, llFileSize);
	::PostMessage(pkProgressDlg->GetHWND(), WM_REDRAWGRAPH, 0, 0);

	if ( fs.fail() )
	{
		if (pFileBuffer)
		{
			delete[] pFileBuffer;
		}

		TransferIndicator::GetSingleton()->SetFailed(hEvent);
		return false;
	}

	//--------------------------------------------------------------
	//	Read data from server then write to file...
	//--------------------------------------------------------------
	while ((cbBytes = recv(sockConn, pFileBuffer + iFileBufferPos, 
		iCurrentCapacity, 0)) > 0)
	{
		if (cbBytes < 0)
		{
			if (pFileBuffer)
			{
				delete[] pFileBuffer;
				pFileBuffer = nullptr;
			}

			TransferIndicator::GetSingleton()->SetFailed(hEvent);
			return false;
		}

		llTotle += cbBytes;
		iFileBufferPos += cbBytes;
		iCurrentCapacity -= cbBytes;

		pkProgressDlg->SetCurrentValue(llTotle);
		//::PostMessage(pkProgressDlg->GetHWND(), WM_REDRAWGRAPH, 0, 0);
		pkProgressDlg->Update();

		if (pkProgressDlg->IsCanceled())
		{
			fs.close();
			pkProgressDlg->Exit();

			if (pFileBuffer)
			{
				delete[] pFileBuffer;
				pFileBuffer = nullptr;
			}

			TransferIndicator::GetSingleton()->SetFailed(hEvent);
			TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->StopAndClearPipeline();
			return true;
		}

		//Write the received partial file data to the hard disk...
		if (iCurrentCapacity <= 0 || llTotle >= llFileSize)
		{
			fs.write(pFileBuffer, iFileBufferPos);

			if (fs.bad())
			{
				fs.close();

				if (pFileBuffer)
				{
					delete[] pFileBuffer;
					pFileBuffer = nullptr;
				}

				TransferIndicator::GetSingleton()->SetFailed(hEvent);
				return false;
			}

			// Reset values.
			iFileBufferPos = 0;
			iCurrentCapacity = ms_uiFILEBUFFERSIZE;

		}
		

		if (llTotle >= llFileSize)
		{
			if (!TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->HasNext())
			{
				pkProgressDlg->SetFinish(true);
				//::Sleep(20);
			}

			TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->SetWaitEvent();
			
			break;
		}

	}

	fs.close();

	// If receiving failed.
	if (cbBytes < 0)
	{
		pkProgressDlg->SetText(L"Transfer Failed!");
		pkProgressDlg->SetFinish(true);
		TransferIndicator::GetSingleton()->SetFailed(hEvent);
		TransferIndicator::GetSingleton()->GetMultiFileCoordinator()->SetWaitEvent();
	}

	if (pFileBuffer)
	{
		delete[] pFileBuffer;
		pFileBuffer = nullptr;
	}

	TransferIndicator::GetSingleton()->SetFinish(hEvent);

	return true;

}

//--------------------------------------------------------------





