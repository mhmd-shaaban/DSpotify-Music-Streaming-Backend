typedef struct myPair {
    int first;
    int second;

myPair() = default;
myPair(int fir,int sec) : first(fir) , second(sec){}

bool operator<(const myPair& other) const {
if(first < other.first) 
return true;
if(first > other.first)
return false;
return second < other.second;
}

bool operator>(const myPair& other) const {
    return other < *this;
}

bool operator== (const myPair& other) const {
    return (first == other.first && second == other.second);
}

bool operator!=(const myPair& other) const {
    return !(*this == other);
}

} myPair;