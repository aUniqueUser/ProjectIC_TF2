#pragma once

#include <string>
#include <locale>
#include <codecvt>

namespace Util
{
    std::wstring ConvertUTF8ToWide(const std::string& str);
}