#include <iostream>
#include <vector>
#include <cmath>
#include <complex>

using namespace std;
class LongValue{
public:
    vector<int> value;
    explicit LongValue(vector<int> number){
        this->value = number;
    }

    explicit LongValue(vector<complex<double>> number){
        for (int i = 0; i < number.size(); i++){
            this->value.push_back((int)round(number[i].real()));
        }
    }

    explicit LongValue(long long value){
        while(value){
            this->value.push_back(int(value%10));
            value/=10;
        }
    }

    explicit LongValue(string value){
        for(int i = value.size()-1; i >= 0; i--){
            this->value.push_back(value[i]-'0');
        }
    }

    void set(int index, int num){
        this->value[index] = num;
    }

     int get (const int index) const{
        if (index < value.size()) {
            return value[index];
        } else {
            return 0;
        }
    }

    int size() const{
        return int(value.size());
    }

    LongValue sdvig(int n) const {
        if (n > 0) {
            LongValue result = LongValue(vector<int>(this->size() + n));
            for (int i = 0; i < this->size(); i++) {
                result.set(i + n, this->get(i));
            }
            for (int i = 0; i < n; i++) {
                result.set(i, 0);
            }
            return result;
        }
        if(n < 0){
            LongValue result = *this;
            for(int i = 0; i > n; i--){
                result.value.erase(result.value.begin());

            }
            return result;
        }
    }

    void normalize(){
        for (int i = 0; i < this->value.size(); i++){
            if (this->get(i) >= 10){
                if (i == this->value.size() - 1) {
                    this->value.push_back(this->get(i) / 10);
                    this->set(i, this->get(i) % 10);
                }
                else{
                    value[i+1] += value[i]/10;
                    this->set(i, this->get(i) % 10);
                }
            }
            else if(this->get(i) < 0){
                while(this->get(i) < 0){
                    this->set(i, this->get(i) + 10);
                    this->set(i+1, this->get(i+1) -1);
                }
            }
            if(this->get(this->value.size()-1) == 0){
                this->value.pop_back();
            }
        }
    }

    LongValue operator+(const LongValue &other) const{
        LongValue result = LongValue(vector<int>(max(this->size(), other.size())));
        for (int i = 0; i < max(other.size(), this->size()); i++){
            result.set(i, this->get(i) + other.get(i));
        }
        return result;
    }

    LongValue operator-(const LongValue & other) const{
        LongValue result = LongValue(vector<int>(max(this->size(), other.size())));
        for (int i = 0; i < max(other.size(), this->size()); i++){
            result.set(i, this->get(i) - other.get(i));
        }
        if(result.get(max(this->size(), other.size()) - 1) == 0){
            result.value.pop_back();
        }
        return result;
    }

    LongValue operator*(const LongValue & other) const{
        LongValue result = LongValue(vector<int>(this->size() + other.size()));
        for (int i = 0; i < this->size(); i++){
            for (int j = 0; j < other.size(); j++){
                result.set(i+j, result.get(i+j) + this->get(i)*other.get(j));
            }
        }
        if(result.get(this->size()+ other.size() - 1) == 0){
            result.value.pop_back();
        }
        return result;
    }

    LongValue operator*(int scalar) const{
        LongValue result = LongValue(vector<int>(this->size()));
        for (int i = 0; i < this->size(); i++){
            result.set(i, this->get(i)*scalar);
        }
        return result;
    }

    bool operator>(const LongValue & other) const{
        if(this->size() > other.size()){
            return true;
        }
        else if(this->size() < other.size()){
            return false;
        }
        else{
            for (int i = this->size()-1; i >= 0; i--){
                if(this->get(i) > other.get(i)){
                    return true;
                }
                else if(this->get(i) < other.get(i)){
                    return false;
                }
            }
            return true;
        }
    }

    LongValue operator/(int scalar) const{
        LongValue result = LongValue(vector<int>(this->size()));
        long long ost = 0;
        for (int i = this->size()-1; i >= 0; i--){
            result.set(i, (this->get(i) + ost*10)/scalar);
            ost = (this->get(i) + ost*10)%scalar;
        }
        return result;
    }

    LongValue operator%(int scalar) const{
        if(LongValue(scalar) > *this){
            return *this;
        }
        LongValue B0(scalar);
        LongValue B1(scalar);
        LongValue A = *this;
        while(A.size() > B1.size()){
            B1 = B1.sdvig(1);
        }
        if(B1 > A){
            B1 = B1.sdvig(-1);
        }

        while(B1.size() > B0.size()){
            if(A > B1){
                A = A - B1;
                A.normalize();
            }
            if(B1 > A){
                B1 = B1.sdvig(-1);
            }
        }
        while(A > B0){
            A = A-B0;
            A.normalize();
        }
        return A;
    }


    LongValue &operator=(const LongValue &other){
        if(&(this->value) != nullptr){
            this->value.clear();
        }
        this->value = other.value;
        return *this;
    }

    LongValue Karatsuba(LongValue &other){
        LongValue result = LongValue(vector<int>(this->size() + other.size()));
        if (this->size() < 10 || other.size() < 10){
            return *this * other;
        }
        int m = min(this->size(), other.size());
        int m2 = ceil(m/2);

        LongValue low1 = LongValue(vector<int>(this->value.begin(), this->value.begin() + m2));
        LongValue high1 = LongValue(vector<int>(this->value.begin() + m2, this->value.end()));

        LongValue low2 = LongValue(vector<int>(other.value.begin(), other.value.begin() + m2));
        LongValue high2 = LongValue(vector<int>(other.value.begin() + m2, other.value.end()));

        LongValue z0 = low1.Karatsuba(low2);
        LongValue sum2 = low2+high2;
        LongValue z1 = (low1+high1).Karatsuba(sum2);
        LongValue z2 = high1.Karatsuba(high2);
        LongValue part1 = z2.sdvig(2*m2);
        LongValue part2 = (z1 - z2 - z0).sdvig(m2);
        LongValue part3 = z0;

        return part1 + part2 + part3;
    }

    void printer(){
        this->normalize();
        for (int i = this->size() - 1; i >=0; i--){
            cout <<this->get(i);
        }
        cout<<endl;
    }

};

LongValue ToomCook3(const LongValue &a, const LongValue &b){
    LongValue result = LongValue(vector<int>(a.size() + b.size()));
    if (a.size() < 10 || b.size() < 10) {
        return a*b;
    }
    int k = floor(min(a.size(), b.size())/3);

    LongValue bot1 = LongValue(vector<int>(a.value.begin(), a.value.begin() + k));
    LongValue mid1 = LongValue(vector<int>(a.value.begin() + k, a.value.begin()+2*k));
    LongValue top1 = LongValue(vector<int>(a.value.begin() + 2*k, a.value.end()));

    LongValue bot2 = LongValue(vector<int>(b.value.begin(), b.value.begin() + k));
    LongValue mid2 = LongValue(vector<int>(b.value.begin() + k, b.value.begin() + 2*k));
    LongValue top2 = LongValue(vector<int>(b.value.begin() + 2*k, b.value.end()));

    LongValue sum1 = bot1 + mid1 + top1;
    LongValue sum2 = bot2 + mid2 + top2;

    LongValue diff1 = bot1 - mid1 + top1;
    LongValue diff2 = bot2 - mid2 + top2;

    LongValue sum3 = bot1 + mid1*2 + top1*2;
    LongValue sum4 = bot2 + mid2*2 + top2*2;

    LongValue v0 = ToomCook3(bot1, bot2);
    LongValue v1 = ToomCook3(bot1 + mid1 + top1, sum2);
    LongValue v_1 = ToomCook3(diff1, diff2);
    LongValue v2 = ToomCook3(sum3, sum4);
    LongValue v_inf = ToomCook3(top1, top2);

    LongValue t1 = (v0*3 + v_1*2+ v2)/6 - v_inf*2;
    LongValue t2 = (v1 + v_1)/2;

    LongValue c0 = v0;
    LongValue c1 = v1 - t1;
    LongValue c2 = t2 - v0 - v_inf;
    LongValue c3 = t1 - t2;
    LongValue c4 = v_inf;

    result = c0 + c1.sdvig(k) + c2.sdvig(2*k) + c3.sdvig(3*k) + c4.sdvig(4*k);
    return result;
}

vector<complex<double>> FFT(const vector<complex<double>> &a){
    int n = a.size();
    if (n == 1){
        return a;
    }
    vector<complex<double>> Po(n/2);
    vector<complex<double>> Pe(n/2);
    for (int i = 0; i < n/2; i++){
        Po[i] = a[2*i + 1];
        Pe[i] = a[2*i];
    }
    vector<complex<double>> Ye = FFT(Pe);
    vector<complex<double>> Yo = FFT(Po);
    vector<complex<double>> Y(n);
    for (int i = 0; i < n/2; i++){
        complex<double> w = exp(complex<double>(0, -2*M_PI*i/n));
        Y[i] = Ye[i] + Yo[i]*w;
        Y[i+n/2] = Ye[i] - Yo[i]*w;
    }

    return Y;
}


vector<complex<double>> IFFT(const vector<complex<double>> &a){
    vector<complex<double>> result(a.size());
    for(int i = 0; i < a.size(); i++){
        result[i] = conj(a[i]);
    }
    result = FFT(result);
    for(int i = 0; i < a.size(); i++){
        result[i] = conj(result[i]);
    }
    for(int i = 0; i < a.size(); i++){
        result[i] /= a.size();
    }
    return result;
}

vector<complex<double>> LV_to_CV(const LongValue &a){
    vector<complex<double>> result(a.size());
    for (int i = 0; i < a.size(); i++){
        result[i] = complex<double>(a.get(i), 0);
    }
    return result;
}

LongValue Shenchage(const LongValue &a, const LongValue &b){
    int n = max(a.size(), b.size());
    int p_k = 1;
    while(p_k < n){
        p_k*=2;
    }
    int q_k = 0;
    while(p_k > 18*q_k + 8){
        q_k = 3*q_k - 1;
    }
    p_k = 18*q_k + 8;
    long long m1 = pow(2,6*q_k - 1) -1;
    long long m2 = pow(2,6*q_k+1) -1;
    long long m3 = pow(2,6*q_k+2) -1;
    long long m4 = pow(2,6*q_k+3) -1;
    long long m5 = pow(2,6*q_k+5) -1;
    long long m6 = pow(2,6*q_k+7) -1;


}

int main() {
    std::cout << "Hello, World!" << std::endl;
    LongValue A("12136788777777786767749467767676474698690640640608478074807807848047804780780870477");
    LongValue B("2385294730398711677956544567899532655");
    LongValue C("1234");
    cout<<"A*B"<<endl;
    (A*B).printer();
    A.printer();
    (A%23850389).printer();
    return 0;
}
