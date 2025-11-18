#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

const int MAX_REVIEWS = 100;

// Arrays to store reviews
string trendNames[MAX_REVIEWS];
int ratings[MAX_REVIEWS];
string reviewers[MAX_REVIEWS];

int reviewCount = 0;

// --------------------------------------------
// Load reviews from file
// --------------------------------------------
void loadReviews() {
    ifstream file("tiktok_reviews.txt");

    if (!file) {
        // No file yet—this is normal for first run
        return;
    }

    while (file >> trendNames[reviewCount] >> ratings[reviewCount] >> reviewers[reviewCount]) {
        reviewCount++;
        if (reviewCount >= MAX_REVIEWS) break;
    }

    file.close();
}

// --------------------------------------------
// Save a new review to the file
// --------------------------------------------
void appendReviewToFile(string trend, int rating, string reviewer) {
    ofstream file("tiktok_reviews.txt", ios::app);
    file << trend << " " << rating << " " << reviewer << endl;
    file.close();
}

// --------------------------------------------
// Display all reviews
// --------------------------------------------
void viewAllReviews() {
    cout << "\nTikTok Trend            Rating   Reviewer\n";
    cout << "--------------------------------------------\n";

    for (int i = 0; i < reviewCount; i++) {
        cout << left << setw(22) << trendNames[i]
             << setw(8) << ratings[i]
             << reviewers[i] << endl;
    }
}

// --------------------------------------------
// Search for a trend (simple match)
// --------------------------------------------
void searchReview() {
    string search;
    cout << "\nEnter trend/influencer name: ";
    cin >> search;

    bool found = false;

    for (int i = 0; i < reviewCount; i++) {
        if (trendNames[i] == search) {
            cout << "\nTrend: " << trendNames[i]
                 << ", Rating: " << ratings[i]
                 << ", Reviewer: " << reviewers[i] << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "\nNo review found for that trend.\n";
    }
}

// --------------------------------------------
// Add a new review
// --------------------------------------------
void addReview() {
    if (reviewCount >= MAX_REVIEWS) {
        cout << "Cannot add more reviews. Array full.\n";
        return;
    }

    string trend, reviewer;
    int rating;

    cout << "\nEnter trend/influencer name (1 word): ";
    cin >> trend;
    cout << "Enter rating (1-10): ";
    cin >> rating;
    cout << "Enter reviewer name (1 word): ";
    cin >> reviewer;

    trendNames[reviewCount] = trend;
    ratings[reviewCount] = rating;
    reviewers[reviewCount] = reviewer;

    reviewCount++;

    appendReviewToFile(trend, rating, reviewer);

    cout << "Review added successfully!\n";
}

// --------------------------------------------
// Main Program
// --------------------------------------------
int main() {
    loadReviews();

    int choice;

    do {
        cout << "\nWelcome to the TikTok Review Database\n";
        cout << "1. View All Reviews\n";
        cout << "2. Search for a Trend/Influencer\n";
        cout << "3. Add a New Review\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                viewAllReviews();
                break;
            case 2:
                searchReview();
                break;
            case 3:
                addReview();
                break;
            case 4:
                cout << "Exiting program...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
