//--------------------------------------------------------------
//	SettingsDialog.h.
//	6/25/2013.		by bubo.
//--------------------------------------------------------------
#pragma once

#ifndef _SETTINGSDIALOG_H
#define _SETTINGSDIALOG_H

//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "windows.h"


//--------------------------------------------------------------
namespace cinderella
{
	//--------------------------------------------------------------
	class SettingsDialog
	{
	public:
		static SettingsDialog* GetSingleton();
		void DestroyInstance();
		static bool IsDialogMsg(LPMSG pMsg);
		HWND CreateUI();
		bool Initialize(HWND hWndParent, HINSTANCE);
		const wchar_t* GetIPMask() const;
		const wchar_t* GetName() const;
		bool SaveCurrentPosition();
		bool RetrieveCurrentPosition();

	private:
		SettingsDialog();
		SettingsDialog(SettingsDialog&);
		~SettingsDialog();
		void WirteToRegister(HWND);

		static INT_PTR CALLBACK fnSettingsDialog(HWND hDlg, UINT message, 
			WPARAM wParam, 
			LPARAM lParam);
		static void OnInitDialog (HWND hDlg);

	private:
		static SettingsDialog* ms_pkSettingsDialog;
		static HINSTANCE ms_hInstance;
		static HWND ms_hWndParent;

		HWND m_hWndDlg;	
		wchar_t m_szName[100];
		wchar_t m_szIPMask[100];

	};

	//--------------------------------------------------------------
}

//--------------------------------------------------------------
#endif // !_SETTINGSDIALOG_H


