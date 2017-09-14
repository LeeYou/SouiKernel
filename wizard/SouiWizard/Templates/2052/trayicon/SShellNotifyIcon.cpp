//////////////////////////////////////////////////////////////////////////
//  Class Name: SShellNotifyIcon
// Description:show ShellNotifyIcon
//     Creator: 359501300
//     Version: 2017.9.11 - 2.0 - Create
//////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SShellNotifyIcon.h"
#include "helper\smenuex.h"
#include "helper\SMenu.h"
namespace SOUI
{
	SShellNotifyIcon::SShellNotifyIcon():m_hIcon(nullptr),m_menuType(unknow),m_MsgOnlyWnd(NULL)
	{
		memset(&nid, 0, sizeof(nid));
	}

	SShellNotifyIcon::~SShellNotifyIcon(){}

	void SShellNotifyIcon::Create(HWND hOwner, HICON hIcon, UINT uFlags, UINT uCallbackMessage, UINT uId)
	{
		IniNotifyIconData(hOwner, hIcon, uFlags, uCallbackMessage, uId, m_strTip);
	}

	void SShellNotifyIcon::ShowMenu()
	{
		switch (m_menuType)
		{
		case MenuType::menu:
		{
			SMenu tmenu;
			if (tmenu.LoadMenu(m_strMenu))
			{
				POINT pt;
				GetCursorPos(&pt);
				SetForegroundWindow(m_MsgOnlyWnd->m_hWnd);
				tmenu.TrackPopupMenu(0, pt.x, pt.y, m_MsgOnlyWnd->m_hWnd);
			}
		}
		break;
		case MenuType::menuex:
		{
			SMenuEx tmenuex;
			if (tmenuex.LoadMenu(m_strMenu))
			{
				POINT pt;
				GetCursorPos(&pt);
				SetForegroundWindow(m_MsgOnlyWnd->m_hWnd);
				tmenuex.TrackPopupMenu(0, pt.x, pt.y, m_MsgOnlyWnd->m_hWnd);
			}
		}
		break;
		}
	}

	inline HRESULT SShellNotifyIcon::SetMenu(SStringT strValue, BOOL bLoading)
	{
		pugi::xml_document xmlDoc;
		if (SApplication::getSingleton().LoadXmlDocment(xmlDoc, strValue))
		{
			if (_tcscmp(xmlDoc.first_child().name(), _T("menu")) == 0)
				m_menuType = MenuType::menu;
			else if ((_tcscmp(xmlDoc.first_child().name(), _T("menuRoot")) == 0) || (_tcscmp(xmlDoc.first_child().name(), _T("menuItem")) == 0))
				m_menuType = MenuType::menuex;
			else m_menuType = MenuType::unknow;

			if (MenuType::unknow != m_menuType)
				m_strMenu = strValue;
			return S_OK;
		}
		else return S_FALSE;
	}

	BOOL SShellNotifyIcon::Show()
	{
		//未初使化NotifyIconData
		if (nid.cbSize != sizeof(NOTIFYICONDATA))
			return FALSE;
		return Shell_NotifyIcon(NIM_ADD, &nid);
	}

	BOOL SShellNotifyIcon::Hide()
	{
		return Shell_NotifyIcon(NIM_DELETE, &nid);
	}

	BOOL SShellNotifyIcon::CreateChildren(pugi::xml_node xmlNode)
	{
		SHostWnd *pHostWnd = (SHostWnd*)(GetTopLevelParent()->GetContainer());
		SASSERT(pHostWnd);
		m_MsgOnlyWnd = new CShellNotifyHwnd2(pHostWnd, this);
		SASSERT(IsWindow(m_MsgOnlyWnd->m_hWnd));
		Create(m_MsgOnlyWnd->m_hWnd, m_hIcon ? m_hIcon : GETRESPROVIDER->LoadIcon(_T("ICON_LOGO"), 16));
		return Show();
	}

	void SShellNotifyIcon::OnFinalRelease()
	{
		if (m_MsgOnlyWnd)
		{
			Hide();
			m_MsgOnlyWnd->PostMessage(WM_CLOSE);
		}
	}

	void SShellNotifyIcon::IniNotifyIconData(HWND hOwner, HICON hIcon, UINT flags, UINT callbackmsg, UINT ID, LPCTSTR szTip)
	{
		nid.cbSize = sizeof(NOTIFYICONDATA);
		nid.hWnd = hOwner;
		nid.uID = ID;
		nid.uFlags = flags;//NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = callbackmsg;
		nid.hIcon = hIcon;
		_tcscpy_s(nid.szTip, szTip);
	}
}