//////////////////////////////////////
//
// Graphics .H file for .WL6
// IGRAB-ed on Wed Apr 13 06:58:44 1994
//
//////////////////////////////////////

typedef enum {
//		Lump Start
		H_BJPIC=3,						//      [003] [003]
		H_CASTLEPIC,					//      [004] [004]
		H_CONTROLS,						//      [005] [   ]
		H_JOYSTICKS,					//      [006] [   ]
		H_HEALTHITEMS,					//      [007] [   ]
		H_BLANKSQUARE,					//      [008] [   ]
		H_WEAPONS,						//      [009] [   ]
		H_GOLDKEY,						//      [010] [   ]
		H_BLAZEPIC,						//      [011] [005]
		H_WEAPONS2,						//      [012] [   ]
		H_GAMETITLE,					//      [013] [   ]
		H_VISA,							//      [014] [   ]
		H_MASTERCARD,					//      [015] [   ]
		H_IDLOGO,						//      [016] [   ]
		H_TOPWINDOWPIC,					//      [017] [006]
		H_LEFTWINDOWPIC,				//      [018] [007]
		H_RIGHTWINDOWPIC,				//      [019] [008]
		H_BOTTOMINFOPIC,				//      [020] [009]
		H_SPEARPIC,						//      [021] [   ]
//		Lump Start
		C_OPTIONSPIC,					//      [022] [010]
		C_CURSOR1PIC,					//      [023] [011]
		C_CURSOR2PIC,					//      [024] [012]
		C_NOTSELECTEDPIC,				//      [025] [013]
		C_SELECTEDPIC,					//      [026] [014]
		C_FXTITLEPIC,					//      [027] [015]
		C_DIGITITLEPIC,					//      [028] [016]
		C_MUSICTITLEPIC,				//      [029] [017]
		C_MOUSELBACKPIC,				//      [030] [018]
		C_BABYMODEPIC,					//      [031] [019]
		C_EASYPIC,						//      [032] [020]
		C_NORMALPIC,					//      [033] [021]
		C_HARDPIC,						//      [034] [022]
		C_LOADSAVEDISKPIC,				//      [035] [023]
		C_DISKLOADING1PIC,				//      [036] [024]
		C_DISKLOADING2PIC,				//      [037] [025]
		C_CONTROLPIC,					//      [038] [026]
		C_CUSTOMIZEPIC,					//      [039] [027]
		C_LOADGAMEPIC,					//      [040] [028]
		C_SAVEGAMEPIC,					//      [041] [029]
		C_EPISODE1PIC,					//      [042] [030]
		C_EPISODE2PIC,					//      [043] [031]
		C_EPISODE3PIC,					//      [044] [032]
		C_EPISODE4PIC,					//      [045] [033]
		C_EPISODE5PIC,					//      [046] [034]
		C_EPISODE6PIC,					//      [047] [035]
		C_CODEPIC,						//      [048] [036]
		C_TIMECODEPIC,					//      [049] [037]
		C_LEVELPIC,						//      [050] [038]
		C_NAMEPIC,						//      [051] [039]
		C_SCOREPIC,						//      [052] [040]
		C_JOY1PIC,						//      [053] [041]
		C_JOY2PIC,						//      [054] [042]
//		Lump Start
		L_GUYPIC,						//      [055] [043]
		L_COLONPIC,						//      [056] [044]
		L_NUM0PIC,						//      [057] [045]
		L_NUM1PIC,						//      [058] [046]
		L_NUM2PIC,						//      [059] [047]
		L_NUM3PIC,						//      [060] [048]
		L_NUM4PIC,						//      [061] [049]
		L_NUM5PIC,						//      [062] [050]
		L_NUM6PIC,						//      [063] [051]
		L_NUM7PIC,						//      [064] [052]
		L_NUM8PIC,						//      [065] [053]
		L_NUM9PIC,						//      [066] [054]
		L_PERCENTPIC,					//      [067] [055]
		L_APIC,							//      [068] [056]
		L_BPIC,							//      [069] [057]
		L_CPIC,							//      [070] [058]
		L_DPIC,							//      [071] [059]
		L_EPIC,							//      [072] [060]
		L_FPIC,							//      [073] [061]
		L_GPIC,							//      [074] [062]
		L_HPIC,							//      [075] [063]
		L_IPIC,							//      [076] [064]
		L_JPIC,							//      [077] [065]
		L_KPIC,							//      [078] [066]
		L_LPIC,							//      [079] [067]
		L_MPIC,							//      [080] [068]
		L_NPIC,							//      [081] [069]
		L_OPIC,							//      [082] [070]
		L_PPIC,							//      [083] [071]
		L_QPIC,							//      [084] [072]
		L_RPIC,							//      [085] [073]
		L_SPIC,							//      [086] [074]
		L_TPIC,							//      [087] [075]
		L_UPIC,							//      [088] [076]
		L_VPIC,							//      [089] [077]
		L_WPIC,							//      [090] [078]
		L_XPIC,							//      [091] [079]
		L_YPIC,							//      [092] [080]
		L_ZPIC,							//      [093] [081]
		L_EXPOINTPIC,					//      [094] [082]
		L_APOSTROPHEPIC,				//      [095] [083]
		L_GUY2PIC,						//      [096] [084]
		L_BJWINSPIC,					//      [097] [085]
		STATUSBARPIC,					//      [098] [086]
		TITLEPIC,						//      [099] [087]
		PG13PIC,						//      [100] [088]
		CREDITSPIC,						//      [101] [089]
		HIGHSCORESPIC,					//      [102] [090]
//		Lump Start
		KNIFEPIC,						//      [103] [091]
		GUNPIC,							//      [104] [092]
		MACHINEGUNPIC,					//      [105] [093]
		GATLINGGUNPIC,					//      [106] [094]
		NOKEYPIC,						//      [107] [095]
		GOLDKEYPIC,						//      [108] [096]
		SILVERKEYPIC,					//      [109] [097]
		N_BLANKPIC,						//      [110] [098]
		N_0PIC,							//      [111] [099]
		N_1PIC,							//      [112] [100]
		N_2PIC,							//      [113] [101]
		N_3PIC,							//      [114] [102]
		N_4PIC,							//      [115] [103]
		N_5PIC,							//      [116] [104]
		N_6PIC,							//      [117] [105]
		N_7PIC,							//      [118] [106]
		N_8PIC,							//      [119] [107]
		N_9PIC,							//      [120] [108]
		FACE1APIC,						//      [121] [109]
		FACE1BPIC,						//      [122] [110]
		FACE1CPIC,						//      [123] [111]
		FACE2APIC,						//      [124] [112]
		FACE2BPIC,						//      [125] [113]
		FACE2CPIC,						//      [126] [114]
		FACE3APIC,						//      [127] [115]
		FACE3BPIC,						//      [128] [116]
		FACE3CPIC,						//      [129] [117]
		FACE4APIC,						//      [130] [118]
		FACE4BPIC,						//      [131] [119]
		FACE4CPIC,						//      [132] [120]
		FACE5APIC,						//      [133] [121]
		FACE5BPIC,						//      [134] [122]
		FACE5CPIC,						//      [135] [123]
		FACE6APIC,						//      [136] [124]
		FACE6BPIC,						//      [137] [125]
		FACE6CPIC,						//      [138] [126]
		FACE7APIC,						//      [139] [127]
		FACE7BPIC,						//      [140] [128]
		FACE7CPIC,						//      [141] [129]
		FACE8APIC,						//      [142] [130]
		GOTGATLINGPIC,					//      [143] [131]
		MUTANTBJPIC,					//      [144] [132]
		GODMODEFACE1PIC,				//      [145] [   ]
		GODMODEFACE2PIC,				//      [146] [   ]
		GODMODEFACE3PIC,				//      [147] [   ]
		PAUSEDPIC,						//      [148] [133]
		GETPSYCHEDPIC,					//      [149] [134]

		STARTTILE8,						//      [150] [135]
		STARTTILE16,					//      [151] [   ]
//		STARTTILE16M,					//      [316] [   ]

		ORDERSCREEN=316,				//      [316] [136]
		ERRORSCREEN,					//      [317] [137]
		T_HELPART,						//      [318] [138]
		T_DEMO0,						//      [319] [139]
		T_DEMO1,						//      [320] [140]
		T_DEMO2,						//      [321] [141]
		T_DEMO3,						//      [322] [142]
		T_ENDART1,						//      [323] [143]
		T_ENDART2,						//      [324] [144]
		T_ENDART3,						//      [325] [145]
		T_ENDART4,						//      [326] [146]
		T_ENDART5,						//      [327] [147]
		T_ENDART6,						//      [328] [148]
		ENUMEND
	} graphicnums;

	//
	// Data LUMPs
	//
	#define README_LUMP_START		3
	#define README_LUMP_END			21				// [9]

	#define CONTROLS_LUMP_START		22				// [10]
	#define CONTROLS_LUMP_END		54				// [42]

	#define LEVELEND_LUMP_START		55				// [43]
	#define LEVELEND_LUMP_END		102				// [85]

	#define LATCHPICS_LUMP_START	KNIFEPIC		// [91]
	#define LATCHPICS_LUMP_END		GETPSYCHEDPIC	// [134]

	#define NUMLATCHPICS			LATCHPICS_LUMP_END - LATCHPICS_LUMP_START + 3

	//
	// Amount of each data item
	//
	#define NUMCHUNKS				ENUMEND			// [149]
	#define NUMFONT					2
	#define NUMFONTM				0
	#define NUMPICS					147				// [132]
	#define NUMPICM					0
	#define NUMSPRITES				0
	#define NUMTILE8				25				// [72]
	#define NUMTILE8M				0
	#define NUMTILE16				165				// [0]
	#define NUMTILE16M				0
	#define NUMTILE32				0
	#define NUMTILE32M				0
	#define NUMEXTERNS				13
	//
	// File offsets for data items
	//
	#define STRUCTPIC				0

	#define STARTFONT				1
	#define STARTFONTM				3
	#define STARTPICS				3
	#define STARTPICM				150				// [135]
	#define STARTSPRITES			150				// [135]
	#define STARTTILE8				150				// [135]
	#define STARTTILE8M				151				// [136]
	#define STARTTILE16				151				// [136]
	#define STARTTILE16M			316				// [136]
	#define STARTTILE32				ORDERSCREEN		// [136]
	#define STARTTILE32M			ORDERSCREEN		// [136]
	#define STARTEXTERNS			ORDERSCREEN		// [136]

	//
	// Thank you for using IGRAB!
	//
