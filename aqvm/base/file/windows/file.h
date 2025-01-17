#ifdef _WIN32
// Copyright 2024 AQ author, All Rights Reserved.
// This program is licensed under the AQ License. You can find the AQ license in
// the root directory.

#ifndef AQ_AQVM_BASE_FILE_WINDOWS_FILE_H_
#define AQ_AQVM_BASE_FILE_WINDOWS_FILE_H_

#include <windows.h>

#include "aqvm/base/file/file.h"

HANDLE AqvmBaseFileWindows_ConvertFileToHandle(
    const struct AqvmBaseFile_File* file);

#endif
#endif