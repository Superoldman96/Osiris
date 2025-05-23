#pragma once

#include <cstdint>

#include <CS2/Panorama/CUI_3dPanel.h>
#include <Utils/FieldOffset.h>
#include <Utils/StrongTypeAlias.h>

STRONG_TYPE_ALIAS(OffsetToPortraitWorld, FieldOffset<cs2::CUI_3dPanel, cs2::CUI_3dPanel::PortraitWorld, std::int8_t>);
