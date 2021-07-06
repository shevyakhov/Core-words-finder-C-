// coreWord.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
void Clear(int Arr[50],int count) {
	for (int i = 0; i < count;i++) {
		Arr[i] = 0;
	}
}
void toCount(char A[25][50], int C[50],int count) {
	for (int i = 0; i < count ; i++)
	{
		for (int j = 0; j < count; j++) {

			if (i != j && strncmp(A[i], A[j],strlen(A[i])) == 0) {
				C[i]++;
			}
		}
	}
}
void allSubKeyWords(int longest, char A[25][50], int count,char str[100]) {

	for (int i = 0;i < count; i++) {
		if ((i != longest) && (strncmp(A[longest], A[i], strlen(A[longest])) == 0)) {
			strcat(str, A[i]);
			strcat(str, " ");
			
		}
	}
}
int whatIsKeyWord(int C[50],int count) {
	int key = -1;
	for (int i = 0; i < count; i++) {
		if (key >= 0) {
			if (C[i] && (C[i] > C[key])) key = i;
		}
		else if (C[i] > 0) { key = i; }
	}
	return key;
}
int whatIsLongestWord(char A[25][50], int C[50],int count) {
	int biggest = -1;
	for (int i = 0; i < count; i++) {
		if (biggest >= 0) {
			if (C[i] && (strlen(A[i]) > strlen(A[biggest])))
			{
				biggest = i;
			}
		}
		else if (C[i] > 0) { biggest = i; }
	}
	return biggest;
}
void Paste(char C[25][50],int count) {
	for (int i = 0; i < count; i++) { cout << C[i] << endl; }
}
int SuperCheck(int bigId, int LongId,char A[25][50], int C[50],int count) {
	int leng = strlen(A[LongId]);
	int imp = C[bigId];

	for (int i = 0; i < count;i++) {
		if (C[i] == imp && strlen(A[i]) == leng) return i;
	}
	return -1;
}

int main()
{
	char Arr[25][50];
	int Count[50],count = 0,i = 0,imp, big;
	char str[100] = "";
	FILE* F1;
	F1 = fopen("input.txt","r+");
	FILE* F2;
	// открытие файлов
	if (!F1) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	F2 = fopen("output.txt","w");
	if (!F2) {
		perror("File opening failed");
		return EXIT_FAILURE;
	}
	
	//чтение слов
	while (!feof(F1)) 
	{
		fscanf(F1, "%s", Arr[i]);
		i++;
		count = i;
	}
	
	Paste(Arr, count);//- вывод слов в консоль
	Clear(Count,count);// очистка счетчиков
	toCount(Arr, Count , count); // вычисление кол-ва корневых слов
	imp = whatIsKeyWord(Count,count);// вычисление индекса "Важного слова"
	big = whatIsLongestWord(Arr, Count,count);// вычисление индекса Длинного корневого слова
	int flag = SuperCheck(imp, big, Arr, Count, count); // вычисление одновременно важного и длинного слова
	cout << endl << imp << " " << big << " "<< count<< endl; // полезно бесполезный вывод статистики
	allSubKeyWords(big, Arr, count,str); // запись откорневых слов от самого длинного слова в str
	
	for (int i = 0;i < count;i++) {						
		cout <<Arr[i] << " - " << Count[i] << endl;		//	вывод: Слово - количество
	}			
	
	// выводы в файл
	if (imp != -1) {
		fprintf(F2, "Самое важное корневое слово - %s -  %d\n", Arr[imp],Count[imp]);
	} else fprintf(F2, "Самое важное корневое слово - NO\n");

	if (big != -1) {
		fprintf(F2, "Самое Длинное корневое слово - %s - %s\n", Arr[big],str);
	}
	else fprintf(F2, "Самое Длинное корневое слово - NO\n");
	
	if (flag>-1) {
		fprintf(F2, "Самое Длинное и важное корневое слово %s\n", Arr[flag]);
	}
	else fprintf(F2, "Самое Длинное и важное корневое слово - NO\n");
	
	fclose(F1);
	fclose(F2);

}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
