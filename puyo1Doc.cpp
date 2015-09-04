// puyo1Doc.cpp : CPuyo1Doc クラスの動作の定義を行います。
//

#include "stdafx.h"
#include "puyo1.h"

#include "puyo1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc

IMPLEMENT_DYNCREATE(CPuyo1Doc, CDocument)

BEGIN_MESSAGE_MAP(CPuyo1Doc, CDocument)
	//{{AFX_MSG_MAP(CPuyo1Doc)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc クラスの構築/消滅

CPuyo1Doc::CPuyo1Doc()
{
	// TODO: この位置に１度だけ呼ばれる構築用のコードを追加してください。

}

CPuyo1Doc::~CPuyo1Doc()
{
}

BOOL CPuyo1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: この位置に再初期化処理を追加してください。
	// (SDI ドキュメントはこのドキュメントを再利用します。)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc シリアライゼーション

void CPuyo1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: この位置に保存用のコードを追加してください。
	}
	else
	{
		// TODO: この位置に読み込み用のコードを追加してください。
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc クラスの診断

#ifdef _DEBUG
void CPuyo1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPuyo1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPuyo1Doc コマンド
