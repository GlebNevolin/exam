//---------------------------------------------------------------------------

#include <System.hpp>
#pragma hdrstop

#include "T_DB_Writer.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(&UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall T_DB_Writer::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------
class DataWriter {
public:
	sqlite3* db;
	DataWriter() {
		int con_db = sqlite3_open("BAZA.sqlite3", &db);
		sqlite3_stmt* pStatement;
		const char* sql = "CREATE TABLE IF NOT EXISTS clusters (number INTEGER, signature TEXT, disk TEXT)";
		sqlite3_exec(db, sql, NULL, NULL, NULL);
	};

	void insertData(ULONGLONG cluster_number, const wchar_t* signature, const wchar_t* L) {
		sqlite3_stmt* pStatement;

		const char* sql = "INSERT INTO clusters VALUES (?, ?, ?)";

		int execResult = sqlite3_prepare_v2(
			db,
			sql,
			-1,
			&pStatement,
			NULL
		);

		sqlite3_bind_int64(pStatement, 1, cluster_number);
		sqlite3_bind_text16(pStatement, 2, signature, -1, SQLITE_TRANSIENT);
		sqlite3_bind_text16(pStatement, 3, L, -1, SQLITE_TRANSIENT);
		sqlite3_step(pStatement);
		sqlite3_finalize(pStatement);

	}

	void selectData() {
		sqlite3_stmt* pStatement;

		const char* sql = "SELECT * FROM clusters";
		int execResult = sqlite3_prepare_v2(
			db,
			sql,
			-1,
			&pStatement,
			NULL
		);

		int execResultStep = sqlite3_step(pStatement);
		int id = sqlite3_column_int(pStatement, 0);
		ULONGLONG cluster_number = sqlite3_column_int64(pStatement, 1);
		const void* signature = sqlite3_column_text16(pStatement, 2);
		const void* L = sqlite3_column_text16(pStatement, 3);
		sqlite3_free((void *)signature);
		sqlite3_free((void *)L);
		sqlite3_finalize(pStatement);


	}

	void closeConnection() {
		sqlite3_close(db);
	}

	~DataWriter() {

	}
};
__fastcall T_DB_Writer::T_DB_Writer(bool CreateSuspended)
	: TThread(CreateSuspended)
{
	FreeOnTerminate = true;
	DataReady = new TEvent(NULL, true, false, "", false);
	DataCopied = new TEvent(NULL, true, false, "", false);
	DataWritten = new TEvent(NULL, true, false, "", false);
}
//---------------------------------------------------------------------------
void __fastcall T_DB_Writer::Execute()
{
Synchronize(treeClear);
DataWriter db;
DataCopied->ResetEvent();
sig = Form1->sign.c_str();
let = Form1->lett.c_str();
i = 0;
//const wchar_t* a = Form1->Signature;
//const wchar_t* b = Form1->Disk_Letter;
while(!Terminated)
{
	if(DataReady->WaitFor(INFINITE) == wrSignaled)
	{
		i++;
		Synchronize(addRow);
		DataReady->ResetEvent();
		cluster_number = Form1->ClusterNumber;
		DataCopied->SetEvent();
		db.insertData(cluster_number, sig, let);
	}
}
}
//---------------------------------------------------------------------------
void __fastcall T_DB_Writer::treeClear()
{
Form1->VirtualStringTree1->Clear();
}

void __fastcall T_DB_Writer::addRow()
{
PVirtualNode entryNode = Form1->VirtualStringTree1->AddChild(Form1->VirtualStringTree1->RootNode);
NodeStruct* nodeData = (NodeStruct*)Form1->VirtualStringTree1->GetNodeData(entryNode);
nodeData->id = i;
nodeData->Cluster_Number = Form1->ClusterNumber;
nodeData->Disk_Letter = Form1->lett;
nodeData->File_Extension = Form1->sign;

}
