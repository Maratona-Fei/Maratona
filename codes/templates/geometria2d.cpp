typedef double T;
 //i just wanna be part of your sinphony
const double eps = 1e-9;
const double pi = acos((double)-1.0);

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

struct line {
	pt a, b;//vai do ponto A ao B
	pt v; T c;//direcao do vetor [cross] (x, y) = c	

	line() {}

	line(pt v, T c) : v(v), c(c) {
		auto p = get_points();
		a = p.f; b = p.s;
	}
	//eq ax + by + c = 0
	line(T _a, T _b, T, T _c) : v({_b, -_a}), c(-_c) {
		auto p = get_points();
		a = p.f; b = p.s;
	}
	//passa pelos pontos p e q
	line(pt p, pt q) : v(q-p), c(cross(v, p)), a(p), b(q) {}
	pair<pt , pt> get_points() { //extrai qualquer dois pontos dessa linha
	pt p, q; T a = -v.y, b = v.x; //ax+by = c
	if(sign(a) == 0) {
		p = pt(0, c/b);
		q = pt(1, c/b);
	}
	else if(sign(b) == 0) {
		p = pt(c/a, 0);
		q = pt(c/a, 1);
	}
	else {
		p = pt(0, c/b);
		q = pt(1, (c-a)/b);
	}

	return {p, q};
	}

	//ax + by + c = 0
	array<T, 3> get_abc() {
		T a = -v.y, b = v.x;
		return {a, b, -c};
	}

	//1 se esta na esquerda, -1 se esta na direita, 0 se estiver na linha
	int side(pt p) {return sign(cross(v, p) -c);}
	//reta perpendicular a esta e passa pelo ponto p
	line perpendicular_through(pt p) {return {p, p+perp(v)};}
	//faz a translacao da linha pelo vetor t i.e fznd o shift com o vetor t
	line translate(pt t) {return {v, c+cross(v, t)};}
	//compara dois pontos com suas proj. ortogonais nessa linha
	//um ponto de projecao vem antes de outro se vier primeiro de acordo com o vetor
	bool cmp_by_projection(pt p, pt q) {return dot(v, p) < dot(v, q);}
	line shift_left(T d) {
		pt z = v.perp().truncate(d);
		return line(a+z, b+z);
	}
};

//encontra um ponto de A ate B com distancia d
pt point_along_line(pt a, pt b, T d) {
	assert(a != b);
	return a + (((b - a) / (b - a).norm()) * d);
}
//projecao do ponto c na linha que passa por A e B 
//assumindo que A!=B
pt project_from_point_to_line(pt a, pt b, pt c) {
	return a + (b - a) * dot(c - a, b - a) / (b - a).norm2();
}
//ponto de reflexao C que passa na linha que passa por A e B
//assumindo que A!=B
pt reflection_from_point_to_line(pt a, pt b, pt c) {
	pt p = project_from_point_to_line(a, b, c);
	return p + p - c;
}
//dist min do ponto  ate a linha que passa por A e B
T dist_from_point_to_line(pt a, pt b, pt c) {
	return fabs(cross(b - a, c - a) / (b - a).norm());
}
//retorna true se o ponto P pertence ao segmento AB
bool is_point_on_seg(pt a, pt b, pt p) {
	if(fabs(cross(p - b, a - b)) < eps) {
		if(p.x < min(a.x, b.x) - eps or p.x > max(a.x, b.x) + eps) return false;
		if(p.y < min(a.y, b.y) - eps or p.y > max(a.y, b.y) + eps) return false;
		return true;
	}
	return false;

}
//pont com dist min de um ponto c ate o seg AB que pertence ao seg AB
pt project_from_point_to_seg(pt a, pt b, pt c) {
	T r = dist2(a, b);
	if(sign(r) == 0) return a;
	r = dot(c - a, b - a) / r;
	if(r < 0) return a;
	if(r > 1) return b;
	return a + (b - a) * r;
}
//dist min de um ponto c ate um seg AB
T dist_from_point_to_seg(pt a, pt b, pt c) {
	return dist(c, project_from_point_to_seg(a, b, c));
}

// 0 se nao eh paralelo, 1 se eh paralelo, 2 se eh colinear
int is_parallel(pt a, pt b, pt c, pt d) {
	T k = fabs(cross(b - a, d - c));
	if(k < eps) {
		if(fabs(cross(a - b, a - c)) < eps and fabs(cross(c - d, c - a)) < eps) return 2;
		else return 1;
	}
	else return 0;
}
//checa se duas linhas sao as mesmas
bool are_lines_same(pt a, pt b, pt c, pt d) {
	if(fabs(cross(a - c, c - d)) < eps and fabs(cross(b - c, c - d)) < eps) return true;
	return false;
}
//vetor bissetriz de <abc
pt angle_bisector(pt& a, pt& b, pt& c) {
	pt p = a - b, q = c - b;
	return p + q * sqrt(dot(p, p) / dot(q, q));
}
//1 se o ponto eh ccw com a linha, 2 se o ponto eh cw da linha
//3 se o ponto esta na linha
int point_line_relation(pt a, pt b, pt p) {
	int c = sign(cross(p - a, b - a));
	if(c < 0) return 1;
	if(c > 0) return 2;
	return 3;
}
//ponto de intersec entre uma linha AB e uma linha CD 
//assumindo que existe apenas uma intersec
bool line_line_intersection(pt a, pt b, pt c, pt d, pt& ans) {
	T a1 = a.y - b.y, b1 = b.x - a.x, c1 = cross(a, b);
	T a2 = c.y - d.y, b2 = d.x - c.x, c2 = cross(c, d);
	T det = a1 * b2 - a2 * b1;
	if(det == 0) return 0;
	ans = pt((b1 * c2 - b2 * c1) / det, (c1 * a2 - a1 * c2) / det);
	return 1;
}
//ponto de intersec entre um seg AB e um seg CD 
//assumindo que existe apenas uma intersec
bool seg_seg_intersection(pt a, pt b, pt c, pt d, pt& ans) {
	T oa = cross2(c, d, a), ob = cross2(c, d, b);
	T oc = cross2(a, b, c), od = cross2(a, b, d);
	if(oa * ob < 0 and oc * od < 0) {
		ans = (a * ob - b * oa) / (ob - oa);
		return 1;
	}
	else return 0;
}
//ponto de intersec entre um seg AB e um seg CD 
//assumindo que poder ter mais de uma intersec
//se.size() == 0, sem intersecs
//se.size() == 1, uma intersec
//se.size() == 2, possui um intervalo de intersecs
set<pt> seg_seg_intersection_inside(pt a, pt b, pt c, pt d) {
	pt ans;
	if(seg_seg_intersection(a, b, c, d, ans)) return {ans};
	set<pt> se;
	if(is_point_on_seg(c, d, a)) se.insert(a);
	if(is_point_on_seg(c, d, b)) se.insert(b);
	if(is_point_on_seg(a, b, c)) se.insert(c);
	if(is_point_on_seg(a, b, d)) se.insert(d);

	return se;
}
//intersec entre seg AB e linha CD
//0 se nao se intersec, 1 se houver intersec adequada, 2 se o seg intersecta
int seg_line_relation(pt a, pt b, pt c, pt d) {
	T p = cross2(c, d, a);
	T q = cross2(c, d, b);
	if(sign(p) == 0 and sign(q) == 0) return 2;
	else if(p * q < 0) return 1;
	else return 0;
}
//intersec entre seg AB e linha CD 
//assumindo uma unica intersec
bool seg_line_intersection(pt a, pt b, pt c, pt d, pt& ans) {
	bool k = seg_line_relation(a, b, c, d);
	assert(k != 2);
	if(k) line_line_intersection(a, b, c, d, ans);
	return k;
}
//dist min de um seg AB e um seg CD
T dist_from_seg_to_seg(pt a, pt b, pt c, pt d) {
	pt dummy;
	if(seg_seg_intersection(a, b, c, d, dummy)) return 0.0;
	return min({dist_from_point_to_seg(a, b, c), dist_from_point_to_seg(a, b, d), dist_from_point_to_seg(c, d, a), dist_from_point_to_seg(c, d, b)});
}
//dist min de um ponto c ate o raio
//(comecando do ponto a e direcao do vetor b)
T dist_from_point_to_ray(pt a, pt b, pt c) {
	b = a + b;
	T r = dot(c - a, b - a);
	if(r < 0.0) return dist(c, a);
	return dist_from_point_to_line(a, b, c);
}
//comecando ponto as e direcao do vetor ad
bool ray_ray_intersection(pt as, pt ad, pt bs, pt bd) {
	T dx = bs.x - as.x, dy = bs.y - as.y;
	T det = bd.x * ad.y - bd.y * ad.x;
	if(fabs(det) < eps) return 0;
	T u = (dy * bd.x - dx * bd.y) / det;
	T v = (dy * ad.x - dx * ad.y) / det;
	if(sign(u) >= 0 and sign(v) >= 0) return 1;
	else return 0;
}
double ray_ray_distance(pt as, pt ad, pt bs, pt bd) {
	if(ray_ray_intersection(as, ad, bs, bd)) return 0.0;
	T ans = dist_from_point_to_ray(as, ad, bs);
	ans = min(ans, dist_from_point_to_ray(bs, bd, as));
	return ans;
}

// retorna a area de um poligono
T area(vector<pt>& v){
	T ans = 0; int n = v.size();

	for(int i = 0; i < n; i++) ans += cross(v[i], v[(i+1)%n]);
	return fabs(ans) * 0.5;
}
