#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;
 
void loadResult();
void loadMatrix();
int table[9][9];

int printMatrix();

int main()
{
	int i, j, k, l, m, n;
	
	loadMatrix();
	printMatrix();
	ofstream constraintFile;
	constraintFile.open ("sudoku.prop");
	
	//-----------------------------------------------------------------------------------------
	/* First set the inputs*/
	for(i = 0; i < 9; i++){
		for(j = 0; j < 9; j++){
			if(table[j][i]!=0){
				constraintFile << "s" << i + 1<< j + 1 << table[j][i] << "&" << endl;
			}
		}
	}

	//-----------------------------------------------------------------------------------------
	/* Each square should contain a number from 1 to 9, which means: for all i, j: Sij1 = 1 or Sij2 = 1 or.... */
	constraintFile << endl;
	for(i = 1; i <= 9; i++){
		for(j = 1; j <= 9; j++){
			constraintFile << "(";
			for(k = 1; k<= 9; k++){
				
				constraintFile << "s" << i << j << k;
				if(k!=9){
					constraintFile << "|";
				}
			}
			if(i!=9||j!=9){
				constraintFile << ")&" << endl;
			}else{
				constraintFile << ")" << endl;
			}
		}
	}
	//-----------------------------------------------------------------------------------------
	constraintFile << endl;
	constraintFile << "&" << endl;
	constraintFile << endl;
	//-----------------------------------------------------------------------------------------
	/* Each square should contain only one number,  which means for  each square, if Sijk = 1, then for all n != k, Sijn = 0 */
	for(i = 1; i<=9; i++){
		for(j = 1; j <= 9; j++){
			constraintFile << "(";
			for(k = 1; k<= 9; k++){
				constraintFile << "(s" << i << j << k << "<->~(";
				
				for(l=1; l<k; l++){
					constraintFile << "s" << i << j << l;
					if(l!=8){
						constraintFile << "|";
					}
				}
				for(l=k+1;l<=9;l++){
					constraintFile << "s" << i << j << l;
					if(l!=9){
						constraintFile << "|";
					}
				}
				
				if(k!=9){
					constraintFile << "))&" <<endl;
				}else{
					constraintFile << "))" <<endl;
				}
			}
			if(i!=9||j!=9){
				constraintFile << ")&" << endl;
			}else{
				constraintFile << ")" << endl;
			}
		}
	}
	//-----------------------------------------------------------------------------------------
	constraintFile << endl;
	constraintFile << "&" << endl;
	constraintFile << endl;
	//-----------------------------------------------------------------------------------------
	/* Each number appears at most once per row, if Sijk = 1, then for all n!=i, Snjk = 0 */
	for(j = 1; j<=9; j++){
		for(k = 1; k <= 9; k++){
			constraintFile << "(";
			for(i = 1; i<= 9; i++){
				constraintFile << "(s" << i << j << k << "<->~(";
				
				for(l=1; l<i; l++){
					constraintFile << "s" << l << j << k;
					if(l!=8){
						constraintFile << "|";
					}
				}
				for(l=i+1;l<=9;l++){
					constraintFile << "s" << l << j << k;
					if(l!=9){
						constraintFile << "|";
					}
				}
				
				if(i!=9){
					constraintFile << "))&" <<endl;
				}else{
					constraintFile << "))" <<endl;
				}
			}
			if(k!=9||j!=9){
				constraintFile << ")&" << endl;
			}else{
				constraintFile << ")" << endl;
			}
		}
	}
	//-----------------------------------------------------------------------------------------
	constraintFile << endl;
	constraintFile << "&" << endl;
	constraintFile << endl;
	//-----------------------------------------------------------------------------------------
	/* Each number appears at most once per column, if Sijk = 1, then for all n!=j, Sink = 0 */
	for(i = 1; i<=9; i++){
		for(k = 1; k <= 9; k++){
			constraintFile << "(";
			for(j = 1; j<= 9; j++){
				constraintFile << "(s" << i << j << k << "<->~(";
				
				for(l=1; l<j; l++){
					constraintFile << "s" << i << l << k;
					if(l!=8){
						constraintFile << "|";
					}
				}
				for(l=j+1;l<=9;l++){
					constraintFile << "s" << i << l << k;
					if(l!=9){
						constraintFile << "|";
					}
				}
				
				if(j!=9){
					constraintFile << "))&" <<endl;
				}else{
					constraintFile << "))" <<endl;
				}
			}
			if(k!=9||i!=9){
				constraintFile << ")&" << endl;
			}else{
				constraintFile << ")" << endl;
			}
		}
	}
	//-----------------------------------------------------------------------------------------
	constraintFile << endl;
	constraintFile << "&" << endl;
	constraintFile << endl;
	//-----------------------------------------------------------------------------------------
	/* Each number appears at most once per small square, if Sijk = 1, then for all n and m in this square such as n!=i and m!=j, Snmk = 0 */
	int smallSquareI = 0;
	int smallSquareJ = 0;
	for(i = 1; i<=9; i++){
		for(j = 1; j <= 9; j++){
			constraintFile << "(";
			for(k = 1; k<= 9; k++){
				constraintFile << "(s" << i << j << k << "<->~(";
				smallSquareI = (i - 1) / 3;
				smallSquareJ = (j - 1) / 3;
				for(l = 0; l < 3; l++){
					for(m = 0; m < 3; m++){
						if(l + smallSquareI * 3 + 1 != i || m + smallSquareJ * 3 + 1 != j){
							constraintFile << "s" << l + smallSquareI * 3 + 1 << m + smallSquareJ * 3 + 1 << k;
							
							if(l==2 && m==1){
								if(!(i - smallSquareI * 3 == 3 && j - smallSquareJ * 3 == 3)){
									constraintFile << "|";
								}
							}else{
								if(!(l==2 && m==2)){
									constraintFile << "|";
								}
							}
							
					
						}
						
						
					}
				}		
				if(k!=9){
					constraintFile << "))&" <<endl;
				}else{
					constraintFile << "))" <<endl;
				}
			}
			if(i!=9||j!=9){
				constraintFile << ")&" << endl;
			}else{
				constraintFile << ")" << endl;
			}
		}
	}
	
	constraintFile.close();
	
	system("cmd.exe /c \"D:\\AI\\Satzoo\\Satzoo.exe\" \"sudoku.prop\" \"-print-model=1\" > \"result.txt\"");
	
	loadResult();
	printMatrix();
	
	string stop;
	getline(cin,stop,'\n');
	
	return 0;

}

void loadResult(){
	// Open a stream
	ifstream file;
	string fileName ="result.txt";
	file.open(fileName.c_str());
	if (!file){
		cout << "Error in openening file";
		return;
	}
	
	string lineread;
	int value;
	int i,j;
	while(lineread != "SATISFIABLE"){
		getline(file, lineread);
	}
	getline(file, lineread,'s');
	while(getline(file, lineread,'s')){

		value = atoi(lineread.c_str());

		i = value /100;
		value -= 100*i;
		j = value / 10;
		value -= 10 * j;
		table[j-1][i-1] = value;
	}

}

void loadMatrix(){
	// Open a stream
	ifstream file;
	string fileName ="matrix.txt";
	file.open(fileName.c_str());
	if (!file){
		cout << "Error in openening file";
		return;
	}
	
	string lineread;
	int value;
	int i,j;
	i = 0;
	j = 0;
	
	while(std::getline(file, lineread,',')){

		value = atoi(lineread.c_str());

		table[j][i]=value;
		i++;
		if(i==9){
			i = 0;
			j++;
		}

	}

}

int printMatrix(){
	int i, j;
	
	printf(" -----------------------------\n");
	
	for(j=0;j<9;j++){

		printf("|");
		for(i=0;i<9;i++){
			if(table[j][i] == 0){
				printf("   ");
			}else{
				printf(" %d ", table[j][i]);
			}
			if(i==2 || i == 5) printf("|");
		}
		
		printf("|\n");
		if(j == 2 || j == 5 || j==8){
			printf(" ----------------------------- \n");
		}else{
			printf("|         |         |         |\n");
		}
	}
	return 0;
}
