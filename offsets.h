#ifndef OFFSETS_H
#define OFFSETS_H

// https://www.unknowncheats.me/forum/league-of-legends/310587-league-legends-reversal-structs-offsets-311.html
// Game Version: 12.7 - Some might be wrong
// Additions may occur in the future

// https://www.unknowncheats.me/forum/league-of-legends/310587-league-legends-reversal-structs-offsets-313.html


#define HeroMagicId 0xD028 // 12.13
#define TurretMagicId 0x059C // 12.13
#define MinionMagicId 0xC854 // 12.13

// To be tested
#define TurretList 0x3105ACC // 12.13
#define HeroList 0x1870C68 // 12.13
#define SpellName 0x0018
#define MinionList 0x24BFAB4 // 12.13
#define MissleList 0x24a4bd4
#define InhibitorList 0x3107454

// General Section
#define GameTime 0x31081A8 // 12.13
#define ObjectManager 0x1870BD8 // 12.13
#define LocalPlayer 0x310ED68 // 12.13
#define UnderMouseObject 0x24B7D9C // 12.13
#define Chat 0x31073B8
#define ViewProjMatrices 0x313E6A0 // 12.13
#define RendererOff 0x3141584 // 12.13
#define MinimapObject 0x4a90cc1d
#define ChatIsOpen 0x754

// Object section
#define ObjIndex 0x8
#define ObjTeam 0x34
#define ObjMissleName 0x54 // 12.13
#define ObjNetId 0xB4
#define ObjPos 0x1DC
#define ObjMissleSpellCast 0x250
#define ObjVisibility 0x274
#define ObjSpawnCount 0x288 // 12.13
#define ObjSrcIndex 0x294 // 12.13
#define ObjMana 0x29C
#define ObjMaxMana 0x2AC
#define ObjRecallState 0xD90
#define ObjHealth 0xE74
#define ObjMaxHealth 0xE84
#define ObjAbilityHaste 0x1690
#define ObjLethality 0x11A8 // 12.13
#define ObjArmor 0x1374
#define ObjBonusArmor 0x1378
#define ObjMagicRes 0x137C
#define ObjBonusMagicRes 0x1380
#define ObjBaseAtk 0x134C
#define ObjBonusAtk 0x12C4
#define ObjMoveSpeed 0x138C
#define ObjSpellBook 0x27B8
#define ObjTransformation 0x3040
#define ObjName 0x2BA4
#define ObjExp 0x337c
#define ObjExpiry 0x298
#define ObjCrit 0x12e0
#define ObjCritMulti 0x12d0
#define ObjAbilityPower 0x1740
#define ObjAtkSpeedMulti 0x1348
#define ObjAtkRange 0x1394
#define ObjTargetable 0xD04
#define ObjInvulnerable 0x3D4
#define ObjIsMoving 0x32e7
#define ObjDirection 0x1b88
#define ObjItemList 0x33e8
#define ObjLvl 0x3384
#define ObjMagicPen 0x11dc
#define ObjMagicPenMulti 0x11e4
#define ObjAdditionalApMulti 0x1248
#define ObjManaRegen 0x1150 // 12.13
#define ObjHealthRegen 0x1388 // 12.13

// Buff section
#define ObjBuffManager 0x2180
#define BuffManagerEntriesArray 0x10
#define BuffEntryBuff 0x8
#define BuffType 0x4
#define BuffEntryBuffStartTime 0xc
#define BuffEntryBuffEndTime 0x10
#define BuffEntryBuffCount 0x74
#define BuffEntryBuffCountAlt 0x24
#define BuffBuffEntryBuffCountAlt2 0x20
#define BuffName 0x8
#define BuffEntryBuffNodeStart 0x20
#define BuffEntryBuffNodeCurrent 0x24

// Item section
#define ItemListItem 0xc
#define ItemInfo 0x20
#define IntemInfoId 0x68

// Renderer section
#define RendererWidth 0xc
#define RendererHeight 0x10

// SpellBook section
#define SpellBookActiveSpellCast 0x20
#define SpellBookSpellSlots 0x478
#define SpellSlotLevel 0x1c
#define SpellSlotTime 0x24
#define SpellSlotCharges 0x54
#define SpellSlotTimeCharge 0x74
#define SpellSlotDamage 0x94
#define SpellSlotSpellInfo 0x120
#define SpellInfoSpellData 0x40
#define SpellDataSpellName 0x6c
#define SpellDataMissleName 0x78
#define SpellSlotSmiteTimer 0x64
#define SpellSlotSmiteCharges 0x58
#define SpellCastSpellInfo 0x8
#define SpellCastStartTime 0x544 // 12.13
#define SpellCastStartTimeAlt 0x534
#define SpellCastCastTime 0x4c0
#define SpellCastStart 0x80
#define SpellCastEnd 0x8c
#define SpellCastSrcIdx 0x68
#define SpellCastDestIdx 0xc0

#define CurrentDashSpeed 0x1d0
#define IsDashing 0x398
#define DashPos 0x1fc
#define IsMoving 0x198
#define NavBegin 0x1bc
#define NavEnd 0x1c0
#define ObjectMapCount 0x2c
#define ObjectMapRoot 0x28
#define ObjectMapNodeNetId 0x10
#define ObjectMapNodeObject 0x14

#define MissleSpellInfo 0x278
#define MissleSrcIdx 0x2dc
#define MissleDestIdx 0x330
#define MissleStartPos 0x2f4
#define MissleEndPos 0x300

#define MinimapObjectHud 0x110
#define MinimapHudPos 0x44
#define MinimapHudSize 0x4c

#endif
