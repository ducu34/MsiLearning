#pragma once

namespace MsiUtil
{
  
  UINT openView(MSIHANDLE aTargetHandle, const wstring& aSqlQuerry, MSIHANDLE& outputHandle);
  UINT runSqlQuerryCommit(MSIHANDLE aTargetHandle, const wstring& aSqlQuerry);

  UINT getFieldCount(MSIHANDLE recordHandle);
  UINT getStringFromRecord(MSIHANDLE recordHandle, int fieldNumber, wstring& resultString);

  UINT getColumnsInfo(MSIHANDLE recordHandle, map<wstring, wstring>& columnsInfo);
  UINT getPrimaryKeys(MSIHANDLE databaseHandle, const wstring& tableName, vector<wstring>& output);

  UINT commit(MSIHANDLE databaseHandle);
}
 