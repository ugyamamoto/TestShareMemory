
// SHMemWrite.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSHMemWriteApp:
// このクラスの実装については、SHMemWrite.cpp を参照してください
//

class CSHMemWriteApp : public CWinApp
{
public:
	CSHMemWriteApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CSHMemWriteApp theApp;
