#include "main.h"

/*Función que inserta números aleatorios en una lista*/
void inserta_datos_de_prueba(Lista lista);

int main()
{
    // Se crea la lista
    Lista lista = crea_lista();
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se insertan datos de prueba
    inserta_datos_de_prueba(lista);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento de la lista
    Elemento* borrado = quita_elemento(lista, 0);
    if (borrado != NULL) {free(borrado->valor);}
    free(borrado);
    printf("La lista tiene %d elementos\n", longitud(lista));

    // Se remueve un elemento que no existe en la lista
    quita_elemento(lista, longitud(lista));
    printf("La lista tiene %d elementos\n", longitud(lista));

    //Se imprime la lista antes de ordenar
    imprime_lista_int(lista);
    ordena_lista(lista, &cmp_int);

    //Se imprime la lista después de ordenar
    imprime_lista_int(lista);

    //Se libera la memoria ocupada
    borra_lista(lista);
}

void inserta_datos_de_prueba(Lista lista)
{
    srand(time(NULL));
    int *num_a_insertar;
    int indice;
    for (indice = 0; indice < 20; ++indice) {
        num_a_insertar = malloc(sizeof(int));
        *num_a_insertar = rand() % 100;
        inserta_elemento(lista, num_a_insertar);
    };
}

/*Compara 2 'Elemento' que contienen como valor un 'int'*/
int cmp_int( const void* a, const void* b){

	//cast a tipo ELEMENTO
	Elemento* x = ( Elemento* )a;
	Elemento* y = ( Elemento* )b;
	//cast de los valores a INT
	int v1 = *(int*) x -> valor;
	int v2 = *(int*) y -> valor;
	
	if( v1 > v2 )
		return 1;

	if( v2 < v2 )
		return -1;

	return 0;

}

/*Función que ordena una lista usando una función comparadora*/
//Recomiendo apoyarte de tu función 'cmp_int', qsort y un arreglo
void ordena_lista(Lista lista, int(*cmp)(const void*, const void*)){

	//creamos un iterador
	Elemento* iterador = *lista;
	//guardamos la longitud de la lista
	size_t len = longitud(lista);
	//creamos un arreglo de elementos para guardar los elementos de la lista
	Elemento* elementos = malloc( sizeof( Elemento )*len );

	//llenamos el arreglo
	for( int i = 0; i < len; i++ ){
		elementos[i] = *iterador;
		iterador = iterador -> siguiente;
	}

	//llamamos a la funcion qsort()
	qsort( elementos, len, sizeof(Elemento), *cmp );

	//apuntamos a la cabeza de la lista
	iterador = *lista;

	//llenamos la lista con los valores ordenados
	for( int i = 0; i < len; i++ ){
		iterador -> valor = elementos[i].valor;
		iterador = iterador -> siguiente;
	}


}

/*Libera(free) la memoria ocupada por la lista, sus elementos y valores*/
//No se te olvide liberar la memoria de cada elemento y su valor.
void borra_lista(Lista lista){
	
	//creamos un iterador
	Elemento* iterador = *lista;

	//si la lista esta vacía solo borra la memoria ocupada por la lista
	if( *lista == NULL ){
		free( lista );
		return;
	}
	//recorremos la lista
	while( iterador != NULL ){
		//quitamos el elemento de la lista
		iterador = quita_elemento( lista, 0 );
		//liberamos ambos campos de ese nodo de la lista
		free( iterador -> valor );
		free( iterador );
		//retomamos el inicio de la lista
		iterador = *lista;
	}
	//liberamos el espacio ocupado por la lista
	free(lista);

}

/*Remueve un elemento de una lista en una posición dada*/
//Si la posición no coincide con ningún elemento se regresa NULL
Elemento *quita_elemento(Lista lista, size_t posicion){

	//creamos un iterador
	Elemento* iterador;
	//auxiliar para mantener el control de la lista al eliminar
	Elemento* auxiliar;
	//En caso de eliminar la cola guardamos el penultimo
	Elemento* auxPenultimo;
	//nos sirve para saber en donde eliminar
	size_t indice = 0;

	//si la lista esta vacía o el apuntador no entra en la longitud regresamos NULL
	if( *lista == NULL || posicion >= longitud(lista) || posicion < 0 )
		return NULL;
	//en caso de que quitemos la cabeza de la lista:
	if( posicion == 0 ){

		//apuntamos al primer elemento de la lista
		iterador = *lista;
		//guardamos el segundo elemento
		auxiliar = iterador -> siguiente;
		//igualamos la referencia del segundo elemento al del primer elemento de la lista
		*lista = auxiliar;
		//regresamos la cabeza
		return iterador;

	}
	//sino nos situamos en el primer elemento.
	iterador = *lista;
	//recorremos la lista
	while( iterador != NULL ){
		//si encontramos la posicion eliminamos el elemento
		if( indice == posicion-1 ){
			//en caso de que sea la cola
			if( posicion == longitud(lista)-1 ){
				auxiliar = iterador;
				//ahora el penultimo es la cola
				auxPenultimo -> siguiente = NULL;
			}else{
				auxiliar = iterador -> siguiente;
				//retomamos el control de la lista
				iterador -> siguiente = auxiliar -> siguiente;
			}
			//regresamos el elemento eliminado
			return auxiliar;

		}
		auxPenultimo = iterador;
		//pasamos al siguiente
		iterador = iterador -> siguiente;
		//aumentamos la posición
		indice ++;
	}

}

/*Imprime los elementos de la lista como enteros*/
void imprime_lista_int(Lista lista){

	//creamos un iterador para recorrer la lista
	Elemento* iterador;
	//nos situamos en el primer elemento.
	iterador = *lista;

	//recorremos la lista
	while( iterador != NULL ){
		void * valor = iterador -> valor;
		//imprimimos el elemento
		printf("%d ", *((int*)valor) );

		iterador = iterador -> siguiente;
	}
	printf("\n");

}

/*Crea una lista vacía*/
Lista crea_lista(){

	//reservamos espacio en memoria para la lista
	Lista lista = malloc( sizeof( Lista ) );
	return lista;

}

/*Inserta un elemento en la lista y se regresa el nuevo tamanio de la lista*/
int inserta_elemento(Lista lista, void *valor){
	//creamos un puntero que apuntará al nuevo elemento
	Elemento* nuevo;

	//si es nulo regresamos la longitud actual de la lista.
	if( valor == NULL )
		return longitud(lista);

	// sino, reservamos espacio en memoria para este nuevo valor
	nuevo = malloc( sizeof( Elemento ) );
	//asignamos el nuevo valor
	nuevo -> valor = valor;
	//apuntamos el elemento a la cabeza de la lista
	nuevo -> siguiente = *lista;
	//apuntamos la lista al nuevo elemento
	*lista = nuevo;
	//regresamos el tamaño de la lista
	return longitud(lista);

}

/*Regresa el número de elementos en la lista*/
size_t longitud(Lista lista){
	
	//creamos un iterador para recorrer la lista
	Elemento* iterador;
	//creamos un contador
	size_t len = 0;

	//nos situamos en el primer elemento.
	iterador = *lista;
	//recorremos la lista
	while( iterador != NULL ){
		iterador = iterador -> siguiente;
		len++;
	}

	return len;

}
