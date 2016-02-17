
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

Key findmax(char *argv,int count){
    FILE *file=NULL;
    Key max;
    Person p;
    int i=0;
    Key girls[count];
    file = fopen(argv, "rb");
    while (fread(&p, sizeof(p), 1, file) == 1)
    {
        if (p.pol=='f'){
            girls[i].klass=p.klass; girls[i].bukva=p.bukva;girls[i].count=0;i++;
        }
    }
    fclose(file);
    file = fopen(argv, "rb");
    while (fread(&p, sizeof(p), 1, file) == 1)
    {
        if (p.pol=='f'){
            for(i=0;i<count;++i){
                if(girls[i].klass==p.klass && girls[i].bukva==p.bukva){girls[i].count++;}
            }
        }
    }
    max=girls[0];
    for(i=0;i<count;++i){
        if(girls[i].count>max.count){
            max=girls[i];
        }
    }
    
    fclose(file);
    return max;
}
int main(int argc, char *argv[])
{
    Person p;
    int tmp=0;
    Key max;
    FILE *file = NULL;
    if (argc < 3)
    {
        printf("Использование: %s файл флагnФлаги:n-f - печать базы данныхn-p - выполнить заданиеn", argv[0]);
        
        return 1;
    }
    
    file = fopen(argv[1], "rb");
    
    if (file == NULL)
    {
        printf("Произошла ошибка при открытии файлаn");
        
        return 1;
    }
    
    if (!strcmp(argv[2], "-f"))
    {
        printf("╔════════════════╦══════════╦═══════╦═══════╦═══════╦═════════╦════════════════╦════════════════╗n");
        printf("║    Фамилия     ║ Инициалы ║  Пол  ║ Класс ║ Буква ║   ВУЗ   ║     Работа     ║      Полк      ║n");
        
        while (fread(&p, sizeof(p), 1, file) == 1)
        {
            printf("╟════════════════╬══════════╬═══════╬═══════╬═══════╬═════════╬════════════════╬════════════════╣n");
            printf("║%16s║%10s║%7s║%7d║%7c║%9s║%16s║%16s║n",
            p.fam,
            p.ini,
            p.pol == 'm' ? "Male" : "Female",
            p.klass,
            p.bukva,
            p.vuz,
            p.work,
            p.polk
        );    }
        
        printf("╚════════════════╩══════════╩═══════╩═══════╩═══════╩═════════╩════════════════╩════════════════╝n");
    }
    else if (!strcmp(argv[2], "-p"))
    {
        while (fread(&p, sizeof(p), 1, file) == 1)
        {
            if (p.pol=='f'){tmp++;}
            
        }
        fclose(file);
        
        if (tmp!=0){
            max=findmax(argv[1],tmp);
            printf("Максимальное число число учениц: %dn",max.count);
            printf("Класс с максимальным числом учениц: %d %cn",max.klass,max.bukva);
            
        }
        else{printf("Не один класс не содержит девушекn");}
    }
    return 0;
}
