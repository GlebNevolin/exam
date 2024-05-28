//---------------------------------------------------------------------------

#pragma hdrstop
#include "iostream"
#include "FS_Classes.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//BASE---BASE---BASE---BASE---BASE---BASE---BASE
Base::Base(const wchar_t* file_path) {


	this->file_handle = CreateFileW(
		file_path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);


	if (file_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Can't open file with error code: " << GetLastError() << '\n';
		this->file_handle = NULL;
	}

}

Base::~Base() {
	CloseHandle(file_handle);
}
//NTFS---NTFS---NTFS---NTFS---NTFS---NTFS---NTFS
int NTFS::getClusterInfo() {
	DWORD lowerCase = SetFilePointer(file_handle, 0, 0, FILE_BEGIN);
	BYTE* read_buffer = new BYTE[sector_size];
	bool k = ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);
#pragma pack(push,1)
	struct BootRecord
	{
		BYTE jump[13];
		UINT8 cluster_multiplier;
		BYTE jump2[26];
		UINT64 total_sectors;
	};
#pragma pack(pop)
	BootRecord* parse = new BootRecord;
	parse = (BootRecord*)read_buffer;
	cluster_size = sector_size * parse->cluster_multiplier;
	cluster_count = (parse->total_sectors++)/parse->cluster_multiplier;
	return 0;
}
void NTFS::getClusterData(
	ULONGLONG cluster_number,
	BYTE* read_buffer)
{
	ULONGLONG startOffset = cluster_number * cluster_size;
	LARGE_INTEGER sectorOffset{0};
	sectorOffset.QuadPart = startOffset;

	DWORD lowerCase = SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
	bool k = ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
}
NTFS::NTFS(const wchar_t* file_path)
{
	cluster_size = NULL;
	file_handle = CreateFileW(
		file_path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (file_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Can't open file with error code: " << GetLastError() << '\n';
		file_handle = NULL;
	}
	this->getClusterInfo();
}
NTFS::~NTFS()
{

}
//EXT4---EXT4---EXT4---EXT4---EXT4---EXT4---EXT4
int EXT4::getClusterInfo() {
	SetFilePointer(file_handle, 1024, 0, FILE_BEGIN);
	BYTE* read_buffer = new BYTE[sector_size];
	ReadFile(file_handle, read_buffer, sector_size, NULL, NULL);

#pragma pack(push, 1)
	struct EXT4_BOOT_REC {
		BYTE jump1[0x4];
		UINT32 block_count;
		BYTE jump2[0x10];
		UINT32 LB_power;
	};
#pragma pack(pop)

	EXT4_BOOT_REC* A = new EXT4_BOOT_REC;
	A = (EXT4_BOOT_REC*)read_buffer;

	this->cluster_count = A->block_count;
	this->cluster_size = (int)std::pow(2, (10 + A->LB_power));

	delete A;
	return 0;
}
void EXT4::getClusterData(
	ULONGLONG cluster_number,
	BYTE* read_buffer)
{
	unsigned __int64 startOffset = static_cast<unsigned long long>(cluster_number) * cluster_size;
	LARGE_INTEGER sectorOffset{};
	sectorOffset.QuadPart = startOffset;

	SetFilePointer(file_handle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
	ReadFile(file_handle, read_buffer, cluster_size, NULL, NULL);
}
EXT4::EXT4(const wchar_t* file_path)
{
	this->cluster_size = NULL;
	this->file_handle = CreateFileW(
		file_path,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL);
	if (this->file_handle == INVALID_HANDLE_VALUE)
	{
		std::cout << "Can't open file with error code: " << GetLastError() << '\n';
		this->file_handle = NULL;
	}
	this->getClusterInfo();
}
EXT4::~EXT4()
{

}
