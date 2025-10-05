#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

const int NUM_REVIEWS = 3;

// struct copied from Lab 18
struct Review{
    double rating;
    string comment;
    Review * next;
};

// prototypes for Review funcs
Review * addFront(Review * head, double r, string c);
void displayAll(Review * head);

class Movie{
    private:
        string title;
        Review * reviewList;

    public:
        Movie(string t, Review * listHead);
        void display();
};

// Constructor
Movie::Movie(string t, Review * listHead){
    title = t;
    reviewList = listHead;
}

// Displays movie title, all reviews, average rating
void Movie::display(){
    cout << title << endl;
    cout << "---" << endl;
    displayAll(reviewList);
}

// create vector, get data from input file, use class and struct methods to display info
int main(){
    vector<Movie> movieList;
    ifstream input;
    input.open("reviews.txt");
    if (input.good()){
        string t, c;
        double r;
        while (getline(input, t)){
            Review * head = nullptr;
            for (int i = 0; i < NUM_REVIEWS; i++){
                r = (rand() % 5) + 1.0 ;
                getline(input, c);
                head = addFront(head, r, c);
            }
            Movie temp = Movie(t, head);
            movieList.push_back(temp);
        }
    }
    else{
        cout << "Error opening file";
    }
    cout << "Displaying all movies and reviews" << endl;
    for (int i = 0; i < movieList.size(); i++){
        movieList[i].display();
        cout << endl;
    }
}

// Copied from Lab 18
Review * addFront(Review * head, double r, string c){
    Review * newR = new Review;
    if (!head){
        newR->next = nullptr;
        newR->rating = r;
        newR->comment = c;
        head = newR;
    }
    else{
        newR->next = head;
        newR->rating = r;
        newR->comment = c;
        head = newR;
    }
    //cout << head->rating << " " << head->comment << endl;
    return head;
}

// Copied from Lab 18 + modifed to include average calculation
void displayAll(Review * head){
    Review * current = head;
    double average = 0;
    int i = 0;
    while(current){
        cout << "> Review " << i + 1 << ": " << current->rating << ", " << current->comment << endl;
        average += current->rating;
        current = current->next;
        i++;
    }
    average /= i;
    cout << "> Average Rating: " << average << endl;
}