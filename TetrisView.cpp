
// TetrisView.cpp : CTetrisView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
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
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CTetrisView 생성/소멸

CTetrisView::CTetrisView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CTetrisView::~CTetrisView()
{
	delete mapMng_;
	delete block_;
}

BOOL CTetrisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CTetrisView 그리기

void CTetrisView::OnDraw(CDC* pDC)
{
	CTetrisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CTetrisView 인쇄

BOOL CTetrisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CTetrisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CTetrisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CTetrisView 진단

#ifdef _DEBUG
void CTetrisView::AssertValid() const
{
	CView::AssertValid();
}

void CTetrisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTetrisDoc* CTetrisView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTetrisDoc)));
	return (CTetrisDoc*)m_pDocument;
}
#endif //_DEBUG


// CTetrisView 메시지 처리기


void CTetrisView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
