#if !defined( SCREENFADEH )
#define SCREENFADEH
#pragma once

typedef struct screenfade_s
{
	float		fadeSpeed;		// How fast to fade (tics / second) (+ fade in, - fade out)
	float		fadeEnd;		// When the fading hits maximum
	float		fadeReset;		// When to reset to not fading (for fadeout and hold)
	byte		fader, fadeg, fadeb, fadealpha;	// Fade color
	int			fadeFlags;		// Fading flags
} screenfade_t;

#endif // !SCREENFADEH