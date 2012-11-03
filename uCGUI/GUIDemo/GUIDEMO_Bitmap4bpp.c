/*
*********************************************************************************************************
*                                                uC/GUI
*                        Universal graphic software for embedded applications
*
*                       (c) Copyright 2002, Micrium Inc., Weston, FL
*                       (c) Copyright 2002, SEGGER Microcontroller Systeme GmbH
*
*              �C/GUI is protected by international copyright laws. Knowledge of the
*              source code may not be used to write a similar product. This file may
*              only be used in accordance with a license and should not be redistributed
*              in any way. We appreciate your understanding and fairness.
*
----------------------------------------------------------------------
File        : GUIDEMO_Bitmap4bpp.c
Purpose     : Contains a 4bpp bitmap
----------------------------------------------------------------------
*/

#include "GUI.h"
#include "GUIDEMO.H"

/*********************************************************************
*
*       Static data
*
**********************************************************************
*/

static const GUI_COLOR _ColorsJoerg[] = {
   0x000000, 0x111111, 0x222222, 0x333333
  ,0x444444, 0x555555, 0x666666, 0x777777
  ,0x888888, 0x999999, 0xAAAAAA, 0xBBBBBB
  ,0xCCCCCC, 0xDDDDDD, 0xEEEEEE, 0xFFFFFF
};

static const GUI_LOGPALETTE _PalJoerg = {
  16,	/* number of entries */
  0, 	/* No transparency */
  &_ColorsJoerg[0]
};

static const unsigned char _acJoerg[] = {
  0x88, 0x88, 0x88, 0x88, 0x89, 0x88, 0x99, 0x99, 0x89, 0x99, 0x88, 0x99, 0x98, 0x88, 0x98, 0x88, 0x89, 0x88, 0x89, 0x99, 0x88, 0x89, 0x88, 0x98, 0x98, 0x89, 0x88, 0x89, 0x98, 0x88, 0x80,
  0x88, 0x88, 0x88, 0x89, 0x88, 0x88, 0x88, 0x89, 0x89, 0x99, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x89, 0x89, 0x88, 0x98, 0x88, 0x89, 0x98, 0x89, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x88, 0x88, 0x88, 0x88, 0x89, 0x88, 0x88, 0x88, 0x89, 0x88, 0x88, 0x88, 0x77, 0x75, 0x68, 0x56, 0x55, 0x55, 0x68, 0x88, 0x88, 0x99, 0x98, 0x99, 0x98, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x88, 0x88, 0x88, 0x88, 0x89, 0x88, 0x88, 0x88, 0x88, 0x85, 0x44, 0x55, 0x53, 0x54, 0x35, 0x33, 0x44, 0x44, 0x46, 0x67, 0x78, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 0x78, 0x75, 0x43, 0x33, 0x33, 0x33, 0x34, 0x33, 0x33, 0x33, 0x44, 0x55, 0x67, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x98, 0x99, 0x88, 0x88, 0x88, 0x88, 0x87, 0x86, 0x63, 0x33, 0x33, 0x33, 0x33, 0x23, 0x22, 0x22, 0x23, 0x33, 0x33, 0x34, 0x56, 0x44, 0x68, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 0x85, 0x47, 0x54, 0x33, 0x33, 0x32, 0x22, 0x23, 0x22, 0x22, 0x22, 0x22, 0x22, 0x33, 0x33, 0x33, 0x43, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x88, 0x88, 0x88, 0x88, 0x88, 0x86, 0x44, 0x43, 0x44, 0x33, 0x33, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x33, 0x23, 0x23, 0x33, 0x45, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x88, 0x88, 0x88, 0x88, 0x87, 0x65, 0x43, 0x33, 0x33, 0x33, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x23, 0x34, 0x46, 0x76, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x98, 0x88, 0x88, 0x88, 0x76, 0x54, 0x33, 0x33, 0x23, 0x32, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x22, 0x22, 0x22, 0x22, 0x33, 0x33, 0x44, 0x48, 0x88, 0x88, 0x88, 0x88, 0x80,
  0x9A, 0x99, 0x99, 0x99, 0x75, 0x43, 0x33, 0x33, 0x22, 0x22, 0x22, 0x22, 0x22, 0x12, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x23, 0x33, 0x33, 0x34, 0x76, 0x78, 0x88, 0x88, 0x88, 0x80,
  0x99, 0x99, 0x99, 0x97, 0x43, 0x33, 0x32, 0x32, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x21, 0x22, 0x12, 0x22, 0x12, 0x22, 0x22, 0x32, 0x22, 0x22, 0x34, 0x34, 0x88, 0x99, 0x99, 0x99, 0x90,
  0x99, 0x99, 0x99, 0x75, 0x43, 0x32, 0x22, 0x22, 0x22, 0x23, 0x23, 0x22, 0x22, 0x22, 0x21, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x23, 0x34, 0x68, 0x89, 0x89, 0x89, 0x80,
  0xAA, 0xAA, 0xA9, 0x86, 0x53, 0x22, 0x21, 0x22, 0x22, 0x23, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x24, 0x58, 0x99, 0x99, 0x99, 0x90,
  0xAA, 0xAA, 0xAA, 0x85, 0x32, 0x22, 0x21, 0x12, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x24, 0x46, 0x79, 0x99, 0x99, 0x90,
  0xAA, 0xAA, 0xA6, 0x33, 0x22, 0x22, 0x21, 0x22, 0x23, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x11, 0x22, 0x22, 0x22, 0x22, 0x22, 0x35, 0x68, 0x99, 0x99, 0x90,
  0xBB, 0xBA, 0xA4, 0x32, 0x22, 0x21, 0x21, 0x22, 0x23, 0x22, 0x22, 0x22, 0x22, 0x33, 0x33, 0x32, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x22, 0x34, 0x66, 0x99, 0x99, 0x90,
  0xBB, 0xBA, 0x83, 0x22, 0x21, 0x12, 0x22, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x23, 0x33, 0x22, 0x33, 0x32, 0x22, 0x21, 0x12, 0x22, 0x33, 0x89, 0x99, 0x90,
  0xBB, 0xBA, 0x63, 0x22, 0x21, 0x11, 0x23, 0x34, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x44, 0x34, 0x45, 0x43, 0x33, 0x33, 0x32, 0x32, 0x21, 0x12, 0x22, 0x23, 0x69, 0x99, 0x90,
  0xBB, 0xBA, 0x32, 0x22, 0x21, 0x22, 0x34, 0x44, 0x45, 0x55, 0x55, 0x55, 0x55, 0x55, 0x44, 0x44, 0x45, 0x44, 0x54, 0x43, 0x33, 0x33, 0x33, 0x43, 0x21, 0x12, 0x22, 0x33, 0x58, 0x99, 0x90,
  0xBB, 0xB6, 0x33, 0x22, 0x22, 0x23, 0x44, 0x55, 0x55, 0x56, 0x66, 0x66, 0x76, 0x66, 0x66, 0x55, 0x66, 0x55, 0x55, 0x44, 0x44, 0x44, 0x44, 0x44, 0x32, 0x22, 0x22, 0x23, 0x36, 0x99, 0x90,
  0xBB, 0x92, 0x33, 0x22, 0x22, 0x34, 0x55, 0x55, 0x56, 0x66, 0x66, 0x66, 0x66, 0x77, 0x77, 0x66, 0x67, 0x76, 0x66, 0x66, 0x66, 0x65, 0x55, 0x55, 0x43, 0x22, 0x22, 0x22, 0x34, 0x99, 0x90,
  0xBB, 0x43, 0x32, 0x22, 0x23, 0x44, 0x55, 0x55, 0x56, 0x66, 0x66, 0x76, 0x66, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76, 0x66, 0x66, 0x65, 0x54, 0x21, 0x12, 0x22, 0x33, 0x69, 0x90,
  0xBC, 0x33, 0x32, 0x22, 0x24, 0x45, 0x55, 0x66, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76, 0x65, 0x55, 0x42, 0x12, 0x22, 0x34, 0x79, 0x90,
  0xBB, 0x33, 0x22, 0x22, 0x34, 0x45, 0x55, 0x66, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76, 0x66, 0x55, 0x43, 0x11, 0x22, 0x33, 0x69, 0x90,
  0xBB, 0x23, 0x23, 0x22, 0x34, 0x55, 0x55, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76, 0x55, 0x43, 0x22, 0x22, 0x33, 0x49, 0x90,
  0xBB, 0x23, 0x33, 0x33, 0x34, 0x55, 0x55, 0x66, 0x67, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x87, 0x77, 0x87, 0x77, 0x77, 0x77, 0x77, 0x77, 0x76, 0x65, 0x54, 0x32, 0x22, 0x33, 0x47, 0x90,
  0xBA, 0x33, 0x33, 0x33, 0x44, 0x55, 0x55, 0x66, 0x67, 0x67, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 0x77, 0x77, 0x77, 0x76, 0x65, 0x55, 0x32, 0x22, 0x33, 0x38, 0x90,
  0xB8, 0x33, 0x23, 0x33, 0x44, 0x55, 0x55, 0x66, 0x66, 0x77, 0x77, 0x77, 0x78, 0x88, 0x89, 0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 0x77, 0x77, 0x76, 0x66, 0x55, 0x32, 0x23, 0x24, 0x38, 0x90,
  0xB9, 0x33, 0x33, 0x33, 0x45, 0x55, 0x55, 0x56, 0x66, 0x67, 0x77, 0x78, 0x88, 0x88, 0x89, 0x98, 0x99, 0x99, 0x98, 0x88, 0x87, 0x77, 0x77, 0x76, 0x66, 0x65, 0x43, 0x23, 0x33, 0x49, 0x90,
  0xB9, 0x32, 0x33, 0x34, 0x44, 0x55, 0x55, 0x56, 0x66, 0x67, 0x77, 0x88, 0x88, 0x88, 0x89, 0x88, 0x99, 0x89, 0x98, 0x88, 0x88, 0x77, 0x77, 0x76, 0x66, 0x65, 0x43, 0x33, 0x33, 0x49, 0x90,
  0xB9, 0x22, 0x33, 0x34, 0x44, 0x55, 0x55, 0x56, 0x66, 0x67, 0x77, 0x88, 0x88, 0x88, 0x99, 0x89, 0x98, 0x98, 0x88, 0x88, 0x88, 0x77, 0x76, 0x76, 0x66, 0x55, 0x43, 0x33, 0x34, 0x79, 0x90,
  0xB8, 0x32, 0x33, 0x34, 0x44, 0x55, 0x55, 0x56, 0x66, 0x67, 0x77, 0x87, 0x88, 0x88, 0x89, 0x89, 0x99, 0x98, 0x88, 0x88, 0x88, 0x77, 0x76, 0x66, 0x65, 0x55, 0x44, 0x33, 0x33, 0x89, 0x90,
  0xB5, 0x32, 0x33, 0x34, 0x44, 0x55, 0x55, 0x56, 0x66, 0x67, 0x77, 0x77, 0x88, 0x88, 0x89, 0x89, 0x99, 0x88, 0x88, 0x88, 0x78, 0x77, 0x76, 0x66, 0x66, 0x65, 0x43, 0x33, 0x33, 0x99, 0x90,
  0xB5, 0x32, 0x23, 0x34, 0x45, 0x55, 0x56, 0x66, 0x66, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x98, 0x89, 0x88, 0x88, 0x87, 0x77, 0x77, 0x66, 0x66, 0x55, 0x43, 0x33, 0x25, 0x99, 0x90,
  0xBA, 0x32, 0x23, 0x33, 0x45, 0x55, 0x66, 0x56, 0x66, 0x77, 0x77, 0x77, 0x78, 0x88, 0x89, 0x89, 0x88, 0x89, 0x88, 0x88, 0x88, 0x77, 0x77, 0x76, 0x66, 0x55, 0x43, 0x33, 0x28, 0x99, 0x90,
  0xB9, 0x23, 0x33, 0x34, 0x45, 0x55, 0x66, 0x66, 0x66, 0x77, 0x77, 0x77, 0x78, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 0x77, 0x77, 0x77, 0x66, 0x65, 0x43, 0x23, 0x29, 0x99, 0x90,
  0xB9, 0x23, 0x33, 0x33, 0x55, 0x56, 0x66, 0x66, 0x66, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x89, 0x88, 0x88, 0x78, 0x77, 0x77, 0x77, 0x76, 0x65, 0x43, 0x23, 0x39, 0x99, 0x90,
  0xBB, 0x33, 0x33, 0x34, 0x55, 0x66, 0x66, 0x66, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x77, 0x77, 0x77, 0x76, 0x66, 0x53, 0x23, 0x1A, 0x99, 0x90,
  0xAA, 0x33, 0x33, 0x33, 0x55, 0x56, 0x66, 0x66, 0x66, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x89, 0x88, 0x88, 0x88, 0x78, 0x77, 0x77, 0x76, 0x66, 0x53, 0x23, 0x1A, 0xA9, 0x90,
  0xAA, 0x23, 0x33, 0x34, 0x56, 0x66, 0x66, 0x66, 0x66, 0x66, 0x77, 0x78, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 0x77, 0x77, 0x76, 0x66, 0x53, 0x23, 0x1A, 0x99, 0x90,
  0xAA, 0x73, 0x33, 0x45, 0x66, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x66, 0x78, 0x88, 0x88, 0x88, 0x88, 0x88, 0x87, 0x77, 0x66, 0x66, 0x77, 0x76, 0x66, 0x53, 0x33, 0x3A, 0x9A, 0xA0,
  0xAB, 0x84, 0x33, 0x35, 0x66, 0x56, 0x55, 0x44, 0x45, 0x43, 0x33, 0x34, 0x56, 0x67, 0x87, 0x77, 0x77, 0x88, 0x65, 0x65, 0x45, 0x55, 0x65, 0x66, 0x66, 0x66, 0x64, 0x33, 0x5A, 0x9A, 0xA0,
  0xAA, 0x33, 0x33, 0x36, 0x66, 0x65, 0x44, 0x45, 0x56, 0x55, 0x44, 0x44, 0x55, 0x66, 0x77, 0x67, 0x77, 0x77, 0x54, 0x44, 0x44, 0x44, 0x45, 0x55, 0x66, 0x66, 0x63, 0x33, 0x8A, 0x9A, 0xA0,
  0xA6, 0x63, 0x33, 0x46, 0x66, 0x65, 0x55, 0x56, 0x67, 0x77, 0x76, 0x55, 0x55, 0x66, 0x78, 0x77, 0x87, 0x76, 0x55, 0x55, 0x67, 0x77, 0x76, 0x55, 0x55, 0x66, 0x63, 0x43, 0x99, 0x9A, 0xA0,
  0xA5, 0x35, 0x33, 0x46, 0x66, 0x55, 0x55, 0x65, 0x65, 0x52, 0x34, 0x45, 0x54, 0x56, 0x78, 0x88, 0x88, 0x76, 0x66, 0x77, 0x88, 0x87, 0x77, 0x65, 0x65, 0x56, 0x63, 0x33, 0x34, 0xAA, 0xA0,
  0xB4, 0x45, 0x44, 0x46, 0x66, 0x65, 0x55, 0x43, 0x12, 0x2A, 0x12, 0x54, 0x44, 0x45, 0x68, 0x88, 0x88, 0x76, 0x66, 0x44, 0x12, 0x46, 0x77, 0x66, 0x66, 0x66, 0x63, 0x33, 0x77, 0x9A, 0xA0,
  0xB4, 0x45, 0x54, 0x46, 0x66, 0x66, 0x65, 0x32, 0x83, 0x22, 0x35, 0x75, 0x55, 0x45, 0x68, 0x88, 0x87, 0x65, 0x54, 0x51, 0x2A, 0x24, 0x24, 0x66, 0x67, 0x76, 0x63, 0x37, 0x75, 0x8A, 0xA0,
  0xB6, 0x45, 0x44, 0x56, 0x66, 0x66, 0x54, 0x55, 0x66, 0x34, 0x58, 0x56, 0x67, 0x44, 0x67, 0x88, 0x86, 0x68, 0x56, 0x83, 0x32, 0x39, 0x74, 0x46, 0x67, 0x77, 0x64, 0x57, 0x66, 0x9A, 0xA0,
  0xA7, 0x56, 0x54, 0x56, 0x66, 0x66, 0x56, 0x66, 0x66, 0x66, 0x77, 0x66, 0x66, 0x55, 0x67, 0x88, 0x87, 0x77, 0x65, 0x67, 0x44, 0x77, 0x66, 0x55, 0x67, 0x77, 0x64, 0x68, 0x76, 0x9A, 0xA0,
  0xA8, 0x56, 0x54, 0x56, 0x66, 0x66, 0x65, 0x56, 0x66, 0x77, 0x87, 0x66, 0x65, 0x55, 0x67, 0x78, 0x87, 0x67, 0x66, 0x67, 0x76, 0x77, 0x76, 0x66, 0x67, 0x76, 0x64, 0x78, 0x65, 0x9A, 0xA0,
  0xAB, 0x66, 0x43, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x76, 0x55, 0x56, 0x67, 0x87, 0x77, 0x76, 0x77, 0x77, 0x78, 0x88, 0x77, 0x77, 0x76, 0x76, 0x64, 0x88, 0x67, 0xAA, 0xA0,
  0xAB, 0x56, 0x44, 0x56, 0x66, 0x66, 0x76, 0x66, 0x77, 0x77, 0x77, 0x66, 0x65, 0x56, 0x67, 0x77, 0x87, 0x76, 0x77, 0x87, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x65, 0x68, 0x78, 0xAA, 0xA0,
  0xAA, 0x46, 0x46, 0x56, 0x66, 0x66, 0x77, 0x77, 0x77, 0x77, 0x76, 0x77, 0x65, 0x66, 0x67, 0x88, 0x87, 0x76, 0x77, 0x88, 0x88, 0x77, 0x88, 0x77, 0x77, 0x76, 0x66, 0x68, 0x7A, 0xAA, 0xA0,
  0xBA, 0x46, 0x55, 0x56, 0x66, 0x66, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x66, 0x65, 0x67, 0x78, 0x87, 0x66, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x77, 0x76, 0x67, 0x78, 0x7A, 0xAA, 0xA0,
  0xAA, 0x46, 0x63, 0x67, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x66, 0x66, 0x67, 0x78, 0x87, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x88, 0x77, 0x76, 0x76, 0x78, 0x9A, 0xAA, 0xA0,
  0xAA, 0x55, 0x65, 0x37, 0x66, 0x66, 0x67, 0x67, 0x77, 0x77, 0x77, 0x77, 0x66, 0x56, 0x66, 0x78, 0x77, 0x66, 0x77, 0x88, 0x77, 0x77, 0x78, 0x88, 0x77, 0x76, 0x86, 0x78, 0xAA, 0xAA, 0xA0,
  0xAA, 0x95, 0x76, 0x56, 0x66, 0x66, 0x66, 0x77, 0x77, 0x87, 0x77, 0x87, 0x75, 0x56, 0x67, 0x78, 0x77, 0x76, 0x88, 0x88, 0x88, 0x77, 0x78, 0x87, 0x77, 0x77, 0x67, 0x77, 0xAA, 0xAA, 0xA0,
  0xAA, 0xA5, 0x66, 0x57, 0x66, 0x66, 0x67, 0x77, 0x77, 0x87, 0x88, 0x87, 0x55, 0x56, 0x67, 0x77, 0x87, 0x66, 0x78, 0x88, 0x88, 0x88, 0x87, 0x87, 0x78, 0x76, 0x79, 0x77, 0xAA, 0xAA, 0xA0,
  0xAA, 0xA7, 0x66, 0x57, 0x66, 0x66, 0x67, 0x77, 0x77, 0x88, 0x88, 0x76, 0x56, 0x66, 0x67, 0x78, 0x87, 0x66, 0x68, 0x89, 0x88, 0x88, 0x88, 0x87, 0x77, 0x76, 0x99, 0x77, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0x66, 0x56, 0x66, 0x66, 0x77, 0x77, 0x78, 0x88, 0x77, 0x65, 0x57, 0x66, 0x67, 0x8A, 0x97, 0x77, 0x77, 0x79, 0x98, 0x98, 0x88, 0x88, 0x87, 0x76, 0x88, 0x6A, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0x66, 0x57, 0x66, 0x66, 0x77, 0x77, 0x78, 0x88, 0x76, 0x65, 0x57, 0x76, 0x68, 0x89, 0x88, 0x77, 0x77, 0x77, 0x89, 0x98, 0x88, 0x88, 0x87, 0x76, 0x87, 0x6A, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0xA6, 0x57, 0x66, 0x66, 0x77, 0x77, 0x77, 0x77, 0x77, 0x65, 0x44, 0x46, 0x68, 0x88, 0x88, 0x77, 0x77, 0x77, 0x88, 0x98, 0x88, 0x88, 0x87, 0x76, 0x88, 0x7A, 0xAA, 0xAA, 0xA0,
  0xA9, 0xAA, 0xAA, 0xA8, 0x66, 0x66, 0x77, 0x77, 0x77, 0x77, 0x76, 0x76, 0x55, 0x44, 0x47, 0x77, 0x86, 0x55, 0x77, 0x77, 0x78, 0x88, 0x88, 0x88, 0x77, 0x76, 0x76, 0xAA, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0xAA, 0xA9, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x76, 0x66, 0x66, 0x54, 0x45, 0x66, 0x66, 0x66, 0x77, 0x78, 0x88, 0x88, 0x88, 0x88, 0x77, 0x66, 0x8B, 0xAA, 0xAA, 0xAA, 0xA0,
  0x9A, 0xAA, 0xA9, 0x9A, 0x77, 0x66, 0x77, 0x77, 0x77, 0x77, 0x76, 0x66, 0x66, 0x66, 0x65, 0x45, 0x56, 0x67, 0x77, 0x77, 0x87, 0x88, 0x88, 0x88, 0x77, 0x75, 0xBA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0xAA, 0xAA, 0x67, 0x66, 0x77, 0x77, 0x77, 0x77, 0x66, 0x66, 0x67, 0x67, 0x87, 0x77, 0x77, 0x77, 0x77, 0x77, 0x87, 0x78, 0x88, 0x88, 0x77, 0x64, 0xBA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xA9, 0xAA, 0xAA, 0xAA, 0x67, 0x66, 0x67, 0x77, 0x77, 0x77, 0x56, 0x55, 0x55, 0x66, 0x77, 0x77, 0x78, 0x87, 0x67, 0x77, 0x88, 0x77, 0x88, 0x88, 0x77, 0x75, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0xAA, 0xA9, 0x57, 0x66, 0x67, 0x78, 0x87, 0x76, 0x33, 0x34, 0x33, 0x45, 0x57, 0x77, 0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x87, 0x77, 0x79, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0xAA, 0xAA, 0x76, 0x66, 0x77, 0x77, 0x89, 0x77, 0x66, 0x54, 0x44, 0x43, 0x23, 0x34, 0x34, 0x56, 0x66, 0x75, 0x68, 0x78, 0x88, 0x88, 0x77, 0x5B, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xAA, 0xAA, 0xAA, 0xAA, 0x76, 0x66, 0x75, 0x78, 0x88, 0x77, 0x76, 0x65, 0x55, 0x56, 0x65, 0x55, 0x55, 0x43, 0x34, 0x67, 0x67, 0x88, 0x88, 0x88, 0x76, 0x5A, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xA9, 0xAA, 0xAA, 0xAA, 0x76, 0x77, 0x76, 0x77, 0x78, 0x87, 0x76, 0x66, 0x65, 0x56, 0x66, 0x67, 0x66, 0x56, 0x67, 0x88, 0x88, 0x88, 0x88, 0x87, 0x76, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xA9, 0xAA, 0xAA, 0xAA, 0x66, 0x67, 0x67, 0x77, 0x78, 0x87, 0x76, 0x76, 0x76, 0x66, 0x76, 0x67, 0x67, 0x77, 0x78, 0x88, 0x88, 0x88, 0x88, 0x87, 0x77, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xA9, 0x9A, 0xAA, 0xAA, 0x66, 0x66, 0x77, 0x77, 0x77, 0x77, 0x76, 0x76, 0x77, 0x67, 0x66, 0x67, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x77, 0x7B, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xA9, 0xAA, 0xAA, 0xAA, 0x66, 0x56, 0x67, 0x77, 0x77, 0x77, 0x76, 0x67, 0x67, 0x77, 0x77, 0x77, 0x88, 0x88, 0x78, 0x88, 0x88, 0x88, 0x88, 0x77, 0x6A, 0xBA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xA9, 0xAA, 0xAA, 0x74, 0x65, 0x55, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x77, 0xBA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0xAA, 0x9A, 0xA8, 0x54, 0x65, 0x55, 0x66, 0x66, 0x67, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x78, 0x5B, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0x99, 0xA9, 0x97, 0x45, 0x66, 0x65, 0x66, 0x66, 0x66, 0x66, 0x77, 0x77, 0x66, 0x67, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x76, 0xBA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBA, 0xA0,
  0x99, 0x99, 0x85, 0x75, 0x66, 0x66, 0x55, 0x55, 0x66, 0x66, 0x67, 0x77, 0x67, 0x77, 0x78, 0x87, 0x88, 0x88, 0x88, 0x88, 0x78, 0x77, 0x75, 0xBA, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xAA, 0xA0,
  0x99, 0x99, 0x93, 0x73, 0x66, 0x66, 0x55, 0x55, 0x56, 0x66, 0x66, 0x77, 0x67, 0x78, 0x78, 0x88, 0x88, 0x88, 0x88, 0x87, 0x87, 0x77, 0x67, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0x99, 0x99, 0x95, 0x63, 0x65, 0x66, 0x56, 0x55, 0x55, 0x56, 0x67, 0x77, 0x67, 0x67, 0x78, 0x88, 0x88, 0x88, 0x87, 0x77, 0x77, 0x76, 0x66, 0xAB, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0x99, 0x99, 0x97, 0x33, 0x65, 0x55, 0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x66, 0x77, 0x77, 0x77, 0x88, 0x87, 0x77, 0x77, 0x76, 0x66, 0x74, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xA0,
  0x99, 0x99, 0xA3, 0x32, 0x55, 0x66, 0x65, 0x55, 0x55, 0x55, 0x65, 0x66, 0x66, 0x77, 0x77, 0x77, 0x77, 0x88, 0x77, 0x77, 0x66, 0x67, 0x62, 0xA9, 0xAA, 0xBA, 0xAA, 0xBB, 0xAA, 0xAA, 0xA0,
  0x99, 0x9A, 0x91, 0x23, 0x56, 0x66, 0x66, 0x55, 0x55, 0x55, 0x55, 0x66, 0x66, 0x77, 0x77, 0x77, 0x77, 0x87, 0x77, 0x66, 0x76, 0x77, 0x62, 0x9A, 0xAA, 0xBA, 0xBA, 0xAA, 0xBA, 0xBA, 0xA0,
  0x99, 0x9A, 0xA1, 0x33, 0x56, 0x66, 0x66, 0x55, 0x55, 0x55, 0x55, 0x55, 0x66, 0x67, 0x77, 0x76, 0x76, 0x76, 0x66, 0x67, 0x77, 0x77, 0x33, 0x9A, 0xAA, 0xAA, 0xAA, 0xAA, 0xBB, 0xAB, 0xB0,
  0x99, 0x9A, 0xA2, 0x23, 0x55, 0x66, 0x66, 0x65, 0x55, 0x55, 0x55, 0x55, 0x56, 0x66, 0x66, 0x66, 0x66, 0x55, 0x56, 0x67, 0x77, 0x77, 0x23, 0x9A, 0xAA, 0xBB, 0xBB, 0xAA, 0xBA, 0xAA, 0xB0,
  0x99, 0x9A, 0xA5, 0x34, 0x55, 0x66, 0x66, 0x65, 0x66, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x55, 0x66, 0x67, 0x77, 0x77, 0x77, 0x22, 0x9A, 0xAB, 0xAA, 0xBA, 0xAA, 0xBA, 0xAA, 0xA0,
  0x99, 0x9A, 0xA8, 0x34, 0x45, 0x66, 0x66, 0x56, 0x66, 0x65, 0x55, 0x55, 0x55, 0x55, 0x55, 0x56, 0x66, 0x67, 0x77, 0x77, 0x77, 0x75, 0x31, 0x8A, 0xAA, 0x9A, 0xAA, 0xBB, 0xAB, 0xBA, 0xA0,
  0x99, 0x9A, 0xA9, 0x34, 0x45, 0x66, 0x76, 0x66, 0x66, 0x65, 0x66, 0x66, 0x66, 0x65, 0x67, 0x77, 0x77, 0x77, 0x88, 0x77, 0x77, 0x75, 0x31, 0x9B, 0xBA, 0xBA, 0xAA, 0x9A, 0xBB, 0xBA, 0xB0,
  0x9A, 0x9A, 0xAA, 0x54, 0x45, 0x56, 0x66, 0x76, 0x77, 0x66, 0x66, 0x77, 0x77, 0x77, 0x67, 0x77, 0x77, 0x77, 0x78, 0x77, 0x77, 0x64, 0x31, 0xAA, 0xAA, 0xAB, 0xBB, 0xBA, 0x9A, 0xAA, 0xB0,
  0x99, 0x9A, 0xAA, 0xA3, 0x45, 0x56, 0x66, 0x77, 0x77, 0x67, 0x67, 0x77, 0x77, 0x77, 0x88, 0x88, 0x88, 0x88, 0x87, 0x77, 0x77, 0x64, 0x35, 0xAA, 0xBA, 0xBB, 0xBA, 0xAA, 0xBB, 0xAA, 0xA0,
  0xA9, 0xAA, 0xAA, 0xB8, 0x44, 0x56, 0x66, 0x77, 0x77, 0x77, 0x77, 0x77, 0x77, 0x88, 0x89, 0x88, 0x88, 0x88, 0x78, 0x77, 0x77, 0x53, 0x27, 0xAB, 0xBA, 0xBA, 0xBB, 0xBB, 0xBA, 0xAA, 0xB0
};

/*********************************************************************
*
*       GUIDEMO_bm4bpp
*
**********************************************************************
*/

const GUI_BITMAP GUIDEMO_bm4bpp = {
  61,        /* XSize */
  92,        /* YSize */
  31,        /* BytesPerLine */
  4,         /* BitsPerPixel */
  _acJoerg,  /* Pointer to picture data (indices) */
  &_PalJoerg /* Pointer to palette */
};
	 	 			 		    	 				 	  			   	 	 	 	 	 	  	  	      	   		 	 	 		  		  	 		 	  	  			     			       	   	 			  		    	 	     	 				  	 					 	 			   	  	  			 				 		 	 	 			     			 
