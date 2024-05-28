//---------------------------------------------------------------------------

#ifndef Main_FormH
#define Main_FormH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "VirtualTrees.AncestorVCL.hpp"
#include "VirtualTrees.BaseAncestorVCL.hpp"
#include "VirtualTrees.BaseTree.hpp"
#include "VirtualTrees.hpp"
#include "Decorator.h"
#include "DB_Class.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TComboBox *ComboBox1;
	TLabel *Label1;
	TButton *Button1;
	TComboBox *ComboBox2;
	TLabel *Label2;
	TVirtualStringTree *VirtualStringTree1;
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall VirtualStringTree1GetText(TBaseVirtualTree *Sender, PVirtualNode Node,
          TColumnIndex Column, TVSTTextType TextType, UnicodeString &CellText);

private:	// User declarations
public:		// User declarations
	const wchar_t* Path;
	const wchar_t* Signature;
	const wchar_t* Disk_Letter;
	ULONGLONG ClusterNumber;
	UnicodeString sign;
	UnicodeString lett;
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
typedef struct
{
ULONGLONG id;
UnicodeString Disk_Letter;
UnicodeString File_Extension;
ULONGLONG Cluster_Number;
} NodeStruct;
//---------------------------------------------------------------------------
#endif
