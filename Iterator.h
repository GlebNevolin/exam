//---------------------------------------------------------------------------

#ifndef IteratorH
#define IteratorH
#include "FS_Factory.h"
#include "FS_Classes.h"
//---------------------------------------------------------------------------
class FsIterator {
public:
	Base* fs;
	BYTE* cluster_buffer;
	ULONGLONG current_cluster;
	LARGE_INTEGER cluster_offset;
	FsIterator(Base* FileSystem);
	void Next();
	void First();
	bool IsDone();
	BYTE* GetCurrent();
	FsIterator() = default;
	~FsIterator();
};

class FsContainer {
public:
	Base* fs;
	FsContainer(const wchar_t* file_path);
	FsIterator* getIterator();
	~FsContainer();
};
#endif
