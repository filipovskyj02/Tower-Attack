#ifndef __PROGTEST__
#include <cstdio>
#include "vector"
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */


//=================================================================================================
// a dummy exception class, keep this implementation
class InvalidDateException : public invalid_argument
{
public:
    InvalidDateException ( )
            : invalid_argument ( "invalid date or format" )
    {
    }
};
//=================================================================================================
// date_format manipulator - a dummy implementation. Keep this code unless you implement your
// own working manipulator.
ios_base & ( * date_format ( const char * fmt ) ) ( ios_base & x )
{
    return [] ( ios_base & ios ) -> ios_base & { return ios; };
}
//=================================================================================================
class CDate
{
    tm * Time = nullptr;
    time_t secs = 0;

public:
   static bool isLeap (int & y){
        if (y % 400 == 0) return true;
        if (y % 100 == 0) return false;
        if (y % 4 == 0) return true;
        return false;
        }




    static bool isCorrect (int & y, int & m, int & d){
        if (y < 2000 or y > 2030) return false;
        if (m < 1 or m > 12) return false;
        if (d < 1 or d > 31) return false;
        int arr[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
        if (isLeap(y)) arr[1] = 29;

        if (d > arr[m-1]) return false;

        return true;


    }


    CDate(int y, int m, int d){
        if (!isCorrect(y,m,d)) throw InvalidDateException();
        Time = new struct tm;

        *this->Time = {0};

        this->Time->tm_year = y - 1900;
        this->Time->tm_mon = m -1;
        this->Time->tm_mday = d;
        this->secs = mktime(this->Time);




    }
    CDate(const CDate &p1) {Time = p1.Time; secs = p1.secs; }
    ~CDate(void ){
        
        this->secs = 0;

    }
    CDate& operator=(const CDate& t)
    {
        this->Time = t.Time;
        this->secs = t.secs;
        return *this;

    }
   CDate operator+ (int n){
    this->secs += (86400 * n);
    this->Time = localtime(&this->secs);

       return *this;
    }
    CDate operator - (int n){
        this->secs -= (86400* n);
        this->Time = localtime(&this->secs);
        return *this;
    }
    int operator - (CDate &b){
        time_t newsecs = this->secs - b.secs;
        return newsecs/86400;


    }
    CDate operator ++(void ){
        this->secs += 86400;
        this->Time = localtime(&this->secs);
        return *this;

    }
    CDate operator ++(int a ){
        CDate temp(this->Time->tm_year+1900, this->Time->tm_mon+1,this->Time->tm_mday);
        ++(*this);
        return temp;

    }

    CDate operator --(void ){
        this->secs -= 86400;
        this->Time = localtime(&this->secs);
        return *this;

    }
    CDate operator --(int a ){
        CDate temp(this->Time->tm_year+1900, this->Time->tm_mon+1,this->Time->tm_mday);
        --(*this);
        return temp;

    }
    bool operator ==(CDate& b){
        if (this->secs == b.secs) return true;
        return false;

    }
    bool operator !=(CDate& b){
        if (this->secs == b.secs) return false;
        return true;

    }
    bool operator <(CDate& b){
        if (this->secs < b.secs) return true;
        return false;

    }
    bool operator >(CDate& b){
        if (this->secs > b.secs) return true;
        return false;

    }
    bool operator <=(CDate& b){
        if (this->secs <= b.secs) return true;
        return false;

    }
    bool operator >=(CDate& b){
        if (this->secs >= b.secs) return true;
        return false;

    }

    friend std::ostream& operator << (std::ostream& out, const CDate& c) {
        out << c.Time->tm_year + 1900 << "-" << std::setfill ('0') << std::setw (2) << c.Time->tm_mon + 1 << "-" << std::setfill ('0') << std::setw (2)<< c.Time->tm_mday ;
        return out;
    }
   friend ostringstream & operator << (ostringstream &stream,const CDate& c) {

      stream << c.Time->tm_year + 1900 << "-" << std::setfill ('0') << std::setw (2) << c.Time->tm_mon + 1 << "-" << std::setfill ('0') << std::setw (2)<< c.Time->tm_mday;
      //cout << stream.str() << '\n';
        return stream;
    }
    friend bool operator >> (istringstream &stream,CDate& c) {
        int year= 0;
        int month = 0;
        int day = 0;
        char dash1 = '-';
        char dash2 = '-';
        stream >> year >> dash1 >> month >> dash2 >> day;

        if ((!isCorrect(year,month,day)) or dash1 != '-' or dash2 != '-'){ stream.setstate(ios::failbit); return false;}
        c.Time->tm_year = year - 1900;
        c.Time->tm_mon = month -1;
        c.Time->tm_mday = day;
        c.secs = mktime(c.Time);


        return true;
    }



};

#ifndef __PROGTEST__
int main ( void )
{
    ostringstream oss;
    istringstream iss;

    CDate a ( 2000, 1, 2 );
    CDate b ( 2010, 2, 3 );
    CDate c ( 2004, 2, 10 );
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2000-01-02" );
    oss . str ("");
    oss << b;
    assert ( oss . str () == "2010-02-03" );
    oss . str ("");
    oss << c;
    assert ( oss . str () == "2004-02-10" );
    a = a + 1500;
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2004-02-10" );
    b = b - 2000;
    oss . str ("");
    oss << b;
    assert ( oss . str () == "2004-08-13" );
    assert ( b - a == 185 );
    assert ( ( b == a ) == false );
    assert ( ( b != a ) == true );
    assert ( ( b <= a ) == false );
    assert ( ( b < a ) == false );
    assert ( ( b >= a ) == true );
    assert ( ( b > a ) == true );
    assert ( ( c == a ) == true );
    assert ( ( c != a ) == false );
    assert ( ( c <= a ) == true );
    assert ( ( c < a ) == false );
    assert ( ( c >= a ) == true );
    assert ( ( c > a ) == false );
    a = ++c;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-11 2004-02-11" );
    a = --c;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-10 2004-02-10" );
    a = c++;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-10 2004-02-11" );
    a = c--;
    oss . str ( "" );
    oss << a << " " << c;
    assert ( oss . str () == "2004-02-11 2004-02-10" );
    iss . clear ();
    iss . str ( "2015-09-03" );
    assert ( ( iss >> a ) );
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2015-09-03" );
    a = a + 70;
    oss . str ("");
    oss << a;
    assert ( oss . str () == "2015-11-12" );

    CDate d ( 2000, 1, 1 );
    try
    {
        CDate e ( 2000, 32, 1 );
        assert ( "No exception thrown!" == nullptr );
    }
    catch ( ... )
    {
    }
    iss . clear ();
    iss . str ( "2000-12-33" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-01-01" );
    iss . clear ();
    iss . str ( "2000-11-31" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-01-01" );
    iss . clear ();
    iss . str ( "2000-02-29" );
    assert ( ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-02-29" );
    iss . clear ();
    iss . str ( "2001-02-29" );
    assert ( ! ( iss >> d ) );
    oss . str ("");
    oss << d;
    assert ( oss . str () == "2000-02-29" );
/*
    //-----------------------------------------------------------------------------
    // bonus test examples
    //-----------------------------------------------------------------------------
    CDate f ( 2000, 5, 12 );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2000-05-12" );
    oss . str ("");
    oss << date_format ( "%Y/%m/%d" ) << f;
    assert ( oss . str () == "2000/05/12" );
    oss . str ("");
    oss << date_format ( "%d.%m.%Y" ) << f;
    assert ( oss . str () == "12.05.2000" );
    oss . str ("");
    oss << date_format ( "%m/%d/%Y" ) << f;
    assert ( oss . str () == "05/12/2000" );
    oss . str ("");
    oss << date_format ( "%Y%m%d" ) << f;
    assert ( oss . str () == "20000512" );
    oss . str ("");
    oss << date_format ( "hello kitty" ) << f;
    assert ( oss . str () == "hello kitty" );
    oss . str ("");
    oss << date_format ( "%d%d%d%d%d%d%m%m%m%Y%Y%Y%%%%%%%%%%" ) << f;
    assert ( oss . str () == "121212121212050505200020002000%%%%%" );
    oss . str ("");
    oss << date_format ( "%Y-%m-%d" ) << f;
    assert ( oss . str () == "2000-05-12" );
    iss . clear ();
    iss . str ( "2001-01-1" );
    assert ( ! ( iss >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2000-05-12" );
    iss . clear ();
    iss . str ( "2001-1-01" );
    assert ( ! ( iss >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2000-05-12" );
    iss . clear ();
    iss . str ( "2001-001-01" );
    assert ( ! ( iss >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2000-05-12" );
    iss . clear ();
    iss . str ( "2001-01-02" );
    assert ( ( iss >> date_format ( "%Y-%m-%d" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2001-01-02" );
    iss . clear ();
    iss . str ( "05.06.2003" );
    assert ( ( iss >> date_format ( "%d.%m.%Y" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2003-06-05" );
    iss . clear ();
    iss . str ( "07/08/2004" );
    assert ( ( iss >> date_format ( "%m/%d/%Y" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2004-07-08" );
    iss . clear ();
    iss . str ( "2002*03*04" );
    assert ( ( iss >> date_format ( "%Y*%m*%d" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2002-03-04" );
    iss . clear ();
    iss . str ( "C++09format10PA22006rulez" );
    assert ( ( iss >> date_format ( "C++%mformat%dPA2%Yrulez" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2006-09-10" );
    iss . clear ();
    iss . str ( "%12%13%2010%" );
    assert ( ( iss >> date_format ( "%%%m%%%d%%%Y%%" ) >> f ) );
    oss . str ("");
    oss << f;
    assert ( oss . str () == "2010-12-13" );

    CDate g ( 2000, 6, 8 );
    iss . clear ();
    iss . str ( "2001-11-33" );
    assert ( ! ( iss >> date_format ( "%Y-%m-%d" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "29.02.2003" );
    assert ( ! ( iss >> date_format ( "%d.%m.%Y" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "14/02/2004" );
    assert ( ! ( iss >> date_format ( "%m/%d/%Y" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "2002-03" );
    assert ( ! ( iss >> date_format ( "%Y-%m" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "hello kitty" );
    assert ( ! ( iss >> date_format ( "hello kitty" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "2005-07-12-07" );
    assert ( ! ( iss >> date_format ( "%Y-%m-%d-%m" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-06-08" );
    iss . clear ();
    iss . str ( "20000101" );
    assert ( ( iss >> date_format ( "%Y%m%d" ) >> g ) );
    oss . str ("");
    oss << g;
    assert ( oss . str () == "2000-01-01" );
*/
    return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
