#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void display();
char label[10], opcode[10], operand[10];
char opcodeS[10], operand_S[3];



int main()
{

    int locctr, start, length;
    //1
    FILE *fp1, *fp2, *fp3, *fp4, *fp5;

    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("intermediate.txt", "w");
    fp5 = fopen("length.txt", "w");


    //2
    fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);

    //3
    if (strcmp(opcode, "START") == 0) {
        start = atoi(operand);
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%s\n", label, opcode, operand);
        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }
    else {
        locctr = 0;
    }


    //4
    while (strcmp(opcode, "END") != 0) {

//a
        fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);
//b
        if (strcmp(label, "**") != 0) {
            fprintf(fp3, "%s\t%d\n", label, locctr);
        }
//c
        fscanf(fp2, "%s\t%s", opcodeS, operand_S);

        while (strcmp(opcodeS, "END") != 0) { //for checking the optab
            if (strcmp(opcode, opcodeS) == 0) {
                locctr += 3;
                break;
            }
            //  fscanf(fp2, "%s\t%s", opcodeS, operand_S);
        }

//d
        if (strcmp(opcode, "WORD") == 0) {
            locctr += 3;
        }
        else if (strcmp(opcode, "RESW") == 0) {
            locctr += (3 * (atoi(operand)));
        }
        else if (strcmp(opcode, "BYTE") == 0) {
            int a=strlen(operand)-3;
            printf("%d",a);
            locctr+=a;
        }
        else if (strcmp(opcode, "RESB") == 0) {
            locctr += atoi(operand);
        }

        fscanf(fp1, "%s\t%s\t%s", label, opcode, operand);
    }



    //5
    fprintf(fp4, "%d\t%s\t%s\t%s\n", locctr, label, opcode, operand);



    fclose(fp4);
    fclose(fp3);
    fclose(fp2);
    fclose(fp1);


    //6
    length = locctr - start;
    fprintf(fp5, "%d", length);


    fclose(fp5);
    printf("\nThe length of the code : %d\n", length);
    return 0;
}



/*
input
**	START	2000
**	LDA	FIVE
**	STA	ALPHA
** 	LDCH 	CHARZ
** 	STCH 	C1
ALPHA 	RESW 	2
FIVE 	WORD 	5
CHARZ 	BYTE 	C'KlINCE'
C1 	RESB 	1
** 	END	**


intermediate
** 2000
2003 ** LDA FIVE
2006 ** STA ALPHA
2009 ** LDCH CHARZ
2012 ** STCH C1
2018 ALPHA RESW 2
2021 FIVE WORD 5
2027 CHARZ BYTE C'KlINCE'
2028 C1 RESB 1

LDA 03
STA	0f
LDCH	53
STCH	57
END	-




2012 ALPHA
2018 FIVE
2021 CHARZ
2027 C1



28



*/




