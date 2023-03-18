#include "spell.h"

Spell::Spell(){};
Spell::~Spell(){};

void Spell::readSpell(int address)
{
    char buf[0x610];
    readMem(address, buf, 0x600);

    memcpy(&level, &buf[SpellSlotLevel], sizeof(int));
    memcpy(&ready, &buf[SpellSlotTime], sizeof(float));

    int spellInfo;

    memcpy(&spellInfo, &buf[SpellSlotSpellInfo], sizeof(int));

    int spellData;
    readDw(spellInfo + SpellInfoSpellData, &spellData);

    int namePtr;
    readDw(spellData + SpellDataSpellName, &namePtr);

    readStr(namePtr, name);
}

std::ostream& operator << (std::ostream& os, const Spell& spell)
{
    os << "\nSpell name: " << spell.name  << "\n"
       << "Level: "      << spell.level << "\n"
       << "Time: "       << spell.ready << "\n\n";

    return os;
}
