
// TetrisView.h : CTetrisView Ŭ������ �������̽�
//

#pragma once

#include "Block.h"
#include "MapManager.h"
#include "TetrisDoc.h"
#define MY_TIMER 1000
using namespace std;

class CTetrisView : public CView
{
private:
	MapManager* mapMng_;
	Block* block_;
	blockRect drawBlocks_;
protected: // serialization������ ��������ϴ�.
	CTetrisView();
	DECLARE_DYNCREATE(CTetrisView)

// Ư���Դϴ�.
public:
	CTetrisDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CTetrisView();
	BOOL RemoveBlockAndCallPaint(blockRect, bool);
	void UpdateMapView(blockRect&);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // TetrisView.cpp�� ����� ����
inline CTetrisDoc* CTetrisView::GetDocument() const
   { return reinterpret_cast<CTetrisDoc*>(m_pDocument); }
#endif

