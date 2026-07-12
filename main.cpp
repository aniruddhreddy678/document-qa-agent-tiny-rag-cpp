#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

string toLower(string text) {
    transform(text.begin(), text.end(), text.begin(), ::tolower);
    return text;
}

vector<string> splitWords(string text) {
    vector<string> words;
    string word;
    stringstream ss(text);

    while (ss >> word) {
        words.push_back(word);
    }

    return words;
}

int calculateScore(string question, string paragraph) {

    question = toLower(question);
    paragraph = toLower(paragraph);

    vector<string> qWords = splitWords(question);
    vector<string> pWords = splitWords(paragraph);

    int score = 0;

    for (string q : qWords) {
        for (string p : pWords) {
            if (q == p) {
                score++;
            }
        }
    }

    return score;
}

int main() {

   ifstream file(R"(D:\TRADE\TINY RAG IN C++\bin\Debug\document.txt.txt)");

    if (!file) {
        cout << "Error opening document.txt" << endl;
        return 1;
    }

    vector<string> paragraphs;
    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            paragraphs.push_back(line);
        }
    }

    file.close();

    cout << "Tiny RAG Document Q&A Agent" << endl;

    while (true) {

        string question;

        cout << "\nAsk a question (type exit to stop): ";
        getline(cin, question);

        if (toLower(question) == "exit") {
            break;
        }

        int bestScore = 0;
        string bestAnswer = "No relevant answer found.";

        for (string para : paragraphs) {

            int score = calculateScore(question, para);

            if (score > bestScore) {
                bestScore = score;
                bestAnswer = para;
            }
        }

        cout << "\nAnswer:\n";
        cout << bestAnswer << endl;
    }

    return 0;
}
