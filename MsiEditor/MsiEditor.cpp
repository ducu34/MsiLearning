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

  UINT errorMessage = ::MsiOpenDatabase(msiPath, MSIDBOPEN_DIRECT, &handleTest);
  cout << handleTest;

  // start works
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Database Open";

  MSIHANDLE phView;
  LPCTSTR sqlQuerry = L"SELECT `Text` FROM `Control` WHERE `Dialog_`='WelcomeDlg' AND `Type`='Text' ";
  errorMessage = ::MsiDatabaseOpenView(handleTest, sqlQuerry, &phView);
  if (errorMessage == ERROR_SUCCESS)
    cout << " \n YEE";

  MSIHANDLE emptyRecord = ::MsiCreateRecord(2);
  if (emptyRecord != NULL)
    cout << " \n Record Created";

  errorMessage = ::MsiViewExecute(phView, NULL);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Msi view executed";

  
  MSIHANDLE recordToColumn;
  errorMessage = ::MsiViewGetColumnInfo(phView, MSICOLINFO_TYPES, &recordToColumn);
  if (errorMessage == ERROR_SUCCESS)
    cout << " \n YEE";

  cout << "\n" << ::MsiRecordGetFieldCount(recordToColumn);
  
  DWORD stringLenght = 0;
  MSIHANDLE phRecord;
  errorMessage = ::MsiViewFetch(phView, &phRecord);
  if (errorMessage == ERROR_SUCCESS)
    cout << "\n Fetch succeeded"; 

  errorMessage = ::MsiRecordGetString(phRecord, 1, L"", &stringLenght);
  if (errorMessage == ERROR_MORE_DATA)
    cout << "\n not enough memory";

  //string stringResult(stringLenght, L'');
  wchar_t stringResult[54];
  stringLenght++;
  ::MsiRecordGetString(phRecord, 1, stringResult, &stringLenght);
  wcout << L"\n " << stringResult;
  stringLenght = 0;

  int stop;
  cin >> stop;

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

