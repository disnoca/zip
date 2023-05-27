#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <windows.h>
#include "wrapper_functions.h"

void exit_with_error(const char* format, ...) {
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    exit(1);
}

void* Malloc(size_t size) {
    void* ptr = malloc(size);
    if(ptr == NULL) 
        exit_with_error("%s\n", "Malloc error");
    return ptr;
}

void* Calloc(size_t nitems, size_t size) {
    void* ptr = calloc(nitems, size);
    if(ptr == NULL) 
        exit_with_error("%s\n", "Calloc error");
    return ptr;
}

void* Realloc(void* ptr, size_t size) {
    if(size == 0) {
        Free(ptr);
        return NULL;
    }

    ptr = realloc(ptr, size);
    if(ptr == NULL) 
        exit_with_error("%s\n", "Realloc error");
    return ptr;
}

void Free(void* ptr) {
    free(ptr);
    ptr = NULL;
}


HANDLE _CreateFileA(LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) {
    HANDLE fileHandle = CreateFileA(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
    if(fileHandle == INVALID_HANDLE_VALUE)
        exit_with_error("CreateFileA error: %lu\n", GetLastError());
    return fileHandle;
}

void _CloseHandle(HANDLE hObject) {
    if(!CloseHandle(hObject))
        exit_with_error("CloseHandle error: %lu\n", GetLastError());
}

BOOL _ReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) {
    if(!ReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped)) {
        if(GetLastError() != ERROR_HANDLE_EOF)
            exit_with_error("ReadFile error: %lu\n", GetLastError());
        return FALSE;
    }
    return TRUE;
}

void _WriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten, LPOVERLAPPED lpOverlapped) {
    if(!WriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped))
        exit_with_error("WriteFile error: %lu\n", GetLastError());
}

void _SetFilePointerEx(HANDLE hFile, LARGE_INTEGER liDistanceToMove, PLARGE_INTEGER lpNewFilePointer, DWORD dwMoveMethod) {
    if(!SetFilePointerEx(hFile, liDistanceToMove, lpNewFilePointer, dwMoveMethod))
        exit_with_error("SetFilePointerEx error: %lu\n", GetLastError());
}

void _Rewind(HANDLE hFile) {
    if(SetFilePointer(hFile, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
        exit_with_error("Rewind error: %lu\n", GetLastError());
}


DWORD _GetFileAttributes(LPCSTR lpFileName) {
    DWORD dwAttrib = GetFileAttributes(lpFileName);
    if(dwAttrib == INVALID_FILE_ATTRIBUTES)
        exit_with_error("GetFileAttributes error: %lu\n", GetLastError());
    return dwAttrib;
}


void _GetFileTime(HANDLE hFile, LPFILETIME lpCreationTime, LPFILETIME lpLastAccessTime, LPFILETIME lpLastWriteTime) {
    if(!GetFileTime(hFile, lpCreationTime, lpLastAccessTime, lpLastWriteTime))
        exit_with_error("GetFileTime error: %lu\n", GetLastError());
}

void _FileTimeToSystemTime(const FILETIME* lpFileTime, LPSYSTEMTIME lpSystemTime) {
    if(!FileTimeToSystemTime(lpFileTime, lpSystemTime))
        exit_with_error("FileTimeToSystemTime error: %lu\n", GetLastError());
}

void _SystemTimeToTzSpecificLocalTime(const TIME_ZONE_INFORMATION* lpTimeZoneInformation, const SYSTEMTIME* lpUniversalTime, LPSYSTEMTIME lpLocalTime) {
    if(!SystemTimeToTzSpecificLocalTime(lpTimeZoneInformation, lpUniversalTime, lpLocalTime))
        exit_with_error("SystemTimeToTzSpecificLocalTime error: %lu\n", GetLastError());
}


HANDLE _FindFirstFile(LPCSTR lpFileName, LPWIN32_FIND_DATAA lpFindFileData) {
    HANDLE hFind = FindFirstFile(lpFileName, lpFindFileData);
    if(hFind == INVALID_HANDLE_VALUE)
        exit_with_error("FindFirstFile error: %lu\n", GetLastError());
    return hFind;
}

BOOL _FindNextFile(HANDLE hFindFile, LPWIN32_FIND_DATAA lpFindFileData) {
    if(!FindNextFile(hFindFile, lpFindFileData)) {
        if(GetLastError() != ERROR_NO_MORE_FILES)
            exit_with_error("FindNextFile error: %lu\n", GetLastError());
        return FALSE;
    }
    return TRUE;
}

void _FindClose(HANDLE hFindFile) {
    if(!FindClose(hFindFile))
        exit_with_error("FindClose error: %lu\n", GetLastError());
}


void _GetFileSizeEx(HANDLE hFile, PLARGE_INTEGER lpFileSize) {
    if(!GetFileSizeEx(hFile, lpFileSize))
        exit_with_error("GetFileSizeEx error: %lu\n", GetLastError());
}


HANDLE _CreateThread(LPSECURITY_ATTRIBUTES lpThreadAttributes, SIZE_T dwStackSize, LPTHREAD_START_ROUTINE  lpStartAddress, __drv_aliasesMem LPVOID lpParameter, DWORD dwCreationFlags, LPDWORD lpThreadId) {
    HANDLE hThread = CreateThread(lpThreadAttributes, dwStackSize, lpStartAddress, lpParameter, dwCreationFlags, lpThreadId);
    if(hThread == NULL)
        exit_with_error("CreateThread error: %lu\n", GetLastError());
    return hThread;
}

DWORD _WaitForMultipleObjects(DWORD nCount,const HANDLE* lpHandles,BOOL bWaitAll,DWORD dwMilliseconds) {
    DWORD dwWaitResult = WaitForMultipleObjects(nCount, lpHandles, bWaitAll, dwMilliseconds);
    if(dwWaitResult == WAIT_FAILED)
        exit_with_error("WaitForMultipleObjects error: %lu\n", GetLastError());
    return dwWaitResult;
}