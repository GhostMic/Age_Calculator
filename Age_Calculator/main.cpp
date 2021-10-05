#include <iostream>

using namespace std;

void cls()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void cinfail()
{
    cin.clear();
    cin.ignore(256, '\n');
}

class Present_date {
public:
    int m;
    int d;
    int y;

    Present_date(int mm, int dd, int yy)
        : m(mm), d(dd), y(yy) {}

    void print() const
    {
        cout << m << "/" << d << "/" << y << endl;
    }
};

class Birth_date {
public:
    int m;
    int d;
    int y;

    Birth_date(int mm, int dd, int yy)
        : m(mm), d(dd), y(yy) {}

    void print() const
    {
        cout << m << "/" << d << "/" << y << endl;
    }
};

class Date {
public:
    Present_date input_present();
    Birth_date input_birth();

    bool isValid(const int&, const int&, const int&);
    bool leapyear(const int&);
    void current_age(const Present_date&, const Birth_date&);

    void print() const
    {
        cout << years << " years old, " << months << " months, " << days << " days" << endl;
    }

private:
    int years;
    int months;
    int days;
};

bool Date::leapyear(const int& y)
{
    int div = y % 4;
    int end_of_century = y % 400;
    int hundreds = y % 100;

    if(end_of_century == 0 && hundreds == 0 || div == 0 && end_of_century == 0){
        return true;
    } else if(div == 0 && end_of_century != 0 && hundreds == 0){
        return false;
    } else if(div == 0){
        return true;
    } else {
        return false;
    }
}

bool Date::isValid(const int& m, const int& d, const int& y)
{
    int days_of_month = 31;
    int days_of_feb = 28;
    if(m <= 12 && m > 0 && d <= days_of_month && d > 0){
        switch (m) {
        case 2:
            if(leapyear(y)){
                days_of_feb++;
            }
            if(d > days_of_feb){
                return false;
            }
            break;
        case 4: case 6: case 9: case 11:
            --days_of_month;
            if(d > days_of_month){
                return false;
            }
            break;
        default:
            if(d > days_of_month){
                return false;
            }
            break;
        }
        return true;
    } else {
        return false;
    }
}

void Date::current_age(const Present_date& pd, const Birth_date& bd)
{
    if(bd.m > pd.m || bd.m == pd.m && bd.d > pd.d){
        years = (pd.y-1) - bd.y;
    } else {
        years = pd.y - bd.y;
    }

    int bmonth = bd.m;
    int pmonth = pd.m;
    int month_counter = 0;
    if(pd.m == bd.m && pd.d < bd.d){
        while(bmonth+1 != pmonth){
            if(bmonth >= 12){
                bmonth = 0;
            }
            bmonth++;
            month_counter++;
        }
    } else {
        while(bmonth != pmonth){
            if(bmonth >= 12){
                bmonth = 0;
            }
            bmonth++;
            month_counter++;
        }
    }
    months = month_counter;

    int bday = bd.d;
    int pday = pd.d;
    int day_counter = 0;
    if(bday > pday && pd.m != bd.m){
        months--;
    }
    while(bday != pday){
        if(bday >= 30){
            bday = 0;
        }
        bday++;
        day_counter++;
    }
    days = day_counter;

    print();
}

bool isLessthan(const Present_date& pd, const Birth_date& bd)
{
    if(bd.y < pd.y){
        return true;
    } else if(bd.y > pd.y){
        return false;
    } else {
        if(bd.m < pd.m){
            return true;
        } else if(bd.m > pd.m){
            return false;
        } else {
            if(bd.d <= pd.d){
                return true;
            } else {
                return false;
            }
        }
    }
}

Present_date Date::input_present()
{
    int m,d,y;
    char sep;
    while(true){
        cout << "Input the date today in the format mm/dd/yy: ";
        cin >> m >> sep >> d >> sep >> y;
        if(isValid(m,d,y)){
            return Present_date(m,d,y);
        } else {
            cerr << "[Invalid Date]\n";
            cinfail();
            continue;
        }
    }
}

Birth_date Date::input_birth()
{
    int m,d,y;
    char sep;
    while(true){
        cout << "Input birthdate in the format mm/dd/yy: ";
        cin >> m >> sep >> d >> sep >> y;
        if(isValid(m,d,y)){
            return Birth_date(m,d,y);
        } else {
            cerr << "[Invalid Date]\n";
            cinfail();
            continue;
        }
    }
}

int main()
{
    Date d;
    char ch;
    while(true){
        Present_date pd = d.input_present();
        Birth_date bd = d.input_birth();
        if(!isLessthan(pd,bd)){
            cerr << "[BIRTHDATE CANNOT BE GREATER THAN PRESENT DATE]\n\n";
            continue;
        }
        d.current_age(pd, bd);
        cout << endl;

        while(true){
            cinfail();
            cout << "Retry? y/n: ";
            cin.get(ch);
            if(ch == 'y'){
                cls();
                break;
            } else if(ch == 'n'){
                cout << "[Exiting Program]\n";
                return 0;
            } else {
                cerr << "[Option '" << ch << "' does not exist]\n";
                continue;
            }
        }

    }
}
