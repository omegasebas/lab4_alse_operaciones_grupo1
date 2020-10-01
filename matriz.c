/*Este programa hace la suma,resta y transpuesta de dos matrices,pero estas matrices se encuentran en un archivo .csv
y si el usuario introduce -w, la operación que quiera hacer también se visualizaran en un archivo .csv
Autores=Ximena Garzón López y Sebastián Babativa Veloza
version=1.0.0 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define TAM_MAX 200
#define MAX_POS  50	
 #define MAX1_POS 50
#define MIN_POS 2

typedef  struct Matrices{
	 float Mat1[TAM_MAX][TAM_MAX],Mat2[TAM_MAX][TAM_MAX];
     }Matrices;//estructa que contiene las dos matrices	 
	 
void formar_matrizA(Matrices *mat,char buffer1[TAM_MAX],int *fila,int *colum);	
void formar_matrizB(Matrices *mat,char buffer2[TAM_MAX],int *fila2,int *colum2);
void help();
void Mostrar_version();
void suma(Matrices mat,int fila,int columna,int fila2,int columna2,float res_suma[TAM_MAX][TAM_MAX]);
void resta(Matrices mat,int fila,int columna,int fila2,int columna2,float res_resta[TAM_MAX][TAM_MAX]);
void transpuesta(Matrices mat,int fila,int columna,int fila2,int columna2,float trans1[TAM_MAX][TAM_MAX],float trans2[TAM_MAX][TAM_MAX]);
 void pasar_p(float resultado[TAM_MAX][TAM_MAX],char *buf,int fila,int columna);
 void pasar_pm(float resultado[TAM_MAX][TAM_MAX],char *buf,int fila,int columna);
 void mostrar_respuesta(char buffer[TAM_MAX],char dir[TAM_MAX]);
void main(int argc,char *argv[])
{
     Matrices matric;
	 int fila,col,fila2,col2,cont_fila,cont_columna;
	 char buffer1[TAM_MAX],buffer2[TAM_MAX],buffer_suma[TAM_MAX],buffer_resta[TAM_MAX],ruta[TAM_MAX];
	 char buffer_trans1[TAM_MAX],buffer_trans2[TAM_MAX];
	FILE *file_descriptor1,*file_descriptor2;
	size_t result1=0,result2=0;
	long file_size1=0,file_size2=0;
	float result_suma[TAM_MAX][TAM_MAX],result_resta[TAM_MAX][TAM_MAX],mat_trans1[TAM_MAX][TAM_MAX],mat_trans2[TAM_MAX][TAM_MAX];
    char rutica[TAM_MAX]={"archivo.csv"};
	

    memset(ruta, 0, TAM_MAX);
	
	strcpy(ruta,argv[5]);
	
	
	printf("la ruta es %s",ruta);
	
	
	file_descriptor1=fopen(argv[2],"r");
	
	fseek (file_descriptor1,0, SEEK_END);
	
	file_size1=ftell(file_descriptor1);
	
	rewind(file_descriptor1);
	
	result1=fread(buffer1, 1, file_size1,file_descriptor1);
	if(result1!=file_size1)
	{
     fputs("Error de lectura de buffer",stderr);
    }
    fclose(file_descriptor1);
    buffer1[file_size1]='\0';

	
	file_descriptor2=fopen(argv[3],"r");
	
	fseek (file_descriptor2,0, SEEK_END);
	
	file_size2=ftell(file_descriptor2);
	
	rewind(file_descriptor2);
	
	result2=fread(buffer2, 1, file_size2,file_descriptor2);
	if(result2!=file_size2)
	{
     fputs("Error de lectura de buffer",stderr);
    }
    fclose(file_descriptor2);
    buffer2[file_size2]='\0';
	
	
	formar_matrizA(&matric,buffer1,&fila,&col);
	formar_matrizB(&matric,buffer2,&fila2,&col2);
		if(strcmp(argv[1],"--help") == 0)
		{ 
		
	help();	
		
		}
		else 
		{
		if(strcmp(argv[1],"-v\0") == 0)
	    {
			
	    Mostrar_version();
		}
		else
		
			if(strcmp(argv[1],"-a\0") == 0)
			{
		suma(matric,fila,col,fila2,col2,result_suma);
		}
		else 
		
		if(strcmp(argv[1],"-r\0") == 0)
		{	
		resta(matric,fila,col,fila2,col2,result_resta);
		}
		
         else 
			 
		if(strcmp(argv[1],"-t\0") == 0)
		{	
	    transpuesta(matric,fila,col,fila2,col2,mat_trans1,mat_trans2);
		
	    }

			 else 
				 
			 printf("\nPor favor ingrese una opción correcta\n\n");			 
		 	
	
}

           if(strcmp(argv[4],"-w\0") == 0)
		 {
			 if (strcmp(argv[1],"-a\0") == 0)
			 {
			 pasar_p(result_suma,buffer_suma,fila,col);
	         mostrar_respuesta( buffer_suma,ruta);
			 }
			 if (strcmp(argv[1],"-r\0") == 0)
			 {
			 pasar_p(result_resta,buffer_resta,fila,col);
	         mostrar_respuesta(buffer_resta,ruta);			 
			 }
			 if (strcmp(argv[1],"-t\0") == 0)
			 {
			  pasar_pm(mat_trans1,buffer_trans1,fila,col);	 
			  pasar_pm(mat_trans2,buffer_trans2,fila2,col2);
			  
				 if (strcmp(argv[6],"2\0") == 0)
				 {
					 mostrar_respuesta( buffer_trans2,ruta);
				 }
				else
				{
			  mostrar_respuesta( buffer_trans1,ruta);
			 }
	}
  }  
}	

void formar_matrizA(Matrices *mat,char buffer1[TAM_MAX],int *fila,int *colum)
{
	int cont_fila=0,cont_columna=0,cont1=0,cont2=0,cont3=0,coni=0,conn=0,fil=0,col=0;
	char str1[TAM_MAX],numeros[MAX1_POS],numeros2[MIN_POS],numeros3[MAX1_POS],numeros4[MIN_POS];
	float valor1=0,val4;
	int val3=0,contt=0,contn=0,val2=0,conte=0;
	//para saber cuantas filas hay	
 for(cont_fila=0;cont_fila<strlen(buffer1);cont_fila++)
  {
     if(buffer1[cont_fila]=='\n')
     {
      *fila=*fila+1;
     }	  
  }
//para saber cuantas columnas hay  
   for(cont_columna=0;buffer1[cont_columna]!='\n';cont_columna++)
  {
     if(buffer1[cont_columna]==';')
     {
      *colum=*colum+1;
     }	  
  }
 
 //para pasar del buffer a la Matriz1 
 
  for(cont1=0;cont1<strlen(buffer1);cont1++)//contdor desde 0 hasta la posicion final del buffer
	   
   {  
	            val3=1;//inicializacion de variable para poder usar exponente 
				conn=0;
            memset(numeros, 0, MAX_POS);//limpieza de la cadena numeros para eliminar basura  
        
		  while((buffer1[cont1]!=';') && (buffer1[cont1]!='\n')&&(buffer1[cont1]!='\r')) //condicion para empezar a asignar numeros ala nueva cadena 
			  
		  {
			  if((buffer1[cont1]=='\r'))//tomar el \r como si no existiera para guiarnos solo con \n y ;
			  {
				  cont1=cont1+1;
				  
			  }
				  
			  if((buffer1[cont1]==','))//en caso de encontrar una coja se realiza un conteo
				  
			  {	
				  cont1=cont1+1;
				  conn=cont1;

					coni=0;
					
				  while((buffer1[conn]!=';') && (buffer1[conn]!='\n')&&(buffer1[conn]!='\r')) //contar las posiciones despues de la coma 
				  {
					  coni=coni+1;
					  conn=conn+1;	  
				  }  
				  
			  for(conte=0;conte<coni;conte++)// poder hacer la funcion 10 elevado ala val3 sin usar otra libreria 
		{
			val3=val3*10;
	     
		}	
	
				  }
           numeros2[0]=buffer1[cont1];//asiganacion caracter por caracter 
		   numeros2[1]='\0';

	   	   strcat(numeros,numeros2);// concatenar caracter por caracter para poder aplicarlo al atoi
		   cont1=cont1+1;
			}

			val4=atoi(numeros);//conversion de cadena de caracteres a entero y asignarlo en un flotante
	       mat->Mat1[fil][col]=(val4/val3);// asignacion del numero en la posicion de la matriz 
	     	col=col+1; //desplazamiento en la columna 
			
      if(buffer1[cont1]=='\n')//desplazamiento en la fila 
	    {  
		  fil=fil+1;
		  col=0;
		}

}
   //imprimir matriz
    printf("\n La  Matriz1 es:\n\n");
  for(cont2=0;cont2<*fila;cont2++)
	  
   {
	   for(cont3=0;cont3<=*colum;cont3++)
	   {
		   printf(" %.2f ",mat->Mat1[cont2][cont3]);
	   }
	   
	   printf("\n");
   }   
  printf("\n\n");

}

void formar_matrizB(Matrices *mat,char buffer2[TAM_MAX],int *fila2,int *colum2)
{
	int cont_fila=0,cont_columna=0,cont1=0,cont2=0,cont3=0,coni=0,conn=0,fil=0,col=0;
	char str1[TAM_MAX],numeros[MAX1_POS],numeros2[MIN_POS],numeros3[MAX1_POS],numeros4[MIN_POS];
	float valor1=0,val4;
	int val3=0,contt=0,contn=0,val2=0,conte=0;
	//para saber cuantas filas hay	
 for(cont_fila=0;cont_fila<strlen(buffer2);cont_fila++)
  {
     if(buffer2[cont_fila]=='\n')
     {
      *fila2=*fila2+1;
     }	  
  }
//para saber cuantas columnas hay  
   for(cont_columna=0;buffer2[cont_columna]!='\n';cont_columna++)
  {
     if(buffer2[cont_columna]==';')
     {
      *colum2=*colum2+1;
     }	  
  }


 //para pasar del buffer a la Matriz2
 
   for(cont1=0;cont1<strlen(buffer2);cont1++)//contdor desde 0 hasta la posicion final del buffer
	   
   {  
	            val3=1;//inicializacion de variable para poder usar exponente 
				conn=0;
            memset(numeros, 0, MAX_POS);
        
		  while((buffer2[cont1]!=';') && (buffer2[cont1]!='\n')&&(buffer2[cont1]!='\r')) //condicion para empezar a asignar numeros ala nueva cadena 
			  
		  {
			  if((buffer2[cont1]=='\r'))//tomar el \r como si no existiera para guiarnos solo con \n y ;
			  {
				  cont1=cont1+1;
				  
			  }
				  
			  if((buffer2[cont1]==','))//en caso de encontrar una coja se realiza un conteo
				  
			  {	
				  cont1=cont1+1;
				  conn=cont1;

					coni=0;
					
				  while((buffer2[conn]!=';') && (buffer2[conn]!='\n')&&(buffer2[conn]!='\r')) //contar las posiciones despues de la coma 
				  {
					  coni=coni+1;
					  conn=conn+1;	  
				  }  
				  
			for(conte=0;conte<coni;conte++)// poder hacer la funcion 10 elevado ala val3 sin usar otra libreria
		{
			val3=val3*10;
	     
		}	
	
				  }
           numeros2[0]=buffer2[cont1];//asiganacion caracter por caracter
		   numeros2[1]='\0';

	   	   strcat(numeros,numeros2);// concatenar caracter por caracter para poder aplicarlo al atoi
		   cont1=cont1+1;
			}

			val4=atoi(numeros);//conversion de cadena de caracteres a entero y asignarlo en un flotante
	       mat->Mat2[fil][col]=(val4/val3);// asignacion del numero en la posicion de la matriz 
	     	col=col+1; //desplazamiento en la columna 
			
      if(buffer2[cont1]=='\n')//desplazamiento en la fila 
	    {  
		  fil=fil+1;
		  col=0;
		}

}
//imprimir matriz
    printf("\n La  Matriz2 es:\n\n");
  for(cont2=0;cont2<*fila2;cont2++)
	  
   {
	   for(cont3=0;cont3<=*colum2;cont3++)
	   {
		   printf(" %.2f ",mat->Mat2[cont2][cont3]);
	   }
	   
	   printf("\n");
   }   
  printf("\n\n");

}
void help()
{
printf("\n\n-v \tMuestra versión, autores y fecha de desarrollo\n");
printf("-t  \tMuestra la transpuesta de las dos matrices\n");
printf("-a  \tSuma las dos matrices\n");
printf("-r  \tResta las dos matrices\n"),
printf("-w  \tIndica que el resultado de la operación se debe \n"); 
printf("    \tguardar en un archivo con formato CSV. Se debe agregar ruta y \n");
printf("    \tnombre de donde se guardará el archivo.\n\n");
}	
void Mostrar_version()
{
printf("\n\nVersión: 1.0.0\n");
printf("Autores: Leidy Ximena Garzón López y ");
printf("Sebastián Babativa Veloza\n");
printf("Fecha de desarrollo: 25 de septiembre del 2020\n\n"); 
}
void suma(Matrices mat,int fila,int columna,int fila2,int columna2,float res_suma[TAM_MAX][TAM_MAX])
{
	int cont_fila,cont_columna;
	 float Suma[MAX_POS][MAX_POS];
  if(fila==fila2 && columna==columna2)

	{
      for(cont_fila=0;cont_fila<fila;cont_fila++)
      {
        for(cont_columna=0;cont_columna<columna+1;cont_columna++)
        {			
	       res_suma[cont_fila][cont_columna]=mat.Mat1[cont_fila][cont_columna]+mat.Mat2[cont_fila][cont_columna];
		}
      }
	  //imprimir la matriz Suma
    printf("\n La  Matriz Suma es:\n\n");
			for(cont_fila=0;cont_fila<fila;cont_fila++)
			{
				for(cont_columna=0;cont_columna<columna+1;cont_columna++)
				{			
				printf(" %.2f ",res_suma[cont_fila][cont_columna]);
				}
		printf("\n");
			}
	}
    else
	{
   printf("\n\n Las matrices ingresadas no tienen el mismo tamaño\n\n");		
	}
printf("\n\n");	
}
void resta(Matrices mat,int fila,int columna,int fila2,int columna2,float res_resta[TAM_MAX][TAM_MAX])
{
	int cont_fila,cont_columna;
	 float Resta[MAX_POS][MAX_POS];
  if(fila==fila2 && columna==columna2)

	{
      for(cont_fila=0;cont_fila<fila;cont_fila++)
      {
        for(cont_columna=0;cont_columna<columna+1;cont_columna++)
        {			
	       res_resta[cont_fila][cont_columna]=mat.Mat1[cont_fila][cont_columna]-mat.Mat2[cont_fila][cont_columna];
		}
      }
	  	  //imprimir la matriz resta
    printf("\n La  Matriz Resta es:\n\n");
			for(cont_fila=0;cont_fila<fila;cont_fila++)
			{
				for(cont_columna=0;cont_columna<columna+1;cont_columna++)
				{			
				printf(" %.2f ",res_resta[cont_fila][cont_columna]);
				}
		printf("\n");
			}
	}
    else
	{
   printf("\n\n Las matrices ingresadas no tienen el mismo tamaño\n\n");		
	} 
printf("\n\n");	
}
void transpuesta(Matrices mat,int fila,int columna,int fila2,int columna2,float trans1[TAM_MAX][TAM_MAX],float trans2[TAM_MAX][TAM_MAX])
{
	int cont_fila=0,cont_columna=0;
	float matriztrans1[MAX_POS][MAX_POS],matriztrans2[MAX_POS][MAX_POS];


	  for(cont_fila=0;cont_fila<=columna;cont_fila++)
      {
	  for(cont_columna=0;cont_columna<fila;cont_columna++)
	   {
	   trans1[cont_fila][cont_columna]=mat.Mat1[cont_columna][cont_fila];
	   }
	   
	   printf("\n");
     }  
	  //imprimir la transpuesta de Matriz1
    printf("\n La Transpuesta  de  la Matriz1  es:\n\n");
	  for(cont_fila=0;cont_fila<=columna;cont_fila++)
      {
	  for(cont_columna=0;cont_columna<fila;cont_columna++)
	   {
	   printf(" %.2f ",trans1[cont_fila][cont_columna]);
	   }
	   
	   printf("\n");
     }  
 printf("\n");
   
	  for(cont_fila=0;cont_fila<=columna2;cont_fila++)
   {
	   for(cont_columna=0;cont_columna<fila2;cont_columna++)
	   {
		 trans2[cont_fila][cont_columna]=mat.Mat2[cont_columna][cont_fila];
	   }
	   
	   printf("\n");
   } 
     //imprimir la transpuesta de Matriz2
    printf("\n La Transpuesta  de  la Matriz2  es:\n\n");
for(cont_fila=0;cont_fila<=columna2;cont_fila++)
   {
	   for(cont_columna=0;cont_columna<fila2;cont_columna++)
	   {
		   printf(" %.2f ",trans2[cont_fila][cont_columna]);
	   }
	   
	   printf("\n");
   } 
   printf("\n\n");
}
 void pasar_p(float resultado[TAM_MAX][TAM_MAX],char *buf,int fila,int columna )
 //pasa la matriz a un buffer
 {
	 
	 int cont2=0,cont3=0,cont4=0;
	 char pasar1[TAM_MAX],pasar2[TAM_MAX],pasar3[TAM_MAX],pasar4[TAM_MAX];
	 int bande=0;
	 
	
		
	 memset(buf, 0, TAM_MAX);
  	 
 for(cont2=0;cont2<fila;cont2++)
      {

	  for(cont3=0;cont3<=columna;cont3++)
	   {

		   if(cont3-1==1)
		   {
		bande=1;  //bande se activa cuando se debe cambiar de fila 
		   }
        sprintf(pasar1,"%.2f",resultado[cont2][cont3]);
		
		strcpy(pasar2,pasar1);
		
		if(bande==1)
		{
			pasar3[0]='\r';
	    pasar3[1]='\0';
		
	    pasar4[0]='\n';
	    pasar4[1]='\0';

	    strcat(pasar2,pasar3);
	    strcat(pasar2,pasar4);
		
		}
      else
	   {
		   
		
		pasar3[0]=';';
	    pasar3[1]='\0';
	
	   strcat(pasar2,pasar3);

	   }
	   
	  strcat(buf,pasar2);	
	   memset(pasar2, 0, TAM_MAX);
	   memset(pasar3, 0, TAM_MAX);
 
	   bande=0;
	   
	  }
  
	  }


	   
 }
 
void mostrar_respuesta(char buffer[TAM_MAX],char dir[TAM_MAX])
//genera el archivo.csv e introduce el buffer
 {
	 
FILE *descriptor;
     descriptor=fopen(dir,"w");
        fputs(buffer, descriptor);
    fclose(descriptor);
 }
 
 
 
  void pasar_pm(float resultado[TAM_MAX][TAM_MAX],char *buf,int fila,int columna )
   //pasa la matriz transpuesta a un buffer
 {
	 
	 int cont2=0,cont3=0,cont4=0;
	 char pasar1[TAM_MAX],pasar2[TAM_MAX],pasar3[TAM_MAX],pasar4[TAM_MAX];
	 int bande=0;
	 
	
		
	 memset(buf, 0, TAM_MAX);
  	 
 for(cont2=0;cont2<=columna;cont2++)
      {

	  for(cont3=0;cont3<fila;cont3++)
	   {

		   if(cont3-2==1)
		   {
		bande=1;   //bande se activa cuando se debe cambiar de fila 
		   }
        sprintf(pasar1,"%.2f",resultado[cont2][cont3]);
		
		strcpy(pasar2,pasar1);
		
		if(bande==1)
		{
			pasar3[0]='\r';
	    pasar3[1]='\0';
		
	    pasar4[0]='\n';
	    pasar4[1]='\0';

	    strcat(pasar2,pasar3);
	    strcat(pasar2,pasar4);
		
		}
      else
	   {
		   
		
		pasar3[0]=';';
	    pasar3[1]='\0';
	
	   strcat(pasar2,pasar3);

	   }
	   
	  strcat(buf,pasar2);	
	   memset(pasar2, 0, TAM_MAX);
	   memset(pasar3, 0, TAM_MAX);
 
	   bande=0;
	   
	  }

	  }
	   
 }