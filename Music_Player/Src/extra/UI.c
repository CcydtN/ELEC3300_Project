#include <DIR.h>
#include "UI.h"
#include "lcd.h"
#include "string.h"
#include "Trace.h"

extern char path[512];
extern char currentList[20][_MAX_LFN];
unsigned int cursor, pageStart, pageEnd;

void UI_INIT(void) {
	LCD_INIT();
	cursor = 0;
	pageStart = 0;
	pageEnd = 13;
	for (int i = 0; i < 17; ++i) {
		LCD_OpenWindow(8, 8 + 18 * i, 224, 16);
	}
	LCD_DrawBox(8, 8, 224, 16, RED, CYAN);   //1st song  ARR[0]
	LCD_DrawBox(8, 26, 224, 16, RED, CYAN);  //2nd song  ARR[1]
	LCD_DrawBox(8, 44, 224, 16, RED, CYAN);  //3rd song  ARR[2]
	LCD_DrawBox(8, 62, 224, 16, RED, CYAN);  //4th song  ARR[3]
	LCD_DrawBox(8, 80, 224, 16, RED, CYAN);  //5th song  ARR[4]
	LCD_DrawBox(8, 98, 224, 16, RED, CYAN);  //6th song  ARR[5]
	LCD_DrawBox(8, 116, 224, 16, RED, CYAN); //7th song  ARR[6]
	LCD_DrawBox(8, 134, 224, 16, RED, CYAN); //8th song  ARR[7]
	LCD_DrawBox(8, 152, 224, 16, RED, CYAN); //9th song  ARR[8]
	LCD_DrawBox(8, 170, 224, 16, RED, CYAN); //10th song ARR[9]
	LCD_DrawBox(8, 188, 224, 16, RED, CYAN); //11th song ARR[10]
	LCD_DrawBox(8, 206, 224, 16, RED, CYAN); //12th song ARR[11]
	LCD_DrawBox(8, 224, 224, 16, RED, CYAN); //13th song ARR[12]
	//LCD_DrawBox(8, 242, 224, 16, RED, CYAN); //14th song ARR[13]

	LCD_DrawLine(19, 262, 19, 273, BLACK);
	LCD_DrawLine(221, 262, 221, 273, BLACK);
	LCD_DrawLine(20, 267, 220, 267, BLACK);
	LCD_DrawLine(20, 268, 220, 268, BLACK);
	const unsigned char icon[2][32] = { { 0xff, 0xff, 0xff, 0xff, 0xf3, 0xef,
			0xf3, 0xcf, 0xf3, 0x8f, 0xf3, 0x0f, 0xf2, 0x0f, 0xf0, 0x0f, 0xf0,
			0x0f, 0xf2, 0x0f, 0xf3, 0x0f, 0xf3, 0x8f, 0xf3, 0xcf, 0xf3, 0xef,
			0xff, 0xff, 0xff, 0xff },

	{ 0xff, 0xff, 0xff, 0xff, 0xe7, 0x7f, 0xe7, 0x3f, 0xe7, 0x1f, 0xe7, 0x0f,
			0xe7, 0x07, 0xe7, 0x03, 0xe7, 0x03, 0xe7, 0x07, 0xe7, 0x0f, 0xe7,
			0x1f, 0xe7, 0x3f, 0xe7, 0x7f, 0xff, 0xff, 0xff, 0xff } };

	uint8_t ucTemp, ucPage, ucColumn;

	for (int i = 0; i < 2; ++i) {
		LCD_OpenWindow(50 * i + 62, 296, 16, 16);
		LCD_Write_Cmd( CMD_SetPixel);

		for (ucPage = 0; ucPage < 32; ucPage++) {
			ucTemp = icon[i][ucPage];
			for (ucColumn = 0; ucColumn < 8; ucColumn++) {
				if (ucTemp & 0x80)
					LCD_Write_Data(0xFFFF);
				else
					LCD_Write_Data(0x001F);
				ucTemp <<= 1;

			}
		}
	}
	LCD_OpenWindow(162, 296, 16, 16);
	LCD_Write_Cmd( CMD_SetPixel);
	for (ucPage = 0; ucPage < 32; ucPage++) {
		ucTemp = icon[0][ucPage];
		for (ucColumn = 0; ucColumn < 8; ucColumn++) {
			if (ucTemp & 0x01)
				LCD_Write_Data(0xFFFF);
			else
				LCD_Write_Data(0x001F);
			ucTemp >>= 1;

		}
	}

//	trace_printf("WTF\n");
}

void cursorUP(void) {
	if (cursor != 0) {
		cursor--;
		if ((2 * cursor < pageStart + pageEnd) && (pageStart != 0)) {
			pageStart--;
			pageEnd--;
		}
	}
}

void cursorDown(void) {
	if (cursor != 20) {
		cursor++;
		if ((2 * cursor > pageStart + pageEnd) && (pageEnd != 20)) {
			pageStart--;
			pageEnd--;
		}
	}
}
