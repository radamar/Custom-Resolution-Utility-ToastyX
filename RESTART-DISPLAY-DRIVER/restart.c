/* Includes *****************************************************************/

#include "stdafx.h"

/* Defines ******************************************************************/

#define MAX_WINDOWS 10000

/* Globals ******************************************************************/

DWORD window_count;
HWND window_list[MAX_WINDOWS];
WINDOWPLACEMENT window_placement[MAX_WINDOWS];

/* Functions ****************************************************************/

int ErrorMessage(LPCTSTR text)
{
	MessageBox(NULL, text, _T("Error"), MB_ICONERROR);
	return 1;
}

/****************************************************************************/

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

int RecoverDevice(LPCTSTR display_id, LPCTSTR device_id, BOOL recover)
{
	HKEY key;
	TCHAR subkey[256];
	int result = 0;

	if (_sntprintf(subkey, 256, _T("SYSTEM\\CurrentControlSet\\Enum\\DISPLAY\\%s\\%s\\Device Parameters"), display_id, device_id) >= 256)
		return -2;

	switch (RegOpenKeyEx(HKEY_LOCAL_MACHINE, subkey, 0, KEY_SET_VALUE, &key))
	{
		case ERROR_SUCCESS:
			if (recover)
			{
				RegDeleteTree(key, _T("EDID_RECOVERY"));

				switch (RegRenameKey(key, L"EDID_OVERRIDE", L"EDID_RECOVERY"))
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
			else
			{
				RegDeleteTree(key, _T("EDID_OVERRIDE"));

				switch (RegRenameKey(key, L"EDID_RECOVERY", L"EDID_OVERRIDE"))
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

int RecoverDisplay(LPCTSTR display_id, BOOL recover)
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
		result |= RecoverDevice(display_id, device_id, recover);

	RegCloseKey(key);
	return result;
}

/****************************************************************************/

int RecoverDisplays(BOOL recover)
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
		result |= RecoverDisplay(display_id, recover);

	RegCloseKey(key);
	return result;
}

/****************************************************************************/

BOOL CALLBACK EnumWindowsProc(HWND window, LPARAM lParam)
{
	if (window_count >= MAX_WINDOWS)
		return FALSE;

	if (IsWindowVisible(window))
	{
		window_list[window_count] = window;
		window_placement[window_count].length = sizeof window_placement[window_count];
		GetWindowPlacement(window, &window_placement[window_count]);

		switch (window_placement[window_count].showCmd)
		{
			case SW_SHOWNORMAL:
				GetWindowRect(window, &window_placement[window_count].rcNormalPosition);
				break;

			case SW_SHOWMAXIMIZED:
				ShowWindow(window, SW_SHOWNORMAL);
				break;
		}

		window_placement[window_count].flags |= WPF_ASYNCWINDOWPLACEMENT;
		window_count++;
	}

	return TRUE;
}

/****************************************************************************/

void SaveWindows()
{
	window_count = 0;
	EnumWindows(EnumWindowsProc, 0);
}

/****************************************************************************/

BOOL SetWindowRect(HWND window, RECT rect, UINT flags)
{
	return SetWindowPos(window, HWND_TOP, rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, flags);
}

/****************************************************************************/

BOOL RestoreWindows()
{
	DWORD i;

	for (i = 0; i < window_count; i++)
	{
		if (window_placement[i].showCmd == SW_SHOWNORMAL)
			SetWindowRect(window_list[i], window_placement[i].rcNormalPosition, SWP_ASYNCWINDOWPOS);
		else
			SetWindowPlacement(window_list[i], &window_placement[i]);
	}

	return TRUE;
}

/****************************************************************************/

DWORD KillProcess(LPCTSTR name)
{
	HANDLE processes;
	PROCESSENTRY32 process_entry;
	HANDLE process;
	DWORD result = 0;

	processes = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

	if (processes == INVALID_HANDLE_VALUE)
		return 0;

	process_entry.dwSize = sizeof process_entry;

	if (Process32First(processes, &process_entry))
	{
		do
		{
			if (_tcsicmp(process_entry.szExeFile, name) == 0)
			{
				process = OpenProcess(PROCESS_TERMINATE, FALSE, process_entry.th32ProcessID);

				if (process)
				{
					TerminateProcess(process, 0);
					CloseHandle(process);
					result++;
				}
			}
		}
		while (Process32Next(processes, &process_entry));
	}

	CloseHandle(processes);
	return result;
}

/****************************************************************************/

BOOL RefreshNotifyWindow(HWND window)
{
	RECT rect;
	int x, y;

	GetClientRect(window, &rect);

	for (y = 0; y < rect.bottom; y += 4)
		for (x = 0; x < rect.right; x += 4)
			PostMessage(window, WM_MOUSEMOVE, 0, (y << 16) | (x & 65535));

	return TRUE;
}

/****************************************************************************/

BOOL RefreshNotifyIcons()
{
	HWND parent;
	HWND window;

	parent = FindWindow(_T("Shell_TrayWnd"), NULL);

	if (!parent)
		return FALSE;

	parent = FindWindowEx(parent, NULL, _T("TrayNotifyWnd"), NULL);

	if (!parent)
		return FALSE;

	parent = FindWindowEx(parent, NULL, _T("SysPager"), NULL);

	if (!parent)
		return FALSE;

	window = FindWindowEx(parent, NULL, _T("ToolbarWindow32"), _T("Notification Area"));

	if (window)
		RefreshNotifyWindow(window);

	window = FindWindowEx(parent, NULL, _T("ToolbarWindow32"), _T("User Promoted Notification Area"));

	if (window)
		RefreshNotifyWindow(window);

	parent = FindWindow(_T("NotifyIconOverflowWindow"), NULL);

	if (parent)
	{
		window = FindWindowEx(parent, NULL, _T("ToolbarWindow32"), _T("Overflow Notification Area"));

		if (window)
			RefreshNotifyWindow(window);
	}

	return TRUE;
}

/****************************************************************************/

BOOL SetProcessTokenPrivilege(LPCTSTR name, DWORD attributes)
{
	TOKEN_PRIVILEGES token_privileges;
	HANDLE process_token;

	token_privileges.PrivilegeCount = 1;
	token_privileges.Privileges[0].Attributes = attributes;

	if (!LookupPrivilegeValue(NULL, name, &token_privileges.Privileges[0].Luid))
		return FALSE;

	if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &process_token))
		return FALSE;

	if (!AdjustTokenPrivileges(process_token, FALSE, &token_privileges, 0, NULL, NULL))
	{
		CloseHandle(process_token);
		return FALSE;
	}

	CloseHandle(process_token);
	return TRUE;
}

/****************************************************************************/

HANDLE GetUserToken()
{
	HWND shell_window;
	DWORD process_id;
	HANDLE process_handle;
	HANDLE process_token;
	HANDLE user_token;

	if (!SetProcessTokenPrivilege(SE_INCREASE_QUOTA_NAME, SE_PRIVILEGE_ENABLED))
		return NULL;

	shell_window = GetShellWindow();

	if (!shell_window)
		return NULL;

	GetWindowThreadProcessId(shell_window, &process_id);

	if (!process_id)
		return NULL;

	process_handle = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, process_id);

	if (!process_handle)
		return NULL;

	if (!OpenProcessToken(process_handle, TOKEN_DUPLICATE, &process_token))
	{
		CloseHandle(process_handle);
		return NULL;
	}

	if (!DuplicateTokenEx(process_token, TOKEN_QUERY | TOKEN_DUPLICATE | TOKEN_ASSIGN_PRIMARY | TOKEN_ADJUST_DEFAULT | TOKEN_ADJUST_SESSIONID, NULL, SecurityImpersonation, TokenPrimary, &user_token))
		user_token = NULL;

	CloseHandle(process_handle);
	CloseHandle(process_token);
	return user_token;
}

/****************************************************************************/

BOOL RunAsUser(LPWSTR command)
{
	HANDLE user_token;
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;

	user_token = GetUserToken();

	if (!user_token)
		return FALSE;

	GetStartupInfo(&startup_info);

	if (!CreateProcessWithTokenW(user_token, 0, NULL, command, 0, NULL, NULL, &startup_info, &process_info))
	{
		CloseHandle(user_token);
		return FALSE;
	}

	CloseHandle(user_token);
	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
	return TRUE;
}

/****************************************************************************/

BOOL StopCCC()
{
	KillProcess(_T("MOM.exe"));
	KillProcess(_T("CCC.exe"));
	return TRUE;
}

/****************************************************************************/

BOOL StartCCC()
{
	WCHAR command[] = L"CLI.exe start";
	LPCTSTR program_files;

	program_files = _tgetenv(_T("ProgramFiles(x86)"));

	if (!program_files)
	{
		program_files = _tgetenv(_T("ProgramFiles"));

		if (!program_files)
			return FALSE;
	}

	if (_tchdir(program_files) != 0)
		return FALSE;

	if (_tchdir(_T("AMD\\ATI.ACE\\Core-Static")) != 0)
		if (_tchdir(_T("ATI Technologies\\ATI.ACE\\Core-Static")) != 0)
			return FALSE;

	if (!RunAsUser(command))
		return FALSE;

	return TRUE;
}

/****************************************************************************/

BOOL StopRadeonSettings()
{
	KillProcess(_T("RadeonSettings.exe"));
	KillProcess(_T("cnext.exe"));
	return TRUE;
}

/****************************************************************************/

BOOL StartRadeonSettings()
{
	WCHAR command[] = L"cncmd.exe restart";
	LPCTSTR program_files;

	program_files = _tgetenv(_T("ProgramFiles"));

	if (!program_files)
		return FALSE;

	if (_tchdir(program_files) != 0)
		return FALSE;

	if (_tchdir(_T("AMD\\CNext\\CNext")) != 0)
		return FALSE;

	if (!RunAsUser(command))
		return FALSE;

	return TRUE;
}

/****************************************************************************/

BOOL FixTaskbar()
{
	KillProcess(_T("ShellExperienceHost.exe"));
	KillProcess(_T("SearchUI.exe"));
	return TRUE;
}

/****************************************************************************/

DWORD SetDriverState(DWORD state)
{
	HDEVINFO devices;
	DWORD i;
	SP_DEVINFO_DATA device;
	SP_PROPCHANGE_PARAMS params;
	DWORD result = 0;

	devices = SetupDiGetClassDevs(&GUID_DEVCLASS_DISPLAY, NULL, NULL, DIGCF_PRESENT);

	if (devices == INVALID_HANDLE_VALUE)
		return 0;

	for (i = 0; device.cbSize = sizeof device, SetupDiEnumDeviceInfo(devices, i, &device); i++)
	{
		params.ClassInstallHeader.cbSize = sizeof params.ClassInstallHeader;
		params.ClassInstallHeader.InstallFunction = DIF_PROPERTYCHANGE;
		params.StateChange = state;
		params.Scope = DICS_FLAG_GLOBAL;
		params.HwProfile = 0;

		if (SetupDiSetClassInstallParams(devices, &device, &params.ClassInstallHeader, sizeof params))
			if (SetupDiCallClassInstaller(DIF_PROPERTYCHANGE, devices, &device))
				result++;
	}

	SetupDiDestroyDeviceInfoList(devices);
	return result;
}

/****************************************************************************/

BOOL StopDriver()
{
	SaveWindows();

	if (!SetDriverState(DICS_DISABLE))
		return FALSE;

	StopCCC();
	StopRadeonSettings();
	Sleep(100);
	RefreshNotifyIcons();
	Sleep(2500);
	return TRUE;
}

/****************************************************************************/

BOOL StartDriver()
{
	if (!SetDriverState(DICS_ENABLE))
		return FALSE;

	FixTaskbar();
	Sleep(3000);
	RestoreWindows();
	StartRadeonSettings();
	Sleep(100);
	return TRUE;
}

/****************************************************************************/

int FinishRestart()
{
	StartCCC();
	return 0;
}

/****************************************************************************/

BOOL RestartDriver()
{
	if (!StopDriver())
		return FALSE;

	if (!StartDriver())
		return FALSE;

	return TRUE;
}

/****************************************************************************/

BOOL IsWow64()
{
	BOOL result;

	if (!IsWow64Process(GetCurrentProcess(), &result))
		return FALSE;

	return result;
}

/****************************************************************************/

BOOL RestartOnly(LPTSTR options)
{
	TCHAR path[32768];
	LPTSTR file;

	if (_tcscmp(options, _T("-q")) == 0)
		return TRUE;

	if (!GetModuleFileName(NULL, path, 32768))
		return FALSE;

	file = _tcsrchr(path, _T('\\'));

	if (!file)
		file = path;

	_tcslwr(file);

	if (_tcsstr(file, _T("-only.")))
		return TRUE;

	return FALSE;
}

/****************************************************************************/

BOOL Restart64(LPTSTR options)
{
	TCHAR command[256];
	STARTUPINFO startup_info;
	PROCESS_INFORMATION process_info;

	if (RestartOnly(options))
		_tcscpy(command, _T("restart64.exe -q"));
	else
		_tcscpy(command, _T("restart64.exe"));

	GetStartupInfo(&startup_info);

	if (!CreateProcess(NULL, command, NULL, NULL, FALSE, 0, NULL, NULL, &startup_info, &process_info))
		return FALSE;

	CloseHandle(process_info.hProcess);
	CloseHandle(process_info.hThread);
	return TRUE;
}

/****************************************************************************/

BOOL WaitForDesktop()
{
	int passes;
	HDESK desktop;

	for (passes = 1;; passes++)
	{
		desktop = OpenInputDesktop(0, FALSE, MAXIMUM_ALLOWED);

		if (desktop)
		{
			CloseDesktop(desktop);
			break;
		}

		if (passes == 20)
			return FALSE;

		Sleep(200);
	}

	return TRUE;
}

/****************************************************************************/

INT_PTR CALLBACK RestartProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			RegisterHotKey(window, IDC_RECOVERY, 0, VK_F8);
			SetForegroundWindow(window);
			return TRUE;

		case WM_CLOSE:
			UnregisterHotKey(window, 0);
			EndDialog(window, IDC_EXIT);
			return TRUE;

		case WM_HOTKEY:
		case WM_COMMAND:
			if (wParam == IDCANCEL)
				return FALSE;

			UnregisterHotKey(window, 0);
			EndDialog(window, wParam);
			return TRUE;
	}

	return FALSE;
}

/****************************************************************************/

INT_PTR CALLBACK RecoveryProc(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_INITDIALOG:
			SetForegroundWindow(window);
			return TRUE;

		case WM_CLOSE:
			EndDialog(window, IDC_EXIT);
			return TRUE;

		case WM_COMMAND:
			if (wParam == IDCANCEL)
				return FALSE;

			EndDialog(window, wParam);
			return TRUE;
	}

	return FALSE;
}

/* Main *********************************************************************/

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	if (IsWow64())
	{
		if (!Restart64(lpCmdLine))
			return ErrorMessage(_T("Failed to load restart64.exe."));

		return 0;
	}

	WaitForDesktop();

	if (!RestartDriver())
		return ErrorMessage(_T("Failed to restart graphics driver."));

	if (RestartOnly(lpCmdLine))
		return FinishRestart();

	for (;;)
	{
		switch (DialogBox(hInstance, _T("IDD_RESTART"), NULL, RestartProc))
		{
			case IDC_RESTART:
				if (!RestartDriver())
					return ErrorMessage(_T("Failed to restart graphics driver."));

				break;

			case IDC_RECOVERY:
				ResetConfigurations();
				ResetConnectivity();
				RecoverDisplays(TRUE);

				if (!RestartDriver())
					return ErrorMessage(_T("Failed to restart graphics driver."));

				ResetConfigurations();
				ResetConnectivity();
				RecoverDisplays(FALSE);

				if (DialogBox(hInstance, _T("IDD_RECOVERY"), NULL, RecoveryProc) == IDC_EXIT)
					return FinishRestart();

				if (!RestartDriver())
					return ErrorMessage(_T("Failed to restart graphics driver."));

				break;

			case IDC_EXIT:
				return FinishRestart();
		}
	}
}
