#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
AVANCE:
[X] Crear La estructura Nodo
[X] Funciones Buscar e insertar
[ ] Funcion borrar
[ ] Validar repetidos en un mismo directorio
[ ] Validar que la raiz nunca sea borrada
[X] Funcion Imprimir como el comando de CMD: TREE
*/


typedef struct _Nodo
{
	char file[50];
	struct _Nodo *son; //nodo hijo
	struct _Nodo *brother; //nodo hermano siguiente
	int counter; //cuantos hijos tiene este nodo
}Nodo;

//Arbol n-ario -> atributos
Nodo* root; //nodo root del Arbol
Nodo *answer; //nodo answer: ayuda a tener el resultado de una busqueda

//Arbol n-ario -> funciones
void find(const char* file, Nodo* tmp = root)
{
	if(answer!=NULL) return;	
	if(tmp==NULL)    return;
	if(strcmp(tmp->file,file)==0){
		answer = tmp;
	}
	else{
		find(file, tmp->son);
		find(file, tmp->brother);
	}
	
}

bool insert(const char* file, const char* new_file, Nodo* tmp = root)
{
	answer = NULL;
	find(file);
	if(answer==NULL) return false;
	Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
	novo->son = novo->brother = NULL;
	novo->counter = 0;
	strcpy(novo->file, new_file);
	
	answer->counter++;
	if(answer->son==NULL) answer->son = novo;
	else{
		answer = answer->son;
		while(answer->brother != NULL){
			answer = answer->brother;
		}
		answer->brother = novo;
	}
	return true;
}

//format nos ayuda a verificar el ponemos '|' o ' ' cuando comvenga
const int MAX_WIDTH = int(1e6);
bool format[MAX_WIDTH]; //{0 0 0 1 0 0 0 1 0 1 0 0 1 0 1}

void tabs(int deep, int len, int pos) //puts deep tabs
{
	for(int i=0;i<deep;++i){
		if(i==deep-1){
			if(pos == 0)       printf("%c", char(192)); //└
			else if(pos>0)     printf("%c", char(195)); //├
		}
		else{
			if(format[i] == 1) printf("%c", char(179)); //│
			else               printf(" ");             //' '
		}
		for(int j=0;j<3;++j) //espacio de TAB
			if(i==deep-1)      printf("%c", char(196)); //─
			else               printf(" ");             //' '
	}
}

/*
tmp : nodo actual
deep: profundidad actual
len : cantidad de hijos de un nodo
pos : indice de posicion de un hermano, hijo de un nodo
brothers : indica que solo la primera que entramos a la funciones
			solo buscamos en su hijo de tmp, y no en sus hermanos
			, las demas veces es lbre de entrar en hijo y hermanos
           
*/
void print(Nodo* tmp, int deep=0, int len=0, int pos=0, bool brothers=false)
{
	if(tmp){
		tabs(deep, len, pos);
		printf("%s\n", tmp->file);
		
		if(tmp->son){
			if(tmp->counter == 1) format[deep] = 0;
			else                  format[deep] = 1;
			print(tmp->son, deep+1, tmp->counter, tmp->counter-1,true);
		}
		
		if(tmp->brother && brothers){
			if(tmp->brother->brother == NULL) format[deep-1] = 0;
			print(tmp->brother, deep, len, pos-1,brothers);
		}
	}
}
int main()
{
	root       = (Nodo*)malloc(sizeof(Nodo)); 
	root->son = root->brother = NULL;
	root->counter = 0;
	strcpy(root->file, "1");
	
	
	insert("1", "2");
	insert("1", "3");
	insert("1", "4");
	
	insert("2", "5");
	insert("2", "6");
	
	insert("6", "34");
	insert("6", "35");
	insert("6", "36");
	
	insert("4", "7");
	insert("4", "8");
	
	insert("7", "9");
	
	insert("9", "19");
	
	insert("5", "10");
	
	insert("10", "12");
	insert("10", "13");
	insert("10", "14");
	insert("10", "15");
	
	insert("13", "16");
	insert("13", "17");
	
	insert("17", "18");
	
	answer = NULL;
	find("10");
	if(answer == NULL){
		printf("no encontrado\n");
	}
	else {
		printf("Encontrado: %s\n", answer -> file);
		print(answer); // comando TREE de CMD
	}
	
	//Comando de CMD -> tree
	//print(root);
	
	
	return 0;
}
