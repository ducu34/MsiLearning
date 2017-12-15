// MsiEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TestFunctions.h"

#include "../MsiFramework/Database.h"
#include "../MsiFramework/Table.h"
#include "../MsiFramework/RecordCollection.h"
#include "../MsiFramework/SingleRecord.h"

#include "../MsiFrameworkTree/LogicCondition.h"

MSIHANDLE handleTest;

int main()
{
  // test driver for our MSI Framework (EXE)

  // path to msi
  LPCTSTR msiPath = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles\\Your Application.msi";
//  LPCTSTR pathExport = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles";
//  LPCTSTR afileName = L"somefile.txt";

  
  // Open Database
  ::MsiOpenDatabase(msiPath, MSIDBOPEN_DIRECT, &handleTest);
  cout << handleTest;

  // select view then update
  //selectUpdate(handleTest);

  // only update
  //justUpdate(handleTest);

  LogicCondition x(L"a");

  wcout << x.mExpectedValues[3];
  return 0;


}

