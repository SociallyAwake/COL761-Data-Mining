#include<fstream>
#include<iostream>
#include<sstream>
#include<vector>
#include <cfloat>
#include <cmath>
using namespace std;


ofstream outfile2;
ofstream outfile3;
ofstream outfile4;

// 2D points
struct Point2D{

double XX,YY;
int cluster;
double minDist;

Point2D():
 XX(0.0),
 YY(0.0),
 cluster(-1),
 minDist(DBL_MAX) {}

Point2D(double XX, double YY):
 XX(XX),
 YY(YY),
 cluster(-1),
 minDist(DBL_MAX) {}
 
double distance(Point2D P)
{
return (P.XX -XX) * (P.XX-XX) + (P.YY -YY) * (P.YY -YY);
}
};

// 3D Points
struct Point3D{

double XX,YY,ZZ;
int cluster;
double minDist;

Point3D():
 XX(0.0),
 YY(0.0),
 ZZ(0.0),
 cluster(-1),
 minDist(DBL_MAX) {}

Point3D(double XX, double YY,double ZZ):
 XX(XX),
 YY(YY),
 ZZ(ZZ),
 cluster(-1),
 minDist(DBL_MAX) {}
 
double distance(Point3D P)
{
return (P.XX -XX) * (P.XX-XX) + (P.YY -YY) * (P.YY -YY) + (P.ZZ -ZZ)*(P.ZZ-ZZ);
}
};

// 4D Points
struct Point4D{

double XX,YY,ZZ,AA;
int cluster;
double minDist;

Point4D():
 XX(0.0),
 YY(0.0),
 ZZ(0.0),
 AA(0.0),
 cluster(-1),
 minDist(DBL_MAX) {}

Point4D(double XX, double YY,double ZZ, double AA):
 XX(XX),
 YY(YY),
 ZZ(ZZ),
 AA(AA),
 cluster(-1),
 minDist(DBL_MAX) {}
 
double distance(Point4D P)
{
return (P.AA-AA)*(P.AA-AA) + (P.XX -XX) * (P.XX-XX) + (P.YY -YY) * (P.YY -YY) + (P.ZZ -ZZ)*(P.ZZ-ZZ);
}
};



// read the 2D from the file
vector<Point2D> read_dat2D(string dataset){

vector<Point2D> points2d;

string line;
ifstream file(dataset);

while (getline(file,line))
{
stringstream lineStream(line);
string bit;
double XX, YY;

getline(lineStream,bit,',');
XX=stof(bit);
getline(lineStream,bit,'\n');
YY=stof(bit);

points2d.push_back(Point2D(XX,YY));
}

return points2d;
}


//read the 3D from file
vector<Point3D> read_dat3D(string dataset){

vector<Point3D> points3d;

string line;
ifstream file(dataset);

while (getline(file,line))
{
stringstream lineStream(line);
string bit;
double XX, YY,ZZ;

getline(lineStream,bit,',');
XX=stof(bit);
getline(lineStream,bit,',');
YY=stof(bit);
getline(lineStream,bit,'\n');
ZZ=stof(bit);

points3d.push_back(Point3D(XX,YY,ZZ));
}

return points3d;
}

//read the 4D from line

vector<Point4D> read_dat4D(string dataset){

vector<Point4D> points4d;

string line;
ifstream file(dataset);

while (getline(file,line))
{
stringstream lineStream(line);
string bit;
double XX, YY,AA,ZZ;

getline(lineStream,bit,',');
XX=stof(bit);
getline(lineStream,bit,',');
YY=stof(bit);
getline(lineStream,bit,',');
ZZ=stof(bit);
getline(lineStream,bit,'\n');
AA=stof(bit);

points4d.push_back(Point4D(XX,YY,ZZ,AA));
}

return points4d;
}


// KMEANS clustring for 2D space
void KMclustering2D(vector<Point2D>* points, int epochs, int k,string filename)
{

int n=points->size();
if(k>n){ cout<<"Number of clusters is more than  input points"; return;}

vector<Point2D> centeriods;

srand(time(0)); 

// Selction of random points
for(int i=0;i<k;++i)
{
centeriods.push_back(points->at(rand()%n));
}

//Number of epochs
for(int e=0;e<epochs;e++)
{// cout<<"\n Epoch:"<<e;
// Check for the  nearest neighbour
// Assign point to the cluster
int nochange=1;
for(vector<Point2D>::iterator c=begin(centeriods); c!= end(centeriods);c++)
{

	int clusterId= c -begin(centeriods);

	for(vector<Point2D>::iterator interim = points->begin(); interim != points->end();++interim)
	{

	Point2D p = *interim;

	double dist = c->distance(p);

	if(dist< p.minDist)
	{
	p.minDist =dist;
	p.cluster = clusterId;
	
	nochange=0;}
	*interim= p;
	}
}

if(nochange){break;}

vector<double> sumX(k,0);
vector<double> sumY(k,0);

//Calculate new centriod of the cluster
for(vector<Point2D>::iterator interim = points->begin();interim != points->end();++interim)
{
Point2D p = *interim;
sumX[p.cluster]+=p.XX;
sumY[p.cluster]+=p.YY;
}

for(int i=0;i<k;i++)
{
sumX[i]=sumX[i]/k;
sumY[i]=sumY[i]/k;

Point2D p(sumX[i],sumY[i]);
centeriods[i]=p;
}
}// epochs

// Calculate the interdistance sum of the value of sum
vector<double> Distance(k,0);
//vector<double> sumY(k,0);

for(vector<Point2D>::iterator interim = points->begin();interim != points->end();++interim)
{
vector<Point2D>::iterator c=begin(centeriods);
Point2D p = *interim;
c=c+p.cluster;
Distance[p.cluster]+=c->distance(p);
}

//Write the distance to AA file

double Sum=0;
for(int i=0;i<k;i++)
{
Sum+=Distance[i];
}



outfile2<<k<<" "<<sqrt(Sum)<<endl;

//cout<<"\nValue of Sum="<<sqrt(Sum)<<" K="<<k;

}


// 3D for kmeans clustering...........


void KMclustering3D(vector<Point3D>* points, int epochs, int k,string filename)
{

int n=points->size();
if(k>n){ cout<<"Number of clusters is more than  input points"; return;}

vector<Point3D> centeriods;

srand(time(0)); 

// Selction of random points
for(int i=0;i<k;++i)
{
centeriods.push_back(points->at(rand()%n));
}

//Number of epochs
for(int e=0;e<epochs;e++)
{// cout<<"\n Epoch:"<<e;
// Check for the  nearest neighbour
// Assign point to the cluster
int nochange=1;
for(vector<Point3D>::iterator c=begin(centeriods); c!= end(centeriods);c++)
{

	int clusterId= c -begin(centeriods);

	for(vector<Point3D>::iterator interim = points->begin(); interim != points->end();++interim)
	{

	Point3D p = *interim;

	double dist = c->distance(p);

	if(dist< p.minDist)
	{
	p.minDist =dist;
	p.cluster = clusterId;
	
	nochange=0;}
	*interim= p;
	}
}

if(nochange){break;}

vector<double> sumX(k,0);
vector<double> sumY(k,0);
vector<double> sumZ(k,0);

//Calculate new centriod of the cluster
for(vector<Point3D>::iterator interim = points->begin();interim != points->end();++interim)
{
Point3D p = *interim;
sumX[p.cluster]+=p.XX;
sumY[p.cluster]+=p.YY;
sumZ[p.cluster]+=p.ZZ;
}

for(int i=0;i<k;i++)
{
sumX[i]=sumX[i]/k;
sumY[i]=sumY[i]/k;
sumZ[i]=sumZ[i]/k;
Point3D p(sumX[i],sumY[i],sumZ[i]);
centeriods[i]=p;
}
}// epochs

// Calculate the interdistance sum of the value of sum
vector<double> Distance(k,0);
//vector<double> sumY(k,0);

for(vector<Point3D>::iterator interim = points->begin();interim != points->end();++interim)
{
vector<Point3D>::iterator c=begin(centeriods);
Point3D p = *interim;
c=c+p.cluster;
Distance[p.cluster]+=c->distance(p);
}

//Write the distance to AA file

double Sum=0;
for(int i=0;i<k;i++)
{
Sum+=Distance[i];
}


outfile3<<k<<" "<<sqrt(Sum)<<endl;

//cout<<"\nValue of Sum="<<sqrt(Sum)<<" K="<<k;
}




// 4D for kmeans clustering...........
void KMclustering4D(vector<Point4D>* points, int epochs, int k,string filename)
{

int n=points->size();
if(k>n){ cout<<"Number of clusters is more than  input points"; return;}

vector<Point4D> centeriods;

srand(time(0)); 

// Selction of random points
for(int i=0;i<k;++i)
{
centeriods.push_back(points->at(rand()%n));
}

//Number of epochs
for(int e=0;e<epochs;e++)
{
//cout<<"\n Epoch:"<<e;
// Check for the  nearest neighbour
// Assign point to the cluster
int nochange=1;
for(vector<Point4D>::iterator c=begin(centeriods); c!= end(centeriods);c++)
{

	int clusterId= c -begin(centeriods);

	for(vector<Point4D>::iterator interim = points->begin(); interim != points->end();++interim)
	{

	Point4D p = *interim;

	double dist = c->distance(p);

	if(dist< p.minDist)
	{
	p.minDist =dist;
	p.cluster = clusterId;
	
	nochange=0;}
	*interim= p;
	}
}

if(nochange){break;}

vector<double> sumX(k,0);
vector<double> sumY(k,0);
vector<double> sumZ(k,0);
vector<double> sumA(k,0);

//Calculate new centriod of the cluster
for(vector<Point4D>::iterator interim = points->begin();interim != points->end();++interim)
{
Point4D p = *interim;
sumX[p.cluster]+=p.XX;
sumY[p.cluster]+=p.YY;
sumZ[p.cluster]+=p.ZZ;
sumA[p.cluster]+=p.AA;
}

for(int i=0;i<k;i++)
{
sumX[i]=sumX[i]/k;
sumY[i]=sumY[i]/k;
sumZ[i]=sumZ[i]/k;
sumA[i]=sumA[i]/k;
Point4D p(sumX[i],sumY[i],sumZ[i],sumA[i]);
centeriods[i]=p;
}
}// epochs

// Calculate the interdistance sum of the value of sum
vector<double> Distance(k,0);
//vector<double> sumY(k,0);

for(vector<Point4D>::iterator interim = points->begin();interim != points->end();++interim)
{
vector<Point4D>::iterator c=begin(centeriods);
Point4D p = *interim;
c=c+p.cluster;
Distance[p.cluster]+=c->distance(p);
}

//Write the distance to AA file

double Sum=0;
for(int i=0;i<k;i++)
{
Sum+=Distance[i];
}

outfile4<<k<<" "<<sqrt(Sum)<<endl;


//cout<<"\nValue of Sum="<<sqrt(Sum)<<" K="<<k;
}
// 



int main(int argc, char** argv)
{

if(argc != 4){ cout<<"Input format for the <dataset> <dimension> <q3_<dimension>_<RollNo>.png";}

string dataset=argv[1];
int dim=stoi(argv[2]);
string plot_name=argv[3];

//cout<<"Data="<<dataset;
//cout<<"dimension="<<dim;

if(dim==2)
{
vector<Point2D> points=read_dat2D(dataset);
outfile2.open("./datasets/2.txt");
if(!outfile2){
cerr <<"Error: file could not be opened"<<endl;
exit(1);
}
for(int i=1;i<=15;i++)
{
KMclustering2D(&points,1000000, i,"./datasets/2.txt");
}
outfile2.close();
}

else if(dim==3){

vector<Point3D> points=read_dat3D(dataset);

outfile3.open("./datasets/3.txt");
if(!outfile3){
cerr <<"Error: file could not be opened"<<endl;
exit(1);
}
for(int i=1;i<=15;i++)
{
KMclustering3D(&points,1000000, i,"./datasets/3.txt");
}
outfile3.close();
}

else if(dim==4){

vector<Point4D> points=read_dat4D(dataset);
outfile4.open("./datasets/4.txt");


if(!outfile4){
cerr <<"Error: file could not be opened"<<endl;
exit(1);
}

for(int i=1;i<=15;i++)
{
KMclustering4D(&points,1000000, i,"./datasets/4.txt");
}
outfile4.close();
}
else{
cout<<"Not a permissible dimension";
}
return 0;}
