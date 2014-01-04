/***************************************************************************** * Copyright (c) 1999-2002, Pierre-Olivier Latour * http://www.pol-online.net * info@pol-online.net * * This program is free software; you can redistribute it and/or modify * it under the terms of the GNU General Public License as published by * the Free Software Foundation; either version 2 of the License, or * (at your option) any later version. *  * This program is distributed in the hope that it will be useful, * but WITHOUT ANY WARRANTY; without even the implied warranty of * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the * GNU General Public License for more details. * * You should have received a copy of the GNU General Public License * along with this program; if not, write to the Free Software * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA. *****************************************************************************/#ifndef __SERIAL_NUMBER__#define __SERIAL_NUMBER__//Constants#define	kKeyMax			9999#define	kKeyMin			1000#define	kNumMax			0x7FFFFFFF#define	kNumMin			0x11111111#define	kMagic_Basic	16807#define	kMagic_Pro		12541//Inlineinline unsigned long MakeSN(StringPtr sn, unsigned long magic, unsigned long key){	unsigned long	num,					i;					Run:	//Make key number	if((key < kKeyMin) || (key > kKeyMax))	return 0;		//Generate num	num = key;	for(i = 0; i < (kKeyMax - key) % kKeyMin; ++i)	num = (num * magic) % kNumMax;		//Check num	if(num < kNumMin) {		++key;		goto Run;	}		//Build sn	sn[0] = 13;	sn[1] = ((num & 0xF0000000) >> 28) + 'A';	sn[2] = ((num & 0x0F000000) >> 24) + 'G';	sn[3] = ((num & 0x00F00000) >> 20) + 'C';	sn[4] = ((num & 0x000F0000) >> 16) + 'E';	sn[5] = ((num & 0x0000F000) >> 12) + 'D';	sn[6] = ((num & 0x00000F00) >> 8) + 'F';	sn[7] = ((num & 0x000000F0) >> 4) + 'B';	sn[8] = ((num & 0x0000000F) >> 0) + 'H';	NumToString(key, &sn[9]);	sn[9] = '-';		return key + 1;}inline Boolean SNValid(StringPtr sn, unsigned long magic){	unsigned long		num = 0,						key,						i,						num2;					//Extract num	num |= ((sn[1] - 'A') << 28) & 0xF0000000;	num |= ((sn[2] - 'G') << 24) & 0x0F000000;	num |= ((sn[3] - 'C') << 20) & 0x00F00000;	num |= ((sn[4] - 'E') << 16) & 0x000F0000;	num |= ((sn[5] - 'D') << 12) & 0x0000F000;	num |= ((sn[6] - 'F') << 8) & 0x00000F00;	num |= ((sn[7] - 'B') << 4) & 0x000000F0;	num |= ((sn[8] - 'H') << 0) & 0x0000000F;		//Extract key	key = (sn[10] - '0') * 1000 + (sn[11] - '0') * 100 + (sn[12] - '0') * 10 + (sn[13] - '0');		//Check key against num	num2 = key;	for(i = 0; i < (kKeyMax - key) % kKeyMin; ++i)	num2 = (num2 * magic) % kNumMax;		return (num2 == num);}#endif //__SERIAL_NUMBER__