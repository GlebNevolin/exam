//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include <iostream>
#include <string.h>
#include <wchar.h>
#pragma hdrstop
#include "FS_Classes.h"
#include "FS_Factory.h"
#include "Iterator.h"
#include "Decorator.h"
#include "DB_Class.h"
#include "T_DB_Writer.h"
#include "Main_Form.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "VirtualTrees"
#pragma link "VirtualTrees.AncestorVCL"
#pragma link "VirtualTrees.BaseAncestorVCL"
#pragma link "VirtualTrees.BaseTree"
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
auto mask = GetLogicalDrives();
	for (int x = 0; x < 26; x++)
	{
		auto n = ((mask >> x) & 1);
		if (n)
		{
			ComboBox2->Items->Add((char)(65 + x));
		}
		VirtualStringTree1->NodeDataSize = sizeof(NodeStruct);
	}

}
//---------------------------------------------------------------------------
class FS_init : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall FS_init(bool CreateSuspended);
	T_DB_Writer* writer;
	const wchar_t* stable_path;
	/*FsContainer* container;
	FsIterator* iter;
	FsDecorator* decor;*/
};

__fastcall FS_init::FS_init(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	writer = new T_DB_Writer(false);
	/*container = new FsContainer(Path);
	iter = container->getIterator();  //memory corruption example
	decor = new FsDecorator(iter);*/
}
//---------------------------------------------------------------------------
void __fastcall FS_init::Execute()
{
	const wchar_t tmp[] = {
	 *(Form1->Path),
	 *(Form1->Path+1),
	 *(Form1->Path+2),
	 *(Form1->Path+3),
	 *(Form1->Path+4),
	 *(Form1->Path+5),
	 *(Form1->Path+6)};
	stable_path = tmp;
	FsContainer container(stable_path);
	FsIterator* iter = container.getIterator();
	FsDecorator decor(iter);
	/*for (iter->First(); !iter->IsDone(); iter->Next() ) {
		Form1->ClusterNumber = iter->current_cluster;
		writer->DataReady->SetEvent();
		while(writer->DataCopied->WaitFor(INFINITE) != wrSignaled){}
		writer->DataCopied->ResetEvent();
	}*/
	for (decor.First(); !decor.IsDone(); decor.Next()) {
        int a =0;
		if (decor.isFind) {
			Form1->ClusterNumber = decor.current_cluster;
			writer->DataReady->SetEvent();
			while(writer->DataCopied->WaitFor(INFINITE) != wrSignaled){}
			writer->DataCopied->ResetEvent();
		}
	}

	//writer->Terminate();
	//writer->WaitFor();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	if (!ComboBox1->Text.IsEmpty() && !ComboBox2->Text.IsEmpty())
	{
		Form1->sign = Form1->ComboBox1->Text;
		Form1->lett = Form1->ComboBox2->Text;
		Form1->Path = (L"\\\\.\\" + Form1->ComboBox2->Text + L":").c_str();
		FS_init* iter_thread = new FS_init(false);

	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
		  TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText)

{
if (!Node) return;

NodeStruct* nodeData = (NodeStruct*)Sender->GetNodeData(Node);

switch (Column)
{
	case 0: CellText = nodeData->id; break;
	case 1: CellText = nodeData->Disk_Letter; break;
	case 2: CellText = nodeData->File_Extension; break;
	case 3: CellText = nodeData->Cluster_Number; break;
}

}
//---------------------------------------------------------------------------

