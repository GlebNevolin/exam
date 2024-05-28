//---------------------------------------------------------------------------

#ifndef FS_ClassesH
#define FS_ClassesH
//---------------------------------------------------------------------------
#pragma once
#include <windows.h>
#include <string>
enum class FileSystem {
	NTFS, EXT4, None
};
//BASE---BASE---BASE---BASE---BASE---BASE---BASE
class Base {

public:
	const int sector_size = 512;
	int cluster_size;
	ULONGLONG cluster_count;
	HANDLE file_handle;
	int first_cluster_offset;
	virtual void getClusterData(
		ULONGLONG cluster_number,
		BYTE* read_buffer
	) = 0;
	virtual int getClusterInfo() = 0;

	Base(const wchar_t* file_path);
	Base() = default;
	virtual ~Base();
};
//NTFS---NTFS---NTFS---NTFS---NTFS---NTFS---NTFS
class NTFS :
    public Base
{
public:

	int getClusterInfo();
    void getClusterData(
        ULONGLONG cluster_number,
        BYTE* read_buffer);

	NTFS(const wchar_t* file_path);
    ~NTFS();
};
//EXT4---EXT4---EXT4---EXT4---EXT4---EXT4---EXT4
class EXT4 :
    public Base
{
public:
    int getClusterInfo();
    void getClusterData(
        ULONGLONG cluster_number,
        BYTE* read_buffer);
    EXT4(const wchar_t* file_path);
    ~EXT4();
};
#endif
