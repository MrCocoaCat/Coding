//--------------------------------------------------------------
//	Communicator.inl.
//	6/9/2013.		by bubo.
//	Modified		3/5/2014.
//--------------------------------------------------------------
using namespace cinderella;

//--------------------------------------------------------------
inline Communicator::UserData* Communicator::GetUserData (wstring& szIP)
{
	auto it = ms_UsersContainer.find(szIP);

	if (it != ms_UsersContainer.end ())
	{
		return ms_UsersContainer[szIP];
	}
	else
	{
		return nullptr;
	}

}

//--------------------------------------------------------------
inline void Communicator::SetIPMask(wchar_t* szIPMask)
{
	//convert the IP string to IPv6...
	::InetPtonW(AF_INET6, szIPMask, &m_kIPMask);  // IPv6

}


//--------------------------------------------------------------
inline wchar_t* Communicator::GetLocalNameW ()
{
	return m_szName;
}

//--------------------------------------------------------------
//	Class Communicator::UserData.  Inner Class.
//--------------------------------------------------------------
inline const wchar_t* Communicator::UserData::GetUserData () const
{
	//return m_szUserData;
}

//--------------------------------------------------------------
inline const wchar_t* Communicator::UserData::GetUserNameW () const
{
	return m_szUserName;
}

//--------------------------------------------------------------
inline Communicator::TRANSFERTYPE Communicator::UserData::GetUserType () const
{
	return m_eTranType;
}

//--------------------------------------------------------------
inline void Communicator::UserData::SetUserNameW (const wchar_t* pszName)
{
	wcscpy (m_szUserName, pszName);
}

//--------------------------------------------------------------
inline void Communicator::UserData::SetUserData (const wchar_t* pszData)
{
	//wcscpy (m_szUserData, pszData);
}

//--------------------------------------------------------------
inline void Communicator::UserData::SetUserType (TRANSFERTYPE eTransferType)
{
	m_eTranType = eTransferType;
}


//--------------------------------------------------------------
//	Class Communicator::UserDataText.  Inner Class.
//--------------------------------------------------------------
inline const wchar_t* Communicator::UserDataText::GetUserData() const
{
	return m_szUserData;
}

//--------------------------------------------------------------
inline void Communicator::UserDataText::SetUserData(const wchar_t* pszData)
{
	::wcscpy (m_szUserData, pszData);
}


//--------------------------------------------------------------
//	Class Communicator::FileHeader.
//--------------------------------------------------------------
inline const wchar_t* Communicator::FileHeader::GetFileName () const
{
	return m_szFileName;
}

//--------------------------------------------------------------
inline long long Communicator::FileHeader::GetFileSize () const
{
	return m_cbSize;
}

//--------------------------------------------------------------
inline void Communicator::FileHeader::SetFileSize (long long llSize)
{
	m_cbSize = llSize;
}

//--------------------------------------------------------------
inline void Communicator::FileHeader::SetFileName (const wchar_t* szName)
{
	::wcscpy (m_szFileName, szName);
}

//--------------------------------------------------------------
inline Communicator::FileHeader::FileHeader (): m_bConuinue (false),
	m_eFileType (FT_REGULAR)
{
	//
}

//--------------------------------------------------------------
inline bool Communicator::FileHeader::GetContinueState () const
{
	return m_bConuinue;
}

//--------------------------------------------------------------
inline void Communicator::FileHeader::SetContinueState (bool bContinue /*= false*/)
{
	m_bConuinue = bContinue;
}

//--------------------------------------------------------------
inline Communicator::FileHeader::FILETYPE Communicator::FileHeader::
	GetFileType () const
{
	return m_eFileType;
}

//--------------------------------------------------------------
inline void Communicator::FileHeader::SetFileType 
	(Communicator::FileHeader::FILETYPE eFileType)
{
	m_eFileType = eFileType;
}

//--------------------------------------------------------------
inline wchar_t* Communicator::FileHeader::GetFileLevel() const
{
	return m_szFileLevel;
}

//--------------------------------------------------------------
inline void Communicator::FileHeader::SetFileLevel(wchar_t* szFileLevel)
{
	wcscpy(m_szFileLevel, szFileLevel);
}

//--------------------------------------------------------------



