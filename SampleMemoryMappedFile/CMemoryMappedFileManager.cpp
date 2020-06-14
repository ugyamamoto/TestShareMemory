#include "stdafx.h"
#include "CMemoryMappedFileManager.h"

//コンストラクタ
CMemoryMappedFileManager::CMemoryMappedFileManager(LPCTSTR lpName,int nSize /* = 16 * 1024*/)
{
	//
	m_hShareMemory = NULL;
	//
	m_lpzName = _T("");

	//Create File MappingObject and get a view of file
	open(lpName,nSize);

}

//デストラクタ
CMemoryMappedFileManager::~CMemoryMappedFileManager()
{
	if (!isClose())
	{
		Close();
	}
}

//共有メモリ生成
HANDLE CMemoryMappedFileManager::Create( int nSize , LPCTSTR lpName) {

	HANDLE hFm = NULL;
	for (;;) {

		if (m_hShareMemory != NULL || lpName == _T("")) {

			break;
		}

		//
		m_lpzName = lpName;
		m_nSize = nSize;
		
		//
		hFm = CreateFileMapping(INVALID_HANDLE_VALUE,	// use paging file 
								NULL,					// default security
								PAGE_READWRITE,			// read/write access
								NULL, 					// maximum object size (high-order DWORD)
								nSize, 					// maximum object size (low-order DWORD)
								lpName					// name of mapping object
								);						
		if (!hFm) {

			//Fail to Createfilemapping Object?
			_tprintf(TEXT("Could not create file mapping object (%d).\n"),
				GetLastError());
			break;
		}

		m_hShareMemory = hFm;

		break;
	}

	return hFm;

}

bool CMemoryMappedFileManager::open(LPCTSTR lpName, int nSize /*16*1024*/) {


	//close if already opened.
	Close();

	//Create File Mapping Object
	if ( !Create(nSize, lpName) ) {

		return false;

	}

	//Get the view of file
	LPVOID pBuf = MapViewOfFile(m_hShareMemory,			//handle to the map object 
								FILE_MAP_ALL_ACCESS,	//read/write permission
								0,					
								0,					
								m_nSize);				
	if (pBuf == NULL) {

		_tprintf(TEXT("Could not map view of file (%d).\n"),
			GetLastError());

		//
		Close();

		return false;

	}

	m_pMapView = pBuf;

	return true;

}

//Has Opened?
bool CMemoryMappedFileManager::IsOpen() {

	//
	return (m_hShareMemory != NULL && m_pMapView != NULL);
	
}

//Closed?
bool CMemoryMappedFileManager::isClose() {

	return(m_hShareMemory == NULL && m_pMapView == NULL);

}

//Get Shared Memory Access(Access of file view)
LPVOID CMemoryMappedFileManager::GetSHMA() {

	LPVOID pFV = NULL;

	for (;;) {

		if (!IsOpen()) {
			
			break;
		}


		pFV = m_pMapView;

		break;

	}

	return pFV;
}


void CMemoryMappedFileManager::Read(LPVOID lpReadValue) {

	//HANDLE = OpenMappedFile?
	if (!m_hShareMemory) {

		//⇒なければ作る
		if (!Create(m_nSize, m_lpzName)) {

			//⇒失敗
			return;
		}

	}

	//共有メモリから値取得
	if (m_pMapView != NULL) {

			

	}
	
	LPCTSTR pBuf = (LPTSTR)MapViewOfFile(m_hShareMemory,FILE_MAP_ALL_ACCESS,NULL,NULL,m_nSize);
	if (pBuf != NULL) {

		//m_pMapView = pBuf;

	}

	//memcpy_s(&pBuf,lpReadValue,sizeof(lpReadValue));


}

void CMemoryMappedFileManager::Write(LPVOID lpReadValue) {

	LPCSTR pszVal = (LPCSTR)lpReadValue;

	if (!m_hShareMemory) {

		return;

	}
	
	//Open
	HANDLE hMap = OpenFileMapping(FILE_MAP_ALL_ACCESS,FALSE,m_lpzName);
	if (!hMap) {
		//Error
		return;

	}


	LPCTSTR pBuf = (LPTSTR)MapViewOfFile(hMap,FILE_MAP_ALL_ACCESS,0,0,m_nSize);
	if (!pBuf) {
		//Error
		return;

	}

	



	//CopyMemory((PVOID)pBuf, pszVal, (_tcslen(pszVal) * sizeof(TCHAR));

	//
	UnmapViewOfFile(pBuf);


}

//破棄
bool CMemoryMappedFileManager::Close()
{
	//
	if (m_pMapView != NULL) {
		
		UnmapViewOfFile(m_pMapView);
		m_pMapView = NULL;

	}

	//
	if (m_hShareMemory != NULL) {
		
		CloseHandle(m_hShareMemory);
		m_hShareMemory = NULL;

	}

	return (m_pMapView == NULL && m_hShareMemory == NULL);

}