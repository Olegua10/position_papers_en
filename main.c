//setlocale(En)
//changing are letters in the surnames
//(ld-->Sheld/Held; nt-->Shent/Hent;ll-->Shell/Hell;)woman/man
//processing in the primary data table

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 20//array sur/names(line)
#define M 20//array sur/names(column)

#define DN 20//array data/res_table(line)
#define DM 4 //array data/res_table(column)

void readFiles_sur(char [][M]);
void readFiles_mames(char[][M]);
void fixSex(int [][DM]);
void changeSur(char [][M],int [][DM]);
void print_sur(char [][M]);
void print_names(char [][M]);
void fixName(int [][DM]);
void print_data(int [][DM]);
void fixAge(int [][DM]);
int fixRange(int,int);
int filterAppl(int [][DM],int,int,int *);
void print_matrix_data(int [][DM]);
float midAge(int [][DM],int);


main()
{
    int min,max;//age generation range
    int c_i=0;//-<flag>-counter iteration(filterAppl)
    float middleAge_w;//women
    float middleAge_m;//men
    int v_w=1;//1->women
    int v_m=0;//0->men

   char sur[N][M];//list of surnames
   char names[N][M];//list of names

   int data[DN][DM];//primary data table


readFiles_sur(sur);//-<-copy->-filling the data array"sur" from a file "sur_en"
readFiles_mames(names);//-<-copy->-filling the data array"names" from a file "names_en"

//---print before endings replacement---
print_sur(sur);
print_names(names);
//--------------------------------------
fixSex(data);//Random 0 or 1 to array"data" for sex determination
changeSur(sur,data);//changing are letters in the surnames
                    //(ld-->Sheld/Held; nt-->Shent/Hent;ll-->Shell/Hell;)woman/man
                    //respective a particular gender(array"data")

//---print after endings replacement----
print_sur(sur);
//--------------------------------------

fixName(data);//name selection
fixAge(data);//age people

min=fixRange(18,25);//--magic(18..25)->generation range(Age min/max)
max=fixRange(45,60);//--magic(45..60)->generation range(Age min/max)

//---way to call function  to  conformity with a condition-----
//---------------------<filterAppl>----------------------------
for(int i=0;i<N;i++)
   {//1 or 0(appropriate/inappropriate)
    data[i][3]=filterAppl(data,min,max,&c_i);;
    c_i++;
   }//is writing to in column 3 array "data"

printf("min=%i",min);
printf("max=%i",max);
printf("\n");
//--------------------------------------
print_matrix_data(data);

middleAge_w=midAge(data,v_w);//for women
middleAge_m=midAge(data,v_m);//for men
//--------------------------------------
printf("middleAge women=%3.1f\n",middleAge_w);
printf("middleAge men=%3.1f\n",middleAge_m);
//--------------------------------------

}

//-----------------------------------------
void readFiles_sur(char sur[][M])
{
    FILE* s;
    int i;
    s = fopen("F:/material/c_/tests/intermediary_tests/test_file/sur_en.txt","r");
    //opening for reading

    if (s == NULL)//if not
    {
     printf("A file with that name missing");
         getchar();
         return;
    }
//-<-copy->-filling the data array"sur" from a file "sur_en"
    for(i=0;i<N;i++)
        //if ((EOF)==fgets(sur[i],M-1,s))break;
        if (('\n'&&'\0')==fscanf(s,"%s",sur[i]))break;
//----
    fclose(s);
}
//-----------------------------------------
void readFiles_mames(char names[][M])
{
    FILE* n;
    int i;
    n = fopen("F:/material/c_/tests/intermediary_tests/test_file/names_en.txt","r");
    //opening for reading

    if (n == NULL)//if not
    {
     printf("A file with that name missing");
         getchar();
         return;
    }
//--<-copy->---filling the data array"names" from a file "names_en"
    for(i=0;i<N;i++)
        if (('\n'&&'\0')==fscanf(n,"%s",names[i]))break;//to array
            //if ((EOF)==fgets(sur[i],M-1,s))break;
//-----------
    fclose(n);
}
//-----------------------------------------
void fixSex(int data[][DM])
{
//Random 0 or 1 to array
        for(int i=0;i<DN;i++)
        {
            data[i][0]=rand() %2;
        }
}

void changeSur(char sur[][M],int data[][DM])
{
    int L=0;//length of string

    //------------to replace that in the case of female name
    char *woman_ld={"Sheld"};char *woman_nt={"Shent"};char *woman_ll={"Shell"};

    //----------to replace that in the case of male name
    char *man_ld={"Held"};char *man_nt={"Hent"};char *man_ll={"Hell"};

    //----------temporary array to copy
    char new_m[N][M]={0};

    //in the case of modification symbol
     char *d={"d"}; char *n={"n"}; char *t={"t"}; char *l={"l"};


    for(int i=0;i<N;i++)//algorithm for training purposes
    {
        L = strlen(sur[i]);//length of string

        if (data[i][0]==1)// if female name
        {
       if( (sur[i][L-2]==*l)  && (sur[i][L-1]==*d) )//determining coincidence symbols(...-2,-1 from length)
        {strncpy(new_m[i],sur[i],L-2);//delete two symbol and copy residual intemporary array
        strcat(new_m[i],woman_ld);//merger
        strcpy(sur[i],new_m[i]);}//back into place

           if( (sur[i][L-2]==*n)  && (sur[i][L-1]==*t) )//determining coincidence symbols(...-2,-1 from length)
              {strncpy(new_m[i],sur[i],L-2);//delete two symbol and copy residual intemporary array
              strcat(new_m[i],woman_nt);//merger
              strcpy(sur[i],new_m[i]);}//back into place

               if( (sur[i][L-2]==*l)  && (sur[i][L-1]==*l) )//determining coincidence symbols(...-2,-1 from length)
                  {strncpy(new_m[i],sur[i],L-2);//delete two symbol and copy residual intemporary array
                  strcat(new_m[i],woman_ll);//merger
                  strcpy(sur[i],new_m[i]);}//back into place
     }

        if (data[i][0]==0)//if male name
        {
            if( (sur[i][L-2]==*l)  && (sur[i][L-1]==*d) )//determining coincidence symbols(...-2,-1 from length)
             {strncpy(new_m[i],sur[i],L-2);//delete two symbol and copy residual intemporary array
             strcat(new_m[i],man_ld);//merger
             strcpy(sur[i],new_m[i]);}//back into place

                if( (sur[i][L-2]==*n)  && (sur[i][L-1]==*t) )//determining coincidence symbols(...-2,-1 from length)
                   {strncpy(new_m[i],sur[i],L-2);//delete two symbol and copy residual intemporary array
                   strcat(new_m[i],man_nt);//merger
                   strcpy(sur[i],new_m[i]);}//back into place

                    if( (sur[i][L-2]==*l)  && (sur[i][L-1]==*l) )//determining coincidence symbols(...-2,-1 from length)
                       {strncpy(new_m[i],sur[i],L-2);//delete two symbol and copy residual intemporary array
                       strcat(new_m[i],man_ll);//merger
                       strcpy(sur[i],new_m[i]);}//back into place
        }
    }
}
//-----------------------------------------
void print_sur(char sur [][M])
{
    for(int i=0;i<N;i++)
               {
           if (('\n')== puts(sur[i]))break;
               }
 //------------
    printf("\n");
    printf("\n");
}
//-----------------------------------------
void print_names(char names[][M])
{
    for(int i=0;i<N;i++)
               {
           if (('\n')== puts(names[i]))break;
               }
    printf("\n");
    printf("\n");
}
//-----------------------------------------
void fixName(int data[][DM])
{
    for(int i=0;i<DN;i++)
    {
        if (data[i][0]==1)data[i][1]=rand()%10;//from 0 to 10
        if (data[i][0]==0)data[i][1]=rand()%10+10;//from 10 to 20
    }
}
//-----------------------------------------
void print_data(int data[][DM])
{
    for (int i=0;i<DN;i++)
        printf("data[%i][0]=%d\n",i,data[i][0]);
    printf("\n");
    printf("\n");

    for (int i=0;i<DN;i++)
        printf("data[%i][1]=%d\n",i,data[i][1]);
    printf("\n");
    printf("\n");
}
//-----------------------------------------
void fixAge(int data[][DM])
{
    for (int i=0;i<DN;i++)
    data[i][2]=rand()%(60-18+1)+18;//from 18 to 60
}
//-----------------------------------------
int fixRange(int a,int b)
{//--generation range
return rand()%(b-a+1)+a;
}
//-----------------------------------------
int filterAppl(int data[][DM],int min,int max,int *flag )
{
    int res;
         if (  (data[*flag][2]>=min )&&(data[*flag][2]<=max)  ) {res =1;}
            else {res= 0;}
            return res;
     //1 or 0(appropriate/inappropriate)
}
//-----------------------------------------
void print_matrix_data(int data[][DM])
{
    for (int i=0;i<DN;i++)
        {
            for (int j=0;j<DM;j++)
            {
               printf("%3d",data[i][j]);
            }
            printf("\n");
        }
}
//-----------------------------------------
float midAge(int data [][DM],int v_s )
{
    //v_s-->value (sex)

    int q_w=0;//quantity accepted (women)
    int q_m=0;//quantity accepted (men)
    int s_aw=0;//age amount women
    int s_am=0;//age amount men
    int q_acc=0;//number of accepted men and women

    float middleAge_w;//women
    float middleAge_m;//men

    for (int i=0;i<DN;i++)
    {
     if(  (data[i][0]==1) && (data[i][3]==1) )//if a woman is accepted to job
      {q_w++;s_aw+=data[i][2];q_acc++;}
    }
    for (int i=0;i<DN;i++)
    {
     if(  (data[i][0]==0) && (data[i][3]==1) )//if a man is accepted to job
      {q_m++;s_am+=data[i][2];q_acc++;}
    }

    middleAge_w=s_aw/q_w;
    middleAge_m=s_am/q_m;
/*
    printf("quantity accepted (women)=%i\n",q_w);
    printf("quantity accepted (man)=%i\n",q_m);
    printf("middleAge women=%3.1f\n",middleAge_w);
    printf("middleAge men=%3.1f\n",middleAge_m);
    printf("number of accepted men and women=%i\n",q_acc);
*/
    if (v_s==1) return middleAge_w;
    if (v_s==0) return middleAge_m;
}
//-----------------------------------------



