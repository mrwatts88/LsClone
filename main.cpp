#include <iostream>
#include <sys/stat.h>

using namespace std;

int main(int argc, char **argv) {
    for (int i = 1; i < argc; i++) {
        struct stat mystat{};
        int check = stat(argv[i], &mystat);

        if (!check) {
            mode_t mode = mystat.st_mode;

            int myMode = (mode & 0777);
            int myMask = 0400;

            for (int j = 1; j <= 9; j++) {
                if (myMask == (myMask & myMode)) {
                    if (j % 3 == 0)
                        cout << "x";
                    if (j % 3 == 1)
                        cout << "r";
                    if (j % 3 == 2)
                        cout << "w";
                } else
                    cout << "-";

                myMask >>= 1;
            }

            if (S_ISDIR(mystat.st_mode)) {
                string s = string(argv[i]);
                cout << " " << s.substr(0, s.size() - 1) << " ";
                cout << "-" << endl;
            } else {
                cout << " " << argv[i] << " ";
                cout << mystat.st_size << endl;
            }
        } else
            cout << "not found" << endl;
    }

    return 0;
}
