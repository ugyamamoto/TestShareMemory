#pragma once
class CMemoryMappedFileManager
{
public:
	CMemoryMappedFileManager(int nSize, LPCTSTR lpName);
	virtual ~CMemoryMappedFileManager();


public:

	bool Create( int nSize ,LPCTSTR lpName);

	void Read(LPVOID lpReadValue);

	void Write();

	void Close();


protected:

	//
	HANDLE m_hShareMemory;

	//
	LPCTSTR m_lpzName;

	//
	int m_nSize;

	//
	LPVOID	m_pMapView;

};

