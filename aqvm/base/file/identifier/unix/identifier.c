#ifdef __unix__
// Copyright 2024 AQ author, All Rights Reserved.
// This program is licensed under the AQ License. You can find the AQ license in
// the root directory.

#include "aqvm/base/file/identifier/unix/identifier.h"

#include <sys/stat.h>
#include <sys/types.h>

#include "aqvm/base/file/unix/file.h"
#include "aqvm/base/hash/hash.h"

int AqvmBaseFileIdentifierUnix_GetIdentifier(
    const struct AqvmBaseFile_File* file,
    AqvmBaseFileIdentifierUnix_Identifier* identifier) {
  if (file == NULL || file->file == NULL || identifier == NULL) {
    // TODO(logging)
    return -1;
  }

  struct stat st = AqvmBaseFileUnix_ConvertFileToStat(file);
  if (stat(filename, &st) != 0) {
    // TODO(logging)
    return -2;
  }

  identifier->st_dev = st.st_dev;
  identifier->st_ino = st.st_ino;

  return 0;
}

uint32_t AqvmBaseFileIdentifierUnix_GetIdentifierHash(
    const AqvmBaseFileIdentifierUnix_Identifier* identifier) {
  if (identifier == NULL) {
    // TODO(logging)
    return 0;
  }
  uint32_t hash[2];

  hash[0] = identifier->st_dev;
  hash[1] = identifier->st_ino;

  return AqvmBaseHash_HashUnsignedIntArray(hash, 2);
}

bool AqvmBaseFileIdentifierUnix_IsEqual(
    const AqvmBaseFileIdentifierUnix_Identifier* identifier1,
    const AqvmBaseFileIdentifierUnix_Identifier* identifier2) {
  if (identifier1 == NULL || identifier2 == NULL) {
    // TODO(logging)
    return false;
  }

  if (identifier1->st_dev == identifier2->st_dev &&
      identifier1->st_ino == identifier2->st_ino) {
    return true;
  }
  return false;
}
#endif