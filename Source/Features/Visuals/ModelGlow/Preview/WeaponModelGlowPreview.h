#pragma once

#include <GameClient/EntitySystem/EntityHandle.h>
#include <GameClient/Panorama/UiItem3dPanel.h>
#include <Platform/Macros/FunctionAttributes.h>

template <typename HookContext>
class WeaponModelGlowPreview {
public:
    explicit WeaponModelGlowPreview(HookContext& hookContext) noexcept
        : hookContext{hookContext}
    {
    }

    void updateSceneObjectUpdaterHooks() const noexcept
    {
        hookContext.template make<ModelGlow>().updateWeaponSceneObjectUpdaterHook(previewWeapon());
        hookContext.template make<ModelGlow>().updateWeaponSceneObjectUpdaterHook(previewFlashbang());
        hookContext.template make<ModelGlow>().updateWeaponSceneObjectUpdaterHook(previewSmokeGrenade());
        hookContext.template make<ModelGlow>().updateWeaponSceneObjectUpdaterHook(previewHEGrenade());
        hookContext.template make<ModelGlow>().updateWeaponSceneObjectUpdaterHook(previewIncendiary());
    }

    void onUnload() const noexcept
    {
        hookContext.template make<WeaponModelGlow>().onUnload(previewWeapon());
        hookContext.template make<WeaponModelGlow>().onUnload(previewFlashbang());
        hookContext.template make<WeaponModelGlow>().onUnload(previewSmokeGrenade());
        hookContext.template make<WeaponModelGlow>().onUnload(previewHEGrenade());
        hookContext.template make<WeaponModelGlow>().onUnload(previewIncendiary());
    }

private:
    [[nodiscard]] [[NOINLINE]] decltype(auto) previewWeapon(cs2::CEntityHandle& handle, bool& hadHandle, const char* panelId, const char* itemId) const noexcept
    {
        auto&& entityIdentity = hookContext.template make<EntityHandle>(handle).getOrInit(
            [&hadHandle] { hadHandle = true; },
            [this, &hadHandle, panelId, itemId] {
                auto&& previewPanel = hookContext.gui().modelGlowPreviewPanel(panelId);
                auto&& portraitWorld = previewPanel.portraitWorld();
                if (hadHandle && portraitWorld.isMapLoaded()) {
                    previewPanel.template as<UiItem3dPanel>().createItem(itemId);
                    hadHandle = false;
                }
                return portraitWorld.findPreviewWeapon().baseEntity().handle();
            });
        return entityIdentity.template as<BaseWeapon>();
    }

    [[nodiscard]] decltype(auto) previewWeapon() const noexcept
    {
        return previewWeapon(state().previewWeaponHandle, state().hadPreviewWeaponHandle, "ModelGlowPreviewWeapon", "17293822569119416336");
    }

    [[nodiscard]] decltype(auto) previewFlashbang() const noexcept
    {
        return previewWeapon(state().previewFlashbangHandle, state().hadPreviewFlashbangHandle, "ModelGlowPreviewFlashbang", "17293822569102704683");
    }

    [[nodiscard]] decltype(auto) previewHEGrenade() const noexcept
    {
        return previewWeapon(state().previewHEGrenadeHandle, state().hadPreviewHEGrenadeHandle, "ModelGlowPreviewHEGrenade", "17293822569102704684");
    }

    [[nodiscard]] decltype(auto) previewSmokeGrenade() const noexcept
    {
        return previewWeapon(state().previewSmokeGrenadeHandle, state().hadPreviewSmokeGrenadeHandle, "ModelGlowPreviewSmoke", "17293822569102704685");
    }

    [[nodiscard]] decltype(auto) previewIncendiary() const noexcept
    {
        return previewWeapon(state().previewIncendiaryHandle, state().hadPreviewIncendiaryHandle, "ModelGlowPreviewIncendiary", "17293822569102704688");
    }

    [[nodiscard]] auto& state() const noexcept
    {
        return hookContext.weaponModelGlowPreviewState();
    }

    HookContext& hookContext;
};
