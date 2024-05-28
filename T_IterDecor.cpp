//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop
#include "Main_Form.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall FS_init::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

/*FS_init::FS_init(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	DataReady = new TEvent(NULL, true, false, "", false);
	DataCopied = new TEvent(NULL, true, false, "", false);
	DataWritten = new TEvent(NULL, true, false, "", false);
	writer = new T_DB_Writer(false);

}
//---------------------------------------------------------------------------
void __fastcall FS_init::Execute()
{



	writer->Terminate();
	writer->WaitFor();
}*/
//---------------------------------------------------------------------------
