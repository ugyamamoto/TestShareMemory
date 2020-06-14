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
	//�t�@�C���}�b�v�h�I�u�W�F�N�g�i���L���ꂽ�������̈�Ɋ��蓖�Ă�ꂽ�ϐ��j
	//��n���΂���
	LPVOID Open();
	//
	void Read(LPVOID lpReadValue);
	//���ɂ�������ɂ��Ă��A�����̓|�C���^�łȂ��Ă���
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

