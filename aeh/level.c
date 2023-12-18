#include "level.h"

void readLevelFile(char* _c, float* _buf) {
	FILE* f = fopen(_c, "r");
	if (f == NULL) return;

	fread(_buf, sizeof(char), 16 * 8, f);
	fclose(f);
}