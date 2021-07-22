DemoChristmasDucks_MapScripts::
	map_script MAP_SCRIPT_ON_TRANSITION, DemoChristmasDucks_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, DemoChristmasDucks_OnLoad
	.byte 0

DemoChristmasDucks_OnLoad:
	call_if_unset FLAG_HIDE_FALLARBOR_AZURILL, DemoChristmasDucks_EventScript_HideDoor
	end

DemoChristmasDucks_OnTransition:
	call_if_unset FLAG_HIDE_FALLARBOR_AZURILL, DemoChristmasDucks_EventScript_HideDoor
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
	.string "test$"

DemoChristmasDucks_Text_Battle_Defeat:
	.string "est$"

DemoChristmasDucks_Text_Battle_Post:
	.string "best$"

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