/*
 *        Bal_Cs.h
 */

#ifndef _BAL_CS_H_
#define _BAL_CS_H_

//===========================================================================
// Function prototype
//===========================================================================

int  CSByte( unsigned char  *cBuf, unsigned int len, bool bCheck );

int  CSWord( unsigned short *wBuf, unsigned int len, bool bCheck );
int ICSWord( unsigned short *wBuf, unsigned int len, bool bCheck );

unsigned short ikpCSWord( unsigned short *wBuf, unsigned int len );

//---------------------------------------------------------------------------

#endif /* _BAL_CS_H_ */

