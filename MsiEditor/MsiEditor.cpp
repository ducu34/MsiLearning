// MsiEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "TestFunctions.h"

#include "../MsiFramework/Database.h"
#include "../MsiFramework/IEvaluator.h"

MSIHANDLE handleTest;

int main()
{
  // test driver for our MSI Framework (EXE)

  // path to msi
  LPCTSTR msiPath = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles\\Your Application2.msi";
//  LPCTSTR pathExport = L"E:\\MSI\\MsiTest\\Your Application-SetupFiles";
//  LPCTSTR afileName = L"somefile.txt";

  testFunction(msiPath);

  //msiFrameworkTree(msiPath);
//  orderAtoZ(msiPath);

  return 0;

}

