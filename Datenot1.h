//---------------------------------------------------------------------------
#ifndef Datenot1H
#define Datenot1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <Dialogs.hpp>

// Мои дополнения
#include <Filectrl.hpp>
#include <Buttons.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TDateTimePicker *DateTimePicker1;
        TMemo *Memo1;
        TSpeedButton *SpeedButton1;
        TSpeedButton *SpeedButton2;
        TSpeedButton *SpeedButton3;
        TTimer *Timer1;
        TSpeedButton *SpeedButton4;
        void __fastcall DateTimePicker1CloseUp(TObject *Sender);
        void __fastcall DateTimePicker1DropDown(TObject *Sender);
        void __fastcall FormCloseQuery(TObject *Sender, bool &CanClose);
        void __fastcall Memo1KeyDown(TObject *Sender, WORD &Key,
                                     TShiftState Shift);
        void __fastcall SpeedButton1Click(TObject *Sender);
        void __fastcall SpeedButton2Click(TObject *Sender);
        void __fastcall SpeedButton3Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SpeedButton4Click(TObject *Sender);
        void __fastcall FormActivate(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// Мои объявления - User declarations
        bool TextChange;
        AnsiString fName;
        Graphics::TBitmap *sbImage1, *sbImage2, *sbImage3, *sbImage4;

        AnsiString DateFileName();
        void DateFileSave();
        void AckDateFileSave();

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
