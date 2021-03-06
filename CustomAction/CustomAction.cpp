// CustomAction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "CustActUtil.h"
#include "../MsiFramework/Database.h"

// My CustAct #Test
UINT WINAPI TestCustAct(MSIHANDLE hSession)
{
  ::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  
  // too much work for an insert
  auto database = Database(hSession);

  // delete
  auto d = database.inTable(L"Control")->withColumns(L"X")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg"))->select();
  auto ele = d->getRowWithNumber(0)->getElementFromColumn(L"X");
  //int e = ele->getValue();
  auto e2 = ele->getAsInt();
  auto e3 = ele->getAsString();
  e; e2; e3;

  return ERROR_SUCCESS;
}

// My CustAct #1
UINT WINAPI MeasureUIText(MSIHANDLE hSession)
{
  Database database(hSession);

  // optimize property search

  // select table
  auto folderDlgText = database.inTable(L"Control")->withColumns(L"Text")->whereConditionIs(Equal(L"Dialog_", L"FolderDlg"))->orderByAsc(L"Control")->select();
  
  for (auto& row : *folderDlgText)
  {
    // get element
    auto initialString = row.getElementFromColumn(L"Text")->getAsString();
    
    // put value insted of property
    initialString = CustActUtil::getStringWithProperties(database, initialString);

    // nr chars after ignoring some types of sequences
    UINT nrChars = CustActUtil::getNrCharDisplayed(initialString);

    // update value
    row.getElementFromColumn(L"Text")->update(to_wstring(nrChars) + L" " + initialString);
  }

  return ERROR_SUCCESS;
}

UINT WINAPI PopulateComboboxDialogNames(MSIHANDLE hSession)
{
  Database database(hSession);

  // get all dialog names
  vector<wstring> dialogNames;
  auto table = database.inTable(L"Dialog")->withColumns(L"Dialog")->select();
  if (table)
  {
    int nrRows = table->getNumberOfRows();
    for (int i = 0; i < nrRows; i++)
    {
      dialogNames.push_back(table->getRowWithNumber(i)->getElementFromColumn(L"Dialog")->getAsString());
    }
  }

  // delete elements from combobox
  database.inTable(L"ComboBox")->whereConditionIs(Equal(L"Property", L"COMBOBOX_1_PROP"))->deleteRows();

  // populate combobox
  int i = 0;
  for (const auto& dialogName : dialogNames)
  {
    auto inserter = database.inTable(L"ComboBox")->insertInColumnWithValue(L"Property", L"COMBOBOX_1_PROP");
    inserter = inserter->insertInColumnWithValue(L"Order", to_wstring(++i));
    inserter = inserter->insertInColumnWithValue(L"Value", dialogName);
    inserter = inserter->insertInColumnWithValue(L"Text", dialogName);
    inserter->insert();
  }

  return ERROR_SUCCESS;
}

UINT WINAPI PopulateComboboxDirectoryNames(MSIHANDLE hSession)
{
  //::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);

  Database database(hSession);

  // get all dialog names
  vector<wstring> directoryNames;
  auto table = database.inTable(L"Directory")->withColumns(L"Directory")->select([](Row& aRow) {
    if (aRow.getElementFromColumn(L"Directory")->getAsString() == L"TARGETDIR" || 
        aRow.getElementFromColumn(L"Directory")->getAsString() == L"WindowsFolder")
      return false;
    return true;
  });

  if (table)
  {
    for (auto& row : *table)
    {
      wstring name = row.getElementFromColumn(L"Directory")->getAsString();
      wstring fullPaht = CustActUtil::findFullPathForDirectory(database, name);
      directoryNames.push_back(fullPaht);
    }
  }

  // delete elements from combobox
  database.inTable(L"ComboBox")->whereConditionIs(Equal(L"Property", L"COMBOBOX_2_PROP"))->deleteRows();

  // populate combobox
  database.insertElementsInComboBox(L"COMBOBOX_2_PROP", directoryNames);

  return ERROR_SUCCESS;
}

// My CustAct #2
UINT WINAPI PopulateListBoxAtoZ(MSIHANDLE hSession)
{
  //::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);

  Database database(hSession);
  wstring chosenDialog = database.getValueFromProperty(L"COMBOBOX_1_PROP");

  // delete elements from listbox
  database.inTable(L"ListBox")->whereConditionIs(Equal(L"Property", L"LISTBOX_1_PROP"))->deleteRows();

  // populate listbox
  if (chosenDialog.size())
  {
    auto controlTable = database.inTable(L"Control")->withColumns(L"Control", L"Type")->whereConditionIs(Equal(L"Dialog_", chosenDialog))->orderByAsc(L"Control")->select();
    //int nrRows = controlTable->getNumberOfRows();

    // extract elements
    vector<wstring> extracted;
    for (auto& row : *controlTable)
    {
      wstring value = L"Control: " + row.getElementFromColumn(L"Control")->getAsString();
      extracted.push_back(value);
    }

    // sort elements
    sort(extracted.begin(), extracted.end());

    // insert
    database.insertElementsInListBox(L"LISTBOX_1_PROP", extracted);
    //CustActUtil::insertElementsInListBox(database, L"LISTBOX_1_PROP", extracted);
  }
  else
  {
    return 1;
  }

  return ERROR_SUCCESS;
}

UINT WINAPI PopulateListBoxTabOrder(MSIHANDLE hSession)
{
  //::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  Database database(hSession);

  wstring chosenDialog = database.getValueFromProperty(L"COMBOBOX_1_PROP");

  // sort controls
  auto controlsTable = database.inTable(L"Control")->withColumns(L"Control", L"Control_Next")->whereConditionIs(Equal(L"Dialog_", chosenDialog))->select();
  map<wstring, wstring> controls;

  wstring firstControl = database.inTable(L"Dialog")->withColumns(L"Control_First")->whereConditionIs(Equal(L"Dialog", chosenDialog))->select()->getRowWithNumber(0)->getElementFromColumn(L"Control_First")->getAsString();

  for (auto& row : *controlsTable)
  {
    wstring control = row.getElementFromColumn(L"Control")->getAsString();
    wstring controlNext = row.getElementFromColumn(L"Control_Next")->getAsString();
    controls[control] = controlNext;
  }
  
  vector<wstring> sorted = { firstControl };
  while (true)
  {
    wstring next = controls[sorted[sorted.size() - 1]];
    if (next != firstControl)
    {
      sorted.push_back(next);
    }
    else
    {
      break;
    }
  }

  for (auto& control : sorted)
  {
    control = L"Control: " + control;
  }

  // delete elements from listbox
  database.inTable(L"ListBox")->whereConditionIs(Equal(L"Property", L"LISTBOX_1_PROP"))->deleteRows();

  database.insertElementsInListBox(L"LISTBOX_1_PROP", sorted);

  return ERROR_SUCCESS;
}

UINT WINAPI DirectorFiles(MSIHANDLE hSession)
{
  //::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  hSession;

  auto err = CustActUtil::DirectorFilesPopulateListBox(hSession, false);
  err;

  return ERROR_SUCCESS;
}

UINT WINAPI DirectorFilesInstall(MSIHANDLE hSession)
{
  //::MessageBox(NULL, L"debug", NULL, MB_OKCANCEL);
  hSession;

  auto err = CustActUtil::DirectorFilesPopulateListBox(hSession, true);
  err;

  return ERROR_SUCCESS;
}
