/************

GravityLab
ControlBar.h

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (姚裕欣).

Released under GPL-3.0 license

************/

#pragma once

#include "resource.h"
#include "MainFrame.h"

class MainFrame;

// ControlBar 对话框

class ControlBar : public CDialogBar
{
	DECLARE_DYNAMIC(ControlBar)

public:
	ControlBar() : mMass(0.0), mIsCreating(false), mIsPlaying(false), mSpeed(1) { }

	BOOL Create(MainFrame *mainFrame, UINT nID);

	bool isCreating() { return mIsCreating; }
	void isCreating(bool b) { mIsCreating = b; }
	bool isPlaying() { return mIsPlaying; }
	double getMass() { return mMass * 1e5; }
	int getSpeed() { return mSpeed; }

// 对话框数据
	enum { IDD = IDD_DIALOGBAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

private:
	double mMass;
	bool mIsCreating;
	bool mIsPlaying;
	int mSpeed;

	MainFrame *pFrame;

public:
	afx_msg void OnUpdateButton(CCmdUI *pCmdUI);
	afx_msg void OnBnClickedBtnClear();
	afx_msg void OnBnClickedBtnRandom();
	afx_msg void OnBnClickedBtnNew();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnSpeed();
	afx_msg void OnBnClickedAbout();
};
