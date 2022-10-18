// WL_DEBUG.C

#include "WL_DEF.H"
#pragma hdrstop
#include <BIOS.H>

// Added these so dead enemies will be shown on the map
extern	statetype s_grddie4;
extern	statetype s_dogdead;
extern	statetype s_ofcdie5;
extern	statetype s_mutdie5;
extern	statetype s_ssdie4;
extern	statetype s_fakestand;
extern	statetype s_fakedie6;
extern	statetype s_mechadie4;
extern	statetype s_mechastand;

/*
=============================================================================

						 LOCAL CONSTANTS

=============================================================================
*/

#define VIEWTILEX	(viewwidth/16)
#define VIEWTILEY	(viewheight/16)

/*
=============================================================================

						 GLOBAL VARIABLES

=============================================================================
*/

int DebugKeys (void);

/*
=============================================================================

						 LOCAL VARIABLES

=============================================================================
*/

int	maporgx;
int	maporgy;
enum {mapview,tilemapview,actoratview,visview}	viewtype;

void ViewMap (void);

//===========================================================================

/*
==================
=
= DebugMemory
=
==================
*/

void DebugMemory (void)
{
	int	i;
	char	scratch[80],str[10];
	long	mem;
	spritetype _seg	*block;

	CenterWindow (16,7);

	US_CPrint ("Memory Usage");
	US_CPrint ("------------");
	US_Print ("Total     :");
	US_PrintUnsigned (mminfo.mainmem/1024);
	US_Print ("k\nFree      :");
	US_PrintUnsigned (MM_UnusedMemory()/1024);
	US_Print ("k\nWith purge:");
	US_PrintUnsigned (MM_TotalFree()/1024);
	US_Print ("k\n");
	VW_UpdateScreen();
	IN_Ack ();
}

//===========================================================================

/*
==================
=
= CountObjects
=
==================
*/

void CountObjects (void)
{
//	int	i,total,count,active,inactive,doors;
	int	i,total,count,active,inactive,lgdoors,lsdoors,edoors,ndoors,doors;
	objtype	*obj;

//	CenterWindow (16,7);
	CenterWindow (16,12);
//	active = inactive = count = doors = 0;
	active = inactive = count = lgdoors = lsdoors = edoors = ndoors = doors = 0;

//	US_Print ("Total statics :");
	US_Print ("Total statics    :");
	total = laststatobj-&statobjlist[0];
	US_PrintUnsigned (total);

//	US_Print ("\nIn use statics:");
	US_Print ("\nIn use statics   :");
	for (i=0;i<total;i++)
		if (statobjlist[i].shapenum != -1)
			count++;
//		else
//			doors++;	//debug
	US_PrintUnsigned (count);

//	US_Print ("\nDoors         :");
	US_Print ("\nTotal Doors       :");

	for (i=0;i<doornum;i++)
	{
		if (doorobjlist[i].lock == dr_lock1)
			lgdoors++;
		else if (doorobjlist[i].lock == dr_lock2)
			lsdoors++;
		else if (doorobjlist[i].lock == dr_elevator)
			edoors++;
		else if (doorobjlist[i].lock == dr_normal)
			ndoors++;
		doors++;
	}

//	US_PrintUnsigned (doornum);
	US_PrintUnsigned (doors);

	US_Print ("\nGold Key Doors   :");
	US_PrintUnsigned (lgdoors);

	US_Print ("\nSilver Key Doors :");
	US_PrintUnsigned (lsdoors);

	US_Print ("\nNormal Doors     :");
	US_PrintUnsigned (ndoors);

	US_Print ("\nElevator Doors   :");
	US_PrintUnsigned (edoors);

	for (obj=player->next;obj;obj=obj->next)
	{
		if (obj->active)
			active++;
		else
			inactive++;
	}

//	US_Print ("\nTotal actors  :");
	US_Print ("\nTotal actors     :");
	US_PrintUnsigned (active+inactive);

//	US_Print ("\nActive actors :");
	US_Print ("\nActive actors    :");
	US_PrintUnsigned (active);

	US_Print ("\nInactive actors  :");
	US_PrintUnsigned (inactive);

	VW_UpdateScreen();
	IN_Ack ();
}

//===========================================================================

/*
================
=
= PicturePause
=
================
*/

#if 0
void PicturePause (void)
{
	int			i;
	byte		p;
	unsigned	x;
	byte		far	*dest,far *src;
	memptr		buffer;

	VW_ColorBorder (15);
	/// *** ALPHA RESTORATION ***
//#if (GAMEVER_WOLFREV > GV_WR_WL920312)
	FinishPaletteShifts ();
//#endif

	LastScan = 0;
	while (!LastScan)
	;
	if (LastScan != sc_Enter)
	{
		VW_ColorBorder (0);
		return;
	}

	VW_ColorBorder (1);
	VW_SetScreen (0,0);
		// *** ALPHA RESTORATION ***
//#if (GAMEVER_WOLFREV <= GV_WR_WL920312)
			PM_UnlockMainMem ();
//#endif
//
// vga stuff...
//

		// APOGEE + FORMGEN + ALPHA RESTORATION
//#if (GAMEVER_WOLFREV > GV_WR_WL920312)
	ClearMemory ();
//#if (GAMEVER_WOLFREV > GV_WR_SODFG14A)
	CA_SetAllPurge();
//#endif
//#endif
	MM_GetPtr (&buffer,64000);
	for (p=0;p<4;p++)
	{
		src = MK_FP(0xa000,displayofs);
		dest = (byte far *)buffer+p;
		VGAREADMAP(p);
		// *** PRE-V1.4 APOGEE RESTORATION ***
//#if (GAMEVER_WOLFREV <= GV_WR_WL6AP11)
//		for (x=0;x<16000;x++,dest+=4)
//#else
		for (x=0;x<16000;x++,dest+=4)
//#endif
			*dest = *src++;
	}

	// *** PRE-V1.4 APOGEE RESTORATION ***
	// Re-enable code for pre-v1.4 Apogee releases
//#if (GAMEVER_WOLFREV <= GV_WR_WL6AP11)
//#if 0
	for (p=0;p<4;p++)
	{
		src = MK_FP(0xa000,0);
		dest = (byte far *)buffer+51200+p;
		VGAREADMAP(p);
		for (x=0;x<3200;x++,dest+=4)
			*dest = *src++;
	}
//#endif

	asm	mov	ax,0x13
	asm	int	0x10

	dest = MK_FP(0xa000,0);
	_fmemcpy (dest,buffer,64000);

	VL_SetPalette (&gamepal);

	IN_Shutdown ();

	VW_WaitVBL(70);
	bioskey(0);
	VW_WaitVBL(70);
	Quit (NULL);
}
#endif

//===========================================================================

/*
================
=
= ShapeTest
=
================
*/

#pragma warn -pia
void ShapeTest (void)
{
extern	word	NumDigi;
extern	word	_seg *DigiList;
static	char	buf[10];

	boolean			done;
	ScanCode		scan;
	int				i,j,k,x;
	longword		l;
	memptr			addr;
	PageListStruct	far *page;

	CenterWindow(20,16);
	VW_UpdateScreen();
	for (i = 0,done = false;!done;)
	{
		US_ClearWindow();
//		sound = -1;

		page = &PMPages[i];
		US_Print(" Page #");
		US_PrintUnsigned(i);
		if (i < PMSpriteStart)
			US_Print(" (Wall)");
		else if (i < PMSoundStart)
			US_Print(" (Sprite)");
		else if (i == ChunksInFile - 1)
			US_Print(" (Sound Info)");
		else
			US_Print(" (Sound)");

		US_Print("\n XMS: ");
		if (page->xmsPage != -1)
			US_PrintUnsigned(page->xmsPage);
		else
			US_Print("No");

		US_Print("\n Main: ");
		if (page->mainPage != -1)
			US_PrintUnsigned(page->mainPage);
		else if (page->emsPage != -1)
		{
			US_Print("EMS ");
			US_PrintUnsigned(page->emsPage);
		}
		else
			US_Print("No");

		US_Print("\n Last hit: ");
		US_PrintUnsigned(page->lastHit);

		US_Print("\n Address: ");
		addr = PM_GetPageAddress(i);
		sprintf(buf,"0x%04x",(word)addr);
		US_Print(buf);

		if (addr)
		{
			if (i < PMSpriteStart)
			{
			//
			// draw the wall
			//
				bufferofs += 32*SCREENWIDTH;
				postx = 128;
				postwidth = 1;
				postsource = ((long)((unsigned)addr))<<16;
				for (x=0;x<64;x++,postx++,postsource+=64)
				{
					wallheight[postx] = 256;
					FarScalePost ();
				}
				bufferofs -= 32*SCREENWIDTH;
			}
			else if (i < PMSoundStart)
			{
			//
			// draw the sprite
			//
				bufferofs += 32*SCREENWIDTH;
				SimpleScaleShape (160, i-PMSpriteStart, 64);
				bufferofs -= 32*SCREENWIDTH;
			}
			else if (i == ChunksInFile - 1)
			{
				US_Print("\n\n Number of sounds: ");
				US_PrintUnsigned(NumDigi);
				for (l = j = k = 0;j < NumDigi;j++)
				{
					l += DigiList[(j * 2) + 1];
					k += (DigiList[(j * 2) + 1] + (PMPageSize - 1)) / PMPageSize;
				}
				US_Print("\n Total bytes: ");
				US_PrintUnsigned(l);
				US_Print("\n Total pages: ");
				US_PrintUnsigned(k);
			}
			else
			{
				byte far *dp = (byte far *)MK_FP(addr,0);
				for (j = 0;j < NumDigi;j++)
				{
					k = (DigiList[(j * 2) + 1] + (PMPageSize - 1)) / PMPageSize;
					if
					(
						(i >= PMSoundStart + DigiList[j * 2])
					&&	(i < PMSoundStart + DigiList[j * 2] + k)
					)
						break;
				}
				if (j < NumDigi)
				{
//					sound = j;
					US_Print("\n Sound #");
					US_PrintUnsigned(j);
					US_Print("\n Segment #");
					US_PrintUnsigned(i - PMSoundStart - DigiList[j * 2]);
				}
				for (j = 0;j < page->length;j += 32)
				{
					byte v = dp[j];
					int v2 = (unsigned)v;
					v2 -= 128;
					v2 /= 4;
					if (v2 < 0)
						VWB_Vlin(WindowY + WindowH - 32 + v2,
								WindowY + WindowH - 32,
								WindowX + 8 + (j / 32),BLACK);
					else
						VWB_Vlin(WindowY + WindowH - 32,
								WindowY + WindowH - 32 + v2,
								WindowX + 8 + (j / 32),BLACK);
				}
			}
		}

		VW_UpdateScreen();

		while (!(scan = LastScan))
			SD_Poll();

		IN_ClearKey(scan);
		switch (scan)
		{
			case sc_LeftArrow:
				if (i)
					i--;
				break;
			case sc_RightArrow:
				if (++i >= ChunksInFile)
					i--;
				break;
			case sc_W:	// Walls
				i = 0;
				break;
			case sc_S:	// Sprites
				i = PMSpriteStart;
				break;
			case sc_D:	// Digitized
				i = PMSoundStart;
				break;
			case sc_I:	// Digitized info
				i = ChunksInFile - 1;
				break;
			case sc_L:	// Load all pages
				for (j = 0;j < ChunksInFile;j++)
					PM_GetPage(j);
				break;
			case sc_P:
//				if (sound != -1)
//					SD_PlayDigitized(sound);
				break;
			case sc_Escape:
				done = true;
				break;
			case sc_Enter:
				PM_GetPage(i);
				break;
		}
	}
	SD_StopDigitized();
}
#pragma warn +pia

//===========================================================================

/*
================
=
= DebugKeys
=
================
*/

int DebugKeys (void)
{
	boolean esc;
	int level,i;

#if 0	// this function serves no real purpose in this game
	if (Keyboard[sc_B])					// B = border color
	{
		CenterWindow(24,3);
		PrintY+=6;
		US_Print(" Border color (0-15):");
		VW_UpdateScreen();
		esc = !US_LineInput (px,py,str,NULL,true,2,0);
		if (!esc)
		{
			level = atoi (str);
			if (level>=0 && level<=15)
				VW_ColorBorder (level);
		}
		return 1;
	}
#endif

	if (Keyboard[sc_C])					// C = count objects
	{
		CountObjects();
		return 1;
	}

	if (Keyboard[sc_E])					// E = quit level
	{
		if (tedlevel)
			Quit (NULL);
		playstate = ex_completed;
//		gamestate.mapon++;
	}

	if (Keyboard[sc_F])					// F = facing spot
	{
		CenterWindow (14,4);
		US_Print ("X:");
		US_PrintUnsigned (player->x);
		US_Print ("\nY:");
		US_PrintUnsigned (player->y);
		US_Print ("\nA:");
		US_PrintUnsigned (player->angle);
		VW_UpdateScreen();
		IN_Ack();
		return 1;
	}

#if 0	// removed this as redundant since it's in the main game now
	if (Keyboard[sc_G])					// G = god mode
	{
		CenterWindow (12,2);
		if (godmode)
		  US_PrintCentered ("God mode OFF");
		else
		  US_PrintCentered ("God mode ON");
		VW_UpdateScreen();
		IN_Ack();
		godmode ^= 1;
		return 1;
	}
#endif

	if (Keyboard[sc_H])					// H = hurt self
	{
		IN_ClearKeysDown ();
		TakeDamage (16,NULL);
	}
	else if (Keyboard[sc_I])			// I = item cheat
	{
		CenterWindow (12,3);
		US_PrintCentered ("Free items!");
		VW_UpdateScreen();
		GivePoints (100000);
		HealSelf (99);
		if (gamestate.bestweapon<wp_chaingun)
			GiveWeapon (gamestate.bestweapon+1);
		gamestate.ammo += 50;
		if (gamestate.ammo > 99)
			gamestate.ammo = 99;
		DrawAmmo ();
		IN_Ack ();
		return 1;
	}
	else if (Keyboard[sc_M])			// M = memory info
	{
		DebugMemory();
		return 1;
	}
#if 0	// removed this as redundant since it's in the main game now
//#ifdef SPEAR
	else if (Keyboard[sc_N])			// N = no clip
	{
		noclip^=1;
		CenterWindow (18,3);
		if (noclip)
			US_PrintCentered ("No clipping ON");
		else
			US_PrintCentered ("No clipping OFF");
		VW_UpdateScreen();
		IN_Ack ();
		return 1;
	}
//#endif
//#if 0
	else if (Keyboard[sc_O])			// O = overhead
	{
		ViewMap();
		return 1;
	}
//#endif
	else if (Keyboard[sc_P])			// P = pause with no screen {disruptioon} disruption
	{
		PicturePause ();
		return 1;
	}
#endif
	else if (Keyboard[sc_Q])			// Q = fast quit
		Quit (NULL);
	else if (Keyboard[sc_S])			// S = slow motion
	{
		singlestep^=1;
		CenterWindow (18,3);
		if (singlestep)
			US_PrintCentered ("Slow motion ON");
		else
			US_PrintCentered ("Slow motion OFF");
		VW_UpdateScreen();
		IN_Ack ();
		return 1;
	}
	else if (Keyboard[sc_T])			// T = shape test
	{
		ShapeTest ();
		return 1;
	}
	else if (Keyboard[sc_V])			// V = extra VBLs
	{
		CenterWindow(30,3);
		PrintY+=6;
		US_Print("  Add how many extra VBLs(0-8):");
		VW_UpdateScreen();
		esc = !US_LineInput (px,py,str,NULL,true,2,0);
		if (!esc)
		{
			level = atoi (str);
			if (level>=0 && level<=8)
				extravbls = level;
		}
		return 1;
	}
	else if (Keyboard[sc_W])			// W = warp to level
	{
		CenterWindow(26,3);
		PrintY+=6;
#ifndef SPEAR
		US_Print("  Warp to which level(1-10):");
#else
		US_Print("  Warp to which level(1-21):");
#endif
		VW_UpdateScreen();
		esc = !US_LineInput (px,py,str,NULL,true,2,0);
		if (!esc)
		{
			level = atoi (str);
#ifndef SPEAR
			if (level>0 && level<11)
#else
			if (level>0 && level<22)
#endif
			{
				gamestate.mapon = level-1;
				playstate = ex_warped;
			}
		}
		return 1;
	}
	else if (Keyboard[sc_X])			// X = item cheat
	{
		CenterWindow (12,3);
		US_PrintCentered ("Extra stuff!");
		VW_UpdateScreen();
		// DEBUG: put stuff here
		IN_Ack ();
		return 1;
	}

	return 0;
}

//#if 0
/*
===================
=
= OverheadRefresh
=
===================
*/

void OverheadRefresh (void)
{
	unsigned	x,y,endx,endy,sx,sy;
//	unsigned	tile;
	unsigned	tile,i,temp;
	byte		nosecret;

	doorobj_t	*thisDoor;
	objtype		*check;
	statobj_t	*statptr;

	endx = maporgx+VIEWTILEX;
	endy = maporgy+VIEWTILEY;
	temp = bufferofs;

	for (y=maporgy;y<endy;y++)
	{
		for (x=maporgx;x<endx;x++)
		{
			sx = (x-maporgx)*16;
			sy = (y-maporgy)*16;

			tile = (unsigned)actorat[x][y];

/*
			switch (viewtype)
			{
#if 0
				case mapview:
					tile = *(mapsegs[0]+farmapylookup[y]+x);
					break;

				case tilemapview:
					tile = tilemap[x][y];
					break;

				case visview:
					tile = spotvis[x][y];
					break;
#endif
				case actoratview:
					tile = (unsigned)actorat[x][y];
					break;
			}

			if (tile<MAXWALLTILES)
				LatchDrawTile(sx,sy,tile);
			else
			{
				LatchDrawChar(sx,sy,NUMBERCHARS+((tile&0xf000)>>12));
				LatchDrawChar(sx+8,sy,NUMBERCHARS+((tile&0x0f00)>>8));
				LatchDrawChar(sx,sy+8,NUMBERCHARS+((tile&0x00f0)>>4));
				LatchDrawChar(sx+8,sy+8,NUMBERCHARS+(tile&0x000f));
			}
*/

			for (i = 0; i < 3; i++)
			{
				bufferofs = screenloc[i] + screenofs;
				nosecret = 1;

				if (VW_MarkUpdateBlock(sx,sy,sx+15,sy+15))
				{

					if (tile && tile < 256)
					{

						if (tile<MAXWALLTILES)
						{
							// added this routine to check for elevator control or wall
							if (tile == ELEVATORTILE)
							{
								if ((x > 0 && ((unsigned)actorat[x - 1][y] > 0 && (unsigned)actorat[x - 1][y] < MAXWALLTILES)) &&
									(x < 63 && ((unsigned)actorat[x + 1][y] > 0 && (unsigned)actorat[x + 1][y] < MAXWALLTILES)))
								{
									// When there's a wall to the left and right, draw the elevator side.
									VL_MemToScreen (grsegs[STARTTILE16 + tile],16,16,sx,sy);
								}
								else
								{
									// Draw the elevator switch
									VL_MemToScreen (grsegs[STARTTILE16 + tile + 1],16,16,sx,sy);
									nosecret = 0;
								}
							}
							else
								if (MAPSPOT(x,y,1) == 0 || MAPSPOT(x,y,1) == 98)	// if no object or object is pushwall
									VL_MemToScreen (grsegs[STARTTILE16 + tile],16,16,sx,sy);	// draw the wall
						}
						else if (tile & 0x80)
						{

							thisDoor = &doorobjlist[tile & ~0x80];

							if (thisDoor->lock >= dr_lock1 && thisDoor->lock <= dr_lock4)
								VL_MemToScreen (grsegs[STARTTILE16 + 69],16,16,sx,sy);    // Locked Door
							else if (thisDoor->lock == dr_elevator)
							{
								VL_MemToScreen (grsegs[STARTTILE16 + 68],16,16,sx,sy);    // Elevator Door
								nosecret = 0;
							}
							else if (thisDoor->lock == dr_normal)
								VL_MemToScreen (grsegs[STARTTILE16 + 66],16,16,sx,sy);    // Normal Door
						}
					}
					else if (actorat[x][y])	// if the object is an actor
					{
						for (check = player->next; check; check = check->next)
						{

							if (check->tilex != x || check->tiley != y)
								continue;

							// draw the floor space to prevent the game from showing through behind the actor
							VL_MemToScreen(grsegs[STARTTILE16],16,16,sx,sy);

							switch (check->obclass)
							{
								case guardobj:
									if (check->state == &s_grddie4)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 52],16,16,sx,sy); // draw dead Guard
									else if (check->dir == east)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 53],16,16,sx,sy); // draw east facing Guard
									else if (check->dir == north)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 54],16,16,sx,sy); // draw north facing Guard
									else if (check->dir == west)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 55],16,16,sx,sy); // draw west facing Guard
									else if (check->dir == south)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 56],16,16,sx,sy); // draw south facing Guard
									break;

								case officerobj:
									if (check->state == &s_ofcdie5)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 72],16,16,sx,sy); // draw dead Officer
									else if (check->dir == east)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 73],16,16,sx,sy); // draw east facing Officer
									else if (check->dir == north)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 74],16,16,sx,sy); // draw north facing Officer
									else if (check->dir == west)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 75],16,16,sx,sy); // draw west facing Officer
									else if (check->dir == south)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 76],16,16,sx,sy); // draw south facing Officer
									break;

								case ssobj:
									if (check->state == &s_ssdie4)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 62],16,16,sx,sy); // draw dead SS
									else if (check->dir == east)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 63],16,16,sx,sy); // draw east facing SS
									else if (check->dir == north)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 64],16,16,sx,sy); // draw north facing SS
									else if (check->dir == west)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 65],16,16,sx,sy); // draw west facing SS
									else if (check->dir == south)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 66],16,16,sx,sy); // draw south facing SS
									break;

								case dogobj:
									if (check->state == &s_dogdead)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 57],16,16,sx,sy); // draw dead Dog
									else if (check->dir == east)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 58],16,16,sx,sy); // draw east facing Dog
									else if (check->dir == north)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 59],16,16,sx,sy); // draw north facing Dog
									else if (check->dir == west)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 60],16,16,sx,sy); // draw west facing Dog
									else if (check->dir == south)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 61],16,16,sx,sy); // draw south facing Dog
									break;

								case mutantobj:
									if (check->state == &s_mutdie5)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 67],16,16,sx,sy); // draw dead Mutant
									else if (check->dir == east)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 68],16,16,sx,sy); // draw east facing Mutant
									else if (check->dir == north)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 69],16,16,sx,sy); // draw north facing Mutant
									else if (check->dir == west)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 70],16,16,sx,sy); // draw west facing Mutant
									else if (check->dir == south)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 71],16,16,sx,sy); // draw south facing Mutant
									break;

								case ghostobj:
									switch (check->temp1)
									{
										case en_blinky:
											VL_MaskedToScreen (grsegs[STARTTILE16M + 77],16,16,sx,sy); // draw Red ghost (Blinky)
										break;
										case en_pinky:
											VL_MaskedToScreen (grsegs[STARTTILE16M + 78],16,16,sx,sy); // draw Pink ghost (Pinky)
										break;
										case en_clyde:
											VL_MaskedToScreen (grsegs[STARTTILE16M + 79],16,16,sx,sy); // draw Orange ghost (Clyde)
										break;
										case en_inky:
											VL_MaskedToScreen (grsegs[STARTTILE16M + 80],16,16,sx,sy); // draw Blue ghost (Inky)
										break;
									}
									break;

								case bossobj:
									VL_MaskedToScreen (grsegs[STARTTILE16M + 81],16,16,sx,sy); // draw Hans Grosse
									break;

								case schabbobj:
									VL_MaskedToScreen (grsegs[STARTTILE16M + 82],16,16,sx,sy); // draw Dr. Schabbs
									break;

								case fakeobj:
									if (check->state == &s_fakestand)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 87],16,16,sx,sy); // draw Robed (Fake) Hitler
									else if (check->state == &s_fakedie6)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 88],16,16,sx,sy); // draw dead Robed (Fake) Hitler
									break;

								case mechahitlerobj:
									if (check->state == &s_mechastand)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 89],16,16,sx,sy); // draw Mechanized Hitler
									else if (check->state == &s_mechadie4)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 90],16,16,sx,sy); // draw dead Mechanized Hitler
									break;

								case realhitlerobj:
									VL_MaskedToScreen (grsegs[STARTTILE16M + 85],16,16,sx,sy); // draw Real Hitler
									break;

								case giftobj:
									VL_MaskedToScreen (grsegs[STARTTILE16M + 86],16,16,sx,sy); // draw Otto Giftmacher
									break;

								case gretelobj:
									VL_MaskedToScreen (grsegs[STARTTILE16M + 87],16,16,sx,sy); // draw Gretel Grosse
									break;

								case fatobj:
									VL_MaskedToScreen (grsegs[STARTTILE16M + 88],16,16,sx,sy); // draw General Fettgesicht
									break;

								default:
									if (MAPSPOT(x,y,1) == 124)
										VL_MaskedToScreen (grsegs[STARTTILE16M + 52],16,16,sx,sy);	// draw dead guard
									else
									{
										LatchDrawChar(sx,sy,NUMBERCHARS+((tile&0xf000)>>12));
										LatchDrawChar(sx+8,sy,NUMBERCHARS+((tile&0x0f00)>>8));
										LatchDrawChar(sx,sy+8,NUMBERCHARS+((tile&0x00f0)>>4));
										LatchDrawChar(sx+8,sy+8,NUMBERCHARS+(tile&0x000f));
									}
							}
						}
					}

					else	// draws the floor space initially
						VL_MemToScreen(grsegs[STARTTILE16],16,16,sx,sy);	// draw the floor space

					if (MAPSPOT(x,y,1) && MAPSPOT(x,y,1) < 100 && (MAPSPOT(x,y,1) < 90 || MAPSPOT(x,y,1) > 97))	// if the object is not a movement marker
					{
						if (MAPSPOT(x,y,1) != 98)	// if it's not a pushwall
							VL_MemToScreen(grsegs[STARTTILE16],16,16,sx,sy);	// draw the floor space to deal with the game showing through behind an object

						for (statptr = &statobjlist[0]; statptr != laststatobj; statptr++)
						{
						    if (statptr->tilex != x || statptr->tiley != y)
						        continue;
							else if (statptr->shapenum != -1)
								VL_MaskedToScreen (grsegs[STARTTILE16M + (MAPSPOT(x,y,1) - 19)],16,16,sx,sy); // draw the object
						}
						if (MAPSPOT(x,y,1) == 98 || MAPSPOT(x,y,1) == 99)
							VL_MaskedToScreen (grsegs[STARTTILE16M + (MAPSPOT(x,y,1) - 19)],16,16,sx,sy); // draw the pushwall or endgame object
						if (MAPSPOT(x,y,1) >= 19 && MAPSPOT(x,y,1) <= 22)
							VL_MaskedToScreen (grsegs[STARTTILE16M + (MAPSPOT(x,y,1) - 19)],16,16,sx,sy); // draw the object
					}
					if (MAPSPOT(x,y,0) == 107 && nosecret)
						VL_MaskedToScreen (grsegs[STARTTILE16M + 78],16,16,sx,sy);	// draw the secret floor tile

				}
			}
		}
	}

	bufferofs = temp;

// added this to fill a gap between the status bar and the bottom of the map when screen size is max
	if (viewsize == 19)
	{
		VWB_Bar ((320 - viewwidth) >> 1,viewheight - 4,viewwidth,8,127);
//		VWB_Bar ((320 - viewwidth) >> 1,viewheight - 4,viewwidth,8,BORDERCOLOR);
		fontnumber = 0;
		fontcolor = 14;	// yellow
		PrintX = ((320-viewwidth) >> 1) + 1;	// position on the bar for this element
		PrintY = viewheight - 4;
		US_Print("Kills:");
		fontcolor = 13;	// magenta
		PrintX = ((320-viewwidth) >> 1) + 30;
		US_PrintSigned(gamestate.killtotal - gamestate.killcount);	// remaining on level
		fontcolor = 11;	// cyan
		PrintX = ((320-viewwidth) >> 1) + 53;
		if (gamestate.killtotal > 0)
			US_PrintSigned((gamestate.killcount*100)/gamestate.killtotal);	// percentage achieved so far
		else
			US_PrintSigned(gamestate.killtotal);
		US_Print("%");
		fontcolor = 14;
		PrintX = ((320-viewwidth) >> 1) + 84;
		US_Print("Secret:");
		fontcolor = 13;
		PrintX = ((320-viewwidth) >> 1) + 131;
		US_PrintSigned(gamestate.secrettotal - gamestate.secretcount);	// remaining on level
		fontcolor = 11;
		PrintX = ((320-viewwidth) >> 1) + 154;
		if (gamestate.secrettotal > 0)
			US_PrintSigned((gamestate.secretcount*100)/gamestate.secrettotal);	// percentage achieved so far
		else
			US_PrintSigned(gamestate.secrettotal);
		US_Print("%");
		fontcolor = 14;
		PrintX = ((320-viewwidth) >> 1) + 185;
		US_Print("Treasures:");
		fontcolor = 13;
		PrintX = ((320-viewwidth) >> 1) + 253;
		US_PrintSigned(gamestate.treasuretotal - gamestate.treasurecount);	// remaining on level
		fontcolor = 11;
		PrintX = ((320-viewwidth) >> 1) + 275;
		if (gamestate.treasuretotal > 0)
			US_PrintSigned((gamestate.treasurecount*100)/gamestate.treasuretotal);	// percentage achieved so far
		else
			US_PrintSigned(gamestate.treasuretotal);
		US_Print("%");
		VW_UpdateScreen ();
	}

}
//#endif

//#if 0
/*
===================
=
= ViewMap
=
===================
*/

void ViewMap (void)
{
//	boolean		button0held;

	viewtype = actoratview;
//	button0held = false;

	maporgx = player->tilex - VIEWTILEX/2;
	if (maporgx<0)
		maporgx = 0;
	if (maporgx>MAPSIZE-VIEWTILEX)
		maporgx=MAPSIZE-VIEWTILEX;
	maporgy = player->tiley - VIEWTILEY/2;
	if (maporgy<0)
		maporgy = 0;
	if (maporgy>MAPSIZE-VIEWTILEY)
		maporgy=MAPSIZE-VIEWTILEY;

	do
	{
//
// let user pan around
//
		PollControls ();
		if (controlx < 0 && maporgx>0)
			maporgx--;
		if (controlx > 0 && maporgx<mapwidth-VIEWTILEX)
			maporgx++;
		if (controly < 0 && maporgy>0)
			maporgy--;
		if (controly > 0 && maporgy<mapheight-VIEWTILEY)
			maporgy++;

#if 0
		if (c.button0 && !button0held)
		{
			button0held = true;
			viewtype++;
			if (viewtype>visview)
				viewtype = mapview;
		}
		if (!c.button0)
			button0held = false;
#endif

		OverheadRefresh ();

	} while (!Keyboard[sc_Escape]);

	IN_ClearKeysDown ();
}
//#endif
