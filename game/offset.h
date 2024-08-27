#pragma once


#include <cstdint>
#include "../includes.h"



namespace Offsets
{
    namespace UpdateFunctions
    {
        const uintptr_t player_move_cupdate = 0x10000;
        const uintptr_t weaponsoundsupdate = 0x10000;
        const uintptr_t petengineupdate = 0x10000;
        const uintptr_t turretupdateoffset = 0x10000;
        const uintptr_t playermovecdestroy = 0x10000;
        const uintptr_t weaponmanager = 0x10000;
        const uintptr_t playerscorecontroller = 0x10000;
        const uintptr_t gamemodecontrollerupdate = 0x10000;
    }

    namespace Player_Move_C {
        const uintptr_t show_xray_offset = 0x10000;
        const uintptr_t godmode1offset = 0x10000;
        const uintptr_t enablejetpackoffset = 0x10000;
        const uintptr_t sendchat = 0x10000;
        const uintptr_t makeinvisibleforsecondsrpc = 0x10000;
        const uintptr_t _shoot = 0x10000;
        const uintptr_t shoots = 0x10000;
        const uintptr_t shotpressed = 0x10000;
        const uintptr_t RailGunShot = 0x10000;
        const uintptr_t applyDamage = 0x10000;
        const uintptr_t slowDown = 0x10000;
        const uintptr_t rocket = 0x10000;
        const uintptr_t get_isShooting = 0x10000;
        const uintptr_t get_shootCheckPoint = 0x10000;
        const uintptr_t isVisibleTargetNew = 0x10000;
        const uintptr_t CanTarget = 0x10000;
        const uintptr_t IsVisibleTarget = 0x10000;
    }

    namespace PlayerScoreController {
        const uintptr_t addscore = 0x10000;
    }

    namespace PlayerDamageable {
        const uintptr_t addammofromweponline = 0x10000;
        const uintptr_t enemyto = 0x10000;
        const uintptr_t isdead = 0x10000;
    }

    namespace PetEngine {
        const uintptr_t petsethealth = 0x10000;
    }

    namespace PetInfo {
        const uintptr_t petspeedoffset = 0x10000;
        const uintptr_t petdamageoffset = 0x10000;
    }

    namespace ExperienceController {
        const uintptr_t addexperience = 0x10000;
        const uintptr_t maxlvloffset = 0x10000;
    }

    namespace PlayerEquipmentSlot {
        const uintptr_t setWeaponset = 0x10000;
    }

    namespace WeaponManager {
        const uintptr_t SetWeaponsSetUpd = 0x10000;
        const uintptr_t addweapon = 0x10000;
    }

    namespace ItemModule {
        const uintptr_t spoofModule = 0x10000;
        const uintptr_t modupoffset = 0x10000;
    }

    namespace PlaceableItemSettings {
        const uintptr_t clanenergyoffset = 0x10000;
        const uintptr_t clanparts = 0x10000;
        const uintptr_t clanparts1 = 0x10000;
        const uintptr_t upgradetime = 0x10000;
    }

    namespace SkinName {
        const uintptr_t ontriggerneter = 0x10000;
        const uintptr_t oncolliderhit = 0x10000;
    }

    namespace VIPController {
        const uintptr_t activevip = 0x10000;
    }

    namespace Rocket {
        const uintptr_t rocketUpd = 0x10000;

        namespace Field {
            const uintptr_t RocketSettings = 0x10000;
            const uintptr_t PlayermovecPtr = 0x10000;

            namespace FieldToRocketSettings {
                const uintptr_t typeFly = 0x10000;
                const uintptr_t throughWalls = 0x10000;
            }
        }
    }

    namespace FilterBadWorld {
        const uintptr_t filteroffset = 0x10000;
    }

    namespace ShopHelper {
        const uintptr_t weaponskins = 0x10000;
    }

    namespace NickNameValidator {
        const uintptr_t validatenick = 0x10000;
        const uintptr_t validatenickanalytics = 0x10000;
    }

    namespace EffectsController {
        const uintptr_t reloadoffset = 0x10000;
    }

    namespace GadgetG {
        const uintptr_t gadgetcdoffset = 0x10000;
    }

    namespace GadgetInfo {
        const uintptr_t gadgetunlock = 0x10000;
        const uintptr_t addgadgets = 0x10000;
    }

    namespace ItemPrice {
        const uintptr_t freekeysoffset = 0x10000;
    }

    namespace LobbyItem {
        const uintptr_t bundle1offset = 0x10000;
    }

    namespace ProgressUpdater {
        const uintptr_t setcurrencyoffset = 0x10000;
        const uintptr_t givearmor = 0x10000;
        const uintptr_t webinstance = 0x10000;
    }

    namespace Wear {
        const uintptr_t givewear = 0x10000;
        const uintptr_t armorindex = 0x10000;
    }

    namespace SceneManager {
        const uintptr_t loadscene = 0x10000;
    }

    namespace RoyaleCustomizationItemsManager {
        const uintptr_t addbr = 0x10000;
    }

    namespace InappBonusesController {
        const uintptr_t givepetoffset = 0x10000;
    }

    namespace GraffitiController {
        const uintptr_t graffitiinstance = 0x10000;
        const uintptr_t addgraffiti = 0x10000;
    }

    namespace PlayerCoreSettingsStorager {
        const uintptr_t PlayerCoreSettingsStoragerInstance = 0x10000;
    }

    //Photon
    namespace Photon
    {
        namespace PhotonPlayer {
            const uintptr_t set_nickname = 0x10000;
            const uintptr_t get_LocalPlayer = 0x10000;
            const uintptr_t instantiate = 0x10000;
        }
    }

    //UnityEngine
    namespace UnityEngine
    {
        namespace TextMesh
        {
            const uintptr_t textmesh = 0x10000;
        }

        namespace Component
        {
            const uintptr_t componentgettransform = 0x10000;
        }

        namespace Camera
        {
            const uintptr_t worldtoscreen = 0x10000;
            const uintptr_t getmain = 0x10000;
            const uintptr_t current = 0x10000;
        }

        namespace Transform
        {
            const uintptr_t rotate = 0x10000;
            const uintptr_t getrot = 0x10000;
            const uintptr_t inversetransformpoint = 0x10000;
            const uintptr_t getpos = 0x10000;
            const uintptr_t setpos = 0x10000;
            const uintptr_t setlocscale = 0x10000;
        }

        namespace Time
        {
            const uintptr_t timeScale = 0x10000;
        }
    }

    namespace System {
        namespace String {
            const uintptr_t ctor = 0x10000;
        }
    }
}