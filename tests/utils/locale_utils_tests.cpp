////////////////////////////////////////////////////////////////////////////////
/// DISCLAIMER
///
/// Copyright 2016 by EMC Corporation, All Rights Reserved
///
/// Licensed under the Apache License, Version 2.0 (the "License");
/// you may not use this file except in compliance with the License.
/// You may obtain a copy of the License at
///
///     http://www.apache.org/licenses/LICENSE-2.0
///
/// Unless required by applicable law or agreed to in writing, software
/// distributed under the License is distributed on an "AS IS" BASIS,
/// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
/// See the License for the specific language governing permissions and
/// limitations under the License.
///
/// Copyright holder is EMC Corporation
///
/// @author Andrey Abramov
/// @author Vasiliy Nabatchikov
////////////////////////////////////////////////////////////////////////////////

#include <locale>

#include "gtest/gtest.h"
#include "utils/locale_utils.hpp"
#include "utils/misc.hpp"

#if defined (__GNUC__)
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

  #include <boost/locale.hpp>

#if defined (__GNUC__)
  #pragma GCC diagnostic pop
#endif

namespace tests {
  class LocaleUtilsTestSuite: public ::testing::Test {
    virtual void SetUp() {
      // Code here will be called immediately after the constructor (right before each test).
    }

    virtual void TearDown() {
      // Code here will be called immediately after each test (right before the destructor).
    }
  };
}

using namespace tests;
using namespace iresearch::locale_utils;

// -----------------------------------------------------------------------------
// --SECTION--                                                        test suite
// -----------------------------------------------------------------------------

TEST_F(LocaleUtilsTestSuite, test_locale_create) {
  {
    std::locale locale = iresearch::locale_utils::locale(nullptr);

    ASSERT_EQ(std::locale::classic(), locale);
  }

  {
    std::locale locale = iresearch::locale_utils::locale(nullptr, true);

    ASSERT_EQ(std::string("c.utf-8"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_TRUE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("*");

    ASSERT_EQ(std::string("*"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("C");

    ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("en");

    ASSERT_EQ(std::string("en"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("en_US");

    ASSERT_EQ(std::string("en_US"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("en_US.UTF-8");

    ASSERT_EQ(std::string("en_US.utf-8"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_TRUE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("ru_RU.KOI8-R");

    ASSERT_EQ(std::string("ru_RU.koi8-r"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("ru_RU.KOI8-R", true);

    ASSERT_EQ(std::string("ru_RU.utf-8"), std::use_facet<boost::locale::info>(locale).name());
    ASSERT_TRUE(std::use_facet<boost::locale::info>(locale).utf8());
  }

  {
    std::locale locale = iresearch::locale_utils::locale("InvalidString");

    ASSERT_EQ(std::string("invalidstring"), std::use_facet<boost::locale::info>(locale).name());
  }
}

TEST_F(LocaleUtilsTestSuite, test_locale_build) {
  {
    {
      std::locale expected = boost::locale::generator().generate("");
      std::locale locale = iresearch::locale_utils::locale("", "", "");

      ASSERT_EQ(std::use_facet<boost::locale::info>(expected).name(), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::use_facet<boost::locale::info>(expected).language(), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::use_facet<boost::locale::info>(expected).country(), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::use_facet<boost::locale::info>(expected).encoding(), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::use_facet<boost::locale::info>(expected).variant(), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_EQ(std::use_facet<boost::locale::info>(expected).utf8(), std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("en", "", "");

      ASSERT_EQ(std::string("en"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("en"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("en", "US", "");

      ASSERT_EQ(std::string("en_US"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("en"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string("US"), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("en", "US", "ISO-8859-1");

      ASSERT_EQ(std::string("en_US.iso-8859-1"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("en"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string("US"), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("iso-8859-1"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("en", "US", "ISO-8859-1", "args");

      ASSERT_EQ(std::string("en_US.iso-8859-1@args"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("en"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string("US"), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("iso-8859-1"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string("args"), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("en", "US", "UTF-8");

      ASSERT_EQ(std::string("en_US.utf-8"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("en"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string("US"), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("utf-8"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_TRUE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    // ...........................................................................
    // invalid
    // ...........................................................................

    {
      std::locale locale = iresearch::locale_utils::locale("", "US", "");

      ASSERT_EQ(std::string("_US"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("", "US", "ISO-8859-1");

      ASSERT_EQ(std::string("_US.iso-8859-1"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("", "US", "ISO-8859-1", "args");

      ASSERT_EQ(std::string("_US.iso-8859-1@args"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("", "US", "UTF-8");

      ASSERT_EQ(std::string("_US.utf-8"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("", "", "ISO-8859-1");

      ASSERT_EQ(std::string(".iso-8859-1"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("", "", "ISO-8859-1", "args");

      ASSERT_EQ(std::string(".iso-8859-1@args"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("", "", "UTF-8");

      ASSERT_EQ(std::string(".utf-8"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    {
      std::locale locale = iresearch::locale_utils::locale("", "", "UTF-8", "args");

      ASSERT_EQ(std::string(".utf-8@args"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }

    // ...........................................................................
    // invalid
    // ...........................................................................

    {
      std::locale locale = iresearch::locale_utils::locale("_.@", "", "", "");

      ASSERT_EQ(std::string("_.@_.@"), std::use_facet<boost::locale::info>(locale).name());
      ASSERT_EQ(std::string("C"), std::use_facet<boost::locale::info>(locale).language());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).country());
      ASSERT_EQ(std::string("us-ascii"), std::use_facet<boost::locale::info>(locale).encoding());
      ASSERT_EQ(std::string(""), std::use_facet<boost::locale::info>(locale).variant());
      ASSERT_FALSE(std::use_facet<boost::locale::info>(locale).utf8());
    }
  }
}

TEST_F(LocaleUtilsTestSuite, test_locale_codecvt) {
  auto c = irs::locale_utils::locale("C");
  auto en = irs::locale_utils::locale("en.IBM-943"); // EBCDIC
  auto ru0 = irs::locale_utils::locale("ru_RU.CP1251");
  auto ru1 = irs::locale_utils::locale("ru_RU.KOI8-R");
  auto zh = irs::locale_utils::locale("zh_CN.UTF-8");

  // ascii (char)
  {
    std::istringstream in;
    std::ostringstream out;
    std::string buf;

    in.imbue(c);
    out.imbue(c);

    in.str("in-test-data");
    in >> buf;
    ASSERT_EQ(std::string("in-test-data"), buf);

    out << "out test data" << std::endl;
    ASSERT_EQ(std::string("out test data\n"), out.str());
  }

  // ascii (char16)
  {
    auto& cvt = std::use_facet<std::codecvt<char16_t, char, mbstate_t>>(c);
    mbstate_t state = mbstate_t();
    std::string from("in test data");
    const char* from_cnext;
    char16_t buf16[12];
    const char16_t* buf16_cnext;
    char16_t* buf16_next;
    char buf8[12];
    char* buf8_next;

    ASSERT_EQ(
      //std::codecvt_base::result::partial, FIXME TODO should be partial
      std::codecvt_base::result::ok,
      cvt.in(state, &from[0], &from[0] + from.size(), from_cnext, buf16, buf16 + 1, buf16_next)
    );
    ASSERT_EQ(&from[1], from_cnext);
    ASSERT_EQ(&buf16[1], buf16_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(char16_t(from[i]), buf16[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt.in(state, &from[0], &from[0] + from.size(), from_cnext, buf16, buf16 + IRESEARCH_COUNTOF(buf16), buf16_next)
    );

    ASSERT_EQ(&from[0] + from.size(), from_cnext);
    ASSERT_EQ(&buf16[0] + IRESEARCH_COUNTOF(buf16), buf16_next);

    for (size_t i = 0, count = from.size(); i < count; ++i) {
      ASSERT_EQ(char16_t(from[i]), buf16[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt.out(state, buf16, buf16 + IRESEARCH_COUNTOF(buf16), buf16_cnext, buf8, buf8 + 1, buf8_next)
    );
    ASSERT_EQ(&buf16[1], buf16_cnext);
    ASSERT_EQ(&buf8[1], buf8_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(buf16[i], char16_t(buf8[i]));
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt.out(state, buf16, buf16 + IRESEARCH_COUNTOF(buf16), buf16_cnext, buf8, buf8 + IRESEARCH_COUNTOF(buf8), buf8_next)
    );

    ASSERT_EQ(&buf16[0] + IRESEARCH_COUNTOF(buf16), buf16_cnext);
    ASSERT_EQ(&buf8[0] + IRESEARCH_COUNTOF(buf8), buf8_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(buf16); i < count; ++i) {
      ASSERT_EQ(buf16[i], char16_t(buf8[i]));
    }
  }

  // ascii (char32)
  {
    auto& cvt = std::use_facet<std::codecvt<char32_t, char, mbstate_t>>(c);
    mbstate_t state = mbstate_t();
    std::string from("in test data");
    const char* from_cnext;
    char32_t buf32[12];
    const char32_t* buf32_cnext;
    char32_t* buf32_next;
    char buf8[12];
    char* buf8_next;

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt.in(state, &from[0], &from[0] + from.size(), from_cnext, buf32, buf32 + 1, buf32_next)
    );
    ASSERT_EQ(&from[1], from_cnext);
    ASSERT_EQ(&buf32[1], buf32_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(char32_t(from[i]), buf32[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt.in(state, &from[0], &from[0] + from.size(), from_cnext, buf32, buf32 + IRESEARCH_COUNTOF(buf32), buf32_next)
    );

    ASSERT_EQ(&from[0] + from.size(), from_cnext);
    ASSERT_EQ(&buf32[0] + IRESEARCH_COUNTOF(buf32), buf32_next);

    for (size_t i = 0, count = from.size(); i < count; ++i) {
      ASSERT_EQ(char32_t(from[i]), buf32[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt.out(state, buf32, buf32 + IRESEARCH_COUNTOF(buf32), buf32_cnext, buf8, buf8 + 1, buf8_next)
    );
    ASSERT_EQ(&buf32[1], buf32_cnext);
    ASSERT_EQ(&buf8[1], buf8_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(buf32[i], char32_t(buf8[i]));
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt.out(state, buf32, buf32 + IRESEARCH_COUNTOF(buf32), buf32_cnext, buf8, buf8 + IRESEARCH_COUNTOF(buf8), buf8_next)
    );

    ASSERT_EQ(&buf32[0] + IRESEARCH_COUNTOF(buf32), buf32_cnext);
    ASSERT_EQ(&buf8[0] + IRESEARCH_COUNTOF(buf8), buf8_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(buf32); i < count; ++i) {
      ASSERT_EQ(buf32[i], char32_t(buf8[i]));
    }
  }

  // ascii (wchar)
  {
    std::wistringstream in;
    std::wostringstream out;
    std::wstring buf;

    in.imbue(c);
    out.imbue(c);

    in.str(L"in-test-data");
    in >> buf;
    ASSERT_EQ(std::wstring(L"in-test-data"), buf);

    out << L"out test data" << std::endl;
    ASSERT_EQ(std::wstring(L"out test data\n"), out.str());
  }

  // koi8-r (char) uint8_t charset
  {
    auto& cvt_cp1251 = std::use_facet<std::codecvt<char, char, mbstate_t>>(ru0);
    auto& cvt_koi8r = std::use_facet<std::codecvt<char, char, mbstate_t>>(ru1);
    mbstate_t state = mbstate_t();
    char cp1251[] = { char(0xe2), char(0xf5), char(0xee), char(0xe4), char(0xff), char(0xf9), char(0xe8), char(0xe5), ' ', char(0xe4), char(0xe0), char(0xed), char(0xed), char(0xfb), char(0xe5) };
    char koi8r[] =  { char(0xd7), char(0xc8), char(0xcf), char(0xc4), char(0xd1), char(0xdd), char(0xc9), char(0xc5), ' ', char(0xc4), char(0xc1), char(0xce), char(0xce), char(0xd9), char(0xc5) };
    const char* koi8r_cnext;
    char buf[16];
    const char* buf_cnext;
    char* buf_next;
    char out[16];
    char* out_next;

/* FIXME TODO Boost implementation of codecvt fails to convert from koi8
    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_koi8r.in(state, koi8r, koi8r + strlen(koi8r), koi8r_cnext, buf, buf + 1, buf_next)
    );
    ASSERT_EQ(&koi8r[1], koi8r_cnext);
    ASSERT_EQ(&buf[1], buf_next);

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_koi8r.in(state, koi8r, koi8r + strlen(koi8r), koi8r_cnext, buf, buf + IRESEARCH_COUNTOF(buf), buf_next)
    );

    ASSERT_EQ(koi8r + strlen(koi8r), koi8r_cnext);
    ASSERT_EQ(buf + IRESEARCH_COUNTOF(buf), buf_next);

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_cp1251.out(state, buf, buf + IRESEARCH_COUNTOF(buf), buf_cnext, out, out + 1, out_next)
    );
    ASSERT_EQ(&buf[1], buf_cnext);
    ASSERT_EQ(&out[1], out_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(cp1251[i], out[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_cp1251.out(state, buf, buf + IRESEARCH_COUNTOF(buf), buf_cnext, out, out + IRESEARCH_COUNTOF(out), out_next)
    );

    ASSERT_EQ(buf + IRESEARCH_COUNTOF(buf), buf_cnext);
    ASSERT_EQ(out + IRESEARCH_COUNTOF(out), out_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(out); i < count; ++i) {
      ASSERT_EQ(cp1251[i], out[i]);
    }
*/
  }

  // koi8-r (char16) uint8_t charset
  {
    auto& cvt_koi8r = std::use_facet<std::codecvt<char16_t, char, mbstate_t>>(ru1);
    mbstate_t state = mbstate_t();
    char koi8r[] =  { char(0xd7), char(0xc8), char(0xcf), char(0xc4), char(0xd1), char(0xdd), char(0xc9), char(0xc5), ' ', char(0xc4), char(0xc1), char(0xce), char(0xce), char(0xd9), char(0xc5) };
    char16_t utf16[] = { 0x0432, 0x0445, 0x043E, 0x0434, 0x044F, 0x0449, 0x0438, 0x0435, 0x0020, 0x0434, 0x0430, 0x043D, 0x043D, 0x044B, 0x0435 };
    const char* koi8r_cnext;
    const char16_t* utf16_cnext;
    char16_t buf[16];
    char16_t* buf_next;
    char out[16];
    char* out_next;

/* FIXME TODO Boost implementation of codecvt fails to convert from koi8
    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_koi8r.in(state, koi8r, koi8r + strlen(koi8r), koi8r_cnext, buf, buf + 1, buf_next)
    );
    ASSERT_EQ(&koi8r[1], koi8r_cnext);
    ASSERT_EQ(&buf[1], buf_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(utf16[i], buf[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_koi8r.in(state, &koi8r[0], &koi8r[0] + strlen(koi8r), koi8r_cnext, buf, buf + IRESEARCH_COUNTOF(buf), buf_next)
    );

    ASSERT_EQ(&koi8r[0] + strlen(koi8r), koi8r_cnext);
    ASSERT_EQ(&buf[0] + IRESEARCH_COUNTOF(buf), buf_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(buf); i < count; ++i) {
      ASSERT_EQ(utf16[i], buf[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_koi8r.out(state, utf16, utf16 + IRESEARCH_COUNTOF(utf16), utf16_cnext, out, out + 1, out_next)
    );
    ASSERT_EQ(&utf16[1], utf16_cnext);
    ASSERT_EQ(&out[1], out_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(koi8r[i], out[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_koi8r.out(state, utf16, utf16 + IRESEARCH_COUNTOF(utf16), utf16_cnext, out, out + IRESEARCH_COUNTOF(out), out_next)
    );

    ASSERT_EQ(utf16 + IRESEARCH_COUNTOF(utf16), utf16_cnext);
    ASSERT_EQ(out + IRESEARCH_COUNTOF(out), out_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(out); i < count; ++i) {
      ASSERT_EQ(koi8r[i], out[i]);
    }
*/
  }

  // koi8-r (char32) uint8_t charset
  {
    auto& cvt_koi8r = std::use_facet<std::codecvt<char32_t, char, mbstate_t>>(ru1);
    mbstate_t state = mbstate_t();
    char koi8r[] =  { char(0xd7), char(0xc8), char(0xcf), char(0xc4), char(0xd1), char(0xdd), char(0xc9), char(0xc5), ' ', char(0xc4), char(0xc1), char(0xce), char(0xce), char(0xd9), char(0xc5) };
    char32_t utf32[] = { 0x0432, 0x0445, 0x043E, 0x0434, 0x044F, 0x0449, 0x0438, 0x0435, 0x0020, 0x0434, 0x0430, 0x043D, 0x043D, 0x044B, 0x0435 };
    const char* koi8r_cnext;
    const char32_t* utf32_cnext;
    char32_t buf[16];
    char32_t* buf_next;
    char out[16];
    char* out_next;

/* FIXME TODO Boost implementation of codecvt fails to convert from koi8
    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_koi8r.in(state, koi8r, koi8r + strlen(koi8r), koi8r_cnext, buf, buf + 1, buf_next)
    );
    ASSERT_EQ(&koi8r[1], koi8r_cnext);
    ASSERT_EQ(&buf[1], buf_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(utf32[i], buf[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_koi8r.in(state, &koi8r[0], &koi8r[0] + strlen(koi8r), koi8r_cnext, buf, buf + IRESEARCH_COUNTOF(buf), buf_next)
    );

    ASSERT_EQ(&koi8r[0] + strlen(koi8r), koi8r_cnext);
    ASSERT_EQ(&buf[0] + IRESEARCH_COUNTOF(buf), buf_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(buf); i < count; ++i) {
      ASSERT_EQ(utf32[i], buf[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_koi8r.out(state, utf32, utf32 + IRESEARCH_COUNTOF(utf32), utf32_cnext, out, out + 1, out_next)
    );
    ASSERT_EQ(&utf32[1], utf32_cnext);
    ASSERT_EQ(&out[1], out_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(koi8r[i], out[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_koi8r.out(state, utf32, utf32 + IRESEARCH_COUNTOF(utf32), utf32_cnext, out, out + IRESEARCH_COUNTOF(out), out_next)
    );

    ASSERT_EQ(utf32 + IRESEARCH_COUNTOF(utf32), utf32_cnext);
    ASSERT_EQ(out + IRESEARCH_COUNTOF(out), out_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(out); i < count; ++i) {
      ASSERT_EQ(koi8r[i], out[i]);
    }
*/
  }

  // koi8-r (wchar) uint8_t charset
  {
    auto& cvt_cp1251 = std::use_facet<std::codecvt<wchar_t, char, mbstate_t>>(ru0);
    auto& cvt_koi8r = std::use_facet<std::codecvt<wchar_t, char, mbstate_t>>(ru1);
    mbstate_t state = mbstate_t();
    char cp1251[] = { char(0xe2), char(0xf5), char(0xee), char(0xe4), char(0xff), char(0xf9), char(0xe8), char(0xe5), ' ', char(0xe4), char(0xe0), char(0xed), char(0xed), char(0xfb), char(0xe5) };
    char koi8r[] =  { char(0xd7), char(0xc8), char(0xcf), char(0xc4), char(0xd1), char(0xdd), char(0xc9), char(0xc5), ' ', char(0xc4), char(0xc1), char(0xce), char(0xce), char(0xd9), char(0xc5) };
    const char* koi8r_cnext;
    wchar_t buf[16];
    const wchar_t* buf_cnext;
    wchar_t* buf_next;
    char out[16];
    char* out_next;

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_koi8r.in(state, koi8r, koi8r + strlen(koi8r), koi8r_cnext, buf, buf + 1, buf_next)
    );
    ASSERT_EQ(&koi8r[1], koi8r_cnext);
    ASSERT_EQ(&buf[1], buf_next);

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_koi8r.in(state, koi8r, koi8r + strlen(koi8r), koi8r_cnext, buf, buf + IRESEARCH_COUNTOF(buf), buf_next)
    );

    ASSERT_EQ(koi8r + strlen(koi8r), koi8r_cnext);
    ASSERT_EQ(buf + IRESEARCH_COUNTOF(buf) -1, buf_next); // FIXME TODO Boost incorrectly sets buf_next, remove -1

    ASSERT_EQ(
      std::codecvt_base::result::partial,
      cvt_cp1251.out(state, buf, buf + IRESEARCH_COUNTOF(buf), buf_cnext, out, out + 1, out_next)
    );
    ASSERT_EQ(&buf[1], buf_cnext);
    ASSERT_EQ(&out[1], out_next);

    for (size_t i = 0, count = 1; i < count; ++i) {
      ASSERT_EQ(cp1251[i], out[i]);
    }

    ASSERT_EQ(
      std::codecvt_base::result::ok,
      cvt_cp1251.out(state, buf, buf + IRESEARCH_COUNTOF(buf), buf_cnext, out, out + IRESEARCH_COUNTOF(out), out_next)
    );

    ASSERT_EQ(buf + IRESEARCH_COUNTOF(buf), buf_cnext);
    ASSERT_EQ(out + IRESEARCH_COUNTOF(out), out_next);

    for (size_t i = 0, count = IRESEARCH_COUNTOF(out); i < count; ++i) {
      ASSERT_EQ(cp1251[i], out[i]);
    }
  }
}

TEST_F(LocaleUtilsTestSuite, test_locale_info) {
  {
    std::locale locale = std::locale::classic();

    ASSERT_EQ(std::string(""), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("us-ascii"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("C"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("C"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale(nullptr);

    ASSERT_EQ(std::string(""), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("us-ascii"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("C"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("C"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale("*");

    ASSERT_EQ(std::string(""), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("us-ascii"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("*"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("*"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale("C");

    ASSERT_EQ(std::string(""), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("us-ascii"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("C"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("C"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale("en");

    ASSERT_EQ(std::string(""), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("us-ascii"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("en"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("en"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale("en_US");

    ASSERT_EQ(std::string("US"), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("us-ascii"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("en"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("en_US"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale("en_US.UTF-8");

    ASSERT_EQ(std::string("US"), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("utf-8"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("en"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("en_US.utf-8"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale("ru_RU.KOI8-R");

    ASSERT_EQ(std::string("RU"), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("koi8-r"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("ru"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("ru_RU.koi8-r"), iresearch::locale_utils::name(locale));
  }

  {
    std::locale locale = iresearch::locale_utils::locale("InvalidString");

    ASSERT_EQ(std::string(""), iresearch::locale_utils::country(locale));
    ASSERT_EQ(std::string("us-ascii"), iresearch::locale_utils::encoding(locale));
    ASSERT_EQ(std::string("invalidstring"), iresearch::locale_utils::language(locale));
    ASSERT_EQ(std::string("invalidstring"), iresearch::locale_utils::name(locale));
  }
}

TEST_F(LocaleUtilsTestSuite, test_locale_num_put) {
  auto c = irs::locale_utils::locale("C");
  auto de = irs::locale_utils::locale("de");
  auto en = irs::locale_utils::locale("en.IBM-943"); // EBCDIC
  auto ru = irs::locale_utils::locale("ru_RU.KOI8-R");

  // bool (char)
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << "|" << std::boolalpha << false
           << "|" << std::boolalpha << true
           << "|" << std::noboolalpha << std::dec << std::uppercase << false
           << "|" << std::noboolalpha << std::hex << std::uppercase << false
           << "|" << std::noboolalpha << std::oct << std::uppercase << false
           << "|" << std::noboolalpha << std::dec << std::uppercase << true
           << "|" << std::noboolalpha << std::hex << std::uppercase << true
           << "|" << std::noboolalpha << std::oct << std::uppercase << true
           << "|" << std::noboolalpha << std::dec << std::nouppercase << false
           << "|" << std::noboolalpha << std::hex << std::nouppercase << false
           << "|" << std::noboolalpha << std::oct << std::nouppercase << false
           << "|" << std::noboolalpha << std::dec << std::nouppercase << true
           << "|" << std::noboolalpha << std::hex << std::nouppercase << true
           << "|" << std::noboolalpha << std::oct << std::nouppercase << true
           << "|" << std::showbase << std::showpos << std::internal << std::boolalpha << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::internal << std::boolalpha << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::internal << std::noboolalpha << std::dec << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::internal << std::noboolalpha << std::hex << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::internal << std::noboolalpha << std::oct << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::internal << std::noboolalpha << std::dec << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::internal << std::noboolalpha << std::hex << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::internal << std::noboolalpha << std::oct << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::left << std::boolalpha << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::left << std::boolalpha << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::left << std::noboolalpha << std::dec << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::left << std::noboolalpha << std::hex << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::left << std::noboolalpha << std::oct << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::left << std::noboolalpha << std::dec << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::left << std::noboolalpha << std::hex << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::left << std::noboolalpha << std::oct << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::right << std::boolalpha << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::right << std::boolalpha << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::right << std::noboolalpha << std::dec << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::right << std::noboolalpha << std::hex << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::right << std::noboolalpha << std::oct << std::setw(10) << false
           << "|" << std::showbase << std::showpos << std::right << std::noboolalpha << std::dec << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::right << std::noboolalpha << std::hex << std::setw(10) << true
           << "|" << std::showbase << std::showpos << std::right << std::noboolalpha << std::oct << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::internal << std::boolalpha << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::internal << std::boolalpha << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::internal << std::noboolalpha << std::dec << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::internal << std::noboolalpha << std::hex << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::internal << std::noboolalpha << std::oct << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::internal << std::noboolalpha << std::dec << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::internal << std::noboolalpha << std::hex << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::internal << std::noboolalpha << std::oct << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::left << std::boolalpha << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::left << std::boolalpha << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::left << std::noboolalpha << std::dec << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::left << std::noboolalpha << std::hex << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::left << std::noboolalpha << std::oct << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::left << std::noboolalpha << std::dec << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::left << std::noboolalpha << std::hex << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::left << std::noboolalpha << std::oct << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::right << std::boolalpha << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::right << std::boolalpha << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::right << std::noboolalpha << std::dec << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::right << std::noboolalpha << std::hex << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::right << std::noboolalpha << std::oct << std::setw(10) << false
           << "|" << std::showbase << std::noshowpos << std::right << std::noboolalpha << std::dec << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::right << std::noboolalpha << std::hex << std::setw(10) << true
           << "|" << std::showbase << std::noshowpos << std::right << std::noboolalpha << std::oct << std::setw(10) << true
           << "|" << std::endl;
    }

    ASSERT_EQ(std::string("|false|true|0|0|0|1|1|1|0|0|0|1|1|1|     false|      true|+        0|+        0|+        0|+        1|+      0x1|+       01|false     |true      |+0        |+0        |+0        |+1        |+0x1      |+01       |     false|      true|        +0|        +0|        +0|        +1|      +0x1|       +01|     false|      true|         0|         0|         0|         1|0x       1|        01|false     |true      |0         |0         |0         |1         |0x1       |01        |     false|      true|         0|         0|         0|         1|       0x1|        01|\n"), c_out.str());
    ASSERT_EQ(std::string("|false|true|0|0|0|1|1|1|0|0|0|1|1|1|     false|      true|+        0|+        0|+        0|+        1|+      0x1|+       01|false     |true      |+0        |+0        |+0        |+1        |+0x1      |+01       |     false|      true|        +0|        +0|        +0|        +1|      +0x1|       +01|     false|      true|         0|         0|         0|         1|0x       1|        01|false     |true      |0         |0         |0         |1         |0x1       |01        |     false|      true|         0|         0|         0|         1|       0x1|        01|\n"), de_out.str());
    ASSERT_EQ(std::string("|false|true|0|0|0|1|1|1|0|0|0|1|1|1|     false|      true|+        0|+        0|+        0|+        1|+      0x1|+       01|false     |true      |+0        |+0        |+0        |+1        |+0x1      |+01       |     false|      true|        +0|        +0|        +0|        +1|      +0x1|       +01|     false|      true|         0|         0|         0|         1|0x       1|        01|false     |true      |0         |0         |0         |1         |0x1       |01        |     false|      true|         0|         0|         0|         1|       0x1|        01|\n"), en_out.str());
    ASSERT_EQ(std::string("|false|true|0|0|0|1|1|1|0|0|0|1|1|1|     false|      true|+        0|+        0|+        0|+        1|+      0x1|+       01|false     |true      |+0        |+0        |+0        |+1        |+0x1      |+01       |     false|      true|        +0|        +0|        +0|        +1|      +0x1|       +01|     false|      true|         0|         0|         0|         1|0x       1|        01|false     |true      |0         |0         |0         |1         |0x1       |01        |     false|      true|         0|         0|         0|         1|       0x1|        01|\n"), ru_out.str());
  }

  // long
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << sizeof(long)
           << "|" << std::dec << std::uppercase << (long)(-1234)
           << "|" << std::hex << std::uppercase << (long)(-1234)
           << "|" << std::oct << std::uppercase << (long)(-1234)
           << "|" << std::dec << std::uppercase << (long)(0)
           << "|" << std::hex << std::uppercase << (long)(0)
           << "|" << std::oct << std::uppercase << (long)(0)
           << "|" << std::dec << std::uppercase << (long)(1234)
           << "|" << std::hex << std::uppercase << (long)(1234)
           << "|" << std::oct << std::uppercase << (long)(1234)
           << "|" << std::dec << std::nouppercase << (long)(-1234)
           << "|" << std::hex << std::nouppercase << (long)(-1234)
           << "|" << std::oct << std::nouppercase << (long)(-1234)
           << "|" << std::dec << std::nouppercase << (long)(0)
           << "|" << std::hex << std::nouppercase << (long)(0)
           << "|" << std::oct << std::nouppercase << (long)(0)
           << "|" << std::dec << std::nouppercase << (long)(1234)
           << "|" << std::hex << std::nouppercase << (long)(1234)
           << "|" << std::oct << std::nouppercase << (long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (long)(1234)
           << "|" << std::endl;
    }

    if (4 == sizeof(long)) {
      ASSERT_EQ(std::string("4|-1234|FFFFFB2E|37777775456|0|0|0|1234|4D2|2322|-1234|fffffb2e|37777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffb2e|+037777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffb2e|+037777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffb2e|+037777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffb2e|037777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), c_out.str());
      ASSERT_EQ(std::string("4|-1234|FFFFFB2E|37777775456|0|0|0|1234|4D2|2322|-1234|fffffb2e|37777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffb2e|+037777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffb2e|+037777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffb2e|+037777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffb2e|037777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), de_out.str());
      ASSERT_EQ(std::string("4|-1234|FFFFFB2E|37777775456|0|0|0|1234|4D2|2322|-1234|fffffb2e|37777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffb2e|+037777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffb2e|+037777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffb2e|+037777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffb2e|037777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), en_out.str());
      ASSERT_EQ(std::string("4|-1234|FFFFFB2E|37777775456|0|0|0|1234|4D2|2322|-1234|fffffb2e|37777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffb2e|+037777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffb2e|+037777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffb2e|+037777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffb2e|037777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffb2e|037777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), ru_out.str());
    } else {
      ASSERT_EQ(std::string("8|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), c_out.str());
      ASSERT_EQ(std::string("8|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), de_out.str());
      ASSERT_EQ(std::string("8|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), en_out.str());
      ASSERT_EQ(std::string("8|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), ru_out.str());
    }
  }

  // long long
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << "|" << std::dec << std::uppercase << (long long)(-1234)
           << "|" << std::hex << std::uppercase << (long long)(-1234)
           << "|" << std::oct << std::uppercase << (long long)(-1234)
           << "|" << std::dec << std::uppercase << (long long)(0)
           << "|" << std::hex << std::uppercase << (long long)(0)
           << "|" << std::oct << std::uppercase << (long long)(0)
           << "|" << std::dec << std::uppercase << (long long)(1234)
           << "|" << std::hex << std::uppercase << (long long)(1234)
           << "|" << std::oct << std::uppercase << (long long)(1234)
           << "|" << std::dec << std::nouppercase << (long long)(-1234)
           << "|" << std::hex << std::nouppercase << (long long)(-1234)
           << "|" << std::oct << std::nouppercase << (long long)(-1234)
           << "|" << std::dec << std::nouppercase << (long long)(0)
           << "|" << std::hex << std::nouppercase << (long long)(0)
           << "|" << std::oct << std::nouppercase << (long long)(0)
           << "|" << std::dec << std::nouppercase << (long long)(1234)
           << "|" << std::hex << std::nouppercase << (long long)(1234)
           << "|" << std::oct << std::nouppercase << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (long long)(-1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (long long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (long long)(1234)
           << "|" << std::endl;
    }

    ASSERT_EQ(std::string("|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), c_out.str());
    ASSERT_EQ(std::string("|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), de_out.str());
    ASSERT_EQ(std::string("|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), en_out.str());
    ASSERT_EQ(std::string("|-1234|FFFFFFFFFFFFFB2E|1777777777777777775456|0|0|0|1234|4D2|2322|-1234|fffffffffffffb2e|1777777777777777775456|0|0|0|1234|4d2|2322|-     1234|+0xfffffffffffffb2e|+01777777777777777775456|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|-1234     |+0xfffffffffffffb2e|+01777777777777777775456|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |     -1234|+0xfffffffffffffb2e|+01777777777777777775456|        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|-     1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|0x     4d2|     02322|-1234     |0xfffffffffffffb2e|01777777777777777775456|0         |0         |0         |1234      |0x4d2     |02322     |     -1234|0xfffffffffffffb2e|01777777777777777775456|         0|         0|         0|      1234|     0x4d2|     02322|\n"), ru_out.str());
  }

  // unsigned long
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << "|" << std::dec << std::uppercase << (unsigned long)(0)
           << "|" << std::hex << std::uppercase << (unsigned long)(0)
           << "|" << std::oct << std::uppercase << (unsigned long)(0)
           << "|" << std::dec << std::uppercase << (unsigned long)(1234)
           << "|" << std::hex << std::uppercase << (unsigned long)(1234)
           << "|" << std::oct << std::uppercase << (unsigned long)(1234)
           << "|" << std::dec << std::nouppercase << (unsigned long)(0)
           << "|" << std::hex << std::nouppercase << (unsigned long)(0)
           << "|" << std::oct << std::nouppercase << (unsigned long)(0)
           << "|" << std::dec << std::nouppercase << (unsigned long)(1234)
           << "|" << std::hex << std::nouppercase << (unsigned long)(1234)
           << "|" << std::oct << std::nouppercase << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (unsigned long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (unsigned long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (unsigned long)(1234)
           << "|" << std::endl;
    }

    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), c_out.str());
    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), de_out.str());
    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), en_out.str());
    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), ru_out.str());
  }

  // unsigned long long (char)
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << "|" << std::dec << std::uppercase << (unsigned long long)(0)
           << "|" << std::hex << std::uppercase << (unsigned long long)(0)
           << "|" << std::oct << std::uppercase << (unsigned long long)(0)
           << "|" << std::dec << std::uppercase << (unsigned long long)(1234)
           << "|" << std::hex << std::uppercase << (unsigned long long)(1234)
           << "|" << std::oct << std::uppercase << (unsigned long long)(1234)
           << "|" << std::dec << std::nouppercase << (unsigned long long)(0)
           << "|" << std::hex << std::nouppercase << (unsigned long long)(0)
           << "|" << std::oct << std::nouppercase << (unsigned long long)(0)
           << "|" << std::dec << std::nouppercase << (unsigned long long)(1234)
           << "|" << std::hex << std::nouppercase << (unsigned long long)(1234)
           << "|" << std::oct << std::nouppercase << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::dec << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::hex << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::oct << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::left << std::dec << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::hex << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::oct << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::showpos << std::right << std::dec << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::hex << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::oct << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::dec << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::hex << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::oct << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::dec << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::hex << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::oct << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (unsigned long long)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::dec << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::hex << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::oct << std::setw(10) << (unsigned long long)(1234)
           << "|" << std::endl;
    }

    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), c_out.str());
    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), de_out.str());
    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), en_out.str());
    ASSERT_EQ(std::string("|0|0|0|1234|4D2|2322|0|0|0|1234|4d2|2322|+        0|+        0|+        0|+     1234|+    0x4d2|+    02322|+0        |+0        |+0        |+1234     |+0x4d2    |+02322    |        +0|        +0|        +0|     +1234|    +0x4d2|    +02322|         0|         0|         0|      1234|0x     4d2|     02322|0         |0         |0         |1234      |0x4d2     |02322     |         0|         0|         0|      1234|     0x4d2|     02322|\n"), ru_out.str());
  }

// GCC v4.x does not support std::defaultfloat or std::hexfloat
#if !defined(__GNUC__) || __GNUC__ > 4
  // double (char)
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (double)(-1003.1415)
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (double)(-1003.1415)
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (double)(-1003.1415)
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (double)(-1003.1415)
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (double)(-64.) // power of 2
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (double)(-64.) // power of 2
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (double)(-64.) // power of 2
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (double)(-64.) // power of 2
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (double)(0.)
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (double)(0.)
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (double)(0.)
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (double)(0.)
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (double)(32.) // power of 2
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (double)(32.) // power of 2
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (double)(32.) // power of 2
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (double)(32.) // power of 2
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (double)(1002.71828)
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (double)(1002.71828)
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (double)(1002.71828)
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (double)(1002.71828)
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (double)(-1003.1415)
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (double)(-1003.1415)
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (double)(-1003.1415)
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (double)(-1003.1415)
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (double)(-64.) // power of 2
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (double)(-64.) // power of 2
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (double)(-64.) // power of 2
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (double)(-64.) // power of 2
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (double)(0.)
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (double)(0.)
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (double)(0.)
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (double)(0.)
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (double)(32.) // power of 2
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (double)(32.) // power of 2
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (double)(32.) // power of 2
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (double)(32.) // power of 2
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (double)(1002.71828)
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (double)(1002.71828)
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (double)(1002.71828)
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::hex << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::hex << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::hex << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::hex << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::hex << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::hex << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (double)(1002.71828)
           << "|" << std::endl;
    }

    ASSERT_EQ(std::string("|-1003.1415|-1003.141500|-0X1.F5921CAC08312P+9|-1.003142E3|-64|-64.000000|-0X1P+6|-6.400000E1|0|0.000000|0X0P+0|0.000000E0|32|32.000000|0X1P+5|3.200000E1|1002.71828|1002.718280|0X1.F55BF0995AAF8P+9|1.002718E3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64.|-64.000000|-0x1.p+6|-6.400000e1|0.|0.000000|0x0.p+0|0.000000e0|32.|32.000000|0x1.p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|+        0|+ 0.000000|+   0x0p+0|+0.000000e0|+       32|+32.000000|+   0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|+0        |+0.000000 |+0x0p+0   |+0.000000e0|+32       |+32.000000|+0x1p+5   |+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|        +0| +0.000000|   +0x0p+0|+0.000000e0|       +32|+32.000000|   +0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|         0|  0.000000|0x    0p+0|0.000000e0|        32| 32.000000|0x    1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|0         |0.000000  |0x0p+0    |0.000000e0|32        |32.000000 |0x1p+5    |3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|         0|  0.000000|    0x0p+0|0.000000e0|        32| 32.000000|    0x1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|\n"), c_out.str());
    ASSERT_EQ(std::string("|-1003,1415|-1003,141500|-0X1.F5921CAC08312P+9|-1,003142E3|-64|-64,000000|-0X1P+6|-6,400000E1|0|0,000000|0X0P+0|0,000000E0|32|32,000000|0X1P+5|3,200000E1|1002,71828|1002,718280|0X1.F55BF0995AAF8P+9|1,002718E3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64.|-64,000000|-0x1.p+6|-6,400000e1|0.|0,000000|0x0.p+0|0,000000e0|32.|32,000000|0x1.p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|+        0|+ 0,000000|+   0x0p+0|+0,000000e0|+       32|+32,000000|+   0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|+0        |+0,000000 |+0x0p+0   |+0,000000e0|+32       |+32,000000|+0x1p+5   |+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|        +0| +0,000000|   +0x0p+0|+0,000000e0|       +32|+32,000000|   +0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|         0|  0,000000|0x    0p+0|0,000000e0|        32| 32,000000|0x    1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|0         |0,000000  |0x0p+0    |0,000000e0|32        |32,000000 |0x1p+5    |3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|         0|  0,000000|    0x0p+0|0,000000e0|        32| 32,000000|    0x1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|\n"), de_out.str());
    ASSERT_EQ(std::string("|-1003.1415|-1003.141500|-0X1.F5921CAC08312P+9|-1.003142E3|-64|-64.000000|-0X1P+6|-6.400000E1|0|0.000000|0X0P+0|0.000000E0|32|32.000000|0X1P+5|3.200000E1|1002.71828|1002.718280|0X1.F55BF0995AAF8P+9|1.002718E3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64.|-64.000000|-0x1.p+6|-6.400000e1|0.|0.000000|0x0.p+0|0.000000e0|32.|32.000000|0x1.p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|+        0|+ 0.000000|+   0x0p+0|+0.000000e0|+       32|+32.000000|+   0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|+0        |+0.000000 |+0x0p+0   |+0.000000e0|+32       |+32.000000|+0x1p+5   |+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|        +0| +0.000000|   +0x0p+0|+0.000000e0|       +32|+32.000000|   +0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|         0|  0.000000|0x    0p+0|0.000000e0|        32| 32.000000|0x    1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|0         |0.000000  |0x0p+0    |0.000000e0|32        |32.000000 |0x1p+5    |3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|         0|  0.000000|    0x0p+0|0.000000e0|        32| 32.000000|    0x1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|\n"), en_out.str());
    ASSERT_EQ(std::string("|-1003,1415|-1003,141500|-0X1.F5921CAC08312P+9|-1,003142E3|-64|-64,000000|-0X1P+6|-6,400000E1|0|0,000000|0X0P+0|0,000000E0|32|32,000000|0X1P+5|3,200000E1|1002,71828|1002,718280|0X1.F55BF0995AAF8P+9|1,002718E3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64.|-64,000000|-0x1.p+6|-6,400000e1|0.|0,000000|0x0.p+0|0,000000e0|32.|32,000000|0x1.p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|+        0|+ 0,000000|+   0x0p+0|+0,000000e0|+       32|+32,000000|+   0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|+0        |+0,000000 |+0x0p+0   |+0,000000e0|+32       |+32,000000|+0x1p+5   |+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|        +0| +0,000000|   +0x0p+0|+0,000000e0|       +32|+32,000000|   +0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|         0|  0,000000|0x    0p+0|0,000000e0|        32| 32,000000|0x    1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|0         |0,000000  |0x0p+0    |0,000000e0|32        |32,000000 |0x1p+5    |3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|         0|  0,000000|    0x0p+0|0,000000e0|        32| 32,000000|    0x1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|\n"), ru_out.str());
  }

  // long double (char)
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << sizeof(long double)
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (long double)(-1003.1415)
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (long double)(-1003.1415)
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (long double)(-1003.1415)
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (long double)(-1003.1415)
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (long double)(-64.) // power of 2
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (long double)(-64.) // power of 2
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (long double)(-64.) // power of 2
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (long double)(-64.) // power of 2
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (long double)(0.)
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (long double)(0.)
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (long double)(0.)
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (long double)(0.)
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (long double)(32.) // power of 2
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (long double)(32.) // power of 2
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (long double)(32.) // power of 2
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (long double)(32.) // power of 2
           << "|" << std::defaultfloat << std::uppercase << std::noshowpoint << (long double)(1002.71828)
           << "|" << std::fixed        << std::uppercase << std::noshowpoint << (long double)(1002.71828)
           << "|" << std::hexfloat     << std::uppercase << std::noshowpoint << (long double)(1002.71828)
           << "|" << std::scientific   << std::uppercase << std::noshowpoint << (long double)(1002.71828)
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (long double)(-1003.1415)
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (long double)(-1003.1415)
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (long double)(-1003.1415)
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (long double)(-1003.1415)
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (long double)(-64.) // power of 2
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (long double)(-64.) // power of 2
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (long double)(-64.) // power of 2
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (long double)(-64.) // power of 2
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (long double)(0.)
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (long double)(0.)
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (long double)(0.)
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (long double)(0.)
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (long double)(32.) // power of 2
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (long double)(32.) // power of 2
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (long double)(32.) // power of 2
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (long double)(32.) // power of 2
           << "|" << std::defaultfloat << std::nouppercase << std::showpoint << (long double)(1002.71828)
           << "|" << std::fixed        << std::nouppercase << std::showpoint << (long double)(1002.71828)
           << "|" << std::hexfloat     << std::nouppercase << std::showpoint << (long double)(1002.71828)
           << "|" << std::scientific   << std::nouppercase << std::showpoint << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::hex << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::hex << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::hex << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::showpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::hex << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::defaultfloat << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::fixed        << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::hexfloat     << std::hex << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::internal << std::scientific   << std::oct << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::hex << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::defaultfloat << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::fixed        << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::hexfloat     << std::hex << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::left << std::scientific   << std::oct << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::hex << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(-1003.1415)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(-64.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(0.)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(32.) // power of 2
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::defaultfloat << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::fixed        << std::dec << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::hexfloat     << std::hex << std::setw(10) << (long double)(1002.71828)
           << "|" << std::showbase << std::noshowpos << std::noshowpoint << std::right << std::scientific   << std::oct << std::setw(10) << (long double)(1002.71828)
           << "|" << std::endl;
    }

    if (8 == sizeof(long double)) {
      ASSERT_EQ(std::string("|-1003.1415|-1003.141500|-0X1.F5921CAC08312P+9|-1.003142E3|-64|-64.000000|-0X1P+6|-6.400000E1|0|0.000000|0X0P+0|0.000000E0|32|32.000000|0X1P+5|3.200000E1|1002.71828|1002.718280|0X1.F55BF0995AAF8P+9|1.002718E3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64.|-64.000000|-0x1.p+6|-6.400000e1|0.|0.000000|0x0.p+0|0.000000e0|32.|32.000000|0x1.p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|+        0|+ 0.000000|+   0x0p+0|+0.000000e0|+       32|+32.000000|+   0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|+0        |+0.000000 |+0x0p+0   |+0.000000e0|+32       |+32.000000|+0x1p+5   |+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|        +0| +0.000000|   +0x0p+0|+0.000000e0|       +32|+32.000000|   +0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|         0|  0.000000|0x    0p+0|0.000000e0|        32| 32.000000|0x    1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|0         |0.000000  |0x0p+0    |0.000000e0|32        |32.000000 |0x1p+5    |3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|         0|  0.000000|    0x0p+0|0.000000e0|        32| 32.000000|    0x1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|\n"), c_out.str());
      ASSERT_EQ(std::string("|-1003,1415|-1003,141500|-0X1.F5921CAC08312P+9|-1,003142E3|-64|-64,000000|-0X1P+6|-6,400000E1|0|0,000000|0X0P+0|0,000000E0|32|32,000000|0X1P+5|3,200000E1|1002,71828|1002,718280|0X1.F55BF0995AAF8P+9|1,002718E3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64.|-64,000000|-0x1.p+6|-6,400000e1|0.|0,000000|0x0.p+0|0,000000e0|32.|32,000000|0x1.p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|+        0|+ 0,000000|+   0x0p+0|+0,000000e0|+       32|+32,000000|+   0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|+0        |+0,000000 |+0x0p+0   |+0,000000e0|+32       |+32,000000|+0x1p+5   |+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|        +0| +0,000000|   +0x0p+0|+0,000000e0|       +32|+32,000000|   +0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|         0|  0,000000|0x    0p+0|0,000000e0|        32| 32,000000|0x    1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|0         |0,000000  |0x0p+0    |0,000000e0|32        |32,000000 |0x1p+5    |3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|         0|  0,000000|    0x0p+0|0,000000e0|        32| 32,000000|    0x1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|\n"), de_out.str());
      ASSERT_EQ(std::string("|-1003.1415|-1003.141500|-0X1.F5921CAC08312P+9|-1.003142E3|-64|-64.000000|-0X1P+6|-6.400000E1|0|0.000000|0X0P+0|0.000000E0|32|32.000000|0X1P+5|3.200000E1|1002.71828|1002.718280|0X1.F55BF0995AAF8P+9|1.002718E3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64.|-64.000000|-0x1.p+6|-6.400000e1|0.|0.000000|0x0.p+0|0.000000e0|32.|32.000000|0x1.p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|+        0|+ 0.000000|+   0x0p+0|+0.000000e0|+       32|+32.000000|+   0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|+0        |+0.000000 |+0x0p+0   |+0.000000e0|+32       |+32.000000|+0x1p+5   |+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|        +0| +0.000000|   +0x0p+0|+0.000000e0|       +32|+32.000000|   +0x1p+5|+3.200000e1|+1002.71828|+1002.718280|+0x1.f55bf0995aaf8p+9|+1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-       64|-64.000000|-   0x1p+6|-6.400000e1|         0|  0.000000|0x    0p+0|0.000000e0|        32| 32.000000|0x    1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|-64       |-64.000000|-0x1p+6   |-6.400000e1|0         |0.000000  |0x0p+0    |0.000000e0|32        |32.000000 |0x1p+5    |3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|-1003.1415|-1003.141500|-0x1.f5921cac08312p+9|-1.003142e3|       -64|-64.000000|   -0x1p+6|-6.400000e1|         0|  0.000000|    0x0p+0|0.000000e0|        32| 32.000000|    0x1p+5|3.200000e1|1002.71828|1002.718280|0x1.f55bf0995aaf8p+9|1.002718e3|\n"), en_out.str());
      ASSERT_EQ(std::string("|-1003,1415|-1003,141500|-0X1.F5921CAC08312P+9|-1,003142E3|-64|-64,000000|-0X1P+6|-6,400000E1|0|0,000000|0X0P+0|0,000000E0|32|32,000000|0X1P+5|3,200000E1|1002,71828|1002,718280|0X1.F55BF0995AAF8P+9|1,002718E3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64.|-64,000000|-0x1.p+6|-6,400000e1|0.|0,000000|0x0.p+0|0,000000e0|32.|32,000000|0x1.p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|+        0|+ 0,000000|+   0x0p+0|+0,000000e0|+       32|+32,000000|+   0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|+0        |+0,000000 |+0x0p+0   |+0,000000e0|+32       |+32,000000|+0x1p+5   |+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|        +0| +0,000000|   +0x0p+0|+0,000000e0|       +32|+32,000000|   +0x1p+5|+3,200000e1|+1002,71828|+1002,718280|+0x1.f55bf0995aaf8p+9|+1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-       64|-64,000000|-   0x1p+6|-6,400000e1|         0|  0,000000|0x    0p+0|0,000000e0|        32| 32,000000|0x    1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|-64       |-64,000000|-0x1p+6   |-6,400000e1|0         |0,000000  |0x0p+0    |0,000000e0|32        |32,000000 |0x1p+5    |3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|-1003,1415|-1003,141500|-0x1.f5921cac08312p+9|-1,003142e3|       -64|-64,000000|   -0x1p+6|-6,400000e1|         0|  0,000000|    0x0p+0|0,000000e0|        32| 32,000000|    0x1p+5|3,200000e1|1002,71828|1002,718280|0x1.f55bf0995aaf8p+9|1,002718e3|\n"), ru_out.str());
    } else {
      ASSERT_EQ(std::string("16|-1003.1415|-1003.141500|-0XF.AC90E5604189P+6|-1.003142E3|-64|-64.000000|-0X8P+3|-6.400000E1|0|0.000000|0X0P+0|0.000000E0|32|32.000000|0X8P+2|3.200000E1|1002.71828|1002.718280|0XF.AADF84CAD57CP+6|1.002718E3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-64.|-64.000000|-0x8.p+3|-6.400000e1|0.|0.000000|0x0.p+0|0.000000e0|32.|32.000000|0x8.p+2|3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-       64|-64.000000|-   0x8p+3|-6.400000e1|+        0|+ 0.000000|+   0x0p+0|+0.000000e0|+       32|+32.000000|+   0x8p+2|+3.200000e1|+1002.71828|+1002.718280|+0xf.aadf84cad57cp+6|+1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-64       |-64.000000|-0x8p+3   |-6.400000e1|+0        |+0.000000 |+0x0p+0   |+0.000000e0|+32       |+32.000000|+0x8p+2   |+3.200000e1|+1002.71828|+1002.718280|+0xf.aadf84cad57cp+6|+1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|       -64|-64.000000|   -0x8p+3|-6.400000e1|        +0| +0.000000|   +0x0p+0|+0.000000e0|       +32|+32.000000|   +0x8p+2|+3.200000e1|+1002.71828|+1002.718280|+0xf.aadf84cad57cp+6|+1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-       64|-64.000000|-   0x8p+3|-6.400000e1|         0|  0.000000|0x    0p+0|0.000000e0|        32| 32.000000|0x    8p+2|3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-64       |-64.000000|-0x8p+3   |-6.400000e1|0         |0.000000  |0x0p+0    |0.000000e0|32        |32.000000 |0x8p+2    |3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|       -64|-64.000000|   -0x8p+3|-6.400000e1|         0|  0.000000|    0x0p+0|0.000000e0|        32| 32.000000|    0x8p+2|3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|\n"), c_out.str());
      ASSERT_EQ(std::string("16|-1003,1415|-1003,141500|-0XF.AC90E5604189P+6|-1,003142E3|-64|-64,000000|-0X8P+3|-6,400000E1|0|0,000000|0X0P+0|0,000000E0|32|32,000000|0X8P+2|3,200000E1|1002,71828|1002,718280|0XF.AADF84CAD57CP+6|1,002718E3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-64.|-64,000000|-0x8.p+3|-6,400000e1|0.|0,000000|0x0.p+0|0,000000e0|32.|32,000000|0x8.p+2|3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-       64|-64,000000|-   0x8p+3|-6,400000e1|+        0|+ 0,000000|+   0x0p+0|+0,000000e0|+       32|+32,000000|+   0x8p+2|+3,200000e1|+1002,71828|+1002,718280|+0xf.aadf84cad57cp+6|+1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-64       |-64,000000|-0x8p+3   |-6,400000e1|+0        |+0,000000 |+0x0p+0   |+0,000000e0|+32       |+32,000000|+0x8p+2   |+3,200000e1|+1002,71828|+1002,718280|+0xf.aadf84cad57cp+6|+1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|       -64|-64,000000|   -0x8p+3|-6,400000e1|        +0| +0,000000|   +0x0p+0|+0,000000e0|       +32|+32,000000|   +0x8p+2|+3,200000e1|+1002,71828|+1002,718280|+0xf.aadf84cad57cp+6|+1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-       64|-64,000000|-   0x8p+3|-6,400000e1|         0|  0,000000|0x    0p+0|0,000000e0|        32| 32,000000|0x    8p+2|3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-64       |-64,000000|-0x8p+3   |-6,400000e1|0         |0,000000  |0x0p+0    |0,000000e0|32        |32,000000 |0x8p+2    |3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|       -64|-64,000000|   -0x8p+3|-6,400000e1|         0|  0,000000|    0x0p+0|0,000000e0|        32| 32,000000|    0x8p+2|3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|\n"), de_out.str());
      ASSERT_EQ(std::string("16|-1003.1415|-1003.141500|-0XF.AC90E5604189P+6|-1.003142E3|-64|-64.000000|-0X8P+3|-6.400000E1|0|0.000000|0X0P+0|0.000000E0|32|32.000000|0X8P+2|3.200000E1|1002.71828|1002.718280|0XF.AADF84CAD57CP+6|1.002718E3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-64.|-64.000000|-0x8.p+3|-6.400000e1|0.|0.000000|0x0.p+0|0.000000e0|32.|32.000000|0x8.p+2|3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-       64|-64.000000|-   0x8p+3|-6.400000e1|+        0|+ 0.000000|+   0x0p+0|+0.000000e0|+       32|+32.000000|+   0x8p+2|+3.200000e1|+1002.71828|+1002.718280|+0xf.aadf84cad57cp+6|+1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-64       |-64.000000|-0x8p+3   |-6.400000e1|+0        |+0.000000 |+0x0p+0   |+0.000000e0|+32       |+32.000000|+0x8p+2   |+3.200000e1|+1002.71828|+1002.718280|+0xf.aadf84cad57cp+6|+1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|       -64|-64.000000|   -0x8p+3|-6.400000e1|        +0| +0.000000|   +0x0p+0|+0.000000e0|       +32|+32.000000|   +0x8p+2|+3.200000e1|+1002.71828|+1002.718280|+0xf.aadf84cad57cp+6|+1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-       64|-64.000000|-   0x8p+3|-6.400000e1|         0|  0.000000|0x    0p+0|0.000000e0|        32| 32.000000|0x    8p+2|3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|-64       |-64.000000|-0x8p+3   |-6.400000e1|0         |0.000000  |0x0p+0    |0.000000e0|32        |32.000000 |0x8p+2    |3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|-1003.1415|-1003.141500|-0xf.ac90e5604189p+6|-1.003142e3|       -64|-64.000000|   -0x8p+3|-6.400000e1|         0|  0.000000|    0x0p+0|0.000000e0|        32| 32.000000|    0x8p+2|3.200000e1|1002.71828|1002.718280|0xf.aadf84cad57cp+6|1.002718e3|\n"), en_out.str());
      ASSERT_EQ(std::string("16|-1003,1415|-1003,141500|-0XF.AC90E5604189P+6|-1,003142E3|-64|-64,000000|-0X8P+3|-6,400000E1|0|0,000000|0X0P+0|0,000000E0|32|32,000000|0X8P+2|3,200000E1|1002,71828|1002,718280|0XF.AADF84CAD57CP+6|1,002718E3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-64.|-64,000000|-0x8.p+3|-6,400000e1|0.|0,000000|0x0.p+0|0,000000e0|32.|32,000000|0x8.p+2|3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-       64|-64,000000|-   0x8p+3|-6,400000e1|+        0|+ 0,000000|+   0x0p+0|+0,000000e0|+       32|+32,000000|+   0x8p+2|+3,200000e1|+1002,71828|+1002,718280|+0xf.aadf84cad57cp+6|+1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-64       |-64,000000|-0x8p+3   |-6,400000e1|+0        |+0,000000 |+0x0p+0   |+0,000000e0|+32       |+32,000000|+0x8p+2   |+3,200000e1|+1002,71828|+1002,718280|+0xf.aadf84cad57cp+6|+1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|       -64|-64,000000|   -0x8p+3|-6,400000e1|        +0| +0,000000|   +0x0p+0|+0,000000e0|       +32|+32,000000|   +0x8p+2|+3,200000e1|+1002,71828|+1002,718280|+0xf.aadf84cad57cp+6|+1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-       64|-64,000000|-   0x8p+3|-6,400000e1|         0|  0,000000|0x    0p+0|0,000000e0|        32| 32,000000|0x    8p+2|3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|-64       |-64,000000|-0x8p+3   |-6,400000e1|0         |0,000000  |0x0p+0    |0,000000e0|32        |32,000000 |0x8p+2    |3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|-1003,1415|-1003,141500|-0xf.ac90e5604189p+6|-1,003142e3|       -64|-64,000000|   -0x8p+3|-6,400000e1|         0|  0,000000|    0x0p+0|0,000000e0|        32| 32,000000|    0x8p+2|3,200000e1|1002,71828|1002,718280|0xf.aadf84cad57cp+6|1,002718e3|\n"), ru_out.str());
    }
  }
#endif

  // const void* (char)
  {
    std::ostringstream c_out;
    std::ostringstream de_out;
    std::ostringstream en_out;
    std::ostringstream ru_out;
    std::vector<std::ostringstream*> v = { &c_out, &de_out, &en_out, &ru_out };

    c_out.imbue(c);
    de_out.imbue(de);
    en_out.imbue(en);
    ru_out.imbue(ru);

    for (auto out: v) {
      *out << "|" << std::uppercase << (const void*)(0)
           << "|" << std::uppercase << (const void*)(1234)
           << "|" << std::nouppercase << (const void*)(0)
           << "|" << std::nouppercase << (const void*)(1234)
           << "|" << std::showbase << std::showpos << std::internal << std::setw(20) << (const void*)(0)
           << "|" << std::showbase << std::showpos << std::internal << std::setw(20) << (const void*)(1234)
           << "|" << std::showbase << std::showpos << std::left << std::setw(20) << (const void*)(0)
           << "|" << std::showbase << std::showpos << std::left << std::setw(20) << (const void*)(1234)
           << "|" << std::showbase << std::showpos << std::right << std::setw(20) << (const void*)(0)
           << "|" << std::showbase << std::showpos << std::right << std::setw(20) << (const void*)(1234)
           << "|" << std::showbase << std::noshowpos << std::internal << std::setw(20) << (const void*)(0)
           << "|" << std::showbase << std::noshowpos << std::internal << std::setw(20) << (const void*)(1234)
           << "|" << std::showbase << std::noshowpos << std::left << std::setw(20) << (const void*)(0)
           << "|" << std::showbase << std::noshowpos << std::left << std::setw(20) << (const void*)(1234)
           << "|" << std::showbase << std::noshowpos << std::right << std::setw(20) << (const void*)(0)
           << "|" << std::showbase << std::noshowpos << std::right << std::setw(20) << (const void*)(1234)
           << "|" << std::endl;
    }

    ASSERT_EQ(std::string("|0000000000000000|00000000000004D2|0000000000000000|00000000000004d2|+ 0x0000000000000000|+ 0x00000000000004d2|+0x0000000000000000 |+0x00000000000004d2 | +0x0000000000000000| +0x00000000000004d2|0x  0000000000000000|0x  00000000000004d2|0x0000000000000000  |0x00000000000004d2  |  0x0000000000000000|  0x00000000000004d2|\n"), c_out.str());
    ASSERT_EQ(std::string("|0000000000000000|00000000000004D2|0000000000000000|00000000000004d2|+ 0x0000000000000000|+ 0x00000000000004d2|+0x0000000000000000 |+0x00000000000004d2 | +0x0000000000000000| +0x00000000000004d2|0x  0000000000000000|0x  00000000000004d2|0x0000000000000000  |0x00000000000004d2  |  0x0000000000000000|  0x00000000000004d2|\n"), de_out.str());
    ASSERT_EQ(std::string("|0000000000000000|00000000000004D2|0000000000000000|00000000000004d2|+ 0x0000000000000000|+ 0x00000000000004d2|+0x0000000000000000 |+0x00000000000004d2 | +0x0000000000000000| +0x00000000000004d2|0x  0000000000000000|0x  00000000000004d2|0x0000000000000000  |0x00000000000004d2  |  0x0000000000000000|  0x00000000000004d2|\n"), en_out.str());
    ASSERT_EQ(std::string("|0000000000000000|00000000000004D2|0000000000000000|00000000000004d2|+ 0x0000000000000000|+ 0x00000000000004d2|+0x0000000000000000 |+0x00000000000004d2 | +0x0000000000000000| +0x00000000000004d2|0x  0000000000000000|0x  00000000000004d2|0x0000000000000000  |0x00000000000004d2  |  0x0000000000000000|  0x00000000000004d2|\n"), ru_out.str());
  }
}

// -----------------------------------------------------------------------------
// --SECTION--                                                       END-OF-FILE
// -----------------------------------------------------------------------------