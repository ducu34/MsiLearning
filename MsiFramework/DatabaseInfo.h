#pragma once
#include "stdafx.h"
#include "Table.h"
#include "LogicCondition.h"
#include "MsiUtil.h"
#include "ErrorHandling.h"

#define SQLSELECT L" SELECT "
#define SQLUPDATE L" UPDATE "
#define SQLDELETE L" DELETE "
#define SQLINSERTINTO L" INSERT INTO "
#define SQLVALUES L" VALUES "
#define SQLSET L" SET "
#define SQLFROM L" FROM "
#define SQLWHERE L" WHERE "
#define SQLCREATE L" CREATE "
#define SQLTABLE L" TABLE "
#define SQLORDERBY L" ORDER BY "
#define SQLASC L" ASC ";
#define SQLDESC L" DESC ";

struct targetMetadata {
  targetMetadata(const wstring& aName, const ColumnType aType, bool isKeyMember, bool isNullable)
    :mName(aName), mType(aType), isKeyMember(isKeyMember), isNullable(isNullable) 
  {
    if (mType == ColumnType::Integer)
      mTypeString = L" int ";
    if (mType == ColumnType::String)
      mTypeString = L" varchar(255) ";
  }

  wstring mName;
  wstring mTypeString;
  ColumnType mType;
  bool isKeyMember;
  bool isNullable;
};

struct targetColumn {
  targetColumn() :mMetadata(L"", ColumnType::String, true, true) {}
  targetColumn(const wstring& aColumnName) :mName(aColumnName), mMetadata(L"", ColumnType::String, true, true) {}

  targetMetadata mMetadata;
  UINT mNumber;
  wstring mName;
  wstring mNewValue;
};

struct targetTable {
  // constructor
  targetTable() = default;
  targetTable(const wstring& aTableName)
    : tableName(aTableName) {}
  // constructor with column names
  targetTable(const wstring& aTableName, vector<wstring> aColumnNames) 
    : tableName(aTableName)
  {
    for (auto& columnName : aColumnNames)
    {
      mColumnCollection.push_back(targetColumn(columnName));
    }
  }

  wstring tableName;

  vector<targetColumn> mColumnCollection;
};

class DatabaseInfo
{
public:

  // default constructor
  DatabaseInfo(const wstring& databasePath);
  DatabaseInfo(const MSIHANDLE handleToDatabase);

  // update condition with another condition ( add AND )
  // by default no condition
  void updateConditionWith(const LogicCondition& anotherCondition);
  
  // select
  void setTargetTable(const wstring& aTableName);
  unique_ptr<Table> select();

  // update
  UINT update();
  void updateColumnWithValue(const wstring& aColumnName, const wstring& aNewValue);

  // delete
  UINT deleteRows();
  UINT deleteAllRows();

  // insert
  void insertInColumnValue(const wstring& aColumnName, const wstring& aValue);
  UINT insert();

  // create a table
  void createTable(const wstring& aTableName);
  void createColumn(const wstring& aColumnName, const ColumnType& aColumnType);
  void createNullableColumn(const wstring& aColumnName, const ColumnType& aColumntType);
  void createKeyColumn(const wstring& aColumnName, const ColumnType& aColumnType);
  UINT addTableToDatabase();

  // order by
  void orderBy(const wstring& aColumnName, bool ascending);
  UINT order();

  // error handling
  bool isGood();
  wstring getLastError();

  // run any query
  UINT runSql(const wstring& aSqlQuerry);
  
  // set target table
  template<typename... Types>
  void addTableWithColumns(const Types... aColumns)
  {
    mTargetTabel = targetTable(mTargetTabel.tableName, vector<wstring>{ aColumns... });
  }

private: 

  // if opened from CustAct -> false
  bool isOpenFromDisk;

  UINT mErrorMessage = ERROR_SUCCESS;

  ErrorHandling mErrorHandling;

  wstring selectSqlCondition();
  wstring updateSqlCondition();
  wstring insertSqlCondition();

  wstring composeSqlQuerryTable();
  wstring composeSqlEnumerateColumns();
  wstring composeSqlEnumerateColumnValues();
  wstring composeSqlUpdateColumns();
  wstring composeSqlColumnTypes();
  wstring composeSqlCondition();

  void populateMetadataForTargetColumns(MSIHANDLE selectRecord);
  TableMetadata generateMetadataFromTarget(const wstring& aTableName);
  RowCollection generateRowCollection(const TableMetadata& aTableMetadata, MSIHANDLE aViewHandle);

  // single table
  targetTable mTargetTabel;

  Table createTableFromSqlQuerry(const wstring& sqlSelect);

  wstring mDatabasePath;

  MSIHANDLE mDatabaseHandle;

  wstring mOrderByCondition = L"";

  vector<LogicCondition> mConditions;
};
