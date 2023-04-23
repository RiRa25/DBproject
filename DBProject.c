#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void opendbfile();
void printinitialwrites();
void printstructdetails();
void printswitchcase();
void printcasecreate();
void printcaseread();
void printcaseupdate();
void printcasedelete();
void printcaseexit();
void closedbfile();
void compileprogram();

FILE *fp;

struct db_details
{
    char fieldname[20];
    int datatype;
};
struct db_details db[10];
char dbname[50], dbnameshort[10];
int num_of_fields = 0;
char dbnamefile[50];

int main()
{
    opendbfile();
    printinitialwrites();
    printstructdetails();
    printswitchcase();
    printcasecreate();
    printcaseread();
    printcaseupdate();
    printcasedelete();
    printcaseexit();
    closedbfile();
    compileprogram();
}

void opendbfile()
{
    printf("***********************************************************************************************************************************************************\n");
    printf("\t\t\t\t SisCode Database Utility - Created by Gang of 4 - Richa, Saee, Unnati and Shrawani - FY ENTC\n");
    printf("***********************************************************************************************************************************************************\n\n\n");
    printf("\t\tEnter the name of the Database you want to create : ");
    scanf("%s", dbname);
    printf("\n");
    strcpy(dbnamefile, dbname);
    strcat(dbnamefile, ".c");

    fp = fopen(dbnamefile, "w");
}

void printinitialwrites()
{
    fprintf(fp, "#include <stdio.h>\n");
    fprintf(fp, "#include <stdlib.h>\n");
    fprintf(fp, "int main()\n{\n\n");
    fprintf(fp, "int choice;\n");
    fprintf(fp, "FILE *fp;\n");
    fprintf(fp, "char ch;\n");
    fprintf(fp, "struct %s {\n", dbname);
}

void printstructdetails()
{
    char fieldname[50];
    int datatype;

    while(1)
    {
        printf("\t\tEnter the name of field (type exit if done) : ");
        scanf("%s", fieldname);

        if (strcmp(fieldname, "exit") == 0)
        {
            break;
        }

        printf("\t\tEnter the datatype [1 Integer, 2 String, 3 Decimal] : ");
        scanf("%d", &datatype);

        printf("\n");
        switch(datatype)
        {
            case 1:
            {
                fprintf(fp, "int %s;\n", fieldname);
                break;
            }

            case 2:
            {
                fprintf(fp, "char %s[50];\n", fieldname);
                break;
            }

            case 3:
            {
                fprintf(fp, "float %s;\n", fieldname);
                break;
            }
        }
        db[num_of_fields].datatype = datatype;
        strcpy(db[num_of_fields].fieldname, fieldname);
        num_of_fields++;
    }
    fprintf(fp, "};\n");
    strncpy(dbnameshort, dbname, 3);
    fprintf(fp, "struct %s %s;\n", dbname, dbnameshort);
    fprintf(fp, "fp = fopen(\"%s.csv\", \"a+\");\n", dbname);
    fprintf(fp, "printf(\"\\n\\t\\t %s Database\\n\");\n", dbname);
}

void printswitchcase()
{
    int i;
    fprintf(fp, "while(1)\n{\n");
    fprintf(fp, "printf(\"\\n\\tMenu - \\n\");\n");
    fprintf(fp, "printf(\"\\t1. Create new %s record\\n\");\n", dbname);
    fprintf(fp, "printf(\"\\t2. Read existing %s record\\n\");\n", dbname);
    fprintf(fp, "printf(\"\\t0. To end the program\\n\");\n");
    fprintf(fp, "printf(\"\\tEnter your choice : \");\n");
    fprintf(fp, "scanf(\"%%d\", &choice);\n\n");
    fprintf(fp, "printf(\"\\n\");\n");
    fprintf(fp, "switch(choice)\n{\n");
}

void printcasecreate()
{
    int i;
    fprintf(fp, "case 1: \n");
    for(i=0; i<num_of_fields; i++)
    {
        fprintf(fp, "printf(\"Enter %s : \");\n", db[i].fieldname);

        if(db[i].datatype == 1)
        {
            fprintf(fp, "scanf(\"%%d\", &%s.%s);\n",dbnameshort, db[i].fieldname);
        }
        if(db[i].datatype == 2)
        {
            fprintf(fp, "scanf(\"%%s\", %s.%s);\n",dbnameshort, db[i].fieldname);
        }
        if(db[i].datatype == 3)
        {
            fprintf(fp, "scanf(\"%%f\", &%s.%s);\n",dbnameshort, db[i].fieldname);
        }
    }

    fprintf(fp, "fprintf(fp,\"");

    if(db[0].datatype == 1)
    {
        fprintf(fp, "%%d");
    }
    if(db[0].datatype == 2)
    {
        fprintf(fp, "%%s");
    }
    if(db[0].datatype == 3)
    {
        fprintf(fp, "%%f");
    }

    for(i=1; i<num_of_fields; i++)
    {
        if(db[i].datatype == 1)
        {
            fprintf(fp, " , %%d");
        }
        if(db[i].datatype == 2)
        {
            fprintf(fp, " , %%s");
        }
        if(db[i].datatype == 3)
        {
            fprintf(fp, " , %%f");
        }
    }
    fprintf(fp, "\\n\",");
    for(i=0; i<num_of_fields - 1; i++)
    {
        fprintf(fp,"%s.%s, ", dbnameshort, db[i].fieldname);
    }
    fprintf(fp,"%s.%s);\n", dbnameshort, db[num_of_fields - 1].fieldname);
    fprintf(fp, "break;\n\n");
}

void printcaseread()
{
    int i;
    fprintf(fp, "case 2: \n");
    fprintf(fp, "fseek(fp, 0, SEEK_SET);\n");
    fprintf(fp, "while(1) \n{\n");
    fprintf(fp, "fscanf(fp,\"");

    if(db[0].datatype == 1)
    {
        fprintf(fp, "%%d");
    }
    if(db[0].datatype == 2)
    {
        fprintf(fp, "%%s");
    }
    if(db[0].datatype == 3)
    {
        fprintf(fp, "%%f");
    }

    for(i=1; i<num_of_fields; i++)
    {
        if(db[i].datatype == 1)
        {
            fprintf(fp, " %%c %%d");
        }
        if(db[i].datatype == 2)
        {
            fprintf(fp, " %%c %%s");
        }
        if(db[i].datatype == 3)
        {
            fprintf(fp, " %%c %%f");
        }
    }
    fprintf(fp, "\"");
    fprintf(fp, ",&%s.%s", dbnameshort, db[0].fieldname);
    for(i=1; i<num_of_fields; i++)
    {
        fprintf(fp,", &ch, &%s.%s ", dbnameshort, db[i].fieldname);
    }
    fprintf(fp, ");\n");
    fprintf(fp, "if(feof(fp))\n{\n");
    fprintf(fp, "break;\n}\n");

    fprintf(fp, "printf(\"");
    for(i=0; i<num_of_fields - 1; i++)
    {
        if(db[i].datatype == 1)
        {
            fprintf(fp, "%%d, ");
        }
        if(db[i].datatype == 2)
        {
            fprintf(fp, "%%s, ");
        }
        if(db[i].datatype == 3)
        {
            fprintf(fp, "%%f, ");
        }
    }
    if(db[num_of_fields - 1].datatype == 1)
    {
        fprintf(fp, "%%d \\n\"");
    }
    if(db[num_of_fields - 1].datatype == 2)
    {
        fprintf(fp, "%%s \\n\"");
    }
    if(db[num_of_fields - 1].datatype == 3)
    {
        fprintf(fp, "%%f \\n\"");
    }

    for(i=0; i<num_of_fields; i++)
    {
        fprintf(fp,", %s.%s", dbnameshort, db[i].fieldname);
    }
    fprintf(fp, ");\n}\n");
    fprintf(fp, "getchar();\n");
    fprintf(fp, "getchar();\n");
    fprintf(fp, "break;\n\n");

}

void printcaseupdate()
{
    int i;
    fprintf(fp, "case 3: \n");
    fprintf(fp, "break;\n\n");
}

void printcasedelete()
{
    int i;
    fprintf(fp, "case 4: \n");
    fprintf(fp, "break;\n\n");
}

void printcaseexit()
{
    fprintf(fp, "case 0:\n");
    fprintf(fp, "fclose(fp);\n");
    fprintf(fp, "exit(0);\n");
    fprintf(fp, "}\n}\n}\n");
}

void closedbfile()
{
    fclose(fp);
}

void compileprogram()
{
    char command[100];
    strcpy(command, "C:\\MinGW\\bin\\gcc ");
    strcat(command, dbnamefile);
    strcat(command, " -o ");
    strcat(command, dbname);
    strcat(command, ".exe");

    printf("\n\n\t\tYour %s database is ready to use !\n\n", dbname);
    system(command);
}
