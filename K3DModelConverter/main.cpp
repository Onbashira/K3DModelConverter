
#include <stdio.h>  /* printf */
#include <stdlib.h>  /* system */

#pragma

int main(int argc,char *argv[]) {

	if (argc >= 2) {
		printf("�t�@�C�����H��%s\n", argv[1]);
	}
	else {
		printf("�����Ȃ�\n");
	}

	/* Windows���璼�ڋN������ƈ�u�ŃR�}���h�v�����v�g������̂ő΍� */
	system("pause");

	return 0;

};