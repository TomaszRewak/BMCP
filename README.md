# BMCP
Bandwidth Multi Coloring Problem slover written in C++

The metaheuristic is based on genetic and greedy algorithms. 

It consists of separate modules:

# Genetic algorithm
Abstract genetic algorithm, that can be also used for sloving any other problem due to its modular structure.
Here is an example of initializing and running created GA:
```
auto ga = GA::Builder::std()
    .withInitialPopulation<BMCP_GA::InitialPopulation>(graph, 100)
    .withStopCondition<BMCP_GA::TimeStopCondition>(2000)
    .with<BMCP_GA::RingSelection>(0.1)
    .with<BMCP_GA::Mutation>(0.2)
    .with<BMCP_GA::Crossing>(graph, 0.2)
    .with<BMCP_GA::Fitness>(graph)
    .with<BMCP_GA::Restore>(100)
    .with<FitnessLog>();
ga.start();
```
New components can be created be inheriting ```Component``` class. Components are used in a pipeline to transform one population into another.

# BMCP
The main component here is ```Greedy``` class that enables user to compute a coloring based on a graph definition and a vector containing an order of colors assigning. 

Graph class is able to store a BMCP graph definition. 
Also implemented is ```std::ostream& operator<<(std::ostream& stream, Graph& graph)``` operator, so new graphs can be easily read from a file input. It requires a graph definition structure as in examples in ```In/``` directory.

# Tabu
Here defined is a fast and low memory consuming tabu table. Main operations that one can do on it is to insert a new vector of numbers, check if a provided vector already exists and remove the oldes vector from the table. By default it searches for exactly the same vector when asked, but you can creat a tabu table (by specifying ```maxDiff``` parameter) that will treat elements as same when a sum of differences between next values is less then a bandwidth.
In a standars scenario (when the bandwidth = 0) all main (adding, checking and removing) operations have pessimistic complexity of ```N*M```, where ```N``` is a length of a vector and ```M``` is maximum number of values that a single node can have. An expected complexity is closer to the O(N) tho, as the whole thing is based on a tree structure (that is stored inside of on array, so it's not too memory consuming). 

I have tested it for sloving BMCP, but it doesn't seem to have any impact to results. So I'm not using it anymore, but the structure as it is might be used for different projects in the future. 

# BMCP_GA
This project defines some classes that combine BMCP
 with genetic algorithms.

# Test
This project uses all previously defined modules to compute graphs stored in ```In/``` directory.

# Compilation
I have created this project in a VS, so I'm shipping it with all files necessary to compile the code in it. The compilation process produces a Test.exe file inside a Release directory. The project itself doesn't use any platform-specific operations, so it can be easily ported, compiled and reused with other IDEs/compilers on other platforms.

# Testing
To test the program on provided test cases from ```In``` directory you have to run Release/Test.exe file from within solution directory. It will log some information on the console and output more details into ```Out``` directory. You might want to create the ```Out``` directory yourself, as it might not get created automatically (also within the main solution directory). 
