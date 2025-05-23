#pragma once

#include <cstdint>
#include <CS2/Panorama/CUI_3dPanel.h>

namespace cs2
{

struct CUI_Item3dPanel : CUI_3dPanel {
    using SetItemItemId = void(cs2::CUI_Item3dPanel* thisptr, const char* itemId, const char* attributes);
    using UnknownField = std::int32_t;
};

}
