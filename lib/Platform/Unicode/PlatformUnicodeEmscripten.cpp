/*
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include "hermes/Platform/Unicode/PlatformUnicode.h"

#if HERMES_PLATFORM_UNICODE == HERMES_PLATFORM_UNICODE_EMSCRIPTEN

#include <emscripten.h>

namespace hermes {
namespace platform_unicode {

// clang-format off

EM_JS(int, js_platform_unicode_localeCompare, (
    const char16_t *a, size_t aLen, const char16_t *b, size_t bLen), {
  function copyStr(p, len) {
    var res = "";
    p >>>= 1;
    for (; len >= 0; --len, ++p) {
      res += String.fromCharCode(HEAP16[p])
    }
    return res;
  }
  var strA = copyStr(a, aLen);
  var strB = copyStr(b, bLen);
  return strA.localeCompare(strB);
});

// clang-format on

int localeCompare(
    llvm::ArrayRef<char16_t> left,
    llvm::ArrayRef<char16_t> right) {
  return js_platform_unicode_localeCompare(
      left.data(), left.size(), right.data(), right.size());
}

void dateFormat(
    double unixtimeMs,
    bool formatDate,
    bool formatTime,
    llvm::SmallVectorImpl<char16_t> &buf) {
  // FIXME: implement this.
  llvm::ArrayRef<char> str{"dateFormat not implemented"};
  buf.assign(str.begin(), str.end());
}

void convertToCase(
    llvm::SmallVectorImpl<char16_t> &str,
    CaseConversion targetCase,
    bool useCurrentLocale) {
  // FIXME: implement this.
}

void normalize(llvm::SmallVectorImpl<char16_t> &buf, NormalizationForm form) {
  // FIXME: implement this.
}

} // namespace platform_unicode
} // namespace hermes

#endif // HERMES_PLATFORM_UNICODE_JAVA
