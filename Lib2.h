#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<time.h>
#include<windows.h>
#include<algorithm> 
#define M 25

using namespace std;

int random(int a, int b){
	int n[2];
	if(a>=b){
		n[1] = a;
		n[0] = b;
	}
	else{
		n[1] = b;
		n[0] = a;
	}
		
	int s = rand()%(n[1]-n[0]+1);
	s=s+n[0];
	return s;}
void gotoxy(int x, int y){
    COORD coord;
    coord.X = x; coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void Cout(char str, int colore){
	cout<<"\x1b["<<colore<<"m"<<str<<"\x1b[37m"<<" ";
}

struct Point{
	int r, c;
};
bool Diverso(vector <Point> P, Point p1, int n){
	for(int i=0; i<P.size(); i++){
		if(P[i].r == p1.r && P[i].c == p1.c && i!=n) return true;
	}
	return false;}
int d(Point a, Point b, int dimm){
	int dr = abs(a.r - b.r); //distanza normale
    int dc = abs(a.c - b.c); 
	
    return min(dr, dimm-dr) + min(dc, dimm-dc);}

struct CaratteristichePericolo{
	Point P;
	int i, d;
};
struct adiacente{
	Point A, B;
	bool boolean;
};

class mappa{
public:
	vector <vector <char> > m;
	vector <vector <int> > m2;
	int dimm;

	mappa(int dimm){
		this->dimm = dimm;
		m = vector <vector <char> > (dimm, vector <char> (dimm));
		m2 = vector <vector <int> > (dimm, vector <int> (dimm));
		for(int i=0; i<dimm; i++){
			for(int j=0; j<dimm; j++){
				m[i][j]=' ';
				m2[i][j]=37;
			} 
		}
	}	
	void print(){
		cout<<"+";
		for(int i=0; i<m.size(); i++){
			cout<<"--";
		} cout<<"+\n";
		
		for(int i=0; i<m.size(); i++){
			cout<<"|";
			for(int j=0; j<m[i].size(); j++){
				Cout(m[i][j], m2[i][j]);
			} cout<<"|\n";
		}
		
		cout<<"+";
		for(int i=0; i<m.size(); i++){
			cout<<"--";
		} cout<<"+\n";
	}	
			
	void add(int r, int c, char s, int color){
		this->m[r][c] = s;
		this->m2[r][c] = color;
	}
	void add(int r, int c, char s){
		this->m[r][c] = s;
		this->m2[r][c] = 37;
	}
	void sub(int r, int c){
		this->m[r][c] = ' ';	
		
	}
};
class Cell{
public:
	int r, c, vr, vc;		
	char simbolo;
	Point P; 
	int cooldown;
	
	Cell(char ch, int vr, int vc){
		this->simbolo=ch;
		this->vr = vr;
		this->vc = vc;
		cooldown = -5;
	}
	Cell(){
		
	}
	void move(mappa m1){
		if(m1.m[(r + vr + m1.dimm)%m1.dimm][(c + vc + m1.dimm)%m1.dimm]==' '){
			int MoltV = (this->simbolo=='O') ? 2 : 1;
			
			r = (r + vr*MoltV + m1.dimm)%m1.dimm;
    		c = (c + vc*MoltV + m1.dimm)%m1.dimm;
    		P.r = r; P.c = c;	
		}
		else{
			r = r;
			c = c;
			P.r = r; 
			P.c = c;
		}
    	
	}

private:
	
	void ScappaDa(int distanza, vector <Cell> Pericolo) {
	
    	P.r = r; P.c = c;
    	int sommaDistanze[8] = {};
		
		Point drdc[8] = {
			{-1, -1}, {-1, 0}, {-1, 1},
			{0,  -1},          {0,  1},
			{1,  -1}, {1,  0}, {1,  1}
		};
 		random_shuffle(drdc, drdc+8);
		
		vector <CaratteristichePericolo> caratteristiche(Pericolo.size());
		for(int i=0; i<Pericolo.size(); i++){
			caratteristiche[i].P = Pericolo[i].P;
			caratteristiche[i].d = d(this->P, Pericolo[i].P, M);
			caratteristiche[i].i = i; 
		}
		
		sort(caratteristiche.begin(), caratteristiche.end(),
			[](const CaratteristichePericolo& a, const CaratteristichePericolo& b) {	
        	return a.d > b.d;
    	});
		for(int i=0; i<caratteristiche.size(); i++){
			if(caratteristiche[i].d>distanza){
				caratteristiche.erase(caratteristiche.begin() + i);
				i--;	
			} 
		}
		
    	for(int i=0; i<8; i++) {

        	Point futuro;
        	futuro.r = (r + drdc[i].r + M)%M;
        	futuro.c = (c + drdc[i].c + M)%M;

        	for(int z = 0; z < caratteristiche.size(); z++) {
            	sommaDistanze[i] += d(futuro, caratteristiche[z].P, M);		
        	}
    	}	

    	int iMax = 0;

    	for(int i = 1; i < 8; i++) {
        	if(sommaDistanze[i] > sommaDistanze[iMax]) {
            	iMax = i;
        	}
    	}
		vr = drdc[iMax].r;
    	vc = drdc[iMax].c;
			
	}
	void ScappaDa(int distanza, vector <Cell> Pericolo, int j){
		vector <Cell> Pericolo1;
		
		Pericolo1.reserve(Pericolo.size() - 1); //alloco spazio in memoria preventivamente
		for(int i = 0; i < Pericolo.size(); i++) {
    		if(i != j) {
       			Pericolo1.push_back(Pericolo[i]);
    		}
		}
		ScappaDa(distanza, Pericolo1);
	}
	
	void AttrattoDa(vector <Cell> Obbiettivo){
		if (Obbiettivo.empty()) return;
		
		vector <CaratteristichePericolo> caratteristiche;
		caratteristiche.reserve(Obbiettivo.size());
		
		CaratteristichePericolo C1;
		for(int i=0; i<Obbiettivo.size(); i++){ //inizializzo il vector di caratteristiche 
			C1.P = Obbiettivo[i].P;
			C1.d = d(this->P, Obbiettivo[i].P, M);
			C1.i = i; 
			
			caratteristiche.push_back(C1);
		}
		
		int dMin=caratteristiche[0].d; int iMin=0;
		for(int i=0; i<caratteristiche.size(); i++){ //trovo il piu vicino
			if(caratteristiche[i].d < dMin){
				dMin = caratteristiche[i].d;
				iMin = i;
			}  
		}
	
		int dr, dc;
		dr = Obbiettivo[iMin].P.r - r;
		dc = Obbiettivo[iMin].P.c - c;
		
		if(dr<0) vr=-1;
		else if(dr>0) vr=1;
		else vr = 0;
		
		if(dc<0) vc=-1;
		else if(dc>0) vc=1;
		else vc = 0;
	}
	void AttrattoDa(vector <Cell> Obbiettivo, int j){
		vector <Cell> Obbiettivo1;
		
		Obbiettivo1.reserve(Obbiettivo.size() - 1); //alloco spazio in memoria preventivamente
		for(int i = 0; i < Obbiettivo.size(); i++) {
    		if(i != j) {
       			Obbiettivo1.push_back(Obbiettivo[i]);
    		}
		}
		AttrattoDa(Obbiettivo1);
	}
	
public: 	
	
	void CambiaDirezione(int d1, vector <Cell> Pericolo, int i, vector <Cell> Obbiettivo){
		AttrattoDa(Obbiettivo);	
		ScappaDa(d1, Pericolo, i);
	}
	void CambiaDirezione(int d1, vector <Cell> Pericolo, vector <Cell> Obbiettivo, int i){
		AttrattoDa(Obbiettivo, i);	
		ScappaDa(d1, Pericolo);
	}

};


