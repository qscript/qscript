#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 32767

void QueryKey(HKEY hKey)
{
    TCHAR    achKey[MAX_KEY_LENGTH];   // buffer for subkey name
    DWORD    cbName;                   // size of name string
    TCHAR    achClass[MAX_PATH] = TEXT("");  // buffer for class name
    //DWORD    cchClassName = MAX_PATH;  // size of class string
    DWORD    cchClassName = MAX_PATH;  // size of class string
    DWORD    cSubKeys=0;               // number of subkeys
    DWORD    cbMaxSubKey =0 ;              // longest subkey size
    DWORD    cchMaxClass = 0;              // longest class string
    DWORD    cValues = 0;              // number of values for key
    DWORD    cchMaxValue =0;          // longest value name
    DWORD    cbMaxValueData = 0;       // longest value data
    DWORD    cbSecurityDescriptor = 0; // size of security descriptor
    FILETIME ftLastWriteTime;      // last write time


    TCHAR    achKeyValue[MAX_VALUE_NAME];   // buffer for subkey name
    //TCHAR    achKeyValueData[MAX_VALUE_NAME];   // buffer for subkey name
    BYTE    achKeyValueData[MAX_VALUE_NAME];   // buffer for subkey name
    DWORD  pcbData = 0;

    DWORD i, retCode;

    TCHAR  achValue[MAX_VALUE_NAME];
    DWORD cchValue = MAX_VALUE_NAME;

    // Get the class name and the value count.
    retCode = RegQueryInfoKey(
        hKey,                    // key handle
        achClass,                // buffer for class name
        &cchClassName,           // size of class string
        NULL,                    // reserved
        &cSubKeys,               // number of subkeys
        &cbMaxSubKey,            // longest subkey size
        &cchMaxClass,            // longest class string
        &cValues,                // number of values for this key
        &cchMaxValue,            // longest value name
        &cbMaxValueData,         // longest value data
        &cbSecurityDescriptor,   // security descriptor
        &ftLastWriteTime);       // last write time

    // Enumerate the subkeys, until RegEnumKeyEx fails.

    if (cSubKeys)
    {
        printf( "\nNumber of subkeys: %d\n", cSubKeys);

        for (i=0; i<cSubKeys; i++)
        {
            cbName = MAX_KEY_LENGTH;
            retCode = RegEnumKeyEx(hKey, i,
                     achKey,
                     &cbName,
                     NULL,
                     NULL,
                     NULL,
                     &ftLastWriteTime);
            if (retCode == ERROR_SUCCESS)
            {
                _tprintf(TEXT("(%d) %s\n"), i+1, achKey);
            }
        }
    }

    // Enumerate the key values.

    if (cValues)
    {
        printf( "\nNumber of values: %d\n", cValues);

        for (i=0, retCode=ERROR_SUCCESS; i<cValues; i++)
        {
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
			DWORD pcbKeyValueData = MAX_VALUE_NAME;
            retCode = RegEnumValue(hKey, i,
                achValue,
                &cchValue,
                NULL,
                NULL,
                //NULL,
                //NULL
                achKeyValueData,
                &pcbKeyValueData
				);

            if (retCode == ERROR_SUCCESS )
            {
                _tprintf(TEXT("step 1, retCode: %d: (%d) %s\n"), retCode, i+1, achValue);
                _tprintf(TEXT("step 2, retCode: %d: achKeyValueData:  %s\n"), retCode,  achKeyValueData);
            }
        }
    }
    	i=0;
    	short int my_cchValue=32767;
		DWORD pcbKeyValueData = MAX_VALUE_NAME;
            cchValue = MAX_VALUE_NAME;
            achValue[0] = '\0';
            retCode = RegEnumValue(hKey, i,
                achValue,
                //&my_cchValue,
                &cchValue,
                NULL /* reserved */,
                NULL /* type: can be null if type not required */,
                achKeyValueData,
                &pcbKeyValueData
		);

	if (retCode == ERROR_SUCCESS ) {
                _tprintf(TEXT("step 2, retCode: %d: (%d) %s\n"), retCode, i+1, achValue);
                _tprintf(TEXT("step 2, retCode: %d: achKeyValueData:  %s\n"), retCode,  achKeyValueData);
	} else {
		_tprintf(TEXT("step 2, !ERROR_SUCCESS retCode: (%d) \n"),  retCode);
	}

	/*
	i = 0;
	retCode = RegEnumValue(hKey, i,
                achValue,
                &my_cchValue,
                NULL,
                NULL,
                NULL,
                NULL);
            if (retCode == ERROR_SUCCESS )
            {
                _tprintf(TEXT("(%d) %s\n"), i+1, achValue);
            } else {
                _tprintf(TEXT("retCode: (%d) \n"),  retCode);
	    }
	for (i=0; i<MAX_VALUE_NAME; ++i) {
		achKeyValue[i] = 0;
	}
	*/

	// retCode = RegGetValueA (hKey, "SOFTWARE\\QScript", "Install_Dir",
	// 			0x00000002  /*RRF_RT_REG_SZ */, NULL, achKeyValue, &pcbData);
        // if (retCode == ERROR_SUCCESS )
        // {
	// 	_tprintf(TEXT("achKeyValue: %s\n"), achKeyValue);
	// } else {
	// 	_tprintf(TEXT("retCode: (%d) \n"),  retCode);
	// }
}

int main()
{
	HKEY hTestKey;


	//
	//HKEY_CURRENT_USER
	//HKEY_LOCAL_MACHINE
	if (RegOpenKeyEx( HKEY_CURRENT_USER,
		TEXT("SOFTWARE\\QScript"),
		0,
		KEY_READ,
		&hTestKey) == ERROR_SUCCESS
		)
	{
		QueryKey(hTestKey);
	}

	RegCloseKey(hTestKey);
}
