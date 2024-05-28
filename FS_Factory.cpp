//---------------------------------------------------------------------------

#pragma hdrstop

#include "FS_Factory.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

FsFactory::FsFactory(const wchar_t* file_path)  {

		file_path_inf = file_path;

		file_handle = CreateFileW(
		file_path_inf,
		GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
	);

}

FsFactory::~FsFactory() {
	CloseHandle(file_handle);
}

FileSystem FsFactory::detectFileSystem() {
#pragma pack(push, 1)
	struct BootStruct {
		BYTE jump1[3];
		UINT32 NTFS;
		BYTE jump2[15];
		UINT16 FAT_detect;
		BYTE jump3[486];
		UINT16 FAT;
		BYTE jump4[568];
		UINT16 EXT4;
	};
#pragma pack(pop)

	BYTE* buffer = new BYTE[1536];

	SetFilePointer(
		file_handle,
		0,
		0,
		FILE_BEGIN
	);

	ReadFile(
		file_handle,
		buffer,
		1536,
		0,
		NULL);


	BootStruct* boot_st = new BootStruct;
	boot_st = (BootStruct*)buffer;

	if (boot_st->NTFS == 0x5346544E)  // 0x5346544E 0x4E544653
	{
		return FileSystem::NTFS;
	}
	else if (boot_st->EXT4 == 0xEF53) // 0x53EF 0xEF53
	{
		return FileSystem::EXT4;
	}
	else {
		return FileSystem::None;
	}
	delete boot_st;

}


Base* FsFactory::getFileSystem() {
	switch (
		this->detectFileSystem()
		)
	{
	case FileSystem::NTFS:
		return new NTFS(
			file_path_inf
		);
	case FileSystem::EXT4:
		return new EXT4(
			file_path_inf
	);
	case FileSystem::None: return NULL;
	}
}