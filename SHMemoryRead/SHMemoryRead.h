
// SHMemoryRead.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSHMemoryReadApp:
// このクラスの実装については、SHMemoryRead.cpp を参照してください
//

class CSHMemoryReadApp : public CWinApp
{
public:
	CSHMemoryReadApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CSHMemoryReadApp theApp;
