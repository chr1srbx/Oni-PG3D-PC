#pragma once
#include "imgui/imgui.h"
#include "imgui/elements.h"
#include "game/hook.h"
#include "game/ESP.h"
#include <vector>
#include "game/types.h"
#include "unity/unity.h"
#include "obuscator.h"
#include "obfString.hpp"
#include "protection/AntiDebug.hpp"
#include "main.h";
enum heads {
	AIMBOT,
	ACCOUNT,
	VISUALS,
	SETTINGS,
	PLAYER,
	WEAPON,
	MISC
};

namespace fonts {
	ImFont* medium;
	ImFont* semibold;
	ImFont* logo;
};

std::vector<Lines> boneLines;
std::vector<Vector3> headVectors;
std::vector<EspData> boxDataList;
static heads head_selected = AIMBOT;

const char* curList[] = { "GemsCurrency", "Coins", "ClanSilver", "ClanLootBoxPoints", "Coupons", "PixelPassCurrency", "RouletteAdsCurrency", "RouletteAdsSpin", "PixelBucks", "BattlePassCurrency", "CurrencyCompetitionTier1", "CurrencyCompetitionTier2" };
const char* bodyList[] = { "Head", "Body", "Feet" };
const char* graffitiList1[] = { "graffiti_1028", "graffiti_2028", "graffiti_3028", "graffiti_4028", "graffiti_5028", "graffiti_6028", "graffiti_7028", "graffiti_8028", "graffiti_9028", "graffiti_10028", "graffiti_11028", "graffiti_12028", "graffiti_13028", "graffiti_14028", "graffiti_15028", "graffiti_16028", "graffiti_17028", "graffiti_18028", "graffiti_19028", "graffiti_20028", "graffiti_21028", "graffiti_22028", "graffiti_23028", "graffiti_24028", "graffiti_25028", "graffiti_26028", "graffiti_27028", "graffiti_28028", "graffiti_29028", "graffiti_30028", "graffiti_31028", "graffiti_32028", "graffiti_33028", "graffiti_34028", "graffiti_35028", "graffiti_36028", "graffiti_37028", "graffiti_38028", "graffiti_39028", "graffiti_40028", "graffiti_41028", "graffiti_42028", "graffiti_43028" };
const char* rocketMode1[] = { "None", "Homing", "Follow Crosshair" };
//aim
bool aimbot, fireCheck, fov, silentAim, triggerBot, silentAim1, stw, triggerbot, VisCheck;
int selectedPart;
float fovRadius, smoothVal;
float myScale, otherScale;

//visual
bool esp, lines, box, chams, names, thirdPerson;

//statistic
bool experience, addCurrency, addArmors, addCapes, addBoots, addHats, godAll, addMasks, addPets, unlockWear, modUp, addWeapons, unlockAll, addGraffiti, addWeaponSkins, floatAll, mech
,addGadgets, buyWeaponSkins, Vip, addWeapons1, addWeapons2, addWeapons3, addWeapons4, addWeapons5, addWeapons6, addWeapons7, bugAll, addWeapons8, addWeapons9, infiniteAmmo, sandboxGuns;
int selectedCur, currAmount, expVal, arrayStart, arrayEnd, lotteryAmount, selectedGraffiti, rocketNum, spoofModVal;

//player
bool godmode, speed, fly, instaCharge, jump, addJetpack, doubleJump, invisible, invisibleMe, setMyScale, setOtherScale, clonePlayer, spamRockets, freeze, spoofModules;
float speedVal, jumpVal, flySpeed;

//weapon
bool ammo, recoilandspread, noreload, explosionradius, breakcam, polymorph, harpoonbull, headmagnify, blik, stealAmmo, coinDrop, firerate, damageMod;
float fireRateVal, damageCoeff;

//game
bool killall, playerscore, teamkill, chatSpam, turret, turretGod, turretDmg, turretRange, gadgetcd, pet, pgod, pspeed, pdamage, telekill, hideNames, playerscoreAdd,
forceCritical, glitchEveryone, forceScope, reflections, flamethrowerBullets, railgunBull, ignoreReflection, charm, gadgetDisabler, speedUp, slowDown, jumpDisable, poison, curse
, stun, droneGod, quickScope, noBR, sandboxAll, SpoofName, breakGuns, freezeall, timescale;

float timeScaleVal;

//clan
bool clanEnergy, freeClanParts, instantUpgrades, clan;

//settings
bool unlockCur, unlockEXP, BanTraceCleaner, showConfirmationPopup;

int resolutionX, resolutionY, rocketMode;
bool ricochet, NukeShoot, massKill, gravity, longLifetime, spamRocket, bundles, explosive;



ImVec4 boxColor = ImColor(255, 255, 255);
ImVec4 FilledBoxColor = ImColor(255, 255, 255);
ImVec4 lineColor = ImColor(255, 255, 255);
ImVec4 nameColor = ImColor(255, 255, 255);

void DrawESP() {
	if (lines) {
		auto background = ImGui::GetBackgroundDrawList();
		ImVec4 color(1.0f, 0.0f, 0.0f, 1.0f); // Red color
		for (const auto& head : headVectors) {
			DrawLine(ImVec2(resolutionX / 2, 0), ImVec2(head.X, resolutionY - head.Y), ImVec4(lineColor), background);
		}
	}

	if (box) {
		auto background = ImGui::GetBackgroundDrawList();
		for (const auto& espData : boxDataList) {
			float boxHeight = espData.boxHeight;
			float boxWidth = espData.boxWidth;
			Vector2 vBox = espData.vBox;
			Vector3 head = espData.head;

			ImVec2 boxMin = ImVec2(head.X - (boxWidth / 2), head.Y - boxHeight);
			ImVec2 boxMax = ImVec2(head.X + (boxWidth / 2), head.Y);

			DraEdgesRectFil(vBox.X, resolutionY - vBox.Y, boxWidth, boxHeight, ImColor(FilledBoxColor), ImColor(boxColor), background);
		}
	}

	if (names) {
		auto background = ImGui::GetBackgroundDrawList();
		for (const auto& espData : boxDataList) {
			float boxHeight = espData.boxHeight;
			float boxWidth = espData.boxWidth;
			Vector2 vBox = espData.vBox;
			Vector3 head = espData.head;
			std::string name = espData.name;
			float distance = espData.distance;

			ImVec2 namePos = ImVec2(vBox.X - (boxWidth / 2) - (name.length() * 3 / 2), resolutionY - vBox.Y - 25);

			const float thresholdDistance = 25.0f;
			const float offsetFactor = 100.f;
			if (distance < thresholdDistance) {
				float offset = offsetFactor * (1.0f - exp(-distance * 0.01f));
				namePos.x += offset;
			}

			// Draw the name above the box
			background->AddText(namePos, ImColor(nameColor), name.c_str());
		}
	}

	if (names)
	{
		auto background = ImGui::GetBackgroundDrawList();
		for (const auto& line : boneLines)
		{
			// Convert Vector3 to ImVec2 (screen positions)
			ImVec2 start(line.start.X, line.start.Y);
			ImVec2 end(line.end.X, line.end.Y);

			// Draw the line using your DrawLine function
			DrawLine(start, end, ImColor(255, 0, 0, 255), background);
		}
	}
}

void DrawAimbot() {

	auto draw = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Main"));
	ImGui::SetCursorPos({ 25, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Main"), ImVec2(215, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Aimbot"), &aimbot);
		ImGui::Checkbox(OBFUSCATE_STR("FOV"), &fov);
		ImGui::Checkbox(OBFUSCATE_STR("Visual Check"), &VisCheck);

		if (fov) {
			ImGui::SliderFloat(OBFUSCATE_STR("FOV Radius"), &fovRadius, 10.0, 360);
		}
		ImGui::Checkbox(OBFUSCATE_STR("Fire Check"), &fireCheck);

		ImGui::TextUnformatted(OBFUSCATE_STR(" "));
		ImGui::Combo(OBFUSCATE_STR("Body Part"), &selectedPart, bodyList, IM_ARRAYSIZE(bodyList));
		ImGui::TextUnformatted(OBFUSCATE_STR(" "));
	}

	ImGui::EndChild();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 255, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Rage"));
	ImGui::SetCursorPos({ 255, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Rage"), ImVec2(255, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Obvious Silent-Aim"), &silentAim);
		ImGui::Checkbox(OBFUSCATE_STR("Legit Silent-Aim"), &silentAim1);
		ImGui::Checkbox(OBFUSCATE_STR("TriggerBot"), &triggerBot);
	}
	ImGui::EndChild();
}

void DrawVisuals() {
	auto draw = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("ESP"));
	ImGui::SetCursorPos({ 25, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Main"), ImVec2(215, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Main Switch"), &esp);
		ImGui::Checkbox(OBFUSCATE_STR("Boxes"), &box);
		ImGui::Checkbox(OBFUSCATE_STR("Lines"), &lines);
		ImGui::Checkbox(OBFUSCATE_STR("Names"), &names);
	}

	ImGui::EndChild();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 255, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("In-Game"));
	ImGui::SetCursorPos({ 255, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Rage"), ImVec2(255, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Chams"), &chams);
		ImGui::Checkbox(OBFUSCATE_STR("Third Person Camera"), &thirdPerson);
		ImGui::TextUnformatted(OBFUSCATE_STR("Aimbot & ESP wont work"));
		ImGui::TextUnformatted(OBFUSCATE_STR("Enable it in lobby."));
	}
	ImGui::EndChild();
}

void DrawAccount() {
	auto draw = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Currency"));
	ImGui::SetCursorPos({ 25, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Main"), ImVec2(215, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Modify EXP Reward"), &experience);
		if (experience) {

			if (expVal > 32645)
				expVal = 32645;

			ImGui::InputInt(OBFUSCATE_STR("EXP Amount"), &expVal);

			if (!unlockEXP && expVal > 2000) {
				expVal = 2000;
				ImGui::TextUnformatted(OBFUSCATE_STR("Unlock EXP In Settings."));
			}
			ImGui::Separator();
		}

		ImGui::InputInt(OBFUSCATE_STR("Curr Amount"), &currAmount);
		if (!unlockCur && currAmount > 10000) {
			currAmount = 10000;
			ImGui::TextUnformatted(OBFUSCATE_STR("Unlock Currency In Settings."));
		}

		ImGui::Combo(OBFUSCATE_STR("Currency"), &selectedCur, curList, IM_ARRAYSIZE(curList), 4);
		if (ImGui::Button(("Add Currency"))) {
			addCurrency = true;
		}
	}

	ImGui::EndChild();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 255, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("In-Game"));
	ImGui::SetCursorPos({ 255, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Misc"), ImVec2(215, 999));
	{
		if (arrayStart > 1309)
			arrayStart = 1309;

		ImGui::InputInt(OBFUSCATE_STR("Gallery Number"), &arrayStart);
		if (ImGui::Button(OBFUSCATE_STR("Add Weapon"))) {
			addWeapons = true;
		}

		ImGui::Combo(OBFUSCATE_STR("Graffiti List"), &selectedGraffiti, graffitiList1, IM_ARRAYSIZE(graffitiList1), 4);//internal bool 下下丌不丄丞三丐专(string 一不丏丗万不不丄丞) { } might be set to true see in future
		if (ImGui::Button(OBFUSCATE_STR("Equip Graffiti"))) {
			addGraffiti = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Battlepass"))) {
			unlockAll = true;
		}
		ImGui::TextUnformatted(OBFUSCATE_STR("Will add enough battlepass currency to max out the whole\n battlepass."));

		ImGui::TextUnformatted(OBFUSCATE_STR("Wait abit between adding weapons."));
		if (ImGui::Button(OBFUSCATE_STR("Add Battle Royale Items"))) {
			addWeaponSkins = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 1"))) {
			addWeapons1 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 2"))) {
			addWeapons2 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 3"))) {
			addWeapons3 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 4"))) {
			addWeapons4 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 5"))) {
			addWeapons5 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 6"))) {
			addWeapons6 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 7"))) {
			addWeapons7 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 8"))) {
			addWeapons8 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Unlock Weapons 9"))) {
			addWeapons9 = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Add All Gadgets"))) {
			addGadgets = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Add All Armors"))) {
			addArmors = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Add All Capes"))) {
			addCapes = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Add All Boots"))) {
			addBoots = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Add All Hats"))) {
			addHats = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Add All Masks"))) {
			addMasks = true;
		}

		if (ImGui::Button(OBFUSCATE_STR("Add All Pets"))) {
			addPets = true;
		}

		ImGui::Checkbox(OBFUSCATE_STR("Free Lottery Boxes"), &unlockWear);
		ImGui::SliderInt(OBFUSCATE_STR("Box Price"), &lotteryAmount, -5000, 1);
		ImGui::TextUnformatted(OBFUSCATE_STR(" "));
		ImGui::Checkbox(OBFUSCATE_STR("Instant Modules"), &modUp);
		ImGui::Checkbox(OBFUSCATE_STR("Spoof Module Level"), &spoofModules);
		if (spoofModules)
			ImGui::InputInt(OBFUSCATE_STR("Module Level"), &spoofModVal);

		ImGui::Checkbox(OBFUSCATE_STR("Purchase weapon skins"), &buyWeaponSkins);
		ImGui::TextUnformatted(OBFUSCATE_STR("Click on the skin to purchase.\nSteam skins = Instaban"));
		ImGui::Checkbox(OBFUSCATE_STR("Force VIP Rewards"), &Vip);
		ImGui::Button(OBFUSCATE_STR("Free Lobby Bundles"));
		ImGui::TextUnformatted(OBFUSCATE_STR("  "));
	}
	ImGui::EndChild();
}

void DrawPlayer() {
	auto draw = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Legit"));
	ImGui::SetCursorPos({ 25, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Main"), ImVec2(215, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Speed"), &speed);
		if (speed)
			ImGui::SliderFloat(OBFUSCATE_STR("Speed Value"), &speedVal, 10, 1000);

		ImGui::Checkbox(OBFUSCATE_STR("Double Jump"), &doubleJump);
		if (ImGui::Button(OBFUSCATE_STR("Make yourself Invisible"))) {
			invisibleMe = true;
		}
		if (ImGui::Button(OBFUSCATE_STR("Add Jetpack"))) {
			addJetpack = true;
		}
	}

	ImGui::EndChild();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 255, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Rage"));
	ImGui::SetCursorPos({ 250, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Misc"), ImVec2(250, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Godmode"), &godmode);
		ImGui::TextUnformatted(OBFUSCATE_STR("If you disable, rejoin match."));

		ImGui::Checkbox(OBFUSCATE_STR("Set Your Scale"), &setMyScale);
		if (setMyScale)
			ImGui::SliderFloat(OBFUSCATE_STR("Scale Value"), &myScale, 0, 100.0);

		ImGui::Checkbox(OBFUSCATE_STR("Set Other Scale"), &setOtherScale);
		if (setOtherScale)
			ImGui::SliderFloat(OBFUSCATE_STR("Other Scale Value"), &otherScale, 0, 100.0);

		ImGui::Checkbox(OBFUSCATE_STR("Fly"), &fly);
		if (fly) {
			ImGui::SliderFloat(OBFUSCATE_STR("Fly Speed Value"), &flySpeed, 0, 2.5);
			ImGui::TextUnformatted(OBFUSCATE_STR("Higher Speed = noclip"));
		}
	}
	ImGui::EndChild();
}

void DrawWeapon() {
	auto draw = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Weapon"));
	ImGui::SetCursorPos({ 25, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Main"), ImVec2(215, 470));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Infinite Ammo"), &ammo);
		ImGui::Checkbox(OBFUSCATE_STR("No spread"), &recoilandspread);
		ImGui::Checkbox(OBFUSCATE_STR("No Reload"), &noreload);
		ImGui::Checkbox(OBFUSCATE_STR("Infinite Explosion Radius"), &explosionradius);
		ImGui::Checkbox(OBFUSCATE_STR("Instant Charge"), &instaCharge);
		ImGui::Checkbox(OBFUSCATE_STR("Force Critical Hits"), &forceCritical);
		ImGui::Checkbox(OBFUSCATE_STR("Force Scope"), &forceScope);
		//ImGui::Checkbox(OBFUSCATE_STR("Quick Scope"), &quickScope);
	}

	ImGui::EndChild();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 255, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Bullet"));
	ImGui::SetCursorPos({ 255, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Misc"), ImVec2(255, 300));
	{

		ImGui::Checkbox(OBFUSCATE_STR("Rocket Mods"), &explosive);
		if (explosive) {
			ImGui::Checkbox(OBFUSCATE_STR("Lifetime Rocket"), &longLifetime);
			ImGui::Checkbox(OBFUSCATE_STR("Ricochet"), &ricochet);
			ImGui::Combo(OBFUSCATE_STR("Rocket Mode"), &rocketMode, rocketMode1, IM_ARRAYSIZE(rocketMode1), 3);
			ImGui::Separator();
		}
		ImGui::Checkbox(OBFUSCATE_STR("Shoot Through Walls"), &stw);
		ImGui::Checkbox(OBFUSCATE_STR("Shoot Nukes"), &NukeShoot);
		ImGui::Checkbox(OBFUSCATE_STR("Break peoples cameras"), &breakcam);
		ImGui::TextUnformatted(OBFUSCATE_STR("Hit = break their camera."));
		ImGui::Checkbox(OBFUSCATE_STR("Make everyone a goat"), &polymorph);
		ImGui::TextUnformatted(OBFUSCATE_STR("Hit = make them a goat"));
		ImGui::Checkbox(OBFUSCATE_STR("Shoot explosive bullets"), &harpoonbull);
		ImGui::TextUnformatted(OBFUSCATE_STR("Shoot explosive bullets"));
		ImGui::Checkbox(OBFUSCATE_STR("Make everyone's heads bigger"), &headmagnify);
		ImGui::TextUnformatted(OBFUSCATE_STR("Hit = head bigger."));
		ImGui::Checkbox(OBFUSCATE_STR("Force Poison"), &poison);
		ImGui::Checkbox(OBFUSCATE_STR("Force Curse"), &curse);
		ImGui::Checkbox(OBFUSCATE_STR("Force Jump Disable"), &jumpDisable);
		ImGui::Checkbox(OBFUSCATE_STR("Force Slow Down"), &slowDown);
		ImGui::TextUnformatted(OBFUSCATE_STR("Hit = Slow Down."));
		ImGui::Checkbox(OBFUSCATE_STR("Force Speed Up"), &speedUp);
		ImGui::TextUnformatted(OBFUSCATE_STR("Hit = Speed Up."));
		ImGui::Checkbox(OBFUSCATE_STR("Force Gadget Disabler"), &gadgetDisabler);
		ImGui::Checkbox(OBFUSCATE_STR("Force Charm"), &charm);
		ImGui::Checkbox(OBFUSCATE_STR("Force Ignore Reflection"), &ignoreReflection);
		ImGui::Checkbox(OBFUSCATE_STR("Force Railgun Bullets"), &railgunBull);
		ImGui::Checkbox(OBFUSCATE_STR("Force Flamethrower Bullets"), &flamethrowerBullets);
		ImGui::Checkbox(OBFUSCATE_STR("Increase reflection count"), &reflections);
		ImGui::TextUnformatted(OBFUSCATE_STR("  "));
	}
	ImGui::EndChild();
}

void DrawMisc() {
	auto draw = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Weapon"));
	ImGui::SetCursorPos({ 25, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Main"), ImVec2(215, 300));
	{
		if (ImGui::Button(OBFUSCATE_STR("Bug All"))) {
			bugAll = true;
			mech = true;
		}
		ImGui::TextUnformatted(OBFUSCATE_STR("Change weapons after clicking\nGlitches out players, then\ntriggers the AC on them."));
		if (ImGui::Button(OBFUSCATE_STR("Kill All"))) {
			killall = true;
		}
		if (ImGui::Button(OBFUSCATE_STR("Make everyone Invisible"))) {
			invisible = true;
		}
		if (ImGui::Button(OBFUSCATE_STR("Clone Player"))) {
			clonePlayer = true;
		}
		ImGui::Checkbox(OBFUSCATE_STR("Loop Player Score"), &playerscoreAdd);
		ImGui::Checkbox(OBFUSCATE_STR("Float All"), &floatAll);
		ImGui::Checkbox(OBFUSCATE_STR("Mech All"), &mech);
		ImGui::Checkbox(OBFUSCATE_STR("Break Everyone's Guns"), &breakGuns);
		ImGui::TextUnformatted(OBFUSCATE_STR("Will make everyone's\nguns shoot fast."));
		ImGui::Checkbox(OBFUSCATE_STR("Name Spoofer"), &SpoofName);
		ImGui::Checkbox(OBFUSCATE_STR("Hide Names"), &hideNames);
		ImGui::Checkbox(OBFUSCATE_STR("Telekill"), &telekill);
		ImGui::Checkbox(OBFUSCATE_STR("Masskill"), &massKill);
		ImGui::Checkbox(OBFUSCATE_STR("TeamKill"), &teamkill);
		ImGui::Checkbox(OBFUSCATE_STR("Chat Spam"), &chatSpam);
		ImGui::Checkbox(OBFUSCATE_STR("Spam Rockets on Everyone"), &spamRockets);
		ImGui::Checkbox(OBFUSCATE_STR("Any Guns"), &sandboxGuns);
		ImGui::TextUnformatted(OBFUSCATE_STR("Go in a deathmatch match\nthen turn this on"));
		ImGui::TextUnformatted(OBFUSCATE_STR("You can use guns in every mode."));

		ImGui::TextUnformatted(OBFUSCATE_STR("  "));
	}

	ImGui::EndChild();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 255, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Bullet"));
	ImGui::SetCursorPos({ 255, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("Misc"), ImVec2(255, 300));
	{
		ImGui::Checkbox(OBFUSCATE_STR("Time Scale"), &timescale);
		if (timescale)
			if (ImGui::SliderFloat(OBFUSCATE_STR("Time Scale Value"), &timeScaleVal, 0.1, 10.0))

				ImGui::Checkbox(OBFUSCATE_STR("Turret Mods"), &turret);
		if (turret) {
			ImGui::Checkbox(OBFUSCATE_STR("Turret Godmode"), &turretGod);
			ImGui::Checkbox(OBFUSCATE_STR("More Turret Damage"), &turretDmg);
			ImGui::Checkbox(OBFUSCATE_STR("Infinite Turret Range"), &turretRange);
			ImGui::Separator();
		}
		ImGui::Checkbox(OBFUSCATE_STR("Drone Godmode"), &droneGod);
		ImGui::Checkbox(OBFUSCATE_STR("No gadget cooldown"), &gadgetcd);
		ImGui::Checkbox(OBFUSCATE_STR("Pet Mods"), &pet);
		if (pet) {
			ImGui::Checkbox(OBFUSCATE_STR("Pet Godmode"), &pgod);
			ImGui::Checkbox(OBFUSCATE_STR("Pet Speed"), &pspeed);
			ImGui::Checkbox(OBFUSCATE_STR("Pet One Shot Kill"), &pdamage);
			ImGui::Separator();
		}
		ImGui::Checkbox(OBFUSCATE_STR("Clan Mods"), &clan);
		if (clan) {
			ImGui::Checkbox(OBFUSCATE_STR("Infinite Clan Energy"), &clanEnergy);
			ImGui::Checkbox(OBFUSCATE_STR("Free Clan Parts"), &freeClanParts);
			ImGui::Checkbox(OBFUSCATE_STR("Instant Upgrade"), &instantUpgrades);
			ImGui::Separator();
		}
	}
	ImGui::EndChild();
}

void ExecuteCommandAndClose(const std::string& command) {
	system(command.c_str());

	std::cout << OBFUSCATE_STR("Ban trace has been removed, reopen Pixel Gun 3D.") << std::endl;
}

void DrawSettings() {
	auto draw = ImGui::GetWindowDrawList();
	auto pos = ImGui::GetWindowPos();
	auto size = ImGui::GetWindowSize();
	draw->AddText(fonts::medium, 14.0f, ImVec2(pos.x + 25, pos.y + 60), ImColor(1.0f, 1.0f, 1.0f, 0.6f), OBFUSCATE_STR("Settings"));

	ImGui::SetCursorPos({ 25, 85 });
	ImGui::BeginChild(OBFUSCATE_STR("##container"), ImVec2(380, 550), false, ImGuiWindowFlags_NoScrollbar); {
		ImGui::Checkbox(OBFUSCATE_STR("Unlock Currency Bar"), &unlockCur);
		ImGui::Checkbox(OBFUSCATE_STR("Unlock EXP Bar"), &unlockEXP);

		if (ImGui::Button(OBFUSCATE_STR("Ban Trace Cleaner"))) {
			showConfirmationPopup = true;
		}

		if (showConfirmationPopup) {
			ImGui::OpenPopup(OBFUSCATE_STR("Confirmation"));
			if (ImGui::BeginPopupModal(OBFUSCATE_STR("Confirmation"), NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
				ImGui::Text(OBFUSCATE_STR("Please check the console and input 'yes' to confirm."));
				if (ImGui::Button(OBFUSCATE_STR("OK"))) {
					ImGui::CloseCurrentPopup();
					showConfirmationPopup = false;

					if (!BanTraceCleaner) {
						std::string command = R"(rmdir /s /q "%USERPROFILE%\AppData\LocalLow\Pixel Gun Team" && reg delete "HKEY_CURRENT_USER\SOFTWARE\Pixel Gun Team")";
						ExecuteCommandAndClose(command);

						BanTraceCleaner = true;
					}
				}
				ImGui::EndPopup();
			}
		}

		ImGui::TextUnformatted(OBFUSCATE_STR("  "));
		ImGui::ColorEdit4(OBFUSCATE_STR("ESP Box Color"), &boxColor.x);
		ImGui::ColorEdit4(OBFUSCATE_STR("ESP Lines Color"), &lineColor.x);
		ImGui::ColorEdit4(OBFUSCATE_STR("ESP Name Color"), &nameColor.x);
		ImGui::ColorEdit4(OBFUSCATE_STR("ESP Name Color"), &FilledBoxColor.x);

	}
	ImGui::EndChild();
}



void DrawMenu() {
	ImGui::Begin("oni", nullptr, ImGuiWindowFlags_NoDecoration);
	{
		auto draw = ImGui::GetWindowDrawList();

		auto pos = ImGui::GetWindowPos();
		auto size = ImGui::GetWindowSize();

		draw->AddRectFilled(pos, ImVec2(pos.x + size.x, pos.y + 51), ImColor(24, 24, 24), 9.0f, ImDrawFlags_RoundCornersTop);
		draw->AddRectFilledMultiColorRounded(pos, ImVec2(pos.x, pos.y + 51), ImColor(1.0f, 1.0f, 1.0f, 0.00f), ImColor(1.0f, 1.0f, 1.0f, 0.05f), ImColor(1.0f, 1.0f, 1.0f, 0.00f), ImColor(1.0f, 1.0f, 1.0f, 0.00f), ImColor(1.0f, 1.0f, 1.0f, 0.05f), 9.0f, ImDrawFlags_RoundCornersTopLeft);

		draw->AddText(fonts::semibold, 17.0f, ImVec2(pos.x + 25, pos.y + 18), ImColor(192, 203, 229), "oni");

		ImGui::SetCursorPos({ 90, 19 });
		ImGui::BeginGroup(); {
			security_loop();
			if (elements::tab(OBFUSCATE_STR("Aim"), head_selected == AIMBOT)) head_selected = AIMBOT;
			ImGui::SameLine();
			if (elements::tab(OBFUSCATE_STR("Vis"), head_selected == VISUALS)) head_selected = VISUALS;
			ImGui::SameLine();
			if (elements::tab(OBFUSCATE_STR("Account"), head_selected == ACCOUNT)) head_selected = ACCOUNT;
			ImGui::SameLine();
			if (elements::tab(OBFUSCATE_STR("Player"), head_selected == PLAYER)) head_selected = PLAYER;
			ImGui::SameLine();
			if (elements::tab(OBFUSCATE_STR("Weapon"), head_selected == WEAPON)) head_selected = WEAPON;
			ImGui::SameLine();
			if (elements::tab(OBFUSCATE_STR("Misc"), head_selected == MISC)) head_selected = MISC;
			ImGui::SameLine();
			if (elements::tab(OBFUSCATE_STR("Settings"), head_selected == SETTINGS)) head_selected = SETTINGS;
		}
		ImGui::EndGroup();

		switch (head_selected) {
		case AIMBOT: // Aim
			DrawAimbot();
			break;
		case VISUALS: // Visual
			DrawVisuals();
			break;
		case ACCOUNT: // Weapon
			DrawAccount();
			break;
		case SETTINGS: // Player
			DrawSettings();
			//DrawPlayer();
			break;
		case PLAYER: // Game
			DrawPlayer();
			break;
		case WEAPON: // Clan
			DrawWeapon();
			break;
		case MISC: // Maxing
			DrawMisc();
			break;
		}
	}
	ImGui::End();
}