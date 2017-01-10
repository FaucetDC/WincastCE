00001 /* assert.h
00002    Copyright (C) 2001, 2003 Free Software Foundation, Inc.
00003    Written by Stephane Carrez (stcarrez@nerim.fr)       
00004 
00005 This file is free software; you can redistribute it and/or modify it
00006 under the terms of the GNU General Public License as published by the
00007 Free Software Foundation; either version 2, or (at your option) any
00008 later version.
00009 
00010 In addition to the permissions in the GNU General Public License, the
00011 Free Software Foundation gives you unlimited permission to link the
00012 compiled version of this file with other programs, and to distribute
00013 those programs without any restriction coming from the use of this
00014 file.  (The General Public License restrictions do apply in other
00015 respects; for example, they cover modification of the file, and
00016 distribution when not linked into another program.)
00017 
00018 This file is distributed in the hope that it will be useful, but
00019 WITHOUT ANY WARRANTY; without even the implied warranty of
00020 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
00021 General Public License for more details.
00022 
00023 You should have received a copy of the GNU General Public License
00024 along with this program; see the file COPYING.  If not, write to
00025 the Free Software Foundation, 59 Temple Place - Suite 330,
00026 Boston, MA 02111-1307, USA.  */
00027 
00028 #ifndef _ASSERT_H
00029 #define _ASSERT_H
00030 
00031 #ifdef NDEBUG
00032 # define assert(EX)
00033 #else
00034 # define assert(EX) (void)((EX) || (__assert (#EX, __FILE__, __LINE__),0))
00035 #endif
00036 
00037 #ifdef __cplusplus
00038 extern "C" {
00039 #endif
00040 
00041 extern void __assert (const char *msg, const char *file, int line);
00042 
00043 #ifdef __cplusplus
00044 };
00045 #endif
00046 #endif