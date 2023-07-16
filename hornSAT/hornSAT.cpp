#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

/*Is there a clause P1^P2^P3.....^Pk->P of formula such that all Pj are marked but P isnt marked*/
bool shouldContinue(vector<vector<char>>& formula, unordered_map<char,bool>& assignments)
{
    int f;  //flag

    for (vector<char> clause : formula)
    {
        f = 1;
        for (int i = 0; i < clause.size()-1; i++)
        {
            if(assignments.find(clause[i]) == assignments.end())
            {
                f = 0;
            }
        }

        if (f == 1 && assignments.find(clause[clause.size()-1]) == assignments.end())
        {
            return true;
        }
       
    }

    return false;
}

int main()
{
    //Vector to store the horn formula
    vector<vector<char>> formula = {{'T','a'},{'a','F'}};

    //Map to store the assigment of the variables
    unordered_map<char,bool> assignments;


    /*Step 1: Mark all occurances of T in formula*/
    for(vector<char> clause: formula)
    {
        for(int literal: clause)
        {
            if (literal == 'T')
            {
                if (assignments.find(literal) == assignments.end())
                {
                    assignments[literal] = 1;
                }
                
            }
            
        }
    }
    

    /*Step 2: There is a clause p1^p2^p3.....^pk->P of formula such that all Pj are marked but P isn't marked,
    do mark P */
    while (shouldContinue(formula,assignments))
    {
        int f;

        for (vector<char> clause : formula)
        {
            f = 1;
            for (int i = 0; i < clause.size()-1; i++)
            {
                if(assignments.find(clause[i]) == assignments.end())
                {
                    f = 0;
                }
            }

            if (f == 1 && assignments.find(clause[clause.size()-1]) == assignments.end())
            {
                assignments[clause[clause.size()-1]] = clause[clause.size()-1]>0;
            }
            
        }
    }


    /*Step 3: If F is marked then return UNSATISFIABLE else return SATISFIABLE*/
    if (assignments.find('F') == assignments.end())
    {
        cout<<"SATISFIABLE";
    }
    else
    {
        cout<<"UNSATISFIABLE";
    }
    
    
}
