#include "object.h"

Object::Object(){};
Object::~Object(){};

void Object::readObject(int address)
{
    char buf[0x4100];
    readMem(address, buf, 0x3500);

    memcpy(&health, &buf[ObjHealth], sizeof(float));
    memcpy(&maxHealth, &buf[ObjMaxHealth], sizeof(float));
    memcpy(&baseAttack, &buf[ObjBaseAtk], sizeof(float));
    memcpy(&bonusAttack, &buf[ObjBonusAtk], sizeof(float));
    memcpy(&mana, &buf[ObjMana], sizeof(float));
    memcpy(&maxMana, &buf[ObjMaxMana], sizeof(float));
    memcpy(&armor, &buf[ObjArmor], sizeof(float));
    memcpy(&magicResist, &buf[ObjMagicRes], sizeof(float));
    memcpy(&abilityPower, &buf[ObjAbilityPower], sizeof(float));
    memcpy(&level, &buf[ObjLvl], sizeof(int));
    memcpy(&attackRange, &buf[ObjAtkRange], sizeof(float));
    memcpy(&recallState, &buf[ObjRecallState], sizeof(int));
    memcpy(&objectIndex, &buf[ObjIndex], sizeof(int));
    memcpy(&team, &buf[ObjTeam], sizeof(int));
    memcpy(&netId, &buf[ObjNetId], sizeof(int));
    memcpy(&position, &buf[ObjPos], 3 * sizeof(float));
    memcpy(&movementSpeed, &buf[ObjMoveSpeed], sizeof(float));
    memcpy(&visible, &buf[ObjVisibility], sizeof(int));

    if (isVisible())
    {
        lastVisible[0] = position[0];
        lastVisible[1] = position[1];
        lastVisible[2] = position[2];
    }

    int name_ptr;

    memcpy(&name_ptr, &buf[ObjName], sizeof(int));
    readStr(name_ptr, name);
}

void Object::readChampion(int address)
{
    readObject(address);

    char buf1[0x110];
    readMem(address + ObjSpellBook, buf1, 0x100);

    Spell spell;
    int spellP;

    for (int i=0; i<6; i++)
    {
        memcpy(&spellP, &buf1[i * 4], sizeof(int));
        spell.readSpell(spellP);
        spells[i] = spell;
    }
}

bool Object::isVisible()
{
    return visible == 0x101;
}

std::ostream& operator<<(std::ostream& os, const Object& obj)
{
    os << "\nName: "           << obj.name         << "\n"
       << "Team: "             << obj.team         << "\n"
       << "Current Health: "   << obj.health       << "\n"
       << "Max Health: "       << obj.maxHealth    << "\n"
       << "Mana: "             << obj.mana         << "\n"
       << "Max Mana: "         << obj.maxMana      << "\n"
       << "Base Attack: "      << obj.baseAttack   << "\n"
       << "Bonus Attack: "     << obj.bonusAttack  << "\n"
       << "Ability Power: "    << obj.abilityPower << "\n"
       << "Attack Range: "     << obj.attackRange  << "\n"
       << "Level: "            << obj.level        << "\n"
       << "Recall State: "     << obj.recallState  << "\n"
       << "Movement Speed: "   << obj.movementSpeed<< "\n"
       << "Position: {"        << obj.position[0]  << "; "
                               << obj.position[1]  << "; "
                               << obj.position[2]  << "}\n\n";

        for (int i=0; i<6; i++)
            os << obj.spells[i];

        return os;
}
