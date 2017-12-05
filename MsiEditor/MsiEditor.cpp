// MsiEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "EngineMsi.h"


int main()
{
  // test driver for our MSI Framework (EXE)

  // path to msi
  LPCTSTR msiPath = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles\\Your Application.msi";
//  LPCTSTR pathExport = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles";
//  LPCTSTR afileName = L"somefile.txt";

  MSIHANDLE handleTest;


  // Open Database
  UINT errorMessage = ::MsiOpenDatabase(msiPath, MSIDBOPEN_DIRECT, &handleTest);
  cout << handleTest;

  // start works
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Database Open";


  // Open View
  MSIHANDLE phView;
  LPCTSTR sqlQuerry = L"SELECT `Text` FROM `Control` WHERE `Dialog_`='WelcomeDlg' AND `X`= 135 ";
  errorMessage = ::MsiDatabaseOpenView(handleTest, sqlQuerry, &phView);
  if (errorMessage == ERROR_SUCCESS)
    cout << " \n YEE";

  sqlQuerry = L"SELECT * FROM `Control`";
  errorMessage = ::MsiDatabaseOpenView(handleTest, sqlQuerry, &phView);
  if (errorMessage == ERROR_SUCCESS)
    cout << " \n open the god damn table";


  // create record
  MSIHANDLE emptyRecord = ::MsiCreateRecord(2);
  if (emptyRecord != NULL)
    cout << " \n Record Created";

  // execute view
  errorMessage = ::MsiViewExecute(phView, NULL);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Msi view executed";

  
  MSIHANDLE recordToColumn;
  errorMessage = ::MsiViewGetColumnInfo(phView, MSICOLINFO_TYPES, &recordToColumn);
  if (errorMessage == ERROR_SUCCESS)
    cout << " \n YEE";

  cout << "\n" << ::MsiRecordGetFieldCount(recordToColumn);
  
  // view fetch
  DWORD stringLenght = 0;
  MSIHANDLE phRecord;
  errorMessage = ::MsiViewFetch(phView, &phRecord);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Fetch succeeded"; 



  // print the string
  errorMessage = ::MsiRecordGetString(phRecord, 1, L"", &stringLenght);
  if (errorMessage == ERROR_MORE_DATA)
    cout << "\n not enough memory";

  stringLenght++;
  wchar_t stringResult[256];
  ::MsiRecordGetString(phRecord, 1, stringResult, &stringLenght);
  wcout << L"\n " << stringResult;
  stringLenght = 0;

  // modify the record
  wchar_t newString[256] = L"{\\VerdanaBold13}New value for the String, HORAAY!";
  errorMessage = MsiRecordSetString(phRecord, 1, newString);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n string set";



  // print the string again
  errorMessage = ::MsiRecordGetString(phRecord, 1, L"", &stringLenght);
  if (errorMessage == ERROR_MORE_DATA)
    cout << "\n not enough memory";

  stringLenght++;
  ::MsiRecordGetString(phRecord, 1, stringResult, &stringLenght);
  wcout << L"\n " << stringResult;
  stringLenght = 0;



  // save the modify
  errorMessage = ::MsiViewModify(phView, MSIMODIFY_REPLACE, phRecord);
  if (errorMessage == ERROR_SUCCESS)
    wcout << L"\n view modified";

  errorMessage = ::MsiDatabaseCommit(handleTest);
  if (errorMessage == ERROR_SUCCESS)
    wcout << L"\n commited";

  ::MsiCloseHandle(handleTest);

  int stop;
  cin >> stop;
  /*
  // how I want to look
  Database db = Database();
  Tabel tb = db.getTable("Control");
  Record rd = tb.getRecord(Condition);
  // modify the rd
  tb.setRecord(rd);

  Record rd = db.getTable("Control").getRecord(Condition)
  */


  /*
  Framework::LoadFunc::loadTable(2);
  listAllTables();
  printSchemaTbl(2);
  printRowTbl(2, 1);
  Framework::AddFunc::addRowTbl(2, 1, L" some value ");
  Framework::UpdateFunc::updateColRowTbl(2, 1, 3, L" some value ");
  */

  return 0;


}

