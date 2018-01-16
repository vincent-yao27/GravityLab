/************

GravityLab
MainFrame.cpp

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (Ҧԣ��).

Released under GPL-3.0 license

************/

#include "stdafx.h"
#include "GravityLab.h"
#include "MainFrame.h"


// MainFrame

IMPLEMENT_DYNCREATE(MainFrame, CFrameWnd)

MainFrame::MainFrame() : mTimerID(1), mSpace(0.001, 10), mFlag(0) {
	mView.init(&mSpace, &mCtrlBar);
}

MainFrame::~MainFrame() {
	KillTimer(mTimerID);
}


BEGIN_MESSAGE_MAP(MainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_TIMER()
//	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// MainFrame ��Ϣ�������


int MainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	// ����ReBar����ΪCtrlBar������
	if (!mReBar.Create(this)) {
		TRACE0("Failed to create ReBar\n");
		return -1;
	}

	// CtrlBar��������CDialogBar
	if (!mCtrlBar.Create(this, IDD_DIALOGBAR)) {
		TRACE0("Failed to create DlgBar\n");
		return -1;      // Fail to create.
	}

	// ��������ͼ
	if (!mView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW, CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL)) {
		TRACE0("Failed to create ChildView\n");
		return -1;
	}

	if (!mAboutDlg.Create(IDD_ABOUT)) {
		TRACE0("Failed to create AboutDlg\n");
		return -1;
	}

	mCtrlBar.UpdateData(FALSE);		// To set the mass input

	mReBar.AddBar(&mCtrlBar);		// ��CtrlBar��ӵ�ReBar����ʾ

	SetTimer(mTimerID, ChildView::interval, NULL);	// animation

	return 0;
}


void MainFrame::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == mTimerID) {
		mView.setFlag(mFlag);
		mFlag = 0;
		mView.InvalidateRect(NULL);
	}
	CFrameWnd::OnTimer(nIDEvent);
}