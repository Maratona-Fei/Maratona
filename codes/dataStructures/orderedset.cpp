///* 
//ordered set
//
//descricao:
//	set normal, mas deixa fazer perguntas sobre posicao.
//	o multiset permite a insercao de varios valores iguais. 
//	so colocar um inteiro nadave no .s.
//	insert, erase, begin, end, clear, size;
//	find_by_order(i): iterador pro elemento na posicao i;
//	order_of_key(i): quantidade de valores menores que i;
//
//complexidades:
//	tudo log(n);
//*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using ordered_set = tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update>;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template <class T>
using ordered_multiset = tree<pair<T, int>, null_type, less<pair<T, int>>, rb_tree_tag, tree_order_statistics_node_update>;

