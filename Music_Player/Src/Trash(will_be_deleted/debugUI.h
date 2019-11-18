#ifndef __DEBUGUI_H
#define	__DEBUGUI_H

#define	SIZE		15
#define	LENGTH		28 //max char in a line is LENGTH-1
#define	HEIGHT		20
typedef enum {
	off = 0, on
} OnOff;

void DebugUI_INIT(OnOff input);
void DebugUI_update(void);
void DebugUI_push(char *message);
void DebugUI_pushValue(int val);
void DebugUI_test(void);

#endif