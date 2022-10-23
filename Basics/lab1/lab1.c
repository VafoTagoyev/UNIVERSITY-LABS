/*************Даны целые положительные числа k и N. Найти P=(K)^(n!)**************
*********Определить диапазон допустимых значений N для целого типа данных.*********/

#include <stdio.h>
#include <math.h>
#include <limits.h>

int main() {

    int k;                 //k  ����� ����� => ���� int
    unsigned int n;

    printf ("k = "); scanf ("%d", &k);  // ������� k
    printf ("n = "); scanf ("%d", &n);  // ������� n

	int i, j, s = 1, prevS = s, P = 1, a = 1;
	for (i = 1; i <= n; i++) {                   //"i" �� 1 �� n
		s *= i;                                 //��������� "n!"
		for (j = prevS; j <= s; j++) {
			P *= k;			     			   //��������� "P=(k)^n!"
			if(P <= 0 || P > INT_MAX) {
				printf("�������� ���������� �������� n = [1, %d]", i - 1);
				a = 0;
				break;
			}
		}
		if(a == 0) {
		break;
		}
		prevS = s + 1;
	}

	if(a == 1){
		printf ("P = %d", P);                  // �������� P ���� ������ �������� �������
	}

	return 0;                                  //��������� ��������
}
