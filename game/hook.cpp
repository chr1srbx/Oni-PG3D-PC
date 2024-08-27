#include "hook.h"
#include "../unity/unity.h"
#include "../unity/Vector3.h"
#include <list>
#include "types.h"
#include "../unity/Quaternion.h"
#include "offset.h"
#include <algorithm> // for std::remove_copy_ifweaponList
#include <thread>
#include <random>
#include "MinHook.h"
#include <stdexcept>
#include "../main.h"
#include "MinHook.h"
#include "../obfString.hpp"
#include "../VMP/VMProtectSDK.h"
//#include <curl/curl.h>

uintptr_t gameAssembly = (uintptr_t)GetModuleHandle("GameAssembly.dll");

const char* curList1[] = { "GemsCurrency", "Coins", "ClanSilver", "ClanLootBoxPoints", "Coupons", "PixelPassCurrency", "RouletteAdsCurrency", "RouletteAdsSpin", "PixelBucks", "BattlePassCurrency", "CurrencyCompetitionTier1", "CurrencyCompetitionTier2" };
const char* weaponList[] = { "FirstPistol", "FirstShotgun", "UziWeapon", "Revolver", "Machingun", "MinersWeapon", "AK47", "Knife", "m16", "Eagle 1", "SPAS", "FAMAS", "Glock", "Shovel", "Hammer", "Beretta", "IronSword", "SteelAxe", "WoodenBow", "Chainsaw 2", "SteelCrossbow", "Hammer 2", "Mace 2", "Staff 2", "DoubleShotgun", "AlienGun", "m16_2", "Tree", "Fire_Axe", "SVD", "Barrett_2", "Uzi2", "Hunter_Rifle", "Bazooka", "railgun", "tesla", "grenade_launcher", "grenade_launcher2", "Bazooka_3", "GravityGun", "AUG", "katana_3", "bigbuddy", "Mauser", "Shmaiser", "Tompson", "Tompson_2", "basscannon", "SparklyBlaster", "CherryGun", "AK74", "FreezeGun", "3pl_Shotgun_3", "flowerpower_3", "Revolver4", "Scythe_3", "plazma_3", "plazma_pistol_2", "plazma_pistol_3", "Razer_3", "Flamethrower_3", "FreezeGun_0", "Minigun_3", "Barret_3", "LightSword_3", "Sword_2_3", "Staff 3", "DragonGun", "Bow_3", "Bazooka_2_3", "m79_3", "Red_Stone_3", "XM8_1", "PumpkinGun_1", "TwoBolters", "RayMinigun", "SignalPistol", "AutoShotgun", "TwoRevolvers", "SnowballGun", "SnowballMachingun", "HeavyShotgun", "Solar_Ray", "Water_Pistol", "Solar_Power_Cannon", "Water_Rifle", "Needle_Throw", "Valentine_Shotgun", "Carrot_Sword", "Easter_Bazooka", "RailRevolverBuy", "Assault_Machine_GunBuy", "Impulse_Sniper_RifleBuy", "Autoaim_RocketlauncherBuy", "PX-3000", "Sunrise", "Bastion", "DualHawks", "StormHammer", "Badcode_gun", "ElectroBlastRifle", "PlasmaShotgun", "Devostator", "Dark_Matter_Generator", "Hydra", "TacticalBow", "FutureRifle", "RapidFireRifle", "DualUzi", "LaserDiscThower", "Tesla_Cannon", "Photon_Pistol", "Fire_orb", "Hand_dragon", "Alligator", "Hippo", "Alien_Cannon", "Alien_Laser_Pistol", "Dater_Flowers", "Dater_DJ", "Dater_Arms", "Dater_Bow", "FriendsUzi", "Alien_rifle", "VACUUMIZER", "Fireworks_Launcher", "Shotgun_Pistol", "Range_Rifle", "Pit_Bull", "Tiger_gun", "Balloon_Cannon", "Mech_heavy_rifle", "Shuriken_Thrower", "BASIC_FLAMETHROWER", "snowball", "MysticOreEmitter", "Laser_Crossbow", "Nutcracker", "SPACE_RIFLE", "Icicle_Generator", "PORTABLE_DEATH_MOON", "Candy_Baton", "Hockey_stick", "Space_blaster", "mp5_gold_gift", "Dynamite_Gun_1", "Dual_shotguns_1", "Antihero_Rifle_1", "HarpoonGun_1", "Red_twins_pistols_1", "Toxic_sniper_rifle_1", "NuclearRevolver_1", "NAIL_MINIGUN_1", "DUAL_MACHETE_1", "Fighter_1", "Gas_spreader", "LaserBouncer_1", "magicbook_fireball", "magicbook_frostbeam", "magicbook_thunder", "TurboPistols_1", "Laser_Bow_1", "loud_piggy", "Trapper_1", "chainsaw_sword_1", "dark_star", "toy_bomber", "zombie_head", "mr_squido", "RocketCrossbow", "spark_shark", "power_claw", "zombie_slayer", "AcidCannon", "frank_sheepone", "Ghost_Lantern", "Semiauto_sniper", "Chain_electro_cannon", "Barier_Generator", "Demoman", "charge_rifle", "minigun_pistol", "bad_doctor_1", "dual_laser_blasters", "toxic_bane", "Charge_Cannon", "Heavy_Shocker", "ruler_sword_1", "pencil_thrower_1", "napalm_cannon", "sword_of_shadows", "dracula", "xmas_destroyer", "santa_sword", "snow_storm", "heavy_gifter", "bell_revolver", "elfs_revenge", "photon_sniper_rifle", "subzero", "mercenary", "laser_spear", "nunchuks", "double_dragon", "magicbook_love", "casanova", "romeo_and_juliette", "Q_grenade_launcher", "Q_machine_gun", "Q_electrogun", "Q_railgun", "Q_rocket_launcher", "Q_shotgun", "Q_plasma_gun", "Q_chopper", "Q_BFG", "Blade_of_Justice", "lab_eight_barrel_shotgun", "Tactical_tomahawk", "Masterpiece_musket", "Executioner", "Serious_argument", "lab_piranha", "lab_oneshot", "lab_machinegun", "lab_combatyoyo", "lab_orbital_pistol", "Defender_of_the_law", "fidget_thrower", "festive_bazooka", "thunderer", "bomber_slingshot", "future_sniper_rifle", "beast", "invader", "core_sword", "hedgehog", "third_eye", "eraser", "excalibur", "poseidon_trident", "reaper", "void_ray_rifle", "black_mamba", "chip_sword", "vampire_hunter", "mountain_wolf", "hurricane", "dino_slayer", "soulstone", "electrosphere", "prototype_s", "frozen_dragon", "special_agent", "Power_Fists", "VerticalShotgun", "astral_bow", "zeus_chain_ sword", "music_lover", "veteran", "mini_alien_spaceship", "flag_keeper", "leaders_sword", "last_christmas", "laser_assistant", "dual_cryo_pistols", "automatic_decorator", "elder_force_saber", "Champion_Mercenary", "champion_peacemaker", "adamant_laser_cannon", "Adamant_Revolver", "adamant_spear", "champion_electric_arc", "adamant_sniper_rifle", "Anti-Champion_Rifle", "Champion_Solar_Cannon", "Adamant_Bomber", "sharp_snowflake", "little_cthulhu", "magicbook_curse_spell", "airblade_spell", "magicbook_poison_spell", "magicbook_earth_spikes_spell", "magicbook_shadow_spell", "Dragon_King", "angry_pumpkin", "Steam_Knuckes", "electro_blast_pistol", "wyvern_sniper", "hero", "sly_avenger", "bright_reflector", "sakura", "deadly_beat", "killer_whale", "renegade", "demon_sword", "bolters2", "Stormtrooper_Exoskeleton", "Sniper_Exoskeleton", "demolition_exosceleton", "hitman_exoskeleton", "berserk_exoskeleton", "engineer_exoskeleton", "death_claws", "Eva", "space_desinsector", "mega_gun", "laser_revolver", "Sword_and_Shield", "last_samurai", "manga_gun", "anime_schtye", "nitrogen_spreader", "future_police_rifle", "stakegun", "alive_blaster", "plasma_cutter", "good_doctor", "devastator", "supercharged_rifle", "archangel", "manticore", "soul_thief", "multitaskers", "yin_yang", "last_hope", "Jet_hammer", "energy_drill", "Spender", "graviton", "acid_pistol", "Rhino", "antique_pistol", "lava_thrower", "Inventors_Rifle", "vandals", "revolver_sniper_rifle", "captain", "void_energy_pistol", "destruction_system", "circus_cannon", "military_grenade_launcher", "cyborg_hands", "ritual_blade", "tactical_rifle", "sparkling_eel", "alien_sniper_rifle", "neutralizer", "bone_sniper_rifle", "prehistoric_shotgun", "shamans_bow", "poison_darts", "primal_beast", "eye_of_ra", "gym_rifle", "bone_crusher", "soda_launcher", "rocket_launcher", "royale_fighter", "royale_revolver", "royale_sniper_rifle", "royale_ashbringer", "dagger_shovels", "worker_shovel", "sniper_shovel", "gold_shovel", "jet_shovel", "shover_laser", "monster_shovel", "penilizer", "fan_revolver", "football_cannon", "shovel_axe", "cursed_pirate", "Viking", "gladiator", "heart_of_volcano", "shovel_not_a_shovel", "chainsaw_shovel", "clan_legend_shovel", "shovel_road_sign", "cactus_shovel", "toy_hammer", "igniter", "infiltrator", "warmaster", "combat_slinger", "paintball_rifle", "energy_rings_exoskeleton", "particle_accelerator", "RitualRevolvers", "magicbook_Spell_of_Bats", "deadmans_rifle", "Witchunter", "industrial_nailer", "trick_and_treat", "ghost_launcher", "poisonous_vine", "johnny_p", "witch_broom", "cyber_slicer", "ricochet_rifle", "cyber_revolver", "neon_lighting", "quadruple_death", "cops_shovel", "cyber_shovel", "rocket_hand", "cyber_laser", "scull_crossbow", "shovel_hell", "sniper_cyber_module", "cops_club", "ultimatum", "lamp_revolver", "drum_rifle", "bp_flamethrower", "hand_gatling", "steamer", "gold_digger", "bow_of_spirit", "tomahawk_shovel", "sherif_shovel", "miner_shovel", "corn_launcher", "pie_thrower", "triple_musket", "demolition_gun", "ecco_hunter", "like_throver", "photo_gun", "liquid_fire", "electric_vortex", "cursed_staff", "blinder", "peppermint_guardians", "freon_gun", "shovel_ice", "frostomat", "frosty_railgun", "winter_staff", "ice_spiker", "shovel_peppermint", "total_annihilator", "torpedo_launcher", "sawed_off_shotguns", "gauss_machine_gun", "ultra_beam", "sock_bomber", "energy_assault_rifle", "shovel_alien_ice", "shovel_ice_skate", "futuristic_minigun", "sniper_ice", "gloves_of_power", "space_redeemer", "snow_blaster", "alien_bounser", "alien_shuriken", "spruce_pistols", "christmas_spirit", "ice_lightning", "ice_generator", "icecream_pistol", "whip_with_cake", "festive_guitar", "evil_snowman", "gangerbread_homezooka", "portable_gift_factory", "saturn", "venus_n_mercury", "Asteroid", "comet_sniper_rifle", "meteor_shower", "neclaces_ice_king", "Ice_Paws", "frozen_lich_bow", "gift_stitcher", "ice_king_anger", "gifted_revolvers", "yetti_spirit", "bambo", "new_year_defender", "candy_axe", "cold_silence", "proton_freezer", "coldstarter", "cyber_machinegun", "simple_cybergun", "shock", "cyber_sniper", "simple_cyberlauncher", "simple_acid_spray", "spec_ops_backup", "pixel_cola_refresher", "warden", "instigator", "storm", "semi_auto_shotgun", "stinger_3000", "airstrike_laptop", "deadly_digital_system", "night_hunter", "spec_ops_pistol", "tactical_knife", "hand_minigun", "heavy_sniper_rifle", "armadillo", "police_zapper", "temple_guardian", "healing_carp", "moon_halberd", "magic_primary", "magic_backup", "magic_melee", "magic_special", "magic_sniper", "royale_alpenstock", "agent_valentine", "lovebirds", "Serenade", "heartbreakers", "Succubus", "postman", "harpy", "runic_hammer", "blade_rifle", "arahna_bite", "medusa", "bigb_oven", "mr_mixer", "cookie_minigun", "magic_blades", "alchemic_staff", "rune_shovel", "Ðüyclops_shovel", "system_admin", "flash_drive", "disconnector", "network_streamer", "ð░ntivirus", "big_data", "cyclops_siling", "rainbow_dispenser", "rainbow_destroyer", "mister_l", "adamant_claws", "hypersound_uzi", "double_gum", "black_hole", "space_shovel", "heroic_shovel", "protector_of_peace", "portalius_wrath", "chipping_whip", "portalium_rifle", "nuclear_rifle", "deadly_umbrella", "big_bang_revolver", "acid_shotgun", "batohawk", "combat_gautlent", "spider_sense", "werewolf", "sharp_flame", "charged_injector", "garbage_rifle", "firefighter", "huge_boy", "fireman_shovel", "fatal_melter", "dual_anger", "brutal_thinner", "", "", "", "pixelgun_old", "plastic_shovel", "balloon_shovel", "block_rifle", "block_shotgun", "block_flamethrower", "plastic_rifle", "plastic_bazooka", "plastic_carabin", "cloud_launcher", "sucker_gun", "witch_doctor", "portal_cannon", "healing_staff", "laser_ray_rifle", "clockwork_cannon", "transformed_blaster", "transformed_machinegun", "witch_cauldron", "combat_darts", "throwing_spears", "alloha_boom", "professional_bow", "artifact", "ouroboros", "keen_courier", "uncertainty_emitter", "camp_leader_rifle", "knife_and_compass", "super_loudspeaker", "raccoon_with_trumpet", "butterfly_net_shovel", "guitar_shovel", "werewolf_paws", "ice_cream_thrower", "water_juice_cannon", "pop_soda", "pyro_1116", "sparkling_hydra", "tiny_resizer", "pawn_cannon", "horse_axe", "battle_rook", "inevitability", "chess_board_shovel", "royal_shovel", "checkmate", "proud_eagle", "sly_wolf", "brave_lion", "offensive_catapult", "battle_horn", "sharp_ring", "ornate_bagpipes", "pew_pew_rifle", "pixel_stream_sword", "tube_backpack", "supershot_rifle", "hyper_mega_cannon", "", "", "", "arcade_rifle", "arcade_flamethrower", "fatality_hook", "fireball_gauntlets", "anubis", "duck_hunter", "disc_battle_station", "pixel_shovel", "holy_shotgun", "aspen_spear", "dual_hunter_crossbows", "plague_purifier", "lives_oppressor", "sword_of_silence", "gravestone_shovel", "hot_greetings", "cooking_totem", "spiritual_rifle", "storm_all_seas", "huge_anchor_shovel", "hard_corn", "chef_fork_shovel", "lancelot", "galahad", "percival_n_lamorak", "mordred", "morgana", "bediver", "neutron_pulsator", "clapper_gun", "royal_marryer", "snowqueen_wand", "heroic_epee", "ice_club", "last_squeak", "fierce_pack", "mouse_scepter", "ice_chaser", "sneaky_revolver", "coal_frightener", "enchanted_butler_shovel", "golden_bros", "gangsta_shield", "double_cashback", "luxury_beats", "sniper_dude", "gems_power", "spirit_staff", "offensive_fireworks", "sharp_fans", "river_dragon", "explosive_lemonade", "stick_gong_shovel", "fire_spirit", "thunder_storm", "water_blades", "deadly_stings", "dragon_bite", "ancient_scroll", "potato_implant", "ai_pistol", "super_drill", "meteorite_fighter", "gravitator", "predatory_bush_shovel", "zap_blaster", "pew_blaster", "boom_blaster", "psionic_spores", "poisonous_grasshopper", "shrimposaur", "desert_fighter", "egg_colorizer", "hocus_pocus", "bunny_smasher", "a_killer", "carrot_crossbow", "festive_frying_pan_shovel", "carrot_on_stick_shovel", "watchy_snipy", "spiny_shooty", "pully_blasty", "chickoboom", "battle_grainthrowers", "last_cry", "", "dragon_emitter", "fate_fist", "demon_catcher", "aboard_puncher", "deadly_tale", "ninja_shovel", "moon_shovel", "sword_soul_card", "lance_soul_card", "bow_soul_card", "vertical_grip_device", "siege_mode_glove", "one_punch_glove", "treasurer", "merchant_shovel", "shell_bubbler", "tide_bracers", "call_of_sirens", "deep_ambusher", "cthulhu_legacy", "sunken_hook_shovel", "atlantis_shovel", "mooring_anchor", "heavy_drill_rifle", "rivet_gun", "submarine_drone_station", "echo_scanner", "underwater_carbine", "", "", "", "advanced_scout_rifle", "harsh_punisher", "manual_inferno", "offensive_rocket_system", "headhunter_pistols", "thunderbolt", "spear_of_war", "aphrodite_crossbow", "winged_revolver", "ferocious_poleaxe", "hermes_rod_shovel", "hydra_shovel", "cerberus", "souls_conductor", "triple_bite", "wraith_of_fire", "earth_trembler", "primal_cold", "boar_roar", "gorgon_head", "invincible_lion", "advanced_scout_rifle_l", "harsh_punisher_l", "manual_inferno_l", "offensive_rocket_system_l", "headhunter_pistols_l", "debugger", "likes_booster", "ban_hammer", "vr_blasters", "killer_chord", "invigorating_awaker", "total_planner", "money_rain", "render_station", "gun_force", "digital_pad", "graphic_shovel", "cheater_hunter", "super_fixer", "bugs_cleaner", "code_shovel", "good_code", "ambush_crocorifle", "bubble_splasher", "disguised_rifle", "surf_daggers_shovel", "sand_shovel", "enchanting_altar", "spirit_mask", "magical_boomerang", "foam_sword", "sand_tower_pistol", "watermans_rifle", "high_pressure_rifle", "sharkado", "shower_sprinkler", "star_shard", "solar_flare", "magnetic_storm", "MonsterHunterMechBody1", "ectoplasmic_grenade_launcher", "reversed_pistol", "activity_neutralizer", "pga_mirror_shovel", "dimerian_shovel", "goo_substance_rifle", "goo_substance_pistol", "goo_substance_scythe", "pga_tv", "pga_doll", "pga_gates", "pga_living_rifle", "pga_slender_touch", "pga_screaming_saw", "atomic_splitter", "detimerian_divider", "restructurer", "anomaly_concentrator", "MonsterHunterMechBody2", "MonsterHunterMechBody3", "bloq_plasma_module", "plasma_beast", "drone_station", "arma_shovel", "police_alarm_shovel", "max_cruelty", "represser", "fear_and_espair", "rude_bully", "laser_ninja", "rebel", "mobile_outpost", "outlaw_catcher", "fair_sheriff", "minigun_cyber_module", "med_surgery_module", "supply_airdrop", "battle_falcon", "super_mega_tool", "pneumatic_needle_rifle", "summon_dagger", "melter_shovel", "pg3d_flag_shovel", "frozen_heart", "eye_of_the_storm", "frosty_fangs", "combat_candy", "ho_ho_rocket", "expllosive_caramel", "candy_revolver", "elven_killer_rifle", "assassin_daggers", "farewell_volley", "mystic_potion", "siege_crossbow", "storm_poleaxes", "prophet_staff", "hammer_of_thor", "thor_shovel", "carved_paddle_shovel", "geri_n_freki", "sleipnir", "huginn", "deceitful_cheater", "cunning_flame", "harbinger_of_ragnarok", "sun_eater", "call_of_valhalla", "winged_bow", "war_horse", "glitch_machine_gun", "ideal_rocket_launcher", "noob_rifle", "evil_rubiks_cube", "super_pixel_gun", "ultimatum_shovel", "final_sentence", "piercer", "border_eraser", "deminic_crusher", "dual_beam", "ronin", "brutal_rainbow", "tomianom", "time_scythe", "cyber_cat_lantern", "laser_cat_rifle", "bomber_cat", "lab_laser_shovel", "evidence_hunter", "patrol_officer_747", "redneck_bazooka", "mayor_trophy_revolver", "pixel_cola_cans", "city_key_shovel", "police_baton_shovel", "large_machinegun", "tactical_pistol", "mammoth", "debts_collector", "godfathers_assistant", "black_label", "plan_b", "traitor", "incinerator", "saboteur", "rock_smelter", "tunnel_riveter", "complete_grinder", "drilling_railgun", "plasmatic_digger", "drill_shovel", "portalius_shovel", "giant_flytrap_shovel", "portal_rifle", "extracting_ray_pistol", "terramorphing_stone", "aerosaur_rifle", "bone_saur_sword", "heavy_spik_saur", "ritual_rifle", "tooth_of_fate", "staff_crystals_will", "spark_horn", "adventure_swords", "flat_rifle", "secret_burger", "charles", "ink_spreader", "eraser_crossbow", "pencil_spears", "bro_steamer", "sad_magnet", "anvil_pistol", "masterly_trumpet", "blot_axe", "blot_shotgun", "blot_cannon", "adventure_shovel", "flat_shovel", "mr_shovel", "veteran_rifle", "veteran_sniper_rifle", "veteran_rocket_system", "lives_harvester", "jet_dragon", "thermal_scythe", "simple_dimple", "fx_camera", "dance_rifle", "rifle_me_online", "virtual_orchestra", "sharp_chaser", "zap_katana", "cyber_lantern", "bro_rifle", "ninja_swordpad", "hype_yo_yo", "streaming_beast", "dislike", "likes_absorber", "bad_comment", "golden_button_shovel", "pop_it_shovel", "mysterious_obelisk", "ritual_embalmer", "sacred_cat_will", "sentinel", "howl_of_the_mummy", "punishing_light", "piercing_gaze_of_ra", "eternal_suns_wrath", "fair_judge", "black_obelisk", "plaguebringer", "scarab_shrine", "disturbed_sarcophagus", "royal_cobra_spirit", "pharaon_3_breath", "sentinel_shopeish_shovel", "wand_of_summoning_shovel", "hand_mummy_shovel", "block_pyramid_shovel", "ultrasonic_rifle", "electronics_burner", "hounds_rx03", "system_scorpion", "rumble", "huge_wrench_shovel", "shovel_spear_shovel", "experimental_rifle", "jet_spear", "tactical_scorcher", "siege_minigun", "thermal_mecha_knife", "disruptive_howitzer", "anti_aircraft_module", "engineering_saw_thrower", "corpuscular_revolver", "uranium_grenade_launcher", "golden_eagles", "wayfarer", "fate", "holographic_cards", "chronos_shovel", "mutation_cannon", "additional_hand_shovel", "hungry_flower_shovel", "c4_basket", "head_of_statue", "tank_turret", "space_parasite_dreadnought", "space_parasite_fighter", "alien_parasite_mothership", "bad_clown", "disturbing_balloons", "clown_chainsaw", "irradiated_smg", "mutant_fish", "spiky_limbs", "predatory_rifle", "mutant_weapon_one", "mutant_weapon_two", "splutter_weapon_one", "splutter_weapon_two", "jumper_weapon_one", "jumper_weapon_two", "hound_weapon_one", "thorn_weapon_one", "thorn_weapon_two", "supermutant_weapon_one", "automatic_injector", "antidote_missile_launcher", "purifying_shotgun", "mutant_slayer", "mutagen_neutralizer", "antidote_dropper", "power_gauntlet", "rune_buster", "ice_wyvern_horns", "runic_sentinel", "crystal_touch", "crystal_bow", "enchanted_crystal_of_ancients", "full_moon_rifle", "fireflies_blessing", "branch_of_wisdom", "eternal_light", "mirrorer", "realities_sign_shovel", "reflected_light_shovel", "otherworld_wanderer", "dark_deer_bow", "reflected_santa_sword", "combat_fireplace", "combat_candy_machine", "gift_stealer", "tricky_glance", "end_of_fairytale", "fairy_axe", "butterfly_eater", "class_bullet_rifle", "class_knight_hammer", "class_knight_shield", "class_valk_rocket", "class_lifeline_gun", "class_sara_sniper", "class_sara_shotgun", "class_saber_disk", "class_saber_katana", "class_mex_flame", "class_viktor_grenade", "handy_darts", "spirits_whisper", "makeshift_piercer", "battle_kusarigama", "temple_claws", "summoning_totem_shovel", "cloud_standard_shovel", "vortex_core", "storm_bringer", "clouds_disperser", "field_plasma_station", "still_working_windmill", "class_lifeline_healgun", "thunder_formula", "bubblegum_01", "tnt_thrower", "ak5_56", "disguised_weapon", "intelligence_swords", "controlled_drone_system", "deadly_beamer", "tnt_holder_shovel", "aliens_shredder_shovel", "elves_energy_crystal", "tricky_electrizer", "plague_spreader", "ancestors_curse", "moon_hunter_bow", "elf_heavy_crossbow", "lightbringer", "boom_bang_shovel", "plague_flame_shovel", "ice_giant_rifle", "moonblades", "eco_rifle", "solar_lens", "blacklight_pistol", "supernova_generator", "event_horizon", "eco_shovel", "crescent_moon_shovel", "unfriendly_bat", "tamagochi_revolver", "mad_colorer", "nachos_shotgun", "skateboard_shovel", "artists_tool_shovel", "shockorizer", "crescent_power", "odm_special_gear", "sharingan_vengeance", "doubled_quirk", "grenade_quirk", "magic_moon_wand_shovel", "thunder_spear_shovel", "guardian_spirit", "ghost_epee", "the_sorting_pistol", "raven_staff", "corrupted_speelbook", "additional_biting_limb", "pocket_potion_pot_shovel", "ghost_candlestick_shovel", "transforming_rifle", "monkey_pirate", "holographic_hook_saber", "navigation_shotgun", "three_barrels_cannon", "ships_drowner", "cosmo_underwater_mine_shovel", "living_specimen_shovel", "deadly_shark", "wardens_trident", "nets_thrower", "tick_tock_pistol", "heavy_cone_minigun", "starfall", "dreams_warden", "snowstorm_fury", "spirits_overseer", "s_q_dominion", "x_mas_vibes_setter", "fatal_decorator", "x_mas_spirits_defender", "nature_guards_shovel", "starfall_shovel", "harsh_dragon", "armor_piercing_sniper_rifle", "leaders_butterfly", "leaders_bestfriend", "reckoning_day_sniper_rifle", "reckoning_day_pistols", "flaming_reckoning_day", "festive_eliminator", "spirit_exorcist", "wealth_spreader", "ultimate_worship", "ritual_scissors", "dark_ritual", "light_devourer", "bloody_terror_axe", "sacrificial_altar", "hunting_signs", "monster_hand", "locator", "terror_spreader", "spring_snatcher", "sticky_honey_dipper", "chefs_bounty", "cloying_eliminator", "take_your_ice_cream", "pasta_grater", "pasta_sniper_rifle", "pasta_maker", "pg_menu", "space_cycler", "anniversary_alien_blaster", "anniversary_auto_peace", "anniversary_anti_champion", "anniversary_big_buddy", "pixel_rotator", "armored_cuber_power", "cuber_railgun", "secret_pg_archives", "block_eye", "honored_golden_friend", "classic_shovel", "usher", "special_throwing_knives", "springy_shotgun", "clockwork_guardian", "dark_foreteller", "deadly_tent", "playing_pistols", "card_sharper", "scary_bunny", "accurate_bubbler", "soap_hammer", "dangerous_miner", "path_lighter", "heavy_anchor", "deadly_tide", "abyssal_altar", "underwater_whip", "underwater_piercer", "underwater_overseer", "cyber_sai", "intelligent_cyber_bow", "deathbringer", "total_dominator_2", "evasive_dominator_4", "virus_spreader", "errors_generator", "revenger", "exchanger", "rebellion_spray_paints", "rosies_diary", "sharp_butterfly_rifle", "heart_maze", "stationery_friend", "paper_assist", "friendliest_pistol", "innocent_sniper_rifle", "kitten_kutie", "neon_tommy_gun", "neon_colt_1911", "heavy_neon_gun", "danger_posy", "spiky_mortar", "heavy_evidence", "useful_suitcase", "accurate_investigator", "", "", "", "cash_gun", "rudolf_the_deer", "sooty_sniper_rifle", "chris_letters_shredder", "ninja_ice_axe", "cold_shinobi", "ice_ball_generator", "deadly_icing", "drag_sc", "dragoneer", "noble_porce", "dragon_x", "flaming_fan", "flaming_fury", "kn_arbalet", "scepter_and_power", "invig_drink", "bards_song", "gears_of_death", "kill_mech", "assas_assis", "souls_cycler", "arc_souls_dev", "pois_pier", "v_cleaner_sl", "rust_revol", "wooden_rifle", "forester", "forest_prot", "harm_sint", "high_vol_prop", "drag_wrath", "drag_heart", "glass_pain_prot", "hypno_hunter", "hypno_shackles", "hypno_hursuer", "cosmis_geode", "", "portal_ess", "party_sniper_rifle", "win_las_beam", "cosmic_wayfarer", "Itrgal_treasurer" };
const char* graffitiList[] = { "graffiti_1028", "graffiti_2028", "graffiti_3028", "graffiti_4028", "graffiti_5028","graffiti_6028", "graffiti_7028", "graffiti_8028", "graffiti_9028", "graffiti_10028","graffiti_11028", "graffiti_12028", "graffiti_13028", "graffiti_14028", "graffiti_15028","graffiti_16028", "graffiti_17028", "graffiti_18028", "graffiti_19028", "graffiti_20028","graffiti_21028", "graffiti_22028", "graffiti_23028", "graffiti_24028", "graffiti_25028","graffiti_26028", "graffiti_27028", "graffiti_28028", "graffiti_29028", "graffiti_30028","graffiti_31028", "graffiti_32028", "graffiti_33028", "graffiti_34028", "graffiti_35028","graffiti_36028", "graffiti_37028", "graffiti_38028", "graffiti_39028", "graffiti_40028","graffiti_41028", "graffiti_42028", "graffiti_43028"};
const char* skinList[] = { "Weapon1018_black_friday", "Weapon1018_climber", "Weapon1018_default", "Weapon1032_default", "Weapon1032_ice_serpent", "Weapon1032_orobro", "Weapon1041_default", "Weapon1041_yeti", "Weapon1044_default", "Weapon1044_pixel_cola", "Weapon1057_default", "Weapon1057_pumpking_rabbit", "Weapon1057_silver_wolf", "Weapon1063_default", "Weapon1063_hallorifle", "Weapon1063_mini_game", "Weapon1065_default", "Weapon1065_flammable_backpack", "Weapon1068_default", "Weapon1068_digital_pumpkin", "Weapon1069_crystal_cycler", "Weapon1069_default", "Weapon1069_demons_soul", "Weapon1077_default", "Weapon1077_pro_version", "Weapon1087_caution_wild_deer", "Weapon1087_default", "Weapon1089_default", "Weapon1089_north_pole_crusader", "Weapon1110_default", "Weapon1110_spooktober", "Weapon1111_default", "Weapon1111_poison_vein", "Weapon1112_default", "Weapon1112_zombie", "Weapon1125_default", "Weapon1125_ice_dragon_cult", "Weapon1135_default", "Weapon1135_three_eyed_pumpking", "Weapon1137_default", "Weapon1137_love_implant", "Weapon1144_default", "Weapon1144_santa_pew", "Weapon1146_default", "Weapon1146_monster_slimethrower", "Weapon1153_default", "Weapon1153_neon_christmas", "Weapon115_default", "Weapon115_Gold", "Weapon1167_default", "Weapon1167_soul_catcher", "Weapon1169_default", "Weapon1169_winter_fox", "Weapon1172_default", "Weapon1172_pumpkin_shogun", "Weapon1172_soul_of_winter", "Weapon1177_default", "Weapon1177_holy_punch", "Weapon1177_millitary_supply", "Weapon1195_default", "Weapon1195_icicle", "Weapon1195_living_specimen", "Weapon1203_broken_heart", "Weapon1203_default", "Weapon1203_ice_dragon_cult", "Weapon1208_default", "Weapon1208_happy_deers", "Weapon1209_default", "Weapon1209_mecha", "Weapon1210_black_dragon_bite", "Weapon1210_default", "Weapon1214_default", "Weapon1214_сold_breath", "Weapon1216_default", "Weapon1216_grizzly", "Weapon1224_default", "Weapon1224_mecha", "Weapon1231_default", "Weapon1231_jolly", "Weapon1232_santa_list", "Weapon1234_default", "Weapon1234_spooky_hunter", "Weapon1254_default", "Weapon1254_millitary_supply", "Weapon1264_default", "Weapon1264_irradiated", "Weapon1265_default", "Weapon1265_scary_news", "Weapon1269_default", "Weapon1269_mecha", "Weapon127_default", "Weapon127_Gold", "Weapon1284_default", "Weapon1284_night_tempest", "Weapon1286_cristmas_cook", "Weapon1286_default", "Weapon1287_default", "Weapon1287_goth", "Weapon1287_mecha", "Weapon1290_christmas_light", "Weapon1290_default", "Weapon1294_default", "Weapon1294_sckeleton", "Weapon1300_bloody_order", "Weapon1300_default", "Weapon1305_default", "Weapon1305_vummy_again", "Weapon1323_brain_eater", "Weapon1323_default", "Weapon1338_default", "Weapon1338_millitary_supply", "Weapon133_default", "Weapon133_Gold", "Weapon1341_default", "Weapon1341_demon_eye", "Weapon1355_default", "Weapon1355_irradiated", "Weapon1407_default", "Weapon1407_winter_holiday", "Weapon1411_default", "Weapon1411_nuclear_reactor", "Weapon1416_crystal_dislike", "Weapon1416_default", "Weapon1416_nuclear_reactor", "Weapon1422_default", "Weapon1422_santas_deer", "Weapon1428_default", "Weapon1428_сarousel", "Weapon1434_default", "Weapon1434_mummy", "Weapon1435_default", "Weapon1435_frozen_king", "Weapon1448_christmas_tree", "Weapon1448_default", "Weapon1449_default", "Weapon1449_frozen", "Weapon1455_default", "Weapon1455_train", "Weapon1462_antidote", "Weapon1462_default", "Weapon1478_default", "Weapon1478_rafflesia", "Weapon1490_default", "Weapon1490_one_aloner", "Weapon1492_default", "Weapon1492_surgeon", "Weapon1493_default", "Weapon1493_pixel_cola", "Weapon1505_default", "Weapon1505_eternal_night", "Weapon1506_default", "Weapon1506_princess", "Weapon1533_bloody_web", "Weapon1533_default", "Weapon1534_ancient_dragon", "Weapon1534_default", "Weapon1546_altered_ak_5_56", "Weapon1546_default", "Weapon1547_altered_disguised_weapon", "Weapon1547_default", "Weapon1555_default", "Weapon1555_destruction_preader", "Weapon1556_black_dragon_curse", "Weapon1556_default", "Weapon17_altered_fast_death", "Weapon17_default", "Weapon1_default", "Weapon1_halloween", "Weapon220_default", "Weapon220_fishbone", "Weapon220_Gold", "Weapon220_neon", "Weapon221_alligator", "Weapon221_default", "Weapon221_techno", "Weapon224_default", "Weapon224_Gold", "Weapon224_overhited", "Weapon224_transformer", "Weapon25_default", "Weapon25_mythical_power", "Weapon281_bone", "Weapon281_cyborg", "Weapon281_default", "Weapon281_green_dragon", "Weapon281_mythical_power", "Weapon293_blocks", "Weapon293_default", "Weapon293_portalium_blaster", "Weapon293_reactor", "Weapon308_default", "Weapon308_Gold", "Weapon339_cyber_necromancy", "Weapon339_default", "Weapon339_medieval", "Weapon339_paladin", "Weapon345_altered_space_rifle", "Weapon345_default", "Weapon374_default", "Weapon374_Gold", "Weapon386_default", "Weapon386_ice_dragon_cult", "Weapon392_default", "Weapon392_mythical_power", "Weapon399_default", "Weapon399_emperor", "Weapon399_modified", "Weapon399_runes", "Weapon411_black_friday", "Weapon411_default", "Weapon411_insidious", "Weapon413_default", "Weapon413_Gold", "Weapon421_default", "Weapon421_Gold", "Weapon438_default", "Weapon438_Gold", "Weapon444_Clown", "Weapon444_default", "Weapon444_Gold", "Weapon444_RedSkull", "Weapon533_default", "Weapon533_Resort", "Weapon544_default", "Weapon544_mythical_power", "Weapon552_default", "Weapon552_mythical_power", "Weapon564_Chrome", "Weapon564_default", "Weapon564_Predator", "Weapon564_Tropic", "Weapon613_default", "Weapon613_enchanted", "Weapon613_from_the_ruins", "Weapon613_Gold", "Weapon613_neon", "Weapon613_reactor", "Weapon615_default", "Weapon615_jack_the _umpkin", "Weapon625_chamomile", "Weapon625_default", "Weapon625_hype", "Weapon625_samurai", "Weapon640_default", "Weapon640_icicle", "Weapon640_Monster", "Weapon640_Techno", "Weapon654_default", "Weapon654_frozen_candy", "Weapon65_default", "Weapon65_one_dragon_story", "Weapon667_black_friday", "Weapon667_default", "Weapon679_default", "Weapon679_spooky_laser", "Weapon681_default", "Weapon681_military", "Weapon681_relic", "Weapon681_severe_caramel", "Weapon681_supercharged", "Weapon687_crystal_anti_champion", "Weapon687_decorated_pruce", "Weapon687_default", "Weapon687_Neon", "Weapon687_Steampunk", "Weapon687_Watermelon", "Weapon688_altered_champion_solar_cannon", "Weapon688_default", "Weapon688_electro_pine", "Weapon707_default", "Weapon707_jack_the_orac", "Weapon711_default", "Weapon711_santas_helper", "Weapon712_default", "Weapon712_old_clock", "Weapon714_bad_elf", "Weapon714_default", "Weapon720_default", "Weapon720_Gold", "Weapon721_black_dragon_revolver", "Weapon721_default", "Weapon725_default", "Weapon725_Gold", "Weapon725_laser", "Weapon725_lava_spirit", "Weapon725_necromancer", "Weapon727_default", "Weapon727_Gold", "Weapon737_burning", "Weapon737_default", "Weapon737_druid", "Weapon737_Scarab", "Weapon751_default", "Weapon751_ice_dragon_cult", "Weapon752_cosmus", "Weapon752_default", "Weapon752_prehistoric", "Weapon755_Bombardier", "Weapon755_default", "Weapon759_Code", "Weapon759_default", "Weapon759_Mutant", "Weapon764_default", "Weapon764_Gold", "Weapon769_default", "Weapon769_dragons_fury", "Weapon770_default", "Weapon770_ice_dragon_cult", "Weapon778_default", "Weapon778_packed", "Weapon77_default", "Weapon77_Gold", "Weapon77_mythical_power", "Weapon782_candy_factory", "Weapon782_default", "Weapon782_snowman", "Weapon790_default", "Weapon790_match_inviter", "Weapon791_default", "Weapon791_super_bowl_fan", "Weapon792_default", "Weapon792_super_bowl_cannon", "Weapon795_dead_eye", "Weapon795_default", "Weapon795_winter_rune", "Weapon809_default", "Weapon809_xmas_energy", "Weapon811_default", "Weapon811_diner", "Weapon811_snowman", "Weapon82_cheese", "Weapon82_chess", "Weapon82_default", "Weapon82_egypt", "Weapon834_christmas", "Weapon834_default", "Weapon834_nuclear_reactor", "Weapon834_pumpkin_destoyer", "Weapon865_default", "Weapon865_toy", "Weapon895_default", "Weapon895_krampus_soul", "Weapon895_pumpking_king", "Weapon895_robot_head", "Weapon898_black_armor_stitcher", "Weapon898_default", "Weapon906_default", "Weapon906_snow_blower", "Weapon916_asimov", "Weapon916_default", "Weapon916_frosty", "Weapon917_asimov", "Weapon917_default", "Weapon918_asimov", "Weapon918_default", "Weapon918_snow_camouflage", "Weapon925_black_friday", "Weapon925_default", "Weapon928_black_friday", "Weapon928_default", "Weapon949_default", "Weapon949_monstrous_harpy", "Weapon94_black_friday", "Weapon94_default", "Weapon94_giant_bell", "Weapon94_SpacePirate", "Weapon94_Volcano", "Weapon954_default", "Weapon954_fireplace", "Weapon954_hell_oven", "Weapon957_default", "Weapon957_fortune", "Weapon957_poison", "Weapon968_default", "Weapon968_ice_dragon_cult", "Weapon972_altered_rainbow_destroyer", "Weapon972_default", "Weapon977_default", "Weapon977_nothern_lights", "Weapon982_default", "Weapon982_scourge_of_the_king", "Weapon987_default", "Weapon987_mecha", "Weapon991_default", "Weapon991_fenfir", "Weapon999_default", "Weapon999_dual_xmas", "Weapon999_millitary_supply", "Weapon1564_default", "Weapon1564_gemini_constellation", "Weapon447_aries_constellation", "Weapon447_default", "Weapon1046_default", "Weapon1046_pisces_constellation", "Weapon222_default", "Weapon222_sagittarius_constellation", "Weapon1565_default", "Weapon1565_libra_constellation", "Weapon1440_default", "Weapon1440_ultrasounding_rifle", "Weapon1000_brutal_sounder", "Weapon1000_default", "Weapon706_default", "Weapon706_pband_beat", "Weapon189_default", "Weapon189_true_fan_shotgun", "Weapon669_pband_fans_sword", "Weapon669_default", "Weapon1069_legendary_bike", "Weapon1374_default", "Weapon1374_dragon_of_doom", "Weapon1544_default", "Weapon1544_fire_team_no1", "Weapon1356_default", "Weapon1356_sakura", "Weapon1580_default", "Weapon1580_dragons_wrath", "Weapon1588_corrupred_raven_staff", "Weapon1588_default", "Weapon1587_corrupted_sorting_pistol", "Weapon1587_default", "Weapon1021_default", "Weapon1021_enchanted_healing_staff", "Weapon1109_default", "Weapon1109_enchanted_snow_queen_wand", "Weapon132_default", "Weapon132_enchanted_dark_mage_wand", "Weapon1596_cosmic_seas_navigation_shotgun", "Weapon1596_default", "Weapon419_deepwater_dead_star", "Weapon419_default", "Weapon116_deepwater_scythe", "Weapon116_default", "Weapon1595_cosmic_seas_navigation_shotgun", "Weapon1595_default", "Weapon893_deepwater_comet", "Weapon893_default", "Weapon1606_default", "Weapon1606_iced_stars", "Weapon1338_christmas_ronin", "Weapon1607_default", "Weapon1607_winter_curse", "Weapon778_royal_christmas_revolver", "Weapon1259_bad_vibes_neutralizer", "Weapon1259_default", "Weapon1197_default", "Weapon1197_harsh_snowfall", "Weapon834_ultimative_snowfall", "Weapon1196_advanced_snowfall", "Weapon1196_default", "Weapon1200_bullet_snowfall", "Weapon1200_default", "Weapon1618_deadly_butterfly", "Weapon1618_default", "Weapon1619_ancient_warrior", "Weapon1619_default", "Weapon1628_default", "Weapon1628_spring_ritual", "Weapon1200_default" };
const char* royaleList[]{ "carpet_plane", "festive_glider", "glider_additional_deck", "glider_aero_suit", "glider_air_raider", "glider_air_surfboard", "glider_airborne_basket", "glider_basic", "glider_beerocopter", "glider_big_bomb", "glider_block", "glider_blogger", "glider_bloq_jetpack", "glider_boat_of_ra", "glider_bubble", "glider_cartoon_plane", "glider_copter", "glider_cybercop", "glider_d-day_pod", "glider_dragon", "glider_dragon_spirit", "glider_drill", "glider_drone", "glider_elven_cloak", "glider_flutter_pony", "glider_flying_manta", "glider_futuristic", "glider_garbage", "glider_gas_o_copter", "glider_giant_bat", "glider_giant_bubble", "glider_giant_scarab", "glider_hawk", "glider_ice_wings", "glider_icewing_dragon", "glider_inflatable_banana", "glider_judge_rocket", "glider_kite", "glider_leader", "glider_magic_broom", "glider_magic_horse", "glider_magic_wings", "glider_magical_hat", "glider_mattress", "glider_mechanical_wings", "glider_membrawinger", "glider_merchant", "glider_military", "glider_money_case", "glider_mutated_wings", "glider_neon", "glider_netrunner", "glider_pegasus", "glider_pew_pew_spaceship", "glider_phoenix", "Glider_phoenix_wings", "glider_police_cage", "glider_poncho", "glider_popit", "glider_portalius", "glider_pro_hoverboard", "glider_reponosaurus", "glider_satellite", "glider_soaring_sandals", "glider_soundman", "glider_starlet", "glider_steam", "glider_super_power", "glider_tank_for_mutant", "glider_toy_horse", "glider_transport_helicopter", "glider_ufo", "glider_vacation_baggage", "glider_valkyrie_wings", "glider_vecha_glider", "glider_vulture", "Hang_glider", "roast_turkey", "royale_glider_deer", "royale_glider_santa_chair", "royale_jet_scooter", "royale_leaf_glider", "superhero_cape", "tactical_glider", "wooden_glider", "Hat_easter", "merchant_hood", "royale_cubic_hat", "royale_cybercop_helmet", "royale_hat_alien_parasite", "royale_hat_alien_santa", "royale_hat_alpha_squad", "royale_hat_apple_with_arrow", "royale_hat_aquarium", "royale_hat_bat_santa", "royale_hat_beast", "royale_hat_bomb", "royale_hat_bow_ears", "royale_hat_boyscout", "royale_hat_boyscout_tail", "royale_hat_bravo_squad", "royale_hat_cap", "royale_hat_cap_glider", "royale_hat_chief", "royale_hat_combat_ushanka", "royale_hat_cook", "royale_hat_doctor_plague", "royale_hat_donkey", "royale_hat_donnyhelmet", "royale_hat_eared_beret", "royale_hat_ears", "royale_hat_elf", "royale_hat_feather", "royale_hat_fireman", "royale_hat_fish", "royale_hat_football", "royale_hat_gas_mask", "royale_hat_gnome_helmet", "royale_hat_guard", "royale_hat_headband", "royale_hat_hen_hat", "royale_hat_holographic_mohawk", "royale_hat_horned_helmet", "royale_hat_horse", "royale_hat_king", "royale_hat_laser_ears", "royale_hat_laurel_wreath", "royale_hat_leaders", "royale_hat_lich_crown", "royale_hat_mini_crown", "royale_hat_oakbreaker_helmet", "royale_hat_odin_helmet", "royale_hat_of_liberty", "royale_hat_of_phoenixwarrior", "royale_hat_oriental_hairstyle", "royale_hat_pan", "royale_hat_pawn_cap", "royale_hat_pigtail_helmet", "royale_hat_pilgrim", "royale_hat_pirate", "royale_hat_pixel_hero_headband", "royale_hat_psionicradar", "royale_hat_queen", "royale_hat_rangar_helmet", "royale_hat_sheriff", "royale_hat_snakes", "royale_hat_Snowdrift", "royale_hat_snowman", "royale_hat_spec_headset", "royale_hat_spec_ops_mask", "royale_hat_sword_in_the_head", "royale_hat_tours", "royale_hat_tribe_leader", "royale_hat_unicorn", "royale_hat_ushanka", "royale_hat_welding_mask", "royale_hat_zombie_cap", "avatar_ programmer", "avatar_3catspammer", "avatar_aborigine", "avatar_absolute_champion", "avatar_advanced_soldier", "avatar_adventure_dog", "avatar_agent_p", "avatar_agent_r", "avatar_agent_s", "avatar_agent_u", "avatar_agent_x", "avatar_agressivebot", "jubilee_trail", "avatar_alchemist", "avatar_alien_santa", "avatar_alpha_squad", "avatar_amazing_robert_cat", "avatar_amazon", "avatar_angler", "avatar_animator", "avatar_anubis", "avatar_aphrodite", "avatar_ares", "avatar_arma_colonel", "avatar_author", "avatar_awakened_mummy", "avatar_bad_guy", "avatar_bad_santa", "avatar_balloonman", "avatar_bandits_leader", "avatar_barbarian", "avatar_benny", "avatar_BigB", "avatar_bizarre_macho", "avatar_blockcity_detective", "avatar_blockman", "avatar_blogger", "avatar_blogger_girl", "avatar_bloq_directors", "avatar_blot", "avatar_blue_soldier", "avatar_boy_with_duck", "avatar_brave_fireman", "avatar_brave_knight", "avatar_brave_slayer", "avatar_bravo_squad", "avatar_breadboy", "avatar_bug_catcher", "avatar_camp_counselor", "avatar_campaign_girl", "avatar_captain_pixelgun", "avatar_caramel", "avatar_carrot", "avatar_cat_admirer", "avatar_cat_in_boots", "avatar_chicken_667", "avatar_chosen_crystal", "avatar_chronos", "avatar_chubby_viking", "avatar_city_fighter", "avatar_clan_legend", "avatar_colonist", "avatar_colonist_2", "avatar_community_manager", "avatar_confident_researcher", "avatar_cosmus", "avatar_crab", "avatar_cursed_pharaoh", "avatar_cyber_citizen", "avatar_cyber_girl", "avatar_cyber_hare", "avatar_cybercop", "avatar_cyborg_boar", "avatar_cyborg_rhino", "avatar_cyclop", "avatar_dance_queen", "avatar_daugter", "avatar_deep_monster", "avatar_digital_gambler", "avatar_digital_hero", "avatar_diligent_novice", "avatar_dolphin_willy", "avatar_don", "avatar_donny_dark", "avatar_dons_hand", "avatar_dr_plague", "avatar_dragon_child", "avatar_dragoon", "avatar_drilling_drone", "avatar_druid", "avatar_dwarves_king", "avatar_eared_spec_forces", "avatar_eirik_oakbreaker", "avatar_elite_marine_ops", "avatar_elite_police_drone", "avatar_elven_prince", "avatar_enchanted_nutcracker", "avatar_expert_scout", "avatar_far_future_loner", "avatar_fearless_nun", "avatar_fenrir", "avatar_final_boss", "avatar_firefly", "avatar_flat_boy", "avatar_flory", "avatar_fluff", "avatar_forgotten_astronaut", "avatar_friendlybot", "avatar_froggy", "avatar_frozen", "avatar_future_ninja", "avatar_fx_master", "avatar_game_designer", "avatar_gamer_samurai", "avatar_general_bullet", "avatar_general_green", "avatar_ghost_designer", "avatar_ghost_in_shell", "avatar_gingerbread", "avatar_glitch_player", "avatar_golden_ra", "avatar_goliath", "avatar_good_yeti", "avatar_graph_blockula", "avatar_greensoldier", "avatar_grumbler", "avatar_guardian", "avatar_gum_beast", "avatar_guns_bunny", "avatar_gunslinger", "avatar_halfmetal_mechanist", "avatar_hater", "avatar_head_of_academy", "avatar_heavy_dive_suit", "avatar_heavy_siege_robot", "avatar_helga_the_breaker", "avatar_helicopter_pilot", "avatar_hercules", "avatar_hermes", "avatar_hooligan_girl", "avatar_humpty_dumpty", "avatar_ice_dragon_adept", "avatar_ice_dragon_shaman", "avatar_ice_titan", "avatar_igor", "avatar_impositor_black", "avatar_impositor_blue", "avatar_impositor_cyan", "avatar_impositor_green", "avatar_impositor_orange", "avatar_impositor_pink", "avatar_impositor_red", "avatar_impositor_violet", "avatar_impositor_white", "avatar_impositor_yellow", "avatar_indian_boy", "avatar_indian_girl", "avatar_infected_scientist", "avatar_infection_fighter", "avatar_insidious_hades", "avatar_iron_warrior", "avatar_jason_drill", "avatar_joystick", "avatar_kartoszewski", "avatar_katty_pop", "avatar_khepri", "avatar_king", "avatar_king_of_bros", "avatar_knight", "avatar_knitteddoll", "avatar_kraken_cult_knight", "avatar_krampus", "avatar_lab_prototype", "avatar_lava_titan", "avatar_lee_gun", "avatar_legendary_captain", "avatar_legionary", "avatar_log", "avatar_loki", "avatar_mad", "avatar_mafia_head", "avatar_magical_rabbit", "avatar_mayor", "avatar_mech_pilot_exo1", "avatar_mech_pilot_exo2", "avatar_med_paramedic", "avatar_mermaid_princess", "avatar_mikhail_steel", "avatar_minotaurus", "avatar_modern_ninja", "avatar_mouse_king", "avatar_mr_bite", "avatar_mr_bucket", "avatar_mr_streamer", "avatar_mr_ultimatum", "avatar_ms_doc", "avatar_mysterious_warden", "avatar_mystic_merchant", "avatar_navy_tactical_suit", "avatar_neon", "avatar_netrunner", "avatar_nimble_viking", "avatar_ninja_fox", "avatar_ninja_robot", "avatar_noob", "avatar_novice", "avatar_oak_bot", "avatar_obscurant", "avatar_odin", "avatar_oldrobot", "avatar_orange", "avatar_orc", "avatar_pawn", "avatar_pga_goo", "avatar_phoenix_warrior", "avatar_pi_xel", "avatar_pilgrim_boy", "avatar_pilgrim_girl", "avatar_pirqates_queen", "avatar_pixel_cola_mascot", "avatar_player_1", "avatar_player_2", "avatar_polar_archaeologist", "avatar_policeman", "avatar_portalius", "avatar_professor_stone", "avatar_project_manager", "avatar_prospector", "avatar_pyramid_builder", "avatar_queen", "avatar_radioactive_girl", "avatar_raptor", "avatar_red_skull", "avatar_red_soldier", "avatar_redneck", "avatar_redskin", "avatar_rescuer", "avatar_robo_elf", "avatar_robotic", "avatar_robotron", "avatar_rock_titan", "avatar_rocket_jumper", "avatar_rocksy", "avatar_rook", "avatar_rubus", "avatar_ruin_demon", "avatar_runaway_statue", "avatar_same_prince", "avatar_santa_helper", "avatar_scarab_priest", "avatar_scout", "avatar_scuba_diving_scout", "avatar_secret_character", "avatar_flying_dutchman", "avatar_secret_mech_prototype", "avatar_sharko", "avatar_sheriff", "avatar_shining_moon", "avatar_shiny", "avatar_silent_survivor", "avatar_skeleton_pirate", "avatar_skeptic_boy", "avatar_ski_girl", "avatar_soundman", "avatar_spark", "avatar_spec_ops", "avatar_spec_ops_boss", "avatar_spec_ops_boy", "avatar_spec_ops_girl", "avatar_spec_ops_tactical_mech", "avatar_spiky", "avatar_steel_man", "avatar_strange_creature", "avatar_street_king", "avatar_strongman", "avatar_summer_spirit", "avatar_sun", "avatar_super_mutant", "avatar_super_portalius", "avatar_super_pro", "avatar_super_star_girl", "avatar_supreme_lich", "avatar_supreme_prophet", "avatar_supreme_space_parasite", "avatar_thor", "avatar_treasure_raider", "avatar_triceratops", "avatar_turkey_guy", "avatar_twinkle", "avatar_undercover_agent", "avatar_vacation_girl", "avatar_valkyrie", "avatar_vampire_hunter", "avatar_snow_queen", "avatar_virtual_blogger", "avatar_water_warrior", "avatar_werewolf", "avatar_winter_boy", "avatar_winter_girl", "avatar_wooden", "avatar_yakuza", "avatar_yellowsoldier", "avatar_zeus", "avatar_zombie_clown", "avatar_zombie_dude", "avatar_zombified_alien", "avatar_еmperor_son", "aaaaa_trail", "air_trail", "ancient_ice_trail", "balloons_trail", "bats_trail", "beautiful_shells_trail", "berserker_trail", "block_trail", "bloq_commercial_trail", "bombs_trail", "bugs_trail", "bullet_trail", "buttons_trail", "candies_trail", "carrots_trail", "cartoon_clouds_trail", "cartoon_start_trail", "checkerboard_trail", "chess_trail", "clan_trail", "colorful_smoke_trail", "comet_trail", "confetti_trail", "decorated_feathers_trail", "digits_trail", "dislikes_trail", "disputes_trail", "drill_trail", "dust_trail", "energetic_trail", "extinguiser_trail", "fast_furious_trail", "fiery_trail", "firecrackers_trail", "firework_trail", "flashlights_trail", "glitch_trail_trail", "goo_trail", "graphic_trail", "gravilith_trail", "gum_trail", "holy_light_trail", "ice_trail", "lava_lamp_trail", "leaf_trail", "lemonade_bubbles_trail", "likes_trail", "love_trail", "mafia_trail", "magic_trail", "marshmallow_trail", "menacing_trail", "merchant_trail", "mini_helicopters_trail", "money_trail", "moonlight_trail", "mutated_dna_trail", "mystery_notes_trail", "neon_trail", "new_ear_trail", "old_scrolls_trail", "ominous_trail", "ovum_trail", "pixel_cola_trail", "plague_trail", "poisonous_trail", "poisonous_vines_trail", "police_alert_hologram_trail", "power_up_trail", "quick_feathers_trail", "rainbow_trail", "rocket_pursuit_trail", "rocks_trail", "rune_trail_trail", "scout_trail", "secret_documents_trail", "shiny_mutagen_trail", "signal_trail", "sinister_tentacles_trail", "snow_trail", "snowballs_trail", "snowflakes_trail", "sos_trail", "sparkling_stardust_trail", "speed_up_trail", "star_trail", "stardust_trail", "storm_trail", "storm_vortex_trail", "strange_potion_trail", "summer_flowers_trail", "sun_rays_trail", "sunny_trail", "ultimatum_trail_trail", "vampire_trail", "virtual_trail", "virus_trail", "volcano_trail", "water_trail", "wedding_rings_trail", "zeus_wrath_trail", "сurvature_of_space_trail", "black_bullet_car", "royale_car_all_terrain_vehicle", "royale_car_armored_stryker", "royale_car_basic", "royale_car_battle_transport", "royale_car_block", "royale_car_blocks_transport", "royale_car_blogger", "royale_car_bugs_harvester", "royale_car_cyber_cop_car", "royale_car_duck", "royale_car_heavy_rover", "royale_car_irriadiated_taxi", "royale_car_lands_walker", "royale_car_laser_bunny", "royale_car_mining_transport", "royale_car_motorcycle_phoenix", "royale_car_mutated_limps", "royale_car_passenger_beetle", "royale_car_patrol", "royale_car_quicksilver", "royale_car_robot_carrier", "royale_car_secret_explorer", "royale_car_siege_ram", "royale_car_space_traveller", "royale_car_steam", "royale_car_stonecutter", "royale_car_summer_van", "royale_car_survivors", "royale_car_sweeper_z", "royale_car_train", "royale_car_trojan_horse", "royale_car_winter_carriage", "royale_car_yorkshire_buggy", "royale_road_warrior", "royale_snowmobile", "glider_poison_bubble", "avatar_irradiated_pixelman", "avatar_squid_001", "avatar_squid_002", "avatar_squid_004", "avatar_squid_005", "avatar_squid_003", "avatar_front_man", "avatar_security_circle", "avatar_security_square", "avatar_security_triangle", "brave_priest", "glider_chainsaw", "avatar_brave_priest", "royale_car_antimutant_bus", "avatar_sara_zoom", "avatar_viktor_grom", "avatar_madcap_girlie", "avatar_desperate_lab_assistant", "glider_antidote_spray", "barbed_wire_trail", "super_antidote_trail", "glider_tamed_zombolisk", "avatar_ice_lich_king", "helicopter_military", "royale_atv", "avatar_divided_santa", "avatar_treasure_warden", "avatar_the_ancient_god", "avatar_quirky_boy", "avatar_wildwood_creature", "avatar_mystical_fairy", "hare_firefly_trail", "mirrored_night_trail", "avatar_the_mirror", "avatar_forest_guardian", "avatar_summoned_snowman", "avarar_krampus_elf", "avatar_dazzling_moth", "avatar_dazzling_sage", "avatar_krampus_elf", "royale_car_santas_autonomic_sleigh", "glider_cristmas_keeper", "glider_butterfly_of_light", "royale_car_mysterious_carriage", "glider_reality_border", "royale_snowmobile_freeplay", "fps_all_terrain_vehicle", "glider_handmade", "glider_tranquility_stone", "avatar_armed_assistant", "avatar_deft_shinobi", "avatar_elementals_challenger", "avatar_inquisitive_scientists", "avatar_mighty_shaman", "avatar_red_pan_dah", "avatar_wise_shogun", "sakura_flowers_trail", "shamanic_symbols_trail", "royale_car_village_keeper", "royale_car_floating_water_lily", "avatar_storms_overlord", "glider_ancient_dragon_spirit", "glider_loaded_koi", "super_bowl_player", "avatar_super_bowl_player", "royale_amphibian", "glider_executers_high_end", "glider_extraterrestrial_hoverboard", "glider_good_ol_plane", "avatar_aliens_executioner", "avatar_bubble_queen", "avatar_good_ol_bomber", "avatar_royal_confidant", "avatar_the_chosen_one", "avatar_the_empress", "executed_aliens_storage_trail", "pg_is_love_trail", "royale_car_all_terrain_tank", "avatar_goblin_rogue", "avatar_sun_elf", "glider_skyfly_3000", "avatar_troll_warchief", "deadly_plague_trail", "spheres_of_power_trail", "royale_car_flamy_racer", "avatar_moon_elf", "avatar_edelonne_the_undead", "glider_armored_flyer", "avatar_light_paladin", "glider_death_herald", "avatar_crystal_golem", "avatar_living_armor", "avatar_moon", "avatar_neptune", "avatar_earth", "glider_sunstrider", "earth_atmosphere_trail", "neptune_ices_trail", "glider_terra_board", "avatar_the_sun", "avatar_the_everything", "avatar_the_shadow", "avatar_junior_cult_member", "avatar_dark_woods_spirit", "avatar_exorcist", "royale_car_moonstrider", "royale_hat_lich_crown_preview", "glider_yellow_duck", "avatar_maniac_artist", "avatar_mr_monke", "avatar_sad_sally", "avatar_yellow_slicker", "dyed_hares_trail", "royale_car_vacations_minivan", "glider_ramen_noodle", "glider_mad_dyer", "tamagochi_trail", "avatar_the_empress" };
const char* gadgetList[]{ "gadget_armor_regeneration", "gadget_astral", "gadget_bionic_shield", "gadget_black_label", "gadget_Blizzard_generator", "gadget_christmastreeturret", "gadget_combat_spinner", "gadget_cyber_bees", "gadget_cybersamurai", "gadget_demon_stone", "gadget_denied", "gadget_disabler", "gadget_dragonwhistle", "gadget_fakebonus", "gadget_firecrackers", "gadget_firemushroom", "gadget_firework", "gadget_fraggrenade", "gadget_guardian", "gadget_hologram_projector", "gadget_jetpack", "gadget_leaderdrum", "gadget_mech", "gadget_medicalstation", "gadget_medkit", "gadget_mh_mech1", "gadget_mh_mech2", "gadget_mh_mech3", "gadget_mine", "gadget_molotov", "gadget_ninjashurickens", "gadget_nucleargrenade", "gadget_nutcracker", "gadget_pandorabox", "gadget_petbooster", "gadget_phoenix_blood", "gadget_pocket_harpoon", "gadget_reflector", "gadget_rocket_mech", "gadget_shield", "gadget_singularity", "gadget_snowman", "gadget_stealth", "gadget_sticky_turret", "gadget_stickycandy", "gadget_super_magnet", "gadget_timewatch", "gadget_turret", "gadget_x-ray_glasses", "gadget_class_bullet_medkit", "gadget_class_bullet_phonixblood", "gadget_class_knight_magnet", "gadget_class_valk_jetpack", "gadget_class_valk_cyberbees", "gadget_class_lifeline_medstation", "gadget_class_lifeline_biotiksheald", "gadget_class_sara_hook", "gadget_class_sara_xray", "gadget_class_saber_shurikens", "gadget_class_saber_reflector", "gadget_class_mex_turret", "gadget_class_mex_nucleargrenade", "gadget_class_viktor_smilemine", "gadget_class_viktor_nutcracker", "gadget_br_fraggrenade", "gadget_br_molotov", "gadget_br_mine", "gadget_hook_monster" };

std::vector<std::string> usernameList = {
	"Hades", "SparklingFirefly", "GoddessBattle", "MoonlightPhantom", "HeroXehanort", "MeanAim", "TacticalPeach", "HulkEnforcer", "ValiantGent", "PrankBloomer", "WarVanguard", "FistfighterOnline", "DeadlyBuccaneer", "MysticDons", "WanderJoyful", "EnemyTracker", "ProdigySlayer", "EnchantedRelic", "TerrorNova", "ValiantHammer", "SwordpointReady", "FiredrakeSlayer", "RiskySpark", "HaunterSpectral", "TwinklingLilac", "VaporGuardian", "MysteryFigure", "UltraFiery", "MoxMaelstrom", "WarriorClan", "IntimidateKing", "StallionMask", "DriftNight", "ReaperHowler", "PlasmaVortex", "JesterBlazer", "BirdyMist", "ScorpionNeon", "QuickGoblin", "EngineerNerd", "AuroraBeacon", "CyberEnhancer", "IgniteFighter", "DaringCharm", "BlazeLily", "JawEnforcer", "ViciousHawkie", "GoofySprite", "PlayfulRealmers", "HybridLeader", "KittehFreedom", "BlastBehemoth", "StarlightForce", "WildcatRanger", "ShadowMastermind", "HurrahTroopers", "CuteBunny", "TechnoNavigator", "DashPuppy", "ServalScavenger", "QuickPowerhouse", "CosmosTremor", "BuddyRespect", "RocketGarnet", "FiendRage", "VelvetDanger", "StealthBlaster", "HostileBattle", "GoryRedfox", "SquadSniper", "SoldierSpartan", "FlashbloomOrchid", "GnasherKingdom", "SparkSunbeam", "TruthSeer", "TenorQueen", "CoolSnowballer", "LegsReady", "MechanicalBang", "SleekMuncher", "SiliconSpark", "PranksterSkill", "FerociousBound", "TeamPeach", "LimitlessBaker", "SpecterGuide", "LuminousSavior", "GiganticReptile", "WebbyAntler", "RevengeKid", "WatchfulOutlaw", "PixelExplorer", "RebelApple", "GracefulSkill", "GunBattlefield", "StormWitch", "HeartHowl"
};

AnalyticsParams offerwallParams = { 0x0, 0x82, 0x18, 0x0, 0x0, 0x0, 0x0, false, nullptr, 0x0, false, 0x0, nullptr, false, 0x1, 0 };



extern int fontSize;

extern bool aimbot, fireCheck, fov, silentAim, triggerBot, setMyScale, setOtherScale, damageMod, floatAll, mech, godAll, triggerBot, silentAim1, stw, triggerbot, visualCheck;;
extern int selectedPart;
extern float fovRadius, damageCoeff;
extern bool esp, lines, box, chams, firerate;
extern float myScale, otherScale;

extern float fireRateVal;

extern bool experience, addCurrency, addArmors, addCapes, addBoots, addHats, addMasks, addPets, unlockWear, modUp, addWeapons, addGraffiti, addWeaponSkins, addGadgets, telekill, massKill, buyWeaponSkins, unlockAll, Vip, addWeapons1, addWeapons2, addWeapons3, addWeapons4\
, addWeapons5, addWeapons6, addWeapons7, addWeapons8, addWeapons9, addWeapons10, RPC;
extern int selectedCur, currAmount, expVal, arrayStart, arrayEnd, lotteryAmount, selectedGraffiti, rpcSelected;

extern bool godmode, speed, fly, instaCharge, jump, addJetpack, doubleJump, invisible, invisibleMe, SpoofName, bugAll, breakGuns, spamRockets, freeze, spoofModules;
extern float speedVal, jumpVal, flySpeed, timeScaleVal;

extern bool ammo, recoilandspread, noreload, explosionradius, breakcam, polymorph, harpoonbull, headmagnify, blik , stealAmmo, freeClanParts, clanUpgradeTime, instantUpgrades,
forceCritical, noBR, thirdPerson, gravity, longLifetime, ricochet, NukeShoot, freezeall, infiniteAmmo, sandboxGuns;

extern bool BanTraceCleaner, clonePlayer, timescale, VisCheck;

extern int rocketMode, spoofModVal;

extern bool killall, playerscore, teamkill, clanEnergy, chatSpam, turret, turretGod, turretDmg, turretRange, gadgetcd, pet, pgod, pspeed, pdamage, hideNames, playerscoreAdd,
coinDrop, glitchEveryone, forceScope, reflections, flamethrowerBullets, railgunBull, ignoreReflection, charm, gadgetDisabler, speedUp, slowDown, jumpDisable, poison, curse, stun, 
droneGod, quickScope, sandboxAll, spamRocket;
extern int resolutionX, resolutionY;
const char* petsList[] = { "pet_cat", "pet_dog", "pet_parrot", "pet_rabbit", "pet_cat_2", "pet_dachshund", "pet_goat", "pet_cat_3", "pet_bat", "pet_fox", "pet_penguin", "pet_wolf", "pet_sheep", "pet_raccoon", "pet_husky", "pet_boar", "pet_ram", "pet_crab", "pet_owl", "pet_snake", "pet_lion", "pet_panda", "pet_red_panda", "pet_tukan", "pet_meerkat", "pet_robo_dog", "pet_porcupine", "pet_zombiecat", "pet_eagle", "pet_deer", "pet_polarbear", "pet_monkey", "pet_alien_cat", "pet_bear", "pet_hyena", "pet_kangaroo", "pet_skunk", "pet_ostrich", "pet_pterodactyl", "pet_dinosaur", "pet_arnold_3000", "pet_chicken", "pet_paradehorse", "pet_rhino", "pet_tiger", "pet_panther", "pet_horse", "pet_unicorn", "pet_phoenix", "pet_magical_dragon", "pet_griffin", "pet_eaglespirit", "pet_mammoth", "pet_sabertooth_tiger", "pet_raven", "pet_trex", "pet_cyberphoenix", "pet_blocston_dogmatics", "pet_turkey", "pet_armadillo", "pet_griffin_owl", "pet_squirrel", "pet_tactical_ferret", "pet_stone_elemental", "pet_fighting_turtle", "pet_knitted_pony", "pet_stone", "pet_horse_figure", "pet_lucky_duck", "pet_green_novice", "pet_headbug", "pet_chick01", "pet_pocket_demon", "pet_flappy_fish", "pet_zazou", "pet_pga_statue", "pet_vacuum_helpbro_2000", "pet_ice_dragon_egg", "pet_combat_robb_e", "pet_small_floppa", "pet_sacred_scarab", "pet_mecha_cat", "pet_zombie_head", "pet_support_piglet", "pet_firefly_cat", "pet_elementals_helper", "pet_tankmouse", "pet_backwater_dweller", "pet_shiny_companion", "pet_8_bit_boi", "pet_blue_buddy", "pet_wise_owl", "pet_stingray_3000", "pet_bullfinch_the_giver", "pet_festive_black_rabbit", "pet_servants_right_hand", "pet_ice_cream_cup", "pet_anniversary_kitty", "pet_capy", "pet_modified_assistant", "pet_cheering_up_cookie", "pet_glass_dragonfly"};
const char* capeList[] = { "cape_Custom", "cape_EliteCrafter", "StormTrooperCape_Up1", "StormTrooperCape_Up2", "cape_Archimage", "HitmanCape_Up1", "HitmanCape_Up2", "cape_BloodyDemon", "BerserkCape_Up1", "BerserkCape_Up2", "cape_Engineer", "cape_Engineer_Up1", "cape_Engineer_Up2", "cape_SkeletonLord", "SniperCape_Up1", "SniperCape_Up2", "cape_cloak_of_night", "cape_ultimate_defense", "cape_vaneuvering_module", "cape_RoyalKnight", "DemolitionCape_Up1", "DemolitionCape_Up2", "cape_fun_fair_cape", "DemolitionBoots_Up2", "cape_magic_gift", "cape_of_intelligence", "cape_of_loneliness", "cape_gifts", "cape_screen", "cape_loyalty" };
const char* bootsList[] = { "boots_gray", "StormTrooperBoots_Up1", "StormTrooperBoots_Up2", "boots_red", "HitmanBoots_Up1", "HitmanBoots_Up2", "boots_black", "BerserkBoots_Up1", "BerserkBoots_Up2", "EngineerBoots", "EngineerBoots_Up1", "EngineerBoots_Up2", "boots_blue", "SniperBoots_Up1", "SniperBoots_Up2", "boots_green", "DemolitionBoots_Up1", "DemolitionBoots_Up2", "boots_tabi", "boots_cyber_santa", "boots_cyber_santa_Up1", "boots_cyber_santa_Up2", "boots_exoskeleton_pilot_avatar", "boots_exoskeleton_pilot_avatar_up1", "boots_exoskeleton_pilot_avatar_up2", "boots_black_dragon", "boots_halloween", "boots_halloween_up1", "boots_halloween_up2", "boots_roller_skates", "boots_stardust", "boots_ultimate_defense", "boots_piligrim", "boots_piligrim_up1", "boots_piligrim_up2", "boots_space_delivery", "boots_roller_skates", "boots_natural", "boots_magic_gift" };
const char* hatList[] = { "league1_hat_hitman", "league2_hat_cowboyhat", "league3_hat_afro", "league4_hat_mushroom", "league5_hat_brain", "league6_hat_tiara", "hat_Adamant_3", "hat_Headphones", "hat_black_dragon", "hat_chest", "hat_KingsCrown", "hat_stardust", "hat_Samurai", "hat_DiamondHelmet", "hat_SeriousManHat", "hat_cyber_santa", "hat_cyber_santa_Up1", "hat_cyber_santa_Up2", "hat_exoskeleton_pilot_avatar", "hat_exoskeleton_pilot_avatar_up1", "hat_exoskeleton_pilot_avatar_up2", "hat_halloween", "hat_halloween_up1", "hat_halloween_up2", "hat_piligrim", "hat_piligrim_up1", "hat_piligrim_up2", "hat_high_end_earphones" , "hat_magic_gift", "hat_space_delivery" };
const char* maskList[] = { "mask_trooper","mask_trooper_up1","mask_trooper_up2","mask_hitman_1","mask_hitman_1_up1","mask_hitman_1_up2","mask_berserk","mask_berserk_up1","mask_berserk_up2","mask_engineer","mask_engineer_up1","mask_engineer_up2","mask_sniper","mask_sniper_up1","mask_sniper_up2","mask_demolition","mask_demolition_up1","mask_demolition_up2","hat_ManiacMask","mask_cyber_santa","mask_cyber_santa_Up1","mask_cyber_santa_Up2","mask_exoskeleton_pilot_avatar","mask_exoskeleton_pilot_avatar_up1", "mask_exoskeleton_pilot_avatar_up2", "mask_halloween", "mask_halloween_up1", "mask_halloween_up2", "mask_black_dragon", "mask_doctor_plague", "mask_medical_mask", "mask_turkey_piligrim", "mask_turkey_piligrim_up1", "mask_turkey_piligrim_up2", "mask_ultimate_defense", "mask_anime_glasses", "mask_smart_bullet_bazooka", "mask_stop_posting_hepi", "mask_natural"};
const char* armorList[] = { "Armor_Adamant_Const_2", "Armor_Almaz_3", "Armor_Army_1", "Armor_Army_3", "armor_black_dragon", "armor_dope_windcheater", "Armor_Halloween", "armor_inflatable", "Armor_Royal_3", "Armor_Rubin_3", "armor_stardust", "Armor_Steel_3", "armor_ultimate_defense", "cyber_santa_armor", "developer_armor", "exoskeleton_pilot_avatar_armor", "heavy_champion_armor", "pilgrim_armor", "starter_pack_armor", "armor_cash_fix","armor_magic_gift","armor_superhero","armor_cash","armor_natural","armor_space_delivery" };
extern std::vector<Vector3> headVectors;
extern std::vector<EspData> boxDataList;
EspData boxData;
int currentLevel;
bool hooked;

uintptr_t getAbsolute(uintptr_t addr) {
	if (addr != 0) {
		return gameAssembly + addr;
	}
	return 0;
}

std::string getRandomUsername() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, usernameList.size() - 1);

	int index = dis(gen);

	return usernameList[index];
}

monoString* CreateIl2cppString(const char* str)
{
	static monoString* (*CreateIl2cppString)(const char* str, int startIndex, int length) =
		(monoString * (*)(const char* str, int startIndex, int length))(getAbsolute(Offsets::System::String::ctor));
	int startIndex = 0;
	int length = strlen(str);
	return CreateIl2cppString(str, startIndex, length);
}

std::string CleanString(const std::string& str) {
	std::string cleanStr;
	cleanStr.reserve(str.size());

	std::remove_copy_if(str.begin(), str.end(), std::back_inserter(cleanStr), [](char c) {
		return c == '\0';
		});

	return cleanStr;
}


namespace pg3d {
	namespace Unity {

		void* Instantiate(monoString* prefabName, Vector3 pos, Quaternion rot, uint8_t a1)
		{
			static const auto fn = (void* (*)(monoString*, Vector3, Quaternion, uint8_t))(getAbsolute(Offsets::Photon::PhotonPlayer::instantiate));
			return fn(prefabName, pos, rot, a1);
		}

		Vector3 WorldToScreenPoint(void* player, Vector3 position)
		{
			if (!player) return Vector3(0, 0, 0);
			static const auto fn = (Vector3(*)(void*, Vector3)) (getAbsolute(Offsets::UnityEngine::Camera::worldtoscreen));
			return fn(player, position);
		}

		void* GetTransform(void* obj)
		{
			if (!obj) return nullptr;
			static const auto fn = (void* (*)(void*)) (getAbsolute(Offsets::UnityEngine::Component::componentgettransform));
			return fn(obj);
		}

		Quaternion GetRotation(void* obj)
		{
			if (!obj) return Quaternion(0, 0, 0, 0);
			static const auto fn = (Quaternion(*)(void*)) (getAbsolute(Offsets::UnityEngine::Transform::getrot));
			return fn(obj);
		}

		Vector3 GetPosition(void* obj)
		{
			if (!obj) return Vector3(0, 0, 0);
			static const auto fn = (Vector3(*)(void*)) (getAbsolute(Offsets::UnityEngine::Transform::getpos));
			return fn(obj);
		}


		void SetPosition(void* obj, Vector3 val)
		{
			static const auto fn = (void(*)(void*, Vector3)) (getAbsolute(Offsets::UnityEngine::Transform::setpos));
			return fn(obj, val);
		}

		void SetLocalScale(void* obj, Vector3 val)
		{
			static const auto fn = (void(*)(void*, Vector3)) (getAbsolute(Offsets::UnityEngine::Transform::setlocscale));
			return fn(obj, val);
		}


		Vector3 InverseTransformPoint(void* obj, Vector3 pos)
		{
			if (!obj) return Vector3(0, 0, 0);
			static const auto fn = (Vector3(*)(void*, Vector3)) (getAbsolute(Offsets::UnityEngine::Transform::inversetransformpoint));
			return fn(obj, pos);
		}

		void Rotate(void* obj, float x, float y, float z)
		{
			if (!obj) return;
			static const auto fn = (void(*)(void*, float, float, float)) (getAbsolute(Offsets::UnityEngine::Transform::rotate));
			return fn(obj, x, y, z);
		}

		void LoadScene(monoString* scene)
		{
			static const auto fn = (void(*)(monoString*)) (getAbsolute(Offsets::SceneManager::loadscene));
			return fn(scene);
		}

		void* get_main() {
			static const auto fn = (void* (*)()) (getAbsolute(Offsets::UnityEngine::Camera::getmain));
			return fn();
		}

		void* get_Current() {
			static const auto fn = (void* (*)()) (getAbsolute(Offsets::UnityEngine::Camera::current));
			return fn();
		}

		void* get_playerTransform(void* player) {
			if (player) {
				void* transform = *(void**)((uint64_t)player + 0x3b8);
				return transform;
			}
			return nullptr;
		}

		void set_timeScale(float val)
		{
			static const auto fn = (void(*)(float)) (getAbsolute(Offsets::UnityEngine::Time::timeScale));
			return fn(val);
		}
	}

	namespace PlayerScoreController {
		void AddScore(void* obj, int scoreType, float koef) {
			static const auto green_fn = (void (*)(void*, int, float)) (getAbsolute(Offsets::PlayerScoreController::addscore));
			return green_fn(obj, scoreType, koef);
		}
	}

	namespace player_move_c {

		void* get_shootCheckPoint(void* obj) {
			static const auto fn = (void* (*)(void*)) (getAbsolute(Offsets::Player_Move_C::get_shootCheckPoint));
			return fn(obj);
		}

		void* WeaponTransform(void* player) {
			if (player) {
				void* transform = *(void**)((uint64_t)player + 0x3c0);
				return transform;
			}
			return nullptr;
		}

		void* GunShootPoint(void* player) {
			if (player) {
				void* transform = *(void**)((uint64_t)player + 0x518);
				return transform;
			}
			return nullptr;
		}

		void* GunCamera(void* player) {
			if (player) {
				void* camera = *(void**)((uint64_t)player + 0x2a8);
				return camera;
			}
			return nullptr;
		}

		void* TextMeshGetText(void* obj)
		{
			if (!obj) return nullptr;
			static const auto fn = (void* (*)(void*)) (getAbsolute(Offsets::UnityEngine::TextMesh::textmesh));
			return fn(obj);
		}

		std::string GetPlayerName(void* player_move_c)
		{
			void* nick_label = (void*)*(uint64_t*)((uint64_t)player_move_c + 0x3d0);
			void* name_ptr = pg3d::player_move_c::TextMeshGetText(nick_label);
			std::string name = ((monoString*)name_ptr)->getChars();
			return CleanString(name);
		}

		bool IsMyPlayer(void* player_move_c)
		{
			if (!player_move_c) return false;
			std::string player_name = GetPlayerName(player_move_c);
			return player_name.find("1111") != std::string::npos;
		}

		bool CanTarget(void* obj)//Works
		{
			static const auto greem_fucknigga = (bool (*) (void* obj))(getAbsolute(Offsets::Player_Move_C::CanTarget));
			return greem_fucknigga(obj);
		}

		void* get_baseCameraTransform(void* player) {
			void* skinName = *(void**)((uint64_t)player + 0x690);
			if (skinName != nullptr) {
				void* firstPersonControlSharp = *(void**)((uint64_t)skinName + 0x1E0);
				if (firstPersonControlSharp != nullptr) {
					void* baseCamera = *(void**)((uint64_t)firstPersonControlSharp + 0x1A0);
					if (baseCamera != nullptr) {
						return *(void**)((uint64_t)baseCamera + 0x48);
					}
				}
			}
		}

		bool IsMyWeaponSounds(void* weapon_sounds)
		{
			void* player_move_c = (void*)*(uint64_t*)((uint64_t)weapon_sounds + 0x4f0);
			if (player_move_c == nullptr) return false;
			return IsMyPlayer(player_move_c);
		}

		void ShowXray(void* obj, bool a1, ZoomTypes a2) {
			if (!obj) return;
			static const auto fn = (void(*)(void*, bool, ZoomTypes)) (getAbsolute(Offsets::Player_Move_C::show_xray_offset));
			return fn(obj, a1, a2);
		}

		void EnableJetpack(void* obj, bool a1) {
			if (!obj) return;
			static const auto fn = (void(*)(void*, bool)) (getAbsolute(Offsets::Player_Move_C::enablejetpackoffset));
			return fn(obj, a1);
		}

		void MakeInvisibleForSecondsRPC(void* obj, float a1) {
			if (!obj) return;
			static const auto fn = (void(*)(void*, float)) (getAbsolute(Offsets::Player_Move_C::makeinvisibleforsecondsrpc));
			return fn(obj, a1);
		}


		void ApplyDamageToTarget(void* obj, void* damageable, float damage, void* hitCollider, Vector3 damageSourcePosition, monoString* weaponName, int typeDead, int typeKill)
		{
			static const auto green_fn = (void (*)(void*, void*, float, void*, Vector3, monoString*, int, int)) (getAbsolute(Offsets::Player_Move_C::applyDamage));
			return green_fn(obj, damageable, damage, hitCollider, damageSourcePosition, weaponName, typeDead, typeKill);
		}

		void SlowdownTarget(void* obj, void* hitCollider, float slowdownTime, float slowdownCoeff)
		{
			static const auto green_fn = (void (*)(void*, void*, float, float))(getAbsolute(Offsets::Player_Move_C::slowDown));
			return green_fn(obj, hitCollider, slowdownTime, slowdownCoeff);
		}

		bool get_isShooting(void* obj)//Yes fuck nigga
		{
			static const auto greem_fucknigga = (bool (*) (void* obj))(getAbsolute(Offsets::Player_Move_C::get_isShooting));
			return greem_fucknigga(obj);
		}

		/*void* get_transform(void* obj) {
			static const auto fn = (void*(*)(void*)) (getAbsolute(Offsets::componenttransform));
			return fn(obj);
		}

		Vector3 get_position(void* obj) {
			static const auto fn = (Vector3(*)(void*)) (getAbsolute(Offsets::getposition));
			return fn(obj);
		}

		void set_position(void* obj, Vector3 pos) {
			if (!obj) return;
			static const auto fn = (void(*)(void*, Vector3)) (getAbsolute(Offsets::setposition));
			return fn(obj, pos);
		}*/

		bool IsVisibleTargetNew(void* obj, Vector3 position) //Works
		{
			static const auto greem_fucknigga = (bool (*) (void* obj, Vector3 position))(getAbsolute(Offsets::Player_Move_C::isVisibleTargetNew));
			return greem_fucknigga(obj, position);
		}

		void CreateRocket(void* _currentWeaponSounds, Vector3 pos, Quaternion rot, float _chargePower, int smokeNum)
		{
			static const auto green_fn = (void (*)(void* _currentWeaponSounds, Vector3 pos, Quaternion rot, float _chargePower, int smokeNum))(getAbsolute(Offsets::Player_Move_C::rocket));
			return green_fn(_currentWeaponSounds, pos, rot, _chargePower, smokeNum);
		}

		void AddAmmoFromWeaponOnline(void* obj, float amount)
		{
			if (!obj) return;
			static const auto fn = (void(*)(void*, float, char*)) (getAbsolute(Offsets::PlayerDamageable::addammofromweponline));
			return fn(obj, amount, nullptr);
		}
		void* get_playerDamageable(void* player) {
			if (player) {
				void* damageable = *(void**)((uint64_t)player + 0x650);
				return damageable;
			}
			return nullptr;
		}

		void* webInstance()
		{
			static void* (*webInstance)() = (void* (*)())(getAbsolute(Offsets::ProgressUpdater::webinstance));//Analyze LeprechauntManager.DropReward() and youll find it :)
			return webInstance();
		}

		void AddCurrency(void* obj, monoString* currencyType, int value, int reason, AnalyticsParams params) {
			static const auto green_fn = (void (*)(void*, monoString*, int, int, bool, bool, AnalyticsParams)) (getAbsolute(Offsets::ProgressUpdater::setcurrencyoffset));
			return green_fn(obj, currencyType, value, reason, false, false, params);
		}

		void AddWeapon(void* obj, monoString* weapon, AnalyticsParams params) {
			static const auto green_fn = (void (*)(void*, monoString*, int, bool, bool, void*, AnalyticsParams)) (getAbsolute(Offsets::WeaponManager::addweapon));
			return green_fn(obj, weapon, 62, false, false, nullptr, params);
		}


		void AddGraffiti(void* obj, monoString* graffiti) {
			static const auto green_fn = (void (*)(void*, monoString*)) (getAbsolute(Offsets::GraffitiController::addgraffiti));
			return green_fn(obj, graffiti);
		}

		void AddExp(void* obj, int exp, int reason) {
			static const auto green_fn = (void (*)(void*, int, int)) (getAbsolute(Offsets::ExperienceController::addexperience));
			return green_fn(obj, exp, reason);
		}

		void AddArmor(void* obj, int value, int reason, monoString* currencyType, AnalyticsParams params) {
			static const auto green_fn = (void (*)(void*, int, int, monoString*, AnalyticsParams)) (getAbsolute(Offsets::ProgressUpdater::givearmor));
			return green_fn(obj, value, reason, currencyType, params);
		}

		int AddWear(int categoryNames, monoString* armor) {
			static const auto green_fn = (int (*)(int, monoString*)) (getAbsolute(Offsets::Wear::givewear));
			return green_fn(categoryNames, armor);
		}

		void AddPet(monoString* pet, int lvl) {
			static const auto green_fn = (void (*)(monoString*, int)) (getAbsolute(Offsets::InappBonusesController::givepetoffset));
			return green_fn(pet, lvl);
		}

		void AddGadgets(monoString* gadget, int* lvl) {
			static const auto green_fn = (void (*)(monoString*, int*)) (getAbsolute(Offsets::GadgetInfo::addgadgets));
			return green_fn(gadget, lvl);
		}

		void AddBR(monoString* br, bool* idk, AnalyticsParams params) {
			static const auto green_fn = (void (*)(monoString*, bool*, AnalyticsParams)) (getAbsolute(Offsets::RoyaleCustomizationItemsManager::addbr));
			return green_fn(br, idk, params);
		}
		void SendChat(void* obj, monoString* chat, bool clan, monoString* chaticon) {
			static const auto green_fn = (void (*)(void*, monoString*, bool, monoString*)) (getAbsolute(Offsets::Player_Move_C::sendchat));
			return green_fn(obj, chat, clan, chaticon);
		}

		int getWearIndex(const char* str)
		{
			static const auto green_fn = (int (*)(monoString * str))(getAbsolute(Offsets::Wear::armorindex));//search for ERROR!!!!!!! ??? ????????? ??????? ??? ?????? {0}
			return green_fn(CreateIl2cppString(str));
		}

		void* graffitiInstance()
		{
			static void* (*graffitiInstance)() = (void* (*)())(getAbsolute(Offsets::GraffitiController::graffitiinstance));
			return graffitiInstance();
		}

		void _Shot(void* obj)
		{
			static const auto green_fn = (void (*)(void* obj))(getAbsolute(Offsets::Player_Move_C::_shoot));
			return green_fn(obj);
		}

		void ShootS(void* obj)
		{
			static const auto green_fn = (void (*)(void* obj))(getAbsolute(Offsets::Player_Move_C::shoots));
			return green_fn(obj);
		}

		void ShotPressed(void* obj)
		{
			static const auto green_fn = (void (*)(void* obj))(getAbsolute(Offsets::Player_Move_C::shotpressed));
			return green_fn(obj);
		}

		/*void* SetWeaponRPC(int weaponName) {
			static const auto green_fn = (void* (*)( int))(getAbsolute(0x7bc3d0));
			return green_fn( weaponName);
		}*/
		/*void EnableXray(void* obj, bool a1, ZoomTypes a2, ZoomTypes a3) {
			if (!obj) return;
			static const auto fn = (void(*)(void*, bool, ZoomTypes, ZoomTypes)) (getAbsolute(Offsets::show_xray_offset));
			return fn(obj, a1, a2, a3);
		}*/
	}

	namespace petengine {
		void SetHealth(void* obj, float health) {
			if (!obj) return;
			static const auto fn = (void(*)(void*, float)) (getAbsolute(Offsets::PetEngine::petsethealth));
			return fn(obj, health);
		}
	}

	namespace PlayerDamageable {
		bool isEnemyTo(void* me, void* enemy) {
			if (!me) return false;
			void* playerDamageable = *(void**)((uintptr_t)me + 0x668);
			static const auto fn = (bool(*)(void*, void*)) (getAbsolute(Offsets::PlayerDamageable::enemyto));
			return fn(playerDamageable, enemy);
		}

		bool isDead(void* me) {
			void* playerDamageable = *(void**)((uintptr_t)me + 0x668);
			static const auto fn = (bool(*)(void*)) (getAbsolute(Offsets::PlayerDamageable::isdead));
			return fn(playerDamageable);
		}
	}

	namespace PhotonPlayer {

		void set_NickName(void* _instance, monoString* value) {
			static const auto green_fn = (void(*)(void*, monoString*))(getAbsolute(Offsets::Photon::PhotonPlayer::set_nickname));
			return green_fn(_instance, value);
		}

		void* get_LocalPlayer() {
			static const auto green_fn = (void* (*)()) (getAbsolute(Offsets::Photon::PhotonPlayer::get_LocalPlayer));
			return green_fn();
		}
	}

}

void(*oAddEXP)(...);
void AddEXP(void* obj, int val, int reason, monoDictionary<monoString*, void>* dictionary) {
	if (experience)
		val = expVal;

	oAddEXP(obj, val, reason, dictionary);
}

void(__stdcall* ogodmode)(...);
void __stdcall godMode(void* obj, float r, int t, int y, int c, int v, Vector3 z, monoString* l, int o) {
	if (godmode && obj)
		return;

	return ogodmode(obj, r, t, y, c, v, z, l, o);
}

void(__stdcall* oOnTriggerEnter)(...);
void __stdcall OnTriggerEnter(void* obj, void* collider) {
	if (godmode || fly)
		return;

	return oOnTriggerEnter(obj, collider);
}

void(__stdcall* oOnControllerColliderHit)(...);
void __stdcall OnControllerColliderHit(void* obj, void* collider) {
	if (godmode || fly)
		return;

	return oOnControllerColliderHit(obj, collider);
}

void(__stdcall* oPlayerScoreController)(...);
void __stdcall PlayerScoreController(void* obj) {
	if (playerscoreAdd) {
		pg3d::PlayerScoreController::AddScore(obj, 48, 99);
	}
	oPlayerScoreController(obj);
}

float (*oGetDPSCoeff)(int prefab);
float GetDPSCoeff(int prefab) {
	if (damageMod)
		return damageCoeff;

	return oGetDPSCoeff(prefab);
}

void (*_SetWeaponsSet)(void* _this, int filterMap);
void SetWeaponsSet(void* _this, int filterMap) {
	if (sandboxGuns) {
		return; 
	}
	_SetWeaponsSet(_this, filterMap);
}

void* myPlayer;
void* closestEnemy;
void* baseCamTransform;
void* CurrentCamera;
void* GunCameraTransform;
void* GunTransformPivot;

std::vector<void*> playerList;
void(__stdcall* oWeaponSounds)(void* obj);
void __stdcall WeaponSounds(void* obj) {
	if (obj) {

		if (timescale) {
			pg3d::Unity::set_timeScale(timeScaleVal);
		}
		else {
			pg3d::Unity::set_timeScale(1);
		}

		if (unlockAll) {
			pg3d::player_move_c::AddCurrency(pg3d::player_move_c::webInstance(), CreateIl2cppString(OBFUSCATE_STR("PixelPassCurrency")), 5340, 145, offerwallParams);
			unlockAll = false;
		}
		if (godmode && !hooked) {
			MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::Player_Move_C::godmode1offset), &godMode, (LPVOID*)&ogodmode);
			MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::Player_Move_C::godmode1offset));

			hooked = true;
		}
		else if (!godmode && hooked) {
			MH_DisableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::Player_Move_C::godmode1offset));

			hooked = false;
		}

		if (addCurrency) {
			pg3d::player_move_c::AddCurrency(pg3d::player_move_c::webInstance(), CreateIl2cppString(curList1[selectedCur]), currAmount, 145, offerwallParams);
			addCurrency = false;
		}

		if (addWeaponSkins) {
			for (int i = 0; i < 100; i++) {

				pg3d::player_move_c::AddBR(CreateIl2cppString(royaleList[i]), (bool*)true, offerwallParams);
			}
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));
			std::this_thread::sleep_for(std::chrono::seconds(5));

			for (int i = 101; i < 200; i++) {
				pg3d::player_move_c::AddBR(CreateIl2cppString(royaleList[i]), (bool*)true, offerwallParams);
			}
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));
			std::this_thread::sleep_for(std::chrono::seconds(5));
			for (int i = 200; i < 400; i++) {
				pg3d::player_move_c::AddBR(CreateIl2cppString(royaleList[i]), (bool*)true, offerwallParams);
			}
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));
			std::this_thread::sleep_for(std::chrono::seconds(5));
			for (int i = 400; i < 600; i++) {
				pg3d::player_move_c::AddBR(CreateIl2cppString(royaleList[i]), (bool*)true, offerwallParams);
			}
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));
			std::this_thread::sleep_for(std::chrono::seconds(5));
			for (int i = 600; i < 720; i++) {
				pg3d::player_move_c::AddBR(CreateIl2cppString(royaleList[i]), (bool*)true, offerwallParams);
			}
			addWeaponSkins = false;
		}

		if (addGraffiti) {
			//printf(graffitiList[i]);
			pg3d::player_move_c::AddGraffiti(pg3d::player_move_c::graffitiInstance(), CreateIl2cppString(graffitiList[selectedGraffiti]));
			addGraffiti = false;
		}

		if (addGadgets) {
			for (int i = 0; i < 68; i++) {
				pg3d::player_move_c::AddGadgets(CreateIl2cppString(gadgetList[i]), (int*)currentLevel);
			}
			addGadgets = false;
		}


		if (addPets) {
			for (int i = 0; i < 102; i++) {
				pg3d::player_move_c::AddPet(CreateIl2cppString(petsList[i]), 260);
			}
			addPets = false;
		}

		if (addMasks) {
			for (int i = 0; i < 39; i++) {
				pg3d::player_move_c::AddWear(12, CreateIl2cppString(maskList[i]));
			}
			addMasks = false;
		}

		if (addHats) {
			for (int i = 0; i < 30; i++) {
				pg3d::player_move_c::AddWear(6, CreateIl2cppString(hatList[i]));
			}
			addHats = false;
		}

		if (addCapes) {
			for (int i = 0; i < 30; i++) {
				pg3d::player_move_c::AddWear(9, CreateIl2cppString(capeList[i]));
			}
			addCapes = false;
		}

		if (addBoots) {
			for (int i = 0; i < 39; i++) {
				pg3d::player_move_c::AddWear((10), CreateIl2cppString(bootsList[i]));
			}
			addBoots = false;
		}

		if (addArmors) {
			for (int i = 0; i < 25; i++) {
				pg3d::player_move_c::AddArmor(pg3d::player_move_c::webInstance(), pg3d::player_move_c::getWearIndex(armorList[i]), currentLevel, CreateIl2cppString(OBFUSCATE_STR("migr")), offerwallParams);
			}
			addArmors = false;
		}

		if (SpoofName) {
			pg3d::PhotonPlayer::set_NickName(pg3d::PhotonPlayer::get_LocalPlayer(), CreateIl2cppString(getRandomUsername().c_str()));
		}

		if (pg3d::player_move_c::IsMyWeaponSounds(obj)) {

			if (stw) {
				*(bool*)((uint64_t)obj + 0x197) = true;//bulletBreakout
				*(bool*)((uint64_t)obj + 0x194) = true;//bulletSuperBreakout
			}

			if (floatAll || mech) {
				*(bool*)((uint64_t)obj + 0x359) = true;//isFrostSword
				*(float*)((uint64_t)obj + 0x360) = 99999;
				*(float*)((uint64_t)obj + 0x35c) = -0.1;
			}

			if (NukeShoot) {
				*(bool*)((uint64_t)obj + 0x127) = true; // bazooka 
			}

			if (doubleJump) {
				*(bool*)((uint64_t)obj + 0x467) = true; // doubleJump
			}

			if (harpoonbull) {
				*(bool*)((uint64_t)obj + 0x2a8) = true; // harpoon
			}

			if (polymorph) {
				*(bool*)((uint64_t)obj + 0x2dc) = true; // polymorpher
				*(float*)((uint64_t)obj + 0x2e0) = 999999999; // polymorphDuarationTime
				*(float*)((uint64_t)obj + 0x2e4) = 0; // polymorphType
				*(float*)((uint64_t)obj + 0x2e8) = 999999; // polymorphMaxHealth
				harpoonbull = true;
			}

			if (headmagnify) {
				*(bool*)((uint64_t)obj + 0x250) = true; // isHeadMagnifier
				*(float*)((uint64_t)obj + 0x254) = 999999; // headMagnifierTime
			}

			if (recoilandspread) {
				*(float*)((uint64_t)obj + 0x100) = 0; // maxKoofZoom
				*(float*)((uint64_t)obj + 0x104) = 0; // upKoofFireZoom
				*(float*)((uint64_t)obj + 0x108) = 0; // downKoofFirstZoom
				*(float*)((uint64_t)obj + 0x10c) = 0; // downKoofZoom
				*(float*)((uint64_t)obj + 0x94) = 0; // tekKoof
				*(float*)((uint64_t)obj + 0x98) = 0; // upKoofFire
				*(float*)((uint64_t)obj + 0x9c) = 0; // downKoofFirst
				*(float*)((uint64_t)obj + 0xa0) = 0; // downKoof
				*(float*)((uint64_t)obj + 0xa8) = 0; // timerForTekKoofVisual
				*(float*)((uint64_t)obj + 0xac) = 0; // timerForTekKoofVisualByFireRate
				*(float*)((uint64_t)obj + 0xb0) = 0; // timerForTekKoofVisualByFireRate
				*(Vector2*)((uint64_t)obj + 0xf8) = Vector2(0, 0); // startZone
			}

			if (silentAim) {
				*(bool*)((uint64_t)obj + 0x3b0) = true; // isSectorsAOE 
				*(bool*)((uint64_t)obj + 0x33c) = false; // flamethrower 
				*(bool*)((uint64_t)obj + 0x1ac) = false; // railgun 
				*(bool*)((uint64_t)obj + 0x127) = false; // bazooka 
				*(bool*)((uint64_t)obj + 0x2a8) = false; // harpoon 
				*(float*)((uint64_t)obj + 0x3b4) = 360.0f; // sectorsAOEAngleFront 
				*(float*)((uint64_t)obj + 0x3b8) = 360.0f; // sectorsAOEAngleBack
				*(float*)((uint64_t)obj + 0x3c8) = 999999.0f; // sectorsAOERadiusSectorsAoE 
			}

			if (breakcam) {
				*(bool*)((uint64_t)obj + 0x41c) = true; // isElectricShock
				*(float*)((uint64_t)obj + 0x420) = 99999; // electricShockCoeff
				*(float*)((uint64_t)obj + 0x424) = 99999; // electricShockTime
			}

			if (explosionradius) {
				*(float*)((uint64_t)obj + 0x140) = 99999999;
				*(float*)((uint64_t)obj + 0x144) = 0;

			}

			if (instaCharge) {
				*(float*)((uint64_t)obj + 0x1d4) = 0;
			}

			if (floatAll) {
				*(bool*)((uint64_t)obj + 0x258) = true; // isBlindEffect 
				*(EffectType*)((uint64_t)obj + 0x25c) = EffectType::RocketFly; //blindEffect
				*(int*)((uint64_t)obj + 0x260) = 99999999; //isBlindEffectTime
			}

			if (bugAll) {
				teamkill = true;
				for (int i = 0; i < playerList.size(); i++) {
					*(bool*)((uint64_t)obj + 0x258) = true; // harpoon 
					*(EffectType*)((uint64_t)obj + 0x25c) = EffectType::SetMechPlayer; // sectorsAOEAngleFront 
					*(int*)((uint64_t)obj + 0x260) = 50;
					*(bool*)((uint64_t)obj + 0x359) = true;//isFrostSword
					*(float*)((uint64_t)obj + 0x360) = 99999;
					*(float*)((uint64_t)obj + 0x35c) = -0.1;
				}
				mech = false;
				bugAll = false;
				teamkill = false;
			}

			if (mech) {
				*(bool*)((uint64_t)obj + 0x258) = true; // harpoon 
				*(EffectType*)((uint64_t)obj + 0x25c) = EffectType::SetMechPlayer; // sectorsAOEAngleFront 
				*(int*)((uint64_t)obj + 0x260) = 8999999;
			}


			if (ammo) {
				*(bool*)((uint64_t)obj + 0x459) = true;
			}

			if (coinDrop) {
				*(bool*)((uint64_t)obj + 0x320) = true;
				*(float*)((uint64_t)obj + 0x324) = 999999;
			}

			if (forceCritical) {
				*(int*)((uint64_t)obj + 0x30) = 999999;
			}

			if (forceScope) {
				*(bool*)((uint64_t)obj + 0xc4) = true;
			}

			if (reflections) {
				*(int*)((uint64_t)obj + 0x1a8) = 15; // countReflectionRay
			}

			if (flamethrowerBullets) {
				*(bool*)((uint64_t)obj + 0x33c) = true;//flamethrower
			}

			if (railgunBull) {
				*(bool*)((uint64_t)obj + 0x1ac) = true;//railgun
			}

			if (ignoreReflection) {
				*(bool*)((uint64_t)obj + 0x301) = false;//isDamageReflection
				*(bool*)((uint64_t)obj + 0x302) = false;//isDamageAbsorption
			}

			if (charm) {
				*(bool*)((uint64_t)obj + 0x264) = true;
				*(float*)((uint64_t)obj + 0x268) = 999999;
			}

			if (gadgetDisabler) {
				*(bool*)((uint64_t)obj + 0x1e0) = true;
				*(float*)((uint64_t)obj + 0x1e4) = 999999;
			}

			if (speedUp) {
				*(bool*)((uint64_t)obj + 0x214) = true;//isSlowdown
				*(float*)((uint64_t)obj + 0x21c) = 999999;//slowdownCoeff
				*(float*)((uint64_t)obj + 0x218) = 999999;//slowdownTime
			}

			if (slowDown) {
				*(bool*)((uint64_t)obj + 0x214) = true;//isSlowdown
				*(float*)((uint64_t)obj + 0x21c) = -9999999;//slowdownCoeff
				*(float*)((uint64_t)obj + 0x218) = 999999;//slowdownTime
			}

			if (jumpDisable) {
				*(bool*)((uint64_t)obj + 0x1fe) = true;
				*(float*)((uint64_t)obj + 0x200) = 99999999;
			}

			if (poison) {
				*(bool*)((uint64_t)obj + 0x1e8) = true;
				*(float*)((uint64_t)obj + 0x1f4) = 99999999;
			}
			//*(bool*)((uint64_t)obj + 0x1ae) = true;

			//*(int*)((uint64_t)obj + 0x1a4) = 50;

			if (curse) {
				*(bool*)((uint64_t)obj + 0x208) = true;
				*(float*)((uint64_t)obj + 0x20c) = 99999999;
			}
			//*(monoString**)((uintptr_t)obj + 0x148) = CreateIl2cppString(OBFUSCATE_STR("A");

		}
		// useless shit printf(" trolley %s", lol1.c_str());
	}
	oWeaponSounds(obj);
}

void clearPlayerList()
{
	playerList.clear();
	boxDataList.clear();
	headVectors.clear();
	myPlayer = nullptr;
}

void rotateStrings(std::vector<std::string>& strings) {
	std::string firstString = strings[0];
	strings.erase(strings.begin());
	strings.push_back(firstString);
}

monoArray<void*>* CreateMonoArray(std::initializer_list<void*> elements)
{
	size_t size = elements.size();
	monoArray<void*>* array = (monoArray<void*>*)malloc(sizeof(monoArray<void*>) + (size - 1) * sizeof(void*));
	array->klass = nullptr;
	array->monitor = nullptr;
	array->bounds = nullptr;
	array->max_length = static_cast<int>(size);

	void** ptr = array->vector;
	for (auto& element : elements)
	{
		*ptr++ = element;
	}

	return array;
}

int counter = 0;
std::vector<std::string> messages = { "oni >> all", "oni on top!!!", ".gg/onipg" };
void(__stdcall* o_player_move_c)(void* obj);
void __stdcall player_move_c(void* obj) {

	if (obj) {
		if (pg3d::player_move_c::IsMyPlayer(obj))
			myPlayer = obj;
		else
		{
			if (std::find(playerList.begin(), playerList.end(), obj) == playerList.end()) {
				playerList.push_back(obj);
			}
		}
	}
	if (silentAim1 && myPlayer) {
		void* camera = pg3d::Unity::get_main();
		if (myPlayer && playerList.size() > 0 && camera)
		{
			void* closestEnemy = nullptr;
			float minDistance = 999999;

			for (int i = 0; i < playerList.size(); i++)
			{
				void* enemy = playerList[i];
				if (pg3d::PlayerDamageable::isEnemyTo(myPlayer, enemy) && !pg3d::PlayerDamageable::isDead(enemy))
				{
					void* myTransform = pg3d::Unity::GetTransform(myPlayer);
					void* enemyTransform = pg3d::Unity::GetTransform(enemy);

					Vector3 myPos = pg3d::Unity::GetPosition(myTransform);
					Vector3 enemyPos = pg3d::Unity::GetPosition(enemyTransform);
					Quaternion myRotation = pg3d::Unity::GetRotation(myTransform);
					Vector3 enemyScreenPos = pg3d::Unity::WorldToScreenPoint(camera, enemyPos);
					float distance = std::sqrt(pow(enemyPos.X - myPos.X, 2) + pow(enemyPos.Y - myPos.Y, 2) + pow(enemyPos.Z - myPos.Z, 2));
					static const Vector3 forwardDir(0.0f, 0.0f, 1.0f);
					Vector3 playerForwardDirection = myRotation * forwardDir;
					float screenX = (float)resolutionX - ((float)resolutionX - enemyScreenPos.X);
					float screenY = ((float)resolutionY - enemyScreenPos.Y);
					float screenDistance2Middle = sqrt(pow((screenX - (resolutionX / 2)), 2) + pow((screenY - (resolutionY / 2)), 2));

					if (Vector3::Dot(playerForwardDirection, enemyPos - myPos) > 0 &&  // Check if enemy is in front
						Vector3::Magnitude(enemyPos - myPos) < minDistance) {
						if (fov) {
							if (screenDistance2Middle <= fovRadius) {
								minDistance = Vector3::Magnitude(distance);
								closestEnemy = enemy;
							}
						}
						else {
							minDistance = Vector3::Magnitude(distance);
							closestEnemy = enemy;
						}
					}
				}
			}

			if (closestEnemy != nullptr)
			{

				void* myTransform = pg3d::Unity::GetTransform(pg3d::Unity::get_playerTransform(myPlayer));
				void* closestEnemyTransform = pg3d::Unity::GetTransform(closestEnemy);
				Vector3 closestEnemyPos = pg3d::Unity::GetPosition(closestEnemyTransform);
				Vector3 enemyScreenPos = pg3d::Unity::WorldToScreenPoint(camera, closestEnemyPos);
				Vector3 myPos = pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(myPlayer));
				float distanceToClosestEnemy = Vector3::Magnitude(closestEnemyPos - myPos);

				if (enemyScreenPos.Z >= 1 && distanceToClosestEnemy < minDistance)
				{
					baseCamTransform = pg3d::player_move_c::get_baseCameraTransform(myPlayer);

					CurrentCamera = pg3d::Unity::get_Current();
					void* CamCurTransform = pg3d::Unity::GetTransform(CurrentCamera);

					GunCameraTransform = pg3d::player_move_c::GunCamera(myPlayer);
					void* WeaponTransform = pg3d::player_move_c::WeaponTransform(myPlayer);
					void* GunCamera_Tranform = pg3d::Unity::GetTransform(GunCameraTransform);
					void* bulletTransform = pg3d::player_move_c::get_shootCheckPoint(myPlayer);

					// Calculate direction to enemy
					Vector3 bulletPos = pg3d::Unity::GetPosition(bulletTransform);
					Vector3 direction = closestEnemyPos - bulletPos;
					direction.Normalized;


					Vector3 targetEnemyVector = pg3d::Unity::InverseTransformPoint(GunCamera_Tranform, closestEnemyPos);

					float deltaYaw = (std::atan2(targetEnemyVector.Z, targetEnemyVector.X)) * 180 / M_PI;
					float distanceVector = std::sqrt(targetEnemyVector.X * targetEnemyVector.X + targetEnemyVector.Z * targetEnemyVector.Z);

					float pitchOffset = 0.60;
					if (selectedPart == 0)
						pitchOffset = 0.60;
					else if (selectedPart == 1)
						pitchOffset = 0;
					else if (selectedPart == 2)
						pitchOffset = -0.60;

					float deltaPitch = (std::atan2(targetEnemyVector.Y + pitchOffset, distanceVector)) * 180 / M_PI;

					if ((fireCheck && pg3d::player_move_c::get_isShooting(myPlayer)) || (!fireCheck))
					{
						if (VisCheck && pg3d::player_move_c::IsVisibleTargetNew(myPlayer, closestEnemyPos) && pg3d::player_move_c::CanTarget(myPlayer) || (!VisCheck))
						{
							pg3d::Unity::Rotate(WeaponTransform, 0, 0, 0);
							pg3d::Unity::Rotate(GunCamera_Tranform, 0, 0, 0);
							pg3d::Unity::Rotate(bulletTransform, 0, -(deltaYaw - 90), 0);
						}
					}
				}
			}
		}
	}

	if (aimbot) {
		void* camera = pg3d::Unity::get_main();
		if (myPlayer && playerList.size() > 0 && camera) {
			void* closestEnemy = nullptr;
			float minDistance = 999999;

			for (int i = 0; i < playerList.size(); i++) {
				void* enemy = playerList[i];
				if (pg3d::PlayerDamageable::isEnemyTo(myPlayer, enemy) && !pg3d::PlayerDamageable::isDead(enemy)) {
					void* myTransform = pg3d::Unity::GetTransform(myPlayer);
					void* enemyTransform = pg3d::Unity::GetTransform(enemy);

					Vector3 myPos = pg3d::Unity::GetPosition(myTransform);
					Vector3 enemyPos = pg3d::Unity::GetPosition(enemyTransform);
					Quaternion myRotation = pg3d::Unity::GetRotation(myTransform);
					Vector3 enemyScreenPos = pg3d::Unity::WorldToScreenPoint(camera, enemyPos);
					float distance = std::sqrt(pow(enemyPos.X - myPos.X, 2) + pow(enemyPos.Y - myPos.Y, 2) + pow(enemyPos.Z - myPos.Z, 2));
					static const Vector3 forwardDir(0.0f, 0.0f, 1.0f);
					Vector3 playerForwardDirection = myRotation * forwardDir;
					float screenX = (float)resolutionX - ((float)resolutionX - enemyScreenPos.X);
					float screenY = ((float)resolutionY - enemyScreenPos.Y);
					float screenDistance2Middle = sqrt(pow((screenX - (resolutionX / 2)), 2) + pow((screenY - (resolutionY / 2)), 2));

					if (Vector3::Dot(playerForwardDirection, enemyPos - myPos) > 0 &&  // Check if enemy is in front
						Vector3::Magnitude(enemyPos - myPos) < minDistance) {
						if (fov) {
							if (screenDistance2Middle <= fovRadius) {
								minDistance = Vector3::Magnitude(distance);
								closestEnemy = enemy;
							}
						}
						else {
							minDistance = Vector3::Magnitude(distance);
							closestEnemy = enemy;
						}
					}
				}
			}

			if (closestEnemy != nullptr) {

				void* myTransform = pg3d::Unity::GetTransform(pg3d::Unity::get_playerTransform(myPlayer));
				void* closestEnemyTransform = pg3d::Unity::GetTransform(closestEnemy);
				Vector3 closestEnemyPos = pg3d::Unity::GetPosition(closestEnemyTransform);
				Vector3 enemyScreenPos = pg3d::Unity::WorldToScreenPoint(camera, closestEnemyPos);
				Vector3 myPos = pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(myPlayer));
				float distanceToClosestEnemy = Vector3::Magnitude(closestEnemyPos - myPos);

				if (enemyScreenPos.Z >= 1 && distanceToClosestEnemy < minDistance) {
					Vector3 direction = closestEnemyPos - myPos;
					baseCamTransform = pg3d::player_move_c::get_baseCameraTransform(myPlayer);
					Quaternion myRotation = pg3d::Unity::GetRotation(baseCamTransform);
					Vector3 targetEnemyVector = pg3d::Unity::InverseTransformPoint(baseCamTransform, closestEnemyPos);
					float deltaYaw = (std::atan2(targetEnemyVector.Z, targetEnemyVector.X)) * 180 / M_PI;
					float distanceVector = std::sqrt(targetEnemyVector.X * targetEnemyVector.X + targetEnemyVector.Z * targetEnemyVector.Z);

					float pitchOffset = 0.60;
					if (selectedPart == 0)
						pitchOffset = 0.60;
					else if (selectedPart == 1)
						pitchOffset = 0;
					else if (selectedPart == 2)
						pitchOffset = -0.60;

					float deltaPitch = (std::atan2(targetEnemyVector.Y + pitchOffset, distanceVector)) * 180 / M_PI;


					float centerX = resolutionX / 2.0f;
					float centerY = resolutionY / 2.0f;

					if ((fireCheck && pg3d::player_move_c::get_isShooting(myPlayer)) || (!fireCheck))
					{
						if (VisCheck && pg3d::player_move_c::IsVisibleTargetNew(myPlayer, closestEnemyPos) && pg3d::player_move_c::CanTarget(myPlayer) || (!VisCheck))
						{
							pg3d::Unity::Rotate(baseCamTransform, -(deltaPitch), 0, 0);
							pg3d::Unity::Rotate(myTransform, 0, -(deltaYaw - 90), 0);

							//pg3d::Unity::LookAt(myTransform, closestEnemyTransform);
							//pg3d::Unity::LookAt(baseCamTransform, closestEnemyTransform);
						}
					}
				}

			}
		}
	}

	if (invisible) {

		for (int i = 0; i < playerList.size(); i++) {
			void* enemy = playerList[i];
			if (enemy) {
				pg3d::player_move_c::MakeInvisibleForSecondsRPC(enemy, 88888);
			}
		}
		invisible = false;
	}

	if (speed && myPlayer) {
		Vector3 currPos = pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(myPlayer));
		Vector3 cameraPos = pg3d::Unity::GetPosition(pg3d::player_move_c::get_baseCameraTransform(myPlayer));
		Quaternion cameraRotation = pg3d::Unity::GetRotation(pg3d::player_move_c::get_baseCameraTransform(myPlayer));

		Vector3 forwardVector = cameraRotation * Vector3::Forward();
		Vector3 rightVector = cameraRotation * Vector3::Right();

		Vector3 horizontalForward = forwardVector;
		horizontalForward.Y = 0;

		if (horizontalForward != Vector3::Zero()) {
			horizontalForward.Normalized(horizontalForward);
		}

		Vector3 newPosition = currPos;

		if (GetAsyncKeyState(0x57) & 0x8000) {
			newPosition += horizontalForward * (speedVal / 650);
		}

		if (GetAsyncKeyState(0x41) & 0x8000) {
			newPosition -= rightVector * (speedVal / 650);
		}

		if (GetAsyncKeyState(0x53) & 0x8000) {
			newPosition -= horizontalForward * (speedVal / 650);
		}

		if (GetAsyncKeyState(0x44) & 0x8000) {
			newPosition += rightVector * (speedVal / 650);
		}

		pg3d::Unity::SetPosition(pg3d::Unity::get_playerTransform(myPlayer), newPosition);
	}



	if (fly && myPlayer) {
		Vector3 myPos = pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(myPlayer));
		baseCamTransform = pg3d::player_move_c::get_baseCameraTransform(myPlayer);
		Quaternion myRotation = pg3d::Unity::GetRotation(baseCamTransform);
		Vector3 forwardVector = Vector3::Forward();
		Vector3 rightVector = Vector3::Right();


		forwardVector = myRotation * forwardVector;
		rightVector = myRotation * rightVector;
		static Vector3 prevPos = myPos;


		if (GetAsyncKeyState(0x57) & 0x8000) {
			// Move forward
			myPos += forwardVector * flySpeed;
		}
		else if (GetAsyncKeyState(0x53) & 0x8000) {
			// Move backward
			myPos -= forwardVector * flySpeed;
		}
		else if (GetAsyncKeyState(0x41) & 0x8000) {
			myPos -= rightVector * flySpeed;
		}
		else if (GetAsyncKeyState(0x44) & 0x8000) {
			myPos += rightVector * flySpeed;
		}
		else if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
			myPos += (myRotation * Vector3::Up()) * flySpeed;
		}
		else if (GetAsyncKeyState(VK_LSHIFT) & 0x8000) {
			myPos += (myRotation * Vector3::Down()) * flySpeed;
		}

		else {
			myPos = prevPos;
		}

		prevPos = myPos;
		pg3d::Unity::SetPosition(pg3d::Unity::get_playerTransform(myPlayer), myPos);
	}

	if (telekill && myPlayer) {
		if (!pg3d::player_move_c::IsMyPlayer(obj) && pg3d::PlayerDamageable::isEnemyTo(myPlayer, obj)) {
			pg3d::Unity::SetPosition(pg3d::Unity::get_playerTransform(obj), pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(myPlayer)) + Vector3(0, 0, 3));
		}
	}

	if (spamRockets) {
		for (size_t i = 0; i < playerList.size(); i++) {
			void* enemy = playerList[i];
			if (enemy) {
				if (pg3d::PlayerDamageable::isEnemyTo(myPlayer, enemy) &&
					!pg3d::PlayerDamageable::isDead(enemy) &&
					!pg3d::player_move_c::IsMyPlayer(enemy)) {
					void* enemyTransform = pg3d::Unity::GetTransform(enemy);
					if (enemyTransform) {
						Quaternion enemyRotation = pg3d::Unity::GetRotation(enemyTransform);
						Vector3 e_Pos = pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(enemy));
						void* myCurrentWeaponSounds = *(void**)((uintptr_t)obj + 0x638);
						if (myCurrentWeaponSounds) {
							pg3d::player_move_c::CreateRocket(myCurrentWeaponSounds, e_Pos, enemyRotation, 1.0f, 1);
						}
					}
				}
			}
		}
	}

	if (massKill && myPlayer) {
		for (int i = 0; i < playerList.size(); i++) {
			void* enemy = playerList[i];
			if (!pg3d::player_move_c::IsMyPlayer(enemy) && pg3d::PlayerDamageable::isEnemyTo(myPlayer, enemy) && !pg3d::PlayerDamageable::isDead(enemy)) {
				Vector3 e_Pos = pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(enemy));
				pg3d::Unity::SetPosition(pg3d::Unity::get_playerTransform(myPlayer), Vector3(e_Pos.X - 2, e_Pos.Y, e_Pos.Z));
			}
		}
	}


	if (setMyScale && myPlayer) {
		pg3d::Unity::SetLocalScale(pg3d::Unity::get_playerTransform(myPlayer), Vector3(myScale, myScale, myScale));
	}

	if (setOtherScale && myPlayer) {
		if (!pg3d::player_move_c::IsMyPlayer(obj) && pg3d::PlayerDamageable::isEnemyTo(myPlayer, obj)) {
			pg3d::Unity::SetLocalScale(pg3d::Unity::get_playerTransform(obj), Vector3(otherScale, otherScale, otherScale));
		}
	}
	/*if (triggerBot && myPlayer) {
		for (int i = 0; i < playerList.size(); i++) {
			void* enemy = playerList[i];
			if (enemy) {
				void* myTransform = pg3d::Unity::GetTransform(myPlayer);
				void* enemyTransform = pg3d::Unity::GetTransform(enemy);
				void* camera = pg3d::Unity::get_main();
				Vector3 enemyPos = pg3d::Unity::GetPosition(enemyTransform);
				Quaternion myRotation = pg3d::Unity::GetRotation(myTransform);
				Vector3 enemyScreenPos = pg3d::Unity::WorldToScreenPoint(camera, enemyPos);
				Vector3 screenCenter(resolutionX / 2, resolutionY / 2, 0);
				float tolerance = 20.0f; // Example tolerance level
				float minX = screenCenter.X - tolerance;
				float maxX = screenCenter.X + tolerance;
				float minY = screenCenter.Y - tolerance;
				float maxY = screenCenter.Y + tolerance;

				if (enemyScreenPos.X >= minX && enemyScreenPos.X <= maxX && enemyScreenPos.Y >= minY && enemyScreenPos.Y <= maxY) {
					printf("yes");

					mouse_event(MOUSEEVENTF_LEFTDOWN, resolutionX / 2, resolutionY / 2, 0, 0);

				}
			}
		}
	}*/

	if (esp) {
		void* camera = pg3d::Unity::get_main();
		if (myPlayer && playerList.size() > 0 && camera) {
			headVectors.clear();
			boxDataList.clear();
			for (int i = 0; i < playerList.size(); i++) { // Start from index 0
				void* enemy = playerList[i];

				void* myTransform = pg3d::Unity::GetTransform(myPlayer);
				void* enemyTransform = pg3d::Unity::GetTransform(enemy);

				Vector3 myPos = pg3d::Unity::GetPosition(myTransform);
				Vector3 enemyPos = pg3d::Unity::GetPosition(enemyTransform);

				float distance = Vector3::Distance(enemyPos, myPos);
				if (pg3d::PlayerDamageable::isEnemyTo(myPlayer, enemy) && !pg3d::PlayerDamageable::isDead(enemy) && !pg3d::player_move_c::IsMyPlayer(enemy)) {
					Vector3 w2sPoint = pg3d::Unity::WorldToScreenPoint(camera, enemyPos);
					if (w2sPoint.Z > 0) {
						Vector3 w2s = pg3d::Unity::WorldToScreenPoint(camera, enemyPos - Vector3(0, 1.1, 0));
						Vector3 head = pg3d::Unity::WorldToScreenPoint(camera, enemyPos + Vector3(0, 1, 0));
						headVectors.push_back(head); // Store head vector in the container
						Vector2 to = Vector2(head.X, resolutionY - head.Y);
						float boxHeight = abs(head.Y - w2s.Y);
						float boxWidth = boxHeight * 0.65f;
						Vector2 vBox = { head.X - (boxWidth / 2), head.Y };;
						boxData.head = head;
						boxData.vBox = vBox;
						boxData.boxWidth = boxWidth;
						boxData.boxHeight = boxHeight;
						boxData.distance = distance;
						boxData.name = pg3d::player_move_c::GetPlayerName(enemy);
						boxDataList.push_back(boxData);
					}
				}
			}
		}
	}

	if (!pg3d::player_move_c::IsMyPlayer(obj) && breakGuns)
	{
		pg3d::player_move_c::_Shot(obj);
		pg3d::player_move_c::ShootS(obj);
	}



	if (clonePlayer && myPlayer) {

		pg3d::Unity::Instantiate(CreateIl2cppString(OBFUSCATE_STR("Player")), pg3d::Unity::GetPosition(pg3d::Unity::GetTransform(myPlayer)), Quaternion(0, 0, 0, 0), 0);
		clonePlayer = false;
	}

	if (pg3d::player_move_c::IsMyPlayer(obj)) {


		if (invisibleMe) {
			pg3d::player_move_c::MakeInvisibleForSecondsRPC(obj, 8888888);
			invisibleMe = false;
		}

		if (jump) {
			void* mySkinName = *(void**)((uintptr_t)obj + 0x678);
			if (mySkinName) {
				void* firstPersonControl = *(void**)((uintptr_t)mySkinName + 0x1e0);
				*(float*)((uintptr_t)firstPersonControl + 0x4B0) = jumpVal;
			}
		}


		if (chatSpam) {
			rotateStrings(messages);
			std::string newMessage = messages[0];
			pg3d::player_move_c::SendChat(obj, CreateIl2cppString(newMessage.c_str()), false, CreateIl2cppString(OBFUSCATE_STR("0")));
		}

		if (chams) {
			pg3d::player_move_c::ShowXray(obj, true, ZoomTypes::XRay);
		}

		if (addJetpack) {
			pg3d::player_move_c::EnableJetpack(obj, true);
			addJetpack = false;
		}

		void* PlayerDamageable = *(void**)((uintptr_t)obj + 0x668);
		if (ammo) {
			pg3d::player_move_c::AddAmmoFromWeaponOnline(PlayerDamageable, 50);
		}
	}
	o_player_move_c(obj);
}


bool(__stdcall* oValidateNickName)(...);
bool __stdcall ValidateNickName(void* obj, monoString* yes) {
	return true;
}

bool(__stdcall* oValidateNickNameNoAnalytics)(...);
bool __stdcall ValidateNickNameNoAnalytics(void* obj, monoString* yes) {
	return true;
}


void* (__stdcall* ofilter)();
void* __stdcall filter(monoString* yes) {
	if (hideNames)
		return NULL;

	return yes;
}

void(__stdcall* oWeaponManager)(void* obj);
void __stdcall WeaponManager(void* obj) {

	if (obj) {

		if (addWeapons) {
			pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[arrayStart - 1]), offerwallParams);
			addWeapons = false;
		}


		if (addWeapons1) {
			printf("Weapons 0-150 \n\n");
			for (int i = 0; i < 150; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
			addWeapons1 = false;
		}

		if (addWeapons2) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));
			printf("Weapons 151-300 \n\n");
			for (int i = 151; i < 300; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}

			addWeapons2 = false;
		}

		if (addWeapons3) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));

			printf("Weapons 301-450 \n\n");
			for (int i = 301; i < 450; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
			addWeapons3 = false;

		}

		if (addWeapons4) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));

			printf("Weapons 451-600 \n\n");
			for (int i = 451; i < 600; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
			addWeapons4 = false;
		}

		if (addWeapons5) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));

			printf("Weapons 601-750 \n\n");
			for (int i = 601; i < 750; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
			addWeapons5 = false;
		}

		if (addWeapons6) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));

			printf("Weapons 751-900 \n\n");
			for (int i = 751; i < 900; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
			addWeapons6 = false;
		}

		if (addWeapons7) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));

			printf("Weapons 1001-1140 \n\n");
			for (int i = 901; i < 1050; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
		}
		addWeapons7 = false;

		if (addWeapons8) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));

			printf("Weapons 1001-1150 \n\n");
			for (int i = 1050; i < 1200; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
			addWeapons8 = false;
		}

		if (addWeapons9) {
			pg3d::Unity::LoadScene(CreateIl2cppString(OBFUSCATE_STR("Menu_Custom")));

			printf("Weapons 1201-1309 \n\n");
			for (int i = 1201; i < 1309; i++) {
				pg3d::player_move_c::AddWeapon(obj, CreateIl2cppString(weaponList[i]), offerwallParams);
			}
			addWeapons9 = false;
		}
	}
	oWeaponManager(obj);
}

void(__stdcall* odestroyDrone)(void* obj);
void __stdcall destroyDrone(void* obj) {
	if (droneGod)
		return;

	odestroyDrone(obj);
}

void(__stdcall* odestroyDrone1)(...);
void __stdcall destroyDrone1(void* obj, void* a1) {
	if (droneGod)
		return;

	odestroyDrone1(obj, a1);
}

void(__stdcall* oplayer_move_cDestroy)(void* obj);
void __stdcall player_move_cDestroy(void* obj) {
	if (obj) {
		clearPlayerList();
	}
	oplayer_move_cDestroy(obj);
}

int(__stdcall* oclanParts)(...);
int __stdcall clanParts(void* obj, int a1) {
	if (freeClanParts)
		return -1;

	return oclanParts(obj, a1);
}

int(__stdcall* oclanParts1)(...);
int __stdcall clanParts1(void* obj, int a1) {
	if (freeClanParts)
		return -1;

	return oclanParts1(obj, a1);
}


int(__stdcall* oget_UpgradeTime)(...);
int __stdcall get_UpgradeTime(void* obj, int a1) {
	if (instantUpgrades)
		return 3;

	return oget_UpgradeTime(obj, a1);
}

bool(__stdcall* oweaponSkins)(...);
bool __stdcall weaponSkins(void* obj, void* a1) {
	if (buyWeaponSkins)
		return true;

	return oweaponSkins(obj, a1);
}

int(__stdcall* olevel)(...);
int __stdcall level() {
	currentLevel = olevel();
	return olevel();
}

float(__stdcall* oReload)(...);
float __stdcall Reload(void* obj, void* wp, void* a1, void* a2, void* a3) {
	if (noreload) {
		return 99999;
	}

	return oReload(obj, wp, a1, a2, a3);
}

bool(__stdcall* oTeamkill)(...);
bool __stdcall Teamkill(void* obj, void* a1) {
	if (teamkill) {
		return false;
	}

	return oTeamkill(obj, a1);
}

bool(__stdcall* oTeamkill1)(...);
bool __stdcall Teamkill1(void* obj) {
	if (teamkill) {
		return false;
	}

	return oTeamkill1(obj);
}

int(__stdcall* omodUp)(...);
int __stdcall modUps(void* obj, int a) {
	if (modUp) {
		return 0;
	}
	return omodUp(obj, a);
}

void* (__stdcall* obundles)(...);
void* __stdcall bundles(void* obj) {//0x20C16C0{
	if (bundles)
		return nullptr;

	return obundles(obj);
}



void* (__stdcall* obundles1)(...);
void* __stdcall bundles1(void* obj) {//0x55AE60
	if (bundles)
		return nullptr;

	return obundles1(obj);
}

int(__stdcall* oget_Energy)(...);
int __stdcall get_Energy(void* obj) {
	if (clanEnergy) {
		return 0;
	}

	return oget_Energy(obj);
}

int(__stdcall* ounlockWear1)(...);
int __stdcall unlockWear1(void* obj) {
	if (unlockWear) {
		return lotteryAmount;
	}

	return ounlockWear1(obj);
}

void(__stdcall* oPetEngine)(void* obj);
void __stdcall PetEngine(void* obj) {
	void* petInfo = *(void**)((uintptr_t)obj + 0x90);
	if (petInfo) {
		if (pspeed) {
			*(float*)((uint64_t)obj + 0x1B4) = 999999;
			*(float*)((uint64_t)obj + 0x1B8) = 999999;
		}

		if (pgod) {
			pg3d::petengine::SetHealth(obj, 999999);
		}
	}
	oPetEngine(obj);
}

extern int rocketNum;
void(__stdcall* oRocket)(void* obj);
void __stdcall Rocket(void* obj) {
	void* RocketSettings = *(void**)((uintptr_t)obj + 0x28);
	void* PlayermovecPtr = *(void**)((uintptr_t)obj + 0x1C8);
	//void* SkinNamePtr = *(void**)((uintptr_t)PlayermovecPtr + 0x678);
	//bool isMine = *(bool**)((uintptr_t)SkinNamePtr + 0xC0);


	if (!RocketSettings)
		return oRocket(obj);

	if (!PlayermovecPtr)
		return oRocket(obj);


	if (RocketSettings) {
		*(int*)((uintptr_t)RocketSettings + 0x48) = rocketNum;
		*(bool*)((uintptr_t)RocketSettings + 0x7f) = false;

	}

	if (pg3d::player_move_c::IsMyPlayer(PlayermovecPtr)) {
		if (gravity) {
			*(bool*)((uintptr_t)obj + 0x78) = true;
		}

		if (NukeShoot) {
			*(monoString**)((uintptr_t)obj + 0x68) = CreateIl2cppString(OBFUSCATE_STR("a-bomb_mini"));
			*(monoString**)((uintptr_t)obj + 0x70) = CreateIl2cppString(OBFUSCATE_STR("a-bomb_mini"));
		}

		if (longLifetime) {
			*(float*)((uintptr_t)RocketSettings + 0x54) = std::numeric_limits<float>::infinity();
		}

		if (ricochet) {
			*(bool*)((uintptr_t)RocketSettings + 0x160) = true;
			*(int*)((uintptr_t)RocketSettings + 0x164) = INT_MAX;
		}

		switch (rocketMode) {
		case 1:
			*(int*)((uintptr_t)RocketSettings + 0x48) = 10;
			*(float*)((uintptr_t)RocketSettings + 0xD4) = 15.0f;
			*(float*)((uintptr_t)RocketSettings + 0xD8) = std::numeric_limits<float>::infinity();
			*(float*)((uintptr_t)RocketSettings + 0x198) = std::numeric_limits<float>::infinity();
			break;

		case 2:
			*(int*)((uintptr_t)RocketSettings + 0x48) = 4;
			*(float*)((uintptr_t)RocketSettings + 0xD4) = 15.0f;
			break;
		}
	}
	oRocket(obj);
}

float(__stdcall* opetDamage)(...);
float __stdcall petDamage(void* obj) {
	if (pdamage) {

		return 9999999;
	}

	return opetDamage(obj);
}

float(__stdcall* opetSpeed)(...);
float __stdcall petSpeed(void* obj) {
	if (pdamage) {
		return 9999999;
	}

	return opetSpeed(obj);
}


float(__stdcall* ogadgetCooldown)(...);
float __stdcall gadgetCooldown(void* obj) {
	if (gadgetcd) {
		return 0;
	}

	return ogadgetCooldown(obj);
}

bool(__stdcall* oenemyToHooked)(...);
bool __stdcall enemyToHooked(void* obj, void* me) {
	if (teamkill)
		return true;

	return oenemyToHooked(obj, me);
}
/*void(__stdcall* oAuthSceneController)(...);
void __stdcall LoadScene(monoString* level) {
	printf("%s", level);
	level = CreateIl2cppString(OBFUSCATE_STR("SteamNewGameWindows");
	//void* StartNewGameWindows = *(void**)((uintptr_t)obj + 0x30);
	if (fly) {
		//pg3d::player_move_c::NewGame(obj, true);
		fly = false;
	}
	oAuthSceneController(level);
}*/

bool(__stdcall* ogameType23)(...);
bool __stdcall gameType23(void* obj) {
	if (sandboxAll)
		return true;

	return ogameType23(obj);
}

void(__stdcall* oTurretController)(void* obj);
void __stdcall TurretController(void* obj) {
	if (turretDmg)
		*(float*)((uint64_t)obj + 0x30) = 4;

	if (turretGod) {
		*(float*)((uint64_t)obj + 0xDC) = 999999;
		*(float*)((uint64_t)obj + 0x34) = 999999;
		*(float*)((uint64_t)obj + 0xD8) = 999999;
	}

	if (turretRange) {
		*(float*)((uint64_t)obj + 0x38) = 999999;
	}

	oTurretController(obj);
}

bool(__stdcall* oVIPActive)(void* obj);
bool __stdcall VIPActive(void* obj) {
	if (Vip) {
		return true;
	}

	return oVIPActive(obj);
}

void(__stdcall* oGameModeController)(...);
void __stdcall GameModeController(void* obj) {
	if (thirdPerson) {
		*(bool*)((uintptr_t)obj + 0x191) = true;
		*(bool*)((uintptr_t)obj + 0x192) = true;
	}

	oGameModeController(obj);
}

int (*oSpoofModules)(void* obj);
int spoofModule(void* obj) {
	if (obj && spoofModules) {
		return spoofModVal;
	}
	return oSpoofModules(obj);
}

void InitHook() {

	MH_Initialize();
	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::PetInfo::petdamageoffset), &petDamage, (LPVOID*)&opetDamage);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::PetInfo::petdamageoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::PetInfo::petspeedoffset), &petSpeed, (LPVOID*)&opetSpeed);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::PetInfo::petspeedoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::turretupdateoffset), &TurretController, (LPVOID*)&oTurretController);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::turretupdateoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::GadgetG::gadgetcdoffset), &gadgetCooldown, (LPVOID*)&ogadgetCooldown);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::GadgetG::gadgetcdoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::ExperienceController::maxlvloffset), &level, (LPVOID*)&olevel);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::ExperienceController::maxlvloffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::LobbyItem::bundle1offset), &bundles1, (LPVOID*)&obundles1);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::LobbyItem::bundle1offset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::SkinName::ontriggerneter), &OnTriggerEnter, (LPVOID*)&oOnTriggerEnter);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::SkinName::ontriggerneter));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::playerscorecontroller), &PlayerScoreController, (LPVOID*)&oPlayerScoreController);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::playerscorecontroller));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::SkinName::oncolliderhit), &OnControllerColliderHit, (LPVOID*)&oOnControllerColliderHit);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::SkinName::oncolliderhit));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::ItemModule::modupoffset), &modUps, (LPVOID*)&omodUp);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::ItemModule::modupoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::ExperienceController::addexperience), &AddEXP, (LPVOID*)&oAddEXP);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::ExperienceController::addexperience));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::PlaceableItemSettings::clanenergyoffset), &get_Energy, (LPVOID*)&oget_Energy);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::PlaceableItemSettings::clanenergyoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::weaponmanager), &WeaponManager, (LPVOID*)&oWeaponManager);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::weaponmanager));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::NickNameValidator::validatenick), &ValidateNickName, (LPVOID*)&oValidateNickName);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::NickNameValidator::validatenick));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::NickNameValidator::validatenickanalytics), &ValidateNickNameNoAnalytics, (LPVOID*)&oValidateNickNameNoAnalytics);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::NickNameValidator::validatenickanalytics));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::FilterBadWorld::filteroffset), &filter, (LPVOID*)&ofilter);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::FilterBadWorld::filteroffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::gamemodecontrollerupdate), &GameModeController, (LPVOID*)&oGameModeController);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::gamemodecontrollerupdate));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::PlaceableItemSettings::clanparts), &clanParts, (LPVOID*)&oclanParts);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::PlaceableItemSettings::clanparts));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::PlaceableItemSettings::clanparts1), &clanParts1, (LPVOID*)&oclanParts1);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::PlaceableItemSettings::clanparts1));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::PlaceableItemSettings::upgradetime), &get_UpgradeTime, (LPVOID*)&oget_UpgradeTime);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::PlaceableItemSettings::upgradetime));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::ShopHelper::weaponskins), &weaponSkins, (LPVOID*)&oweaponSkins);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::ShopHelper::weaponskins));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::Rocket::rocketUpd), &Rocket, (LPVOID*)&oRocket);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::Rocket::rocketUpd));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::ItemModule::spoofModule), &spoofModule, (LPVOID*)&oSpoofModules);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::ItemModule::spoofModule));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::WeaponManager::SetWeaponsSetUpd), &SetWeaponsSet, (LPVOID*)&_SetWeaponsSet);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::WeaponManager::SetWeaponsSetUpd));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::weaponsoundsupdate), &WeaponSounds, (LPVOID*)&oWeaponSounds);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::weaponsoundsupdate));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::PlayerDamageable::enemyto), &enemyToHooked, (LPVOID*)&oenemyToHooked);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::PlayerDamageable::enemyto));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::player_move_cupdate), &player_move_c, (LPVOID*)&o_player_move_c);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::player_move_cupdate));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::playermovecdestroy), &player_move_cDestroy, (LPVOID*)&oplayer_move_cDestroy);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::playermovecdestroy));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::VIPController::activevip), &VIPActive, (LPVOID*)&oVIPActive);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::VIPController::activevip));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::EffectsController::reloadoffset), &Reload, (LPVOID*)&oReload);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::EffectsController::reloadoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::ItemPrice::freekeysoffset), &unlockWear1, (LPVOID*)&ounlockWear1);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::ItemPrice::freekeysoffset));

	MH_CreateHook(reinterpret_cast<LPVOID*>(gameAssembly + Offsets::UpdateFunctions::petengineupdate), &PetEngine, (LPVOID*)&oPetEngine);
	MH_EnableHook(reinterpret_cast<LPVOID*> (gameAssembly + Offsets::UpdateFunctions::petengineupdate));
}
