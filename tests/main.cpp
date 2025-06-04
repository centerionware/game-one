#include <iostream>
#include <cctype>
#include <cstring>
#include <climits>
bool is_big_endian(void)
{
    union {
        int i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}
unsigned int
intreverse(register unsigned int x)
{
    x = (((x & 0xaaaaaaaa) >> 1) | ((x & 0x55555555) << 1));
    x = (((x & 0xcccccccc) >> 2) | ((x & 0x33333333) << 2));
    x = (((x & 0xf0f0f0f0) >> 4) | ((x & 0x0f0f0f0f) << 4));
    x = (((x & 0xff00ff00) >> 8) | ((x & 0x00ff00ff) << 8));
    return((x >> 16) | (x << 16));

}

unsigned char
bytereverse(register unsigned char v)
{
return (v * 0x0202020202ULL & 0x010884422010ULL) % 1023;

}


void* reverse(void *optr, size_t s) {
	unsigned char *d = (unsigned char*)optr;
	size_t ds = s;
	for(;s!=0;--s) {
		unsigned char input = (unsigned char)(*d);
		unsigned char &output = (unsigned char&)(*d);
		output = bytereverse(input);
		++d;
	}
	--d;
	unsigned char *l = (unsigned char *)optr;
	for(;ds!=0&&d!=l;--(--ds)) {
		unsigned char vv = *l;
		*l = *d;
		*d = vv;
		++l;
		--d;
	}
}

void endiansafe_memcpy(void *t, void*o, size_t s) {
	if(is_big_endian) {
		memcpy(t,reverse(o, s), s);
	} else {
		memcpy(t,o,s);
	} 
}

using namespace std;

struct binaryUInt { 
unsigned val; 
binaryUInt() : val(0) { }
binaryUInt(unsigned x) : val(x) { }
};

bool binBaseFormat = false;

ios_base& bin(ios_base& str) {
binBaseFormat = true;
return str;
}

ostream& operator<<(ostream& os, const binaryUInt& x) {
if (binBaseFormat == true) {
unsigned n = (sizeof(x.val) * CHAR_BIT) - 1;
for (unsigned i = 0; i <= n; i++) {
os << ((x.val >> (n-i)) & 1); 
}
binBaseFormat = false;
} else {
os << x.val;
}
return os;
}

int main(int argc, char *argv[]) {



binaryUInt y(0xDEAFBABE);
binaryUInt z(0xDEAFBABE);
reverse(&(y.val) , sizeof(y.val));


cout << "z = " << bin << z << endl;
cout << "y = " << bin << y << endl;


unsigned x = 0xDEADBEEF;
cout << "x = " << hex << static_cast<binaryUInt>(x) << endl;

return 0;
}

