/*
SociallyAwake
Manish Kumar Srivastava
*/
#pragma region headers
//Basic Necessities
#include<iostream>
#include<cassert>
#include<algorithm>
#include<numeric>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<ctime>
#include<cctype>
#include<bitset>
#include<fstream>
#include<tuple>
//C++ templates
#include<queue>
#include<deque>
#include<stack>
#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<map>
#include<unordered_map>
// 
#include <boost/graph/vf2_sub_graph_iso.hpp>
#include <boost/graph/graph_utility.hpp>
#include <boost/graph/adjacency_list.hpp>  
// 
#pragma endregion
#pragma region shortcuts
//Shortcuts
#define MAX (ll)1e18+7
#define MIN (ll)-1e18-7
#define N (ll)1e5+7
#define M (ll)1e6+7
#define mid (l+r)/2
#define outl(a) printf("%lld\n",a)
#define outs(a) printf("%lld ",a)
#define out(a)  printf("%lld",a)
#define mod 1000000007
#define mem(a) memset(a,0,sizeof(a))
#define all(a) a.begin(),a.end()
#define mp(a,b) make_pair(a,b)
#define ll long long int
using namespace std;
using namespace boost;
#pragma endregion
 

// Define edge and vertex properties
typedef property<edge_name_t, int> edge_t;
typedef property<vertex_name_t, int, property<vertex_index_t, int> > vertex_t;

// Using a vecS graphs => the index maps are implicit.
typedef adjacency_list<vecS, vecS, undirectedS, vertex_t, edge_t> graph_t;

// Create the vertex binary predicate
typedef property_map<graph_t, vertex_name_t>::type vertex_name_map_t;
typedef property_map_equivalent<vertex_name_map_t, vertex_name_map_t> vertex_comp_t;

// Create the vertex binary predicate
typedef property_map<graph_t, edge_name_t>::type edge_name_map_t;
typedef property_map_equivalent<edge_name_map_t, edge_name_map_t> edge_comp_t;
