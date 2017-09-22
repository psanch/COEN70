
#include "mystring.h"
#include <cassert>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;
using std::istream;
using std::ostream;
using std::size_t;
using std::copy;


namespace coen70_lab{

string::string(const char str[ ]){
    assert(str != NULL);
    
    sequence = NULL;
    
    size_t n = strlen(str);
    
    sequence = new char[n+1];
    
    assert(sequence != NULL);
    
    strncpy(sequence, str, n);
    allocated = n+1;
    current_length = n;
    
}

string::string(char c){
    sequence = NULL;
    
    sequence = new char[2];
    
    assert(sequence != NULL);
    
    sequence[0] = c;
    sequence[1] = '\0';
    
}

string::string(const string& source){
    sequence = NULL;
    
    size_t n = source.length();
    
    sequence = new char[n + 1];
    
    assert(sequence != NULL);
    
    for(size_t i = 0; i < source.length(); i++){
        
        sequence[i] = source.sequence[i];
    }

    sequence[n] = '\0';
    allocated = n + 1;
    current_length = n;
    
}

string::~string( ){
    
    delete [] sequence;
    
}

void string::operator +=(const string& addend){
    
    size_t r = length() + addend.length();
    size_t i,j;
    
    reserve(r + 1);
    
    for(i = length(), j = 0; i < r + 1; i++,j++){
        
        sequence[i] = addend.sequence[j];
        
    }
    sequence[r+1] = '\0';
    
    allocated += addend.allocated;
    current_length += addend.current_length;
    
}

void string::operator +=(const char addend[ ]){
    
    assert (addend != NULL);
    
    size_t r = ( this->length() + strlen(addend) ) ;
    size_t i,j;
    
    reserve(r + 1);
    
    for(i = this->length(), j = 0; i < r + 1; i++, j++){
        
        sequence[i] = addend[j];
        
    }
    
    sequence[r+1] = '\0';
    
    allocated += strlen(addend);
    current_length += strlen(addend);
        
}

void string::operator +=(char addend){
    
    size_t r = length();
    
    reserve(r + 1);
    
    sequence[r] = addend;
    sequence[r + 1] = '\0';
    allocated++;
    current_length++;
    
}

void string::reserve(size_t n){
    
    {
        
        if (n == allocated)
            return;
        if (n < current_length+1)
            n = current_length+1;
        
        char* temp = sequence;
        sequence = new char[n];
        
        assert(sequence != NULL);
        
        if(temp != NULL){
            
            strncpy(sequence, temp, n);
            delete[] temp;
            
        }
        
        allocated = n;
    }
    
}
    
string& string::operator =(const string& source){
    
    size_t n = source.length();
    reserve(n + 1);
    
    size_t i;
    
    for (i = 0; i < n + 1; i++){
        
        sequence[i] = source.sequence[i];
        
    }
    
    current_length = source.length();
    sequence[current_length] = '\0';
    allocated = current_length + 1;
    
    return *this;
}

void string::insert(const string& source, unsigned int position){ 
    
    assert( position <= length() );
    
    size_t n = source.length() + length();
    
    reserve(n + 1);
    sequence[n+1] = '\0';
    size_t i,j,k;
    
    
    
    for(i = length() + source.length() - 1 , j = i - source.length(); i >= position + source.length(); i--, j--){
    
        sequence[i] = sequence[j];
        
        
    }
    
    std::cout << sequence << endl;

    
    for(i = position, j = 0; j < source.length() ; i++, j++){
        
        sequence[i] = source.sequence[j];
        
    }
    
    current_length = n;
    allocated = n+1;
    
}

void string::dlt(unsigned int position, unsigned int num){
    
    assert((position + num) <= length());
    
    size_t i,j;
    
    for(i = position; i < position+num; i++){
        
        sequence[i] = ' ';
                               
    }
    
    for(i = position, j = position + num; sequence[j] != '\0'; i++, j++){
        
        sequence[i] = sequence[j];
        
    }
    
    sequence[i] = '\0';
    
    return;
    
}

void string::replace(char c, unsigned int position){
    assert(position < length());
    
    sequence[position] = c;
    
    
}

void string::replace(const string& source, unsigned int position){ 
    
    assert((position + source.length()) <= length());
    
    size_t i,j;
    
    for (i = position, j = 0; i < position + source.length(); i++,j++){
        
        sequence[i] = source.sequence[j];
        
    }
    
}

char string::operator [ ](size_t position) const{
    
    assert (position < length());
    
    return sequence[position];
    
}

int string::search(char c) const{
    
    size_t i;
    
    for(i = 0; i < length(); i++){
        
        if(sequence[i] == c)
            return i;
    }
    
    return -1;
    
}

int string::search(const string& substring) const{
    
    char *loc = strstr(sequence,substring.sequence);
    
    return (loc == NULL) ? -1 : (loc-sequence);
    
}

unsigned int string::count(char c) const{
    
    unsigned int count = 0;
    unsigned int i = 0;
    
    while (sequence[i] != '\0'){
        
        if(sequence[i] == c){
            
            count++;
            
        }
        
        i++;
    }
    
    return count;
    
}

std::ostream& operator <<(std::ostream& outs, const string& source){
    
    size_t i;
    size_t n = source.length();
    
    for(i = 0; source.sequence[i] != '\0'; i++){
        
        outs << source.sequence[i];
        
    }
    
    return outs;
    
}

bool operator ==(const string& s1, const string& s2){
    
    size_t i;
    size_t n = s1.length();
    if(s1.length() != s2.length())
        return false;
    
    for(i = 0; i <= n; i++){
        
        if (s1.sequence[i] != s2.sequence[i])
            return false;
        
    }
    return true;
}

bool operator !=(const string& s1, const string& s2){
    
    size_t i;
    
    if(s1.length() != s2.length())
        return true;
    
    size_t n;
    
    if(s1.length() > s2.length()) n = s1.length();
    else n = s2.length();
    
    for(i = 0; i <= n; i++){
        
        if (s1.sequence[i] != s2.sequence[i])
            return true;
        
    }
    return false;
    
}

bool operator > (const string& s1, const string& s2){
    
    size_t i;
    size_t n = s1.length();
    
    if(s1.length() > s2.length())
        return true;
    if(s1.length() < s2.length())
        return false;
    
    for(i = 0; i < n; i++){
        
        if (s1.sequence[i] > s2.sequence[i])
            return true;
        
    }
    
    return false;
    
}

bool operator < (const string& s1, const string& s2){
    
    size_t i;
    size_t n = s1.length();
    
    if(s1.length() < s2.length())
        return true;
    if(s1.length() > s2.length())
        return false;
    
    for(i = 0; i < n; i++){
        
        if (s1.sequence[i] < s2.sequence[i])
            return true;
        
    }
    
    return false;
    
}

bool operator >=(const string& s1, const string& s2){
    
    if(s1 > s2 || s1 == s2)
        return true;
    return false;
    
}

bool operator <=(const string& s1, const string& s2){
    
    if( s1 < s2 || s1 == s2)
        return true;
    return false;
    
}
    
string operator +(const string& s1, const string& s2){
    
    string sum(s1);
    sum += s2;
    
    return sum;
    
    }

string operator +(const string& s1, const char addend[ ]){
    
    string sum(s1);
    sum += addend;
    
    return sum;
    
    }

std::istream& operator >> (std::istream& ins, string& target){
    
    while (ins && isspace(ins.peek()))
        ins.ignore();
    
    char tmp;
    
    target = "";
    
    while( ins && !isspace(ins.peek())){
        
        ins >> tmp;
        target += tmp;
        
    }
    
    return ins;
    
    
    }
    
}
