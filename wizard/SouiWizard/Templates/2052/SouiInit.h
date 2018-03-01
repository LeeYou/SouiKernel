//�û��ؼ�/Ƥ��/����/��ֵ�㷨ע����
class SUserObjectDefaultRegister : public TObjRefImpl<ISystemObjectRegister>
{
public:
	void RegisterWindows(SObjectFactoryMgr *objFactory);
	//void RegisterSkins(SObjectFactoryMgr *objFactory);
	//void RegisterLayouts(SObjectFactoryMgr *objFactory);
	//void RegisterInterpolator(SObjectFactoryMgr *objFactory);
};
//Soui ������
class CSouiLoader
{
	SApplication *theApp;
	SComMgr *pComMgr;
public:
	//ͨ��������һ��ISystemObjectRegister������ע���û��ؼ������������SApplication�Ĳ���һ��
	CSouiLoader(HINSTANCE hInst,ISystemObjectRegister *pUserObjRegister=new SUserObjectDefaultRegister(), LPCTSTR pszHostClassName = _T("SOUIHOST"), ISystemObjectRegister *pSysObjRegister = new SObjectDefaultRegister()) 
		:theApp(NULL),pComMgr(NULL)
	{		
		pComMgr = new SComMgr;
		CAutoRefPtr<SOUI::IImgDecoderFactory> pImgDecoderFactory;
		CAutoRefPtr<SOUI::IRenderFactory> pRenderFactory;
[!if RADIO_RANDER_GDI]
		BOOL bLoaded = pComMgr->CreateRender_GDI((IObjRef**)&pRenderFactory);
[!else]
		BOOL bLoaded = pComMgr->CreateRender_Skia((IObjRef**)&pRenderFactory);
[!endif]
		SASSERT_FMT(bLoaded, _T("load interface [render] failed!"));
		bLoaded = pComMgr->CreateImgDecoder((IObjRef**)&pImgDecoderFactory);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("imgdecoder"));
		pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);
		theApp = new SApplication(pRenderFactory, hInst, pszHostClassName, pSysObjRegister);

		[!if CHECKBOX_USE_LUA]
		//����LUA�ű�ģ�顣
#if (defined(DLL_CORE) || defined(LIB_ALL)) && !defined(_WIN64)
		//����LUA�ű�ģ�飬ע�⣬�ű�ģ��ֻ����SOUI�ں�����DLL��ʽ����ʱ����ʹ�á�
		CAutoRefPtr<SOUI::IScriptFactory> pScriptLuaFactory;
		bLoaded = pComMgr->CreateScrpit_Lua((IObjRef**)&pScriptLuaFactory);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("scirpt_lua"));
		theApp->SetScriptFactory(pScriptLuaFactory);
#endif//DLL_CORE
[!endif]

[!if CHECKBOX_TRANSLATOR_SUPPORT]
		//���ض����Է���ģ�顣
		CAutoRefPtr<ITranslatorMgr> trans;
		bLoaded = pComMgr->CreateTranslator((IObjRef**)&trans);
		SASSERT_FMT(bLoaded, _T("load interface [%s] failed!"), _T("translator"));
		if (trans)
		{//�������Է����
			theApp->SetTranslator(trans);
			pugi::xml_document xmlLang;
			if (theApp->LoadXmlDocment(xmlLang, _T("lang_cn"), _T("translator")))
			{
				CAutoRefPtr<ITranslator> langCN;
				trans->CreateTranslator(&langCN);
				langCN->Load(&xmlLang.child(L"language"), 1);//1=LD_XML
				trans->InstallTranslator(langCN);
			}
		}
[!endif]

		//ע���û��Զ���Ķ���
		pUserObjRegister->RegisterLayouts(theApp);
		pUserObjRegister->RegisterSkins(theApp);
		pUserObjRegister->RegisterWindows(theApp);
		pUserObjRegister->RegisterInterpolator(theApp);
		pUserObjRegister->Release();
	}
	~CSouiLoader()
	{
		if (theApp)
			delete theApp;
		if (pComMgr)
			delete pComMgr;
	}
	SApplication *GetApp()
	{
		SASSERT(theApp);
		return theApp;
	}
	SComMgr *GetComMgr()
	{
		SASSERT(pComMgr);
		return pComMgr;
	}
};
//��ʹ����Դ����·��
void InitDir(TCHAR *Path=NULL);

void InitSystemRes(SApplication *theApp, SComMgr *pComMgr);

void InitUserRes(SApplication * theApp, SComMgr *pComMgr);

template<class T>
int Run(SApplication *theApp)
{
	T dlgMain;
	dlgMain.Create(GetActiveWindow());
	dlgMain.SendMessage(WM_INITDIALOG);
	dlgMain.CenterWindow(dlgMain.m_hWnd);
[!if CHECKBOX_MAXIMIZED]
	dlgMain.ShowWindow(SW_SHOWMAXIMIZED);
[!else]
	dlgMain.ShowWindow(SW_SHOWNORMAL);
[!endif]
	return theApp->Run(dlgMain.m_hWnd);
}

