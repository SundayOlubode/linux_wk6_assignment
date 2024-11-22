#include <stdio.h>
#include <stdlib.h>

int add(int a, int b)
{
	return a + b;
}

int subtract(int a, int b)
{
	return a - b;
}

int multiply(int a, int b)
{
	return a * b;
}

float divide(int a, int b)
{
	if (b == 0)
	{
		printf("Division by zero!\n");
		exit(1);
	}
	return (float)a / b;
}

int atoi_custom(char *str)
{
	int result = 0;
	while (*str)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return result;
}

void fpu_to_str(float num)
{
	int int_part = (int)num;
	printf("%d", int_part);
}

int main()
{
	char operator;
	int num1, num2;
	float result;

	printf("Enter first number: ");
	scanf("%d", &num1);

	printf("Enter operator (+, -, *, /): ");
	scanf(" %c", &operator);

	printf("Enter second number: ");
	scanf("%d", &num2);

	switch (operator)
	{
	case '+':
		result = add(num1, num2);
		break;
	case '-':
		result = subtract(num1, num2);
		break;
	case '*':
		result = multiply(num1, num2);
		break;
	case '/':
		result = divide(num1, num2);
		break;
	default:
		printf("Invalid operator!\n");
		exit(1);
	}

	printf("Result: ");
	fpu_to_str(result);
	printf("\n");

	return 0;
}
