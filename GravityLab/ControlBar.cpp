/************

GravityLab
ControlBar.h

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (姚裕欣).

Released under GPL-3.0 license

************/

#include "stdafx.h"
#include "GravityLab.h"
#include "ControlBar.h"
#include "afxdialogex.h"

// ControlBar 对话框

IMPLEMENT_DYNAMIC(ControlBar, CDialogBar)


BOOL ControlBar::Create(MainFrame *mainFrame, UINT nID) {
	pFrame = mainFrame;
	return CDialogBar::Create(mainFrame, IDD, WS_CHILD | WS_VISIBLE, nID);
}

void ControlBar::DoDataExchange(CDataExchange* pDX)
{
	CDialogBar::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_INPUT_MASS, mMass);
}


BEGIN_MESSAGE_MAP(ControlBar, CDialogBar)
	ON_UPDATE_COMMAND_UI(IDC_BTN_CLEAR, &ControlBar::OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BTN_RANDOM, &ControlBar::OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BTN_NEW, &ControlBar::OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BTN_RESET, &ControlBar::OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BTN_START, &ControlBar::OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_BTN_SPEED, &ControlBar::OnUpdateButton)
	ON_UPDATE_COMMAND_UI(IDC_ABOUT, &ControlBar::OnUpdateButton)
	ON_BN_CLICKED(IDC_BTN_NEW, &ControlBar::OnBnClickedBtnNew)
	ON_BN_CLICKED(IDC_BTN_START, &ControlBar::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &ControlBar::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_RANDOM, &ControlBar::OnBnClickedBtnRandom)
	ON_BN_CLICKED(IDC_BTN_RESET, &ControlBar::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_SPEED, &ControlBar::OnBnClickedBtnSpeed)
	ON_BN_CLICKED(IDC_ABOUT, &ControlBar::OnBnClickedAbout)
END_MESSAGE_MAP()


// ControlBar 消息处理程序


void ControlBar::OnUpdateButton(CCmdUI *pCmdUI) {
	pCmdUI->Enable(TRUE);
}

void ControlBar::OnBnClickedBtnClear() {
	pFrame->setFlag(SPACE_FLAG_CLEAR);
}

void ControlBar::OnBnClickedBtnRandom() {
	pFrame->setFlag(SPACE_FLAG_RANDOM);
}

void ControlBar::OnBnClickedBtnNew() {
	CString str;
	GetDlgItem(IDC_INPUT_MASS)->GetWindowText(str);
	if (str.IsEmpty())
		mMass = 0;
	else
		UpdateData(TRUE);
	isCreating(true);
}

void ControlBar::OnBnClickedBtnStart() {
	if (mIsPlaying) {
		mIsPlaying = false;
		SetDlgItemText(IDC_BTN_START, L"Start");
	} else {
		mIsPlaying = true;
		SetDlgItemText(IDC_BTN_START, L"Pause");
	}
}

void ControlBar::OnBnClickedBtnReset() {
	pFrame->setFlag(SPACE_FLAG_RESET);
}


void ControlBar::OnBnClickedBtnSpeed()
{
	switch (mSpeed) {
	case 1:
		mSpeed = 2;
		SetDlgItemText(IDC_BTN_SPEED, L"Speed x2");
		break;
	case 2:
		mSpeed = 4;
		SetDlgItemText(IDC_BTN_SPEED, L"Speed x4");
		break;
	case 4:
		mSpeed = 1;
		SetDlgItemText(IDC_BTN_SPEED, L"Speed x1");
		break;
	}
}


void ControlBar::OnBnClickedAbout()
{
	pFrame->showAbout();
}
