// GravityLab.h : GravityLab DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGravityLabApp
// �йش���ʵ�ֵ���Ϣ������� GravityLab.cpp
//

class CGravityLabApp : public CWinApp {
public:
	CGravityLabApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
