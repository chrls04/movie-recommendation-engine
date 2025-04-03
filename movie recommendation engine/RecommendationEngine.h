
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>

using namespace std;

// Bipartite graph representation
class RecomendationEngine {
private:
    unordered_map<int, vector<pair<char, int>>> userToMovies; // User -> [(Movie, Rating)]
    unordered_map<char, vector<pair<int, int>>> movieToUsers; // Movie -> [(User, Rating)]
public:
    // Add a rating (edge) to the graph
    // add edge to both userToMovies and movieToUsers
    void addRating(int user, char movie, int rating) {
        userToMovies[user].push_back({movie,rating});
        movieToUsers[movie].push_back({user,rating});
    }
    // Recommend movies based on a watched movie
    // see assignment for details
    vector<pair<char, double>> recommend(char watchedMovie) {
        unordered_map<char,double> movieRatings;
        unordered_set<char> ratedMovies;

        if (movieToUsers.find(watchedMovie) == movieToUsers.end()) {
            return {};
        }
        for(const auto& [user,rating] : movieToUsers[watchedMovie]) {
            for (const auto& [movie, movieRating] : userToMovies[user]) {
                if (movie == watchedMovie) {
                    continue;
                }
                double score = rating * movieRating;
                if (movieRatings.find(movie) == movieRatings.end()) {
                    movieRatings[movie] = score;
                } else {
                    movieRatings[movie] += score;
                }
            }
        }
        vector<pair<char,double>> sortedMovies(movieRatings.begin(),movieRatings.end());
        sort(sortedMovies.begin(),sortedMovies.end(), [](const pair<char,double> &a,const pair<char,double> &b) {
            return a.second > b.second;
        });
        return sortedMovies;
    }

    // Print the graph
    void printGraph() {
        cout << "User -> Movies:" << endl;
        for (const auto& [user, movies] : userToMovies) {
            cout << "User " << user << ": ";
            for (const auto& [movie, rating] : movies) {
                cout << "(" << movie << ", " << rating << ") ";
            }
            cout << endl;
        }
        cout << "Movie -> Users:" << endl;
        for (const auto& [movie, users] : movieToUsers) {
            cout << "Movie " << movie << ": ";
            for (const auto& [user, rating] : users) {
                cout << "(" << user << ", " << rating << ") ";
            }
            cout << endl;
        }
    }
};
