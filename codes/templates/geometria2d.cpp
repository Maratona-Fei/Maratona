#include <bits/stdc++.h>

using namespace std;

#define _ ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'

#define f first
#define s second

#define vi vector<int>
#define grafo vector<vector<int>>

#define dbg(x) cout << #x << " = " << x << endl;

typedef long long ll;
typedef double T;

const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const double eps = 1e-9;
const double pi = acos((double)-1.0);

/*
Para trabalhar com nums complexos
typedef complex<T> pt;
#define x real()
#define y imag()
*/

// Funcao q retorna -1 para nums negativos, 0 para zero e 1 para positivos
int sign(double x) {return (x > eps) - (x < -eps);}

struct pt{
	T x, y;
	
	pt(T x, T y) : x(x), y(y) {}
	pt() {x=0,y=0;}
	pt operator+(pt p) {return {x+p.x, y+p.y};}
	pt operator-(pt p) {return {x-p.x, y-p.y};}
	pt operator*(T d) {return {x*d, y*d};}
	pt operator/(T d) {return {x/d, y/d};}
	bool operator==(pt a) const {return sign(a.x - x) == 0 and sign(a.y - y) == 0;}
	bool operator!=(pt a) const {return !(*this == a);}
	bool operator<(pt a) const {return sign(a.x - x) == 0 ? y < a.y : x < a.x;}
	bool operator>(pt a) const {return sign(a.x - x) == 0 ? y > a.y : x > a.x;}
	double norm() {return sqrt(x*x + y*y);}
	double norm2() {return x*x + y*y;}
	pt perp() {return pt(-y, x);}
	double arg() {return atan2(y, x);}
	T polarAngle(){
			double angle = atan2(y, x);//Computa ang em rad
			if(angle < 0) angle+=2*pi;//ajusta para [0,2pi]
			return angle;
		}
	pt truncate(double r){// retorna um vetor de normal r e de mesma direcao
		double k = norm();
		if(!sign(k)) return *this;
		r /= k;
		return pt(x*r, y*r);
	}
};

pt operator*(T a, pt b) {return a*b;}

// Declarao para facilitar entradas
istream& operator>>(istream &in, pt &p){return in>>p.x>>p.y;}
// Declaracao para facilitar debugs
ostream& operator<<(ostream& os, pt p){return os << '(' << p.x << ',' << p.y << ')';}

inline T dot(pt a, pt b) {return a.x*b.x + a.y*b.y;}

inline T dist2(pt a, pt b) {return dot(a-b, a-b);}

inline T dist(pt a, pt b) {return sqrt(dot(a-b, a-b));}

double abs(pt p) {return sqrt(p.norm());}

double proj(pt a, pt b) {return dot(a, b) / abs(b);}

inline T cross(pt a, pt b){ return a.x*b.y - a.y*b.x;}

inline T cross2(pt a, pt b, pt c) {return cross(b-a, c-a);}

// Prod vet AB x AC
// > 0 -> esquerda | == 0 -> colineres | < 0 direita
inline T orient(pt a, pt b, pt c) {return sign(cross(b-a, c-a));}

T sq(double x) {return x*x;}

T rad_to_deg(double r) {return (r * 180.0 / pi);}

T deg_to_rad(double d) {return (d*pi/ 180.0);}

/*
Se complex 
T dot(pt v, pt w) {return (conj(v)*w).x;}
T cross(pt v, pt w) {return (conj(v)*w).y;}
*/


double angle(pt a, pt b){
	double cosTheta = dot(a, b) / a.norm() / b.norm();
	return acos(max(-1.0, min(1.0, cosTheta)));
}

double orientedAngle(pt a, pt b, pt c){
	if(orient(a, b, c) >= 0)
		return angle(b-a, c-a);
	else
		return 2*pi - angle(b-a, c-a);
}

bool isPerp(pt v, pt w) {return dot(v, w) == 0;}

bool isAngle(pt a, pt b, pt c, pt p){
	assert(orient(a, b, c) != 0);
	if(orient(a, b, c) < 0) swap(b, c);
	return orient(a, b, p) >= 0 and orient(a, c, p) <= 0;
}


// Retorn true plano superior
bool half(pt p){
	return p.y > 0.0 or (p.y == 0.0 and p.x < 0.0);
}

pt translate(pt v, pt p) {return p+v;}

pt scale(pt c, double factor, pt p){
	return c + (p-c)*factor;
}

pt rotateccw90(pt a) {return pt(-a.y, a.x);}

pt rotatecw90(pt a) {return pt(a.y, -a.x);}

pt rotateccw(pt a, double t){return {a.x*cos(t) - a.y*sin(t), a.x*sin(t) + a.y*cos(t)};}

pt rotatecw(pt a, double t){return {a.x*cos(t) + a.y*sin(t), -a.x*sin(t) + a.y*cos(t)};}

pt linearTranfo(pt p, pt q, pt r, pt fp, pt fq){
	pt pq = q-p, num{cross(pq, fq-fp), dot(pq, fq-fp)};
	return fp + pt{cross(r-p, num), dot(r-p, num)} / pq.norm();
}

pt lineIntersection(pt a1, pt b1, pt a2, pt b2){
	return a1 + cross(a2 - a1, b2) / cross(b1, b2) * b1;
}

pt perp(pt a) {return pt(-a.y, a.x);}

void polarSort(vector<pt> &v){ // Sort antiHorario
	sort(v.begin(), v.end(), [](pt a, pt b){
		return make_tuple(half(a), 0.0, a.norm2()) < 
			   make_tuple(half(b), cross(a, b), b.norm2());
	});
}

void polarSort(vector<pt>& v, pt o){ // Sort antiHorario
	sort(v.begin(), v.end(), [&](pt a, pt b){ // pensando no pt o
		return make_tuple(half(a-o), 0.0, (a-o).norm2()) <
			   make_tuple(half(b-o), cross(a-o, b-o), (b-o).norm2());
		});
}

// Verifica se o poligono e convexo
// Verifica a orientacao de 3 em 3 pt
// para ser convexo todos os 'orient' devem
// ser somente >= 0 ou <= 0
bool isConvex(vector<pt> p){
	bool hasPos = false, hasNeg = false;
	int n = p.size();
	for(int i=0; i<n; i++){
		int o = orient(p[i], p[(i+1)%n], p[(i+2)%n]);
		if(o > 0) hasPos = true;
		if(o < 0) hasNeg = true;
	}

	return !(hasPos and hasNeg);
}
int main(){ _
	return 0;
}
