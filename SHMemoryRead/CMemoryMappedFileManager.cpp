#include "stdafx.h"
#include "CMemoryMappedFileManager.h"

//コンストラクタ
CMemoryMappedFileManager::CMemoryMappedFileManager(int nSize, LPCTSTR lpName)
{
	//
	m_hShareMemory = NULL;
	//
	m_lpzName = _T("");

	//
	Create(nSize,lpName);

}

//デストラクタ
CMemoryMappedFileManager::~CMemoryMappedFileManager()
{

	Close();

}

//共有メモリ生成
bool CMemoryMappedFileManager::Create( int nSize , LPCTSTR lpName) {

	if ( m_hShareMemory != NULL || lpName == _T("") ) {

		return false;

	}

	//
	m_lpzName = lpName;
	m_nSize = nSize;

	HANDLE hHandle = CreateFileMapping(NULL, NULL, PAGE_READWRITE, NULL, nSize, lpName);
	if (!hHandle) {

		//Fail to Createfilemapping Object?
		return false;
	}

	m_hShareMemory = hHandle;

	return true;

}

void CMemoryMappedFileManager::Read(LPVOID lpReadValue) {

	
	if (!m_hShareMemory) {

		//⇒なければ作る
		if (!Create(m_nSize, m_lpzName)) {

			//⇒失敗
			return;
		}

	}

	//共有メモリから値取得
	lpReadValue = (int*)MapViewOfFile(m_hShareMemory,FILE_MAP_ALL_ACCESS,NULL,NULL,m_nSize);
	if (lpReadValue != NULL) {

		m_pMapView = lpReadValue;
	}

}

void CMemoryMappedFileManager::Write() {

	if (!m_hShareMemory) {

		return;

	}
	


}

//破棄
void CMemoryMappedFileManager::Close()
{
	
	//
	UnmapViewOfFile(m_pMapView);
	
	m_pMapView = NULL;

	//
	CloseHandle(m_hShareMemory);

	m_hShareMemory = NULL;

}