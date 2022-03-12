/*
	�C�����C���A�Z���u���R�[�h��ŁA�}�N���֐��𗘗p���܂��B

	[���]
		�}�N���֐��𗘗p�����������܂��B

		HAS �̃}�N���ɂ́A�l�X�ȍ��x�ȋL�q�e�N�j�b�N�����݂��܂����A
		x68k_gas2has.pl �͂����̑�����F�����邱�Ƃ��ł��܂���B
		���̐����ɂ��A�C�����C���A�Z���u���R�[�h��ŗ��p�\��
		�}�N���\���́A���̃T���v���R�[�h�Ŏ������x�̒P���Ȃ��̂�
		�����܂��B
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	/*
		.macro
	*/
	{
		static int resultA = 0;
		asm volatile (
			/*
				�}�N����`�s�́A�C���f���g�����ōs������J�n���Ȃ���΂Ȃ�Ȃ��B
				inline asm �R�[�h�̓C���f���g���ꂽ��Ԃő}������邽�߁A
				inline asm �u���b�N���̍ŏ��̍s�̓}�N����`�s�ɂȂ�Ȃ��B
				�ŏ��̍s��j�����邽�߁A��̉��s���s���B
			*/
			"\n"

			/*
				�ȍ~�̓}�N����`�s�ɂȂ��B
			*/
			"MY_ADD_L	.macro	reg1,reg2,reg3\n"
			"	move.l	reg1,reg3\n"
			"	add.l	reg2,reg3\n"
			"	.endm\n"
			"\n"
			"	move.l		#1,d1\n"
			"	move.l		#2,d2\n"
			"	MY_ADD_L	d1,d2,d0\n"
			"	move.l		d0,%0\n"

		:	/* �o�� */	"=irm"	(resultA)
		:	/* ���� */
		:	/* �j�� */	"d0","d1","d2"
		);

		printf("result = %d (expected = 3)\n", resultA);
	}

	/*
		.rept
	*/
	{
		static char s_string[] = ".rept test";
		asm volatile (
			"\n"
			"	.rept	3\n"
			"	move.l	%0,-(sp)\n"
			"	jbsr	_puts\n"			/* �O���V���{�����Q�Ƃ��鎞�� _ ��t���� */
			"	addq.l	#4,sp\n"
			"	.endm\n"

		:	/* �o�� */
		:	/* ���� */	"irm" (&s_string)	/* ���� %0 */
		:	/* �j�� */	"d0", "d1", "d2", "a0", "a1", "a2"	/* C �֐��� d0-d2/a0-a2 ��j�󂷂� */
		);
	}

	/*
		.irp
	*/
	{
		asm volatile (
			"\n"
			"	.irp	arg,string0,string1,string2\n"
			"	move.l	#arg,-(sp)\n"
			"	jbsr	_puts\n"			/* �O���V���{�����Q�Ƃ��鎞�� _ ��t���� */
			"	addq.l	#4,sp\n"
			"	.endm\n"

			"			.data\n"
			"string0:	.dc.b $30,0	\n"
			"string1:	.dc.b $31,0	\n"
			"string2:	.dc.b $32,0	\n"

			"			.text\n"

		:	/* �o�� */
		:	/* ���� */
		:	/* �j�� */	"d0", "d1", "d2", "a0", "a1", "a2"	/* C �֐��� d0-d2/a0-a2 ��j�󂷂� */
		);
	}

	return 0;
}
