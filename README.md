# Design of Algorithms (DA) - 2nd Project

## Routing Algorithm for Ocean Shipping and Urban Deliveries

The goal of this assignment is twofold. First, implement a basic exhaustive approach for the classic routing
problem using the TSP abstraction, therefore learning first-hand that although such an approach can find
optimal solutions, its applicability is restricted to very small graphs. Second, refine your critical thinking
skills, by developing and analysing a set of approximate solutions to the TSP. 


In this programming project, students are asked to design efficient algorithms to find optimal routes for vehicles in generic shipping and delivery scenarios, from urban deliveries to ocean shipping. 

This problem corresponds to the TSP. As the TSP is intractable, there are no known efficient algorithms to solve it. 

Backtracking techniques can find the optimal solution to this problem. If the graph is small, the application of these approaches might be reasonable. However, as they will conclude in this project, their application
to large graphs is infeasible, due to their high computational complexity. Therefore, approximation
algorithms based on heuristics need to be devised to efficiently address TSP-based problems. This class of
approaches provide in many cases near-optimal solutions and may also prove bounds on the ratio between
the approximate and the optimal solutions.

In this project students are asked to design efficient solutions to the TSP applied to diverse scenarios. They will
be given multiple graphs and a starting point. 

Additionally, students will implement a backtracking algorithm to the TSP. Although this algorithm is not
efficient, it will enable them to determine the optimal solution to this problem for small graphs. These results
can help them analyse the optimality of your heuristics on small graphs.
