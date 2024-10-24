#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

const int MAX_INTENTOS = 10; //Cantidad máxima de intentos.
const int LARGO_CODIGO = 4; //El largo de los códigos.
const char PRIMERA_LETRA = 'A'; //Letra inicial del rango disponible.
const char ULTIMA_LETRA = 'H'; //Última letra del rango disponible.

using namespace std;

/**
 @brief Genera un código al azar y lo asigna al parámetro codigo.
 El código generado puede contener letras repetidas.
 @param codigo El código (arreglo de caracteres) a inicializar.
**/
void generarCodigo(char codigo[LARGO_CODIGO]) {
	unsigned srand(time(NULL));
	for (int i = 0; i < LARGO_CODIGO; i++)
		codigo[i] = rand() % (ULTIMA_LETRA - PRIMERA_LETRA + 1) + PRIMERA_LETRA;
}
/**
 @brief Lee el codigo de la entrada estandar y lo asigna a codigo.
Además retorna el valor TRUE si el codigo leido es correcto, FALSE sino.
El codigo leido puede ser incorrecto si :
* Contiene uno o mas caracteres fuera del rango.
* No contiene el largo LARGO_CODIGO.
 @param codigo El arreglo donde se asignará el código leído desde la entrada.
 @retval TRUE si la entrada es correcta, FALSE si no lo es.
**/
bool leerCodigo(char codigo[LARGO_CODIGO]) {
	string v;
	int contador = 0;
	cin >> v;


	for (int i = 0; i < LARGO_CODIGO; i++) {
		if (v[i] > ULTIMA_LETRA || v[i] < PRIMERA_LETRA)
			return false;
	}

	for (int i = 0; ; i++) {
		if (v[i] == '\0')
			break;
		contador++;
	}
	if (contador != LARGO_CODIGO)
		return false;

	for (int i = 0; i < LARGO_CODIGO; i++) {
		codigo[i] = v[i];
	}

	return true;
}

/**
 @brief Imprime el codigo pasado como argumento en la salida estandar.
Deja el cursor al final de esa misma línea.
 @param codigo El código a imprimir en la salida.
**/
void imprimirCodigo(char codigo[LARGO_CODIGO]) {
	for (int i = 0; i < LARGO_CODIGO; i++) {
		cout << codigo[i];
	}
	cout << endl;
}

/**
 @brief Calcula las notas de codAdivinador en función de codPensador.
Asigna los buenos y los regulares a los argumentos con el mismo nombre.
 @param codAdivinador El código presentado por el adivinador.
 @param codPensador El código del pensador.
 @param buenos Parámetro para recibir los buenos.
 @param regulares Parámetro para recibir los regulares.
**/
void calcularNota(char codAdivinador[LARGO_CODIGO], char codPensador[LARGO_CODIGO],
	int& buenos, int& regulares) {

	bool evaluadorA[LARGO_CODIGO], evaluadorP[LARGO_CODIGO];

	for (int i = 0; i < LARGO_CODIGO; i++) {
		evaluadorA[i] = false;
		evaluadorP[i] = false;
	}


	for (int i = 0; i < LARGO_CODIGO; i++) {
		if (codPensador[i] == codAdivinador[i]) {
			evaluadorP[i] = true;
			evaluadorA[i] = true;
			buenos++;
		}
	}
	//VAMOS A HACER LA SEGUNDA VERIFICACION
	for (int i = 0; i < LARGO_CODIGO; i++) {
		if (!evaluadorA[i]) {
			for (int j = 0; j < LARGO_CODIGO; j++) {
				if (!evaluadorP[j]) {
					if (codAdivinador[i] == codPensador[j]) {
						regulares++;
						evaluadorA[i] = true;
						evaluadorP[j] = true;
						break;
					}

				}
			}
		}
	}
	cout << "B= " << buenos << " R= " << regulares << endl;
}

int main() {

	char codigoPensador[LARGO_CODIGO];
	char codigoAdivinador[LARGO_CODIGO];
	bool ganar = false;
	int buenos = 0, regulares = 0;

	generarCodigo(codigoPensador);
	//imprimirCodigo(codigoPensador);
	cout << "MasterMind V2.5" << endl
		<< "Dispones de " << MAX_INTENTOS << " intentos para adivinar el codigo." << endl;
	for (int intentos = 1; intentos < MAX_INTENTOS; intentos++) {
		cout << "Codigo " << intentos << " de " << MAX_INTENTOS << ">>";
		while (!leerCodigo(codigoAdivinador)) {
			cout << "ERROR:El codigo no es valido. Ingresa otro con " << LARGO_CODIGO << " letras entre " << PRIMERA_LETRA << " y " << ULTIMA_LETRA << ">>";
		}
		calcularNota(codigoAdivinador, codigoPensador, buenos, regulares);
		//REINICIAMOS LOS VALORES O DEFINIMOS GANADOR
		if (buenos == LARGO_CODIGO) {
			ganar = true;
			break;
		}
		else {

			buenos = 0;
			regulares = 0;
		}


	}
	//DESIGNAR SI GANASTE O PERDISTE
	if (ganar)
		cout << "EXCELENTE!!! Ganaste." << endl;
	else {
		cout << "PERDISTE!!! El codigo era ";
		imprimirCodigo(codigoPensador);
	}
	return 0;
}