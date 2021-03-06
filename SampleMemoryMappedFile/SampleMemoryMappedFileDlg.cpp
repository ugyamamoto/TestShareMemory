
// SampleMemoryMappedFileDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SampleMemoryMappedFile.h"
#include "SampleMemoryMappedFileDlg.h"
#include "afxdialogex.h"

#include "CMemoryMappedFileManager.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSampleMemoryMappedFileDlg ダイアログ



CSampleMemoryMappedFileDlg::CSampleMemoryMappedFileDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAMPLEMEMORYMAPPEDFILE_DIALOG, pParent)
	, m_ctrlEditValue(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//
	m_pMemMpFileManger = NULL;

	m_ctrlEditValue = _T("");


}

void CSampleMemoryMappedFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ctrlEditValue);
}

BEGIN_MESSAGE_MAP(CSampleMemoryMappedFileDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	
	ON_BN_CLICKED(IDC_BUTTON_WRITE, &CSampleMemoryMappedFileDlg::OnBnClickedButtonWrite)
	ON_BN_CLICKED(IDC_BUTTON_READ, &CSampleMemoryMappedFileDlg::OnBnClickedButtonRead)
	ON_BN_CLICKED(IDOK, &CSampleMemoryMappedFileDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CSampleMemoryMappedFileDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CSampleMemoryMappedFileDlg メッセージ ハンドラー

BOOL CSampleMemoryMappedFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	Initialize();


	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CSampleMemoryMappedFileDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CSampleMemoryMappedFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSampleMemoryMappedFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//初期化
bool CSampleMemoryMappedFileDlg::Initialize() {

	if (m_pMemMpFileManger != NULL) {

		return true;
	}
	
	//
	int nSize = 256;
	LPCTSTR strName = _T("SHMem");


	CMemoryMappedFileManager* pmfm = new CMemoryMappedFileManager(strName,nSize);
	if (!pmfm) {

		return false;
	}
	
	m_pMemMpFileManger = pmfm;

	return true;
}

//終了処理
void CSampleMemoryMappedFileDlg::finalize() {

	//
	delete m_pMemMpFileManger;
	m_pMemMpFileManger = NULL;

}



void CSampleMemoryMappedFileDlg::OnBnClickedButtonWrite()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	if (!m_pMemMpFileManger) {
		return;
	}

	//エディットボックスの値を共有メモリに書き込む
	UpdateData(TRUE);		//エディットボックスに表示されている値を変数にセットする

	MessageBox(m_ctrlEditValue);

	//MapFileView取得	共有メモリに値を書く
	LPVOID lpszValue = m_pMemMpFileManger->GetSHMA();

	//lpszValue = (LPVOID)m_ctrlEditValue.GetBuffer();		//文字列のポインタをわたしてはだめ
															

	//参照先に直接コピーする
	int nSize = m_pMemMpFileManger->getMemSize();
	memcpy_s(lpszValue,									//コピー先のポインタ
			nSize,										//サイズ
			m_ctrlEditValue.GetBuffer(),				//コピー元のポインタ
			nSize);										//サイズ

}


void CSampleMemoryMappedFileDlg::OnBnClickedButtonRead()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	if (!m_pMemMpFileManger) {
		return;
	}

	//
	Clear();

	//共有メモリから値を読んでエディットボックスに表示
	//m_pMemMpFileManger->Read(m_ctrlEditValue.GetBuffer());


	//m_ctrlEditValue = _T("Read");

	LPVOID lpszValue = m_pMemMpFileManger->GetSHMA();

	m_ctrlEditValue = (LPCTSTR)lpszValue;					//ここはいけるのか...

	MessageBox(m_ctrlEditValue);

	UpdateData(FALSE);

}

//Endボタン押下時イベント
void CSampleMemoryMappedFileDlg::OnBnClickedOk()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	finalize();

	CDialogEx::OnOK();
}

//Clearボタン押下イベント
void CSampleMemoryMappedFileDlg::OnBnClickedButton1()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	Clear();
	
}

//Clearボタン押下時処理
void CSampleMemoryMappedFileDlg::Clear() {

	//UpdateData(TRUE);				//エディットボックスに表示されている文字列を変数にセット
	m_ctrlEditValue = _T("");
	UpdateData(FALSE);				//変数にセットされている値をエディットボックスに表示

}