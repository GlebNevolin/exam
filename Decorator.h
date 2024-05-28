//---------------------------------------------------------------------------

#ifndef DecoratorH
#define DecoratorH
#pragma once
#include "Iterator.h"
//---------------------------------------------------------------------------


class FsDecorator {
protected:
	FsIterator* It;
	BYTE* buffer;
	BYTE* check_bytes;
	bool isPDF(BYTE* Cluster);
	bool isJPG(BYTE* Cluster);
	bool isPNG(BYTE* Cluster);
public:
	FsDecorator(FsIterator* It);
	UnicodeString type;
	bool isFind;
	ULONGLONG current_cluster;
	void Next();
	void First();
	bool IsDone();
	BYTE* GetCurrent();
	~FsDecorator();
};

#endif
