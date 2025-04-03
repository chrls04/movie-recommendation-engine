/**
 * name: charles lee
 * student id: 100390994
 * section: 002
 * instructtor: muntaseer
*/
#include <iostream>
#include <fstream>
#include <sstream>
#include "RecommendationEngine.h"

using namespace std;

// Parse the input file and build the graph
void buildGraph(RecomendationEngine& g, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        int user;
        char movie;
        int rating;
        ss >> user >> movie >> rating;
        g.addRating(user, movie, rating);
    }
}

int main() {
    RecomendationEngine movieGraph;

    // Build the graph from MovieRatings.txt
    buildGraph(movieGraph, "MovieRatings.txt");

    // Debug: Print the graph (optional)
    cout << "Graph representation:" << endl;
    movieGraph.printGraph();

    // Get user input for movie recommendation
    char watchedMovie;
    cout << "Enter a movie you recently watched: ";
    cin >> watchedMovie;

    // Get recommendations
    auto recommendations = movieGraph.recommend(watchedMovie);
    if (recommendations.empty()) {
        cout << "No recommendations found for movie " << watchedMovie << endl;
    } else {
        cout << "Recommended movies: ";
        for (const auto& rec : recommendations) {
            cout << rec.first << " (Score: " << rec.second << ") ";
        }
        cout << endl;
    }

    return 0;
}