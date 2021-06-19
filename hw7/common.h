#ifndef COMMON_H
#define COMMON_H

enum class Result {
  doesNotHavePrereqs,
  hasPrereqs,

  hasPermission,
  noPermission,

  notFull,
  full,
};

#endif
