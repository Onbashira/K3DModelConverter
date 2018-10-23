
#include <stdio.h>  /* printf */
#include <stdlib.h>  /* system */

#pragma

int main(int argc,char *argv[]) {

	if (argc >= 2) {
		printf("ファイル名？＝%s\n", argv[1]);
	}
	else {
		printf("引数なし\n");
	}

	/* Windowsから直接起動すると一瞬でコマンドプロンプトが閉じるので対策 */
	system("pause");

	return 0;

};