#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include "library.h"
#include "graphics.h"
#include "touch.h"

typedef int BOOL ;
#define	FALSE			0
#define	TRUE			1

typedef struct // ax^2 + bx^1 + c
	{
	float				a ;
	float				b ;
	float				c ;
	} COEF ;

typedef struct
	{
	const char *		name ;
	float * const		pval ;
	const float			vmin ;
	const float			vmax ;
	const uint32_t		xmin ;
	const uint32_t		ymin ;
	const uint32_t		width ;
	const uint32_t		height ;
	uint32_t			xpos ;
	} SLIDER ;

typedef struct
	{
	uint32_t			number ;
	float				first ;
	float				second ;
	} ROOTS ;

#define	GFXCOL1			23
#define	GFXCOLN			(XPIXELS - GFXCOL1)
#define	GFXCOLS			(GFXCOLN - GFXCOL1 + 1)

#define	GFXROW1			54
#define	GFXROWN			215
#define	GFXROWS			(GFXROWN - GFXROW1 + 1)

#define	AXISROW			(GFXROW1 + GFXROWS/2)
#define	AXISCOL			(GFXCOL1 + GFXCOLS/2)

#define	TICKRATEX		(GFXCOLS/6)
#define	TICKRATEY		(GFXROWS/6)
#define	TICKSIZE		4

#define	ROOT_RAD		3

#define	COLOR_PLOT		COLOR_RED
#define	COLOR_ROOT		COLOR_RED
#define	COLOR_AXIS		COLOR_BLACK

#define	DOMAIN_MIN		-15.0
#define	DOMAIN_MAX		+15.0

#define	RANGE_MIN		-15.0
#define	RANGE_MAX		+15.0

#define	FONT_WIDTH		7
#define	FONT_HEIGHT		12

#define	SLIDER_BGCLR	COLOR_LIGHTGRAY
#define	SLIDER_FGCLR	COLOR_BLACK
#define	SLIDER_ROFFSET	2
#define	SLIDER_LOFFSET	(3*FONT_WIDTH+1)
#define	SLIDER_HSIZE	(XPIXELS - SLIDER_LOFFSET - SLIDER_ROFFSET - 3*FONT_WIDTH)
#define	SLIDER_VSIZE	12
#define	SLIDER_SSIZE	SLIDER_VSIZE

#define	A_VMIN			-3.0
#define	A_VMAX			+3.0
#define	A_XMIN			SLIDER_LOFFSET
#define	A_YMIN			230

#define	B_VMIN			-10.0
#define	B_VMAX			+10.0
#define	B_XMIN			SLIDER_LOFFSET
#define	B_YMIN			(A_YMIN + SLIDER_VSIZE + 16)

#define	C_VMIN			-15.0
#define	C_VMAX			+15.0
#define	C_XMIN			SLIDER_LOFFSET
#define	C_YMIN			(B_YMIN + SLIDER_VSIZE + 16)

#define	ENTRIES(a)		(sizeof(a)/sizeof(a[0]))

#define	ACCURACY		0.001

// Functions to be implemented in assembly
extern float			Discriminant(float a, float b, float c) ;
extern float			Quadratic(float x, float a, float b, float c) ;
extern float			Root1(float a, float b, float c) ;
extern float			Root2(float a, float b, float c) ;

// Functions private to this source code file
static BOOL				Adjusted(SLIDER sliders[], uint32_t count) ;
static int32_t			Between(uint32_t min, uint32_t val, uint32_t max) ;
static float			CorrectDisc(COEF *coef) ;
static float			CorrectQuad(float x, COEF *coef) ;
static float			CorrectRoot1(COEF *coef) ;
static float			CorrectRoot2(COEF *coef) ;
static BOOL				DiscOK(float theirs, float mine) ;
static void				DrawXAxis(void) ;
static void				DrawYAxis(void) ;
static void				Error(COEF *coef, char *fmt, ...) ;
static void				InitializeTouchScreen(void) ;
static void				InitSliders(SLIDER sliders[], uint32_t count) ;
static void				LEDs(int grn_on, int red_on) ;
static void				PutStringAt(int x, int y, char *fmt, ...) ;
static void				PlotQuadratic(COEF *coef, uint32_t color) ;
static void				PlotRoot(float x, uint32_t color) ;
static void				PlotRoots(COEF *coef, ROOTS *roots) ;
static BOOL				QuadOK(float theirs, float mine) ;
static BOOL				RootOK(float theirs, float mine) ;
static float			SquareRoot(float radical) ;
static void				UpdateValue(SLIDER *s, uint32_t x) ;
static void				UpdateSlider(SLIDER *s, uint32_t x) ;

int main(void)
	{
	static COEF coef, init = {1.0, 0.0, -10.0} ;
	static SLIDER sliders[] =
		{
		{"a", &coef.a, A_VMIN, A_VMAX, A_XMIN, A_YMIN, SLIDER_HSIZE, SLIDER_VSIZE},
		{"b", &coef.b, B_VMIN, B_VMAX, B_XMIN, B_YMIN, SLIDER_HSIZE, SLIDER_VSIZE},
		{"c", &coef.c, C_VMIN, C_VMAX, C_XMIN, C_YMIN, SLIDER_HSIZE, SLIDER_VSIZE}
		} ;
	static ROOTS roots = {0, 0.0, 0.0} ;
	COEF prev ;

	InitializeHardware(HEADER, "Lab 8b: Hardware Fl-Pt Quadratics") ;
	LEDs(0, 1) ; InitializeTouchScreen() ;

	coef = init ;
	InitSliders(sliders, ENTRIES(sliders)) ;
	LEDs(1, 0) ;

	prev = coef = init ;
	while (1)
		{
		// Erase the old plot and roots
		PlotQuadratic(&prev, COLOR_WHITE) ;
		if (roots.number >= 1) PlotRoot(roots.first, COLOR_WHITE) ;
		if (roots.number == 2) PlotRoot(roots.second, COLOR_WHITE) ;
		roots.number = 0 ;

		// Redraw the x and y axis
		DrawXAxis() ;
		DrawYAxis() ;

		// Plot the new quadratic
		PlotQuadratic(&coef, COLOR_PLOT) ;
		prev = coef ;

		// Plot the new roots
		PlotRoots(&coef, &roots) ;

		// Wait for user input
		while (1)
			{
			if (TS_Touched())
				{
				if (Adjusted(sliders, ENTRIES(sliders)))
					{
					// Any change in coefficient values?
					if (memcmp(&coef, &prev, sizeof(COEF)) != 0) break ;
					}
				}

			if (PushButtonPressed())
				{
				WaitForPushButton() ;
				coef = init ;
				InitSliders(sliders, ENTRIES(sliders)) ;
				break ;
				}
			}
		}

	return 0 ;
	}

static void PlotRoots(COEF *coef, ROOTS *roots)
	{
	float disc ;

	if (coef->a == 0.0)	// linear?
		{
		if (coef->b != 0.0)	// Constant?
			{
			roots->number = 1 ;
			roots->first = -coef->c / coef->b ;
			PlotRoot(roots->first, COLOR_ROOT) ;
			}
		return ;
		}

	disc = Discriminant(coef->a, coef->b, coef->c) ;
	if (!DiscOK(disc, CorrectDisc(coef)))
		{
		Error(coef, "Disc != %f (%08X)", disc, *((uint32_t *) &disc)) ;
		}

	if (disc > 0.0)
		{
		roots->number = 2 ;
		roots->first = Root1(coef->a, coef->b, coef->c) ;
		if (!RootOK(roots->first, CorrectRoot1(coef)))
			{
			Error(coef, "Root1 != %f (%08X)", roots->first, *((uint32_t *) &roots->first)) ;
			}
		PlotRoot(roots->first, COLOR_ROOT) ;
		roots->second = Root2(coef->a, coef->b, coef->c) ;
		if (!RootOK(roots->second, CorrectRoot2(coef)))
			{
			Error(coef, "Root2 != %f (%08X)", roots->second, *((uint32_t *) &roots->second)) ;
			}
		PlotRoot(roots->second, COLOR_ROOT) ;
		return ;
		}

	if (disc == 0.0)
		{
		roots->number = 1 ;
		roots->first = Root1(coef->a, coef->b, coef->c) ;
		if (!RootOK(roots->first, CorrectRoot1(coef)))
			{
			Error(coef, "Root1 != %f (%08X)", roots->first, *((uint32_t *) &roots->first)) ;
			}
		else PlotRoot(roots->first, COLOR_ROOT) ;
		}
	}

static void InitializeTouchScreen(void)
	{
	static char *message[] =
		{
		"If this message remains on",
		"the screen, there is an",
		"initialization problem with",
		"the touch screen. This does",
		"NOT mean that there is a",
		"problem with your code.",
		" ",
		"To correct the problem,",
		"disconnect and reconnect",
		"the power.",
		NULL
		} ;
	char **pp ;
	unsigned x, y ;

	x = 25 ;
	y = 100 ;
	for (pp = message; *pp != NULL; pp++)
		{
		DisplayStringAt(x, y, *pp) ;
		y += 12 ;
		}
	TS_Init() ;
	ClearDisplay() ;
	}

static void PutStringAt(int x, int y, char *fmt, ...)
	{
	va_list args ;
	char text[100] ;

	va_start(args, fmt) ;
	vsprintf(text, fmt, args) ;
	va_end(args) ;

	DisplayStringAt(x, y, text) ;
	}

static BOOL Adjusted(SLIDER sliders[], uint32_t count)
	{
	uint32_t which, x, y ;
	SLIDER *s ;

	x = TS_GetX() ;
	y = TS_GetY() ;

	s = sliders ;
	for (which = 0; which < count; which++, s++)
		{
		uint32_t xmax = s->xmin + s->width - SLIDER_SSIZE/2 - 1 ;
		uint32_t xmin = s->xmin + SLIDER_SSIZE/2 ;
		if (!Between(s->ymin, y, s->ymin + s->height - 1))	continue ;
		if (!Between(s->xmin, x, s->xmin + s->width - 1))	continue ;
		if (x < xmin) x = xmin ;
		if (x > xmax) x = xmax ;
		UpdateValue(s, x) ;
		UpdateSlider(s, x) ;
		return TRUE ;
		}

	return FALSE ;
	}

static void UpdateValue(SLIDER *s, uint32_t x)
	{
	float percent = (float) (x - s->xmin - SLIDER_SSIZE/2) / (s->width - SLIDER_SSIZE - 1) ;
	*s->pval = s->vmin + percent * (s->vmax - s->vmin) ;
	SetColor(COLOR_BLACK) ;
	PutStringAt(s->xmin, s->ymin - 12, "%s = %+5.1f", s->name, *s->pval) ;
	}

static void InitSliders(SLIDER sliders[], uint32_t count)
	{
	uint32_t which ;
	SLIDER *s ;

	s = sliders ;
	for (which = 0; which < count; which++, s++)
		{
		SetColor(COLOR_BLACK) ;
		PutStringAt(s->xmin, s->ymin - 12, "%s = %+5.1f", s->name, *s->pval) ;
		uint32_t ypos = s->ymin + (s->height - FONT_HEIGHT)/2 + 1 ;
		PutStringAt(s->xmin - SLIDER_LOFFSET, ypos, "%3d", (int) s->vmin) ;
		PutStringAt(s->xmin + s->width + SLIDER_ROFFSET, ypos, "+%d", (int) s->vmax) ;
		s->xpos = s->xmin + s->width * (*s->pval - s->vmin)/(s->vmax - s->vmin) ;
		SetColor(SLIDER_BGCLR) ;
		FillRect(s->xmin + 1, s->ymin, s->width - 1, s->height) ;
		SetColor(COLOR_RED) ;
		DrawRect(s->xmin, s->ymin, s->width, s->height) ;
		SetColor(SLIDER_FGCLR) ;
		FillRect(s->xpos - SLIDER_SSIZE/2 + 1, s->ymin + 1, SLIDER_SSIZE, s->height - 1) ;
		}
	}

static void UpdateSlider(SLIDER *s, uint32_t x)
	{
	SetColor(SLIDER_BGCLR) ;
	FillRect(s->xpos - SLIDER_SSIZE/2 + 1, s->ymin + 1, SLIDER_SSIZE, s->height - 1) ;
	s->xpos = x ;
	SetColor(SLIDER_FGCLR) ;
	FillRect(s->xpos - SLIDER_SSIZE/2 + 1, s->ymin + 1, SLIDER_SSIZE, s->height - 1) ;
	}

static int32_t Between(uint32_t min, uint32_t val, uint32_t max)
	{
	return (min <= val && val <= max) ;
	}

static void PlotQuadratic(COEF *coef, uint32_t color)
	{
	int thisCol, thisRow, prevCol, prevRow ;

	prevRow = 0 ;
	for (prevCol = thisCol = GFXCOL1; thisCol < GFXCOLN; thisCol++)
		{
		float percent = (float) (thisCol - GFXCOL1) / GFXCOLS ;
		float x = DOMAIN_MIN + percent * (DOMAIN_MAX - DOMAIN_MIN) ;
		float y = Quadratic(x, coef->a, coef->b, coef->c) ;
		float dRow, dErr, err ;

		if (!QuadOK(y, CorrectQuad(x, coef))) Error(coef, "Quad(%.2f) != %.2f", x, y) ;
		percent = (RANGE_MAX - y) / (RANGE_MAX - RANGE_MIN) ;
		thisRow = GFXROW1 + percent * GFXROWS + 0.5 ;
		if (prevRow == 0) prevRow = thisRow ;

		dRow = thisRow - prevRow ;
		dErr = fabs(dRow) ;
		err  = 0.0 ;
		do
			{
			if (GFXROW1 <= prevRow && prevRow < GFXROWN) DrawPixel(prevCol, prevRow, color) ;
			if ((err += dErr) < 0.5) continue ;
			prevRow = (dRow < 0.0) ? prevRow - 1 : prevRow + 1 ;
			err -= 1.0 ;
			} while (prevRow != thisRow) ;

		prevRow = thisRow ;
		prevCol = thisCol ;
		}
	}

static void PlotRoot(float x, uint32_t color)
	{
	float percent ;
	int col ;

	percent = (x - DOMAIN_MIN) / (DOMAIN_MAX - DOMAIN_MIN) ;
	col = percent * GFXCOLS + 0.5 ;
	if (col < ROOT_RAD || col > GFXCOLS - ROOT_RAD) return ;

	SetColor(color) ;
	FillCircle(col + GFXCOL1, AXISROW, ROOT_RAD) ;
	}

static void DrawXAxis(void)
	{
	int step, col ;

	SetColor(COLOR_AXIS) ;
	DrawLine(GFXCOL1, AXISROW, GFXCOLN, AXISROW) ;
	for (step = -3; step <= +3; step++)
		{
		if (step == 0) continue ;
		col = AXISCOL + TICKRATEX*step ;
		DrawVLine(col, AXISROW - TICKSIZE/2, TICKSIZE) ;
		PutStringAt(col - 12, AXISROW + 8, "%+d", 5*step) ;
		}
	}

static void DrawYAxis(void)
	{
	int step, row ;

	SetColor(COLOR_AXIS) ;
	DrawLine(AXISCOL, GFXROW1, AXISCOL, GFXROWN) ;
	for (step = -3; step <= +3; step++)
		{
		if (step == 0) continue ;
		row = AXISROW + TICKRATEY*step ;
		DrawHLine(AXISCOL - TICKSIZE/2, row, TICKSIZE) ;
		PutStringAt(AXISCOL + 6, row - 6, "%+d", -5*step) ;
		}
	}

static void LEDs(int grn_on, int red_on)
	{
	static uint32_t * const pGPIOG_MODER	= (uint32_t *) 0x40021800 ;
	static uint32_t * const pGPIOG_ODR		= (uint32_t *) 0x40021814 ;
	
	*pGPIOG_MODER |= (1 << 28) | (1 << 26) ;	// output mode
	*pGPIOG_ODR &= ~(3 << 13) ;			// both off
	*pGPIOG_ODR |= (grn_on ? 1 : 0) << 13 ;
	*pGPIOG_ODR |= (red_on ? 1 : 0) << 14 ;
	}

static float SquareRoot(float radical)
	{
	float sqrt, error ;
	uint32_t k ;

	if (radical == 0.0) return 0.0 ;
	sqrt = 1.0 ;
	for (k = 0; k < 100; k++)
		{
		error = fabs(sqrt*sqrt - radical) ;
		if (error <= 0.00001) break ;
		sqrt = (radical / sqrt + sqrt) / 2.0 ;
    	}

	return sqrt ;
	}

static void Error(COEF *coef, char *fmt, ...)
	{
	uint32_t width, row, col, chars ;
	char text[100] ;
	va_list args ;

	va_start(args, fmt) ;
	vsprintf(text, fmt, args) ;
	va_end(args) ;
	chars = strlen(text) ;
	if (chars < 25) chars = 25 ;
	width = FONT_WIDTH * (chars + 2) ;
	col = (XPIXELS - width) / 2 ;
	row = GFXROW1 + GFXROWS / 2 ;

	SetColor(COLOR_RED) ;
	FillRect(col + 1, row, width - 1, 5*FONT_HEIGHT) ;
	SetColor(COLOR_BLACK) ;
	DrawRect(col, row, width, 5*FONT_HEIGHT) ;
	row += FONT_HEIGHT/2 ;

	SetForeground(COLOR_WHITE) ;
	SetBackground(COLOR_RED) ;
	PutStringAt(col + FONT_WIDTH, row, "a = %10.6f (%08X)", coef->a, *((uint32_t *) &coef->a)) ;
	row += FONT_HEIGHT ;
	PutStringAt(col + FONT_WIDTH, row, "b = %10.6f (%08X)", coef->b, *((uint32_t *) &coef->b)) ;
	row += FONT_HEIGHT ; 
	PutStringAt(col + FONT_WIDTH, row, "c = %10.6f (%08X)", coef->c, *((uint32_t *) &coef->c)) ;
	row += FONT_HEIGHT ;
	DisplayStringAt(col + FONT_WIDTH, row, text) ;

	LEDs(0, 1) ;
	for (;;) ;
	}

static float CorrectDisc(COEF *coef)
	{
	return coef->b * coef->b - 4.0 * coef->a * coef->c ;
	}

static float CorrectRoot1(COEF *coef)
	{
	return (-coef->b + SquareRoot(CorrectDisc(coef)))/(2.0 * coef->a) ;
	}

static float CorrectRoot2(COEF *coef)
	{
	return (-coef->b - SquareRoot(CorrectDisc(coef)))/(2.0 * coef->a) ;
	}

static float CorrectQuad(float x, COEF *coef)
	{
	return (coef->a * x + coef->b) * x + coef->c ;
	}

static BOOL DiscOK(float theirs, float mine)
	{
	if ((*((uint32_t *) &theirs) & 0x7F800000) == 0x7F800000) return FALSE ;
	return fabs(theirs - mine) <= ACCURACY ;
	}

static BOOL QuadOK(float theirs, float mine)
	{
	if ((*((uint32_t *) &theirs) & 0x7F800000) == 0x7F800000) return FALSE ;
	if (mine < RANGE_MIN || RANGE_MAX < mine) return TRUE ;
	return fabs(theirs - mine) <= ACCURACY ;
	}

static BOOL RootOK(float theirs, float mine)
	{
	if ((*((uint32_t *) &theirs) & 0x7F800000) == 0x7F800000) return FALSE ;
	if (mine < DOMAIN_MIN || DOMAIN_MAX < mine) return TRUE ;
	return fabs(theirs - mine) <= ACCURACY ;
	}

