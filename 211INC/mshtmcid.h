//*********************************************************************
//*                  Microsoft Windows                               **
//*            Copyright(c) Microsoft Corp., 1996-1997               **
//*********************************************************************

#ifndef __mshtmcid_h__
#define __mshtmcid_h__

//----------------------------------------------------------------------------
//
// MSHTML Command IDs
//
//----------------------------------------------------------------------------

#define IDM_UNKNOWN                 0
#define IDM_ALIGNBOTTOM             1
#define IDM_ALIGNHORIZONTALCENTERS  2
#define IDM_ALIGNLEFT               3
#define IDM_ALIGNRIGHT              4
#define IDM_ALIGNTOGRID             5
#define IDM_ALIGNTOP                6
#define IDM_ALIGNVERTICALCENTERS    7
#define IDM_ARRANGEBOTTOM           8
#define IDM_ARRANGERIGHT            9
#define IDM_BRINGFORWARD            10
#define IDM_BRINGTOFRONT            11
#define IDM_CENTERHORIZONTALLY      12
#define IDM_CENTERVERTICALLY        13
#define IDM_CODE                    14
#define IDM_DELETE                  17
#define IDM_FONTNAME                18
#define IDM_FONTSIZE                19
#define IDM_GROUP                   20
#define IDM_HORIZSPACECONCATENATE   21
#define IDM_HORIZSPACEDECREASE      22
#define IDM_HORIZSPACEINCREASE      23
#define IDM_HORIZSPACEMAKEEQUAL     24
#define IDM_INSERTOBJECT            25
#define IDM_MULTILEVELREDO          30
#define IDM_SENDBACKWARD            32
#define IDM_SENDTOBACK              33
#define IDM_SHOWTABLE               34
#define IDM_SIZETOCONTROL           35
#define IDM_SIZETOCONTROLHEIGHT     36
#define IDM_SIZETOCONTROLWIDTH      37
#define IDM_SIZETOFIT               38
#define IDM_SIZETOGRID              39
#define IDM_SNAPTOGRID              40
#define IDM_TABORDER                41
#define IDM_TOOLBOX                 42
#define IDM_MULTILEVELUNDO          44
#define IDM_UNGROUP                 45
#define IDM_VERTSPACECONCATENATE    46
#define IDM_VERTSPACEDECREASE       47
#define IDM_VERTSPACEINCREASE       48
#define IDM_VERTSPACEMAKEEQUAL      49
#define IDM_JUSTIFYFULL             50
#define IDM_BACKCOLOR               51
#define IDM_BOLD                    52
#define IDM_BORDERCOLOR             53
#define IDM_FLAT                    54
#define IDM_FORECOLOR               55
#define IDM_ITALIC                  56
#define IDM_JUSTIFYCENTER           57
#define IDM_JUSTIFYGENERAL          58
#define IDM_JUSTIFYLEFT             59
#define IDM_JUSTIFYRIGHT            60
#define IDM_RAISED                  61
#define IDM_SUNKEN                  62
#define IDM_UNDERLINE               63
#define IDM_CHISELED                64
#define IDM_ETCHED                  65
#define IDM_SHADOWED                66
#define IDM_FIND                    67
#define IDM_SHOWGRID                69
#define IDM_OBJECTVERBLIST0         72
#define IDM_OBJECTVERBLIST1         73
#define IDM_OBJECTVERBLIST2         74
#define IDM_OBJECTVERBLIST3         75
#define IDM_OBJECTVERBLIST4         76
#define IDM_OBJECTVERBLIST5         77
#define IDM_OBJECTVERBLIST6         78
#define IDM_OBJECTVERBLIST7         79
#define IDM_OBJECTVERBLIST8         80
#define IDM_OBJECTVERBLIST9         81
#define IDM_OBJECTVERBLISTLAST IDM_OBJECTVERBLIST9
#define IDM_CONVERTOBJECT           82
#define IDM_CUSTOMCONTROL           83
#define IDM_CUSTOMIZEITEM           84
#define IDM_RENAME                  85
#define IDM_IMPORT                  86
#define IDM_NEWPAGE                 87
#define IDM_MOVE                    88
#define IDM_CANCEL                  89
#define IDM_FONT                    90
#define IDM_STRIKETHROUGH           91
#define IDM_DELETEWORD              92

#define IDM_FOLLOW_ANCHOR           2008

#define IDM_INSINPUTIMAGE           2114
#define IDM_INSINPUTBUTTON          2115
#define IDM_INSINPUTRESET           2116
#define IDM_INSINPUTSUBMIT          2117
#define IDM_INSINPUTUPLOAD          2118
#define IDM_INSFIELDSET             2119

#define IDM_PASTEINSERT             2120
#define IDM_REPLACE                 2121
#define IDM_EDITSOURCE              2122
#define IDM_BOOKMARK                2123
#define IDM_HYPERLINK               2124
#define IDM_UNLINK                  2125
#define IDM_BROWSEMODE              2126
#define IDM_EDITMODE                2127
#define IDM_UNBOOKMARK              2128

#define IDM_TOOLBARS                2130
#define IDM_STATUSBAR               2131
#define IDM_FORMATMARK              2132
#define IDM_TEXTONLY                2133
#define IDM_OPTIONS                 2135
#define IDM_FOLLOWLINKC             2136
#define IDM_FOLLOWLINKN             2137
#define IDM_VIEWSOURCE              2139
#define IDM_ZOOMPOPUP               2140

// IDM_BASELINEFONT1, IDM_BASELINEFONT2, IDM_BASELINEFONT3, IDM_BASELINEFONT4,
// and IDM_BASELINEFONT5 should be consecutive integers;
//
#define IDM_BASELINEFONT1           2141
#define IDM_BASELINEFONT2           2142
#define IDM_BASELINEFONT3           2143
#define IDM_BASELINEFONT4           2144
#define IDM_BASELINEFONT5           2145

#define IDM_HORIZONTALLINE          2150
#define IDM_LINEBREAKNORMAL         2151
#define IDM_LINEBREAKLEFT           2152
#define IDM_LINEBREAKRIGHT          2153
#define IDM_LINEBREAKBOTH           2154
#define IDM_NONBREAK                2155
#define IDM_SPECIALCHAR             2156
#define IDM_HTMLSOURCE              2157
#define IDM_IFRAME                  2158
#define IDM_HTMLCONTAIN             2159
#define IDM_TEXTBOX                 2161
#define IDM_TEXTAREA                2162
#define IDM_CHECKBOX                2163
#define IDM_RADIOBUTTON             2164
#define IDM_DROPDOWNBOX             2165
#define IDM_LISTBOX                 2166
#define IDM_BUTTON                  2167
#define IDM_IMAGE                   2168
#define IDM_OBJECT                  2169
#define IDM_1D                      2170
#define IDM_IMAGEMAP                2171
#define IDM_FILE                    2172
#define IDM_COMMENT                 2173
#define IDM_SCRIPT                  2174
#define IDM_JAVAAPPLET              2175
#define IDM_PLUGIN                  2176
#define IDM_PAGEBREAK               2177

#define IDM_PARAGRAPH               2180
#define IDM_FORM                    2181
#define IDM_MARQUEE                 2182
#define IDM_LIST                    2183
#define IDM_ORDERLIST               2184
#define IDM_UNORDERLIST             2185
#define IDM_INDENT                  2186
#define IDM_OUTDENT                 2187
#define IDM_PREFORMATTED            2188
#define IDM_ADDRESS                 2189
#define IDM_BLINK                   2190
#define IDM_DIV                     2191

#define IDM_TABLEINSERT             2200
#define IDM_RCINSERT                2201
#define IDM_CELLINSERT              2202
#define IDM_CAPTIONINSERT           2203
#define IDM_CELLMERGE               2204
#define IDM_CELLSPLIT               2205
#define IDM_CELLSELECT              2206
#define IDM_ROWSELECT               2207
#define IDM_COLUMNSELECT            2208
#define IDM_TABLESELECT             2209
#define IDM_TABLEPROPERTIES         2210
#define IDM_CELLPROPERTIES          2211
#define IDM_ROWINSERT               2212
#define IDM_COLUMNINSERT            2213

#define IDM_HELP_CONTENT            2220
#define IDM_HELP_ABOUT              2221
#define IDM_HELP_README             2222

#define IDM_REMOVEFORMAT            2230
#define IDM_PAGEINFO                2231
#define IDM_TELETYPE                2232
#define IDM_GETBLOCKFMTS            2233
#define IDM_BLOCKFMT                2234
#define IDM_SHOWHIDE_CODE           2235
#define IDM_TABLE                   2236

#define IDM_COPYFORMAT              2237
#define IDM_PASTEFORMAT             2238
#define IDM_GOTO                    2239

#define IDM_CHANGEFONT              2240
#define IDM_CHANGEFONTSIZE          2241
#define IDM_INCFONTSIZE             2242
#define IDM_DECFONTSIZE             2243
#define IDM_INCFONTSIZE1PT          2244
#define IDM_DECFONTSIZE1PT          2245
#define IDM_CHANGECASE              2246
#define IDM_SUBSCRIPT               2247
#define IDM_SUPERSCRIPT             2248
#define IDM_SHOWSPECIALCHAR         2249

#define IDM_CENTERALIGNPARA         2250
#define IDM_LEFTALIGNPARA           2251
#define IDM_RIGHTALIGNPARA          2252
#define IDM_REMOVEPARAFORMAT        2253
#define IDM_APPLYNORMAL             2254
#define IDM_APPLYHEADING1           2255
#define IDM_APPLYHEADING2           2256
#define IDM_APPLYHEADING3           2257

#define IDM_DOCPROPERTIES           2260
#define IDM_ADDFAVORITES            2261
#define IDM_COPYSHORTCUT            2262
#define IDM_SAVEBACKGROUND          2263
#define IDM_SETWALLPAPER            2264
#define IDM_COPYBACKGROUND          2265
#define IDM_CREATESHORTCUT          2266
#define IDM_PAGE                    2267
#define IDM_SAVETARGET              2268
#define IDM_SHOWPICTURE             2269
#define IDM_SAVEPICTURE             2270
#define IDM_DYNSRCPLAY              2271
#define IDM_DYNSRCSTOP              2272
#define IDM_PRINTTARGET             2273
#define IDM_IMGARTPLAY              2274
#define IDM_IMGARTSTOP              2275
#define IDM_IMGARTREWIND            2276
#define IDM_PRINTQUERYJOBSPENDING   2277

#define IDM_CONTEXTMENU             2280
#define IDM_GOBACKWARD              2282
#define IDM_GOFORWARD               2283
#define IDM_PRESTOP                 2284

#define IDM_CREATELINK              2290
#define IDM_COPYCONTENT             2291

#define IDM_LANGUAGE                2292

#define IDM_REFRESH                 2300
#define IDM_STOPDOWNLOAD            2301

#define IDM_ENABLE_INTERACTION      2302

#define IDM_LAUNCHDEBUGGER          2310
#define IDM_BREAKATNEXT             2311

#define IDM_INSINPUTHIDDEN          2312
#define IDM_INSINPUTPASSWORD        2313

#define IDM_OVERWRITE               2314

#define IDM_PARSECOMPLETE           2315

#define IDM_HTMLEDITMODE            2316

#define IDM_REGISTRYREFRESH         2317
#define IDM_COMPOSESETTINGS         2318

#define IDM_SHOWALLTAGS             2320
#define IDM_SHOWALIGNEDSITETAGS     2321
#define IDM_SHOWSCRIPTTAGS          2322
#define IDM_SHOWSTYLETAGS           2323
#define IDM_SHOWCOMMENTTAGS         2324
#define IDM_SHOWAREATAGS            2325
#define IDM_SHOWUNKNOWNTAGS         2326
#define IDM_SHOWMISCTAGS            2327
#define IDM_SHOWZEROBORDERATDESIGNTIME         2328

#define IDM_AUTODETECT              2329

#define IDM_SCRIPTDEBUGGER          2330

#define IDM_GETBYTESDOWNLOADED      2331

#define IDM_NOACTIVATENORMALOLECONTROLS        2332
#define IDM_NOACTIVATEDESIGNTIMECONTROLS       2333
#define IDM_NOACTIVATEJAVAAPPLETS              2334

#define IDM_SHOWWBRTAGS             2340

#define IDM_PERSISTSTREAMSYNC       2341
#define IDM_SETDIRTY                2342


#define IDM_MIMECSET__FIRST__           3609
#define IDM_MIMECSET__LAST__            3640

#define IDM_MENUEXT_FIRST__       3700
#define IDM_MENUEXT_LAST__        3732
#define IDM_MENUEXT_COUNT         3733

// Commands mapped from the standard set.  We should
// consider deleting them from public header files.

#define IDM_OPEN                    2000
#define IDM_NEW                     2001
#define IDM_SAVE                    70
#define IDM_SAVEAS                  71
#define IDM_SAVECOPYAS              2002
#define IDM_PRINTPREVIEW            2003
#define IDM_PRINT                   27
#define IDM_PAGESETUP               2004
#define IDM_SPELL                   2005
#define IDM_PASTESPECIAL            2006
#define IDM_CLEARSELECTION          2007
#define IDM_PROPERTIES              28
#define IDM_REDO                    29
#define IDM_UNDO                    43
#define IDM_SELECTALL               31
#define IDM_ZOOMPERCENT             50
#define IDM_GETZOOM                 68
#define IDM_STOP                    2138
#define IDM_COPY                    15
#define IDM_CUT                     16
#define IDM_PASTE                   26

// Defines for IDM_ZOOMPERCENT
#define CMD_ZOOM_PAGEWIDTH -1
#define CMD_ZOOM_ONEPAGE -2
#define CMD_ZOOM_TWOPAGES -3
#define CMD_ZOOM_SELECTION -4
#define CMD_ZOOM_FIT -5


#endif
