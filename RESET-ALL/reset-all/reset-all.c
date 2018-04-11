/* Defines ******************************************************************/

#define _CRT_SECURE_NO_WARNINGS

/* Includes *****************************************************************/

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

/* Constants ****************************************************************/

LPCTSTR title = _T("CRU Reset 1.3");

/* Functions ****************************************************************/

int ResetSubconfiguration(LPCTSTR display_id, LPCTSTR configuration_id)
{
	HKEY key;
	TCHAR subkey[256];
	TCHAR subconfiguration_id[256];
	DWORD i;
	DWORD size;
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers\\Configuration\\%s\\%s"), display_id, configuration_id) >= 256)
		return -2;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_ENUMERATE_SUB_KEYS, &key) != ERROR_SUCCESS)
		return -2;

	for (i = 0; size = 256, RegEnumKeyEx(key, i, subconfiguration_id, &size, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; )
	{
		switch (RegDeleteKey(key, subconfiguration_id))
		{
			case ERROR_SUCCESS:
				result |= 1;
				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				break;

			default:
				i++;
				result |= -2;
				break;
		}
	}

	RegCloseKey(key);
	return result;
}

/****************************************************************************/

int ResetConfiguration(LPCTSTR display_id)
{
	HKEY key;
	TCHAR subkey[256];
	TCHAR configuration_id[256];
	DWORD i;
	DWORD size;
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers\\Configuration\\%s"), display_id) >= 256)
		return -2;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_ENUMERATE_SUB_KEYS, &key) != ERROR_SUCCESS)
		return -2;

	for (i = 0; size = 256, RegEnumKeyEx(key, i, configuration_id, &size, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; )
	{
		result |= ResetSubconfiguration(display_id, configuration_id);

		switch (RegDeleteKey(key, configuration_id))
		{
			case ERROR_SUCCESS:
				result |= 1;
				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				break;

			default:
				i++;
				result |= -2;
				break;
		}
	}

	RegCloseKey(key);
	return result;
}

/****************************************************************************/

int ResetConfigurations()
{
	HKEY key;
	TCHAR subkey[256];
	TCHAR display_id[256];
	DWORD i;
	DWORD size;
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers\\Configuration")) >= 256)
		return -3;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_ENUMERATE_SUB_KEYS, &key) != ERROR_SUCCESS)
		return -3;

	for (i = 0; size = 256, RegEnumKeyEx(key, i, display_id, &size, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; )
	{
		result |= ResetConfiguration(display_id);

		switch (RegDeleteKey(key, display_id))
		{
			case ERROR_SUCCESS:
				result |= 1;
				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				break;

			default:
				i++;
				result |= -2;
				break;
		}
	}

	RegCloseKey(key);
	return result;
}

/****************************************************************************/

int ResetConnectivity()
{
	HKEY key;
	TCHAR subkey[256];
	TCHAR display_id[256];
	DWORD i;
	DWORD size;
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Control\\GraphicsDrivers\\Connectivity")) >= 256)
		return -3;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_ENUMERATE_SUB_KEYS, &key) != ERROR_SUCCESS)
		return -3;

	for (i = 0; size = 256, RegEnumKeyEx(key, i, display_id, &size, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; )
	{
		switch (RegDeleteKey(key, display_id))
		{
			case ERROR_SUCCESS:
				result |= 1;
				break;

			case ERROR_FILE_NOT_FOUND:
			case ERROR_PATH_NOT_FOUND:
				break;

			default:
				i++;
				result |= -2;
				break;
		}
	}

	RegCloseKey(key);
	return result;
}

/****************************************************************************/

int ResetDevice(LPCTSTR display_id, LPCTSTR device_id)
{
	HKEY key;
	TCHAR subkey[256];
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters"), display_id, device_id) >= 256)
		return -2;

	switch (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_SET_VALUE, &key))
	{
		case ERROR_SUCCESS:
			switch (RegDeleteTree(key, _T("EDID_OVERRIDE")))
			{
				case ERROR_SUCCESS:
					result |= 1;
					break;

				case ERROR_FILE_NOT_FOUND:
				case ERROR_PATH_NOT_FOUND:
					break;

				default:
					result |= -2;
					break;
			}

			if (result != -2)
			{
				RegDeleteTree(key, _T("EDID_RECOVERY"));

				switch (RegDeleteValue(key, _T("EDID")))
				{
					case ERROR_SUCCESS:
						result |= 1;
						break;

					case ERROR_FILE_NOT_FOUND:
					case ERROR_PATH_NOT_FOUND:
						break;

					default:
						result |= -2;
						break;
				}
			}

			RegCloseKey(key);
			break;

		case ERROR_FILE_NOT_FOUND:
		case ERROR_PATH_NOT_FOUND:
			break;

		default:
			result |= -2;
			break;
	}

	return result;
}

/****************************************************************************/

int ResetDisplay(LPCTSTR display_id)
{
	HKEY key;
	TCHAR subkey[256];
	TCHAR device_id[256];
	DWORD i;
	DWORD size;
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s"), display_id) >= 256)
		return -2;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_ENUMERATE_SUB_KEYS, &key) != ERROR_SUCCESS)
		return -2;

	for (i = 0; size = 256, RegEnumKeyEx(key, i, device_id, &size, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; i++)
		result |= ResetDevice(display_id, device_id);

	RegCloseKey(key);
	return result;
}

/****************************************************************************/

int ResetDisplays()
{
	HKEY key;
	TCHAR subkey[256];
	TCHAR display_id[256];
	DWORD i;
	DWORD size;
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Enum\\DISPLAY")) >= 256)
		return -3;

	if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_ENUMERATE_SUB_KEYS, &key) != ERROR_SUCCESS)
		return -3;

	for (i = 0; size = 256, RegEnumKeyEx(key, i, display_id, &size, NULL, NULL, NULL, NULL) == ERROR_SUCCESS; i++)
		result |= ResetDisplay(display_id);

	RegCloseKey(key);
	return result;
}

/* Main *********************************************************************/

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (MessageBox(NULL, _T("Reset all displays and delete inactive entries?"), title, MB_YESNO | MB_ICONQUESTION/* | MB_SYSTEMMODAL*/) != IDYES)
		return 0;

	ResetConfigurations();
	ResetConnectivity();

	switch (ResetDisplays())
	{
		case 1:
			MessageBox(NULL, _T("Displays have been reset. Restart to redetect displays."), title, MB_ICONINFORMATION/* | MB_SYSTEMMODAL*/);
			return 0;

		case 0:
			MessageBox(NULL, _T("No displays found in the registry. Restart to redetect displays."), title, MB_ICONERROR/* | MB_SYSTEMMODAL*/);
			return 1;

		case -1:
			MessageBox(NULL, _T("Some displays could not be reset. Restart to redetect displays."), title, MB_ICONWARNING/* | MB_SYSTEMMODAL*/);
			return 1;

		case -2:
			MessageBox(NULL, _T("Failed to reset displays. Try running as administrator."), title, MB_ICONERROR/* | MB_SYSTEMMODAL*/);
			return 1;

		case -3:
			MessageBox(NULL, _T("Failed to open the registry."), title, MB_ICONERROR/* | MB_SYSTEMMODAL*/);
			return 1;
	}

	MessageBox(NULL, _T("Unknown error."), title, MB_ICONERROR/* | MB_SYSTEMMODAL*/);
	return 1;
}
