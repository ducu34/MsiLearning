// CustomAction.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"


// My CustAct #1
UINT WINAPI MeasureUIText(MSIHANDLE hSession)
{
  hSession;
  return ERROR_SUCCESS;
}


// My CustAct #2
UINT WINAPI PopulateCombo(MSIHANDLE hSession)
{
  hSession;
  return ERROR_SUCCESS;
}

