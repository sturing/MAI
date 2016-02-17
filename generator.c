#include <stdio.h>
#include "person.h"

int readPerson(Person *p);

int main(int argc, char *argv[])
{
	Person p; // запись, обрабатываемая на данный момент
	FILE *file = NULL; // файл с базой данных
	
	if (argc != 2) // рекомендации по использованию аргументов
	{
		printf("Использование: %s [файл]\n", argv[0]);

		return 1;
	}
	file = fopen(argv[1], "wb");

	if (file == NULL)// проверка существования файла
	{
		printf("Произошла ошибка при открытии файла\n");

		return 1;
	}

	while (readPerson(&p))
		fwrite(&p, sizeof(p), 1, file);

	fclose(file);

	return 0;
}

int readPerson(Person *p)
{
	int ret = scanf("%s %s %c %d %c %s %s %s",
		p->fam,
		p->ini,
		&p->pol,
		&p->klass,
		&p->bukva,
		p->vuz,
		p->work,
		p->polk
	);
	
	return (ret == 8);
}
