#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

bool dpll(vector<vector<int>>& clauses, unordered_map<int, bool>& assignment)
{
    // Remove clauses containing literals
    for (auto it = clauses.begin(); it != clauses.end();)
    {
        bool removeClause = false;
        for (int literal : *it)
        {
            int key = abs(literal);
            int value = (literal > 0) ? true : false;

            if (assignment.find(key) != assignment.end())
            {
                int assignedValue = assignment[key];
                if (value == assignedValue)
                {
                    removeClause = true;
                    break;
                }
            }
        }

        if (removeClause)
        {
            it = clauses.erase(it);
        }
        else
        {
            ++it;
        }
    }

    // If formula contains no clauses, return true
    if (clauses.empty())
    {
        return true; // All clauses are satisfied
    }

    // Shorten the clause containing the literal
    for (auto& clause : clauses)
    {
        for (auto it = clause.begin(); it != clause.end();)
        {
            int literal = *it;
            int key = abs(literal);
            int value = (literal > 0) ? true : false;

            if (assignment.find(key) != assignment.end())
            {
                int assignedValue = assignment[key];
                if (value != assignedValue)
                {
                    it = clause.erase(it);
                }
                else
                {
                    ++it;
                }
            }
            else
            {
                ++it;
            }
        }
    }

    // If formula contains an empty clause, return false
    for (const auto& clause : clauses)
    {
        if (clause.empty())
        {
            return false; // Conflict detected
        }
    }

    // Choose a literal from the formula
    int literal = clauses[0][0];

    // Assign the selected literal a truth value
    assignment[abs(literal)] = (literal > 0) ? true : false;

    // Recursive call 1
    if (dpll(clauses, assignment))
    {
        return true;
    }

    // Change the assignment of the selected literal
    assignment[abs(literal)] = !assignment[abs(literal)];

    // Recursive call 2
    return dpll(clauses, assignment);
}

int main()
{
    vector<vector<int>> clauses = {
        {1, 2, 3},
        {-1, -3},
        {2, 3},
        {-2}
    };

    unordered_map<int, bool> assignment;
    bool satisfiable = dpll(clauses, assignment);

    if (satisfiable)
    {
        cout << "SATISFIABLE\n";
    }
    else
    {
        cout << "UNSATISFIABLE\n";
    }

    return 0;
}
