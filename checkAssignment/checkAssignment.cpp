#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;


//check if the assignment makes the formula false
bool formulaNotSatisfied(const vector<vector<int>>& clauses, unordered_map<int, bool>& assignment)
{
    for (const vector<int> clause : clauses)
    {
        int f = 1;
        for (int literal : clause)
        {
            int key = (literal > 0) ? literal : (-literal);
            if ((assignment.find(key) != assignment.end()) && ((assignment[key] == 1 && literal < 0) || (assignment[key] == 0 && literal > 0)))
            {
                continue;
            }
            else
            {
                f = 0;
                break;
            }
        }

        if (f == 1)
        {
            return true;
        }
        
    }

    return false;;
 
}

//check if the assignment makes the formula true
bool formulaSatisfied(const vector<vector<int>>& clauses, const unordered_map<int, bool>& assignment)
{
    for (const vector<int>& clause : clauses)
    {
        bool clauseSatisfied = false;

        for (int literal : clause)
        {
            int key = abs(literal);
            if (assignment.find(key) != assignment.end() && assignment.at(key) == (literal > 0))
            {
                clauseSatisfied = true;
                break;
            }
        }

        if (!clauseSatisfied)
        {
            return false;
        }
    }

    return true;
}

//checkAssignment method
void checkAssignment(vector<vector<int>>& clauses,unordered_map<int, bool>& assignment)
{
    if (formulaNotSatisfied(clauses,assignment))
    {
        cout<<"Formula is not satisfied for the given assignment";
    }
    else
    {
        if (formulaSatisfied(clauses,assignment))
        {
            cout<<"Formula is satisfied for the given assignment";
        }
    }
    
}

int main()
{
    //Formula in CNF form
    vector<vector<int>> clauses = {
        {1, 2, 3},
        {1,2,-3},
        {1,-2,3},
        {1,-2,-3},
        {-1,2,3},
        {-1,2,-3},
        {-1,-2,3},
        {-1,-2,-3}
    };

    //Take the truth values of variables from user
    unordered_map<int, bool> assignment;
    int n,a,b;
    cout<<"Enter the number of variables "<<endl;
    cin>>n;
    cout<<"Enter the pair<variable, truth value>"<<endl;
    for(int i = 0; i<n; i++){
        cin>>a>>b;
        assignment.insert(pair<int,int>(a,b));
    }

    //calling the check assignment method
    checkAssignment(clauses, assignment);
}
