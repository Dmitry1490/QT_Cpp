/*
 *        Bal_Cs.cpp
 */

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
#include "Bal_Cs.h"
//---------------------------------------------------------------------------

/***************************************************************************/
/* Calculate check sum (CS) of byte array                                  */
/* ----------------------------------------------------------------------- */

int CSByte( unsigned char  *cBuf, unsigned int len, bool bCheck )
{
   unsigned int i = 0, CS = 0x55;

   do
   {
      CS <<= 1;                                 // rol CS
      CS = (CS & 0xFE) ^ (CS & 0x100)>>8;
      CS = (CS + (cBuf[i])) & 0xFF;             // CS = CS + b[i]

      ++i;

   }  while ( i < len );

   if ( bCheck )
      return ( cBuf[i] ^ CS );                  // check CS
   else
   {
      cBuf[i] = CS;                             // write CS
      return 0;
   }
}
//---------------------------------------------------------------------------

/***************************************************************************/
/* Calculate check sum (CS) of word array                                  */
/* ----------------------------------------------------------------------- */

int CSWord( unsigned short *wBuf, unsigned int len, bool bCheck )
{
   unsigned int i = 1, CS = 0x55;

   CS <<= 1;                                    // rol CS
   CS = (CS & 0xFE) ^ (CS & 0x100)>>8;
   CS = (CS + (wBuf[0] & 0xFF)) & 0xFF;         // CS = CS + w[i] (low byte)

   do
   {
      CS <<= 1;                                 // rol CS
      CS = (CS & 0xFE) ^ (CS & 0x100)>>8;
      CS = (CS + (wBuf[i]>>8    )) & 0xFF;      // CS = CS + w[i] (high byte)
      CS <<= 1;                                 // rol CS
      CS = (CS & 0xFE) ^ (CS & 0x100)>>8;
      CS = (CS + (wBuf[i] & 0xFF)) & 0xFF;      // CS = CS + w[i] (low byte)

      ++i;

   }  while ( i < len );

   if ( bCheck )
      return ( wBuf[0]>>8 ^ CS );               // check CS
   else
   {
      wBuf[0] &= 0xFF;                          // write CS
      wBuf[0] ^= CS<<8;
      return 0;
   }
}
//---------------------------------------------------------------------------

/***************************************************************************/
/* Calculate internal control symbol (ICS) of word array                   */
/* ----------------------------------------------------------------------- */

int ICSWord( unsigned short *wBuf, unsigned int len, bool bCheck )
{
   unsigned int i = 1, ICS = 0x55;

   do
   {
      ICS <<= 1;                                // rol ICS
      ICS = (ICS & 0xFE) ^ (ICS & 0x100)>>8;
      ICS = (ICS + (wBuf[i]>>8)) & 0xFF;        // ICS = ICS + w[i] (high byte)
      ICS = ICS<<1;                             // rol ICS
      ICS = (ICS & 0xFE) ^ (ICS & 0x100)>>8;
      ICS = (ICS + (wBuf[i] & 0xFF)) & 0xFF;    // ICS = ICS + w[i] (low byte)

      ++i;

   } while ( i < len );

   if ( bCheck )
      return ( (wBuf[0] & 0xFF) ^ ICS );        // check ICS
   else
   {
      wBuf[0] &= 0xFF00;                        // write ICS
      wBuf[0] ^= ICS;
      return 0;
   }
}
//---------------------------------------------------------------------------

/***************************************************************************/
/* Calculate checksum of IKPMO word array                                  */
/* ----------------------------------------------------------------------- */

unsigned short ikpCSWord( unsigned short *wBuf, unsigned int len )
{
   unsigned int  i = 0, CS = 0;

   do
   {
      CS = (CS + wBuf[i]) & 0xFFFF;
      ++i;

   } while ( i < len );

   return (unsigned short)CS;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------

