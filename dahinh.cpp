#include <bits/stdc++.h>
using namespace std;
const float PI = 3.14;

class Hinh3D{
    private:
        double the_tich;
        string mau_sac;
    public:
        virtual double tinhTheTich() = 0;

        void setInfor(string m){
            the_tich = tinhTheTich();
            mau_sac = m;
        }
        virtual void print(){
            cout << "The tich va mau sac: " <<the_tich << ", " << mau_sac << endl;
        }
};

class HinhHop : public Hinh3D{
    double a, b, c;
    public:

        HinhHop(double x = 0, double y = 0, double z = 0){
            setInfor(x, y, z);
        }
        double tinhTheTich(){
            return a * b * c;
        }

        void setInfor(double x, double y, double z){
            a = x;
            b = y;
            c = z;
        }
        void print(){
            cout << "Hinh Hop : ";
            cout << a << " " << b << " " << c << endl;
            Hinh3D :: setInfor("Red");
            Hinh3D :: print();
        }
};

class HinhCau : public Hinh3D{
    double r;
    public:

        HinhCau(double ban_kinh){
            setInfor(ban_kinh);
        }

        double tinhTheTich(){
            return (4/3 * PI * pow(r, 3));
        }
        void setInfor(double ban_kinh){
            r = ban_kinh;
        }
        void print(){
            cout << "Hinh cau: "; 
            cout << r << endl;
            Hinh3D :: setInfor("Red");
            Hinh3D :: print();
        }

};

int main(){
    Hinh3D *h[10] = { new HinhCau(4.5), new HinhHop(4, 5, 6),
                      new HinhCau(5.4), new HinhHop(4, 6, 5),
                      new HinhCau(6.5), new HinhHop(5, 4, 6),
                      new HinhCau(5.6), new HinhHop(6, 5, 4),
                      new HinhCau(5.7), new HinhHop(4, 6, 5),};
    for(int i = 0; i < 10; i++){
        cout << i << endl;
        h[i]->print();
    }
}