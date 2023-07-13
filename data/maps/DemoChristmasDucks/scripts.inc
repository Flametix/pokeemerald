DemoChristmasDucks_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DemoChristmasDucks_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, DemoChristmasDucks_OnLoad
	.byte 0

DemoChristmasDucks_OnLoad:
	setrespawn HEAL_LOCATION_DEMO
	call_if_unset FLAG_HIDE_FALLARBOR_AZURILL, DemoChristmasDucks_EventScript_HideDoor
	call_if_unset FLAG_SYS_POKEMON_GET, DemoChristmasDucks_EventScript_GiveParty
	end

DemoChristmasDucks_OnTransition:
	setrespawn HEAL_LOCATION_DEMO
	call_if_unset FLAG_HIDE_FALLARBOR_AZURILL, DemoChristmasDucks_EventScript_HideDoor
	end

DemoChristmasDucks_EventScript_GiveParty::
	setflag FLAG_SYS_POKEMON_GET
	givecustommon SPECIES_3DUCK, 60, ITEM_NONE, ITEM_PREMIER_BALL, NATURE_RELAXED, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_MAGIC_COAT, MOVE_CONVERSION, MOVE_PSYCHIC, MOVE_LOCK_ON
	givecustommon SPECIES_SWORDUCK, 60, ITEM_NONE, ITEM_ULTRA_BALL, NATURE_BRAVE, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_SLASH, MOVE_FLAMETHROWER, MOVE_METAL_CLAW, MOVE_SHARPEN
	givecustommon SPECIES_VERT, 60, ITEM_NONE, ITEM_SAFARI_BALL, NATURE_QUIET, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_VERT, MOVE_ABSORB, MOVE_PROTECT, MOVE_CONFUSION
	givecustommon SPECIES_DUCCAR, 60, ITEM_NONE, ITEM_TIMER_BALL, NATURE_SERIOUS, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_RAPID_SPIN, MOVE_THUNDER_SHOCK, MOVE_METAL_SOUND, MOVE_STEEL_WING
	givecustommon SPECIES_DUCKLES, 60, ITEM_NONE, ITEM_LUXURY_BALL, NATURE_SASSY, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, MOVE_ATTRACT, MOVE_CHARM, MOVE_DRAINING_KISS, MOVE_COVET

	end

DemoChristmasDucks_EventScript_Battle::
	lock
	goto_if_set FLAG_HIDE_FALLARBOR_AZURILL, DemoChristmasDucks_EventScript_PostBattleSpeech
	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
	msgbox DemoChristmasDucks_Text_Battle_Intro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_DEMO, DemoChristmasDucks_Text_Battle_Defeat
	goto DemoChristmasDucks_EventScript_Defeated
	end

DemoChristmasDucks_EventScript_Defeated::
	setflag FLAG_HIDE_FALLARBOR_AZURILL
	call_if_set FLAG_HIDE_FALLARBOR_AZURILL, DemoChristmasDucks_EventScript_ShowWindow
	special DrawWholeMapView
	msgbox DemoChristmasDucks_Text_Battle_Post, MSGBOX_DEFAULT
	release
	end

DemoChristmasDucks_EventScript_PostBattleSpeech:: 
	msgbox DemoChristmasDucks_Text_Battle_Post, MSGBOX_DEFAULT
	release
	end

DemoChristmasDucks_Text_Battle_Intro:
	.string "good luck!$"

DemoChristmasDucks_Text_Battle_Defeat:
	.string "dayum, nice one, ggs$"

DemoChristmasDucks_Text_Battle_Post:
	.string "Congratulations on beating me!\n"
	.string "Step through the door to see your reward...$"

DemoChristmasDucks_EventScript_HideDoor::
	setmetatile 6, 1, METATILE_DemoChristmasDucks_WINDOW1, 1
	setmetatile 6, 2, METATILE_DemoChristmasDucks_WINDOW2, 1
	return

DemoChristmasDucks_EventScript_ShowWindow::
	setmetatile 6, 1, METATILE_DemoChristmasDucks_BLACK_DOOR_TOP, 1
	setmetatile 6, 2, METATILE_DemoChristmasDucks_BLACK_DOOR, 0
	return

@ EverGrandeCity_SidneysRoom_EventScript_Sidney:: @ 8227F64
@ 	lock
@ 	faceplayer
@ 	goto_if_set FLAG_DEFEATED_ELITE_4_SIDNEY, EverGrandeCity_SidneysRoom_EventScript_PostBattleSpeech
@ 	playbgm MUS_ENCOUNTER_ELITE_FOUR, FALSE
@ 	msgbox EverGrandeCity_SidneysRoom_Text_IntroSpeech, MSGBOX_DEFAULT
@ 	trainerbattle_no_intro TRAINER_SIDNEY, EverGrandeCity_SidneysRoom_Text_Defeat
@ 	goto EverGrandeCity_SidneysRoom_EventScript_Defeated
@ 	end

@ EverGrandeCity_SidneysRoom_EventScript_PostBattleSpeech:: @ 8227F8B
@ 	msgbox EverGrandeCity_SidneysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
@ 	release
@ 	end

@ EverGrandeCity_SidneysRoom_EventScript_Defeated:: @ 8227F95
@ 	setflag FLAG_DEFEATED_ELITE_4_SIDNEY
@ 	call PokemonLeague_EliteFour_SetAdvanceToNextRoomMetatiles
@ 	msgbox EverGrandeCity_SidneysRoom_Text_PostBattleSpeech, MSGBOX_DEFAULT
@ 	release
@ 	end
