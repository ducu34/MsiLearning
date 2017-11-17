// MsiEditor.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "EngineMsi.h"


int main()
{
  // test driver for our MSI Framework (EXE)

  // path to msi
  wstring msiPath = L"";

  // to implement

  Framework::LoadFunc::loadTable(2);
  Framework::PrintFunc::listAllTables();
  Framework::PrintFunc::printSchemaTbl(2);
  Framework::PrintFunc::printRowTbl(2, 1);
  Framework::AddFunc::addRowTbl(2, 1, L" some value ");
  Framework::UpdateFunc::updateColRowTbl(2, 1, 3, L" some value ");

  return 0;
}

