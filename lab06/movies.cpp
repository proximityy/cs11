/*
 * movies.cpp
 * purpose: find movies
 * author: zach meyers
 * last modified: 03/08/23
 */

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Hard coded queries that the user can execute
const string MOVIE_YEAR = "m";
const string GROSS = "g";
const string QUIT = "q";

struct Movie {
    string title;
    int year;
    int gross;
    string director;
    string actors[5];
};

Movie *read_movies(string filename, int *num_movies);
void read_actors(ifstream *infile, Movie *movies, int movie_index);
void init_data(Movie *movies, int num_movies);
void prompt_and_execute(Movie *movies, int num_movies);
void handle_movie_year(Movie *movies, int num_movies, int year);

/* ADD MORE FUNCTION DECLARATIONS HERE */

int main(int argc, char *argv[])
{
    if (argc < 2) {
        cerr << "ERROR: A filename must be specified as the first argument.\n";
        exit(EXIT_FAILURE);
    }

    string filename = argv[1];
    int num_movies;
    Movie *movies = read_movies(filename, &num_movies);
    prompt_and_execute(movies, num_movies);

    /* CALL YOUR prompt_and_execute FUNCTION HERE */

    delete[] movies;
    return 0;
}

/* * * * * * * * * * * * QUERY FUNCTIONS * * * * * * * * * * * * */

// TASK 1: Implement prompt_and_execute here

void prompt_and_execute(Movie *movies, int num_movies)
{
    string command = "";
    int year = 0;
    cout << "Enter a query: ";
    cin >> command;
    while(command != "q")
    {
        if(command == "m")
        {
            cin >> year;
            handle_movie_year(movies, num_movies, year);
        }
        else if(command == "g")
        {
            cout << "So Gross!" << endl;
        }
        else{
            cout << command << " wasn't recognized as a valid query" << endl;
        }
        cout << "Enter a query: ";
        cin >> command;

    }
}

// TASK 2: Implement handle_movie_year here

void handle_movie_year(Movie *movies, int num_movies, int year)
{
    cout << year << endl;
    for(int i = 0; i < num_movies; i++)
    {
        if(year == movies[i].year)
        {
            cout << movies[i].title << endl;
        }
    }

}

// CHALLENGE: Implement a function to handle the Highest Gross query here

/* * * * * * * * * * * * FILE READING FUNCTIONS * * * * * * * * * * * * *
 *
 *               DO NOT MODIFY ANY CODE BELOW THIS BLOCK
 *
 * * * * * * * * * * * * FILE READING FUNCTIONS * * * * * * * * * * * * */

// Read all the movie data in from a file. We have to use some funky string
// reading tricks like getline() and ignore() to make this work. You will never
// have to use these things in the lab code or homework code we ask you to
// write.
Movie *read_movies(string filename, int *num_movies)
{
    //Open the given file
    ifstream infile(filename);
    if (infile.fail()) {
        cerr << "ERROR: Error opening file, please check file name: "
             << filename << endl;
        exit(EXIT_FAILURE);
    }

    infile >> *num_movies;
    infile.ignore();
    Movie *movies = new Movie[*num_movies];
    init_data(movies, *num_movies);

    // Read in each movie
    for (int i = 0; i < *num_movies; i++) {
        getline(infile, movies[i].title);
        infile >> movies[i].year;
        infile >> movies[i].gross;
        infile.ignore();
        getline(infile, movies[i].director);

        read_actors(&infile, movies, i);
    }

    return movies;
}

// Read all the actor data for a movie in from a file. We have to use some funky
// string reading tricks like getline() to make this work. You will never have
// to use these things in the lab code or homework code we ask you to write.
void read_actors(ifstream *infile, Movie *movies, int current_movie)
{
    // Read in the actor list for that movie
    for(int j = 0; j < 5; j++){
        string actor;
        getline(*infile, actor);
        movies[current_movie].actors[j] = actor;
    }
}

// Initializes the data in both the movies and actors arrays
void init_data(Movie *movies, int num_movies)
{
    // Initialize movies
    for (int i = 0; i < num_movies; i++) {
        movies[i].title = "";
        movies[i].year = 0;
        movies[i].gross = 0;
        movies[i].director = "";

        for(int j = 0; j < 5; j++){
            movies[i].actors[j] = "";
        }
    }
}
