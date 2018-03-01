#include "stdafx.h"
#include "SouiInit.h"

[!if CHECKBOX_SHELLNOTIFYICON]
#include "trayicon\SShellNotifyIcon.h"
[!endif]
//��PE�ļ����أ�ע����ļ�����·��λ��
#define RES_TYPE [!output ResLoaderType]
//#define SYSRES_TYPE [!output ResLoaderType]
// #define RES_TYPE 0   //PE
// #define RES_TYPE 1   //ZIP
// #define RES_TYPE 2   //7z
// #define RES_TYPE 2   //�ļ�
//ȥ������֧�֣���������Եû���
#if (RES_TYPE==1)
#include "resprovider-zip\zipresprovider-param.h"
#else 
#if (RES_TYPE==2)
#include "resprovider-7zip\zip7resprovider-param.h"
#endif
#endif
#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif
[!if CHECKBOX_USE_LUA]
#ifdef _DEBUG
#pragma comment(lib,"lua-52d")
#pragma comment(lib,"scriptmodule-luad")
#else
#pragma comment(lib,"lua-52")
#pragma comment(lib,"scriptmodule-lua")
#endif
[!endif]


//����Ψһ��һ��R,UIRES����,ROBJ_IN_CPP��resource.h�ж���ĺꡣ
ROBJ_IN_CPP

void InitDir(TCHAR *Path)
{
	if (Path == NULL)
	{
		TCHAR szCurrentDir[MAX_PATH] = { 0 };
		GetModuleFileName(NULL, szCurrentDir, sizeof(szCurrentDir));

		LPTSTR lpInsertPos = _tcsrchr(szCurrentDir, _T('\\'));
#ifdef _DEBUG
		_tcscpy(lpInsertPos + 1, _T("..\\[!output PROJECT_NAME]"));
#else
		_tcscpy(lpInsertPos + 1, _T("\0"));
#endif
		SetCurrentDirectory(szCurrentDir);
	}
	else
		SetCurrentDirectory(Path);
}

void InitSystemRes(SApplication * theApp,SComMgr *pComMgr)
{
[!if CHECKBOX_RES_PACK_ONLAY_RELEASE]
#ifdef _DEBUG
	//ѡ���˽���Release�汾�����Դ��ϵͳ��Դ��DEBUG��ʼ��ʹ��DLL����
	{
		HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
		if (hModSysResource)
		{
			CAutoRefPtr<IResProvider> sysResProvider;
			CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
			sysResProvider->Init((WPARAM)hModSysResource, 0);
			theApp->LoadSystemNamedResource(sysResProvider);
			FreeLibrary(hModSysResource);
		}
		else
		{
			SASSERT(0);
		}
	}
#else		
[!if CHECKBOX_SYSRES_BUILTIN]
	//��ѡ�˸���ϵͳ��Դѡ��
	{
		CAutoRefPtr<IResProvider> pSysResProvider;
[!if ResLoaderType == 0]
		CreateResProvider(RES_PE, (IObjRef**)&pSysResProvider);
		bLoaded = pSysResProvider->Init((WPARAM)hInstance, 0);
		SASSERT(bLoaded);
		bLoaded = theApp->LoadSystemNamedResource(pSysResProvider);
		SASSERT(bLoaded);
[!endif]
[!if ResLoaderType == 1]
		bLoaded = pComMgr->CreateResProvider_ZIP((IObjRef**)&pSysResProvider);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));
		ZIPRES_PARAM param;
		param.ZipFile(theApp->GetRenderFactory(), _T("uires.zip"), "[!output ZIP_PSW]",_T("theme_sys_res"));
		bLoaded = pSysResProvider->Init((WPARAM)&param, 0);
		SASSERT(bLoaded);
		bLoaded = theApp->LoadSystemNamedResource(pSysResProvider);
		SASSERT(bLoaded);
[!endif]
[!if ResLoaderType == 2]
		bLoaded = pComMgr->CreateResProvider_7ZIP((IObjRef**)&pSysResProvider);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));
		ZIP7RES_PARAM param;
		param.ZipFile(theApp->GetRenderFactory(), _T("uires.7z"), "[!output ZIP_PSW]", _T("theme_sys_res"));
		bLoaded = pSysResProvider->Init((WPARAM)&param, 0);
		SASSERT(bLoaded);
		bLoaded = theApp->LoadSystemNamedResource(pSysResProvider);
		SASSERT(bLoaded);
[!endif]
[!if ResLoaderType == 3]
		CreateResProvider(RES_FILE, (IObjRef**)&pSysResProvider);
		bLoaded = pSysResProvider->Init((LPARAM)_T("uires\\theme_sys_res"), 0);
		SASSERT(bLoaded);
		bLoaded = theApp->LoadSystemNamedResource(pSysResProvider);
		SASSERT(bLoaded);
[!endif]
	}
[!else]
	//��DLL����ϵͳ��Դ
	{
		HMODULE hModSysResource = LoadLibrary(SYS_NAMED_RESOURCE);
		if (hModSysResource)
		{
			CAutoRefPtr<IResProvider> sysResProvider;
			CreateResProvider(RES_PE, (IObjRef**)&sysResProvider);
			sysResProvider->Init((WPARAM)hModSysResource, 0);
			theApp->LoadSystemNamedResource(sysResProvider);
			FreeLibrary(hModSysResource);
		}
		else
		{
			SASSERT(0);
		}
	}
[!endif]
#endif
[!endif]
}

void InitUserRes(SApplication * theApp, SComMgr *pComMgr)
{
	CAutoRefPtr<IResProvider>   pResProvider;

[!if CHECKBOX_RES_PACK_ONLAY_RELEASE]
#ifdef _DEBUG		
	//ѡ���˽���Release�汾�����Դ����DEBUG��ʼ��ʹ���ļ�����
	{
		CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
		BOOL bLoaded = pResProvider->Init((LPARAM)_T("uires"), 0);
		SASSERT(bLoaded);
	}
#else
	{
[!if ResLoaderType == 0]
		CreateResProvider(RES_PE, (IObjRef**)&pResProvider);
		BOOL bLoaded = pResProvider->Init((WPARAM)hInstance, 0);
		SASSERT(bLoaded);
[!endif]
[!if ResLoaderType == 1]
		BOOL bLoaded = pComMgr->CreateResProvider_ZIP((IObjRef**)&pResProvider);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));
		ZIPRES_PARAM param;
		param.ZipFile(theApp->GetRenderFactory(), _T("uires.zip"), "[!output ZIP_PSW]");
		bLoaded = pResProvider->Init((WPARAM)&param, 0);
		SASSERT(bLoaded);
[!endif]
[!if ResLoaderType == 2]
		BOOL bLoaded = pComMgr->CreateResProvider_7ZIP((IObjRef**)&pResProvider);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("resprovider_zip"));
		ZIP7RES_PARAM param;
		param.ZipFile(theApp->GetRenderFactory(), _T("uires.7z"), "[!output ZIP_PSW]");
		bLoaded = pResProvider->Init((WPARAM)&param, 0);
		SASSERT(bLoaded);
[!endif]
[!if ResLoaderType == 3]
		CreateResProvider(RES_FILE, (IObjRef**)&pResProvider);
		BOOL bLoaded = pResProvider->Init((LPARAM)_T("uires"), 0);
		SASSERT(bLoaded);
[!endif]
	}
#endif
[!endif]
	theApp->InitXmlNamedID(namedXmlID, ARRAYSIZE(namedXmlID), TRUE);
	theApp->AddResProvider(pResProvider);
}

void SUserObjectDefaultRegister::RegisterWindows(SObjectFactoryMgr * objFactory)
{	
#define RegWnd(wndClass) objFactory->TplRegisterFactory<wndClass>();
	
[!if CHECKBOX_SHELLNOTIFYICON]
	RegWnd(SShellNotifyIcon)
[!endif]
}
