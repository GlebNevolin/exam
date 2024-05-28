//---------------------------------------------------------------------------

#pragma hdrstop
#include "FS_Factory.h"
#include "FS_Classes.h"
#include "Iterator.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
FsIterator::FsIterator(Base* FileSystem) {
	this->fs = FileSystem;
	this->cluster_buffer = new BYTE[fs->cluster_size];
	//this->cluster_offset.QuadPart = fs->first_cluster_offset;
}

void FsIterator::First() {
	this->current_cluster = 0;
	SetFilePointer(
		this->fs->file_handle,
		0,
		0,
		FILE_BEGIN
	);
}

void FsIterator::Next() {
	SetFilePointer(
		fs->file_handle,
		fs->cluster_size,
		NULL,
		FILE_CURRENT
	);
	this->current_cluster++;
}

BYTE* FsIterator::GetCurrent() {
	fs->getClusterData(
		this->current_cluster,
		this->cluster_buffer
	);

	SetFilePointer(
		this->fs->file_handle,
		-fs->cluster_size,
		NULL,
		FILE_CURRENT
	);

	return this->cluster_buffer;
}

bool FsIterator::IsDone() {
	if (this->current_cluster == fs->cluster_count - 1) {
		return true;
	}
	else {
		return false;
	}
}

FsIterator::~FsIterator() {
	delete[] this->cluster_buffer;
}


FsContainer::FsContainer(const wchar_t* file_path) {
	FsFactory factory(file_path);
	this->fs = factory.getFileSystem();
	fs->getClusterInfo();
}

FsIterator* FsContainer::getIterator() {
	return new FsIterator(
		this-> fs
	);
}

FsContainer::~FsContainer() {
	delete fs;
}