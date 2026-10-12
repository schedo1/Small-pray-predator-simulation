#include "Lib2.h"

#define M 25
#define N 10

#define dCritica 2.5

using namespace std;

adiacente AdiacenteA(vector <Cell> V, Point A){
		adiacente B = {{A.r, A.c}, {}, false};
		
		for(int i=0; i<V.size(); i++){
			if((V[i].r == A.r) && (V[i].c==A.c-1 || V[i].c==A.c+1)){
				B.boolean = true; B.B = V[i].P;
			} 
			else if((V[i].c == A.c) && (V[i].r==A.r-1 || V[i].r==A.r+1)){
				B.boolean = true; B.B = V[i].P;
			}
		}
	return B;}
void OtoX(vector <Cell> &O, vector <Cell> &X, int i){
	Cell New = O[i]; 
	New.simbolo = X[0].simbolo;
	X.push_back(New);
	
	O.erase(O.begin() + i);
}

bool VuotoSopra(vector <Cell> V, mappa m1, int i){
	if(m1.m[(V[i].r+2+M)%M][V[i].c]==' ' && m1.m[(V[i].r-2+M)%M][V[i].c]==' ' ) return true;
	return false;}
void MeccanismoDiDifesa(vector <Cell> &O, vector <Cell> &Temporaneo, int i){
		
	Cell New = O[i];	
	New.r = (New.r -2 + M)%M;
	New.cooldown = -5;
	Temporaneo.push_back(New);
	
	New = O[i];
	New.cooldown = -5;
	New.r = (New.r +2 + M)%M;
	Temporaneo.push_back(New);	
}

int DaCoordinateToIndice(vector <Cell> V, Point V1){
	for(int i=0; i<V.size(); i++) 
		if(V[i].r == V1.r && V[i].c == V1.c) return i;}

int main(){
	srand(time(0));
	mappa m1(M);
	
	Cell O1('O', 1, 1);  Cell X1('X', 1, 1);
	Point p0 = {0, 0};
	
	vector <Cell> O(N, (O1));  vector <Cell> X(N, (X1)); //
	vector <Point> Coordinate(O.size()*2, (p0));
	
	for(int i=0; i<Coordinate.size(); i++){ //inizializzo coordinate
		do{
			Coordinate[i].r = random(0, m1.dimm-1);
			Coordinate[i].c = random(0, m1.dimm-1);
		}while(Diverso(Coordinate, Coordinate[i], i));
	}
	for(int i=0; i<O.size(); i++){
		O[i].r = Coordinate[i].r;
		O[i].c = Coordinate[i].c;
		O[i].P.r = O[i].r;
		O[i].P.c = O[i].c;
		m1.add(O[i].r, O[i].c, 'O');
	}
	for(int i=0; i<X.size(); i++){
		X[i].r = Coordinate[i+O.size()].r;
		X[i].c = Coordinate[i+O.size()].c;
		X[i].P.r = X[i].r;
		X[i].P.c = X[i].c;
		m1.add(X[i].r, X[i].c, 'X');
	}
	
	vector <Cell> Temporaneo;
	
	for(int t=0; true; t++){
		//sub vecchi
		for(int i=0; i<O.size(); i++) m1.sub(O[i].r, O[i].c); 
		if(t%2==0) for(int i=0; i<X.size(); i++) m1.sub(X[i].r, X[i].c);
		
		//funzioni supplementari
		for(int i=0; i<O.size(); i++) if(AdiacenteA(X, O[i].P).boolean){OtoX(O, X, i); i--;} 
		for(int i=0; i<O.size(); i++){
			for(int j=0; j<X.size(); j++) 
				if(d(O[i].P, X[j].P, M)<dCritica 
				&& VuotoSopra(O, m1, i) && O[i].cooldown == 0){
					MeccanismoDiDifesa(O, Temporaneo, i);	
					O[i].cooldown = -5;											
				}
		}
		for(int i=0; i<Temporaneo.size(); i++) O.push_back(Temporaneo[i]);
		Temporaneo = {}; 
		if(t%2==0) for(int i=0; i<X.size(); i++) if(!(rand()%10) && O.size()==0){OtoX(X, O, i); i--;}  
		
		//O adiacenti a O
		for(int i=0; i<O.size(); i++){
			adiacente a = AdiacenteA(O, O[i].P);
			if(a.boolean){
				int j = DaCoordinateToIndice(O, a.B);
				m1.sub(O[i].r, O[i].c); O.erase(O.begin() + max(i, j)); 
				m1.sub(O[j].r, O[j].c); O.erase(O.begin() + min(i, j));
				i = min(i, j) - 1;
			}
		}
		//X adiacenti a X
		for(int i=0; i<X.size(); i++){
			adiacente a = AdiacenteA(X, X[i].P);
			if(a.boolean){
				int j = DaCoordinateToIndice(X, a.B);
				m1.sub(X[i].r, X[i].c); X.erase(X.begin() + max(i, j)); 
				m1.sub(X[j].r, X[j].c); X.erase(X.begin() + min(i, j));
				i = min(i, j) - 1;
			}
		}
		
		//direzioni
/*O*/	for(int i=0; i<O.size(); i++) O[i].CambiaDirezione(5, X, O, i);	
/*X*/	if(t%2==0) for(int i=0; i<X.size(); i++) X[i].CambiaDirezione(4, X, i, O);
		
		//move e add	
		for(int i=0; i<O.size(); i++){ 
			O[i].move(m1); m1.add(O[i].r, O[i].c, 'O', 36);
		} 
		if(t%2==0) for(int i=0; i<X.size(); i++){ 
			X[i].move(m1); m1.add(X[i].r, X[i].c, 'X', 31); 
		} 
		m1.print();
		gotoxy(0,0);
		Sleep(250); //125
		
		for(int i=0; i<O.size(); i++) if(O[i].cooldown<0) O[i].cooldown++;
	}
	
	return 0;}
