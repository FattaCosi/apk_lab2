#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include <iostream>


#define SIZE_OF_ARRAY 32

int main()
{
	short int arrayFirst[SIZE_OF_ARRAY], arraySecond[SIZE_OF_ARRAY]; 
	short int resultArray[SIZE_OF_ARRAY];
	srand(NULL);
	for (int i = 0; i < SIZE_OF_ARRAY; i++)
	{
		arrayFirst[i] = rand() % 2;
		arraySecond[i] = rand() % 2;
	}
	
	double start, end, t;
	double begin, limit, step;
	std::cout << "Enter begin: " << std::endl;
	std::cin >> begin;
	std::cout << "Enter limit: " << std::endl;
	std::cin >> limit;
	std::cout << "Enter step: " << std::endl;
	std::cin >> step;
	start = clock();
	for (double k = begin; k < limit; k += step)
	{
		for (int i = 0; i < SIZE_OF_ARRAY; i++)
		{
			resultArray[i] = arrayFirst[i] | arraySecond[i];
		}
	}
	end = clock();
	for (int i = 0; i < SIZE_OF_ARRAY; i++)
	{
		std::cout << arrayFirst[i] << " ";
	}
	std::cout << "\n";
	for (int i = 0; i < SIZE_OF_ARRAY; i++)
	{
		std::cout << arraySecond[i] << " ";
	}
	std::cout << "\n\n";
	for (int i = 0; i < SIZE_OF_ARRAY; i++)
	{
		std::cout << resultArray[i] << " ";
	}
	std::cout << " " << std::endl;
	t = (end - start);
	printf("C time %f seconds\n", t / 1000);


	/////////////////////////////////////////


	start = clock();
	for (double k = begin; k < limit; k += step)
	{
		_asm {
			pusha

			xor esi, esi
			xor ecx, ecx

			mov ecx, 16

			cycle: 

			mov ax, arrayFirst[esi]
			mov bx, arraySecond[esi]

			first: 
			or al, bl
			mov dl, al
				
			second: 
			or ah, bh
			mov dh, ah

			write_result:
			mov resultArray[esi], dx

			add esi, 2

			loop cycle

					popa
		}
	}
	end = clock();
	for (int i = 0; i < SIZE_OF_ARRAY; i++)
	{
		std::cout << resultArray[i] << " ";
	}
	std::cout << " " << std::endl;
	t = (end - start);
	printf("ASM time %f seconds\n", t / 1000);


	////////////////////////////////////

	start = clock();
	for (double k = begin; k < limit; k += step)
	{
		_asm {

			xor esi, esi
			xor ecx, ecx

			mov ecx, 8

			arr_cycle:

			movq MM0, arrayFirst[esi]
			movq MM1, arraySecond[esi]

			por MM0, MM1

			movq resultArray[esi], MM0

			add esi, 4
			loop arr_cycle

			emms
		}
	}
	end = clock();
	for (int i = 0; i < SIZE_OF_ARRAY; i++)
	{
		std::cout << resultArray[i] << " ";
	}
	std::cout << " " << std::endl;
	t = (end - start);
	printf("MMX time %f seconds\n", t / 1000);
	





	system("Pause");
}