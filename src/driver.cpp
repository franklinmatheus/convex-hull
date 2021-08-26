#include "convexhull.h"
#include <sstream>
#include <fstream>
#include <math.h>
#include <chrono>

using namespace ConvexHull;
using namespace std;

int main(int argc, char **argv) {  
    if (argc != 4) {
        printf("two arguments are required:");
        printf("\n<input file name>");
        printf("\n<output file name>");
        printf("\n<option number> : \n\t{1: graham-scan}\n\t{2: brute force}\n\t{3: graham-scan with time}\n\t{3: brute force with time}");
        return EXIT_FAILURE;
    }
    
    std::ifstream infile("./data/" + (string) argv[1]);
    if(infile.fail()){
        printf("%s does not exist", argv[1]);
        return EXIT_FAILURE;
    }

    string line;
    vector<Point> points;

    while (getline(infile, line)) {
        std::istringstream iss(line);
        int x, y;
        if (!(iss >> x >> y)) { break; }

        Point temp = {x, y};
        points.push_back(temp);
    }

    int n = points.size();
    if (n == 0) {
        printf("zero points in file");
        return EXIT_FAILURE;
    }
    
    if(1 == atoi(argv[3])) {
        stack<Point> S = grahamScan(points, n);
        std::ofstream grahamoutfile("./data/graham_" + (string)argv[2]);
        while (!S.empty()) {
            Point p = S.top();
            grahamoutfile << p._x << "," << p._y << endl;
            S.pop();
        }
        grahamoutfile.close();
    } else if (2 == atoi(argv[3])) {
        vector<Point> V = bruteForce(points, n);
    
        std::ofstream bruteoutfile("./data/brute_" + (string)argv[2]);
        for (unsigned int i = 0; i < V.size(); ++i) {
            Point p = V[i];
            bruteoutfile << p._x << "," << p._y << endl;
        }
        bruteoutfile.close();
    } else if (3 == atoi(argv[3])) {
        if ((n & (n - 1)) == 0 && n >= 4) {
            std::ofstream grahamoutfile("./data/timeGraham_" + (string)argv[2]);
            for(int i = 4; i <= n; i+=2) {
                vector<Point> temp;
                for (int j = 0; j < i; ++j) temp.push_back(points[j]);
                auto begin = chrono::steady_clock::now();
                auto shau = grahamScan(temp, i);
                auto end = chrono::steady_clock::now();
                grahamoutfile << i << " " << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << endl;
            }
            grahamoutfile.close();
        } else {
            printf("number of points must be power of 2 but got %d", n);
            return EXIT_FAILURE;
        }
    } else if (4 == atoi(argv[3])) {
        if ((n & (n - 1)) == 0  && n >= 4) {
            std::ofstream bruteoutfile("./data/timeBrute_" + (string)argv[2]);
            for(int i = 4; i <= n; i+=2) {
                vector<Point> temp;
                for (int j = 0; j < i; ++j) temp.push_back(points[j]);
                auto begin = chrono::steady_clock::now();
                auto shau = bruteForce(temp, i);
                auto end = chrono::steady_clock::now();
                bruteoutfile << i << " " << chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << endl;
            }
            bruteoutfile.close();
        } else {
            printf("number of points must be power of 2 but got %d", n);
            return EXIT_FAILURE;
        }
    } else {
        printf("3rd parameter wrong");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}