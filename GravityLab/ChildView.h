/************

GravityLab
ChildView.h

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (姚裕欣).

Released under GPL-3.0 license

************/

#pragma once

#include "Space.h"
#include "ControlBar.h"
#include <vector>

// ChildView

class ChildView : public CWnd {

	DECLARE_DYNAMIC(ChildView)

public:
	ChildView();
	virtual ~ChildView();

	static const unsigned interval = 33;	// animation interval in milisecond
	static const unsigned previewTime = 10;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	void init(Space *space, ControlBar *control);
	void setNewMass(double mass);
	void setCreating();

	void clear();
	void setFlag(unsigned flag);

	class Color;

	Color HueToRGB(unsigned int hue);
	Color nextColor();

private:

	CDC mDC;		// 双缓冲DC
	CBitmap mBmp;	// 双缓冲
	CRect mRect;	// 当前客户区域

	Space *pSpace;
	ControlBar *pControl;

	double mTime;
	unsigned mCrtHue;	// 当前色相
	vector<Color> mColors;

	CPoint mOffset, mLastOffset, mFistPoint;

	bool mIsBtnDown;

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


