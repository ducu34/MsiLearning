// CustomAction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "../MsiFramework/Database.h"


// My CustAct #1
UINT WINAPI MeasureUIText(MSIHANDLE hSession)
{
  ::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);

  /*
  Element has to know how update 
    1. in disk mode
    2. in custact mode
  */

  hSession = ::MsiGetActiveDatabase(hSession);
  Database database(hSession);
  
  LPCWSTR sqlQuery = L" SELECT * FROM `Control` WHERE ( ( ( `Dialog_` = 'FolderDlg' ) ) )";
  MSIHANDLE hView;
  UINT err = ::MsiDatabaseOpenView(hSession, sqlQuery, &hView);
  MSIHANDLE hRecord, hRecordSecond;
  err = ::MsiViewExecute(hView, 0);
  err = ::MsiViewFetch(hView, &hRecord);
  err = ::MsiViewFetch(hView, &hRecord);
  err = ::MsiViewFetch(hView, &hRecord);

  wstring s = L"";
  MsiUtil::getStringFromRecord(hRecord, 10, s);

  err = ::MsiViewFetch(hView, &hRecordSecond);
  err = ::MsiViewFetch(hView, &hRecordSecond);

  err = ::MsiViewExecute(hView, 0);
  err = ::MsiViewFetch(hView, &hRecord);
  err = ::MsiViewFetch(hView, &hRecord);
  err = ::MsiViewFetch(hView, &hRecord);

  err = ::MsiViewModify(hView, MSIMODIFY_DELETE, hRecord);

  s = L"midnight fun FTW";
  err = ::MsiRecordSetString(hRecord, 10, s.c_str());

  err = ::MsiViewModify(hView, MSIMODIFY_INSERT_TEMPORARY, hRecord);


  //auto folderDlgText = database.inTable(L"Control")->withColumns(L"Text")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg"))->select();
  //
  //auto numberRows = folderDlgText->getNumberOfRows();
  //for (auto it = 0; it < numberRows; it++)
  //{
  //  auto initialString = folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text")->getAsString();
  //  folderDlgText->getRowWithNumber(it)->getElementFromColumn(L"Text")->update(to_wstring(initialString.size()) + L" " + initialString);
  //}

  return ERROR_SUCCESS;
}


// My CustAct #2
UINT WINAPI PopulateCombo(MSIHANDLE hSession)
{
  hSession;
  return ERROR_SUCCESS;
}

