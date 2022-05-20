#include <bits/stdc++.h>
using namespace std;
int n, m;
char mas [502][502];
bool can[502][502];
int main () {
    int t; cin >> t;
    while(t--) {
        cin >> n >> m;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cin >> mas[i][j];
                can[i][j] = 1;
                if(mas[i][j] == 'X') can[i][j] = 0;
            }
        }
        if(m == 1) {
            for(int i = 0; i < n; i++) {
                cout << "X\n";
            }
            continue;
        }
        int shift = 0;
        if(n % 3 == 1) shift = 1;
        for(int i = 1-shift; i < n; i += 3) {
            for(int j = 0; j < m; j++) {
                mas[i][j] = 'X';
            }
        }
        
        for(int i = 1-shift; i < n; i += 3) {
            if(i + 3 >= n) break;
            if(!can[i+1][1]) {
                mas[i+2][1] = 'X';
                continue;
            }else if(!can[i+2][1]){
                mas[i+1][1] = 'X';
            }else {
                mas[i+1][0] = 'X';
                mas[i+2][0] = 'X';
            }
        }

//        cout << endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < m; j++) {
                cout << mas[i][j];
            }
            cout << "\n";
        }
    }
    return 0;
}
/*
1 8 6
..X..X
X.....
..X.X.
X.....
...X..
X....X
..X...
X...X.

1
5 5
.X...
....X
.X...
....X
X.X..

1
12 5
X...X
..X..
.....
..X..
X....
..X..
.....
.X...
...X.
.X...
....X
.X...

1
6 10
..X...X...
X...X....X
.......X..
X..X.....X
......X...
.X..X....X

1 11 3
.X.
...
.X.
...
...
.X.
...
.X.
...
X.X
...
   */
