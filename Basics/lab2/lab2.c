/* Calculate ------->ln((1+x)/(1-x))/4 + arctan(x)/2 = x + x^5/5 + ....... + x^(4n+1)/(4n+1) + ... (-1<x<1)<------*/

#include <stdio.h>
#include <math.h>

int main()
{
	float x, eps, k1, k2, P;
	int i = 1; 
	
	printf("x = ");   scanf ("%f", &x);   // ������� � �������� x
    printf("eps = "); scanf ("%f", &eps); // ������� � �������� eps
    
    float a = x * x * x * x; 
    P = k1 = x;
    k2 = a * x / 5.0;
    
    while(fabs(k1 - k2) > eps){ 
    	
       	P += k2;                                    //��������� �����
    	k1 = k2; 
		i++;
		k2 = k1 * a * (float)(4 * (i - 1) + 1) / (float) (4 * i + 5);   //��������� ��������� ���� �� �����������
		
    }
    printf("����� = %f", P);                        //�������� �����
    return 0;
}
