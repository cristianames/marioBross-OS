
#include"Planificador.h"
#define RD_INICIAL 0

void inicializar(info*);

void borrarTanda(info*);
void crearStruct(nuevo*,player*);
int leerNovedad(info*,nuevo**,player*);

void reordenar(t_list*ready);
void cargarAlFinal(player*,t_list*);

void interrupcion(int,short,answer*,global);
int selectear(answer*,short,fd_set*,int,int,global);

int cantleidos=0,RR=0;

void *planificador (void *parametro){
	puts("\nHola mundo!!--Yo planifico.");
	info*raiz=(info*)parametro;
	nuevo*actual;
	actual=raiz->new;
	t_list *stack,*ready,*sleeps;

	stack=list_create();
	ready=list_create();
	sleeps=list_create();
	player exec;
	fd_set master, copy;
	int maxfd,rest=0;
	FD_ZERO(&master);
	FD_ZERO(&copy);
	FD_SET(raiz->nid,&master);
	maxfd=raiz->nid;
	global general;
	general.cabecera=raiz;
	general.ready=ready;
	general.sleeps=sleeps;
	general.algo=&RR;
	general.exe=&exec;
	general.recur=stack;
	general.resto=&rest;
	printf("Nuestro Nivel Se llama: %s\n",raiz->name);
	puts("\nEnviando Saludos al nivel..");
	inicializar(raiz);
	player*temp;
	int estado=1;
	short respuesta;
	while (1){ 		//Solo por ahora lee conexiones!! (estado!=0)
		player aux;
		estado=leerNovedad(raiz,&actual,&aux);
		if(estado!=0){
			puts("Cargando jugador a la base de datos..");
			temp=malloc(sizeof(player));
			*temp=aux;
			cargarAlFinal(temp,ready);
			FD_SET(temp->pid,&master);
			if(temp->pid>maxfd)maxfd=temp->pid;
			raiz->currplay++;
			puts("Avisandole al nivel..");
			sendAnswer(7,0,' ',temp->sym,(short)raiz->nid);
			copy=master;
			puts("Selecteando..");
			respuesta=selectear(NULL,1,&copy,maxfd,raiz->nid,general);
			switch (respuesta){
			case 1:puts("--El nivel se ha enterado.--");
				break;
			case -1:puts("--ERROR: El nivel comenta que hubo un error.--");
				break;
			}
		}

	}
puts("El hilo termina ahora!!");

	return 0;
}

void inicializar(info*raiz){
	puts("\nPidiendo algoritmo.");
	sendAnswer(6,0,' ',' ',(short)raiz->nid);
	sleep(1);
	answer tempo;
	recvAnswer(&tempo,(short)raiz->nid);
	RR=tempo.cont;
	if(RR==0)puts("Se ha elegido usar el Algoritmo SRDF.");
	else printf("Se ha elegido usar el Algoritmo Round Robins Q==%d\n",RR);
}

void borrarTanda(info*raiz){
	int cont;
	for(cont=1;cont<=5;cont++){
		nuevo*aux;
		aux=raiz->new;
		raiz->new=raiz->new->sgte;
		free(aux);
	}
}
void crearStruct(nuevo*actual,player*temp){
	temp->pid=actual->pid;
	temp->sym=actual->sym;
	temp->data.dist=RD_INICIAL;
	temp->data.recsol=' ';
	temp->stack=list_create();
}
int leerNovedad(info*raiz,nuevo**actual,player*temp){
	if (cantleidos==6){
		puts("Ya van 6..");
		borrarTanda(raiz);
		cantleidos=0;
	}
	if ((*actual)->pid==0)return 0;
	else{
		crearStruct(*actual,temp);
		puts("Se ha coenctado un jugador!!");
		*actual=(*actual)->sgte;
	}
	return 1;
}

bool comparator(void*anterior, void*actual){
	player *ant,*act;
	ant=(player*)anterior;
	act=(player*)actual;
	if(ant->data.dist>act->data.dist)return true;
	else return false;
}
void reordenar(t_list*ready){
	if (RR!=0)puts("--Planificación Round Robins => Sin Reordenar--");
	else{
		puts("--Planificación SRDF => Reordenando..--");
		list_sort(ready,comparator);
	}
}
void cargarAlFinal(player*temp,t_list*ready){
	list_add(ready, (void*)temp);
	reordenar(ready);
}

void interrupcion(int i,short respuesta,answer* aux,global tabla){
	if(i==tabla.cabecera->nid){
		/*switch(respuesta){
		case 0:aLaMierdaConTodo(tabla);
		break;
		case 6:modificarAlgoritmo(aux->cont,tabla);
		break;
		case 8:muertePersonaje(aux->cont,tabla);
		break;
		}*/
	}
}
int selectear(answer*tempo,short esperado,fd_set*readfds,int fdmax,int sock,global tabla){
	answer aux;
	short respuesta;
	do{
		selectGRID(fdmax,readfds);

		int i=0;
		while ((!FD_ISSET(i,readfds))&&(i<=fdmax))	i++;
		if (i>fdmax){
			puts("--ERROR:No se encontro candidato para selectear!!--");
			exit(1);
		}else{
			printf("Se escuchara al socket numero %d\n",i);
			respuesta=recvAnswer(&aux,i);
			if (i==sock){
				if((respuesta==esperado)||(respuesta==-1))return respuesta;
				else interrupcion(i,respuesta,&aux,tabla);
			}else{
				interrupcion(i,respuesta,&aux,tabla);
			}
			if (tempo!=NULL)*tempo=aux;
		}
	}while(1);
	return -1;
}


