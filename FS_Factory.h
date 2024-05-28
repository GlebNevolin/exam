//---------------------------------------------------------------------------

#ifndef FS_FactoryH
#define FS_FactoryH
//---------------------------------------------------------------------------
#pragma once
#include "FS_Classes.h"
class FsFactory {
protected:
	//BYTE* buffer;




public:
	HANDLE file_handle;
	const wchar_t* file_path_inf;
    FileSystem detectFileSystem();
	Base* getFileSystem();

	FsFactory(const wchar_t* file_path) ;
	FsFactory() = default;
	~FsFactory();

};
#endif

