#pragma once
#include "core\SimpleWnd.h"
#include "helper\SMenu.h"
#include "SShellNotifyIcon.h"
//���һ���¼����մ�������ר�Ŵ�������ͼ��
#ifndef WM_ICONNOTIFY
#define WM_ICONNOTIFY (WM_USER + 1111)
#endif // !WM_ICONNOTIFY
#ifndef ID_TASKBARICON
#define ID_TASKBARICON	100
#endif // !ID_TASKBARICON


#define CHAIN_MSG_MAP_MEMBER_PTR(theChainMember) \
    { \
	bHandled=FALSE;BOOL bCanChain=TRUE;\
	if(theChainMember==nullptr||((uMsg!=WM_ICONNOTIFY)&&(uMsg!=WM_COMMAND)))\
		bCanChain=FALSE;\
    if(bCanChain&&theChainMember->ProcessWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
		bHandled=TRUE; \
		if(bHandled)\
			return TRUE;\
    }


#if _MSC_VER<1600
#define nullptr NULL
#endif

namespace SOUI
{
	class SShellNotifyIcon;
	class CShellNotifyHwnd2 :public CSimpleWnd
	{
	public:
		CShellNotifyHwnd2(SHostWnd* pMainWnd,SShellNotifyIcon* shellnotifyicon);
		~CShellNotifyHwnd2()
		{
		}
	protected:
		//����֪ͨ��Ϣ������
		LRESULT OnIconNotify(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL/* bHandled*/);
		LRESULT OnTaskbarCreated(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL);
		virtual void OnFinalMessage(HWND hWnd);
		BEGIN_MSG_MAP_EX(CShellNotifyHwnd2)
			//������Ϣ����
			MESSAGE_HANDLER(MsgTaskbarCreated, OnTaskbarCreated)
			CHAIN_MSG_MAP_MEMBER_PTR(m_pMainWnd)
			MESSAGE_HANDLER(WM_ICONNOTIFY, OnIconNotify)
			CHAIN_MSG_MAP(CSimpleWnd)
		END_MSG_MAP()
	private:
		SHostWnd            *m_pMainWnd;
		SShellNotifyIcon	*m_ShellNotifyIcon;
		UINT                MsgTaskbarCreated;		
	};
}