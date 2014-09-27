//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Datenot1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------

// 1. Нужно ли автосохранение?
//    Не мешает работа с временными файлами
// 2. Создать собств. popup-меню или main-меню для memo-поля?
// 3. Правильно ли написано выделение/освобождение памяти?

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{

  Icon->LoadFromFile("datenote.ico");

  sbImage1 = new Graphics::TBitmap;
  sbImage1->Height = 22;
  sbImage1->Width  = 23;
  sbImage1->LoadFromFile("prev.bmp");
  SpeedButton1->Glyph=sbImage1;

  sbImage2 = new Graphics::TBitmap;
  sbImage2->Height = 22;
  sbImage2->Width  = 23;
  sbImage2->LoadFromFile("today.bmp");
  SpeedButton2->Glyph=sbImage2;

  sbImage3 = new Graphics::TBitmap;
  sbImage3->Height = 22;
  sbImage3->Width  = 23;
  sbImage3->LoadFromFile("next.bmp");
  SpeedButton3->Glyph=sbImage3;

  sbImage4 = new Graphics::TBitmap;
  sbImage4->Height = 22;
  sbImage4->Width  = 23;
  sbImage4->LoadFromFile("save.bmp");
  SpeedButton4->Glyph=sbImage4;

  //  Canvas->Draw(200,200,p); левое
                 //... LoadBitmap(name,width,height);
                 // забить функцию, если подобное возм.
}
//---------------------------------------------------------------------------

// Открытие файла для соответствующей даты
void __fastcall TForm1::DateTimePicker1CloseUp(TObject *Sender)
{

  // Получаем имя файла
  fName = "Datenote\\" + DateFileName();

  // Открываем файл
  if (FileExists(fName))
    Memo1->Lines->LoadFromFile(fName);
  else
    Memo1->Lines->Text =
           DateTimePicker1->Date.FormatString("d  mmmm  yyyy г.");

  Memo1->SetFocus();
  TextChange = false;
}
//---------------------------------------------------------------------------

// Сохранение с файлом последней записи
void __fastcall TForm1::DateTimePicker1DropDown(TObject *Sender)
{

  if(TextChange)
  {
    AckDateFileSave();
  }
}
//---------------------------------------------------------------------------


// Преобразование даты в имя сооотв. файла
AnsiString TForm1::DateFileName()
{
  Word wYear, wMonth, wDay;
  AnsiString asMonth, asDay;

  DecodeDate(DateTimePicker1->Date, wYear, wMonth, wDay);

  // Получаем имя нужного файла для конкр. даты
  if ( wMonth < 10 )
    asMonth = "0" + IntToStr(wMonth);
  else
    asMonth = IntToStr(wMonth);
  if ( wDay < 10 )
    asDay = "0" + IntToStr(wDay);
  else
    asDay = IntToStr(wDay);
  return IntToStr(wYear) + asMonth + asDay + AnsiString(".txt");
}
//---------------------------------------------------------------------------

// Сохранение файла
void TForm1::DateFileSave()
{
  // если записей нет, то удаляем файл для соотв. даты
  if(Memo1->Lines->Text.Trim() == "" ||
     Memo1->Lines->Text.Trim() ==
            DateTimePicker1->Date.FormatString("d  mmmm  yyyy г.") )
  {
    if (FileExists(fName))
    {
      DeleteFile(fName);
    }
  }
  else
  {
    if (!FileExists(fName))
    { // если файл не существует, создаем его
      int handle;
      handle = FileCreate(fName);
      FileClose(handle);
    }
    Memo1->Lines->SaveToFile(fName);
  }
}
//---------------------------------------------------------------------------

// Сохранение файла с подтверждением
void TForm1::AckDateFileSave()
{
  if(MessageBox(0,"Сохранить последние изменения?",
               "Сохранение",MB_YESNO)==IDYES)
  {
    DateFileSave();
  }
}
//---------------------------------------------------------------------------

// Сохранение изменений при выходе из "Дневника"
void __fastcall TForm1::FormCloseQuery(TObject *Sender, bool &CanClose)
{
  DateTimePicker1DropDown(Sender);

  // Освобождаем память
  delete sbImage1;
  delete sbImage2;
  delete sbImage3;
  delete sbImage4;

}
//---------------------------------------------------------------------------

// Внесены изменения в текст
void __fastcall TForm1::Memo1KeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
  TextChange = true;
}
//---------------------------------------------------------------------------

// Предыдущий день отн-но выбранного
void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
  TDateTime TmpDate;

  DateTimePicker1DropDown(Sender);

  TmpDate = DateTimePicker1->Date;
  TmpDate--;
  DateTimePicker1->Date = TmpDate;

  DateTimePicker1CloseUp(Sender);
}
//---------------------------------------------------------------------------

// Текущая дата
void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
  DateTimePicker1DropDown(Sender);
  DateTimePicker1->Date = Now();
  DateTimePicker1CloseUp(Sender);
}
//---------------------------------------------------------------------------

// Следующий день отн-но выбранного
void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
  TDateTime TmpDate;

  DateTimePicker1DropDown(Sender);

  TmpDate = DateTimePicker1->Date;
  TmpDate++;
  DateTimePicker1->Date = TmpDate;

  DateTimePicker1CloseUp(Sender);

}
//---------------------------------------------------------------------------

// Автосохранение через каждую минуту
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
  if(TextChange)
      DateFileSave();
}
//---------------------------------------------------------------------------

// Сохранение пользователем по ходу работы
void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
  if(TextChange)
  {
    DateFileSave();
    TextChange = false;
  }
}
//---------------------------------------------------------------------------

// Формирование инфо для текущей даты
void __fastcall TForm1::FormCreate(TObject *Sender)
{
  DateTimePicker1->Date = Now();

  // Получаем имя файла
  fName = "Datenote\\" + DateFileName();

  if (!DirectoryExists("Datenote"))
  {
     if (!CreateDir("Datenote"))
     {
         ShowMessage("Невозможно создать каталог Datenote");
         Form1->Close();
     }
  }

  // Открываем файл
  if (FileExists(fName))
    Memo1->Lines->LoadFromFile(fName);
  else
    Memo1->Lines->Text =
           DateTimePicker1->Date.FormatString("d  mmmm  yyyy г.");

  // Текст пока не изменяли        
  TextChange = false;

}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormActivate(TObject *Sender)
{
  Memo1->SetFocus();

}
//---------------------------------------------------------------------------

