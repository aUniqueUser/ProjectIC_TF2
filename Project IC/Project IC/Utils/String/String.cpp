#include "String.h"

namespace Util
{
    std::wstring ConvertUTF8ToWide(const std::string &str)
    {
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
        return convert.from_bytes(str);
    }
}
