/************

GravityLab
MainFrame.h

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (姚裕欣).

Released under GPL-3.0 license

************/

#pragma once

#include "ChildView.h"
#include "ControlBar.h"
#include "Space.h"

#define SPACE_FLAG_CLEAR 1U
#define SPACE_FLAG_RANDOM (1U << 1)
#define SPACE_FLAG_RESET (1U << 2)

class ControlBar;

// MainFrame 框架

class MainFrame : public CFrameWnd
{
	DECLARE_DYNCREATE(MainFrame)
public:
	MainFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~MainFrame();

	void setFlag(unsigned flag) {
		mFlag |= flag;
	}

	void showAbout() {
		mAboutDlg.DoModal();
	}

private:
	ControlBar mCtrlBar;
	CReBar mReBar;
	ChildView mView;

	CDialog mAboutDlg;

	Space mSpace;

	unsigned mFlag;

	const UINT_PTR mTimerID;

protected:
	DECLARE_MESSAGE_MAP()
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);

};


