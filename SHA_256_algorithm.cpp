#include<iostream>
#include<bitset>
#include<cmath>
using namespace std;
bitset<32> rotate_right(bitset<32> unit0, int rotation) {
    bitset<32> a;
    int i = -1;
    while (1) {
        i++;
        a[i] = unit0[i];
        if ((i+1)==rotation) {
            break;
        }
    }
    unit0>>=rotation;
    i = -1;
    while (1) {
        ++i;
        unit0[31- i] = a[rotation-i-1];
        if (i+1 == rotation) {
            break;
        }
    }
    return unit0;
}
bitset<32> small_sigma_0(bitset<32> unit0) {
    return rotate_right(unit0,7) ^ rotate_right(unit0,18) ^ (unit0>>3);
}
bitset<32> small_sigma_1(bitset<32> unit0) {
    return rotate_right(unit0,17) ^ rotate_right(unit0,19) ^ (unit0>>10);
}
long long  int binary_to_decimal(bitset<32> unit0) {
    long long int sum = 0;
    for (int i = 0; i<32; i++) {
        sum+= unit0[i]*pow(2,i);
    }
    return sum;
}
bitset<32> binary_summation_machine(bitset<32> unit0, bitset<32> unit1, bitset<32> unit2,bitset<32> unit3){
    long long int a[4];
    a[0] = binary_to_decimal(small_sigma_1(unit0));
    a[1] = binary_to_decimal(unit1);
    a[2] = binary_to_decimal(small_sigma_0(unit2));
    a[3] = binary_to_decimal(unit3);
    long long int sum = a[0] + a[1] + a[2] + a[3];
    bitset<32> final_value(sum);
    return final_value;
}
bitset<32> big_sigma_0(bitset<32> unit0) {
    return rotate_right(unit0,2) ^ rotate_right(unit0,13) ^ rotate_right(unit0,22);
}
bitset<32> big_sigma_1(bitset<32> unit0) {
    return rotate_right(unit0,6) ^ rotate_right(unit0,11) ^ rotate_right(unit0,25);
}
bitset<32> choose(bitset<32> unit0, bitset<32> gate1, bitset<32> gate2) {
    bitset<32> storage_unit;
    for (int i = 0; i<32; i++) {
        if (unit0[i] == 1) {
            storage_unit[i] = gate1[i];
        }
        else {
            storage_unit[i] = gate2[i];
        }
    }
    return storage_unit;
}
bitset<32> majority(bitset<32> unit0,bitset<32> unit1, bitset<32> unit2){
    bitset<32> storage_unit;
    for (int i =0; i<32; i++) {
        int summation = unit0[i] + unit1[i] + unit2[i];
        if (summation>1) {
            storage_unit[i] = 1;
        }
        else {
            storage_unit[i] = 0;
        }
    }
    return storage_unit;
}
void k_series_and_its_further_extenstion(bitset<32> (&k_numbers)[64],bitset<32> (&H_numbers)[8]) {
    int index_inc = -1;
    int b[64];
    for (int i = 2;;i++) {
        int verifier = 0;
        for (int j = i-1; j>=2; --j) {
            if (i%j == 0) {
                ++verifier;
            }
        }
        if (verifier == 0) {
            b[++index_inc] = i;
        }
        if (index_inc == 63) {
            break;
        }
    }
    bitset<32> k_numers[64];
    bitset<32> H_numers[8];
    for (int i = 0 ; i < 64; i++) {
        double cube_root = cbrt(b[i]);
        double fractional_part = cube_root - floor(cube_root);
        long long int k = fractional_part*pow(2,32);
        k_numers[i] = bitset<32>(k);
    }
    for (int i =0; i<8;i++) {
        double square_root = sqrt(b[i]);
        double fractional_part = square_root - floor(square_root);
        long long int k = fractional_part*pow(2,32);
        H_numers[i] = bitset<32>(k);
    }
    for (int i = 0; i < 64; i++) {
        k_numbers[i] = k_numers[i];
    }
    for (int i = 0; i<8; i++) {
        H_numbers[i] = H_numers[i];
    }
}
bitset<32> T1(bitset<32> e, bitset<32> f, bitset<32> g,bitset<32> h,bitset<32> k_t,bitset<32> w_t) {
    long long int a[5];
    a[0] = binary_to_decimal(h);
    a[1] = binary_to_decimal(big_sigma_1(e));
    a[2] = binary_to_decimal(choose(e,f,g));
    a[3] = binary_to_decimal(k_t);
    a[4] = binary_to_decimal(w_t);
    long long int sum = 0;
    for (int i =0; i<5; i++) {
        sum+=a[i];
    }
    return (bitset<32>)sum;
}
bitset<32> T2(bitset<32> a,bitset<32> b,bitset<32> c) {
    long long int m[2];
    m[0] = binary_to_decimal(big_sigma_0(a));
    m[1] = binary_to_decimal(majority(a,b,c));
    long long int sum = m[0] + m[1];
    return sum;
}
bitset<32> sum_helper(bitset<32> unit0, bitset<32> unit1) {
    long long int a[2];
    a[0] = binary_to_decimal(unit0);
    a[1] = binary_to_decimal(unit1);
    long long int sum = a[0] + a[1];
    return sum;
}
int main() {
    cout<<"Welcome to this program \"~\" "<<endl<<"__SHA256 Hash generator"<<endl;
    entry_point:

    cout<<"Enter the text to hash with SHA256 Algorithm (Max character limit -> 55)"<<endl;
    int w[64];
    int counter_1 = -1;
    while (1) {
        char a;
        cin.get(a);
        if (a == '\n') {
            break;
        }
        w[++counter_1] = (int)a;
    }
    cout<<"your output is"<<endl;
    int counter_recorder_1 = counter_1;
    bitset<8> binary_set[64];
    int zero_bit = 0;
    for (int i = 0; i<=counter_1; i++) {
        binary_set[i] = w[i];

    }
    binary_set[++counter_1] = 128;
    for (int i = ++counter_1; i<=55; i++) {
        binary_set[i] = zero_bit;
    }
    int required_bits_end = (counter_recorder_1+1)*8;
    bitset<64> end_64_bits(required_bits_end);
    int counter_2 = 0;
    for (int i = 0; i<64; i++) {
        if (i%8 == 0) {
            counter_2++;
        }
        binary_set[55+counter_2][7-i%8] = end_64_bits[63-i];
    }
    //16 carriage
    bitset<32> carriage_64[64];
    int counter_3 = 0;
    int x = -1;
    for (int i = 0; i<16; i++) {
        for (int j =0; j<32; j++) {
            if (j%8 == 0) {
                x++;
            }
            carriage_64[i][31-j] = binary_set[x][7-j%8];
        }
    }
    for (int i = 16; i<64; i++) {
        carriage_64[i] = binary_summation_machine(carriage_64[i-2],carriage_64[i-7],carriage_64[i-15],carriage_64[i-16]);
    }
    bitset<32> k[64];
    bitset<32> H[8];
    k_series_and_its_further_extenstion(k,H);
    bitset<32> a,b,c,d,e,f,g,h;
    a =H[0];
    b =H[1];
    c =H[2];
    d =H[3];
    e =H[4];
    f =H[5];
    g =H[6];
    h =H[7];
    for (int i = 0; i<64; i++) {
        bitset<32> t1 = T1(e,f,g,h,k[i],carriage_64[i]);
        bitset<32> t2 = T2(a,b,c);
        h = g;
        g = f;
        f = e;
        e = sum_helper(d,t1);
        d = c;
        c = b;
        b = a;
        a = sum_helper(t1,t2);
    }
    H[0] = sum_helper(H[0],a);
    H[1] = sum_helper(H[1],b);
    H[2] = sum_helper(H[2],c);
    H[3] = sum_helper(H[3],d);
    H[4] = sum_helper(H[4],e);
    H[5] = sum_helper(H[5],f);
    H[6] = sum_helper(H[6],g);
    H[7] = sum_helper(H[7],h);
    // char hex[65];
    bitset<4> hex_binary[64];
    int hex_index_recorder = 0;
    for (int  i =0; i<8; i++) {
        for (int j = 0; j < 32; j++) {
            hex_binary[hex_index_recorder][3-j%4] = H[i][31-j];
            if (3-j%4 == 0) {
                hex_index_recorder++;
            }
        }
    }
    char character_selection_array[] = "0123456789abcdef";
    char Hash[65];
    for (int i = 0 ; i<64; i++) {
        int x = hex_binary[i].to_ullong();
        Hash[i] = character_selection_array[x];
    }
    Hash[64] = '\0';
    cout<<Hash<<endl;
    cout<<"1.Hash another text"<<endl;
    cout<<"2.EXIT the program &`~`&"<<endl;
    char input_return;
    cin.get(input_return);
    if (input_return == '1') {
        cin.get();
        goto entry_point;
    }
    cout<<"Ending this program ^/~/^"<<endl;
    return 0;
}
