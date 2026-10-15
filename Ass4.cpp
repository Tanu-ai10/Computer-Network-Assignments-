#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

const int INF = 99999;

int main() {
    int N;

    // Input number of routers
    cout << "Enter number of routers: ";
    cin >> N;

    vector<vector<int>> cost(N, vector<int>(N));
    vector<vector<int>> distance(N, vector<int>(N));
    vector<vector<int>> nextHop(N, vector<int>(N));

    // Input cost matrix
    cout << "\nEnter the network cost matrix\n";
    cout << "Use INF if two routers are not directly connected\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {

            string input;
            cin >> input;

            if (input == "INF" || input == "inf") {
                cost[i][j] = INF;
            } else {
                cost[i][j] = stoi(input);
            }

            distance[i][j] = cost[i][j];

            if (i == j) {
                distance[i][j] = 0;
                nextHop[i][j] = i;
            }
            else if (cost[i][j] != INF) {
                nextHop[i][j] = j;
            }
            else {
                nextHop[i][j] = -1;
            }
        }
    }

    // Display Initial Cost Matrix
    cout << "\nInitial Cost Matrix:\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (cost[i][j] == INF)
                cout << setw(6) << "INF";
            else
                cout << setw(6) << cost[i][j];
        }
        cout << endl;
    }

    // Display Initial Routing Tables
    cout << "\nInitial Routing Tables:\n";

    for (int source = 0; source < N; source++) {
        cout << "\nRouter " << source << ":\n";
        cout << "Destination\tDistance\tNext Hop\n";

        for (int destination = 0; destination < N; destination++) {
            cout << destination << "\t\t";

            if (distance[source][destination] == INF)
                cout << "INF\t\t";
            else
                cout << distance[source][destination] << "\t\t";

            if (nextHop[source][destination] == -1)
                cout << "-";
            else
                cout << nextHop[source][destination];

            cout << endl;
        }
    }

    // Distance Vector Algorithm
    bool updated;

    do {
        updated = false;

        for (int source = 0; source < N; source++) {
            for (int destination = 0; destination < N; destination++) {

                for (int neighbour = 0; neighbour < N; neighbour++) {

                    if (cost[source][neighbour] != INF &&
                        distance[neighbour][destination] != INF) {

                        int newCost =
                            cost[source][neighbour] +
                            distance[neighbour][destination];

                        if (newCost < distance[source][destination]) {

                            distance[source][destination] = newCost;
                            nextHop[source][destination] = neighbour;

                            updated = true;
                        }
                    }
                }
            }
        }

    } while (updated);

    // Display Final Routing Tables
    cout << "\n\nFinal Routing Tables:\n";

    for (int source = 0; source < N; source++) {

        cout << "\nRouting Table for Router " << source << ":\n";

        cout << "Destination\tDistance\tNext Hop\n";

        for (int destination = 0; destination < N; destination++) {

            cout << destination << "\t\t";

            if (distance[source][destination] == INF)
                cout << "INF\t\t";
            else
                cout << distance[source][destination] << "\t\t";

            if (nextHop[source][destination] == -1)
                cout << "-";
            else
                cout << nextHop[source][destination];

            cout << endl;
        }
    }

    // Select source and destination
    int selectedSource, selectedDestination;

    cout << "\nEnter source router: ";
    cin >> selectedSource;

    cout << "Enter destination router: ";
    cin >> selectedDestination;

    // Check if path exists
    if (distance[selectedSource][selectedDestination] == INF) {

        cout << "\nNo path exists between the selected routers.\n";
    }
    else {
        cout << "\nMinimum Cost: "
             << distance[selectedSource][selectedDestination]
             << endl;
        cout << "Shortest Path: ";
        int current = selectedSource;
        cout << current;
        while (current != selectedDestination) {
            current = nextHop[current][selectedDestination];
            if (current == -1) {
                cout << "\nPath cannot be determined.";
                return 0;
            }

            cout << " -> " << current;
        }
        cout << endl;
    }

    return 0;
}