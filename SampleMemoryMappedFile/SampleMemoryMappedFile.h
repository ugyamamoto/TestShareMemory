
// SampleMemoryMappedFile.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSampleMemoryMappedFileApp:
// このクラスの実装については、SampleMemoryMappedFile.cpp を参照してください
//

class CSampleMemoryMappedFileApp : public CWinApp
{
public:
	CSampleMemoryMappedFileApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CSampleMemoryMappedFileApp theApp;
