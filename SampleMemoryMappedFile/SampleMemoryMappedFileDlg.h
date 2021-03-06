
// SampleMemoryMappedFileDlg.h : ヘッダー ファイル
//


//#include "CMemoryMappedFileManager.h"

#pragma once


// CSampleMemoryMappedFileDlg ダイアログ
class CMemoryMappedFileManager;
class CSampleMemoryMappedFileDlg : public CDialogEx
{
// コンストラクション
public:
	CSampleMemoryMappedFileDlg(CWnd* pParent = nullptr);	// 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SAMPLEMEMORYMAPPEDFILE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


	//
	bool Initialize();
	void finalize();

protected:

	//
	CMemoryMappedFileManager*	m_pMemMpFileManger;

private:

	//
	void Clear();


public:
	
	CString m_ctrlEditValue;

	afx_msg void OnBnClickedButtonWrite();
	afx_msg void OnBnClickedButtonRead();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
