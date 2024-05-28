//---------------------------------------------------------------------------

#ifndef T_DB_WriterH
#define T_DB_WriterH
//---------------------------------------------------------------------------
#include "Main_Form.h"
#include <System.Classes.hpp>
//---------------------------------------------------------------------------
class T_DB_Writer : public TThread
{
private:
protected:
	void __fastcall Execute();
public:
	__fastcall T_DB_Writer(bool CreateSuspended);
	void __fastcall treeClear();
	void __fastcall addRow();
	TEvent *DataReady;
	TEvent *DataCopied;
	TEvent *DataWritten;
	ULONGLONG cluster_number;
	const wchar_t* sig;
	const wchar_t* let;
	ULONGLONG i;
};
//---------------------------------------------------------------------------
#endif
