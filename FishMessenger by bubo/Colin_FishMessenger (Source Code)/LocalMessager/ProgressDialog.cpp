//--------------------------------------------------------------
//	ProgressDialog.cpp.
//	6/22/2013.		by bubo.
//	Modified		6/23/2013.
//--------------------------------------------------------------
//	Headers.
//--------------------------------------------------------------
#include "ProgressDialog.h"
#include "resource.h"
#include <Windowsx.h>
#include <Gdiplus.h>
#include "Messages.h"

using namespace Gdiplus;
using namespace cinderella;

//--------------------------------------------------------------
//	Initialize static variables...
//--------------------------------------------------------------
HWND ProgressDialog::ms_hWndParent = nullptr;
map<HWND, ProgressDialog*> ProgressDialog::ms_pkDialogContainer;
ULONG_PTR ProgressDialog::ms_gdiplusToken = NULL;
HINSTANCE ProgressDialog::ms_hInstance = nullptr;

//--------------------------------------------------------------
ProgressDialog::ProgressDialog(): m_hDlg(nullptr), m_bFinish(false),
	m_llEnd(100ll), m_llStart(0ll), m_llCurrentValue(20ll), 
	m_bCanceled(false), m_bFirst(true)
{
	m_szText[0] = 0;

	//Create the Dialog box...
	m_hDlg = ::CreateDialog (ms_hInstance, MAKEINTRESOURCE (IDD_DIALOGPROGRESS),
		ms_hWndParent, fnProgressDialog);


	if (m_hDlg)
	{
		ms_pkDialogContainer [m_hDlg] = this;
	}
}

//--------------------------------------------------------------
INT_PTR CALLBACK ProgressDialog::fnProgressDialog(HWND hDlg, 
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


	case WM_PAINT:

		if (ms_pkDialogContainer[hDlg]->m_bFinish)
		{
			ms_pkDialogContainer[hDlg]->Update();
		
			::PostMessage(hDlg, WM_REDRAWGRAPH, NULL, NULL);
		}

		return false;

	case WM_REDRAWGRAPH:

		ms_pkDialogContainer[hDlg]->Update();
		
		return true;

	case WM_COMMAND:

		switch (LOWORD (wParam))
		{
		case IDC_BUTTONCANCEL:

			ms_pkDialogContainer[hDlg]->m_bCanceled = true;

			return true;

		case IDC_BUTTONFINISHED:

			::AnimateWindow(hDlg, 600, AW_CENTER | AW_HIDE);
			::DestroyWindow(hDlg);

			if (ms_pkDialogContainer.find (hDlg) != ms_pkDialogContainer.end ())
			{
				delete ms_pkDialogContainer[hDlg];
			}

			return true;

		case IDC_BUTTONHIDE:

			::AnimateWindow(hDlg, 600, AW_CENTER | AW_HIDE);
			/*::ShowWindow(hDlg, HIDE_WINDOW);*/

			return true;

		}

		break;

	}

	return false;
}

//--------------------------------------------------------------
void ProgressDialog::OnInitDialog(HWND hDlg)
{
	::AnimateWindow (hDlg, 600, AW_CENTER | AW_ACTIVATE );

	return;
}

//--------------------------------------------------------------
void ProgressDialog::Update()
{
	HWND hDrawingWnd = GetDlgItem(m_hDlg, IDC_STATICPIE);
	HDC hDC = ::GetDC(hDrawingWnd);
	RECT kRect;

	::GetClientRect(hDrawingWnd, &kRect);

	HWND hTextWnd = ::GetDlgItem(m_hDlg, IDC_STATICINFO);


	if (m_bFirst)
	{
		::InvalidateRect(hDrawingWnd, NULL, true);
	}

	if (hTextWnd && m_bFirst)
	{
		::SetWindowText(hTextWnd, ms_pkDialogContainer[m_hDlg]->m_szText);
		m_bFirst = false;
	}
	
	// Transfer to the center of window.
	::SetWindowOrgEx(hDC, -(kRect.right - kRect.left) / 2, 
		-(kRect.bottom - kRect.top) / 2, nullptr);

	Rect kTempRect(-(kRect.right - kRect.left) / 2, -(kRect.bottom - kRect.top) / 2, 
		(kRect.right - kRect.left - 1), (kRect.bottom - kRect.top - 1));


	Graphics graphics(hDC);

	// Create a path that consists of a single ellipse.
	GraphicsPath path;
	path.AddEllipse(kTempRect);

	// Use the path to construct a brush.
	PathGradientBrush pthGrBrush(&path);
	pthGrBrush.SetGraphicsPath(&path);

	// Set the color at the center of the path to blue.
	pthGrBrush.SetCenterColor(Color(255, 180, 180, 180));

	// Set the color along the entire boundary of the path to aqua.
	Color colors[] = { Color(255, 90, 90, 90) };
	int count = 1;
	pthGrBrush.SetSurroundColors(colors, &count);

	// Define the pie.
	REAL startAngle = -90.0f;
	REAL sweepAngle = 360.0f * (static_cast<float>(ms_pkDialogContainer[m_hDlg]->m_llCurrentValue) / 
		(ms_pkDialogContainer[m_hDlg]->m_llEnd - ms_pkDialogContainer[m_hDlg]->m_llStart));

	graphics.SetCompositingQuality(CompositingQualityHighQuality);

	// Draw the pie.
	graphics.FillPie(&pthGrBrush, kTempRect, startAngle, sweepAngle);

	::ReleaseDC(hDrawingWnd, hDC);

	
	return;

}

//--------------------------------------------------------------
void ProgressDialog::SetCurrentValue(long long llValue)
{
	m_llCurrentValue = llValue;
}

//--------------------------------------------------------------
void ProgressDialog::SetRange(long long llStart, long long llEnd)
{
	m_llStart = llStart;
	m_llEnd = llEnd;

	m_bFirst = true;
}

//--------------------------------------------------------------
void ProgressDialog::Initialize(HWND hWndParent, HINSTANCE hInstance)
{
	ms_hWndParent = hWndParent;
	ms_hInstance = hInstance;

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	
	GdiplusStartup(&ms_gdiplusToken, &gdiplusStartupInput, NULL);
}

//--------------------------------------------------------------
bool ProgressDialog::IsDialogMsg(LPMSG pMsg)
{
	// Message loop...
	for (auto it : ms_pkDialogContainer)
	{
		if(::IsDialogMessage(it.first, pMsg))
			return true;
	}

	return false;
}

//--------------------------------------------------------------
void ProgressDialog::Shutdown()
{
	GdiplusShutdown(ms_gdiplusToken);
}

//--------------------------------------------------------------
void ProgressDialog::SetText(wchar_t* szFileInfo)
{
	m_bFirst = true;
	::wcscpy(m_szText, szFileInfo);
}

//--------------------------------------------------------------
void ProgressDialog::SetFinish(bool bFinish /*= true*/)
{
	m_llCurrentValue = m_llEnd;
	Update();

	m_bFinish = bFinish;

	HWND hFinishBtn = ::GetDlgItem(m_hDlg, IDC_BUTTONFINISHED);
	HWND hCencelBtn = ::GetDlgItem(m_hDlg, IDC_BUTTONCANCEL);

	::SetWindowLongPtr(hCencelBtn, GWLP_ID, IDC_BUTTONFINISHED);
	::SetWindowText(hCencelBtn, L"FINISHed");
	
}

//--------------------------------------------------------------
bool ProgressDialog::IsCanceled() const
{
	return m_bCanceled;
}

//--------------------------------------------------------------
void ProgressDialog::Exit()
{
	::PostMessage(m_hDlg, WM_COMMAND, MAKELPARAM(IDC_BUTTONFINISHED,
		0), 0ul);
}

//--------------------------------------------------------------
void ProgressDialog::ShowAllProgresses()
{
	for (auto it : ms_pkDialogContainer)
	{
		if (!::IsWindowVisible(it.first))
		{
			ms_pkDialogContainer[it.first]->m_bFirst = true;
			//::ShowWindow(it.first, SW_SHOWNORMAL);
			::AnimateWindow(it.first, 600, AW_CENTER | AW_ACTIVATE);
			::UpdateWindow(it.first);
			ms_pkDialogContainer[it.first]->Update();
		}		
		
	}
}

//--------------------------------------------------------------
void ProgressDialog::HideAllProgresses()
{
	for (auto it : ms_pkDialogContainer)
	{
		if (::IsWindowVisible(it.first))
		{
			::AnimateWindow(it.first, 500, AW_CENTER | AW_HIDE);
			//::ShowWindow(it.first, SW_HIDE);
		}
		
	}
}

//--------------------------------------------------------------
ProgressDialog::~ProgressDialog()
{
	auto it = ms_pkDialogContainer.find (m_hDlg);

	if (it != ms_pkDialogContainer.end ())
	{
		ms_pkDialogContainer.erase (it);
	}

}

//--------------------------------------------------------------
HWND ProgressDialog::GetHWND()
{
	//
	return m_hDlg;
}

//--------------------------------------------------------------


