//--------------------------------------------------------------
//	Communicator.h.
//	06/08/2013.		by bubo.
//	03/13/2014		Modified.
//--------------------------------------------------------------
#pragma once

#ifndef _COMMUNICATOR_H
#define _COMMUNICATOR_H
 
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include <WinSock2.h>
#include <Mstcpip.h>
#include <Ws2tcpip.h>
#include <map>

#define MAXDATASIZE 8192

using namespace std;

//--------------------------------------------------------------
namespace cinderella
{	
	//--------------------------------------------------------------
	class Commander;

	//--------------------------------------------------------------
	class Communicator
	{
	public:
		//--------------------------------------------------------------
		//	Helper structure.
		//--------------------------------------------------------------
		typedef struct _IP_SOCKET
		{
			wstring m_szIP;
			SOCKET m_Socket;
		} IP_SOCKET;

		//--------------------------------------------------------------
		//	Enumeration for types of transfer...
		//--------------------------------------------------------------
		enum TRANSFERTYPE
		{
			TR_REGISTER = 0,
			TR_UNREGISTER,
			TR_QUERY,
			TR_MSG,
			TR_NUM
		};

		//--------------------------------------------------------------
		//	Inner class UserData which holds the user's Data.
		//--------------------------------------------------------------
		class UserData
		{
		public:
			const wchar_t* GetUserNameW () const;
			const wchar_t* GetUserData () const;
			TRANSFERTYPE GetUserType () const;
			void SetUserNameW (const wchar_t*);
			void SetUserData (const wchar_t*);
			void SetUserType (TRANSFERTYPE);

		public:
			sockaddr_in6 ClientAddr;

		private:
			TRANSFERTYPE m_eTranType;
			wchar_t m_szUserName[100];
			/*wchar_t m_szUserData[MAXDATASIZE];*/
		};
		//--------------------------------------------------------------
		//	End of UserData.
		//--------------------------------------------------------------

		//--------------------------------------------------------------
		//	Inner class UserDataText which holds the user's Text.
		//--------------------------------------------------------------
		class UserDataText : public UserData
		{
		public:
			const wchar_t* GetUserData() const;
			void SetUserData(const wchar_t*);

		private:
			wchar_t m_szUserData[MAXDATASIZE];
		};

		//--------------------------------------------------------------
		//	End of UserDataText.
		//--------------------------------------------------------------

		//--------------------------------------------------------------
		//	Inner class FileHeader which holds the file's information.
		//--------------------------------------------------------------
		class FileHeader
		{
		public:
			//--------------------------------------------------------------
			//	Enumeration for types of File confirming info ...
			//--------------------------------------------------------------
			enum FILECONFIRM
			{
				FC_REGULAR = 0,
				FC_REGULARMULTI,
				FC_DIRECTORY,
				FC_OK,
				FC_CANCLE,
				FC_NUM
			};

			//--------------------------------------------------------------
			//	Enumeration for types of File...
			//--------------------------------------------------------------
			enum FILETYPE
			{
				FT_REGULAR = 0,
				FT_DIRECTORY,
				FT_NUM
			};

			//--------------------------------------------------------------

		public:
			FileHeader ();
			const wchar_t* GetFileName () const;
			long long GetFileSize () const;
			void SetFileSize (long long);
			void SetFileName (const wchar_t*);
			bool GetContinueState () const;
			void SetContinueState (bool bContinue = false);
			FILETYPE GetFileType () const;
			void SetFileType (FILETYPE); 
			wchar_t* GetFileLevel() const;
			void SetFileLevel(wchar_t*);

		private:
			wchar_t m_szFileName[MAX_PATH];
			long long m_cbSize;
			bool m_bConuinue;
			FILETYPE m_eFileType;
			wchar_t* m_szFileLevel;
		};

		//--------------------------------------------------------------
		//	End or FileHeader.
		//--------------------------------------------------------------

	public:
		//--------------------------------------------------------------
		//	Initialize the Network settings...
		//--------------------------------------------------------------
		bool Initialize (int iPort);

		//--------------------------------------------------------------
		//	Comment: true -> register, false -> unregister.
		//--------------------------------------------------------------
		void BroadcastInfo (bool bRegister = true); 

		//--------------------------------------------------------------
		//	Used for broadcasting query information...
		//--------------------------------------------------------------
		void BroadcastQueryInfo ();

		//--------------------------------------------------------------
		//	The basic sending UDP data function on which many methods can
		//	send some special data...
		//--------------------------------------------------------------
		bool SendDataUDP(UserData* pUserData, sockaddr_in6* pRecvAddr);
		bool SendDataUDPText(UserDataText* pUserDataText, sockaddr_in6* pRecvAddr);

		//--------------------------------------------------------------
		bool TransferDataTCP(wchar_t* pszName, sockaddr_in6* pRecvAddr,
			FileHeader::FILETYPE);
		void SetCommander (Commander*);
		const map<wstring, UserData*>& GetUserContainer () const;
		void SetLocalNameW(wchar_t*);
		wchar_t* GetLocalNameW ();
		UserData* GetUserData (wstring&);
		void SetIPMask(wchar_t*);

		Communicator ();
		Communicator (Communicator&){}
		~Communicator(){}

		//--------------------------------------------------------------

	protected:
		static Commander* ms_pCommander;

		//--------------------------------------------------------------
		//	*** The main data structure for user and its IP ***
		//--------------------------------------------------------------
		static map<wstring, UserData*> ms_UsersContainer;

		//--------------------------------------------------------------
		SOCKET m_sSocketUDP;
		SOCKET m_sSocketUDPText;
		SOCKET m_sSocketTCP;
		HANDLE m_hThreadTCP;
		HANDLE m_hThreadUDP;
		HANDLE m_hThreadUDPText;
		int m_iPort;
		wchar_t m_szName[100];
		in6_addr m_kIPMask;
		static const unsigned int ms_uiSOCKETBUFSIZE;
		static const unsigned int ms_uiFILEBUFFERSIZE;
		
		//--------------------------------------------------------------

	private:
		//--------------------------------------------------------------
		//	static thread functions for network...
		//--------------------------------------------------------------
		static unsigned long WINAPI fnThreadTCPAccept (LPVOID);
		static unsigned long WINAPI fnThreadTCPReceive (LPVOID);
		static unsigned long WINAPI fnThreadUDPReceive (LPVOID);
		static unsigned long WINAPI fnThreadUDPTextReceive(LPVOID);

		static void AddUser (UserData*);
		static void DeleteUser (UserData*);
		static void Communicator::SendInfoToUser (Communicator*, UserData* pUserData);
		static bool ProcessRecvFile(SOCKET, wchar_t*, HANDLE hEvent);
		bool ProcessSendFile(SOCKET, wchar_t*, FileHeader::FILETYPE);
		bool ProcessSendFile_Directory(SOCKET, wchar_t*);
		bool ProcessSendFile_Files(SOCKET, wchar_t*);
		static bool RecvingSingleFile(SOCKET, wchar_t*, long long, HANDLE);
	};

	//--------------------------------------------------------------
}


//---------------------------------------------------------------------
//		including inline files...
//---------------------------------------------------------------------
#include "Communicator.inl"

//---------------------------------------------------------------------
#endif //!_COMMUNICATOR_H




