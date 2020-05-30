#include "stdafx.h"
#include "CMemoryMappedFileManager.h"

//�R���X�g���N�^
CMemoryMappedFileManager::CMemoryMappedFileManager(int nSize, LPCTSTR lpName)
{
	//
	m_hShareMemory = NULL;
	//
	m_lpzName = _T("");

	//
	Create(nSize,lpName);

}

//�f�X�g���N�^
CMemoryMappedFileManager::~CMemoryMappedFileManager()
{

	Close();

}

//���L����������
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

		//�˂Ȃ���΍��
		if (!Create(m_nSize, m_lpzName)) {

			//�ˎ��s
			return;
		}

	}

	//���L����������l�擾
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

//�j��
void CMemoryMappedFileManager::Close()
{
	
	//
	UnmapViewOfFile(m_pMapView);
	
	m_pMapView = NULL;

	//
	CloseHandle(m_hShareMemory);

	m_hShareMemory = NULL;

}