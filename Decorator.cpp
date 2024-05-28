//---------------------------------------------------------------------------

#pragma hdrstop

#include "Decorator.h"
#include "Main_Form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
 FsDecorator::FsDecorator(
	FsIterator* It
) {
	this->It = It;
	this->type = Form1->ComboBox1->Text;

}

FsDecorator::~FsDecorator() {

}

void FsDecorator::First() {
	It->First();
}

bool FsDecorator::IsDone() {
	return It->IsDone();
}

BYTE* FsDecorator::GetCurrent() {
	return It->GetCurrent();
}

bool FsDecorator::isPDF(BYTE* Cluster)
{
	BYTE pdf[5]{ 0x25, 0x50, 0x44, 0x46, 0x2d };
	for (int i = 0; i < 5; i++)
		if (pdf[i] != Cluster[i]) {
			return false;
		}
	return true;
}

bool FsDecorator::isJPG(BYTE* Cluster)
{
	BYTE jpg[4]{ 0xff, 0xd8, 0xff, 0xee };
	for (int i = 0; i < 4; i++)
		if (jpg[i] != Cluster[i]) {
			return false;
		}
	return true;
}

bool FsDecorator::isPNG(BYTE* Cluster)
{
	BYTE png[8]{ 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };
	for (int i = 0; i < 8; i++)
		if (png[i] != Cluster[i]) {
			return false;
		}
	return true;
}


void FsDecorator::Next() {
UnicodeString pdf = u"PDF";
UnicodeString jpg = u"JPG";
UnicodeString png = u"PNG";
	if (this->type == pdf) {
		for (; !It->IsDone(); It->Next()) {
			this->buffer = It->GetCurrent();
            this->current_cluster = It->current_cluster;
			if (isPDF(this->buffer)) {
				//this->current_cluster = It->current_cluster;
				this->isFind = true;
				break;
			}
		}
	}
	else if (this->type == jpg) {
		for (; !It->IsDone(); It->Next()) {
			this->buffer = It->GetCurrent();
			this->current_cluster = It->current_cluster;
			if (isJPG(this->buffer)) {
				//this->current_cluster = It->current_cluster;
				this->isFind = true;
				break;
			}
		}
	}
	else if (this->type == png) {
		for (; !It->IsDone(); It->Next()) {
			this->buffer = It->GetCurrent();
			this->current_cluster = It->current_cluster;
			if (isPNG(this->buffer)) {
				//this->current_cluster = It->current_cluster;
				this->isFind = true;
				break;
			}
		}
	}
	It->Next();


}