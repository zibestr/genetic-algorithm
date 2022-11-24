#include <iostream>
#include <vector>
#include <cmath>
#include <random>

using namespace std;

const long double h = 1e-2;
int pres_random_value = 0;

long double func(long double x, long double y, long double z) {
    return z / (pow(x, 2) + 3 * y - 10);
}

long double dxFunc(long double x0, long double y0, long double z0) {
    return (func(x0 + h, y0, z0) - func(x0, y0, z0)) / h;
}

long double dyFunc(long double x0, long double y0, long double z0) {
    return (func(x0, y0 + h, z0) - func(x0, y0, z0)) / h;
}

long double dzFunc(long double x0, long double y0, long double z0) {
    return (func(x0, y0, z0 + h) - func(x0, y0, z0)) / h;
}

long double doubleAbs(long double number) {
    return sqrt(pow(number, 2));
}

int sign(int num) {
    if (num >= 0) {
        return 1;
    } 
    return -1;
}

long double randDouble() {
    srand(pres_random_value);
    int rn = rand();
    pres_random_value = rn;
    return rn * 200.0 / RAND_MAX + 100.0;
}

struct chromosome {
    long double gen_x = 1.5;
    long double gen_y = -0.5;
    long double gen_z = 2.5;
};

struct population {
    vector<chromosome> chroms;
};

chromosome generateRandomChrom() {
    chromosome result;
    result.gen_x = randDouble();
    result.gen_y = randDouble();
    result.gen_z = randDouble();
    return result;
}

population generateRandomPopul() {
    population result;
    for (int i = 0; i < 8; i++) {
        result.chroms.push_back(generateRandomChrom());
    }
    return result;
}

long double checkChromosome(chromosome chrom) {
    return doubleAbs(dxFunc(chrom.gen_x, chrom.gen_y, chrom.gen_z))
           + doubleAbs(dyFunc(chrom.gen_x, chrom.gen_y, chrom.gen_z))
           + doubleAbs(dzFunc(chrom.gen_x, chrom.gen_y, chrom.gen_z));
}

vector<chromosome> sortChroms(vector<chromosome> chroms) {
    vector<long double> buffer;
    chromosome temp_chrom;
    long double temp_key;

    for (int i = 0; i < 8; i++) {
        buffer.push_back(checkChromosome(chroms[i]));
    }

    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7 - i; j++) {
            if (buffer[j] > buffer[j + 1]) {
                // меняем хромосомы местами
                temp_chrom = chroms[j];
                chroms[j] = chroms[j + 1];
                chroms[j + 1] = temp_chrom;
                // меняем ключи местами
                temp_key = buffer[j];
                buffer[j] = buffer[j + 1];
                buffer[j + 1] = temp_key;
            }
        }
    }
    return chroms;
}

population generateNewPopulation(population popul) {
    vector<chromosome> old_chroms = sortChroms(popul.chroms);
    popul.chroms[0].gen_x = old_chroms[0].gen_x;
    popul.chroms[0].gen_y = old_chroms[0].gen_y;
    popul.chroms[0].gen_z = old_chroms[1].gen_z;
    popul.chroms[1].gen_x = old_chroms[2].gen_x; 
    popul.chroms[1].gen_y = randDouble();
    popul.chroms[1].gen_z = old_chroms[1].gen_z;
    popul.chroms[2].gen_x = old_chroms[0].gen_x;
    popul.chroms[2].gen_y = old_chroms[0].gen_y;
    popul.chroms[2].gen_z = randDouble();
    popul.chroms[3].gen_x = randDouble(); 
    popul.chroms[3].gen_y = old_chroms[1].gen_y;
    popul.chroms[3].gen_z = old_chroms[1].gen_z;
    popul.chroms[4].gen_x = old_chroms[0].gen_x;
    popul.chroms[4].gen_y = randDouble();
    popul.chroms[4].gen_z = randDouble();
    popul.chroms[5].gen_x = old_chroms[0].gen_x;
    popul.chroms[5].gen_y = old_chroms[2].gen_y;
    popul.chroms[5].gen_z = old_chroms[2].gen_z;
    popul.chroms[6].gen_x = old_chroms[1].gen_x;
    popul.chroms[6].gen_y = old_chroms[1].gen_y;
    popul.chroms[6].gen_z = old_chroms[0].gen_z;
    popul.chroms[7].gen_x = old_chroms[1].gen_x;
    popul.chroms[7].gen_y = old_chroms[1].gen_y;
    popul.chroms[7].gen_z = old_chroms[3].gen_z;
    return popul;
}

int main() {
    population popul = generateRandomPopul();
    long long count_generations = 1000000;
    for (long long i = 0; i < count_generations; i++) {
        cout << "Самая наименьшая ошибка: " << checkChromosome(popul.chroms[0]) << 
        ", поколение: " << i + 1 << "/" << count_generations << endl;
        popul = generateNewPopulation(popul);
        cout << "Лучшая точка экстремума: (" << 
        popul.chroms[0].gen_x << ", " << popul.chroms[0].gen_y << ", " << 
        popul.chroms[0].gen_z << ")\n";
    }
    cout << "Значение экстремума функции f(x,y,z)=z/(x^2+2y+1): " <<
    func(popul.chroms[0].gen_x, popul.chroms[0].gen_y, 
    popul.chroms[0].gen_z) << ", точка экстремума: (" << 
    popul.chroms[0].gen_x << ", " << popul.chroms[0].gen_y << ", " << 
    popul.chroms[0].gen_z << ")\n";
}