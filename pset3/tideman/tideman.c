#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
bool is_there_cycle(int loser, int i);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int j = 0; j < candidate_count; j++) //Alice Bob Charlie Dave Emma
    {
        if (strcmp(candidates[j], name) == 0) //Dave Alice Emma Bob Charlie
        {
            ranks[rank] = j;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (i < j)
            {
                preferences[ranks[i]][ranks[j]]++;
            }

        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                ++pair_count;
            }
        }
    }


    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int strength_victory = preferences[pairs[0].winner][pairs[0].loser];
    int winner = 0;
    int loser = 0;

    for (int i = 0; i < pair_count; i++)
    {
        if (strength_victory < preferences[pairs[i].winner][pairs[i].loser]) //1 //3
        {
            winner = pairs[i - 1].winner;
            loser = pairs[i - 1].loser;

            pairs[i - 1].winner = pairs[i].winner;
            pairs[i - 1].loser = pairs[i].loser;

            pairs[i].winner = winner;
            pairs[i].loser = loser;

            strength_victory = preferences[pairs[i - 1].winner][pairs[i - 1].loser];
        }
    }

    for (int i = 0; i < pair_count; i++)
    {
        printf("%i° par tem como vencedor %i\n", i + 1, pairs[i].winner);
        printf("%i° par tem como perdedor %i\n", i + 1, pairs[i].loser);
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int x = 0; x < pair_count; x++)
    {
        if (!is_there_cycle(pairs[x].winner, pairs[x].loser))
        {
            locked[pairs[x].winner][pairs[x].loser] = true;
        }
    }
    return;
}

bool is_there_cycle(int winner, int loser) //2 //1
{
    if (locked[loser][winner] == true) //0 //1
    {
        return true;
    }

    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[i][winner] == true) //0 //1
        {
            return is_there_cycle(i, loser); //0 //1
        }
    }

    return false;
}


// Print the winner of the election
void print_winner(void)
{
    int count[candidate_count];
    for (int i = 0; i < candidate_count; i++)
    {
        count[i] = 0;
    }
    
    for (int i = 0; i < candidate_count; i ++)
    {
        for (int j = 0; j < candidate_count; j ++)
        {
            count[i] += locked[j][i];
        }
        if (count[i] == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
    return;
}

