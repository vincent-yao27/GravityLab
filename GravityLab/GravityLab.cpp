// GravityLab.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "GravityLab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//TODO: ����� DLL ����� MFC DLL �Ƕ�̬���ӵģ�
//		��Ӵ� DLL �������κε���
//		MFC �ĺ������뽫 AFX_MANAGE_STATE ����ӵ�
//		�ú�������ǰ�档
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CGravityLabApp

BEGIN_MESSAGE_MAP(CGravityLabApp, CWinApp)
END_MESSAGE_MAP()


// CGravityLabApp ����
CGravityLabApp::CGravityLabApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CGravityLabApp ����
CGravityLabApp theApp;


// CGravityLabApp ��ʼ��
BOOL CGravityLabApp::InitInstance()
{
	CWinApp::InitInstance();

	MainFrame *wnd = new MainFrame();	// m_pMainWnd �����ö������� theApp ��Ա�������˳�ʱ����
	m_pMainWnd = wnd;

	wnd->Create(NULL, L"GravityLab");
	wnd->ShowWindow(SW_SHOWMAXIMIZED);

	return TRUE;
}
