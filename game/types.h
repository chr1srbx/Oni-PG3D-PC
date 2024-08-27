#pragma once

enum ZoomTypes
{
    XRay,
    IRay
};

struct AnalyticsParams {
    int enum1;
    int enum2;
    int enum3;
    int enum4;
    int enum5;
    int enum6;
    int enum7;
    bool boolean1;
    void* klass1;
    int enum8;
    bool boolean2;
    int enum9;
    void* klass2;
    bool boolean3;
    int enum10;
    int integer1;
};

enum EffectType {
    None,                // none = 0
    Burning,             // burning = 1
    FireMushroom,        // fireMushroom = 2
    Disabler,            // disabler = 3
    BlackMark,           // blackMark = 4
    Dragon,              // dragon = 5
    LightningEnemies,    // lightningEnemies = 6
    DisablerEffect,      // disablerEffect = 7
    Resurrection,        // resurrection = 8
    AttrackPlayer,       // attrackPlayer = 9
    TimeTravel,          // timeTravel = 10
    LightningSelf,       // lightningSelf = 11
    RocketFly,           // rocketFly = 12
    ClearPoisons,        // clearPoisons = 13
    Charm,               // charm = 14
    VoodooSnowman,       // voodooSnowman = 15
    SniperTeleport,      // sniperTeleport = 16
    BigHead,             // bigHead = 17
    GadgetDenied,        // gadgetDenied = 18
    UltimateAbilityOn,   // ultimateAbilityOn = 19
    UltimateAbilityOff,  // ultimateAbilityOff = 20
    DamageBoost,         // damageBoost = 21
    Weakness,            // weakness = 22
    BlindBrownSand,      // blindBrownSand = 23
    LightningEffect,     // lightningEffect = 24
    SetMechPlayer,       // setMechPlayer = 25
    BlindWhiteNoise,     // blindWhiteNoise = 26
    ResetMechPlayer,     // resetMechPlayer = 27
    BlindSnow,           // blindSnow = 28
    LightningGroundEffect,// lightningGroundEffect = 29
    BlindBrownLoki,      // blindBrownLoki = 30
    BlindCyberCat,       // blindCyberCat = 31
    BlindRainbow,        // blindRainbow = 32
    BlindFlashLight,     // blindFlashLight = 33
    BlindSmoke,          // blindSmoke = 34
    BlindCartoonStars,   // blindCartoonStars = 35
    BlindBlots,          // blindBlots = 36
    BlindVeteranSniper,  // BlindVeteranSniper = 37
    AmmoSteal,           // ammoSteal = 38
    BlindDance,          // blindDance = 39
    BlindMummyAndPerfume,// blindMummyAndPerfume = 40
    BlindMummySun,       // blindMummySun = 41
    BlindRadiation,      // blindRadiation = 42
    BlindRobotInterference,// blindRobotInterference = 43
    BlindAntidote,       // blindAntidote = 44
    BlindFairytale,      // blindFairytale = 45
    BlindFullMoon,       // blindFullMoon = 46
    Heal,                // heal = 47
    BlindStormCloud,     // blindStormCloud = 48
    ElectricShock,       // electricShock = 49
    BlindCrystalDivision,// blindCrystalDivision = 50
    ConsumableAid,       // consumableAid = 51
    ConsumableArmorPlate,// consumableArmorPlate = 52
    BlindEventHorizon,   // blindEventHorizon = 53
    BlindSun,            // blindSun = 54
    BlindMadColorer,     // blindMadColorer = 55
    BlindRobotInterferenceViolet, // BlindRobotInterferenceViolet = 56
    BlindSharingan,      // blindSharingan = 57
    BlindStars,          // blindStars = 58
    BlindFirework,       // blindFirework = 59
    PortalGrenade,       // PortalGrenade = 60
    BlindGhostEpee,      // blindGhostEpee = 61
    BlindNavigationGlitch, // blindNavigationGlitch = 62
    BlindNavigationUnderwater, // blindNavigationUnderwater = 63
    BlindDreamsWarden,   // blindDreamsWarden = 64
    BlindWinterCurse,    // blindWinterCurse = 65
    BlindLightDevorer,   // blindLightDevorer = 66
    BlindNumbers,        // blindNumbers = 67
    BlindUnderwaterOverseer, // blindUnderwaterOverseer = 68
    BlindPathLighter,    // BlindPathLighter = 69
    BlindChromium,       // blindChromium = 70
    BlindScribbles,      // blindScribbles = 71
    BlindRGB,            // BlindRGB = 72
    BlindFrozen,         // BlindFrozen = 73
    MobCurse,            // MobCurse = 74
    BlindLeaves,         // BlindLeaves = 75
    BlindStainedGlass,   // BlindStainedGlass = 76
    BlindRadiationPink   // BlindRadiationPink = 77
};

enum class ItemType {
    None = 0,
    Gadgets,
    Weapons,
    Wears,
    BattleRoyaleItems,
    Skin,
    Pet,
    Graffiti
};

enum RocketType
{
    Rockets1,
    Grenade,
    Bullet,
    MegaBullet,
    Autoaim,
    Bomb,
    AutoaimBullet,
    Ball,
    GravityRocket,
    Lightning,
    AutoTarget,
    StickyBomb,
    Ghost1,
    ChargeRocket,
    ToxicBomb,
    GrenadeBouncing,
    SingularityGrenade,
    NuclearGrenade,
    StickyMine,
    Molotov,
    Drone,
    FakeBonus,
    BlackMarks,
    Firework,
    HomingGrenade,
    SlowdownGrenade,
    ControlledByJoystick,
    ChargeSingularity,
    ClusterBomb1,
    Spinner,
    BionicShield,
    Boomerang1,
    Plague,
    PortalGrenades,
    ClusterGrenadeBouncing
};


enum EventEnum
{
    ActivateMechRPC = 0,
    AddBonusAfterKillPlayerRPC = 1,
    AddForceRPC = 2,
    AddFreezerRayWithLength = 3,
    AddPaticleBazeRPC = 4,
    AddPlayerInCapturePoint = 5,
    AddScoreDuckHuntRPC = 6,
    AddWeaponAfterKillPlayerRPC = 7,
    AdvancedEffectRPC = 8,
    AdvancedEffectWithSenderRPC = 9,
    ApplyDamageRPC = 10,
    ApplyDebuffRPC = 11,
    ChargeGunAnimation = 12,
    ClearScoreCommandInFlagGameRPC = 13,
    Collide = 14,
    CountKillsCommandSynch = 15,
    CreateChestRPC = 16,
    DeactivateMechRPC = 17,
    DestroyRpc = 18,
    GetInPlayerRPC = 19,
    ShowSelectedFortNotification = 20,
    fireFlash = 21,
    GetBonusRewardRPC = 22,
    ActivateGadgetRPC = 23,
    GetDamageRPC = 24,
    RespawnRPC = 25,
    Go = 26,
    GoBazaRPC = 27,
    GoMatchRPC = 28,
    HoleRPC = 29,
    ImDeadInHungerGamesRPC = 30,
    imDeath = 31,
    ImKilledRPC = 32,
    IsVisible_RPC = 33,
    KilledByRPC = 34,
    LikeRPC = 35,
    MakeBonusRPC = 36,
    MeKillRPC = 37,
    OpponentLeftGame = 38,
    PlayDestroyEffectRpc = 39,
    PlayerEffectRPC = 40,
    PlayMusic = 41,
    PlayPortalSoundRPC = 42,
    PlayZombieAttackRPC = 43,
    PlayZombieRunRPC = 44,
    plusCountKillsCommand = 45,
    CheckActivityRPC = 46,
    HitByVehicleRPC = 47,
    ReloadGun = 48,
    RemoveBonusRPC = 49,
    RemoveBonusWithRewardRPC = 50,
    RemovePlayerInCapturePoint = 51,
    ResumeMatchRPC = 52,
    RevengeRequestRPC = 53,
    SendBuffParameters = 54,
    SendChatMessageWithIcon = 55,
    SendSystemMessegeFromFlagAddScoreRPC = 56,
    SendSystemMessegeFromFlagDroppedRPC = 57,
    SendSystemMessegeFromFlagReturnedRPC = 58,
    SetArmorVisInvisibleRPC = 59,
    setBootsRPC = 60,
    SetBotHealthRPC = 61,
    setCapeRPC = 62,
    SetCaptureRPC = 63,
    SetEnemyArmor = 64,
    SetEnemyBoots = 65,
    SetEnemyCape = 66,
    SetEnemyHat = 67,
    SetEnemyMask = 68,
    SetEnemyPet = 69,
    SetEnemySkin = 70,
    SetEnemyWeapon = 71,
    SetGadgetEffectActiveRPC = 72,
    SetGadgetesRPC = 73,
    SetHatRPC = 74,
    SetBigHeadRPC = 75,
    SetJetpackEnabledRPC = 76,
    SetJetpackParticleEnabledRPC = 77,
    SetMaskRPC = 78,
    SetMyClanTexture = 79,
    SetMySkin = 80,
    SetNickName = 81,
    SetNOCaptureRPC = 82,
    SetPixelBookID = 83,
    SetRocketActive = 84,
    SetRocketActiveWithCharge = 85,
    SetRocketStickedRPC = 86,
    SetTargetRPC = 87,
    SetVisibleFireEffectRpc = 88,
    SetWeaponRPC = 89,
    SetWeaponSkinRPC = 90,
    SetWearIsInvisibleRPC = 91,
    ShotRPC = 92,
    ShowBonuseParticleRPC = 93,
    ShowExplosion = 94,
    ShowMultyKillRPC = 95,
    SinchCapture = 96,
    SlowdownRPC = 97,
    StartFlashRPC = 98,
    StartGame = 99,
    StartMatchRPC = 100,
    StartNewRespanObjectRpc = 101,
    StartRocketRPC = 102,
    StartShootLoopRPC = 103,
    StartTurretRPC = 104,
    SynchCaptureCounter = 105,
    SynchCaptureCounterNewPlayer = 106,
    SynchGameRating = 107,
    SynchGameTimer = 108,
    SynchNamberSpawnZoneRPC = 109,
    SynchNumUpdateRPC = 110,
    SynchronizeTimeRPC = 111,
    SynchScoreCommandRPC = 112,
    SynchScoresCommandsNewPlayerRPC = 113,
    SynchScoresCommandsRPC = 114,
    SynchStartTimer = 115,
    SynhCommandRPC = 116,
    SynhCountKillsRPC = 117,
    SynhDeltaHealthRPC = 118,
    SynhHealthRPC = 119,
    SynhIsZoming = 120,
    SynhNameRPC = 121,
    SynhRanksRPC = 122,
    SynhScoreRPC = 123,
    SynhDeltaArmorRPC = 124,
    PropertyRPC = 125,
    winInHungerRPC = 126,
    SetPlayerUniqID = 127,
    SynchLivesItems = 128,
    RegisterPlayerRPC = 129,
    SetGamemodeRPC = 130,
    SetMapRPC = 131,
    StartGameRPC = 132,
    SetReadyRPC = 133,
    QuitFromSquadRPC = 134,
    ShowStartGameRPC = 135,
    StartTimerRPC = 136,
    KickPlayerRPC = 137,
    SynchCurrentCategory = 138,
    ResetVersusTimerRPC = 139,
    StartAirDropItemRPC = 140,
    MakeBetRPC = 141,
    GoTeamMatchRPC = 142,
    StartTeamMatchRPC = 143,
    SynchronizeMatchTimeRPC = 144,
    SetRocketActiveWithNumSmoke = 145,
    SynhDeathCountRPC = 146,
    GoRevengeMatchRPC = 147,
    EndRoundRPC = 148,
    SynchronizeGoTimeRPC = 149,
    SyncronizeTeamWins = 150,
    FireFlashDamagebleRPC = 151,
    SetMaxArmorAndHealthRPC = 152,
    SendEmojiRPC = 153,
    SynchGetGadgets = 154,
    SyncTramPosition = 155,
    UnregisterPlayerRPC = 156,
    SyncLastMoveTime = 157,
    RemoveTargetRPC = 158,
    AttackGateRPC = 159,
    ShotArtilleryRPC = 160,
    SetDestinationRPC = 161,
    SetEquipRPC = 162,
    ShowEndEventRPC = 163,
    ShowEndEventNotificationRPC = 164,
    PlayingInSquadRPC = 165,
    SynchCombatLevelRPC = 166,
    SendPetIdRPC = 167,
    SynchGameLeague = 168,
    ActiveChunkChangedRPC = 169,
    GetBonusRPC = 170,
    SetGliderRPC = 171,
    AddWeaponAfterBonusPreviewRPC = 172,
    RemoveWeaponPreviewRPC = 173,
    SetRoyaleAvatarRPC = 174,
    SetMapPositionSquadRPC = 175,
    PlayerInjuredRPC = 176,
    SynhHealthInjuredRPC = 177,
    PlayerInjuryHealedRPC = 178,
    SetLandingTrailRPC = 179,
    SetUserMapMarkerRPC = 180,
    RemoveUserMapMarkerRPC = 181,
    FlyOnGliderSynchRPC = 182,
    BattleRoyaleSquadMemberKilledRPC = 183,
    HealingByPlayerRPC = 184,
    PlayerInjuryHealingProgressRPC = 185,
    WinRequestRPC = 186,
    SetMyAvatar = 187,
    SetEnemyAvatar = 188,
    SetEquipTypeRPC = 189,
    SynchMinigunRotationRPC = 190,
    PlayZombieBeforeAttackRPC = 191,
    SendNewEmojiRPC = 192,
    SynchVehicleParamsRPC = 193,
    SendBattleEmojiRPC = 194,
    SynchVehicleColorRPC = 195,
    SendChangeMobRPC = 196,
    EnterInTrigger = 197,
    SynchWeaponModulesRPC = 198,
    SynchArmorModulesRPC = 199,
    SetModuleGadgetEffectActiveRPC = 200,
    CreateRocketRPC = 201,
    ShowEffectOnOtherPlayersRPC = 202,
    SetParticleToWeaponRPC = 203,
    RegenerateHealthMob = 204,
    SendKillMob = 205,
    SynhDeltaHealthFromWeaponRPC = 206,
    JumpDisableRPC = 207,
    SetPortalRPC = 208,
    ActivatePolymorphRPC = 209,
    DeactivatePolymorphRPC = 210,
    AlternativeMobAttack = 211,
    AlternativeMobShot = 212,
    DetonateKamikadze = 213,
    SetWeaponLevel = 214,
    MarkEnemy = 215,
    GetDamageToShieldRPC = 216,
    SendOnGroundEffect = 217,
    PluginRPC = 218,
    EnableTeleportEffectsRPC = 219,
    AddAmmoFromWeaponRPC = 220,
    KillerInvisiblityRPC = 221,
    SyncGadgetReflectorCoeffRPC = 222,
    SynchVipStatusRPC = 223,
    InviteToSquadRPC = 224,
    JoinSquadRPC = 225,
    InviteToSquadFailRPC = 226,
    SyncBreakableObjects = 227,
    FreeFallSynchRPC = 228,
    SyncCableCarRPC = 229,
    StartPlantingBomb = 230,
    ResetPlantingBomb = 231,
    StartDefusingBomb = 232,
    ResetDefusingBomb = 233,
    SetIsPaidTransport = 234,
    SyncOwnerTransport = 235,
    SyncCharIdRPC = 236,
    SyncTeammateRegenByMe = 237,
    BossSpawned = 238,
    NewPlayerFillSafe = 239,
    SetPlayerWantedRPC = 240,
    InitMobSpawnPoint = 241,
    SetSingularRPC = 242,
    SyncWeaponCountKills = 243
};


enum PhotonTargets
{

  All = 0,
  Others = 1,
  MasterClient = 2,
  AllBuffered = 3,
  OthersBuffered = 4,
  AllViaServer = 5,
  AllBufferedViaServer = 6,
  SeflViaServer = 7,

};
