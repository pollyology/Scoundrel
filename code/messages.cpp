#include "messages.h"

MessageType getMessageType(const string& type, int value)
{
    std::array<string, 5> combatTypes = { "combat", "Dagger", "Sword", "Spear", "Claymore" };
    if (type == "tutorial") { return MessageType::Tutorial; }

    if (type == "equip") { return getEquipMessageType(value); }
    if (type == "heal") { return getPotionMessageType(value); }
    if (type == "monster") { return getMonsterMessageType(value); }

    if (std::find (combatTypes.begin(), combatTypes.end(), type) != combatTypes.end()) 
    { return getCombatMessageType(type, value); }

    return MessageType::Invalid;
}

MessageType getEquipMessageType(int value)
{
    if (value <= 3) { return MessageType::EquipLow; }
    if (value <= 6) { return MessageType::EquipMid; }
    if (value <= 9) { return MessageType::EquipHigh;}

    return MessageType::EquipLegend;
}

MessageType getPotionMessageType(int value)
{
    if (value <= 3) { return MessageType::HealMinor; }
    if (value <= 6) { return MessageType::HealModerate; }
    if (value <= 9) {return MessageType::HealMajor; }

    return MessageType::HealAltar;
}

MessageType getMonsterMessageType(int value)
{
    if (value <= 3) { return MessageType::MonsterSmall; }
    if (value <= 6) { return MessageType::MonsterMedium; }
    if (value <= 9) { return MessageType::MonsterLarge; }
    if (value == 10) { return MessageType::MonsterBoss; }
    if (value == 11) { return MessageType::MonsterJack; }
    if (value == 12) { return MessageType::MonsterQueen; }
    if (value == 13) { return MessageType::MonsterKing; }

    return MessageType::MonsterAce;
}

MessageType getCombatMessageType(const string& type, int value)
{
    if (type != "combat")
    {
        int dmgTaken = value;
        int tier;
        if (dmgTaken == 0) { tier = 0; }
        if (dmgTaken >= 1) { tier = 1; }
        if (dmgTaken >= 4) { tier = 2; }
        if (dmgTaken >= 7) { tier = 3; }

        if (type == "Dagger")
        {
            switch(tier)
            {
                case 0: return MessageType::DAGGER_PlayerHurtNone;
                case 1: return MessageType::DAGGER_PlayerHurtLow;
                case 2: return MessageType::DAGGER_PlayerHurtMid;
                case 3: return MessageType::DAGGER_PlayerHurtHigh;
            }

        }
        else if (type == "Sword")
        {
            switch(tier)
            {
                case 0: return MessageType::SWORD_PlayerHurtNone;
                case 1: return MessageType::SWORD_PlayerHurtLow;
                case 2: return MessageType::SWORD_PlayerHurtMid;
                case 3: return MessageType::SWORD_PlayerHurtHigh;
            }
        }
        else if (type == "Spear")
        {
            switch(tier)
            {
                case 0: return MessageType::SPEAR_PlayerHurtNone;
                case 1: return MessageType::SPEAR_PlayerHurtLow;
                case 2: return MessageType::SPEAR_PlayerHurtMid;
                case 3: return MessageType::SPEAR_PlayerHurtHigh;
            }
        }
        else if (type == "Claymore")
        {
            switch(tier)
            {
                    case 0: return MessageType::CLAYMORE_PlayerHurtNone;
                    case 1: return MessageType::CLAYMORE_PlayerHurtLow;
                    case 2: return MessageType::CLAYMORE_PlayerHurtMid;
                    case 3: return MessageType::CLAYMORE_PlayerHurtHigh;
            }
        }
    }

    return (value == 1) ? MessageType::CombatEquipped : MessageType::CombatUnequipped; 
}
inline const std::map<MessageType, string> messageMap =
{
// Game
{ MessageType::GameIntro, "This is the game intro."},
{ MessageType::GameEnd, "This is the game ending." },
{ MessageType::GameOver, "Game is over." },
{ MessageType::Tutorial, R"(
╔══════════════════════════════════════════════╗
║        SCOUNDREL: A SOLO DUNGEON CRAWL       ║
╚══════════════════════════════════════════════╝

GOAL:
Explore a dungeon built from cards.  
Fight monsters, equip weapons, drink potions.  
Survive all rooms to win!

╔═════════════╗
║    SETUP    ║
╚═════════════╝
• Use 52-card deck (remove ♥/♦ J|Q|K|A)  
• Start with 20 Health  
• Each room = 4 cards (play 3, keep 1)  
• You may skip a room — but not two in a row

╔══════════════════════════════════════════════╗
║          CARD TYPES & ROOM ACTIONS           ║
╚══════════════════════════════════════════════╝

♣ / ♠  MONSTER  → Damage = Value  
♦      WEAPON   → Equip 1 | Reduces damage | Can only attack weaker foes  
♥      POTION   → Heal = Value | Can only heal once per room

┌────────────┬───────────────────────────────────┐
│ Card Rank  │ 2 – 10 = Value                    │
│            │ J = 11 | Q = 12 | K = 13 | A = 14 │
└────────────┴───────────────────────────────────┘

╔══════════════╗
║    COMBAT    ║
╚══════════════╝
• Pick 1 monster to fight  
• You always win, but take damage  
• Weapon reduces damage — then weakens
• Can't use weapon if monster atk > durability
• No weapon? Take full damage

╔═══════════════╗
║    VICTORY    ║
╚═══════════════╝
• Clear all rooms = WIN  
• Health reaches 0 = DEATH

══════════════════════════════════════════════
Tip: Choose carefully. Healing is rare.  
Death comes swift to the unprepared.
══════════════════════════════════════════════

Good luck, Scoundrel.
)"
},

// Weapons
{ MessageType::EquipLow, R"(
The stench fills your nostril. A small beast lies crumpled on the floor, 
its body twisted and lifeless, yet still warm.

Something glints in its side-a dagger, buried to the hilt.
You kneel, grip the handle, and pull. 
With a slight tug, the blade slides free with a wet sound.

Rusted, chipped... but still deadly in the right hands.)" 
},

{ MessageType::EquipMid, R"(
Slumped against the wall, lies the skeleton of a fallen adventurer.

Time has turned his armor into a coffin of flaking leather
and cracked metal, but the sword in his lap remains.

You pry it from his bony fingers. The edge is dull, but solid.
It's heavy in your grip—reliable, if nothing else.)"
},

{ MessageType::EquipHigh, R"(
You step into a chamber lined with ancient banners,
their colors faded.

Propped near the remains of a once-armored soldier
is a long, iron-tipped spear.

The pole is wrapped in worn leather, its balance still flawless
despite the years.

A weapon of discipline and reach-meant for holding the line.
)" 
},
{ MessageType::EquipLegend, R"(
The door groans open into a wide, silent chamber.

Dozens of armored skeletons lie scattered across the stone,
their weapons shattered, shields split.

Ancient battle standards once flown high, now lay in tatters-
marked with unfamiliar sigils, their colors faded.

Amid the ruin, one knight remains unbroken.
Kneeling on one knee, held upright
by the weapon still in his grasp.

With reverence, you remove the great claymore and gently
lay him to rest alongside his brothers-in-arms.

His duty fulfilled, his final watch ended.
)" 
},

// Potions
{ MessageType::HealMinor, R"(
A faint trail of dried blood leads you to a collapsed figure
slumped against the wall.

Besides them lies a leather satchel, torn open,
its contents spilled across the floor.

Among broken vials and shattered glass, one small bottle
remains intact- a tincture of herbs.

You drink it. 

Bitter on the tongue, but potent enough to dull the pain.
Warmth spreads through your limbs. The worst of your wounds
begin to knit.
)" 
},
{ MessageType::HealModerate, R"(
You stumble upon a makeshift camp tucked behind a fallen pillar.

The fire's long gone cold, but a canvas pack rests beneath a bedroll,
filled with dusty bandaged, dried pultices, and a sealed waterskin.

You patch yourself up, the scent of herbs and ash lingering in the air.
It's not elegant. but it'll hold. 

You feel steadier.
)" 
},
{ MessageType::HealMajor, R"(
You notice a narrow passage in the stone wall,
half-hidden by dust and rubble.

Squeezing through, you emerge into a small sanctuary-
walls carved with sigils of peace and healing.

Melted candlewax pools beneath cracked sconces,
and a statue of a forgotten goddess watches silently.

At her feet, offerings lie untouched: healing salves,
linen wrappings, and a basin of clean water.

You kneel, and tend to your wounds. The room hums
with stillness, as if the air itself wills your body to mend.
)" 
},
{ MessageType::HealAltar, R"(
A hidden stairwell, tucked behind a crumbling wall,
catches your eyes. You descend slowly, each step thick with 
centuries-old dust.

At the bottom, lies a sacred chamber, the stonework untouched by time.
Braziers flicker with pale blue flames, casting long shadows over
stained glass murals depicting scenes of warriors blessed, restored, 
and reborn.

In the center, stands a marble font filled with shimmering water.
As your hands cup the liquid, it glows faintly-cool and luminous.

You drink deeply. Light floods your body. Every wound closes. Bones realign.
Flesh knits together. You feel whole again, for the first time in a long while.

For a moment, it feels as if death itself would hesitate.
)"
},
// Monsters
{ MessageType::MonsterSmall, "You face a low-level monster." },
{ MessageType::MonsterMedium, "You face a mid-level monster." },
{ MessageType::MonsterLarge, "You face a high-level monster." }, 

{ MessageType::MonsterBoss, "You face a boss monster." },
{ MessageType::MonsterJack, "You face the Jack." },
{ MessageType::MonsterQueen, "You face the Queen." },
{ MessageType::MonsterKing, "You face the King." },
{ MessageType::MonsterAce, "You face the Ace." },

// Combat
{ MessageType::CombatEquipped, "You fight with your equipped weapon." },
{ MessageType::CombatUnequipped, "You fight with your bare hands." },

// Dagger
{ MessageType::DAGGER_PlayerHurtNone, R"(
Adrenaline drips. Warmth radiates through your back.

You sidestep its strike with ease and duck low
beneath its following swings.

Sloppy. Telegraphed. You see its exposed vitals.

Your dagger flashes once, twice. 
The creature drops without a sound. 
Clean. Controlled.
)"
},
{ MessageType::DAGGER_PlayerHurtLow, R"(
The beast slashes wildy, the noise slices through air.
You step back, but not before a cut grazes your cheek.

You don't have time to react, as you dart inside its reach.

A quick flurry of stabs ends the fight early.
)"
},
{ MessageType::DAGGER_PlayerHurtMid, R"(
You lunge, but judge the distance too late.

A raking blow catches you in the side-
knocking you back.

You clutch your ribs and wince in pain.
The creature appears to scoff, confident in its
victory.

But with a flick of your wrist, your dagger sails
through the air.

It sinks clean into the creature's eye.
The snarl dies in its throat. And finally, so
does the beast.
)"
},
{ MessageType::DAGGER_PlayerHurtHigh, R"(
You are only a moment too late to react.

The beast crashes into you, slamming your back against
cold, wet stone.

Then, you feel hot. Pain floods your body as talons tear
into you. Now face-to-face, foul stench and viscous drool 
pervade your senses.

You send a desperate strike into the beast's neck.
The creature spasms, shudders, then slumps.

It is dead, and you are alive. But only just.
)"
},

// Sword
{ MessageType::SWORD_PlayerHurtNone, R"(
The moment it lunges-you move.

Steel sings through the dark, cutting the air
in a single arc.

Your strike finds it mark before the beast can 
even land a blow.

It collapses mid-motion. With a flourish, you
cast off the beast blood from your blade.
)"
},
{ MessageType::SWORD_PlayerHurtLow, R"(
The sword meets the creature mid-charge.

But not before a claw grazes your arm;
a shallow cut, hot with pain.

You twist your blade free as the monster crumples
at your feet.
)"
},
{ MessageType::SWORD_PlayerHurtMid, R"(
You plant your stance and swing with practiced weight.

The blade bites deep, but too late to stop the blow.
A club slams into your ribs. You stagger, breathless.

Still you hold your ground, until the hilt of your sword
buries itself into the beast's chest. 

It does not rise again.
)"
},
{ MessageType::SWORD_PlayerHurtHigh, R"(
Steel clashes. Sparks fly. 

The sword cleaves true, but not before you're hurled
to the ground.

Fangs tear into your shoulder, while claws dig in your side;
flesh and chainmail parting like parchment.

You scream through gritted teeth and drive your blade upward.

It dies above you, mouth agape and still twitching.
You crawl out from beneath its corpse, still breathing.
)"
},

// Spear
{ MessageType::SPEAR_PlayerHurtNone, R"(
These beasts outmatch you in ferocity,
but tempered discipline bests savage instincts.

You measure the distance, wait-then strike.
The tip of your spear finds its mark before the 
beast can close the gap.

One clean thrust ends it, without so much as a scratch
on you.

You remain composed. Unshaken.
)"
},
{ MessageType::SPEAR_PlayerHurtLow, R"(
The creature feints, and you react a heartbeat too late.
Its raking limbs grazes alongside your forearm, shallow
but stinging.

You step back, reposition, and with a disciplined jab,
your spear punches through its throat.
)"
},
{ MessageType::SPEAR_PlayerHurtMid, R"(
It barrels forward, and your reach isn't enough.

A swipe catches your thigh, sharp and deep-it nearly
drops you. 

But you recover quickly. 

A graceful pivot catches the beast off-guard.
And a swift, brutal thrust pins it to the wall.
)"
},
{ MessageType::SPEAR_PlayerHurtHigh, R"(
The beast parries the spear tip, knocking your balance.
It presses the advantage and in a split second-lunges
past your reach.

Claws and steel slash across your belly.

Your stances breaks. Blood splashes the floor, your grip falters...
but instinct guides the spear into a brutal counter.

One last, desperate lunge-straight through its heart.
)"
},

// Claymore
{ MessageType::CLAYMORE_PlayerHurtNone, R"(
It lunges.

Too slow.

You step forward, not back-
and bring the claymore down like a thunderbolt.

The blow splits the monster clean in two, armor and all,
and cracks the stone beneath it.

Dust, blood, and gravel fill the air. Then, silence.

You don't blink. You are unyielding.
Nothing touches you.
)"
},
{ MessageType::CLAYMORE_PlayerHurtLow, R"(
A sharp, gnarled thing catches your hip, tearing through chain
and skin.

Your swing doesn't stop. You grit your teeth and pivot, dragging
the great blade in a brutal arc.

Its ruinous weight collides with the monster-
and the wall behind it. Stone cracks. Debris rains down.
The creature lies mangled and crushed beneath the rubble.

You press on, bloodied but unbroken.
)"
},
{ MessageType::CLAYMORE_PlayerHurtMid, R"(
With ferocity and twisted muscle, the beast slams you into a pillar.
You feel the impact echo throughout your body-and the rest of the chamber.

You collapse in a heap. Your ribs scream with every breath.

You rise anyway, dragging the sword-shaped hunk of iron behind you.
The beasts snarls and charges toward you.

With a roar, you heave the claymore upward and send it down like
a guillotine.

Shattered bones, severed limbs, and splintered steel clatter onto
the ground.

While you, remain standing.
)"
},
{ MessageType::CLAYMORE_PlayerHurtHigh, R"(
It roars as it rushes forward, a battering ram of snarling teeth
and twisted muscle, slamming you through a crumbling wall.

Dust fills the air. And your bones ache. You taste blood.

You pull yourself from the rubble, vision red, the claymore drags behind you.
The defiant beast prepares another charge.

With every ounce of strength, you swing.
The blade crashes into the beast with ruinous force,
sending it through a shattered pillar in a spray of stone and bone.

You collapse to one knee, the world spinning.
But the chamber-and the monster-are silent at last.
)"
},

// Debug
{ MessageType::Invalid, "An invalid statement was selected." },
};