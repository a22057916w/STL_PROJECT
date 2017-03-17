#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <string>

using namespace std;

//#define SIMPLE

#define ALTERNATE

//#define ITERATOR

string filein = "data(";
string inFormat = ").in";
string fileout = "data1.out";
fstream fin, fout;
int cas = 1;

bool read() {
    fin.close();

    string filename = "";
    filename = filename + filein + to_string(cas++) + inFormat;
    fin.open(filename, ios::in);

    if(!fin)
        return false;

    cin.rdbuf(fin.rdbuf());
    return true;
}

#ifdef SIMPLE
int main() {
    int n, m;

    fout.open(fileout, ios::out | ios::app);
    cout.rdbuf(fout.rdbuf());

    cout << "PROGRAM #1" << endl;

    while(read()) {
        cin >> m >> n;
        cin.ignore();

        clock_t start = clock();

        vector<string> V;      // Container
        string tmp;

        while ( getline(cin, tmp))
            V.push_back(tmp);

            // sort its argument in ascending order
        sort( V.begin(), V.end() );     // Iterator & Algorithm
        //copy( V.begin(), V.end(), ostream_iterator<string>(cout, "\n") );
        //cout << m << " string length with " << n << " cases: ";
        cout << ((float)clock() - start) / CLOCKS_PER_SEC << "sec" << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
#endif // SIMPLE
#ifdef ITERATOR


class line_iterator
{
    istream*  in;
    string   line;
    bool     at_end;

    void read( ) {
        if (*in)
            getline(*in, line);
        at_end = (*in) ? true : false;
    }

public:
    typedef  input_iterator_tag  iterator_category;
    typedef  string  value_type;
    typedef  ptrdiff_t  difference_type;
    typedef  const string*  pointer;
    typedef  const string&  reference;

    line_iterator( ) : in(&cin), at_end(false) { }
    line_iterator(istream& s) : in(&s) { read( ); }
    reference operator*( ) const { return line; }
    pointer operator->( ) const { return &line; }

    line_iterator operator++( ) {  // prefix ++
        read( );
        return *this;
    }

    line_iterator operator++(int) {  // postfix ++
        line_iterator  tmp = *this;
        read();
        return tmp;
    }

    bool operator==(const line_iterator& i) const {
        return (in == i.in && at_end == i.at_end) ||
               (at_end == false && i.at_end == false);
    }

    bool operator!=(const line_iterator& i) const {
        return !(*this == i);
    }
}; // end  of class line_iterator

int  main() {
    int n, m;

    fout.open(fileout, ios::out | ios::app);
    cout.rdbuf(fout.rdbuf());

    cout << "PROGRAM #2" << endl;

    while(read()) {
        cin >> m >> n;
        cin.ignore();

        clock_t start = clock();

        line_iterator  iter(cin);
        line_iterator  end_of_file;

        vector<string>  V(iter, end_of_file);

        sort( V.begin(), V.end() ); // sort( V.begin(), V.end(), greater<string>() );
        //copy( V.begin(), V.end(), ostream_iterator<string>(cout, "\n"));

        //cout << m << " string length with " << n << " cases: ";
        cout << ((float)clock() - start) / CLOCKS_PER_SEC << "sec" << endl;
    }

    fin.close();
    fout.close();

    return 0;
}

#endif

#ifdef ALTERNATE
struct  strtab_cmp
{
    typedef  vector<char>::iterator  strtab_iterator;

    bool  operator()( const pair<strtab_iterator, strtab_iterator>& x,
                       const pair<strtab_iterator, strtab_iterator>& y ) const {
        return lexicographical_compare( x.first, x.second, y.first, y.second );
    }
};

struct  strtab_print
{
    typedef  vector<char>::iterator strtab_iterator;
    ostream& out;

    strtab_print(ostream&  os) : out (os) {}

    void  operator()( const pair<strtab_iterator, strtab_iterator>&  s ) const {
        copy( s.first, s.second, ostream_iterator<char>(cout) );
    }
};


int main() {
    int n, m;

    fout.open(fileout, ios::out | ios::app);
    cout.rdbuf(fout.rdbuf());

    cout << "PROGRAM #3" << endl;

    while(read()) {
        cin >> m >> n;
        cin.ignore();

        clock_t cstart = clock();

        vector<char>  strtab;	  // Create string table
        char  c;

        while (cin.get(c))
            strtab.push_back(c);

        // Parse the string table into lines.
        typedef  vector<char>::iterator  strtab_iterator;
        vector<pair<strtab_iterator, strtab_iterator>> lines;
        strtab_iterator  start = strtab.begin();

        while (start != strtab.end()) {
            strtab_iterator  next = find( start, strtab.end(), '\n' );

            if (next != strtab.end())
                ++next;
            lines.push_back( make_pair( start, next ) );
            start = next;
        }

            // Sort the vector of lines
        sort( lines.begin(), lines.end(), strtab_cmp() );

            // Write the lines to standard output
            //for_each( lines.begin(), lines.end(), strtab_print(cout) );
        //cout << m << " string length with " << n << " cases: ";
        cout << ((float)clock() - cstart) / CLOCKS_PER_SEC << "sec" << endl;
    }

    fin.close();
    fout.close();

    return 0;
}
#endif // ALTERNATE
