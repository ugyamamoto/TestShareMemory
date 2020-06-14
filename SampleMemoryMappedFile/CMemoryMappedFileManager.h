#pragma once
class CMemoryMappedFileManager
{
public:
	CMemoryMappedFileManager(LPCTSTR lpName, int nSize = 16 * 1024);
	virtual ~CMemoryMappedFileManager();


public:


	//Opened?
	bool IsOpen();

	//
	HANDLE Create( int nSize ,LPCTSTR lpName);

	//
	bool Close();

	//
	LPVOID GetSHMA();

	
	//
	int getMemSize()
	{
		return m_nSize;
	}

	//***************************************************************************
	//ファイルマップドオブジェクト（共有されたメモリ領域に割り当てられた変数）
	//を渡せばいい
	LPVOID Open();
	//
	void Read(LPVOID lpReadValue);
	//仮にこうするにしても、引数はポインタでなくていい
	void Write(LPVOID lpReadValue);


protected:

	//
	bool open(LPCTSTR lpName, int nSize = 16 * 1024);
	//
	//bool isOpen();
	bool isClose();


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

