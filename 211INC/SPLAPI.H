/********************************************************************
  splapi.h

    History:
	3/98	Created by Donald Karlov [donkarl]

  ©1998 Microsoft Corporation
********************************************************************/

// @CESYSGEN IF CE_MODULES_SPLUSA
#if !defined(__INCLUDE_SPELLER)
#define __INCLUDE_SPELLER

typedef	HANDLE	HSPL;

typedef struct	tagSPLSUGGEST
{
    WCHAR  *pwsz;
    DWORD   nScore;
} SPLSUGGEST, *PSPLSUGGEST;

typedef struct	tagSPLBUFFER
{
const	WCHAR	   *pwszIn;			// Text to be processed
		WCHAR	   *pwszOut;		// Results written here
		SPLSUGGEST	aspl[8];		// Information about results
		DWORD		iwcIn;			// Start processing at this index
		DWORD		cwcIn;			// Input buffer is this size
		DWORD		dwMode;			// Processing mode
		DWORD		cwcOut;			// Output buffer is this size
		DWORD		cwcUsed;		// This much was used
		DWORD		dwErr;			// What type of error was detected
		DWORD		iwcErr;			// Where the error occurs
		DWORD		cwcErr;			// How long the error is
		DWORD		cspl;			// How many suggestions were made
} SPLBUFFER, *PSPLBUFFER;

#define	SPL_OK									 0
#define	SPL_ERROR_CAPITALIZATION				 1
#define	SPL_INITIAL_NUMERAL						 2
#define	SPL_MORE_INFO_THAN_BUFFER_CAN_HOLD		 3
#define	SPL_NO_MORE_SUGGESTIONS					 4
#define	SPL_REPEAT_WORD							 5
#define	SPL_RETURNING_AUTO_REPLACE				 6
#define	SPL_RETURNING_CHANGE_ALWAYS				 7
#define	SPL_RETURNING_CHANGE_ONCE				 8
#define	SPL_UNKNOWN_INPUT_WORD					 9
#define	SPL_WORD_CONSIDERED_ABBREVIATION		10
#define	SPL_UNKNOWN_ERROR						15

// Scoring guidelines.  These can be passed to the SplLimitSet function and
// come back as scores in the SPLSUGGEST buffer.

#define	SPL_LIMIT_NONE						256
#define	SPL_LIMIT_CAPITAL					255
#define	SPL_LIMIT_DROP_DOUBLE_CONSONANT		242
#define	SPL_LIMIT_ADD_DOUBLE_CONSONANT		242
#define	SPL_LIMIT_TRANSPOSE_VOWEL			241
#define	SPL_LIMIT_DROP_DOUBLE_VOWEL			240
#define	SPL_LIMIT_ADD_DOUBLE_VOWEL			240
#define	SPL_LIMIT_TRANSPOSE_CONSONANT		238
#define	SPL_LIMIT_TRANSPOSE					237
#define	SPL_LIMIT_SUBSTITUTE_VOWEL			235
#define	SPL_LIMIT_DROP						225
#define	SPL_LIMIT_ADD						221
#define	SPL_LIMIT_SUBSTITUTE_CONSONANT		215
#define	SPL_LIMIT_SUBSTITUTE				213

#define	SPL_FIND_INITIAL_NUMERALS			0x00000001
#define	SPL_FIND_REPEAT_WORD				0x00000002
#define	SPL_IGNORE_ALL_CAPS					0x00000004
#define	SPL_IGNORE_INITIAL_CAP				0x00000008	
#define	SPL_IGNORE_MIXED_DIGITS				0x00000010
#define	SPL_IGNORE_ROMAN_NUMERALS			0x00000020
#define	SPL_IGNORE_SINGLE_LETTER			0x00000040
#define	SPL_SCORE_SUGGESTIONS				0x00000080
#define	SPL_SINGLE_STEP_SUGGEST				0x00000100
#define	SPL_SUGGEST_FROM_USER_DICT			0x00000200

#define	SPL_NO_STATE_INFO					0x00000000
#define	SPL_IS_CONTINUED					0x00000001
#define	SPL_IS_EDITED_CHANGE				0x00000002
#define	SPL_STARTS_SENTENCE					0x00000004

// These indecies are passed to user dictionary functions to specify the
// three 'built-in' dictionaries.  These dictionaries are created as empty
// at initialization and are automatically destroyed on exit.

#define	SPL_IGNORE_LEX			-3
#define	SPL_CHANGE_ALWAYS_LEX	-2
#define	SPL_CHANGE_ONCE_LEX		-1

#if defined(__cplusplus)
extern "C" {
#endif

int	WINAPI	SplInit(HSPL *phspl, int clex, WCHAR **ppwsz);
int	WINAPI	SplQuit(HSPL hspl);
int	WINAPI	SplOptionSet(HSPL hspl, DWORD dw);
int	WINAPI	SplOptionGet(HSPL hspl, DWORD *pdw);
int	WINAPI	SplLimitSet(HSPL hspl, DWORD dw);
int	WINAPI	SplLimitGet(HSPL hspl, DWORD *pdw);
int	WINAPI	SplCheck(HSPL hspl, SPLBUFFER *psb);
int	WINAPI	SplSuggest(HSPL hspl, SPLBUFFER *psb);
int	WINAPI	SplReplace(HSPL hspl, SPLBUFFER *psb);
int	WINAPI	SplAddUserDict(HSPL hspl, int nID, const WCHAR *pwszAdd, const WCHAR *pwszChange);
int	WINAPI	SplRemUserDict(HSPL hspl, int nID, const WCHAR *pwsz);
int	WINAPI	SplClrUserDict(HSPL hspl, int nID);
int	WINAPI	SplSizeUserDict(HSPL hspl, int nID, DWORD *pdw);
int	WINAPI	SplEnumUserDict(HSPL hspl, int nID, DWORD nIndex, SPLBUFFER *psb);

#if defined(__cplusplus)
};
#endif

#endif	// __INCLUDE_SPELLER

// @CESYSGEN ENDIF
