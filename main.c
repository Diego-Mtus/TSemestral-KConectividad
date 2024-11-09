#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// Función para recorrido bfs (del algoritmo visto en clases)
void bfs(int v, int m, int matriz[m][m], int visitado[m]) { // v = vértice inicial, m = cantidad de vértices
    int cola[m]; // Cola para almacenar los vértices visitados
    int sig = 0, padre = 0; 

    visitado[v] = 1; // Marcar el vértice inicial como visitado
    cola[padre++] = v; // Agregar el vértice inicial a la cola

    while (sig < padre) { // Mientras haya vértices en la cola
        int actual = cola[sig++]; // Obtener el vértice actual
        for (int i = 0; i < m; i++) {
            if (matriz[actual][i] == 1 && !visitado[i]) { // Si el vértice actual está conectado con el vértice i y no ha sido visitado.
                visitado[i] = 1;
                cola[padre++] = i;
            }
        }
    }
}

// Función para determinar si el grafo es conexo.
int esConexo(int m, int matriz[m][m]) { // m = cantidad de vértices
    int visitado[m];
    memset(visitado, 0, sizeof(visitado)); // Inicializar el arreglo de visitados con ceros
    
    bfs(0, m, matriz, visitado); 

    /* Realizamos BFS desde el vértice 0 para recorrer el grafo y marcar los vértices visitados.
    De esta forma, para cualquier par de vertices u, v, existirá un camino entre ellos si ambos fueron
    visitados, porque podrán ir por el camino u -> 0 -> v.
    */

    for (int i = 0; i < m; i++) {
        if (!visitado[i]) {
            return 0; // No es conexo
        }
    }
    return 1; // Es conexo
}

// Función para eliminar vértices que será llamada en esKConexo.
void eliminarVertices(int m, int matriz[m][m], int vertices[], int k) {
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < m; j++) {
            matriz[vertices[i]][j] = 0;
            matriz[j][vertices[i]] = 0;
        }
    }
}

// Falta implementar la función esKConexo, y también una función que cree una matriz de adyacencia más pequeña sin los vértices eliminados.
// Para así poder usar la función esConexo en la matriz reducida. (pq el bfs muere cdo los vertices son eliminados pero la matriz es la misma)

int main() {


    // SECCIÓN DE LECTURA DE ARCHIVO
    char path[100];
    printf("Ingrese la ruta del archivo: ");
    scanf("%s", path); // Leer el nombre del archivo de entrada

    freopen(path, "r", stdin); // Redirigir la entrada estándar al archivo de entrada

    if (stdin == NULL) {
        printf("Error al abrir el archivo\n");
        return 1;
    }

    // SECCIÓN DE LECTURA DE DATOS
    int m;
    scanf("%d", &m);

    int matriz[m][m];
    memset(matriz, 0, sizeof(matriz)); // Inicializar la matriz con ceros

    char input[50];
    int row, col;

    for(int i = 0; i < m; i++){
    scanf(" %[^\n]", input); // Leer la entrada del usuario
  
    char *token = strtok(input, ": ,");
    row = atoi(token) - 1; // Obtener el índice de la fila (restar 1 porque los índices empiezan en 0)

    while ((token = strtok(NULL, ": ,")) != NULL) {
        col = atoi(token) - 1; // Obtener el índice de la columna (restar 1 porque los índices empiezan en 0)
        matriz[row][col] = 1; // Marcar la posición en la matriz
    }  
    }

    // Imprimir la matriz para verificar
    printf("Matriz de adyacencia:\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // SECCIÓN DE CÁLCULO DE GRADOS DE LOS VÉRTICES
    int grados[m];
    memset(grados, 0, sizeof(grados)); // Inicializar el arreglo de grados con ceros

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            grados[i] += matriz[i][j]; // Sumar los valores de la fila para obtener el grado de cada vértice
        }
    }

    // Encontrar el vértice con el mayor y menor grado, e imprimirlos.

    int max = 0;
    int min = 0;
    for (int i = 0; i < m; i++) {
        if (grados[i] > grados[max]) {
            max = i;
        }
        if (grados[i] < grados[min]) {
            min = i;
        }
    }

    printf("El grado máximo es: %d\n", grados[max]);
    printf("El grado mínimo es: %d\n", grados[min]);
    

/*  // Pruebas de k-conectividad
    printf("%d\n", esKConexo(m, matriz, 1));
    printf("%d\n", esKConexo(m, matriz, 2));
    printf("%d\n", esKConexo(m, matriz, 3));
    printf("%d\n", esKConexo(m, matriz, 4));
*/

    int k;
    if(esConexo(m, matriz)){
        printf("El grafo es conexo.\n");
        for(k = 1; k <= 4 & k < m; k++){ // Falta implementar la función esKConexo
            //if(!esKConexo(m, matriz, k)){
            //   break;
            //}
        }
        printf("Específicamente, el grafo es %d-conexo.\n", k-1);
    } else {
        printf("El grafo no es conexo.\n");
    }


    return 0;
}
