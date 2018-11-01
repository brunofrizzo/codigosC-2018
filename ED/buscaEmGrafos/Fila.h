#define N 10

struct Fila{
     int data[N]; 
     int tamanho;
     int inicio;
};


Fila* criar();
void enqueue(Fila* f, int elemento);
bool cheia(Fila* f);
bool vazia(Fila* f);
int dequeue(Fila* f);
void print(Fila* f);
int frente(Fila* f);

