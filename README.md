Ant Colony Implementation algorithm for the IA course of UTALCA

How to use:

you need to pass as param the tsp file ,number of ants, alpha, beta and the evaporation rate

NOTE: the tsp file must be in the format that is in the example. Also this assume that it will always be an Euclidian and complete graph

Example:

./ACO a280.tsp 1000 1 1 0.5

this mean that it will execute the program with the a280.tsp test file , 1000 ants, alpha and beta equal to 1 and an evaporation rate of 0.5

The closest path that I've reach without getting bored was 3178.31 with next params 1000 3 2 0.3

For 1000 Ants it took approximate 30000 ms 

If I change the evaporation rate or the number of ants I can see that with a bigger evaporation rata and a low number of ants is better than a low pheromone ratio with a lot of ants.
