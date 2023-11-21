#include <iostream>
#include <vector>
#include <math.h>
#define ll long long
using namespace std;

/////////////////
//OTHER FUNCTIONS
/////////////////

int intervalFunc(double argument){
	int z;
	if (argument == 100){
		return 9;
	}
 	z = int(argument/10);
	return z;
}

ll obernenaX(int x, int p){
	ll res = 1;
	ll mod;
	mod = p+2;
	while(p){
		if(p & 1)
			res *= x;
		res %= mod;
		x *= x;
		x %= mod;
		p >>= 1;
	}
	return res;
}

void printer(vector<double> m){
	for (int i = 0; i<9; i++){
		cout << "[" << i * 10 << ";" << i * 10 + 10 << ") " << m[i] << endl;
	}
	cout << "[" << 90 << ";" <<  100 << "] " << m[9] << endl;
}

void printerSix(vector<double> m){
	for (int i = 0; i<9; i++){
		cout << "[" << -3.0 + i * 0.6 << ";" << -3.0 + i*0.6+0.6<< ") " << m[i] << endl;
	}
	cout << "[" << 2.4 << ";" <<  3 << "] " << m[9] << endl;
}

void printerTen(vector<double> m){
	for (int i = 0; i<19; i++){
		cout << "[" << i * 5 << ";" << i * 5 + 5 << ") " << float(m[i]) << endl;
	}
	cout << "[" << 95 << ";" <<  100 << "] " << m[19] << endl;
}

////////
//CHEKERS
////////

int prostoe(ll n){
	for (int i = 2; i <= sqrt(n); i++) {
    if (n % i == 0) {
        return 0;
    	}
	}
	return 1;
}

int stepin2(ll n){
	int i = 0;
	while(n%2 ==0){
		n = n/2;
		i++;
	}
	if (n == 1)
	{
		return i;
	}
	return 0;
}

int NOD(int g, int h)
{
    while(g!=0 and h!=0)
    {
        if(g>h)
        {
            g=g%h;
        }
        else 
        {
            h=h%g;
        }
        
    }
    return (g+h);
}

int cratnist(ll a, ll  m){
	for(int i = 1 ; i < m; i++){
		if(m%i == 0 and prostoe(i)){
			if(not a%i){
				return 0;
			}
		}
	}
	return 1;
}

int checker1(ll a, ll c, ll m){
	if(NOD(c, m) == 1 and cratnist(a-1, m)){
		if (not m%4 ==0 or (a-1)%4 == 0){
			return 1;
		}
	}
	return 0;
}

int checker2(ll a, ll c, ll m, ll d){
	if(not m%3 == 0 or d != 3*c%9)
		if(NOD(c, m) == 1 and cratnist(a-1, m)){
			if (not m%4 ==0 or (d ==(a-1)%4 and d%2 == 0)){
				return 1;
			}
			if (not m%2 ==0 or d ==(a-1)%2)
			{
				return 1;
			}
		}
	return 0;
}

int checker4(ll a, ll c, ll m){
	if (prostoe(m))
		return 1;
	else if (stepin2(m) > 2 and a%4 == 1 and c%4 == 2){
		return 1;
	}
	return 0;
}

//////////////////////////////
//FUNCTIONS OF CREATING ZMINNA
//////////////////////////////

ll zminnaOdin(ll a, ll c, ll m, ll xprev){
	return (a*xprev + c)%m;
}

ll zminnaTwo(ll a, ll c, ll m, ll xprev, ll d){
	return ((d*xprev*xprev)%m + (a*xprev)%m + c)%m;
}

ll zminnaThree(ll m, ll xprev, ll xprevprev){
	return (xprev + xprevprev)%m;
}

ll zminnaFour(ll a, ll c, ll m, ll xprev){
	return (a*obernenaX(xprev, m-2) + c)%m;
}

ll zminnaFive(ll x, ll y, ll m){
	return ((x-y)%m + m)%m;
}

vector<double> methodOdin(){
	ll a, c, m, x, xprev = 0;
	double zminna;
	vector<double> intervals(10);
	cout<<"Enter a, c, m"<<endl;
	cin >> a >> c >> m;
	while(not checker1(a, c, m)){
		cout<<"Enter different a, c, m"<<endl;
		cin >> a >> c >> m;
	}
	for (int i = 1; i <= 10000; i++){
		x = zminnaOdin(a, c, m, xprev);
		zminna = x*100.0/(m-1);
		intervals[intervalFunc(zminna)] += 0.0001;
		xprev = x;
	}
	return intervals;
}


vector<double> methodTwo(){
	ll a, c, m, x, d, xprev = 0;
	double zminna;
	vector<double> intervals(10);
	cout<<"Enter a, c, m, d"<<endl;
	cin >> a >> c >> m >> d;
	while(not checker2(a, c, m, d)){
		cout<<"Enter different a, c, m, d"<<endl;
		cin >> a >> c >> m >> d;
	}
	for (int i = 1; i <= 10000; i++){
		x = zminnaTwo(a, c, m, xprev, d);
		zminna = x*100.0/(m-1);
		intervals[intervalFunc(zminna)] += 0.0001;
		xprev = x;
	}
	return intervals;
}

vector<double> methodThree(){
	ll m, x = 0;
	ll xprev = 2, xprevprev = 1;
	double zminna;
	vector<double> intervals(10);
	cout<<"Enter m"<<endl;
	cin >> m;
	for (int i = 1; i <= 100000; i++){
		x = zminnaThree(m, xprev, xprevprev);
		zminna = x*100.0/(m-1);
		intervals[intervalFunc(zminna)] += 0.00001;
		xprevprev = xprev;
		xprev = x;
	}
	return intervals;
}

vector<double> methodFour(){
	ll a, c, m, xprev = 1;
	double zminna;
	vector<double> intervals(10);
	cout<<"Enter a, c, m"<<endl;
	cin >> a >> c >> m;
		while(not checker4(a, c, m)){
		cout<<"Enter different a, c, m"<<endl;
		cin >> a >> c >> m;
	}
	for (int i = 1; i <= 10000; i++){
		xprev = zminnaFour(a, c, m, xprev);
		zminna = xprev*100.0/(m-1);
		cout<<zminna<<endl;
		intervals[intervalFunc(zminna)] += 0.0001;
	}
	return intervals;
}

vector<double> methodFive(){
	ll a, c, mx, my, mz, x, xprev = 0, z, y, yprev = 0, yprevprev = 0;
	double zminna;
	vector<double> intervals(10);
	cout<<"Enter a, c, mx, my, mz"<<endl;
	cin >> a >> c >> mx >> my >> mz;
	for (int i = 1; i <= 10000; i++){
		x = zminnaOdin(a, c, mx, xprev);
		y = zminnaThree(my, yprev, yprevprev);
		z = zminnaFive(x, y, mz);
		zminna = z*100.0/(mz-1);
		intervals[intervalFunc(zminna)] += 0.0001;
		xprev = x;
		yprevprev = yprev;
		yprev = y;
	}
	return intervals;
}

vector<double> methodSix(){
	int i = 0;
	ll m, xprev = 1, xprevprev = 1, x;
	double zminna, sum =0;
	vector<double> intervals(10);
	cout<<"Enter m"<<endl;
	cin >> m;
	while(i < 1000){
		sum = 0;
		for(int i2 = 0; i2 < 12; i2++){
			x = zminnaThree(m, xprev, xprevprev);
			sum += 1.0*x/(m-1);
			xprevprev = xprev;
			xprev = x;
			}
		if (int((sum - 3)*5.0/3) < 10){
			i++;
			intervals[int((sum - 3)*5.0/3)] += 0.001;
			}
		}
	return intervals;
}

vector<double> methodSeven(){
	ll m1, m2, u1 = 0, u2 = 0, i=0;
	ll u1prev = 1, u1prevprev = 1, u2prev = 1, u2prevprev = 1;
	double v1, v2, S;
	vector<double> intervals(10);
	cout<<"Enter m1, m2"<<endl;
	cin >> m1 >> m2;
	while(i < 5000){
		u1 = zminnaThree(m1, u1prev, u1prevprev);
		u2 = zminnaThree(m2, u2prev, u2prevprev);
		v1 = 2.0*u1/(m1-1)-1;
		v2 = 2.0*u2/(m2-1)-1;
		u1prevprev = u1prev;
		u1prev = u1;
		u2prevprev = u2prev;
		u2prev = u2;
		S = v1*v1 + v2*v2;
		if(S < 1){
			i++;
			if (v1*sqrt(-2*log(S)/S) < 3){
				intervals[int((v1*sqrt(-2*log(S)/S)+3)*5/3)] += 0.0001;
				}
			if (v2*sqrt(-2*log(S)/S) < 3){
				intervals[int((v2*sqrt(-2*log(S)/S)+3)*5/3)] += 0.0001;
				}
			}
		}
	return intervals;
	}

vector<double> methodEight(){
	ll m1, m2, i=0;
	ll u1prev = 1, u1prevprev = 2, u2prev = 3, u2prevprev = 5;
	double x, u1 = 0, u2 = 0;
	vector<double> intervals(10);
	cout<<"Enter m1, m2"<<endl;
	cin >> m1 >> m2;
	while(i < 1000){
		u1 = zminnaThree(m1, u1prev, u1prevprev);
		u2 = zminnaThree(m2, u2prev, u2prevprev);
		if (u2 != 0)
			x = sqrt(8/2.71828)*(u1/(m1-1)-0.5)/u2*(m2-1);
		u1prevprev = u1prev;
		u1prev = u1;
		u2prevprev = u2prev;
		u2prev = u2;
		if (x*x <= -4*log(1.0*u2/(m2-1))){
			i++;
			if (int((x+3)*5/3) == 10)
			{
				intervals[9] += 0.001;
			}
			else{
				intervals[int((x+3)*5/3)] += 0.001;
			}
		}
	}
	return intervals;
}

vector<double> methodNine(){
	ll m, uprev = 1, uprevprev = 1, u;
	double x;
	vector<double> intervals(10);
	cout<<"Enter m "<<endl;
	cin >> m;
	for(int i = 0; i < 10000; i++){
		u = zminnaThree(m, uprev, uprevprev);
		x = -log(1.0*u/(m-1));
		uprevprev = uprev;
		uprev = u;
		if (not isinf(x))
			intervals[int(1.2*x)] += 0.0001;
	}
	return intervals;
}

vector<double> methodTen(){
	ll m1, m2, i=0;
	ll uprev = 1, uprevprev = 2, vprev = 3, vprevprev = 5;
	double X, Y, u = 0, v = 0, U, V, a = 2;
	vector<double> intervals(10);
	cout<<"Enter m1, m2"<<endl;
	cin >> m1 >> m2;
	while(i < 1000){
		u = zminnaThree(m1, uprev, uprevprev);
		uprevprev = uprev;
		uprev = u;
		U = u/(m1-1);
		Y = tan(22/7*U);
		X = sqrt(2*a-1)*Y+a-1;
		if(X > 0){
			v = zminnaThree(m2, vprev, vprevprev);
			vprevprev = vprev;
			vprev = v;
			V = v/(m2-1);
			if( V <= (1+Y*Y)*exp((a-1)*log(X/(a-1)-sqrt(2*a-1)*Y))){
//				cout << X << '\n';
				i++;
				if(X < 100)
					intervals[int(X/10)]+= 0.001;
			}
		}
	}
	return intervals;
}

//////
//MAIN
//////

int main(){
	int nomer_method;
	vector<double> argument;
	cout<<"Enter number of method: ";
	cin >> nomer_method;
	switch(nomer_method){
		case 1:
			printer(methodOdin());
			break;
		case 2:
			printer(methodTwo());
			break;
		case 3:
			printer(methodThree());
			break;
		case 4:
			printer(methodFour());
			break;
		case 5:
			printer(methodFive());
			break;
		case 6:
			printerSix(methodSix());
			break;
		case 7:
			printerSix(methodSeven());
			break;
		case 8:
			printer(methodEight());
			break;
		case 9:
			printer(methodNine());
			break;
		case 10:
			printerTen(methodTen());
			break;
	}
	return 0;
}