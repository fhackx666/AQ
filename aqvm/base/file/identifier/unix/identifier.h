#ifdef __unix__
// Copyright 2024 AQ author, All Rights Reserved.
// This program is licensed under the AQ License. You can find the AQ license in
// the root directory.

#ifndef AQ_AQVM_BASE_FILE_IDENTIFIER_UNIX_IDENTIFIER_H_
#define AQ_AQVM_BASE_FILE_IDENTIFIER_UNIX_IDENTIFIER_H_

#include <stdbool.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/types.h>

struct AqvmBaseFile_File;

typedef struct {
  dev_t st_dev;
  ino_t st_ino;
} AqvmBaseFileIdentifierUnix_Identifier;

int AqvmBaseFileIdentifierUnix_GetIdentifier(
    const struct AqvmBaseFile_File* file,
    AqvmBaseFileIdentifierUnix_Identifier* identifier);

uint32_t AqvmBaseFileIdentifierUnix_GetIdentifierHash(
    const AqvmBaseFileIdentifierUnix_Identifier* identifier);

bool AqvmBaseFileIdentifierUnix_IsEqual(
    const AqvmBaseFileIdentifierUnix_Identifier* identifier1,
    const AqvmBaseFileIdentifierUnix_Identifier* identifier2);

#endif

#endif