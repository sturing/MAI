/*
43. *Выяснить, в каком классе учится максимальное число учиниц
* Васильев 8О-103Б
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "person.h"

typedef struct _Key
{
	int klass;
	char bukva;
	int count;
} Key;

int main(int argc, char *argv[])
{
	Person p;
	int tmp=0;
	int count=0;
	Key key[100];
    Key max;
	FILE *file = NULL;	
	if (argc < 3)
	{
		printf("Использование: %s файл флаг\nФлаги:\n-f - печать базы данных\n-p - выполнить задание\n", argv[0]);

		return 1;
	}

	file = fopen(argv[1], "rb");

	if (file == NULL)
	{
		printf("Произошла ошибка при открытии файла\n");

		return 1;
	}

	if (!strcmp(argv[2], "-f"))
	{
		printf("╔════════════════╦══════════╦═══════╦═══════╦═══════╦═════════╦════════════════╦════════════════╗\n");
		printf("║    Фамилия     ║ Инициалы ║  Пол  ║ Класс ║ Буква ║   ВУЗ   ║     Работа     ║      Полк      ║\n");
		//printf("╟════════════════╬══════════╬═══════╬═══════╬═══════╬═════════╬════════════════╬════════════════╣\n");

		while (fread(&p, sizeof(p), 1, file) == 1)
		{
			printf("╟════════════════╬══════════╬═══════╬═══════╬═══════╬═════════╬════════════════╬════════════════╣\n");
			printf("║%16s║%10s║%7s║%7d║%7c║%9s║%16s║%16s║\n",
				p.fam,
				p.ini,
				p.pol == 'm' ? "Male" : "Female",
				p.klass,
				p.bukva,
				p.vuz,
				p.work,
				p.polk
			);
			
			//printf("╟════════════════╬══════════╬═══════╬═══════╬═══════╬═════════╬════════════════╬════════════════╣\n");
		}
		
			printf("╚════════════════╩══════════╩═══════╩═══════╩═══════╩═════════╩════════════════╩════════════════╝\n");
	}
	else if (!strcmp(argv[2], "-p"))
	{
		while (fread(&p, sizeof(p), 1, file) == 1)
		{
			if (p.pol=='f'){key[tmp].bukva=p.bukva;key[tmp].klass=p.klass;key[tmp].count=0;tmp++;}
			
		}
		//printf("%d\n",tmp);
		if (tmp!=0){
			fclose(file);	
			file = fopen(argv[1], "rb");
			count=0;			
			max=key[0];
			while (fread(&p, sizeof(p), 1, file) == 1)
				{
						if (p.pol=='f')
							{
							for(int i=0;i<tmp;++i)
									{
										if(key[i].klass==p.klass && key[i].bukva==p.bukva){key[i].count++;}
									}
							}					
				}	
			for(int i=1;i<tmp;++i)
				{
					if(key[i].count>max.count)
						{
							max=key[i];
						}
				}
		
			printf("Максимальное число число учениц: %d\n",max.count);
			printf("Класс с максимальным числом учениц: %d %c\n",max.klass,max.bukva);
	
					
		}
		else{printf("Не один класс не содержит девушек\n");}
		}
	fclose(file);
	return 0;
}
