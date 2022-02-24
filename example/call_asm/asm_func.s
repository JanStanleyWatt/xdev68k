	.cpu 68000
	.text
	.align	2
	.globl	_my_strlcpy


*------------------------------------------------------------------------------
*	strlcpy �݊��֐�
*
*	����
*		d0.l = ������R�s�[��̃������̈�̃T�C�Y
*		a0.l = ������R�s�[��
*		a1.l = ������R�s�[��
*
*	�o��
*		d0.l = �R�s�[��ɍ쐬�����݂�������̒����i�I�[ \0 �������j 
*			d0.l >= ���� d0.l �Ȃ�A������R�s�[��̃�����̈悪
*			�s�����Ă������Ƃ������B
*
*	�j��
*		d0 d1 d2
*		a0 a1
*------------------------------------------------------------------------------
_my_strlcpy:
							* d0.l = siz
							* a0.l = src
							* a1.l = dst

	move.l	a0,d1					* d1.l = src

	jbeq	_?L7
	add.l	d1,d0

_?L3:
	move.l	a0,d2
	addq.l	#1,a0
	cmp.l	a0,d0
	jbne	_?L5

	clr.b	(a1)
	move.l	d2,a0
	jbra	_?L7
_?L5:
	move.b	-1(a0),d2
	move.b	d2,(a1)+
	jbne	_?L3
_?L4:
	move.l	a0,d0
	sub.l	d1,d0
	subq.l	#1,d0
	rts

_?L7:
	tst.b	(a0)+
	jbne	_?L7
	jbra	_?L4
