#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }
        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int k = 0; k < candidate_count; k++)               // for all candidates, where there is a name match
    {
        if (strcmp(candidates[k].name, name) == 0)
        {
            preferences[voter][rank] = k;                   // set preferences[voter][rank] = candidate k
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)              // if there are no eliminated candidates
        {
            for (int j = 0; j < voter_count; j++)
            {
                if (strcmp(candidates[preferences[j][0]].name, candidates[i].name) == 0)
                {
                    candidates[i].votes++;                  // count votes of all voters in preference [j][0]
                }
            }
        }
        else if (candidates[i].eliminated == true)          // if there are eliminated candidates
        {
            int c = 0;
            c++;                                             // count number of candidates that have been eliminated
            for (int j = 0; j < voter_count; j++)           // for each voter j
            {
                for (int n = 0; n < c; n++)                 // look at the first few ranks equal to number of eliminated candidates
                {
                    if (strcmp(candidates[preferences[j][n]].name, candidates[i].name) == 0) // if one of those ranks equal to an eliminated candidate
                    {
                        candidates[preferences[j][n + 1]].votes++;  // count vote from 1 rank higher
                    }
                }
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // if any vote count is greather 50% of voters, then print winner
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > (0.5 * voter_count))
        {
            printf("%s\n", candidates[i].name);
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // define term min to equal least votes a non-eliminated candidate has
    int min = voter_count;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false & candidates[i].votes < min)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int j = 0;                                              // define number of uneliminated candidates with min votes
    int l = 0;                                              // count number of eliminated candidates
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min & candidates[i].eliminated == false)
        {
            j++;                                            // if uneliminated candidate has min vote, add to defined j
        }
        if (candidates[i].eliminated == true)               // if candidate has been eliminated, add to defined l
        {
            l++;
        }
    }
    if (j == candidate_count -
        l)                                                  // if number of uneliminated candidates w min vote = number of remaining candidates
    {
        return true;                                        // return tie
    }
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    for (int i = 0; i < candidate_count; i++)               // if candidate has least votes and there is no tie
    {
        if (candidates[i].votes == min & is_tie(min) == false)
        {
            candidates[i].eliminated = true;                // candidate is eliminated
        }
    }
    return;
}
