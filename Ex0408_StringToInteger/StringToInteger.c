#include <stdio.h>

int my_atoi(const char s[], size_t length)
{
	int rslt = 0;
	int sign = 1;
	int i = 0;
	while (s[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (i < (int)length && s[i] >= '0' && s[i] <= '9')
	{
		rslt *= 10;
		rslt += s[i] - '0';
		i++;
	}
	return rslt * sign;
}

int main(void)
{
	char s[] = "-1231904";
	printf("Origin string: %s\n", s);
	int num = my_atoi(s, sizeof(s)/sizeof(s[0]));
	printf("Translated integer: %d\n", num);
	return 0;
}
