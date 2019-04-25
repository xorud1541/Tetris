
// TetrisView.cpp : CTetrisView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
#ifndef SHARED_HANDLERS
#include "Tetris.h"
#endif

#include "TetrisDoc.h"
#include "TetrisView.h"
#include "MapManager.h"
#include "Block.h"
#include "GameInfo.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTetrisView

IMPLEMENT_DYNCREATE(CTetrisView, CView)

BEGIN_MESSAGE_MAP(CTetrisView, CView)
	// ǥ�� �μ� ����Դϴ�.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTetrisView ����/�Ҹ�

CTetrisView::CTetrisView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CTetrisView::~CTetrisView()
{
	delete mapMng_;
	delete block_;
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CTetrisView �׸���

void CTetrisView::OnDraw(CDC* pDC)
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
}


// CTetrisView �μ�

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
}


// CTetrisView ����

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView �޽��� ó����


void CTetrisView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	mapMng_ = new MapManager();
	block_ = new Block();
	
	block_->MakeFirstBlock();
	block_->SetMap(mapMng_->GetMapState());
	drawBlocks_ = block_->GetCurrentBlock();
	mapMng_->SetBlockToMap(drawBlocks_);
	if(RemoveBlockAndCallPaint(drawBlocks_, true)){
		SetTimer(MY_TIMER, 100, 0);
	}
}

BOOL CTetrisView::RemoveBlockAndCallPaint(blockRect blocks, bool erase){
	int x = mapping(blocks.startX);
	int y = mapping(blocks.startY);
	InvalidateRect(CRect(x, y, x + BLOCKWIDTH, y + BLOCKWIDTH), erase); 
	
	return TRUE;
}

void CTetrisView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	
	for(int i=0; i<4; i++){
		for(int j=0; j<4; j++){
			int x = i + drawBlocks_.startX;
			int y = j + drawBlocks_.startY;

			if(x < 0 || x >= WIDTH_IDX) continue;
			int __startX = mapping(i + drawBlocks_.startX);
			int __startY = mapping(j + drawBlocks_.startY);

			if(mapMng_->GetMapState()[x][y] == -1){
				dc.FillSolidRect(CRect(__startX, __startY, 
				    __startX + PARTICLE, __startY + PARTICLE), RGB(188, 180, 178));
			}
			else if(mapMng_->GetMapState()[x][y] == 1){
				dc.FillSolidRect(CRect(__startX, __startY, 
					__startX + PARTICLE, __startY + PARTICLE), RGB(0, 255, 0));
			}
		}
	}

}

void CTetrisView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(nIDEvent == MY_TIMER){
		blockRect currentRect = block_->GetCurrentBlock();
		int ret = block_->DownBlocks();
		if(ret == KEEP){
			blockRect nextRect = block_->GetNextBlock();

			mapMng_->DeleteBlock(currentRect);
			mapMng_->SetBlockToMap(nextRect);
			drawBlocks_ = nextRect;
			if(RemoveBlockAndCallPaint(currentRect, true)){
				block_->UpdateCurrentBlocks(); // current <- next
			}
		}
		else if(ret == OUT){

		}
		else{
			mapMng_->AddBlockToMap(currentRect);
			drawBlocks_ = currentRect;
			if(RemoveBlockAndCallPaint(currentRect, true)){
				mapMng_->SetBlockToMap(block_->MakeFirstBlock());
			}
		}
	}
	CView::OnTimer(nIDEvent);
}



void CTetrisView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	blockRect currentRect = block_->GetCurrentBlock();
	if(nChar == VK_LEFT){
		int ret = block_->LeftBlocks();
		if(ret == KEEP){
			blockRect nextRect = block_->GetNextBlock();

			mapMng_->DeleteBlock(currentRect);
			mapMng_->SetBlockToMap(nextRect);
			drawBlocks_ = nextRect;
			if(RemoveBlockAndCallPaint(currentRect, true)){
				block_->UpdateCurrentBlocks(); // current <- next
			}
		}
		else if(ret == OUT){

		}
		else {
			mapMng_->AddBlockToMap(currentRect);
			drawBlocks_ = currentRect;
			if(RemoveBlockAndCallPaint(currentRect, true)){
				mapMng_->SetBlockToMap(block_->MakeFirstBlock());
			}
		}
	}
	else if(nChar == VK_RIGHT){
		int ret = block_->RightBlocks();
		if(ret == KEEP){
			blockRect nextRect = block_->GetNextBlock();

			mapMng_->DeleteBlock(currentRect);
			mapMng_->SetBlockToMap(nextRect);
			drawBlocks_ = nextRect;
			if(RemoveBlockAndCallPaint(currentRect, true)){
				block_->UpdateCurrentBlocks(); // current <- next
			}
		}
		else if(ret == OUT){

		}
		else {
			mapMng_->AddBlockToMap(currentRect);
			drawBlocks_ = currentRect;
			if(RemoveBlockAndCallPaint(currentRect, true)){
				mapMng_->SetBlockToMap(block_->MakeFirstBlock());
			}
		}
	}
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
