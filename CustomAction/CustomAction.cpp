// CustomAction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CustActUtil.h"
#include "../MsiFramework/Database.h"


// My CustAct #1
UINT WINAPI MeasureUIText(MSIHANDLE hSession)
{
  ::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);

  Database database(hSession);

  // select table
  auto folderDlgText = database.inTable(L"Control")->withColumns(L"Text")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg").And(Equal(L"Type", L"Text")))->orderByAsc(L"Control")->select();
  
  auto numberRows = folderDlgText->getNumberOfRows();
  for (auto it = 0; it < numberRows; it++)
  {
    // get element
    auto e = folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text");
    
    auto initialString = e->getAsString();

    // put value insted of property
    initialString = CustActUtil::getStringWithProperties(database, initialString);

    // nr chars after ignoring some types of sequences
    UINT nrChars = CustActUtil::getNrCharDisplayed(initialString);

    // update value
    e->update(to_wstring(nrChars) + L" " + initialString);
  }

  // save modif in table selected
  //folderDlgText->commitUpdates();

  return ERROR_SUCCESS;
}


// My CustAct #2
UINT WINAPI PopulateCombo(MSIHANDLE hSession)
{
  hSession;
  return ERROR_SUCCESS;
}

