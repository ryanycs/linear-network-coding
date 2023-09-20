#include <bits/stdc++.h>
#include "matrix.h"
using namespace std;

vector<int> to_ascii(char c) {
    vector<int> res(8);

    int i = 7;
    while (c) {
        res[i--] = c & 1;
        c >>= 1;
    }

    return res;
}

char to_char(vector<int> ascii) {
    char res = 0;

    for (int i = 0; i < ascii.size(); ++i) {
        res <<= 1;
        res |= ascii[i];
    }

    return res;
}

void print(vector<vector<int>> mat, string msg) {
    cout << msg << endl;
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].size(); ++j) {
            cout << mat[i][j] << (j == mat[0].size() - 1 ? '\n' : '\0');
        }
    }
    cout << endl;
}

vector<vector<int>> LNC_encode(string s) {
    int n_packet = s.size();
    vector<vector<int>> packets, coding_vectors, linear_combination, outgoing_packets;

    packets = vector(n_packet, vector<int>());
    for (int i = 0; i < n_packet; ++i) {
        packets[i] = to_ascii(s[i]);
    }

    // Gererate linear independent matrix
    coding_vectors = generate_indep_mat(n_packet);

    linear_combination = mat_mul(coding_vectors, packets);

    // embed coding_vectors to packets
    for (int i = 0; i < n_packet; ++i) {
        outgoing_packets.push_back(coding_vectors[i]);
    }
    for(int i = 0; i < n_packet; ++i) {
        for (int j = 0; j < linear_combination[0].size(); ++j) {
            outgoing_packets[i].push_back(linear_combination[i][j]);
        }
    }

    print(packets, "source packets:");
    print(coding_vectors, "coding vectors:");

    return outgoing_packets;
}

string LNC_decode(vector<vector<int>> &incoming_packets) {
    int n_packet = incoming_packets.size();
    string s;
    vector<vector<int>> coding_vectors, inv_coding_vectors, data, res;

    // extract coding vectors
    coding_vectors = vector(n_packet, vector<int>(n_packet));
    for (int i = 0; i < n_packet; ++i) {
        for (int j = 0; j < n_packet; ++j) {
            coding_vectors[i][j] = incoming_packets[i][j];
        }
    }

    // extract data
    data = vector(n_packet, vector<int>());
    for (int i = 0; i < n_packet; ++i) {
        for (int j = n_packet; j < incoming_packets[0].size(); ++j) {
            data[i].push_back(incoming_packets[i][j]);
        }
    }

    // calculate inverse of coding vectors
    inv_coding_vectors = mat_inverse(coding_vectors);

    // decoding
    res = mat_mul(inv_coding_vectors, data);

    for (int i = 0; i < res.size(); ++i) {
        s.push_back(to_char(res[i]));
    }

    return s;
}

int main() {
    string s1, s2;
    srand(time(NULL));

    cout << "Enter the string you want to encode:" << endl;
    getline(cin, s1);
    cout << endl;

    // encoding
    auto packets = LNC_encode(s1);

    print(packets, "The encoded packets:");

    // decoding
    s2 = LNC_decode(packets);

    cout << "After decoding:" << endl;
    cout << s2 << endl;

    return 0;
}