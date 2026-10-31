#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int size;
    if (!(cin >> size)) return 0;
    string text;
    cin >> text;

    int firstPos = -1;
    int lastPos = -1;

    for (int i = 0; i < size; i++) {
        if (text[i] != 'F') {
            if (firstPos == -1) firstPos = i;
            lastPos = i;
        }
    }

    if (firstPos == -1) {
        cout << size << "\n";
        for (int i = 0; i < size; i++) {
            cout << 1 << "\n";
        }
        return 0;
    }

    int minScore = 0;
    int maxScore = 0;

    maxScore += firstPos;
    maxScore += (size - 1 - lastPos);

    bool stepOne = (firstPos > 0) || (lastPos < size - 1);

    int current = firstPos;
    while (current < lastPos) {
        int nextPos = current + 1;
        while (text[nextPos] == 'F') {
            nextPos++;
        }
        int gap = nextPos - current - 1;

        if (gap == 0) {
            if (text[current] == text[nextPos]) {
                minScore++;
                maxScore++;
            }
        } else {
            if (text[current] == text[nextPos]) {
                if (gap % 2 == 0) minScore++;
                maxScore += (gap + 1);
            } else {
                if (gap % 2 == 1) minScore++;
                maxScore += gap;
            }
        }
        current = nextPos;
    }

    cout << stepOne << " " << firstPos << " " << lastPos << "\n";

    vector<int> answers;
    if (stepOne) {
        for (int i = minScore; i <= maxScore; i++) {
            answers.push_back(i);
        }
    } else {
        for (int i = minScore; i <= maxScore; i += 2) {
            answers.push_back(i);
        }
    }

    cout << answers.size() << "\n";
    for (int i = 0; i < answers.size(); i++) {
        cout << answers[i] << "\n";
    }

    return 0;
}