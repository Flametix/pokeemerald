#include "global.h"
#include "battle_anim.h"
#include "item_menu_icons.h"
#include "sprite.h"
#include "random.h"
#include "gpu_regs.h"
#include "item.h"
#include "rtc.h"
#include "item_icon.h"
#include "sound.h"
#include "menu.h"
#include "malloc.h"
#include "util.h"
#include "trig.h"
#include "graphics.h"
#include "battle_scripts.h"
#include "battle_controllers.h"
#include "constants/moves.h"
#include "constants/hold_effects.h"
#include "constants/items.h"
#include "constants/pokemon.h"
#include "battle_util.h"
#include "constants/songs.h"

// function declarations
static void SpriteCB_SpriteOnMonForDuration(struct Sprite *sprite);
static void SpriteCB_AnimSpriteOnSelectedMonPos(struct Sprite *sprite);


//precipice blades
static const union AnimCmd sAnimCmdLargeSpike[] =
{
    ANIMCMD_FRAME(0, 3),
    ANIMCMD_FRAME(32, 3),
    ANIMCMD_FRAME(64, 3),
    ANIMCMD_FRAME(96, 3),
    ANIMCMD_END,
};
static const union AnimCmd *const sAnimCmdTable_LargeSpike[] =
{
    sAnimCmdLargeSpike,
};
const struct SpriteTemplate gPrecipiceBladesSpikeTemplate =
{
    .tileTag = ANIM_TAG_LARGE_SPIKE,
    .paletteTag = ANIM_TAG_LARGE_SPIKE,
    .oam = &gOamData_AffineOff_ObjNormal_32x64,
    .anims = sAnimCmdTable_LargeSpike,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_SpriteOnMonForDuration
};

static const union AffineAnimCmd sSpriteAffineAnim_LargeHailRock[] =
{
    AFFINEANIMCMD_FRAME(256, 256, 0, 1), //Double sprite size
    AFFINEANIMCMD_END,
};
static const union AffineAnimCmd* const sSpriteAffineAnimTable_LargeHailRock[] =
{
    sSpriteAffineAnim_LargeHailRock,
};
const struct SpriteTemplate gPrecipiceBladesLargeSpikeTemplate =
{
    .tileTag = ANIM_TAG_LARGE_SPIKE,
    .paletteTag = ANIM_TAG_LARGE_SPIKE,
    .oam = &gOamData_AffineDouble_ObjNormal_32x64,
    .anims = sAnimCmdTable_LargeSpike,
    .images = NULL,
    .affineAnims = sSpriteAffineAnimTable_LargeHailRock,
    .callback = SpriteCB_SpriteOnMonForDuration
};

const struct SpriteTemplate gPrecipiceBladesPlumeTemplate =
{
    .tileTag = ANIM_TAG_FIRE_PLUME,
    .paletteTag = ANIM_TAG_FIRE_PLUME,
    .oam = &gOamData_AffineOff_ObjNormal_32x32,
    .anims = gAnims_DragonRageFirePlume,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_AnimSpriteOnSelectedMonPos
};

// functions

static u8 LoadBattleAnimTarget(u8 arg)
{
    u8 battler;

    if (gBattleTypeFlags & BATTLE_TYPE_DOUBLE)
    {
        switch (gBattleAnimArgs[arg])
        {
        case 0:
            battler = gBattleAnimAttacker;
            break;
        default:
            battler = gBattleAnimTarget;
            break;
        case 2:
            battler = BATTLE_PARTNER(gBattleAnimAttacker);
            break;
        case 3:
            battler = BATTLE_PARTNER(gBattleAnimTarget);
            break;
        }
    }
    else
    {
        if (gBattleAnimArgs[arg] == 0)
            battler = gBattleAnimAttacker;
        else
            battler = gBattleAnimTarget;
    }

    return battler;
}

static void InitSpritePosToGivenTarget(struct Sprite *sprite, u8 target)
{
    sprite->x = GetBattlerSpriteCoord2(target, BATTLER_COORD_X);
    sprite->y = GetBattlerSpriteCoord2(target, BATTLER_COORD_Y);

    SetAnimSpriteInitialXOffset(sprite, gBattleAnimArgs[0]);
    sprite->y2 = gBattleAnimArgs[1];
}


static void SpriteCB_SpriteOnMonForDuration(struct Sprite *sprite)
{
    u8 target = LoadBattleAnimTarget(0);

    if (!IsBattlerSpriteVisible(target))
    {
        DestroyAnimSprite(sprite);
    }
    else
    {
        sprite->x = GetBattlerSpriteCoord(target, 0);
        sprite->y = GetBattlerSpriteCoord(target, 1);
        sprite->x += gBattleAnimArgs[1];
        sprite->y += gBattleAnimArgs[2];
        sprite->data[0] = 0;
        sprite->data[1] = gBattleAnimArgs[3];
        sprite->data[2] = gBattleAnimArgs[4];
        sprite->data[3] = 0;
        sprite->callback = AnimBrickBreakWall_Step;
    }
}

static void SpriteCB_AnimSpriteOnSelectedMonPos(struct Sprite *sprite)
{
    if (!sprite->data[0])
    {
        u8 target = LoadBattleAnimTarget(2);

        if (!IsBattlerSpriteVisible(target))
            DestroyAnimSprite(sprite);
        else
        {
            InitSpritePosToGivenTarget(sprite, target);
            sprite->data[0]++;
        }
    }
    else if (sprite->animEnded || sprite->affineAnimEnded)
    {
        DestroySpriteAndMatrix(sprite);
    }
}

