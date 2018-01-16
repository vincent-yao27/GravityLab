/************

GravityLab
ChildView.cpp

Author: Vincent_Yao27@163.com

Copyright (c) 2017 Vincent Yao (姚裕欣).

Released under GPL-3.0 license

************/

#include "stdafx.h"
#include "GravityLab.h"
#include "ChildView.h"

// ChildView

IMPLEMENT_DYNAMIC(ChildView, CWnd)

ChildView::ChildView() : mTime(0), mCrtHue(0), mIsBtnDown(false) { }

ChildView::~ChildView()
{
	mDC.DeleteDC();
	mBmp.DeleteObject();
}

class ChildView::Color {
public:
	unsigned char r, g, b;

	Color() {}
	Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b) {}

	COLORREF scaleAndColorRef(float k) {
		return RGB(r*k, g*k, b*k);
	}

	COLORREF colorRef() {
		return RGB(r, g, b);
	}
};

void ChildView::init(Space *space, ControlBar *control) {
	pSpace = space;
	pControl = control;
}

void ChildView::clear() {
	pSpace->clear();
	mColors.clear();
	mCrtHue = 0;
	mTime = 0;
	mOffset.SetPoint(0, 0);
}

void ChildView::setFlag(unsigned flag) {
	static int randCnt = 0;

	if (flag & SPACE_FLAG_CLEAR) {
		clear();
	} else if (flag & SPACE_FLAG_RESET) {
		pSpace->reset();
//		pSpace->init();
		pSpace->simulate(previewTime);
		mTime = 0;
		mOffset.SetPoint(0, 0);
	} else if (flag & SPACE_FLAG_RANDOM) {
		clear();

		randCnt = ++randCnt % 4;

		switch (randCnt) {
		case 1:
			pSpace->newEntity(Vector2d(300, 300), Vector2d(-2.5, 0), 8e6);
			pSpace->newEntity(Vector2d(300, 100), Vector2d(200, 0), 1e5);
			pSpace->newEntity(Vector2d(275, 100), Vector2d(200, 50));
			pSpace->newEntity(Vector2d(250, 300), Vector2d(0, 540));
	
			pSpace->simulate(previewTime);
	
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			break;
		case 3:
			pSpace->newEntity(Vector2d(300, 300), Vector2d(-100, 0), 1e6);
			pSpace->newEntity(Vector2d(300, 150), Vector2d(20, 0), 1e6);
			pSpace->newEntity(Vector2d(300, 450), Vector2d(80, 0), 1e6);
	
			pSpace->simulate(previewTime);
	
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			break;
		case 0:
		case 2:
			pSpace->newEntity(Vector2d(300, 300), Vector2d(-100, 0), 1e6);
			pSpace->newEntity(Vector2d(300, 150), Vector2d(20, 0), 1e6);
			pSpace->newEntity(Vector2d(300, 450), Vector2d(80, 0), 1e6);
			pSpace->newEntity(Vector2d(300, 105), Vector2d(rand() % 25 + 150, 0));
	
			pSpace->simulate(previewTime);
	
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			mColors.push_back(nextColor());
			break;
		}
	}
}

ChildView::Color ChildView::HueToRGB(unsigned int hue) {
	Color c;

	float f = hue / 60.0f - hue / 60;
	
	switch ((hue / 60) % 6) {
	case 0:
		c = Color(191, round(191 * f), 0);
		break;
	case 1:
		c = Color(round(191 * (1 - f)), 191, 0);
		break;
	case 2:
		c = Color(0, 191, round(191 * f));
		break;
	case 3:
		c = Color(0, round(191 * (1 - f)), 191);
		break;
	case 4:
		c = Color(round(191 * f), 0, 191);
		break;
	case 5:
		c = Color(191, 0, round(191 * (1 - f)));
		break;
	}

	c.r += 64;
	c.g += 64;
	c.b += 64;

	return c;
}

ChildView::Color ChildView::nextColor() {
	Color c = HueToRGB(mCrtHue);
	mCrtHue += 133;
	return c;
}

BEGIN_MESSAGE_MAP(ChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()

// ChildView 消息处理程序

void ChildView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	CRect rect;
	GetClientRect(&rect);

	if (rect != mRect) {
		mRect = rect;

		mDC.DeleteDC();
		mBmp.DeleteObject();

		mDC.CreateCompatibleDC(&dc);
		mBmp.CreateCompatibleBitmap(&dc, mRect.Width(), mRect.Height());

		mDC.SelectObject(&mBmp);
	}

	mDC.FillSolidRect(rect, RGB(0, 0, 0));
	
	for (int i = 0; i < pSpace->getEntities().size(); i++) {

		const Entity &e = (pSpace->getEntities())[i];

		if (e.isNoTrack()) continue;

		// 将来的轨迹，虚线
		CPen pen1(PS_DOT, 1, mColors[i].scaleAndColorRef(0.8));
		mDC.SelectObject(&pen1);

		mDC.MoveTo(CPoint(e.getPosition(int(mTime)).x, e.getPosition(int(mTime)).y) + mOffset);
	
		for (double crt = int(mTime); crt < mTime + previewTime; crt += interval * 0.001) {
			mDC.LineTo(CPoint(e.getPosition(crt).x, e.getPosition(crt).y) + mOffset);
		}

		// 经过的轨迹，实线
		CPen pen2(PS_SOLID, 1, mColors[i].scaleAndColorRef(0.7));
		mDC.SelectObject(&pen2);

		mDC.MoveTo(CPoint(e.getPosition(0).x, e.getPosition(0).y) + mOffset);
	
		for (double crt = 0; crt < mTime; crt += interval * 0.001) {
			mDC.LineTo(CPoint(e.getPosition(crt).x, e.getPosition(crt).y) + mOffset);
		}

		// 画entity本身
		CBrush brush(mColors[i].colorRef());
		mDC.SelectObject(&brush);
		
		const Vector2d &t = e.getPosition(mTime);
		int radius = log(e.getMass() + 5e3);
		mDC.Ellipse(CRect(t.x - radius, t.y - radius, t.x + radius, t.y + radius) + mOffset);
	}

	/*
	for (int i = 0; i < 360; i++) {
		mDC.SetPixel(100 + i, 100, HueToRGB(i).colorRef());
	}
	*/

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &mDC, 0, 0, SRCCOPY);

	if (pControl->isPlaying()) {
		double elapse = interval * 0.001 * pControl->getSpeed();
		pSpace->simulate(elapse);
		mTime += elapse;
	}
}


BOOL ChildView::OnEraseBkgnd(CDC* pDC)
{
	return FALSE/* CWnd::OnEraseBkgnd(pDC) */;
}


void ChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	mIsBtnDown = true;

	if (pControl->isCreating()) {
		pSpace->newEntity(Vector2d(point.x - mOffset.x, point.y - mOffset.y), Vector2d(), pControl->getMass());

		mColors.push_back(nextColor());

		pSpace->simulate(previewTime);
		mTime = 0;
	}

	mFistPoint = point;
	mLastOffset = mOffset;

	CWnd::OnLButtonDown(nFlags, point);
}


void ChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if (mIsBtnDown) {

		if (pControl->isCreating()) {
			Entity &e = pSpace->modifyLastEntity();
			Vector2d v(point.x - mOffset.x, point.y - mOffset.y);
			e.setVelocity(v - e.getPosition());

//			pSpace->init();
			pSpace->simulate(previewTime);
			mTime = 0;
		} else {
			mOffset = mLastOffset + point - mFistPoint;
		}

	}

	CWnd::OnMouseMove(nFlags, point);
}


void ChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	mIsBtnDown = false;
	pControl->isCreating(false);

	CWnd::OnLButtonUp(nFlags, point);
}
