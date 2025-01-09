#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char bitmask[12];

char bit[50]={0};

void convert(   char h[15]) {
    const char  bitmap[16][5]={

        "0000", "0001", "0010", "0011",
                "0100", "0101", "0110", "0111",
                "1000", "1001", "1010", "1011",
                "1100", "1101", "1110", "1111"
        };

    bit[0]='\0';


    for (int i=0;   h[i]!='\0';i++)
    {
        int v =  (h[i]<=	'9'  )  ?   h[i] - '0'  :  h[i]- 'A' +10;
        strcat(	bit,    bitmap[v]);


    }
}
void  main()
{
    int start =4000	;
    int address,   opcode,	tlen;
    int actaddr;
char  input[10], relocbit  ,   add,   pn[10],     length[10];
    char buff[100][30];
    int lc=0;

    printf("enter starting address");
   // scanf("%x", &start);
    FILE *fp1,	*fp2;


    fp1= fopen("RLIN.txt"  ,  "r");
    fp2= fopen( "RLOUT.txt "  ,  "w");


    fscanf(  fp1,  "%s", input    );

    fprintf(fp2, "ADDRESS\t\tCONTENT\n\n");


    while(   fscanf( fp1, "%s",   input)  != EOF  )
    {

        if (strcmp(input,"E")==0)
        {
            break;
        }

        if (  strcmp(input , "H")==0       )
        {

            fscanf( fp1,	"%s",  pn	   );
            fscanf( fp1,	"%s",  add	   );
            fscanf( fp1,	"%s",  length	   );

            continue;
        }

        if ( strcmp(	input, "T")	==0)
        {
            fscanf(  fp1, "%x",  &address  );
            fscanf(  fp1, "%x",  &tlen  );
            fscanf(  fp1, "%s",  bitmask );

            address+=start;
            convert(bitmask);

            int len=  strlen(bit );

            for (int i=0 ;	i<len;	i++)
            {
                fscanf(	fp1,  "%d",  &opcode);
                fscanf(	fp1,  "%d",  &actaddr);
                relocbit=bit[i];
                actaddr=   (relocbit=='0')? actaddr:	actaddr+start;

                sprintf( buff[lc++], 	 " %04d\t%02X\t%04x\n", address,opcode,actaddr);

                address+=3;
            }

        }

    }

    for ( int i=0; i<lc-4;  i++)
    {
        fputs(    buff[i],    fp2);
    }
    fclose(fp1);
    fclose(fp2);

}
